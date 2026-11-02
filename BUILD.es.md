[English](BUILD.md) | **Español**

# Compilación — Ubuntu 26.04 Resolute, amd64, X11

## Dependencias de compilación

```sh
sudo apt install build-essential cmake qtbase5-dev libqt5svg5-dev \
  libqt5x11extras5-dev qttools5-dev qttools5-dev-tools libx11-dev \
  libx11-xcb-dev libgtest-dev libgmock-dev python3
```

## Compilar sin instalar Birdtray

Desde la raíz de las fuentes:

```sh
cmake -S . -B build -DCMAKE_POLICY_VERSION_MINIMUM=3.5 \
  -DCMAKE_BUILD_TYPE=Release -DCMAKE_SKIP_RPATH=ON \
  -DBIRDTRAY_TEST_ISOLATION=OFF -DBUILD_WITH_TESTS=ON
cmake --build build -j4
```

## Verificar sin abrir ventanas

```sh
mkdir -p build/test-env/config build/test-env/cache build/test-env/runtime
chmod 700 build/test-env/runtime
XDG_CONFIG_HOME="$PWD/build/test-env/config" \
XDG_CACHE_HOME="$PWD/build/test-env/cache" \
XDG_RUNTIME_DIR="$PWD/build/test-env/runtime" \
QT_QPA_PLATFORM=offscreen QT_QPA_PLATFORMTHEME= \
ctest --test-dir build --output-on-failure
```

Las muestras incluidas en `tests/res` proceden del proyecto original.
La prueba del monitor utiliza archivos temporales y configuración aislada.

## Generar el paquete

```sh
python3 local-packaging/package.py build \
  'birdtray_1.13.0-1.resolute1_x11_amd64.deb'
```

El script prepara un directorio temporal, genera el paquete con `dpkg-deb` y
retira el directorio temporal. No instala ni ejecuta Birdtray.

Las dependencias del paquete están en `local-packaging/control`. La configuración
`BIRDTRAY_TEST_ISOLATION=OFF` produce la aplicación normal con las rutas originales.
