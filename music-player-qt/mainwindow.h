#ifndef MAINWINDOW_H  // Esta línea verifica si "MAINWINDOW_H" no está definido previamente.
#define MAINWINDOW_H  // Si no está definido, define "MAINWINDOW_H". Esto evita que el archivo se incluya más de una vez (previene errores de múltiples inclusiones).

// Estas son las bibliotecas de Qt que se están incluyendo.
// QMainWindow es la clase base de las aplicaciones que usan ventanas principales con menús, barras de herramientas, etc.
#include <QMainWindow>
// QtMultimedia es un módulo que proporciona soporte para reproducción de multimedia, como música y video.
#include <QtMultimedia>
// QtCore contiene las clases no gráficas esenciales de Qt, como las relacionadas con manejo de tiempo, hilos, eventos, etc.
#include <QtCore>
// QtWidgets contiene todas las clases relacionadas con los widgets de la interfaz gráfica de usuario (botones, sliders, etiquetas, etc.).
#include <QtWidgets>

// Estas macros delimitan un espacio de nombres específico de Qt.
// QT_BEGIN_NAMESPACE y QT_END_NAMESPACE son útiles para evitar colisiones de nombres en grandes proyectos o bibliotecas.
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }  // Declaración adelantada de la clase Ui::MainWindow que será usada en el archivo cpp.
QT_END_NAMESPACE

// Definición de la clase MainWindow que hereda de QMainWindow.
// QMainWindow provee la funcionalidad para la ventana principal de la aplicación.
// La palabra clave "public" indica que la herencia es pública, es decir, todos los miembros públicos y protegidos de QMainWindow son accesibles públicamente en MainWindow.
class MainWindow : public QMainWindow
{
    // Esta macro Q_OBJECT es obligatoria en todas las clases que definen señales y slots en Qt.
    // Q_OBJECT habilita el sistema de "meta-objetos" de Qt, que es esencial para funciones como señales, slots y propiedades dinámicas.
    Q_OBJECT

public:
    // Constructor de la clase MainWindow.
    // Este constructor toma un argumento opcional "parent" que, por defecto, es nullptr.
    // "QWidget *parent" es un puntero al widget que sería el padre de MainWindow (en este caso, la ventana principal no tiene padre).
    MainWindow(QWidget *parent = nullptr);

    // Destructor de la clase MainWindow.
    // El destructor se encarga de liberar cualquier recurso que esté siendo usado cuando el objeto MainWindow sea destruido.
    ~MainWindow();

private slots:
    // Slots son funciones especiales de Qt que pueden conectarse a señales.
    // Este slot es llamado cuando la duración del archivo multimedia cambia.
    // "qint64" es un tipo de dato específico de Qt para enteros de 64 bits (útil para manejar grandes números como duración en milisegundos).
    void durationChanged(qint64 duration);

    // Este slot es llamado cuando la posición de reproducción del archivo multimedia cambia.
    // Permite actualizar la interfaz gráfica con la nueva posición.
    void positionChanged(qint64 position);

    // Este slot es activado cuando el botón de silenciar (mute) es clicado.
    void on_btnMute_clicked();

    // Este slot es activado cuando el menú "Abrir Archivo" es seleccionado.
    void on_actionOpen_File_triggered();

    // Este slot es activado cuando el botón "Previo" es clicado (para retroceder en la lista de reproducción, si existe).
    void on_btnPrev_clicked();

    // Este slot es activado cuando el botón "Siguiente" es clicado (para avanzar en la lista de reproducción, si existe).
    void on_btnNext_clicked();

    // Este slot es activado cuando el botón "Detener" es clicado, deteniendo la reproducción.
    void on_btnStop_clicked();

    // Este slot es activado cuando el valor del slider de volumen cambia.
    // El slider se usa para ajustar el nivel de volumen de reproducción.
    void on_sldrVolume_valueChanged(int value);

    // Este slot es activado cuando el botón de reproducción/pausa es clicado.
    // Cambia el estado entre reproducir y pausar el archivo multimedia.
    void on_btnPlayPause_clicked();

    // Nuevos slots que manejan las interacciones con el slider de búsqueda (seek).
    // Este slot es activado cuando el slider de búsqueda es movido manualmente por el usuario.
    void on_sldrSeek_sliderMoved(int position);

    // Este slot es activado cuando el slider de búsqueda es liberado después de haber sido arrastrado.
    void on_sldrSeek_sliderReleased();

private:
    // Esta función privada se utiliza para actualizar la duración del archivo multimedia.
    // Se encarga de manejar y actualizar cualquier lógica relacionada con la duración del contenido que se está reproduciendo.
    void updateDuration(qint64 duration);

    // Puntero a la interfaz de usuario generada por el archivo .ui de Qt Designer.
    // "Ui::MainWindow" es una clase que se genera automáticamente para manejar la interfaz gráfica.
    Ui::MainWindow *ui;

    // Variable booleana que guarda si el estado actual es "mute" (silencio) o no.
    // Inicialmente, se asume que el sonido no está silenciado (false).
    bool IS_Muted = false;

    // Variable booleana que indica si la reproducción está actualmente pausada.
    // Por defecto, la reproducción empieza en estado pausado (true).
    bool IS_Paused = true;

    // Puntero a QMediaPlayer, que es la clase principal para la reproducción de medios (audio, video, etc.).
    // Esta clase se usa para controlar y gestionar la reproducción del contenido multimedia.
    QMediaPlayer *MPlayer;

    // Puntero a QAudioOutput, que es la clase que maneja la salida de audio (es decir, controla el dispositivo de audio y sus parámetros, como el volumen).
    QAudioOutput *audioOutput;

    // Variable de tipo qint64 que guarda la duración actual del archivo multimedia (en milisegundos).
    qint64 Mduration;
};

#endif // MAINWINDOW_H  // Esta línea final cierra la verificación de preprocesador para evitar múltiples inclusiones del archivo.

