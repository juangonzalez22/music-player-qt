#include "mainwindow.h"  // Incluye el archivo de encabezado "mainwindow.h", que contiene la declaración de la clase MainWindow.
#include "ui_mainwindow.h"  // Incluye el archivo de interfaz de usuario generado automáticamente por Qt Designer.
#include <QFileDialog>  // Incluye la clase QFileDialog, que proporciona un cuadro de diálogo para seleccionar archivos y directorios.
#include <QTime>  // Incluye la clase QTime, que se utiliza para manejar y manipular tiempos.
#include <QFileInfo>  // Incluye la clase QFileInfo, que proporciona información sobre archivos y directorios.
#include <QDebug>  // Incluye la biblioteca QDebug, que permite imprimir mensajes de depuración en la consola.
#include <QMessageBox> // Incluye la clase QMessageBox, que permite mostrar diálogos de mensajes al usuario.

// Constructor de la clase MainWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)  // Llama al constructor de la clase base QMainWindow y pasa el puntero al padre (parent).
    , ui(new Ui::MainWindow)  // Inicializa el puntero "ui" a una nueva instancia de la clase Ui::MainWindow, que gestiona la interfaz gráfica.
    , MPlayer(new QMediaPlayer(this))  // Crea una nueva instancia de QMediaPlayer y le pasa "this" como padre, para asegurar que se destruye correctamente.
    , audioOutput(new QAudioOutput(this))  // Crea una nueva instancia de QAudioOutput y también le pasa "this" como padre.
{
    ui->setupUi(this);  // Llama al método setupUi() para inicializar la interfaz gráfica de usuario, vinculando los widgets definidos en el archivo .ui con el código.

    QString sPath = "C:/"; // Establece una ruta inicial, que será la raíz del explorador de archivos.
    dirmodel = new QFileSystemModel(this); // Crea un nuevo modelo de sistema de archivos para gestionar la visualización de archivos y directorios.
    dirmodel->setRootPath(sPath); // Establece la raíz del modelo de sistema de archivos.

    // Establecer filtros para mostrar solo archivos mp3, mp4 y carpetas.
    dirmodel->setNameFilters(QStringList() << "*.mp3" << "*.mp4" << "*"); // Filtra para mostrar solo archivos de tipo mp3, mp4 y todos los directorios.
    dirmodel->setNameFilterDisables(false); // Habilita el filtrado.

    // Asocia el modelo de sistema de archivos al treeView de la interfaz de usuario.
    ui->treeView->setModel(dirmodel);
    ui->treeView->setRootIndex(dirmodel->setRootPath(sPath)); // Establece el índice raíz del treeView en la ruta inicial.

    // Configura el reproductor de medios para usar la salida de audio.
    MPlayer->setAudioOutput(audioOutput);

    // Configura el slider de volumen para que tenga un valor mínimo de 0 y un máximo de 100.
    ui->sldrVolume->setMinimum(0);  // Establece el valor mínimo del slider de volumen.
    ui->sldrVolume->setMaximum(100);  // Establece el valor máximo del slider de volumen.
    ui->sldrVolume->setValue(30);  // Inicializa el slider de volumen con un valor predeterminado de 30.

    // Establece el volumen del audioOutput basado en el valor actual del slider de volumen.
    audioOutput->setVolume(ui->sldrVolume->value() / 100.0);

    // Conecta la señal "durationChanged" de MPlayer al slot "durationChanged" de MainWindow para manejar cambios en la duración del medio.
    connect(MPlayer, &QMediaPlayer::durationChanged, this, &MainWindow::durationChanged);

    // Conecta la señal "positionChanged" de MPlayer al slot "positionChanged" de MainWindow para manejar cambios en la posición de reproducción.
    connect(MPlayer, &QMediaPlayer::positionChanged, this, &MainWindow::positionChanged);

    // Configura el rango del slider de búsqueda (seek) inicialmente de 0 a 0.
    ui->sldrSeek->setRange(0, 0);

    // Conecta la señal de doble clic del treeView al slot "on_treeView_doubleClicked" para gestionar la selección de archivos.
    connect(ui->treeView, &QTreeView::doubleClicked, this, &MainWindow::on_treeView_doubleClicked);
}

