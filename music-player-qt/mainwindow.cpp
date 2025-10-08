#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTime>
#include <QFileInfo>
#include <QDebug>
#include <QMutexLocker>
#include <QDir>
#include <QFileInfoList>
#include <QVBoxLayout>
#include <QTimer>
#include <QCoreApplication>
#include <QIcon>

/**
 * @brief Constructor de la clase MainWindow.
 *
 * Inicializa los componentes de la interfaz de usuario y configura el reproductor de medios.
 * @param parent Puntero al widget padre (opcional).
 */
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
    // Configuración de la interfaz de usuario
    ui->setupUi(this);

    // Configuración de iconos para los botones
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
    ui->btnPlaybackMode->setIconSize(iconSize);

    // Configuración de la ventana principal
    setWindowIcon(QIcon(":/icons/app.ico")); // Cambia a la ruta del recurso
    setWindowTitle("JL MediaPlayer");

    // Configuración del modelo del sistema de archivos
    QString sPath = "C:/"; // Ruta inicial
    dirmodel = new QFileSystemModel(this);
    dirmodel->setRootPath(sPath);
    dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);

    // Configuración de la vista de árbol
    ui->treeView->setModel(dirmodel);
    ui->treeView->setRootIndex(dirmodel->setRootPath(sPath));

    // Ocultar columnas no deseadas en la vista de árbol
    ui->treeView->setColumnHidden(1, true); // Ocultar columna de tamaño
    ui->treeView->setColumnHidden(2, true); // Ocultar columna de tipo
    ui->treeView->setColumnHidden(3, true); // Ocultar columna de fecha

    // Configuración del reproductor de medios
    MPlayer->setAudioOutput(audioOutput);
    backgroundPlayer->setVideoOutput(videoWidget);

    // Configuración del layout del QGroupBox
    QVBoxLayout *layout = new QVBoxLayout(ui->groupBox);
    layout->addWidget(videoWidget);
    MPlayer->setVideoOutput(videoWidget);

    // Configuración del control deslizante de volumen
    ui->sldrVolume->setMinimum(0);
    ui->sldrVolume->setMaximum(100);
    ui->sldrVolume->setValue(30);
    audioOutput->setVolume(ui->sldrVolume->value() / 100.0);

    // Conexiones de señales y slots
    connect(MPlayer, &QMediaPlayer::durationChanged, this, &MainWindow::durationChanged);
    connect(MPlayer, &QMediaPlayer::positionChanged, this, &MainWindow::positionChanged);
    connect(MPlayer, &QMediaPlayer::mediaStatusChanged, this, &MainWindow::onMediaStatusChanged);

    // Inicialización del control deslizante de búsqueda
    ui->sldrSeek->setRange(0, 0);

    // Configuración del modo de reproducción
    currentPlaybackMode = PlaybackMode::Normal;
    updatePlaybackModeIcon();

    // Configuración del botón de shuffle
    ui->btnShuffle->setIcon(QIcon(":/icons/shuffle_off.png"));
    ui->btnShuffle->setIconSize(iconSize);
}

/**
 * @brief Destructor de la clase MainWindow.
 *
 * Libera los recursos utilizados por la ventana principal.
 */
MainWindow::~MainWindow()
{
    stopMarquee();
    if (marqueeTimer) {
        delete marqueeTimer;
    }
    delete ui;
}

/**
 * @brief Actualiza la duración mostrada en la interfaz de usuario.
 *
 * @param duration La duración total del medio en milisegundos.
 */
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

/**
 * @brief Slot que se activa cuando cambia la duración del medio.
 *
 * @param duration La nueva duración del medio en milisegundos.
 */
void MainWindow::durationChanged(qint64 duration)
{
    Mduration = duration / 1000; // Convertir a segundos
    ui->sldrSeek->setMaximum(Mduration); // Actualizar el rango del control deslizante
}

/**
 * @brief Slot que se activa cuando cambia la posición de reproducción.
 *
 * @param position La nueva posición de reproducción en milisegundos.
 */
