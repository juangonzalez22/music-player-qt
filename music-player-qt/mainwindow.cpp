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
#include <QVBoxLayout>
#include <QTimer>
#include <QCoreApplication>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , MPlayer(new QMediaPlayer(this))
    , audioOutput(new QAudioOutput(this))
    , currentIndex(-1)
    , videoWidget(new QVideoWidget(this))
    , backgroundPlayer(new QMediaPlayer(this))
    , marqueeTimer(nullptr)
    , isMarqueeNeeded(false)
{
    ui->setupUi(this);

    QSize iconSize(24, 24);

    ui->btnPlayPause->setIcon(QIcon(":/icons/play.png"));
    ui->btnPlayPause->setIconSize(iconSize);

    ui->btnStop->setIcon(QIcon(":/icons/stop.png"));
    ui->btnStop->setIconSize(iconSize);

    ui->btnMute->setIcon(QIcon(":/icons/volume.png"));
    ui->btnMute->setIconSize(iconSize);

    ui->btnPrev->setIcon(QIcon(":/icons/prev.png"));
    ui->btnPrev->setIconSize(iconSize);

    ui->btnNext->setIcon(QIcon(":/icons/next.png"));
    ui->btnNext->setIconSize(iconSize);

    setWindowIcon(QIcon(":/icons/app.ico")); // Cambia a la ruta del recurso
    setWindowTitle("Pro MediaPlayer");

    QString sPath = "C:/";
    dirmodel = new QFileSystemModel(this);
    dirmodel->setRootPath(sPath);
    dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);

    ui->treeView->setModel(dirmodel);
    ui->treeView->setRootIndex(dirmodel->setRootPath(sPath));

    // Ocultar columnas no deseadas
    ui->treeView->setColumnHidden(1, true); // Ocultar columna de tamaño
    ui->treeView->setColumnHidden(2, true); // Ocultar columna de tipo
    ui->treeView->setColumnHidden(3, true); // Ocultar columna de fecha

    MPlayer->setAudioOutput(audioOutput);

    backgroundPlayer->setVideoOutput(videoWidget);

    // Configurar el layout del QGroupBox
    QVBoxLayout *layout = new QVBoxLayout(ui->groupBox);
    layout->addWidget(videoWidget);
    MPlayer->setVideoOutput(videoWidget);

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
    QMainWindow::focusInEvent(event);
    if (isMarqueeNeeded) {
        startMarquee();
    }
}

void MainWindow::on_btnMute_clicked()
{
    if (!IS_Muted) {
        // Almacena el volumen actual antes de mutear y mueve el slider a 0
        previousVolume = ui->sldrVolume->value();
        ui->sldrVolume->setValue(0);          // Mueve el slider a 0
        audioOutput->setVolume(0);            // Mutea el audio
        ui->btnMute->setIcon(QIcon(":/icons/mute.png")); // Cambia el ícono a mute
        IS_Muted = true;
    } else {
        // Verifica si el volumen previo era 0, si es así, establece en 15
        if (previousVolume == 0) {
            previousVolume = 15;
        }

        // Restaura el volumen previo al desmutear
        ui->sldrVolume->setValue(previousVolume);  // Restaura el slider a la posición anterior
        audioOutput->setVolume(previousVolume / 100.0); // Restaura el volumen del audio
        ui->btnMute->setIcon(QIcon(":/icons/volume.png")); // Cambia el ícono a volumen
        IS_Muted = false;
    }
}



void MainWindow::on_actionOpen_File_triggered()
{
    QString folderName = QFileDialog::getExistingDirectory(this, tr("Select Directory "), "");
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
    playlist.clear();
    QDir dir(directory);
    QStringList filters;
    filters << "*.mp3" << "*.mp4" << "*.m4a" << "*.wav" << "*.m4v" << "*.mkv";
    QFileInfoList files = dir.entryInfoList(filters, QDir::Files);

    for (const QFileInfo &file : files) {
        ui->playlistWidget->addItem(file.fileName());
        playlist.append(file.filePath());
    }
}

void MainWindow::playFile(const QString &filePath)
{
    QFileInfo fileInfo(filePath);
    QString fileName = fileInfo.fileName();

    setWindowTitle("Pro MediaPlayer: " + fileName);

    if (fileInfo.suffix() == "mp4" || fileInfo.suffix() == "m4v" || fileInfo.suffix() == "mkv") {
        // Reproducir video normalmente
        backgroundPlayer->stop();  // Detener el video de fondo si se está reproduciendo
        MPlayer->setVideoOutput(videoWidget);  // Usar el mismo videoWidget para videos normales
        MPlayer->setSource(QUrl::fromLocalFile(filePath));
        setupMarquee(fileName);
        videoWidget->show();  // Asegurarse de que el videoWidget esté visible
        MPlayer->play();
        ui->btnPlayPause->setIcon(QIcon(":/icons/pause.png")); // Cambiar a ícono de pausa;
        IS_Paused = false;
        currentIndex = playlist.indexOf(filePath);
    } else {
        // Si es un archivo de audio, reproducir el audio
        MPlayer->setVideoOutput(nullptr);  // Asegurarse de que no utilice el QVideoWidget
        MPlayer->setSource(QUrl::fromLocalFile(filePath));
        setupMarquee(fileName);
        MPlayer->play();
        ui->btnPlayPause->setIcon(QIcon(":/icons/pause.png")); // Cambiar a ícono de pausa;
        IS_Paused = false;
        currentIndex = playlist.indexOf(filePath);

        // Reproducir el video "placeholder" en bucle usando el mismo videoWidget
        playPlaceholderVideo();
    }
}

