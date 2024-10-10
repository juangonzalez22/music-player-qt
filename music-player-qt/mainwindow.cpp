#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QAudioOutput>
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

    audioOutput->setVolume(ui->sldrVolume->value() / 100.0); // Set volume from slider value

    connect(MPlayer, &QMediaPlayer::durationChanged, this, &MainWindow::durationChanged);
    connect(MPlayer, &QMediaPlayer::positionChanged, this, &MainWindow::positionChanged);

    ui->sldrSeek->setRange(0, 0); // Initial range

    // Desconectar el slider de la función para poder manejarlo manualmente
    connect(ui->sldrSeek, &QSlider::sliderPressed, this, [=](){
        ui->sldrSeek->setEnabled(false); // Desactivar el slider
    });

    connect(ui->sldrSeek, &QSlider::sliderReleased, this, [=](){
        ui->sldrSeek->setEnabled(true); // Reactivar el slider
        MPlayer->setPosition(ui->sldrSeek->value() * 1000); // Cambiar la posición solo cuando se suelta el slider
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateduration(qint64 duration)
{
    QString timestr;
    if(duration && Mduration){
        QTime CurrentTime((duration / 3600) % 60, (duration / 60) % 60, duration % 60, (duration*1000)%1000);
        QTime TotalTime ((Mduration / 3600) % 60, (Mduration / 60) % 60, Mduration % 60, (Mduration * 1000) % 1000);
        QString format = "mm:ss";
        if(Mduration > 3600){
            format = "hh:mm:ss";
        }
        ui->currentTime->setText(CurrentTime.toString(format));
        ui->totalTime->setText(TotalTime.toString(format));
    }
}

void MainWindow::durationChanged(qint64 duration)
{
    Mduration = duration / 1000; // Convertimos de milisegundos a segundos
    ui->sldrSeek->setMaximum(Mduration);
}

void MainWindow::positionChanged(quint64 progress)
{
    if (!ui->sldrSeek->isSliderDown())  // Solo actualizar si el slider no está siendo movido
    {
        ui->sldrSeek->setValue(progress / 1000);
        updateduration(progress / 1000); // Llama a la función updateduration para actualizar la interfaz
    }
}


void MainWindow::on_btnMute_clicked() {
    if (!IS_Muted) {
        audioOutput->setVolume(0);  // Silenciar
        IS_Muted = true;
    } else {
        audioOutput->setVolume(ui->sldrVolume->value() / 100.0);  // Restaurar volumen
        IS_Muted = false;
    }
}

void MainWindow::on_actionOpen_File_triggered()
{
    QString FileName = QFileDialog::getOpenFileName(this, tr("Select Audio File"), "", tr("MP3 Files (*.mp3)"));
    if (FileName.isEmpty()) return;  // Verifica que se haya seleccionado un archivo

    MPlayer->setSource(QUrl::fromLocalFile(FileName));

    if (MPlayer->error() != QMediaPlayer::NoError) {
        qDebug() << "Error al cargar el archivo:" << MPlayer->errorString();
        return;
    }

    QFileInfo fileInfo(FileName);
    ui->fileName->setText(fileInfo.fileName());
}

void MainWindow::on_btnPlay_clicked()
{
    MPlayer->play();
}

void MainWindow::on_btnPause_clicked()
{
    MPlayer->pause();
}

void MainWindow::on_btnStop_clicked()
{
    MPlayer->stop();
}

void MainWindow::on_btnPrev_clicked()
{

}

void MainWindow::on_btnNext_clicked()
{

}

void MainWindow::on_sldrSeek_valueChanged(int value)
{
    // Solo se cambia la posición si el slider está habilitado
    if (ui->sldrSeek->isEnabled()) {
        MPlayer->setPosition(value * 1000);
    }
}

void MainWindow::on_sldrVolume_valueChanged(int value)
{
    audioOutput->setVolume(value / 100.0);  // Convierte el valor de 0-100 a 0.0-1.0
}
