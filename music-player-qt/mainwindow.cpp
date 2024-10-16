#include "mainwindow.h"  // Incluye el archivo de encabezado "mainwindow.h" que contiene la declaración de la clase MainWindow.
// Esto permite que este archivo fuente tenga acceso a la definición de la clase, sus métodos y miembros.

#include "ui_mainwindow.h"  // Incluye el archivo de interfaz de usuario generado automáticamente por Qt Designer.
// Este archivo se encarga de manejar y conectar los elementos gráficos de la interfaz de usuario (como botones, sliders, etc.) con la lógica del código.

#include <QFileDialog>  // Incluye la clase QFileDialog, que proporciona un cuadro de diálogo para seleccionar archivos y directorios.
#include <QTime>  // Incluye la clase QTime, que se utiliza para manejar y manipular tiempos.
#include <QFileInfo>  // Incluye la clase QFileInfo, que proporciona información sobre archivos y directorios.
#include <QDebug>  // Incluye la biblioteca QDebug, que permite imprimir mensajes de depuración en la consola.


// Constructor de la clase MainWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)  // Llama al constructor de la clase base QMainWindow y pasa el puntero al padre (parent).
    , ui(new Ui::MainWindow)  // Inicializa el puntero "ui" a una nueva instancia de la clase Ui::MainWindow, que gestiona la interfaz gráfica.
    , MPlayer(new QMediaPlayer(this))  // Crea una nueva instancia de QMediaPlayer y le pasa "this" como padre, para asegurar que se destruye correctamente.
    , audioOutput(new QAudioOutput(this))  // Crea una nueva instancia de QAudioOutput y también le pasa "this" como padre.
{
    ui->setupUi(this);  // Llama al método setupUi() para inicializar la interfaz gráfica de usuario, vinculando los widgets definidos en el archivo .ui con el código.

    MPlayer->setAudioOutput(audioOutput);  // Configura el QMediaPlayer para que use audioOutput como su salida de audio.

    // Configura el slider de volumen para que tenga un valor mínimo de 0 y un máximo de 100.
    ui->sldrVolume->setMinimum(0);  // Establece el valor mínimo del slider de volumen.
    ui->sldrVolume->setMaximum(100);  // Establece el valor máximo del slider de volumen.
    ui->sldrVolume->setValue(30);  // Inicializa el slider de volumen con un valor predeterminado de 30.

    // Establece el volumen del audioOutput basado en el valor actual del slider de volumen.
    // Se divide por 100.0 para convertir el rango de 0-100 a un rango de 0.0-1.0 que QAudioOutput requiere.
    audioOutput->setVolume(ui->sldrVolume->value() / 100.0);

    // Conecta la señal "durationChanged" de MPlayer con el slot "durationChanged" de MainWindow.
    // Esto permite que el método durationChanged se ejecute automáticamente cada vez que la duración del medio cambie.
    connect(MPlayer, &QMediaPlayer::durationChanged, this, &MainWindow::durationChanged);

    // Conecta la señal "positionChanged" de MPlayer con el slot "positionChanged" de MainWindow.
    // Esto permite que el método positionChanged se ejecute automáticamente cada vez que la posición de reproducción cambie.
    connect(MPlayer, &QMediaPlayer::positionChanged, this, &MainWindow::positionChanged);

    // Configura el rango del slider de búsqueda (seek) inicialmente de 0 a 0.
    // Esto se actualizará más tarde cuando se cargue un archivo de audio.
    ui->sldrSeek->setRange(0, 0);
}

// Destructor de la clase MainWindow.
MainWindow::~MainWindow()
{
    delete ui;  // Libera la memoria ocupada por el puntero "ui". Esto es esencial para evitar fugas de memoria.
}

void MainWindow::updateDuration(qint64 duration)
{
    // Este método actualiza la visualización de la duración del archivo multimedia.
    // "duration" es la duración en milisegundos que se pasa al método.

    // Comprueba si la duración proporcionada no es cero y si Mduration (la duración total) no es cero.
    if(duration && Mduration){
        // Crea un objeto QTime para el tiempo actual basado en la duración proporcionada.
        // Convierte la duración de milisegundos a horas, minutos y segundos.
        QTime CurrentTime((duration / 3600) % 60, (duration / 60) % 60, duration % 60, (duration * 1000) % 1000);

        // Crea un objeto QTime para el tiempo total basado en la duración total del medio (Mduration).
        QTime TotalTime((Mduration / 3600) % 60, (Mduration / 60) % 60, Mduration % 60, (Mduration * 1000) % 1000);

        // Inicializa el formato de tiempo que se mostrará en la interfaz gráfica.
        QString format = "mm:ss";  // Formato predeterminado para tiempo menor a 1 hora.
        if(Mduration > 3600) {  // Si la duración total es mayor a 1 hora, cambia el formato a horas.
            format = "hh:mm:ss";
        }

        // Actualiza el texto en el widget "currentTime" con el tiempo actual formateado.
        ui->currentTime->setText(CurrentTime.toString(format));

        // Actualiza el texto en el widget "totalTime" con el tiempo total formateado.
        ui->totalTime->setText(TotalTime.toString(format));
    }
}

