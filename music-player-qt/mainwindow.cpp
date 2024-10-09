#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MPlayer = new QMediaPlayer();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnMute_clicked()
{
    if(IS_Muted == false)
    {
        IS_Muted = true;
    }
    else
    {
        IS_Muted = false;
    }
}


void MainWindow::on_actionOpen_File_triggered()
{
    QString FileName = QFileDialog::getOpenFileName(this,tr("Select Audio File"),"",tr("MP3 Files (*.mp3)"));
    MPlayer->setSource(QUrl(FileName));

    QFileInfo fileInfo(FileName);
    ui->fileName->setText(fileInfo.fileName());
}

