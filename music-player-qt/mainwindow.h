#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia>
#include <QtCore>
#include <QtWidgets>
#include <QtGui>
#include <QtMultimediaWidgets>
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
    void on_treeView_clicked(const QModelIndex &index);
    void on_playlistWidget_doubleClicked(const QModelIndex &index);
    void setupMarquee(const QString &text);
    void startMarquee();
    void stopMarquee();
    void focusOutEvent(QFocusEvent *event);
    void focusInEvent(QFocusEvent *event);
    void playPlaceholderVideo();
    void updateMarqueePosition();
private:
    void updateDuration(qint64 duration);
    void updatePlaylist(const QString &directory);
    void playFile(const QString &filePath);

    Ui::MainWindow *ui;
    QMediaPlayer *MPlayer;
    QAudioOutput *audioOutput;
    int currentIndex;
    QVideoWidget *videoWidget;
    QMediaPlayer *backgroundPlayer;
    QTimer *marqueeTimer;
    bool isMarqueeNeeded;
    int marqueeOffset;
    QString marqueeText;
    bool IS_Muted = false;
    bool IS_Paused = true;
    qint64 Mduration;
    QFileSystemModel *dirmodel;
    QString sPath;
    QStringList playlist;
    int previousVolume;
};

#endif // MAINWINDOW_H