void MainWindow::positionChanged(qint64 position)
{
    if (!ui->sldrSeek->isSliderDown()) {
        updateDuration(position / 1000); // Actualizar el tiempo mostrado
        ui->sldrSeek->setValue(position / 1000); // Mover el control deslizante
    }
}

/**
 * @brief Maneja el evento de perder el foco.
 *
 * Detiene el efecto de marquee cuando la ventana pierde el foco.
 *
 * @param event El evento de foco.
 */
void MainWindow::focusOutEvent(QFocusEvent *event)
{
    QMainWindow::focusOutEvent(event);
    stopMarquee();
}

/**
 * @brief Maneja el evento de ganar el foco.
 *
 * Inicia el efecto de marquee cuando la ventana gana el foco.
 *
 * @param event El evento de foco.
 */
void MainWindow::focusInEvent(QFocusEvent *event)
{
    QMainWindow::focusInEvent(event);
    if (isMarqueeNeeded) {
        startMarquee();
    }
}

/**
 * @brief Maneja el clic en el botón de muteo.
 *
 * Alterna el estado de muteo del audio.
 */
void MainWindow::on_btnMute_clicked()
{
    if (!IS_Muted) {
        // Almacena el volumen actual antes de mutear
        previousVolume = ui->sldrVolume->value();
        ui->sldrVolume->setValue(0); // Mueve el slider a 0
        audioOutput->setVolume(0); // Mutea el audio
        ui->btnMute->setIcon(QIcon(":/icons/mute.png")); // Cambia el ícono a mute
        IS_Muted = true;
    } else {
        // Restaura el volumen previo al desmutear
        if (previousVolume == 0) {
            previousVolume = 15; // Establece un volumen mínimo
        }

        ui->sldrVolume->setValue(previousVolume); // Restaura el slider a la posición anterior
        audioOutput->setVolume(previousVolume / 100.0); // Restaura el volumen del audio
        ui->btnMute->setIcon(QIcon(":/icons/volume.png")); // Cambia el ícono a volumen
        IS_Muted = false;
    }
}

/**
 * @brief Actualiza el ícono del botón de modo de reproducción según el modo actual.
 */
void MainWindow::updatePlaybackModeIcon()
{
    QIcon icon;
    switch (currentPlaybackMode) {
    case PlaybackMode::Normal:
        icon = QIcon(":/icons/normal.png");
        break;
    case PlaybackMode::RepeatOne:
        icon = QIcon(":/icons/repeat_one.png");
        break;
    case PlaybackMode::RepeatAll:
        icon = QIcon(":/icons/repeat_all.png");
        break;
    }
    ui->btnPlaybackMode->setIcon(icon);
}

/**
 * @brief Slot que maneja el clic en el botón de modo de reproducción.
 *
 * Alterna entre los modos de reproducción: Normal, Repetir Uno y Repetir Todo.
 */
void MainWindow::on_btnPlaybackMode_clicked()
{
    switch (currentPlaybackMode) {
    case PlaybackMode::Normal:
        currentPlaybackMode = PlaybackMode::RepeatOne;
        break;
    case PlaybackMode::RepeatOne:
        currentPlaybackMode = PlaybackMode::RepeatAll;
        break;
    case PlaybackMode::RepeatAll:
        currentPlaybackMode = PlaybackMode::Normal;
        break;
    }
    updatePlaybackModeIcon(); // Actualiza el ícono del botón según el nuevo modo
}

/**
 * @brief Slot que maneja la acción de abrir un archivo o directorio.
 *
 * Permite al usuario seleccionar un directorio y actualiza la lista de reproducción.
 */
void MainWindow::on_actionOpen_File_triggered()
{
    QString folderName = QFileDialog::getExistingDirectory(this, tr("Select Directory "), "");
    if (!folderName.isEmpty()) {
        sPath = folderName;
        dirmodel->setRootPath(sPath);
        ui->treeView->setRootIndex(dirmodel->setRootPath(sPath));
        updatePlaylist(sPath); // Actualiza la lista de reproducción con los archivos del nuevo directorio
    }
}

