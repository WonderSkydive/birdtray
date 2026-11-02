#include <QApplication>
#include <QTemporaryDir>
#include <QFile>
#include <QElapsedTimer>
#include <QThread>
#include <QTimer>
#include <cstdio>
#include <functional>
#include "unreadmonitor.h"
#include "settings.h"

static bool waitFor(const std::function<bool()> &condition, int timeout = 3500) {
    QElapsedTimer time; time.start();
    while (!condition() && time.elapsed() < timeout) {
        QCoreApplication::processEvents();
        QThread::msleep(5);
    }
    return condition();
}
static bool writeFixture(const QString &path, const QString &name, bool replace = false) {
    QFile input(QString(FIXTURES) + "/" + name);
    if (!input.open(QIODevice::ReadOnly)) return false;
    const QByteArray data = input.readAll();
    const QString destination = replace ? path + ".new" : path;
    QFile output(destination);
    if (!output.open(QIODevice::WriteOnly | QIODevice::Truncate)) return false;
    if (output.write(data) != data.size()) return false;
    output.close();
    if (replace) return std::rename(qPrintable(destination), qPrintable(path)) == 0;
    return true;
}
int main(int argc, char **argv) {
    QTemporaryDir configRoot;
    qputenv("XDG_CONFIG_HOME", configRoot.path().toUtf8());
    qputenv("XDG_CACHE_HOME", configRoot.path().toUtf8());
    qputenv("QT_QPA_PLATFORMTHEME", "");
    QApplication app(argc, argv);
    QTemporaryDir temp;
    const QString path = temp.path() + "/Inbox.msf";
    Settings settings;
    settings.mWatchFileTimeout = 150;
    settings.mIndexFilesRereadIntervalSec = 1;
    settings.watchedMorkFiles[path] = QColor(Qt::red);
    int last = -1;
    writeFixture(path, "6_Unread_Inbox.msf");
    UnreadMonitor monitor(nullptr, &settings);
    QObject::connect(&monitor, &UnreadMonitor::unreadUpdated, &app,
                     [&](unsigned int count, QColor) { last = int(count); });
    monitor.start();
    int failures = 0;
    auto check = [&](bool ok, const char *name) {
        std::printf("%s: %s\n", ok ? "PASS" : "FAIL", name);
        failures += !ok;
    };
    check(waitFor([&]{return last == 6;}), "initial unread count");
    writeFixture(path, "1_Unread_Filter.msf", true);
    check(waitFor([&]{return last == 1;}), "atomic replacement");
    writeFixture(path, "6_Unread_Inbox.msf");
    check(waitFor([&]{return last == 6;}), "watch rearmed after replacement");
    QFile::remove(path);
    check(waitFor([&]{return last == 0;}), "missing file handled");
    writeFixture(path, "1_Unread_Filter.msf");
    check(waitFor([&]{return last == 1;}), "recreation recovered by polling");
    writeFixture(path, "6_Unread_Inbox.msf");
    check(waitFor([&]{return last == 6;}), "watch rearmed after recreation");
    // Disable fast polling to ensure a continuous event burst is handled by
    // the bounded debounce, rather than the recovery timer.
    QMetaObject::invokeMethod(&monitor, [&]{
        settings.mIndexFilesRereadIntervalSec = 0;
        monitor.slotSettingsChanged();
    }, Qt::BlockingQueuedConnection);
    QTimer writer;
    writer.setInterval(20);
    QObject::connect(&writer, &QTimer::timeout, [&]{writeFixture(path, "1_Unread_Filter.msf");});
    writer.start();
    check(waitFor([&]{return last == 1;}, 750), "continuous writes do not starve reads");
    writer.stop();
    writeFixture(path, "6_Unread_Inbox.msf");
    QMetaObject::invokeMethod(&monitor, "forceUpdateUnread", Qt::BlockingQueuedConnection);
    check(waitFor([&]{return last == 6;}), "reset before replacement without fast polling");
    writeFixture(path, "1_Unread_Filter.msf", true);
    check(waitFor([&]{return last == 1;}, 750), "replacement without fast polling");
    writeFixture(path, "6_Unread_Inbox.msf");
    check(waitFor([&]{return last == 6;}, 750), "watch rearmed without fast polling");
    QFile::remove(path);
    check(waitFor([&]{return last == 0;}), "deletion with user polling disabled");
    writeFixture(path, "6_Unread_Inbox.msf");
    check(waitFor([&]{return last == 6;}, 33000), "default 30-second recovery scan");
    monitor.quit(); monitor.wait();
    return failures ? 1 : 0;
}
