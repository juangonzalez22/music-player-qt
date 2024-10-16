#include "mainwindow.h"  // Incluye el archivo de encabezado "mainwindow.h" que contiene la declaración de la clase MainWindow.
#include "ui_mainwindow.h"  // Incluye el archivo de interfaz de usuario generado automáticamente por Qt Designer.
#include <QFileDialog>  // Incluye la clase QFileDialog, que proporciona un cuadro de diálogo para seleccionar archivos y directorios.
#include <QTime>  // Incluye la clase QTime, que se utiliza para manejar y manipular tiempos.
#include <QFileInfo>  // Incluye la clase QFileInfo, que proporciona información sobre archivos y directorios.
#include <QDebug>  // Incluye la biblioteca QDebug, que permite imprimir mensajes de depuración en la consola.
#include <QMessageBox> // Asegúrate de incluir esta línea al inicio del archivo


// Constructor de la clase MainWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)  // Llama al constructor de la clase base QMainWindow y pasa el puntero al padre (parent).
    , ui(new Ui::MainWindow)  // Inicializa el puntero "ui" a una nueva instancia de la clase Ui::MainWindow, que gestiona la interfaz gráfica.
    , MPlayer(new QMediaPlayer(this))  // Crea una nueva instancia de QMediaPlayer y le pasa "this" como padre, para asegurar que se destruye correctamente.
    , audioOutput(new QAudioOutput(this))  // Crea una nueva instancia de QAudioOutput y también le pasa "this" como padre.
{
    ui->setupUi(this);  // Llama al método setupUi() para inicializar la interfaz gráfica de usuario, vinculando los widgets definidos en el archivo .ui con el código.

    QString sPath = "C:/"; // Esto debe ser una variable de instancia
    dirmodel = new QFileSystemModel(this);
    dirmodel->setRootPath(sPath);

    // Establecer filtros para mostrar solo archivos mp3, mp4 y carpetas
    dirmodel->setNameFilters(QStringList() << "*.mp3" << "*.mp4" << "*"); // Filtra para mostrar solo mp3, mp4 y carpetas
    dirmodel->setNameFilterDisables(false); // Habilitar el filtrado

    ui->treeView->setModel(dirmodel);
    ui->treeView->setRootIndex(dirmodel->setRootPath(sPath)); // Establece el índice raíz en el treeView

    MPlayer->setAudioOutput(audioOutput);  // Configura el QMediaPlayer para que use audioOutput como su salida de audio.

    // Configura el slider de volumen para que tenga un valor mínimo de 0 y un máximo de 100.
    ui->sldrVolume->setMinimum(0);  // Establece el valor mínimo del slider de volumen.
    ui->sldrVolume->setMaximum(100);  // Establece el valor máximo del slider de volumen.
    ui->sldrVolume->setValue(30);  // Inicializa el slider de volumen con un valor predeterminado de 30.

    // Establece el volumen del audioOutput basado en el valor actual del slider de volumen.
    audioOutput->setVolume(ui->sldrVolume->value() / 100.0);

    // Conecta la señal "durationChanged" de MPlayer con el slot "durationChanged" de MainWindow.
    connect(MPlayer, &QMediaPlayer::durationChanged, this, &MainWindow::durationChanged);

    // Conecta la señal "positionChanged" de MPlayer con el slot "positionChanged" de MainWindow.
    connect(MPlayer, &QMediaPlayer::positionChanged, this, &MainWindow::positionChanged);

    // Configura el rango del slider de búsqueda (seek) inicialmente de 0 a 0.
    ui->sldrSeek->setRange(0, 0);

    connect(ui->treeView, &QTreeView::doubleClicked, this, &MainWindow::on_treeView_doubleClicked);
}

// Destructor de la clase MainWindow.
MainWindow::~MainWindow()
{
    delete ui;  // Libera la memoria ocupada por el puntero "ui". Esto es esencial para evitar fugas de memoria.
}

