# Build — Ubuntu 26.04 Resolute, amd64, X11

[Español](BUILD.es.md)

## Build dependencies

```sh
sudo apt install build-essential cmake qtbase5-dev libqt5svg5-dev \
  libqt5x11extras5-dev qttools5-dev qttools5-dev-tools libx11-dev \
  libx11-xcb-dev libgtest-dev libgmock-dev python3
```

## Compile without installing Birdtray

From the source directory:

```sh
cmake -S . -B build -DCMAKE_POLICY_VERSION_MINIMUM=3.5 \
  -DCMAKE_BUILD_TYPE=Release -DCMAKE_SKIP_RPATH=ON \
  -DBIRDTRAY_TEST_ISOLATION=OFF -DBUILD_WITH_TESTS=ON
cmake --build build -j4
```

## Test without opening windows

```sh
mkdir -p build/test-env/config build/test-env/cache build/test-env/runtime
chmod 700 build/test-env/runtime
XDG_CONFIG_HOME="$PWD/build/test-env/config" \
XDG_CACHE_HOME="$PWD/build/test-env/cache" \
XDG_RUNTIME_DIR="$PWD/build/test-env/runtime" \
QT_QPA_PLATFORM=offscreen QT_QPA_PLATFORMTHEME= \
ctest --test-dir build --output-on-failure
```

Fixtures in `tests/res` come from the original project. The monitor test uses
temporary files and isolated configuration.

## Package

```sh
python3 local-packaging/package.py build \
  'birdtray_1.13.0-1.resolute1_x11_amd64.deb'
```

The script stages files in a temporary directory, builds the Debian package
with `dpkg-deb`, and removes the temporary directory. It does not install or
run Birdtray.

Package dependencies are in `local-packaging/control`.
`BIRDTRAY_TEST_ISOLATION=OFF` builds the normal application with its standard paths.
