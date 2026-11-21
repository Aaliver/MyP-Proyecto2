# Proyecto 2: Base de datos musical

## Requisitos

Se requiere tener instalados:

+ C++17
+ Qt6
+ SQLite3 3.33.0
+ Meson
+ Ninja
+ Doxygen (opcional para generar la documentación)

## Construcción

Para compilar el programa:

```
meson setup build
meson compile -C build
```

Con el ejecutable generado en el directorio `build/src/main/db`

## Ejecución

El programa recibe un directorio de entrada. Este directorio es el que el
programa minara para obtener la información de la base de datos.

```
./build/src/main/db/musical-db ruta/archivos/mp3
```

## Documentación

Este proyecto esta configurado para que la documentación se genere al compilar
siempre que se cuente con Doxygen instalado.

La documentación generada se puede revisar en `docs/html/index.html`
