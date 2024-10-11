#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia>
#include <QtCore>
#include <QtWidgets>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void durationChanged(qint64 duration);
    void positionChanged(quint64 progress);

    void on_btnMute_clicked();

    void on_actionOpen_File_triggered();

    void on_btnPrev_clicked();

    void on_btnNext_clicked();

    void on_btnStop_clicked();

    void on_sldrSeek_valueChanged(int value);

    void on_sldrVolume_valueChanged(int value);

    void on_btnPlayPause_clicked();

private:
    void updateduration(qint64 duration);
    Ui::MainWindow *ui;
    bool IS_Muted = false;
    bool IS_Paused = true;
    QMediaPlayer *MPlayer;
    QAudioOutput *audioOutput;
    qint64 Mduration;
};
#endif // MAINWINDOW_H
