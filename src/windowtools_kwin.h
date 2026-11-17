// Community Plasma Wayland backend, GPLv3.
#pragma once

#include "windowtools.h"
#include <QDBusContext>
#include <QString>

class WindowTools_KWin : public WindowTools, protected QDBusContext
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.birdtray.KWinResult")
public:
    WindowTools_KWin();
    bool lookup() override;
    bool show() override;
    bool hide() override;
    bool isHidden() override { return hidden; }
    bool closeWindow() override;
    bool isValid() override { return found; }

public slots:
    Q_SCRIPTABLE void report(const QString &token, const QString &state);

private:
    bool run(const QString &operation);
    bool busy = false;
    bool found = false;
    bool hidden = false;
    QString token;
    QString result;
    QString kwinOwner;
    QString windowId;
    bool taskbarWasSkipped = false;
    bool pagerWasSkipped = false;
};
