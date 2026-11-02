# Changelog

[Español](CHANGELOG.es.md)

## 1.13.0 — Resolute / X11 — 2026-11-02

Community release based on Birdtray v1.11.4, commit `7261ff0`.

- Restore lost QFileSystemWatcher paths after index replacement or deletion.
- Use a 30-second recovery scan when the user's polling interval is zero.
- Bound read delays during continuous writes.
- Associate the watcher with the monitor thread and stop timers in that thread.
- Remove unconfigured paths and limit interval conversion.
- Add a monitor regression test with twelve checks.
- Package as `birdtray` using the standard executable and configuration paths.
- Identify the version and About dialog as the community Resolute / X11 edition.

Functional fixes are unchanged from the 1.12.0 edition tested on Kubuntu 26.04.
This release changes version numbering and documentation, retaining monitor behavior.

Debian version: `1.13.0-1~resolute1`.
Package filename: `birdtray_1.13.0-1~resolute1_x11_amd64.deb`.

### Observed limitation

After resume, Thunderbird may display a count different from the count persisted
in its local folder index. Birdtray reflects that index. In the investigated
case, opening the folder in Thunderbird corrected the discrepancy.
