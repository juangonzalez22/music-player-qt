#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia>
#include <QtCore>
#include <QtWidgets>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnMute_clicked();

    void on_actionOpen_File_triggered();

private:
    Ui::MainWindow *ui;
    bool IS_Muted = false;
    QMediaPlayer *MPlayer;
};
#endif // MAINWINDOW_H
