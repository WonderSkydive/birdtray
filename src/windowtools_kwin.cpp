// Community Plasma Wayland backend, GPLv3.
// The KWin scripting approach was inspired by stark1tty/birdtray-wayland.
#include "windowtools_kwin.h"
#include "birdtrayapp.h"
#include "log.h"
#include <QDBusConnection>
#include <QDBusConnectionInterface>
#include <QDBusMessage>
#include <QEventLoop>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QScopedValueRollback>
#include <QTemporaryFile>
#include <QTimer>
#include <QUuid>

static const QString service = QStringLiteral("org.kde.KWin");
static const QString scripting = QStringLiteral("org.kde.kwin.Scripting");
static const QString resultPath = QStringLiteral("/Birdtray/KWinResult");

WindowTools_KWin::WindowTools_KWin()
{
    QDBusConnection::sessionBus().registerObject(resultPath, this, QDBusConnection::ExportScriptableSlots);
}

void WindowTools_KWin::report(const QString &key, const QString &state)
{
    if (busy && calledFromDBus() && message().service() == kwinOwner && key == token)
        result = state;
}

bool WindowTools_KWin::run(const QString &operation)
{
    if (busy) return false;
    QScopedValueRollback<bool> guard(busy, true);
    auto bus = QDBusConnection::sessionBus();
    if (!bus.interface()) return false;
    kwinOwner = bus.interface()->serviceOwner(service).value();
    if (kwinOwner.isEmpty()) return false;
    token = QUuid::createUuid().toString(QUuid::WithoutBraces);
    result.clear();

    const auto settings = BirdtrayApp::get()->getSettings();
    const QJsonArray args{operation, bus.baseService(), resultPath, token, windowId,
                         settings->mThunderbirdProcessName, taskbarWasSkipped, pagerWasSkipped,
                         settings->mHideWhenMinimized, settings->mThunderbirdWindowMatch.trimmed()};
    // JSON encoding keeps configuration strings data rather than script code.
    const QByteArray script = "const a = " + QJsonDocument(args).toJson(QJsonDocument::Compact) + R"JS(;
let state = {found:false};
const matches = workspace.windowList().filter(w => {
    const cls = String(w.resourceClass).toLowerCase();
    const desktop = String(w.desktopFileName).toLowerCase().replace(/\.desktop$/, "");
    const configured = String(a[5]).toLowerCase();
    if (!w.normalWindow || w.transient) return false;
    return cls === "thunderbird" || cls === "org.mozilla.thunderbird" ||
           desktop === "thunderbird" || desktop === "org.mozilla.thunderbird" ||
           (configured.length > 0 && cls === configured);
});
let w = matches.find(x => String(x.internalId) === a[4]);
if (!w && a[0] !== "probe" && a[4]) {
    // Do not act on a different window if the selected window closed.
} else if (!w) {
    const main = matches.filter(x => a[9] && String(x.caption).includes(a[9]));
    const candidates = main.length ? main : matches;
    w = candidates.find(x => x === workspace.activeWindow) || candidates[0];
}
if (w) {
    const remembered = String(w.internalId) === a[4];
    let skipTaskbar = remembered ? a[6] : Boolean(w.skipTaskbar);
    let skipPager = remembered ? a[7] : Boolean(w.skipPager);
    const wasHidden = remembered && w.skipTaskbar && w.skipPager && w.minimized;
    if ((a[0] === "hide" || (a[0] === "probe" && a[8] && w.minimized)) && w.minimizable) {
        if (!wasHidden) {
            skipTaskbar = Boolean(w.skipTaskbar);
            skipPager = Boolean(w.skipPager);
        }
        w.minimized = true;
        if (w.minimized) {
            w.skipTaskbar = true;
            w.skipPager = true;
        }
    } else if (a[0] === "show" || a[0] === "close" ||
               (remembered && !w.minimized && (w.skipTaskbar !== skipTaskbar || w.skipPager !== skipPager))) {
        if (remembered) {
            w.skipTaskbar = skipTaskbar;
            w.skipPager = skipPager;
        }
        if (a[0] === "show") {
            w.minimized = false;
            workspace.activeWindow = w;
        }
        if (a[0] === "close" && w.closeable) w.closeWindow();
    }
    state = {found:true, id:String(w.internalId), hidden:Boolean(w.minimized && w.skipTaskbar && w.skipPager),
             skipTaskbar:skipTaskbar, skipPager:skipPager, minimized:Boolean(w.minimized), closeable:Boolean(w.closeable)};
}
callDBus(a[1], a[2], "org.birdtray.KWinResult", "report", a[3], JSON.stringify(state));
)JS";
    QTemporaryFile file;
    if (!file.open() || file.write(script) != script.size() || !file.flush()) return false;
    file.close();
    const QString plugin = QStringLiteral("birdtray-") + token;
    auto call = [&](const QString &path, const QString &interface, const QString &method,
                    const QVariantList &values = {}) {
        auto message = QDBusMessage::createMethodCall(kwinOwner, path, interface, method);
        message.setArguments(values);
        return bus.call(message, QDBus::Block, 600);
    };
    const auto loaded = call("/Scripting", scripting, "loadScript", {file.fileName(), plugin});
    const int id = loaded.arguments().isEmpty() ? -1 : loaded.arguments().first().toInt();
    if (loaded.type() == QDBusMessage::ErrorMessage || id < 0) {
        call("/Scripting", scripting, "unloadScript", {plugin});
        return false;
    }
    const auto reply = call("/Scripting/Script" + QString::number(id), "org.kde.kwin.Script", "run");
    if (reply.type() != QDBusMessage::ErrorMessage && result.isEmpty()) {
        // Deliver KWin's callback without dispatching clicks during an operation.
        QEventLoop loop;
        QTimer poll;
        connect(&poll, &QTimer::timeout, &loop, [&] { if (!result.isEmpty()) loop.quit(); });
        poll.start(10);
        QTimer::singleShot(200, &loop, &QEventLoop::quit);
        loop.exec(QEventLoop::ExcludeUserInputEvents);
    }
    call("/Scripting", scripting, "unloadScript", {plugin});
    const auto state = QJsonDocument::fromJson(result.toUtf8()).object();
    if (!state.contains("found")) {
        Log::debug("No confirmation from KWin for Birdtray window operation");
        return false;
    }
    found = state.value("found").toBool();
    windowId = state.value("id").toString();
    const bool wasHidden = hidden;
    hidden = state.value("hidden").toBool();
    taskbarWasSkipped = state.value("skipTaskbar").toBool();
    pagerWasSkipped = state.value("skipPager").toBool();
    if (found && hidden != wasHidden) {
        if (hidden) emit onWindowHidden();
        else emit onWindowShown();
    }
    return found && (operation != "hide" || hidden) && (operation != "show" || !state.value("minimized").toBool())
                 && (operation != "close" || state.value("closeable").toBool());
}

bool WindowTools_KWin::lookup() { if (!busy) run("probe"); return found; }
bool WindowTools_KWin::show() { return run("show"); }
bool WindowTools_KWin::hide() { return run("hide"); }
bool WindowTools_KWin::closeWindow() { return run("close"); }