// Destructor de la clase MainWindow.
MainWindow::~MainWindow()
{
    delete ui;  // Libera la memoria ocupada por el puntero "ui". Esto es esencial para evitar fugas de memoria.
}

// Este método actualiza la visualización de la duración del archivo multimedia.
void MainWindow::updateDuration(qint64 duration)
{
    if (duration && Mduration) { // Comprueba si la duración es válida y si Mduration también lo es.
        // Calcula el tiempo actual y total en formato HH:MM:SS o MM:SS dependiendo de la duración.
        QTime CurrentTime((duration / 3600) % 60, (duration / 60) % 60, duration % 60, (duration * 1000) % 1000);
        QTime TotalTime((Mduration / 3600) % 60, (Mduration / 60) % 60, Mduration % 60, (Mduration * 1000) % 1000);

        // Establece el formato de tiempo.
        QString format = "mm:ss";  // Formato predeterminado para tiempos menores a 1 hora.
        if (Mduration > 3600) {  // Si la duración total es mayor a 1 hora, cambia el formato a horas.
            format = "hh:mm:ss";
        }

        // Actualiza las etiquetas de tiempo actual y total en la interfaz gráfica.
        ui->currentTime->setText(CurrentTime.toString(format));
        ui->totalTime->setText(TotalTime.toString(format));
    }
}

// Este slot es llamado cuando la duración del medio cambia.
void MainWindow::durationChanged(qint64 duration)
{
    Mduration = duration / 1000;  // Almacena la duración en segundos.
    ui->sldrSeek->setMaximum(Mduration); // Establece el valor máximo del slider de búsqueda basado en la duración del medio.
}

// Este slot es llamado cuando la posición de reproducción cambia.
void MainWindow::positionChanged(qint64 position)
{
    if (!ui->sldrSeek->isSliderDown()) { // Solo actualiza la interfaz si el slider no está siendo arrastrado.
        updateDuration(position / 1000);  // Actualiza la duración mostrada con la posición actual.
        ui->sldrSeek->setValue(position / 1000); // Actualiza la posición del slider de búsqueda.
    }
}

// Este slot es llamado cuando el botón de silencio es presionado.
void MainWindow::on_btnMute_clicked()
{
    if (!IS_Muted) { // Comprueba si no está silenciado.
        audioOutput->setVolume(0);  // Si no está silenciado, establece el volumen a 0 (silencio).
        IS_Muted = true;  // Actualiza el estado IS_Muted a true.
    } else {
        audioOutput->setVolume(ui->sldrVolume->value() / 100.0); // Restaura el volumen al nivel del slider.
        IS_Muted = false;  // Actualiza el estado IS_Muted a false.
    }
}

// Este slot es llamado cuando el usuario selecciona la opción "Abrir Archivo".
void MainWindow::on_actionOpen_File_triggered()
{
    QString folderName = QFileDialog::getExistingDirectory(this, tr("Select Directory"), ""); // Abre un diálogo para seleccionar un directorio.
    if (!folderName.isEmpty()) { // Comprobar si se seleccionó una carpeta.
        sPath = folderName; // Actualiza sPath con la carpeta seleccionada.
        dirmodel->setRootPath(sPath); // Actualiza el modelo con la nueva ruta.
        ui->treeView->setRootIndex(dirmodel->setRootPath(sPath)); // Establece el índice raíz en el treeView.
    }
}