/**
 * @brief Actualiza la lista de reproducción según los archivos en el directorio especificado.
 *
 * @param directory La ruta del directorio a escanear.
 */
void MainWindow::updatePlaylist(const QString &directory)
{
    ui->playlistWidget->clear(); // Limpia la lista de reproducción actual
    playlist.clear();
    originalPlaylist.clear(); // Limpia la lista de reproducción original

    QDir dir(directory);
    QStringList filters;
    filters << "*.mp3" << "*.mp4" << "*.m4a" << "*.wav" << "*.m4v" << "*.mkv";
    QFileInfoList files = dir.entryInfoList(filters, QDir::Files); // Obtiene archivos de audio y video

    for (const QFileInfo &file : files) {
        ui->playlistWidget->addItem(file.fileName()); // Agrega el nombre del archivo a la lista
        playlist.append(file.filePath()); // Agrega la ruta del archivo a la lista de reproducción
    }

    // Si el modo shuffle está activado, mezcla la nueva lista de reproducción
    if (isShuffleEnabled) {
        originalPlaylist = playlist;
        QStringList tempPlaylist = playlist;
        playlist.clear();

        while (!tempPlaylist.isEmpty()) {
            int randomIndex = QRandomGenerator::global()->bounded(tempPlaylist.size());
            playlist.append(tempPlaylist.takeAt(randomIndex)); // Mezcla aleatoriamente
        }

        // Actualiza la vista
        ui->playlistWidget->clear();
        for (const QString &file : playlist) {
            QFileInfo fileInfo(file);
            ui->playlistWidget->addItem(fileInfo.fileName());
        }
    }
}

/**
 * @brief Reproduce el archivo especificado.
 *
 * @param filePath La ruta del archivo a reproducir.
 */
void MainWindow::playFile(const QString &filePath)
{
    QFileInfo fileInfo(filePath);
    QString fileName = fileInfo.fileName();

    setWindowTitle("JL MediaPlayer is playing: " + fileName); // Actualiza el título de la ventana

    if (fileInfo.suffix() == "mp4" || fileInfo.suffix() == "m4v" || fileInfo.suffix() == "mkv") {
        // Reproducir video normalmente
        backgroundPlayer->stop();  // Detener el video de fondo si se está reproduciendo
        MPlayer->setVideoOutput(videoWidget);  // Usar el mismo videoWidget para videos normales
        MPlayer->setSource(QUrl::fromLocalFile(filePath));
        setupMarquee(fileName); // Configura el marquee con el nombre del archivo
        videoWidget->show();  // Asegurarse de que el videoWidget esté visible
        MPlayer->play();
        ui->btnPlayPause->setIcon(QIcon(":/icons/pause.png")); // Cambiar a ícono de pausa
        IS_Paused = false;
        currentIndex = playlist.indexOf(filePath); // Actualiza el índice actual
    } else {
        // Si es un archivo de audio, reproducir el audio
        MPlayer->setVideoOutput(nullptr);  // Asegurarse de que no utilice el QVideoWidget
        MPlayer->setSource(QUrl::fromLocalFile(filePath));
        setupMarquee(fileName); // Configura el marquee con el nombre del archivo
        MPlayer->play();
        ui->btnPlayPause->setIcon(QIcon(":/icons/pause.png")); // Cambiar a ícono de pausa
        IS_Paused = false;
        currentIndex = playlist.indexOf(filePath); // Actualiza el índice actual

        // Reproducir el video "placeholder" en bucle usando el mismo videoWidget
        playPlaceholderVideo();
    }

    currentIndex = playlist.indexOf(filePath); // Actualiza el índice actual
    ui->playlistWidget->setCurrentRow(currentIndex); // Selecciona el archivo en la lista de reproducción
}

/**
 * @brief Reproduce un video placeholder.
 *
 * Este video se usa como fondo cuando se reproduce un archivo de audio.
 */
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

/**
 * @brief Maneja el clic en la vista de árbol.
 *
 * Actualiza la lista de reproducción según el directorio seleccionado.
 *
 * @param index El índice del elemento seleccionado.
 */
