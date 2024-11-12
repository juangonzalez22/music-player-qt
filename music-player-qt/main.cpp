#include "mainwindow.h"  // Incluye el archivo de encabezado "mainwindow.h".
    // Esto es necesario para que el compilador tenga conocimiento de la clase MainWindow,
    // que define la ventana principal de la aplicación.
    // Todas las funciones y variables de la clase MainWindow están declaradas en este archivo de encabezado.
    // De este modo, podemos crear una instancia de MainWindow más adelante en el código.

#include <QApplication>   // Incluye la biblioteca QApplication, que es esencial para cualquier aplicación gráfica en Qt.
    // QApplication gestiona los recursos globales de la aplicación, tales como el ciclo de eventos,
    // el comportamiento de las ventanas, y la interacción entre el sistema operativo y la interfaz gráfica de usuario (GUI).
    // Sin QApplication, no se puede crear una interfaz gráfica con Qt.

int main(int argc, char *argv[])
{
    // Aquí estamos creando una instancia de QApplication llamada "a".
    // "argc" y "argv" son los argumentos de línea de comandos que pueden ser usados para configurar la aplicación al iniciarla.
    // "argc" es el número de argumentos y "argv" es una lista de esos argumentos.
    // Si no necesitas argumentos específicos, solo se pasan directamente al constructor de QApplication.
    QApplication a(argc, argv);

    // Aquí se crea una instancia de la clase MainWindow, llamada "w".
    // Esto representa la ventana principal de la aplicación que contiene la interfaz gráfica y todos sus elementos (botones, sliders, etc.).
    // En este momento, la ventana "w" se ha creado, pero aún no es visible.
    MainWindow w;

    // Llama al método "show()" de la instancia "w", que hace que la ventana principal sea visible en la pantalla.
    // Esto le dice a Qt que muestre la ventana al usuario.
    w.show();

    // Aquí se inicia el ciclo de eventos de la aplicación llamando al método exec() de QApplication.
    // exec() inicia el bucle de eventos, lo que permite que la aplicación procese eventos como clics del ratón, entradas de teclado, y cualquier otro evento del sistema operativo.
    // Este ciclo de eventos no terminará hasta que se cierre la ventana principal (o cualquier otra ventana que la aplicación esté gestionando).
    // Cuando el ciclo de eventos finaliza (por ejemplo, cuando el usuario cierra la aplicación), exec() devuelve un valor que luego es devuelto por la función main.
    return a.exec();
}
