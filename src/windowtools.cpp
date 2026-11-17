#include <QtCore>

#include "windowtools.h"
#if defined (Q_OS_WIN)
#  include "windowtools_win.h"
#elif defined (Q_OS_MAC)
// TODO
#else
#  include "windowtools_x11.h"
#  include "windowtools_kwin.h"
#  include <QGuiApplication>
#endif


WindowTools::WindowTools()
    : QObject()
{
}

WindowTools::~WindowTools()
{
}


WindowTools *WindowTools::create()
{
    static WindowTools * tools;

    if ( !tools )
    {
#if defined (Q_OS_WIN)
    tools = new WindowTools_Win();
#elif defined (Q_OS_MAC)
    tools = 0;
#else
    if (QGuiApplication::platformName().startsWith("wayland"))
        tools = new WindowTools_KWin();
    else
        tools = new WindowTools_X11();
#endif
    }

    return tools;
}