void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    QString path = dirmodel->filePath(index);
    updatePlaylist(path); // Actualiza la lista de reproducción para el directorio seleccionado
}

/**
 * @brief Maneja el doble clic en la lista de reproducción.
 *
 * Reproduce el archivo seleccionado en la lista de reproducción.
 *
 * @param index El índice del elemento seleccionado.
 */
void MainWindow::on_playlistWidget_doubleClicked(const QModelIndex &index)
{
    QString filePath = playlist.at(index.row());
    playFile(filePath); // Reproduce el archivo seleccionado
}

/**
 * @brief Maneja los cambios en el estado del medio.
 *
 * Controla la reproducción según el modo de reproducción actual.
 *
 * @param status El nuevo estado del medio.
 */
void MainWindow::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia) {
        switch (currentPlaybackMode) {
        case PlaybackMode::Normal:
            if (currentIndex < playlist.size() - 1) {
                currentIndex++;
                playFile(playlist.at(currentIndex)); // Reproduce el siguiente archivo
            } else {
                MPlayer->stop();
                ui->btnPlayPause->setIcon(QIcon(":/icons/play.png")); // Cambiar a ícono de play
                IS_Paused = true;
            }
            break;
        case PlaybackMode::RepeatOne:
            MPlayer->setPosition(0); // Reinicia la posición al inicio
            MPlayer->play(); // Reproduce de nuevo el mismo archivo
            break;
        case PlaybackMode::RepeatAll:
            currentIndex = (currentIndex + 1) % playlist.size(); // Avanza al siguiente archivo en la lista
            playFile(playlist.at(currentIndex)); // Reproduce el siguiente archivo
            break;
        }
    }
}

/**
 * @brief Maneja el clic en el botón de anterior.
 *
 * Reproduce el archivo anterior en la lista de reproducción.
 */
void MainWindow::on_btnPrev_clicked()
{
    if (currentIndex > 0) {
        currentIndex--;
        QString filePath = playlist.at(currentIndex);
        playFile(filePath); // Reproduce el archivo anterior
    }
}

/**
 * @brief Maneja el clic en el botón de siguiente.
 *
 * Reproduce el siguiente archivo en la lista de reproducción.
 */
void MainWindow::on_btnNext_clicked()
{
    if (currentIndex < playlist.size() - 1) {
        currentIndex++;
        QString filePath = playlist.at(currentIndex);
        playFile(filePath); // Reproduce el siguiente archivo
    }
}

/**
 * @brief Maneja el clic en el botón de detener.
 *
 * Detiene la reproducción del medio actual.
 */
void MainWindow::on_btnStop_clicked()
{
    MPlayer->stop();
    ui->btnPlayPause->setIcon(QIcon(":/icons/play.png")); // Cambiar a ícono de play
    IS_Paused = true;

    // Reinicia la posición del slider
    ui->sldrSeek->setValue(0);
    // Actualiza el tiempo actual
    ui->currentTime->setText("00:00");
    if (Mduration > 3600) {
        ui->totalTime->setText("00:00:00");
    } else {
        ui->totalTime->setText("00:00");
    }
}

/**
 * @brief Maneja el cambio en el valor del control deslizante de volumen.
 *
 * Actualiza el volumen del audio y el ícono del botón de muteo según el nivel de volumen.
 *
 * @param value El nuevo valor del volumen (0-100).
 */
