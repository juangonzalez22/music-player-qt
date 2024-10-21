#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTime>
#include <QFileInfo>
#include <QDebug>
#include <QMessageBox>
#include <QMutexLocker>
#include <QDir>
#include <QFileInfoList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , MPlayer(new QMediaPlayer(this))
    , audioOutput(new QAudioOutput(this))
    , currentIndex(-1)  // Inicializamos el índice actual a -1 (ninguna pista seleccionada)
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

    // Conectamos la señal de doble clic en el widget de lista de reproducción con su correspondiente slot
    connect(ui->playlistWidget, &QListWidget::doubleClicked, this, &MainWindow::on_playlistWidget_doubleClicked);
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

        // Actualizamos la lista de reproducción con los archivos del directorio seleccionado
        updatePlaylist(sPath);
    }
}

// Nueva función para actualizar la lista de reproducción
void MainWindow::updatePlaylist(const QString &directory)
{
    // Limpiamos la lista de reproducción actual
    ui->playlistWidget->clear();
    playlist.clear();

    // Obtenemos la lista de archivos en el directorio
    QDir dir(directory);
    QStringList filters;
    filters << "*.mp3" << "*.mp4";
    QFileInfoList files = dir.entryInfoList(filters, QDir::Files);

    // Añadimos cada archivo a la lista de reproducción
    for (const QFileInfo &file : files) {
        ui->playlistWidget->addItem(file.fileName());
        playlist.append(file.filePath());
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
    static bool hasDisplayedWarning = false;

    if (fileInfo.isFile()) {
        QString extension = fileInfo.suffix().toLower();

        if (extension == "mp3" || extension == "mp4") {
            // Llamamos a la nueva función playFile para reproducir el archivo
            playFile(filePath);
            hasDisplayedWarning = false;
        } else {
            if (!hasDisplayedWarning) {
                hasDisplayedWarning = true;
                QMessageBox msgBox;
                msgBox.setText("El archivo no se puede reproducir");
                msgBox.exec();
            }
        }
    }
}

// Nueva función para reproducir un archivo
void MainWindow::playFile(const QString &filePath)
{
    MPlayer->setSource(QUrl::fromLocalFile(filePath));
    QFileInfo fileInfo(filePath);
    ui->fileName->setText(fileInfo.fileName());
    MPlayer->play();
    IS_Paused = false;

    // Actualizamos el índice actual en la lista de reproducción
    currentIndex = playlist.indexOf(filePath);
}

void MainWindow::on_btnStop_clicked()
{
    MPlayer->stop();
}

void MainWindow::on_btnPrev_clicked()
{
    // Implementación para reproducir la pista anterior
    if (currentIndex > 0) {
        currentIndex--;
        playFile(playlist[currentIndex]);
    }
}

void MainWindow::on_btnNext_clicked()
{
    // Implementación para reproducir la siguiente pista
    if (currentIndex < playlist.size() - 1) {
        currentIndex++;
        playFile(playlist[currentIndex]);
    }
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

// Nuevo slot para manejar el doble clic en el widget de lista de reproducción
void MainWindow::on_playlistWidget_doubleClicked(const QModelIndex &index)
{
    if (index.isValid() && index.row() < playlist.size()) {
        currentIndex = index.row();
        playFile(playlist[currentIndex]);
    }
}
