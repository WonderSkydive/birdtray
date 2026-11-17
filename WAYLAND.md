# Plasma Wayland

Birdtray selects its KWin integration in a native Plasma Wayland session and its
X11 integration in an X11 session. The same package supports both.

The KWin integration uses a temporary script to identify Thunderbird windows
by application identity, preferring the configured main-window title. It
restores the window's previous taskbar and pager settings when showing it again.

If a window action fails, open **Preferences → Advanced → Show log window**.
When reporting it, include the action, the session type, and whether the window
was shown, minimized, or hidden.
