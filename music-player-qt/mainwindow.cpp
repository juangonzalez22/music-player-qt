#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTime>
#include <QFileInfo>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , MPlayer(new QMediaPlayer(this))
    , audioOutput(new QAudioOutput(this))
{
    ui->setupUi(this);
    MPlayer->setAudioOutput(audioOutput);

    ui->sldrVolume->setMinimum(0);
    ui->sldrVolume->setMaximum(100);
    ui->sldrVolume->setValue(30);

    audioOutput->setVolume(ui->sldrVolume->value() / 100.0);

    connect(MPlayer, &QMediaPlayer::durationChanged, this, &MainWindow::durationChanged);
    connect(MPlayer, &QMediaPlayer::positionChanged, this, &MainWindow::positionChanged);

    ui->sldrSeek->setRange(0, 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateDuration(qint64 duration)
{
    if(duration && Mduration){
        QTime CurrentTime((duration / 3600) % 60, (duration / 60) % 60, duration % 60, (duration*1000)%1000);
        QTime TotalTime ((Mduration / 3600) % 60, (Mduration / 60) % 60, Mduration % 60, (Mduration * 1000) % 1000);
        QString format = "mm:ss";
        if(Mduration > 3600) {
            format = "hh:mm:ss";
        }
        ui->currentTime->setText(CurrentTime.toString(format));
        ui->totalTime->setText(TotalTime.toString(format));
    }
}

void MainWindow::durationChanged(qint64 duration)
{
    Mduration = duration / 1000;
    ui->sldrSeek->setMaximum(Mduration);
}

void MainWindow::positionChanged(qint64 position)
{
    if (!ui->sldrSeek->isSliderDown()) {
        updateDuration(position / 1000);
        ui->sldrSeek->setValue(position / 1000);
    }
}

void MainWindow::on_btnMute_clicked()
{
    if (!IS_Muted) {
        audioOutput->setVolume(0);
        IS_Muted = true;
    } else {
        audioOutput->setVolume(ui->sldrVolume->value() / 100.0);
        IS_Muted = false;
    }
}

void MainWindow::on_actionOpen_File_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select Audio File"), "", tr("MP3 Files (*.mp3)"));
    if (fileName.isEmpty()) return;

    MPlayer->setSource(QUrl::fromLocalFile(fileName));

    if (MPlayer->error() != QMediaPlayer::NoError) {
        qDebug() << "Error al cargar el archivo:" << MPlayer->errorString();
        return;
    }

    QFileInfo fileInfo(fileName);
    ui->fileName->setText(fileInfo.fileName());
}

void MainWindow::on_btnStop_clicked()
{
    MPlayer->stop();
}

void MainWindow::on_btnPrev_clicked()
{
    // Implementar la funcionalidad para la pista anterior
}

void MainWindow::on_btnNext_clicked()
{
    // Implementar la funcionalidad para la siguiente pista
}

void MainWindow::on_sldrVolume_valueChanged(int value)
{
    audioOutput->setVolume(value / 100.0);
}
void MainWindow::on_btnPlayPause_clicked()
{
    if (!IS_Paused) {
        MPlayer->pause();
        IS_Paused = true;
    } else {
        MPlayer->play();
        IS_Paused = false;
    }
}

void MainWindow::on_sldrSeek_sliderMoved(int position)
{
    MPlayer->setPosition(position * 1000);
}

void MainWindow::on_sldrSeek_sliderReleased()
{
    MPlayer->setPosition(ui->sldrSeek->value() * 1000);
}
