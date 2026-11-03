[English](README.md) | **Español**

# Birdtray para Thunderbird — Resolute / X11

Birdtray lleva Thunderbird a la bandeja del sistema de Linux: consulta el contador
de mensajes sin leer, oculta y restaura su ventana y accede a acciones de correo
sin instalar ninguna extensión en Thunderbird.

Esta edición está empaquetada para **Ubuntu 26.04 Resolute, amd64 y X11**.

**Comprobado en Kubuntu 26.04 con Plasma 6 y X11**, mediante varias semanas de uso.

Versión comunitaria **1.13.0**, basada en el código fuente de
[Birdtray 1.11.4](https://github.com/gyunaev/birdtray/tree/v1.11.4).
Conserva la licencia GPLv3 y los créditos del proyecto original.

## Funciones

- Mostrar el contador de mensajes sin leer en el icono de la bandeja.
- Hacer parpadear o animar el icono mientras haya correo sin leer, opcionalmente.
- Posponer la indicación de correo sin leer de Birdtray durante un tiempo elegido.
- Supervisar las carpetas de correo seleccionadas y asignarles colores distintos.
- Ocultar y restaurar la ventana de Thunderbird desde el icono o su menú.
- Abrir Thunderbird al iniciar Birdtray y cerrarlo al salir, si se configura así.
- Personalizar los iconos de la bandeja y la fuente y los colores del contador.
- Detectar la presencia de la ventana de Thunderbird e indicar cuando está cerrada.
- Redactar nuevos correos desde el menú, con plantillas predefinidas opcionales.

Birdtray lee directamente los índices locales Mork (`.msf`) de las carpetas de
Thunderbird, por lo que no necesita ninguna extensión de Thunderbird.

## Descargar e instalar

En la sección **Releases** de este repositorio, descarga:

```text
birdtray_1.13.0-1.resolute1_x11_amd64.deb
```

Desde la carpeta donde lo hayas descargado:

```sh
sudo apt install './birdtray_1.13.0-1.resolute1_x11_amd64.deb'
```

Se instala como `birdtray`, actualiza las versiones anteriores de ese paquete y
conserva la configuración habitual. Cierra Birdtray antes de actualizarlo y
vuelve a abrirlo desde el menú de aplicaciones al terminar. Si está configurado
para cerrar Thunderbird al salir, ten presente ese comportamiento.

En una instalación nueva, selecciona en la configuración de Birdtray las carpetas
de correo que quieres supervisar. Puedes configurar también las acciones del
icono para mostrar y ocultar Thunderbird.

## Correcciones incluidas

- Recupera la vigilancia de índices `.msf` que Thunderbird elimina o sustituye.
- Vuelve a leer los índices periódicamente: si el intervalo configurado es cero,
  utiliza una comprobación de recuperación cada 30 segundos.
- Evita que una secuencia continua de escrituras aplace indefinidamente la lectura.
- Mantiene el vigilante en el hilo correspondiente y detiene sus temporizadores
  en ese hilo al terminar.
- Retira rutas que dejan de estar configuradas y evita el desbordamiento del
  intervalo al convertir segundos en milisegundos.

El acceso del menú utiliza el backend X11. La edición usa Qt 5.15.18 de Ubuntu
26.04 y puede ejecutarse en Plasma 6.

## Contador después de suspender o hibernar

Birdtray consulta el contador que Thunderbird guarda en el índice local de cada
carpeta. En un caso comprobado, Thunderbird mostraba cero en pantalla mientras
su índice aún guardaba cuatro; al abrir la carpeta, el índice pasó a cero y
Birdtray reflejó el cambio inmediatamente.

Si ocurre esa diferencia, abrir la carpeta en Thunderbird puede actualizar su
índice. La relectura periódica de Birdtray refleja el valor disponible en disco.

## Desinstalar

```sh
sudo apt remove birdtray
```

Se retiran los archivos del paquete. La configuración personal se conserva.
Después puedes instalar otra versión si lo deseas. Las dependencias compartidas
se gestionan con el comportamiento habitual de APT.

## Compilar y verificar

Las instrucciones están en [BUILD.es.md](BUILD.es.md). El paquete no incorpora servicios,
autoinicio ni scripts que abran o cierren aplicaciones al instalarse.

Las siete pruebas automáticas cubren el parser y sus muestras, las utilidades y
la recuperación del monitor ante sustitución, borrado y recreación de índices,
escrituras continuas y recuperación periódica.

## Créditos y licencia

Proyecto original: [gyunaev/birdtray](https://github.com/gyunaev/birdtray).
Consulta [CREDITS.md](CREDITS.md), [CHANGELOG.es.md](CHANGELOG.es.md) y
[LICENSE.txt](LICENSE.txt). Los créditos de autores y traducciones del programa
se conservan. La numeración 1.13.0 identifica esta modificación comunitaria.
