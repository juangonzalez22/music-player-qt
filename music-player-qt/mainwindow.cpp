#include "mainwindow.h"  // Incluye el archivo de encabezado "mainwindow.h", que contiene la declaración de la clase MainWindow.
#include "ui_mainwindow.h"  // Incluye el archivo de interfaz de usuario generado automáticamente por Qt Designer.
#include <QFileDialog>  // Incluye la clase QFileDialog, que proporciona un cuadro de diálogo para seleccionar archivos y directorios.
#include <QTime>  // Incluye la clase QTime, que se utiliza para manejar y manipular tiempos.
#include <QFileInfo>  // Incluye la clase QFileInfo, que proporciona información sobre archivos y directorios.
#include <QDebug>  // Incluye la biblioteca QDebug, que permite imprimir mensajes de depuración en la consola.
#include <QMessageBox> // Incluye la clase QMessageBox, que permite mostrar diálogos de mensajes al usuario.
#include <QMutexLocker> // Incluye QMutexLocker para manejar el mutex.

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , MPlayer(new QMediaPlayer(this))
    , audioOutput(new QAudioOutput(this))
{
    ui->setupUi(this);

    QString sPath = "C:/";
    dirmodel = new QFileSystemModel(this);
    dirmodel->setRootPath(sPath);

    dirmodel->setNameFilters(QStringList() << "*.mp3" << "*.mp4" << "*");
    dirmodel->setNameFilterDisables(false);

    ui->treeView->setModel(dirmodel);
    ui->treeView->setRootIndex(dirmodel->setRootPath(sPath));

    MPlayer->setAudioOutput(audioOutput);

    ui->sldrVolume->setMinimum(0);
    ui->sldrVolume->setMaximum(100);
    ui->sldrVolume->setValue(30);

    audioOutput->setVolume(ui->sldrVolume->value() / 100.0);

    connect(MPlayer, &QMediaPlayer::durationChanged, this, &MainWindow::durationChanged);
    connect(MPlayer, &QMediaPlayer::positionChanged, this, &MainWindow::positionChanged);

    ui->sldrSeek->setRange(0, 0);
    connect(ui->treeView, &QTreeView::doubleClicked, this, &MainWindow::on_treeView_doubleClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateDuration(qint64 duration)
{
    if (duration && Mduration) {
        QTime CurrentTime((duration / 3600) % 60, (duration / 60) % 60, duration % 60, (duration * 1000) % 1000);
        QTime TotalTime((Mduration / 3600) % 60, (Mduration / 60) % 60, Mduration % 60, (Mduration * 1000) % 1000);

        QString format = "mm:ss";
        if (Mduration > 3600) {
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
    QString folderName = QFileDialog::getExistingDirectory(this, tr("Select Directory"), "");
    if (!folderName.isEmpty()) {
        sPath = folderName;
        dirmodel->setRootPath(sPath);
        ui->treeView->setRootIndex(dirmodel->setRootPath(sPath));
    }
}

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    if (!index.isValid()) {
        qDebug() << "Índice no válido";
        return;
    }

    QString filePath = dirmodel->filePath(index);
    QFileInfo fileInfo(filePath);

    static bool hasDisplayedWarning = false; // Variable estática para controlar la visualización del mensaje.

    if (fileInfo.isFile()) {
        QString extension = fileInfo.suffix().toLower();

        if (extension == "mp3" || extension == "mp4") {
            MPlayer->setSource(QUrl::fromLocalFile(filePath));

            ui->fileName->setText(fileInfo.fileName());
            MPlayer->play();
            IS_Paused = false;
            hasDisplayedWarning = false; // Restablece el estado si se reproduce un archivo válido.
        } else {

            if (!hasDisplayedWarning) { // Verifica si el mensaje ya ha sido mostrado.
                hasDisplayedWarning = true; // Marca el mensaje como mostrado.
                QMessageBox msgBox;
                msgBox.setText("El archivo no se puede reproducir");
                msgBox.exec();
            }
        }
    }
}

void MainWindow::on_btnStop_clicked()
{
    MPlayer->stop();
}

void MainWindow::on_btnPrev_clicked()
{
    // Implementación para reproducir la pista anterior.
}

void MainWindow::on_btnNext_clicked()
{
    // Implementación para reproducir la siguiente pista.
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
