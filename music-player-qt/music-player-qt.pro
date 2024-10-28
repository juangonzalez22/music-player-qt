# Esta línea indica que el proyecto usará módulos de Qt específicos.
# "core" y "gui" son módulos estándar de Qt que permiten crear interfaces gráficas y manejar aspectos básicos de la aplicación.
# "multimedia" permite trabajar con contenido multimedia (audio, video, etc.).
# "multimediawidgets" incluye widgets específicos para trabajar con multimedia, como controles para videos.
QT += core gui multimedia multimediawidgets

# Esta línea especifica que si la versión mayor de Qt es superior a 4,
# se incluirá también el módulo "widgets", que contiene widgets básicos como botones, etiquetas, etc.
# Los widgets son componentes gráficos que el usuario puede ver y con los cuales puede interactuar.
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Aquí se especifica que el proyecto debe ser compilado utilizando el estándar de C++17.
# C++17 es una versión específica del lenguaje de programación C++ que incluye ciertas características y mejoras.
CONFIG += c++17

# Esta línea está comentada actualmente, pero si la descomentamos, activaría una macro que desactiva el uso de APIs (funciones y características) obsoletas que fueron marcadas como deprecated (descontinuadas) antes de Qt 6.0.0.
# Esto puede ayudar a evitar usar funciones que ya no se recomiendan o que eventualmente podrían desaparecer en versiones futuras de Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# "SOURCES" define todos los archivos fuente (.cpp) que forman parte del proyecto.
# Estos archivos contienen el código en C++ que será compilado para formar la aplicación.
# En este caso, tenemos dos archivos fuente: "main.cpp" y "mainwindow.cpp".
SOURCES += \
    main.cpp \        # Archivo fuente principal que normalmente contiene el punto de entrada del programa (la función main).
    mainwindow.cpp    # Archivo fuente que contiene la implementación de la ventana principal (MainWindow) de la aplicación.

# "HEADERS" define todos los archivos de encabezado (.h) que forman parte del proyecto.
# Los archivos de encabezado suelen declarar clases, funciones y variables que se usan en los archivos fuente.
# En este caso, tenemos un archivo de encabezado llamado "mainwindow.h".
HEADERS += \
    mainwindow.h      # Archivo de encabezado que contiene la declaración de la clase MainWindow (ventana principal de la aplicación).

# "FORMS" define los archivos de interfaz de usuario (.ui) que forman parte del proyecto.
# Los archivos .ui son archivos XML que describen la interfaz gráfica del usuario y son generados por Qt Designer.
# En este caso, solo tenemos un archivo de formulario: "mainwindow.ui".
FORMS += \
    mainwindow.ui     # Archivo de diseño de la interfaz gráfica de la ventana principal, creado con Qt Designer.

# Estas líneas especifican las reglas de despliegue predeterminadas para cuando se instala el programa.
# "target.path" define la ruta donde se copiará el archivo ejecutable tras la compilación.
# Las rutas dependen del sistema operativo: si el sistema es "qnx" (sistema operativo en tiempo real), la ruta será "/tmp/$${TARGET}/bin".
# Si es un sistema Unix (no Android), la ruta será "/opt/$${TARGET}/bin".
# "$${TARGET}" es una variable que se reemplaza con el nombre del objetivo o del ejecutable del proyecto.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin

# Esta última línea añade "target" a la lista de instalaciones si no está vacía.
# Esto significa que, si la variable target.path tiene una ruta definida, el objetivo de instalación se añade a la lista de instalaciones (INSTALLS), lo que permite que se copie correctamente durante la instalación del proyecto.
!isEmpty(target.path): INSTALLS += target

#Añadimos un archivo de recursos para los íconos de los botones de la interfaz.
RESOURCES += \
    resources.qrc
