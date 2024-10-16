#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia>
#include <QtCore>
#include <QtWidgets>

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

    // Nuevos slots para el slider de búsqueda
    void on_sldrSeek_sliderMoved(int position);
    void on_sldrSeek_sliderReleased();

private:
    void updateDuration(qint64 duration);
    Ui::MainWindow *ui;
    bool IS_Muted = false;
    bool IS_Paused = true;
    QMediaPlayer *MPlayer;
    QAudioOutput *audioOutput;
    qint64 Mduration;
};
#endif // MAINWINDOW_H
