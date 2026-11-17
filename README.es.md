# Birdtray para Thunderbird

[English](README.md)

Birdtray muestra los mensajes sin leer de Thunderbird en la bandeja del sistema y permite ocultar o restaurar su ventana. Esta edición comunitaria funciona en **X11 y KDE Plasma Wayland** sin extensiones de Thunderbird.

## Funciones

- Supervisa las carpetas que elijas y muestra el contador en distintos colores según la cuenta.
- Anima el icono al llegar correo nuevo y permite aplazar las notificaciones.
- Oculta y restaura Thunderbird desde la bandeja. También puede ocultarlo al minimizarlo.
- Puede iniciar Thunderbird junto con Birdtray, reabrirlo desde la bandeja o cerrarlo al salir de Birdtray.
- Permite personalizar el icono y redactar mensajes a partir de plantillas.

## Descarga e instalación

El paquete **1.14.0** está destinado a **Kubuntu 26.04 Resolute (amd64)**. El control de ventanas se probó en X11 y en KDE Plasma 6 con Wayland. Descarga el paquete Debian desde [Publicaciones](https://github.com/WonderSkydive/birdtray/releases/latest). La revisión actual del paquete es `1.14.0-2.resolute1`.

### Primera instalación

1. Instala Thunderbird si aún no lo tienes. Ábrelo y deja que sincronice al menos una vez para que Birdtray encuentre los índices de las carpetas.
2. Abre el archivo `Birdtray.deb` con Discover y pulsa **Instalar**. Si prefieres usar la terminal, ejecuta desde la carpeta de descargas:

   ```sh
   sudo apt install ./Birdtray.deb
   ```

3. Abre **Birdtray** desde el menú de aplicaciones. En **Preferencias → Supervisar**, selecciona las carpetas de Thunderbird que quieras vigilar.
4. En la pestaña **Ocultar**, elige si el icono de la bandeja debe ocultar o restaurar Thunderbird y si quieres ocultar su ventana al minimizarla.

### Actualizar una instalación existente

Si Birdtray está abierto, ciérralo desde el menú de la bandeja. Si activaste el cierre de Thunderbird al salir, también se cerrará Thunderbird. Instala el nuevo paquete con Discover o con el comando anterior y vuelve a abrir Birdtray. Se reutilizarán tus preferencias.

## Novedades de la 1.14.0

El control de ventanas en Plasma Wayland utiliza KWin. X11 sigue disponible y ambas sesiones usan el contador con la recuperación de la vigilancia de índices introducida en la edición comunitaria. Esta versión también actualiza la interfaz en inglés y español y los metadatos del paquete.

## Compilación y ayuda

Consulta [Compilar Birdtray](BUILD.es.md) para compilar, ejecutar las pruebas y generar el paquete. Para pedir ayuda, usa [Discusiones](https://github.com/WonderSkydive/birdtray/discussions). Si encuentras un fallo reproducible, indícalo en [Incidencias](https://github.com/WonderSkydive/birdtray/issues) con tu tipo de sesión y versión de Thunderbird.

## Créditos y licencia

WonderSkydive mantiene esta edición comunitaria, desarrollada a partir de [Birdtray 1.11.4](https://github.com/gyunaev/birdtray/tree/v1.11.4). La integración con KWin se inspiró en [stark1tty/birdtray-wayland](https://github.com/stark1tty/birdtray-wayland). Consulta los [créditos](CREDITS.md) y la [licencia GPLv3](LICENSE.txt).

[Support WonderSkydive](https://www.paypal.com/ncp/payment/KWEHYT4HDTARE)
