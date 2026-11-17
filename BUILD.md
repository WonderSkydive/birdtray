# Building Birdtray on Ubuntu 26.04

[Español](BUILD.es.md)

Install the build tools and Qt 5 development libraries:

```sh
sudo apt install build-essential cmake qtbase5-dev libqt5svg5-dev \
  libqt5x11extras5-dev qttools5-dev qttools5-dev-tools libx11-dev \
  libx11-xcb-dev libgtest-dev libgmock-dev python3 nodejs
```

Build and run the checks from the source directory:

```sh
cmake -S . -B build -DCMAKE_POLICY_VERSION_MINIMUM=3.5 \
  -DCMAKE_BUILD_TYPE=Release -DCMAKE_SKIP_RPATH=ON -DBUILD_WITH_TESTS=ON
cmake --build build -j4
mkdir -p build/test-env/{config,cache,runtime}
chmod 700 build/test-env/runtime
XDG_CONFIG_HOME="$PWD/build/test-env/config" \
XDG_CACHE_HOME="$PWD/build/test-env/cache" \
XDG_RUNTIME_DIR="$PWD/build/test-env/runtime" \
QT_QPA_PLATFORM=offscreen QT_QPA_PLATFORMTHEME= \
ctest --test-dir build --output-on-failure
node tests/kwin/test-window-actions.js
```

Generate the Debian package locally:

```sh
python3 local-packaging/package.py build birdtray_1.14.0-3.resolute1_amd64.deb
```

The packaging script stages the files in a temporary directory and runs
`dpkg-deb`. Package dependencies are listed in [control](local-packaging/control).
