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
    , currentIndex(-1)
    , marqueeTimer(nullptr)  // Inicializar el puntero
    , isMarqueeNeeded(false)
{
    ui->setupUi(this);

    QString sPath = "C:/";
    dirmodel = new QFileSystemModel(this);
    dirmodel->setRootPath(sPath);
    dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs); // Solo mostrar directorios

    ui->treeView->setModel(dirmodel);
    ui->treeView->setRootIndex(dirmodel->setRootPath(sPath));

    // Ocultar las columnas que no deseas mostrar
    ui->treeView->setColumnHidden(1, true); // Ocultar columna de tamaño
    ui->treeView->setColumnHidden(2, true); // Ocultar columna de tipo
    ui->treeView->setColumnHidden(3, true); // Ocultar columna de fecha

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
    stopMarquee();
    if (marqueeTimer) {
        delete marqueeTimer;
    }
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

void MainWindow::focusOutEvent(QFocusEvent *event)
{
    QMainWindow::focusOutEvent(event);
    stopMarquee();
}

void MainWindow::focusInEvent(QFocusEvent *event)
{
    QMainWindow::focusInEvent(event); if (isMarqueeNeeded) {
        startMarquee();
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
        updatePlaylist(sPath);
    }
}

void MainWindow::updatePlaylist(const QString &directory)
{
    ui->playlistWidget->clear();
    playlist.clear(); QDir dir(directory);
    QStringList filters;
    filters << "*.mp3" << "*.mp4";
    QFileInfoList files = dir.entryInfoList(filters, QDir::Files);

    for (const QFileInfo &file : files) {
        ui->playlistWidget->addItem(file.fileName());
        playlist.append(file.filePath());
    }
}

void MainWindow::playFile(const QString &filePath)
{
    MPlayer->setSource(QUrl::fromLocalFile(filePath));
    QFileInfo fileInfo(filePath);
    QString fileName = fileInfo.fileName();

    setupMarquee(fileName);  // Configura el efecto marquee

    MPlayer->play();
    ui->btnPlayPause->setText("Pause");
    IS_Paused = false;
    currentIndex = playlist.indexOf(filePath);
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    QString path = dirmodel->filePath(index);
    updatePlaylist(path);
}

void MainWindow::on_playlistWidget_doubleClicked(const QModelIndex &index)
{
    QString filePath = playlist.at(index.row());
    playFile(filePath);
}

void MainWindow::on_btnPrev_clicked()
{
    if (currentIndex > 0) {
        currentIndex--;
        QString filePath = playlist.at(currentIndex);
        playFile(filePath);
    }
}

void MainWindow::on_btnNext_clicked()
{
    if (currentIndex < playlist.size() - 1) {
        currentIndex++;
        QString filePath = playlist.at(currentIndex);
        playFile(filePath);
    }
}

void MainWindow::on_btnStop_clicked()
{
    MPlayer->stop();
    ui->btnPlayPause->setText("Play");
    IS_Paused = true;
}

void MainWindow::on_sldrVolume_valueChanged(int value)
{
    audioOutput->setVolume(value / 100.0);
}

void MainWindow::on_btnPlayPause_clicked()
{
    if (IS_Paused) {
        MPlayer->play();
        ui->btnPlayPause->setText("Pause");
        IS_Paused = false;
    } else {
        MPlayer->pause();
        ui->btnPlayPause->setText("Play");
        IS_Paused = true;
    }
}

void MainWindow::on_sldrSeek_sliderMoved(int position)
{
    MPlayer->setPosition(position * 1000);
}

void MainWindow::setupMarquee(const QString &text)
{
    // Detener el marquee anterior si existe
    if (marqueeTimer) {
        stopMarquee();
    }

    // Verificar si el texto es más largo que el label
    QFontMetrics metrics(ui->fileName->font());
    int textWidth = metrics.horizontalAdvance(text);
    isMarqueeNeeded = (textWidth > ui->fileName->width());

    if (isMarqueeNeeded) {
        // Inicializar el timer si aún no existe
        if (!marqueeTimer) {
            marqueeTimer = new QTimer(this);
            connect(marqueeTimer, &QTimer::timeout, this, [this]() {
                QString currentText = ui->fileName->text();
                currentText = currentText.mid(1) + currentText.at(0);
                ui->fileName->setText(currentText);
            });
        }

        // Preparar el texto para el efecto marquee
        QString paddedText = text + "    ";  // Añadir espacio entre repeticiones
        ui->fileName->setText(paddedText);
        startMarquee();
    } else {
        // Si el texto cabe, solo mostrarlo normalmente
        ui->fileName->setText(text);
    }
}

void MainWindow::startMarquee()
{
    if (isMarqueeNeeded && marqueeTimer) {
        marqueeTimer->start(200);  // Ajusta este valor para controlar la velocidad
    }
}

void MainWindow::stopMarquee()
{
    if (marqueeTimer) {
        marqueeTimer->stop();
    }
}

void MainWindow::on_sldrSeek_sliderReleased()
{
    MPlayer->setPosition(ui->sldrSeek->value() * 1000);
}