void MainWindow::durationChanged(qint64 duration)
{
    // Este slot se llama cuando la duración del medio cambia.
    // Actualiza Mduration y el rango del slider de búsqueda (seek).

    Mduration = duration / 1000;  // Almacena la duración en segundos (convirtiendo de milisegundos a segundos).

    // Establece el máximo del slider de búsqueda (seek) al valor de duración total.
    ui->sldrSeek->setMaximum(Mduration);
}

void MainWindow::positionChanged(qint64 position)
{
    // Este slot se llama cuando la posición de reproducción cambia.
    // Actualiza el slider de búsqueda y la duración mostrada si el slider no está siendo manipulado.

    if (!ui->sldrSeek->isSliderDown()) {  // Verifica si el usuario no está actualmente moviendo el slider.
        updateDuration(position / 1000);  // Actualiza la duración mostrada con la posición actual.

        // Establece el valor del slider de búsqueda a la posición actual (convirtiendo de milisegundos a segundos).
        ui->sldrSeek->setValue(position / 1000);
    }
}

void MainWindow::on_btnMute_clicked()
{
    // Este slot se llama cuando el botón de silenciar es clicado.

    // Verifica si el audio no está actualmente silenciado.
    if (!IS_Muted) {
        audioOutput->setVolume(0);  // Si no está silenciado, se establece el volumen a 0 (silencio).
        IS_Muted = true;  // Actualiza el estado IS_Muted a true.
    } else {  // Si ya está silenciado,
        // Restaura el volumen del audioOutput al valor actual del slider de volumen.
        audioOutput->setVolume(ui->sldrVolume->value() / 100.0);
        IS_Muted = false;  // Actualiza el estado IS_Muted a false.
    }
}

void MainWindow::on_actionOpen_File_triggered()
{
    // Este slot se llama cuando el usuario selecciona la opción "Abrir Archivo" del menú.

    // Abre un cuadro de diálogo para seleccionar un archivo de audio, permitiendo solo archivos MP3.
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select Audio File"), "", tr("MP3 Files (*.mp3)"));

    // Si no se selecciona ningún archivo (el usuario cancela), se sale de la función.
    if (fileName.isEmpty()) return;

    // Establece la fuente del QMediaPlayer al archivo seleccionado, convirtiendo la ruta del archivo a un objeto QUrl.
    MPlayer->setSource(QUrl::fromLocalFile(fileName));

    // Verifica si hay errores al cargar el archivo.
    if (MPlayer->error() != QMediaPlayer::NoError) {
        // Si hay un error, imprime un mensaje de depuración en la consola con la descripción del error.
        qDebug() << "Error al cargar el archivo:" << MPlayer->errorString();
        return;  // Sale de la función si hubo un error.
    }

    // Usa QFileInfo para obtener información sobre el archivo, como su nombre.
    QFileInfo fileInfo(fileName);

    // Muestra el nombre del archivo en el widget "fileName" de la interfaz gráfica.
    ui->fileName->setText(fileInfo.fileName());
}

void MainWindow::on_btnStop_clicked()
{
    // Este slot se llama cuando el botón de detener es clicado.
    // Detiene la reproducción del medio actual.
    MPlayer->stop();
}

void MainWindow::on_btnPrev_clicked()
{
    // Este slot se llama cuando el botón de pista anterior es clicado.
    // Aquí se puede implementar la funcionalidad para reproducir la pista anterior.
    // Actualmente no hay implementación.
}

void MainWindow::on_btnNext_clicked()
{
    // Este slot se llama cuando el botón de siguiente pista es clicado.
    // Aquí se puede implementar la funcionalidad para reproducir la siguiente pista.
    // Actualmente no hay implementación.
}

void MainWindow::on_sldrVolume_valueChanged(int value)
{
    // Este slot se llama cada vez que el valor del slider de volumen cambia.

    // Establece el volumen del audioOutput al nuevo valor del slider, convirtiendo el rango de 0-100 a 0.0-1.0.
    audioOutput->setVolume(value / 100.0);
}

void MainWindow::on_btnPlayPause_clicked()
{
    // Este slot se llama cuando el botón de reproducir/pausar es clicado.

    // Comprueba si el medio no está en pausa.
    if (!IS_Paused) {
        MPlayer->pause();  // Si no está en pausa, se pausa la reproducción.
        IS_Paused = true;  // Actualiza el estado IS_Paused a true.
    } else {  // Si está en pausa,
        MPlayer->play();  // Reanuda la reproducción del medio.
        IS_Paused = false;  // Actualiza el estado IS_Paused a false.
    }
}

void MainWindow::on_sldrSeek_sliderMoved(int position)
{
    // Este slot se llama cuando el slider de búsqueda se mueve.
    // "position" es la nueva posición del slider en segundos.

    // Establece la posición de reproducción del QMediaPlayer a la nueva posición seleccionada en el slider (convirtiendo de segundos a milisegundos).
    MPlayer->setPosition(position * 1000);
}

void MainWindow::on_sldrSeek_sliderReleased()
{
    // Este slot se llama cuando se libera el slider de búsqueda.
    // Establece la posición de reproducción del QMediaPlayer a la posición final del slider (en milisegundos).

    MPlayer->setPosition(ui->sldrSeek->value() * 1000);  // Convierte de segundos a milisegundos.
}

