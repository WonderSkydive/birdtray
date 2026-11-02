# Birdtray — Resolute / X11

**English** | [Español](README.es.md)

Unread-mail system tray counter and Thunderbird window controls for
**Ubuntu 26.04 Resolute, amd64, X11**.

**Tested on Kubuntu 26.04 with Plasma 6 and X11**, through several weeks of use.

Community edition **1.13.0**, based on the source code of
[Birdtray 1.11.4](https://github.com/gyunaev/birdtray/tree/v1.11.4).
The original GPLv3 license and author credits are retained.

## Download and install

Open this repository's [Releases](https://github.com/WonderSkydive/birdtray/releases)
page and download:

```text
birdtray_1.13.0-1~resolute1_x11_amd64.deb
```

From the download directory:

```sh
sudo apt install './birdtray_1.13.0-1~resolute1_x11_amd64.deb'
```

The package installs as `birdtray`, upgrades earlier versions of that package,
and retains the usual configuration. Quit Birdtray before upgrading, then open
it again from your application menu. If Birdtray is configured to close
Thunderbird when it exits, keep that behavior in mind.

On a fresh installation, select the mail folders to monitor in Birdtray's
settings. You can also configure tray actions to show and hide Thunderbird.

## Fixes

- Restore watches on `.msf` indexes replaced or recreated by Thunderbird.
- Periodically reread indexes: a configured interval of zero uses a 30-second
  recovery scan.
- Bound the read delay during continuous index writes.
- Keep the file watcher in the monitoring thread and stop timers in that thread
  before it exits.
- Remove paths no longer configured and prevent interval-conversion overflow.

The application-menu launcher selects the X11 backend. This edition uses
Ubuntu 26.04's Qt 5.15.18 libraries and can run on Plasma 6.

## Counter after suspend or hibernate

Birdtray reads the counter stored in each folder's local Thunderbird index.
In an investigated case, Thunderbird displayed zero while its index still
stored four. Opening the folder updated the index to zero, which Birdtray
reflected immediately.

If this discrepancy occurs, opening the folder in Thunderbird may refresh its
index. Birdtray's periodic reads reflect the value available on disk.

## Uninstall

```sh
sudo apt remove birdtray
```

Package files are removed; personal settings are retained. You can subsequently
install another version. Shared dependencies follow normal APT behavior.

## Build and verify

See [BUILD.md](BUILD.md) ([Español](BUILD.es.md)). The package adds no services,
autostart entries, or maintainer scripts that launch or stop applications.

All seven automated tests pass. They cover the parser and its fixtures,
utilities, and monitor recovery after index replacement, deletion, recreation,
continuous writes, and periodic recovery.

## Credits and license

Original project: [gyunaev/birdtray](https://github.com/gyunaev/birdtray).
See [CREDITS.md](CREDITS.md), [CHANGELOG.md](CHANGELOG.md)
([Español](CHANGELOG.es.md)), and [LICENSE.txt](LICENSE.txt).
Original author and translator credits are retained. Version 1.13.0 identifies
this community modification, rather than an upstream release.
