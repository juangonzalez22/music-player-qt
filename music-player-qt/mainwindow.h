#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia>
#include <QtCore>
#include <QtWidgets>
#include <QtGui>
#include <QtMultimediaWidgets>
#include <QFileSystemModel>

// Declaración del espacio de nombres para la interfaz de usuario
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * MainWindow es la clase que representa la ventana principal de la aplicación de reproductor de medios.
 * Esta clase hereda de QMainWindow y contiene todos los elementos de la interfaz de usuario,
 * así como la lógica para controlar la reproducción de medios, la gestión de archivos y
 * la interacción del usuario.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor y destructor
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Métodos de slot para manejar eventos de la interfaz de usuario
    void durationChanged(qint64 duration);
    void positionChanged(qint64 position);
    void on_btnMute_clicked();
    void on_actionOpen_File_triggered();
    void on_btnPrev_clicked();
    void on_btnNext_clicked();
    void on_btnStop_clicked();
    void on_sldrVolume_valueChanged(int value);
    void on_btnPlayPause_clicked();
    void on_sldrSeek_sliderMoved(int position);
    void on_sldrSeek_sliderReleased();
    void on_treeView_clicked(const QModelIndex &index);
    void on_playlistWidget_doubleClicked(const QModelIndex &index);
    void setupMarquee(const QString &text);
    void startMarquee();
    void stopMarquee();
    void focusOutEvent(QFocusEvent *event);
    void focusInEvent(QFocusEvent *event);
    void playPlaceholderVideo();
    void updateMarqueePosition();
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
    void on_btnPlaybackMode_clicked();
    void on_btnShuffle_clicked();

private:
    // Métodos privados para la lógica interna
    void updateDuration(qint64 duration);
    void updatePlaylist(const QString &directory);
    void playFile(const QString &filePath);

    // Puntero a la interfaz de usuario generada
    Ui::MainWindow *ui;

    // Objetos de control multimedia
    QMediaPlayer *MPlayer;          // Reproductor de medios principal
    QAudioOutput *audioOutput;      // Salida de audio
    int currentIndex;               // Índice actual de la pista en la lista de reproducción
    QVideoWidget *videoWidget;      // Widget para mostrar video
    QMediaPlayer *backgroundPlayer; // Reproductor de video de fondo
    QTimer *marqueeTimer;           // Temporizador para el efecto de marquee
    bool isMarqueeNeeded;           // Indica si se necesita el efecto de marquee
    int marqueeOffset;              // Desplazamiento actual del marquee
    QString marqueeText;            // Texto para el marquee
    bool IS_Muted = false;          // Estado de muteo
    bool IS_Paused = true;          // Estado de pausa
    qint64 Mduration;               // Duración total del medio
    QFileSystemModel *dirmodel;     // Modelo del sistema de archivos
    QString sPath;                  // Ruta del directorio actual
    QStringList playlist;           // Lista de reproducción actual
    int previousVolume;             // Volumen previo antes de mutear

    // Variable para controlar el estado del shuffle
    bool isShuffleEnabled = false;
    // Lista para mantener el orden original de la playlist
    QStringList originalPlaylist;

    // Enum para controlar los modos de reproducción
    enum class PlaybackMode {
        Normal,
        RepeatOne,
        RepeatAll
    };

    // Variable para mantener el estado actual del modo de reproducción
    PlaybackMode currentPlaybackMode;

    // Método privado para actualizar el ícono del modo de reproducción
    void updatePlaybackModeIcon();
};

#endif // MAINWINDOW_H