void MainWindow::on_sldrVolume_valueChanged(int value)
{
    audioOutput->setVolume(value / 100.0); // Ajusta el volumen del audio

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

/**
 * @brief Maneja el clic en el botón de reproducir/pausar.
 *
 * Alterna entre reproducir y pausar el medio actual.
 */
void MainWindow::on_btnPlayPause_clicked()
{
    if (IS_Paused) {
        MPlayer->play();
        ui->btnPlayPause->setIcon(QIcon(":/icons/pause.png")); // Cambiar a ícono de pausa
        IS_Paused = false;
    } else {
        MPlayer->pause();
        ui->btnPlayPause->setIcon(QIcon(":/icons/play.png")); // Cambiar a ícono de play
        IS_Paused = true;
    }
}

/**
 * @brief Maneja el movimiento del control deslizante de búsqueda.
 *
 * Cambia la posición de reproducción según la posición del slider.
 *
 * @param position La nueva posición del slider en segundos.
 */
void MainWindow::on_sldrSeek_sliderMoved(int position)
{
    MPlayer->setPosition(position * 1000); // Establece la posición en milisegundos
}

/**
 * @brief Configura el efecto de marquee para mostrar el nombre del archivo.
 *
 * @param text El texto a mostrar en el efecto marquee.
 */
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
    ui->fileName->setStyleSheet("QLabel { margin-left: 0px; font-size: 12pt; color: white; }");

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

/**
 * @brief Maneja el clic en el botón de shuffle.
 *
 * Alterna el estado del modo shuffle y actualiza la lista de reproducción.
 */
void MainWindow::on_btnShuffle_clicked()
{
    isShuffleEnabled = !isShuffleEnabled;

    if (isShuffleEnabled) {
        // Guarda la playlist original si aún no se ha guardado
        if (originalPlaylist.isEmpty()) {
            originalPlaylist = playlist;
        }

        // Crea una copia temporal de la playlist actual
        QStringList tempPlaylist = playlist;

        // Limpia la playlist actual
        playlist.clear();

        // Mezcla aleatoriamente
        while (!tempPlaylist.isEmpty()) {
            int randomIndex = QRandomGenerator::global()->bounded(tempPlaylist.size());
            playlist.append(tempPlaylist.takeAt(randomIndex));
        }

        // Actualiza la UI
        ui->btnShuffle->setIcon(QIcon(":/icons/shuffle_on.png"));

        // Actualiza la vista de la playlist
        ui->playlistWidget->clear();
        for (const QString &file : playlist) {
            QFileInfo fileInfo(file);
            ui->playlistWidget->addItem(fileInfo.fileName()); // Agrega el nombre del archivo a la lista de reproducción
        }
    } else {
        // Restaura el orden original
        if (!originalPlaylist.isEmpty()) {
            playlist = originalPlaylist;
            originalPlaylist.clear();
        }

        // Actualiza la UI
        ui->btnShuffle->setIcon(QIcon(":/icons/shuffle_off.png"));

        // Actualiza la vista de la playlist
        ui->playlistWidget->clear();
        for (const QString &file : playlist) {
            QFileInfo fileInfo(file);
            ui->playlistWidget->addItem(fileInfo.fileName()); // Agrega el nombre del archivo a la lista de reproducción
        }
    }
}

/**
 * @brief Actualiza la posición del texto en el efecto marquee.
 *
 * Desplaza el texto hacia la izquierda para crear un efecto de desplazamiento.
 */
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
    QString style = QString("QLabel { margin-left: %1px; font-size: 12pt; color: white; }").arg(marqueeOffset);
    ui->fileName->setStyleSheet(style);
    ui->fileName->setText(marqueeText);
}

/**
 * @brief Inicia el efecto marquee.
 *
 * Comienza a mover el texto en el QLabel.
 */
void MainWindow::startMarquee()
{
    if (isMarqueeNeeded && marqueeTimer) {
        marqueeOffset = 0;
        marqueeTimer->start(32);  // 60 FPS aproximadamente (1000ms/60 ≈ 16ms)
    }
}

/**
 * @brief Detiene el efecto marquee.
 *
 * Detiene el movimiento del texto y limpia el estilo del QLabel.
 */
void MainWindow::stopMarquee()
{
    if (marqueeTimer) {
        marqueeTimer->stop();
        ui->fileName->setStyleSheet(""); // Limpia el estilo del QLabel
    }
}

/**
 * @brief Maneja el evento cuando el slider de búsqueda es liberado.
 *
 * Establece la posición de reproducción según la posición del slider.
 */
void MainWindow::on_sldrSeek_sliderReleased()
{
    MPlayer->setPosition(ui->sldrSeek->value() * 1000); // Establece la posición en milisegundos
}
