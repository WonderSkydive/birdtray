# Birdtray for Thunderbird — X11 and Plasma Wayland

[Español](README.es.md)

Birdtray shows Thunderbird's unread mail count in the system tray and lets you hide or restore its window. This community edition runs on **X11 and KDE Plasma Wayland** without a Thunderbird extension.

## Features

- Monitor selected mail folders and use different counter colors for different accounts.
- Animate the tray icon for new mail or snooze notifications.
- Hide or restore Thunderbird from the tray, including automatically hiding a minimized window.
- Optionally start Thunderbird with Birdtray, reopen it from the tray, or close it when Birdtray exits.
- Customize the tray icon and create messages from email templates.

## Download and install

The **1.14.0** package targets **Ubuntu 26.04 Resolute (amd64)** and was tested on Kubuntu 26.04 with Plasma 6 in X11 and Wayland sessions. Download the Debian package from [Releases](https://github.com/WonderSkydive/birdtray/releases/latest). The current package revision is `1.14.0-3.resolute1`.

### First installation

1. Install Thunderbird first if you do not already have it. Open it and let it sync at least once so Birdtray can find its folder indexes.
2. Open the downloaded `birdtray_1.14.0-3.resolute1_amd64.deb` in Discover and select **Install**. For a terminal installation, run this from the download directory:

   ```sh
   sudo apt install ./birdtray_1.14.0-3.resolute1_amd64.deb
   ```

3. Launch **Birdtray**. In **Birdtray → Preferences → Advanced**, check that **Thunderbird command line** points to your Thunderbird executable. Change it if Thunderbird is installed elsewhere. Then use **Birdtray → Preferences → Monitor** to select the folders you want to track.
4. In the **Hide** tab, choose whether the tray icon should hide or restore Thunderbird and whether to hide its window when minimized.

### Updating an existing installation

Quit Birdtray from the tray menu if it is running. If you enabled the option to close Thunderbird on exit, this will close Thunderbird too. Install the new package using Discover or the command above, then reopen Birdtray. The package reuses your existing preferences.

## What's new in 1.14.0

Window controls on Plasma Wayland use KWin. X11 remains supported, and both sessions use the unread counter with the index-monitoring recovery introduced in the community edition. This release also updates English and Spanish interface text and packaging metadata.

## Build and support

See [Building Birdtray](BUILD.md) for build, test, and packaging instructions. For help, use [Discussions](https://github.com/WonderSkydive/birdtray/discussions). Report reproducible bugs in [Issues](https://github.com/WonderSkydive/birdtray/issues), including your desktop session and Thunderbird version.

## Credits and license

This community edition is maintained by WonderSkydive and builds on [Birdtray 1.11.4](https://github.com/gyunaev/birdtray/tree/v1.11.4). The KWin integration was inspired by [stark1tty/birdtray-wayland](https://github.com/stark1tty/birdtray-wayland). See [credits](CREDITS.md) and the [GPLv3 license](LICENSE.txt).

## Support the project

If you would like to support the work already done and the maintenance of this community edition, you can contribute here: [Support WonderSkydive](https://www.paypal.com/ncp/payment/KWEHYT4HDTARE)