// Este slot es llamado cuando el usuario hace doble clic en un elemento del treeView.
void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    // Verifica que la fila seleccionada sea válida.
    if (!index.isValid()) {
        qDebug() << "Índice no válido"; // Imprime un mensaje de depuración si el índice no es válido.
        return; // Sale de la función si el índice no es válido.
    }

    // Obtén la ruta completa del archivo o directorio seleccionado.
    QString filePath = dirmodel->filePath(index); // Obtener la ruta completa, no solo el nombre del archivo.

    // Verifica si es un archivo y no un directorio.
    QFileInfo fileInfo(filePath); // Crea un objeto QFileInfo para obtener información sobre el archivo.
    if (fileInfo.isFile()) { // Comprueba si el elemento seleccionado es un archivo.
        // Comprueba la extensión del archivo.
        QString extension = fileInfo.suffix().toLower(); // Obtiene la extensión del archivo en minúsculas.

        // Verifica si el archivo tiene una extensión válida (mp3 o mp4).
        if (extension == "mp3" || extension == "mp4") {
            // Si es un archivo de tipo permitido, configura el reproductor de medios.
            MPlayer->setSource(QUrl::fromLocalFile(filePath)); // Establece la fuente del reproductor a la ruta del archivo.

            // Comprueba si hay algún error al cargar el archivo.
            if (MPlayer->error() != QMediaPlayer::NoError) {
                qDebug() << "Error al cargar el archivo:" << MPlayer->errorString(); // Imprime el mensaje de error en la consola.
                return; // Sale si hubo un error al cargar el archivo.
            }

            // Actualiza la interfaz con el nombre del archivo seleccionado.
            ui->fileName->setText(fileInfo.fileName()); // Muestra el nombre del archivo en la interfaz.

            // Inicia la reproducción del medio.
            MPlayer->play(); // Comienza a reproducir el archivo seleccionado.
            IS_Paused = false; // Asegúrate de que el estado de pausa sea falso, ya que empezará a reproducir.
        } else {
            // Si el archivo no es de tipo permitido, muestra un mensaje de advertencia.
            QMessageBox msgBox; // Crea un cuadro de mensaje.
            msgBox.setText("El archivo no se puede reproducir"); // Establece el texto del mensaje.
            msgBox.exec(); // Muestra el cuadro de mensaje al usuario.
        }
    } else {
        qDebug() << "Directorio seleccionado, no se puede reproducir."; // Imprime un mensaje de depuración si se selecciona un directorio.
    }
}

// Este slot es llamado cuando el usuario presiona el botón de detener.
void MainWindow::on_btnStop_clicked()
{
    MPlayer->stop();  // Detiene la reproducción del medio actual.
}

// Este slot es llamado cuando el usuario presiona el botón de anterior.
void MainWindow::on_btnPrev_clicked()
{
    // Implementación para reproducir la pista anterior.
}

// Este slot es llamado cuando el usuario presiona el botón de siguiente.
void MainWindow::on_btnNext_clicked()
{
    // Implementación para reproducir la siguiente pista.
}

// Este slot es llamado cuando el valor del slider de volumen cambia.
void MainWindow::on_sldrVolume_valueChanged(int value)
{
    audioOutput->setVolume(value / 100.0); // Establece el volumen de audioOutput basado en el nuevo valor del slider.
}

// Este slot es llamado cuando el usuario presiona el botón de reproducir/pausar.
void MainWindow::on_btnPlayPause_clicked()
{
    if (!IS_Paused) { // Comprueba si no está en pausa.
        MPlayer->pause();  // Si no está en pausa, se pausa la reproducción.
        IS_Paused = true;  // Actualiza el estado IS_Paused a true.
    } else {
        MPlayer->play();  // Reanuda la reproducción del medio.
        IS_Paused = false;  // Actualiza el estado IS_Paused a false.
    }
}

// Este slot es llamado cuando el slider de búsqueda es movido.
void MainWindow::on_sldrSeek_sliderMoved(int position)
{
    MPlayer->setPosition(position * 1000);  // Establece la posición de reproducción del QMediaPlayer en milisegundos.
}

// Este slot es llamado cuando el usuario libera el slider de búsqueda.
void MainWindow::on_sldrSeek_sliderReleased()
{
    MPlayer->setPosition(ui->sldrSeek->value() * 1000);  // Establece la posición final del slider en milisegundos.
}
