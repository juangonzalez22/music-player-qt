#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia>
#include <QtCore>
#include <QtWidgets>
#include <QFileSystemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
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
    void on_treeView_doubleClicked(const QModelIndex &index);

    // Nuevo slot para manejar el doble clic en el widget de lista de reproducción
    void on_playlistWidget_doubleClicked(const QModelIndex &index);

private:
    void updateDuration(qint64 duration);

    // Nueva función para actualizar la lista de reproducción
    void updatePlaylist(const QString &directory);

    // Nueva función para reproducir un archivo
    void playFile(const QString &filePath);

    Ui::MainWindow *ui;
    bool IS_Muted = false;
    bool IS_Paused = true;
    QMediaPlayer *MPlayer;
    QAudioOutput *audioOutput;
    qint64 Mduration;
    QFileSystemModel *dirmodel;
    QString sPath;

    // Nueva lista para almacenar la lista de reproducción
    QStringList playlist;

    // Nuevo índice para rastrear la pista actual en la lista de reproducción
    int currentIndex;
};

#endif // MAINWINDOW_H