void MainWindow::playPlaceholderVideo()
{
    QString placeholderVideoPath = "qrc:/icons/placeholder.mp4";  // Nota el "qrc:" al principio

    videoWidget->show();
    backgroundPlayer->stop();
    backgroundPlayer->setVideoOutput(videoWidget);

    QTimer::singleShot(500, [this, placeholderVideoPath]() {
        backgroundPlayer->setSource(QUrl(placeholderVideoPath));
        backgroundPlayer->setLoops(QMediaPlayer::Infinite);
        backgroundPlayer->play();
        qDebug() << "Reproduciendo video placeholder en bucle desde los recursos:" << placeholderVideoPath;
    });
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
    ui->btnPlayPause->setIcon(QIcon(":/icons/play.png")); // Cambiar a ícono de play;
    IS_Paused = true;
}

void MainWindow::on_sldrVolume_valueChanged(int value)
{
    audioOutput->setVolume(value / 100.0);

    // Cambiar el icono dependiendo del nivel de volumen
    if (value == 0) {
        // Si el volumen es 0, poner el icono de mute
        ui->btnMute->setIcon(QIcon(":/icons/mute.png"));
        IS_Muted = true;
    } else {
        // Si el volumen no es 0, poner el icono normal
        ui->btnMute->setIcon(QIcon(":/icons/volume.png"));
        IS_Muted = false;
    }
}

void MainWindow::on_btnPlayPause_clicked()
{
    if (IS_Paused) {
        MPlayer->play();
        ui->btnPlayPause->setIcon(QIcon(":/icons/pause.png")); // Cambiar a ícono de pausa;
        IS_Paused = false;
    } else {
        MPlayer->pause();
         ui->btnPlayPause->setIcon(QIcon(":/icons/play.png")); // Cambiar a ícono de play;
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

    // Establecer el texto sin ajuste automático
    ui->fileName->setWordWrap(false);
    ui->fileName->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    // Restaurar el estilo original del label
    ui->fileName->setStyleSheet("QLabel { margin-left: 0px; font-size: 12pt; }"); // Ajusta 12pt al tamaño que desees

    // Verificar si el texto es más largo que el label
    QFontMetrics metrics(ui->fileName->font());
    int textWidth = metrics.horizontalAdvance(text);
    isMarqueeNeeded = (textWidth > ui->fileName->width());

    if (isMarqueeNeeded) {
        // Inicializar el timer si aún no existe
        if (!marqueeTimer) {
            marqueeTimer = new QTimer(this);
            connect(marqueeTimer, &QTimer::timeout, this, &MainWindow::updateMarqueePosition);
        }

        // Preparar el texto para el efecto marquee
        marqueeText = text + "    " + text;  // Duplicar el texto para un efecto continuo
        marqueeOffset = 0;
        startMarquee();
    } else {
        // Si el texto cabe, solo mostrarlo normalmente
        ui->fileName->setText(text);
    }
}


void MainWindow::updateMarqueePosition()
{
    if (!isMarqueeNeeded) return;

    QFontMetrics metrics(ui->fileName->font());
    marqueeOffset -= 1; // Ajusta este valor para controlar la velocidad

    // Reiniciar el offset cuando el primer texto complete su desplazamiento
    if (-marqueeOffset >= metrics.horizontalAdvance(marqueeText) / 2) {
        marqueeOffset = 0;
    }

    // Crear un estilo CSS para el desplazamiento manteniendo el tamaño de fuente
    QString style = QString("QLabel { margin-left: %1px; font-size: 12pt; }").arg(marqueeOffset);
    ui->fileName->setStyleSheet(style);
    ui->fileName->setText(marqueeText);
}

void MainWindow::startMarquee()
{
    if (isMarqueeNeeded && marqueeTimer) {
        marqueeOffset = 0;
        marqueeTimer->start(32);  // 60 FPS aproximadamente (1000ms/60 ≈ 16ms)
    }
}

void MainWindow::stopMarquee()
{
    if (marqueeTimer) {
        marqueeTimer->stop();
        ui->fileName->setStyleSheet("");
    }
}

void MainWindow::on_sldrSeek_sliderReleased()
{
    MPlayer->setPosition(ui->sldrSeek->value() * 1000);
}