void MainWindow::updateDuration(qint64 duration)
{
    // Este método actualiza la visualización de la duración del archivo multimedia.
    if (duration && Mduration) {
        QTime CurrentTime((duration / 3600) % 60, (duration / 60) % 60, duration % 60, (duration * 1000) % 1000);
        QTime TotalTime((Mduration / 3600) % 60, (Mduration / 60) % 60, Mduration % 60, (Mduration * 1000) % 1000);

        QString format = "mm:ss";  // Formato predeterminado para tiempo menor a 1 hora.
        if (Mduration > 3600) {  // Si la duración total es mayor a 1 hora, cambia el formato a horas.
            format = "hh:mm:ss";
        }

        ui->currentTime->setText(CurrentTime.toString(format));
        ui->totalTime->setText(TotalTime.toString(format));
    }
}

void MainWindow::durationChanged(qint64 duration)
{
    Mduration = duration / 1000;  // Almacena la duración en segundos.
    ui->sldrSeek->setMaximum(Mduration);
}

void MainWindow::positionChanged(qint64 position)
{
    if (!ui->sldrSeek->isSliderDown()) {
        updateDuration(position / 1000);  // Actualiza la duración mostrada con la posición actual.
        ui->sldrSeek->setValue(position / 1000);
    }
}

void MainWindow::on_btnMute_clicked()
{
    if (!IS_Muted) {
        audioOutput->setVolume(0);  // Si no está silenciado, se establece el volumen a 0 (silencio).
        IS_Muted = true;  // Actualiza el estado IS_Muted a true.
    } else {
        audioOutput->setVolume(ui->sldrVolume->value() / 100.0);
        IS_Muted = false;  // Actualiza el estado IS_Muted a false.
    }
}

void MainWindow::on_actionOpen_File_triggered()
{
    QString folderName = QFileDialog::getExistingDirectory(this, tr("Select Directory"), "");
    if (!folderName.isEmpty()) { // Comprobar si se seleccionó una carpeta
        sPath = folderName; // Actualizar sPath con la carpeta seleccionada
        dirmodel->setRootPath(sPath); // Actualiza el modelo con la nueva ruta
        ui->treeView->setRootIndex(dirmodel->setRootPath(sPath)); // Establece el índice raíz en el treeView
    }
}

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    // Verifica que la fila seleccionada sea válida
    if (!index.isValid()) {
        qDebug() << "Índice no válido";
        return;
    }

    // Obtén la ruta completa del archivo o directorio seleccionado
    QString filePath = dirmodel->filePath(index); // Obtener la ruta completa, no solo el nombre

    // Verifica si es un archivo y no un directorio
    QFileInfo fileInfo(filePath);
    if (fileInfo.isFile()) {
        // Comprueba la extensión del archivo
        QString extension = fileInfo.suffix().toLower(); // Obtiene la extensión en minúsculas

        if (extension == "mp3" || extension == "mp4") {
            // Si es un archivo de tipo permitido, configura el reproductor de medios
            MPlayer->setSource(QUrl::fromLocalFile(filePath));

            // Comprueba si hay algún error al cargar el archivo
            if (MPlayer->error() != QMediaPlayer::NoError) {
                qDebug() << "Error al cargar el archivo:" << MPlayer->errorString();
                return; // Sale si hubo un error
            }

            // Actualiza la interfaz con el nombre del archivo seleccionado
            ui->fileName->setText(fileInfo.fileName());

            // Inicia la reproducción
            MPlayer->play();
            IS_Paused = false; // Asegúrate de que el estado de pausa sea falso, ya que empezará a reproducir
        } else {
            // Si el archivo no es de tipo permitido, muestra un mensaje de advertencia
            QMessageBox msgBox;
            msgBox.setText("El archivo no se puede reproducir");
            msgBox.exec();
        }
    } else {
        qDebug() << "Directorio seleccionado, no se puede reproducir.";
    }
}

void MainWindow::on_btnStop_clicked()
{
    MPlayer->stop();  // Detiene la reproducción del medio actual.
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
        MPlayer->pause();  // Si no está en pausa, se pausa la reproducción.
        IS_Paused = true;  // Actualiza el estado IS_Paused a true.
    } else {
        MPlayer->play();  // Reanuda la reproducción del medio.
        IS_Paused = false;  // Actualiza el estado IS_Paused a false.
    }
}

void MainWindow::on_sldrSeek_sliderMoved(int position)
{
    MPlayer->setPosition(position * 1000);  // Establece la posición de reproducción del QMediaPlayer.
}

void MainWindow::on_sldrSeek_sliderReleased()
{
    MPlayer->setPosition(ui->sldrSeek->value() * 1000);  // Establece la posición final del slider.
}
