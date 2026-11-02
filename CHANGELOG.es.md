[English](CHANGELOG.md) | **Español**

# Cambios

## 1.13.0 — Resolute / X11 — 2026-11-02

Publicación comunitaria basada en Birdtray v1.11.4, commit `7261ff0`.

- Recuperación de rutas perdidas de QFileSystemWatcher al sustituir o borrar índices.
- Relectura de recuperación cada 30 segundos cuando el intervalo del usuario es cero.
- Agrupación de cambios con espera acotada durante escrituras continuas.
- Vigilante asociado al hilo del monitor y parada de temporizadores en ese hilo.
- Retirada de rutas desconfiguradas y límite de conversión de intervalos.
- Prueba de regresión del monitor con doce comprobaciones.
- Empaquetado Debian como `birdtray`, con rutas y configuración habituales.
- Versión y Acerca de identificados como edición comunitaria Resolute / X11.

Las correcciones funcionales son las de la edición 1.12.0 que se ha probado en
Kubuntu 26.04. Esta publicación cambia numeración y documentación, conservando
el comportamiento del monitor.

Versión interna Debian: `1.13.0-1~resolute1`.
Nombre del archivo: `birdtray_1.13.0-1.resolute1_x11_amd64.deb`.

### Limitación comprobada

Thunderbird puede mostrar un contador en pantalla distinto del persistido en su
índice local después de reanudar. Birdtray refleja el contador del índice; abrir
la carpeta en Thunderbird corrigió la diferencia en el caso investigado.
