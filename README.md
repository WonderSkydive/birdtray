# Birdtray for Thunderbird

[Español](README.es.md)

Birdtray shows Thunderbird's unread mail count in the system tray and lets you hide or restore its window. This community edition runs on **X11 and KDE Plasma Wayland** without a Thunderbird extension.

## Features

- Monitor selected mail folders and use different counter colors for different accounts.
- Animate the tray icon for new mail or snooze notifications.
- Hide or restore Thunderbird from the tray, including automatically hiding a minimized window.
- Optionally start Thunderbird with Birdtray, reopen it from the tray, or close it when Birdtray exits.
- Customize the tray icon and create messages from email templates.

## Download and install

The **1.14.0** Debian package targets **Kubuntu 26.04 Resolute (amd64)**. The 1.14 window integration was tested on X11 and Plasma 6 Wayland. Download it from [Releases](https://github.com/WonderSkydive/birdtray/releases/latest), close Birdtray if it is running, then open the file in Discover or run:

```sh
sudo apt install ./birdtray_1.14.0-1.resolute1_amd64.deb
```

The package upgrades an existing `birdtray` installation and uses its saved preferences. Launch Birdtray from the application menu and choose the Thunderbird folders in **Preferences → Monitor**.

## What's new in 1.14.0

Window controls on Plasma Wayland use KWin. X11 remains supported, and both sessions use the unread counter with the index-monitoring recovery introduced in the community edition. This release also updates English and Spanish interface text and packaging metadata.

## Build and support

See [Building Birdtray](BUILD.md) for build, test, and packaging instructions. For help, use [Discussions](https://github.com/WonderSkydive/birdtray/discussions). Report reproducible bugs in [Issues](https://github.com/WonderSkydive/birdtray/issues), including your desktop session and Thunderbird version.

## Credits and license

This community edition is maintained by WonderSkydive and builds on [Birdtray 1.11.4](https://github.com/gyunaev/birdtray/tree/v1.11.4). The KWin integration was inspired by [stark1tty/birdtray-wayland](https://github.com/stark1tty/birdtray-wayland). See [credits](CREDITS.md) and the [GPLv3 license](LICENSE.txt).

[Support WonderSkydive](https://www.paypal.com/ncp/payment/KWEHYT4HDTARE)
