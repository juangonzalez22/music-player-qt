/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen_File;
    QWidget *centralwidget;
    QPushButton *btnStop;
    QPushButton *btnNext;
    QSlider *sldrSeek;
    QSlider *sldrVolume;
    QPushButton *btnPrev;
    QLabel *fileName;
    QLabel *currentTime;
    QLabel *totalTime;
    QPushButton *btnMute;
    QPushButton *btnPlayPause;
    QGroupBox *groupBox;
    QPushButton *btnPlaybackMode;
    QSplitter *splitter;
    QTreeView *treeView;
    QListWidget *playlistWidget;
    QPushButton *btnShuffle;
    QMenuBar *menubar;
    QMenu *menuOPen;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setEnabled(true);
        MainWindow->resize(1024, 576);
        MainWindow->setMinimumSize(QSize(1024, 576));
        MainWindow->setMaximumSize(QSize(1024, 576));
        QFont font;
        font.setPointSize(15);
        MainWindow->setFont(font);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"    background-color: #2C2C2C; /* Color de fondo oscuro */\n"
"}\n"
""));
        actionOpen_File = new QAction(MainWindow);
        actionOpen_File->setObjectName("actionOpen_File");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Microsoft JhengHei UI")});
        actionOpen_File->setFont(font1);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        btnStop = new QPushButton(centralwidget);
        btnStop->setObjectName("btnStop");
        btnStop->setGeometry(QRect(480, 430, 44, 44));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Microsoft JhengHei UI Light")});
        btnStop->setFont(font2);
        btnStop->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-radius: 21px;  /* Hace que los bordes del bot\303\263n sean redondeados */\n"
"    min-width: 40px;      /* Establece el ancho m\303\255nimo del bot\303\263n */\n"
"    max-width: 40px;      /* Establece el ancho m\303\241ximo del bot\303\263n */\n"
"    min-height: 40px;     /* Establece la altura m\303\255nima del bot\303\263n */\n"
"    max-height: 40px;     /* Establece la altura m\303\241xima del bot\303\263n */\n"
"    border: 2px solid black;  /* Crea un borde s\303\263lido negro de 2 p\303\255xeles */\n"
"    background-color: #6A6A6A;  /* Establece el color de fondo a #6A6A6A */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #555555;  /* Color ligeramente m\303\241s oscuro cuando se presiona */\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #C0C0C0; /* Color cuando se pasa el mouse */\n"
"}\n"
""));
        btnNext = new QPushButton(centralwidget);
        btnNext->setObjectName("btnNext");
        btnNext->setGeometry(QRect(530, 430, 44, 44));
        btnNext->setFont(font2);
        btnNext->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-radius: 21px;  /* Hace que los bordes del bot\303\263n sean redondeados */\n"
"    min-width: 40px;      /* Establece el ancho m\303\255nimo del bot\303\263n */\n"
"    max-width: 40px;      /* Establece el ancho m\303\241ximo del bot\303\263n */\n"
"    min-height: 40px;     /* Establece la altura m\303\255nima del bot\303\263n */\n"
"    max-height: 40px;     /* Establece la altura m\303\241xima del bot\303\263n */\n"
"    border: 2px solid black;  /* Crea un borde s\303\263lido negro de 2 p\303\255xeles */\n"
"    background-color: #6A6A6A;  /* Establece el color de fondo a #6A6A6A */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #555555;  /* Color ligeramente m\303\241s oscuro cuando se presiona */\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #C0C0C0; /* Color cuando se pasa el mouse */\n"
"}\n"
""));
        sldrSeek = new QSlider(centralwidget);
        sldrSeek->setObjectName("sldrSeek");
        sldrSeek->setGeometry(QRect(10, 480, 1001, 20));
        sldrSeek->setStyleSheet(QString::fromUtf8("QSlider {\n"
"    background: #2C2C2C; /* Color de fondo del slider */\n"
"}\n"
"\n"
"QSlider::groove:horizontal {\n"
"    background: #4A4A4A; /* Color de la pista del slider */\n"
"    height: 8px; /* Altura de la pista */\n"
"    border-radius: 4px; /* Bordes redondeados de la pista */\n"
"}\n"
"\n"
"QSlider::sub-page:horizontal {\n"
"    background: #121212; /* Color m\303\241s oscuro cuando se llena el slider */\n"
"	border: 2px solid #000000; /* Borde negro alrededor*/\n"
"    border-radius: 4px; /* Bordes redondeados de la pista de llenado */\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"    background: #6A6A6A; /* Color del control deslizante */\n"
"    border: 2px solid #000000; /* Borde negro alrededor del control deslizante */\n"
"    width: 16px; /* Ancho del control deslizante */\n"
"    margin: -4px 0; /* Margen superior e inferior */\n"
"    border-radius: 8px; /* Bordes redondeados del control deslizante */\n"
"}\n"
"\n"
"QSlider::handle:horizontal:hover {\n"
"    background: #8A8A8A; /* Colo"
                        "r del control deslizante al pasar el mouse */\n"
"}\n"
"\n"
"QSlider::handle:horizontal:pressed {\n"
"    background: #A0A0A0; /* Color del control deslizante cuando se presiona */\n"
"}\n"
"\n"
"\n"
""));
        sldrSeek->setOrientation(Qt::Orientation::Horizontal);
        sldrVolume = new QSlider(centralwidget);
        sldrVolume->setObjectName("sldrVolume");
        sldrVolume->setGeometry(QRect(920, 440, 91, 20));
        sldrVolume->setStyleSheet(QString::fromUtf8("QSlider {\n"
"    background: #2C2C2C; /* Color de fondo del slider */\n"
"}\n"
"\n"
"QSlider::groove:horizontal {\n"
"    background: #4A4A4A; /* Color de la pista del slider */\n"
"    height: 8px; /* Altura de la pista */\n"
"    border-radius: 4px; /* Bordes redondeados de la pista */\n"
"}\n"
"\n"
"QSlider::sub-page:horizontal {\n"
"    background: #121212; /* Color m\303\241s oscuro cuando se llena el slider */\n"
"	border: 2px solid #000000; /* Borde negro alrededor*/\n"
"    border-radius: 4px; /* Bordes redondeados de la pista de llenado */\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"    background: #6A6A6A; /* Color del control deslizante */\n"
"    border: 2px solid #000000; /* Borde negro alrededor del control deslizante */\n"
"    width: 16px; /* Ancho del control deslizante */\n"
"    margin: -4px 0; /* Margen superior e inferior */\n"
"    border-radius: 8px; /* Bordes redondeados del control deslizante */\n"
"}\n"
"\n"
"QSlider::handle:horizontal:hover {\n"
"    background: #8A8A8A; /* Colo"
                        "r del control deslizante al pasar el mouse */\n"
"}\n"
"\n"
"QSlider::handle:horizontal:pressed {\n"
"    background: #A0A0A0; /* Color del control deslizante cuando se presiona */\n"
"}\n"
"\n"
"\n"
""));
        sldrVolume->setOrientation(Qt::Orientation::Horizontal);
        btnPrev = new QPushButton(centralwidget);
        btnPrev->setObjectName("btnPrev");
        btnPrev->setGeometry(QRect(380, 430, 44, 44));
        btnPrev->setFont(font2);
        btnPrev->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-radius: 21px;  /* Hace que los bordes del bot\303\263n sean redondeados */\n"
"    min-width: 40px;      /* Establece el ancho m\303\255nimo del bot\303\263n */\n"
"    max-width: 40px;      /* Establece el ancho m\303\241ximo del bot\303\263n */\n"
"    min-height: 40px;     /* Establece la altura m\303\255nima del bot\303\263n */\n"
"    max-height: 40px;     /* Establece la altura m\303\241xima del bot\303\263n */\n"
"    border: 2px solid black;  /* Crea un borde s\303\263lido negro de 2 p\303\255xeles */\n"
"    background-color: #6A6A6A;  /* Establece el color de fondo a #6A6A6A */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #555555;  /* Color ligeramente m\303\241s oscuro cuando se presiona */\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #C0C0C0; /* Color cuando se pasa el mouse */\n"
"}\n"
""));
        fileName = new QLabel(centralwidget);
        fileName->setObjectName("fileName");
        fileName->setGeometry(QRect(10, 430, 281, 41));
        fileName->setFont(font2);
        fileName->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: white;                          /* Color del texto */\n"
"    font-size: 18px;                       /* Tama\303\261o de fuente */\n"
"    background-color: rgba(0, 0, 0, 0);    /* Fondo transparente */\n"
"    padding: 5px;                          /* Espaciado interno */\n"
"    border: none;                          /* Sin borde */\n"
"}\n"
"\n"
"QLabel::before {\n"
"    content: \"\";                           /* Necesario para el pseudo-elemento */\n"
"    color: rgba(0, 0, 0, 0.5);            /* Color de la sombra (negro con opacidad) */\n"
"    position: absolute;                    /* Posicionamiento absoluto */\n"
"    left: 2px;                             /* Desplazamiento horizontal */\n"
"    top: 2px;                              /* Desplazamiento vertical */\n"
"    font-size: 18px;                       /* Tama\303\261o de fuente igual al del label */\n"
"}\n"
""));
        currentTime = new QLabel(centralwidget);
        currentTime->setObjectName("currentTime");
        currentTime->setGeometry(QRect(10, 500, 111, 21));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Microsoft JhengHei UI Light")});
        font3.setBold(true);
        currentTime->setFont(font3);
        currentTime->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: white;                          /* Color del texto */\n"
"    font-size: 14px;                       /* Tama\303\261o de fuente */\n"
"    background-color: rgba(0, 0, 0, 0);    /* Fondo transparente */\n"
"    padding: 5px;                          /* Espaciado interno */\n"
"    border: none;                          /* Sin borde */\n"
"}\n"
"\n"
"QLabel::before {\n"
"    content: \"\";                           /* Necesario para el pseudo-elemento */\n"
"    color: rgba(0, 0, 0, 0.5);            /* Color de la sombra (negro con opacidad) */\n"
"    position: absolute;                    /* Posicionamiento absoluto */\n"
"    left: 2px;                             /* Desplazamiento horizontal */\n"
"    top: 2px;                              /* Desplazamiento vertical */\n"
"    font-size: 14px;                       /* Tama\303\261o de fuente igual al del label */\n"
"}"));
        totalTime = new QLabel(centralwidget);
        totalTime->setObjectName("totalTime");
        totalTime->setGeometry(QRect(930, 500, 81, 21));
        totalTime->setFont(font3);
        totalTime->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        totalTime->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: white;                          /* Color del texto */\n"
"    font-size: 14px;                       /* Tama\303\261o de fuente */\n"
"    background-color: rgba(0, 0, 0, 0);    /* Fondo transparente */\n"
"    padding: 5px;                          /* Espaciado interno */\n"
"    border: none;                          /* Sin borde */\n"
"}\n"
"\n"
"QLabel::before {\n"
"    content: \"\";                           /* Necesario para el pseudo-elemento */\n"
"    color: rgba(0, 0, 0, 0.5);            /* Color de la sombra (negro con opacidad) */\n"
"    position: absolute;                    /* Posicionamiento absoluto */\n"
"    left: 2px;                             /* Desplazamiento horizontal */\n"
"    top: 2px;                              /* Desplazamiento vertical */\n"
"    font-size: 10px;                       /* Tama\303\261o de fuente igual al del label */\n"
"}"));
        btnMute = new QPushButton(centralwidget);
        btnMute->setObjectName("btnMute");
        btnMute->setGeometry(QRect(870, 430, 44, 44));
        btnMute->setFont(font2);
        btnMute->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-radius: 21px;  /* Hace que los bordes del bot\303\263n sean redondeados */\n"
"    min-width: 40px;      /* Establece el ancho m\303\255nimo del bot\303\263n */\n"
"    max-width: 40px;      /* Establece el ancho m\303\241ximo del bot\303\263n */\n"
"    min-height: 40px;     /* Establece la altura m\303\255nima del bot\303\263n */\n"
"    max-height: 40px;     /* Establece la altura m\303\241xima del bot\303\263n */\n"
"    border: 2px solid black;  /* Crea un borde s\303\263lido negro de 2 p\303\255xeles */\n"
"    background-color: #6A6A6A;  /* Establece el color de fondo a #6A6A6A */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #555555;  /* Color ligeramente m\303\241s oscuro cuando se presiona */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #C0C0C0; /* Color cuando se pasa el mouse */\n"
"}\n"
""));
        btnPlayPause = new QPushButton(centralwidget);
        btnPlayPause->setObjectName("btnPlayPause");
        btnPlayPause->setGeometry(QRect(430, 430, 44, 44));
        btnPlayPause->setFont(font2);
        btnPlayPause->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-radius: 21px;  /* Hace que los bordes del bot\303\263n sean redondeados */\n"
"    min-width: 40px;      /* Establece el ancho m\303\255nimo del bot\303\263n */\n"
"    max-width: 40px;      /* Establece el ancho m\303\241ximo del bot\303\263n */\n"
"    min-height: 40px;     /* Establece la altura m\303\255nima del bot\303\263n */\n"
"    max-height: 40px;     /* Establece la altura m\303\241xima del bot\303\263n */\n"
"    border: 2px solid black;  /* Crea un borde s\303\263lido negro de 2 p\303\255xeles */\n"
"    background-color: #6A6A6A;  /* Establece el color de fondo a #6A6A6A */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #555555;  /* Color ligeramente m\303\241s oscuro cuando se presiona */\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #C0C0C0; /* Color cuando se pasa el mouse */\n"
"}\n"
""));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(290, 10, 720, 401));
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: rgba(20, 20, 20, 0.95);   /* Fondo oscuro */\n"
"    border: 1px solid rgba(255, 255, 255, 0.1); /* Borde sutil */\n"
"    padding: 10px;                              /* Espaciado interno del grupo */\n"
"    color: #D0D0D0;                            /* Color del texto */\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    background-color: transparent;              /* Fondo transparente para el t\303\255tulo */\n"
"    color: #D0D0D0;                            /* Color del texto del t\303\255tulo */\n"
"    padding: 5px;                              /* Espaciado del t\303\255tulo */\n"
"}\n"
"\n"
"QGroupBox::indicator {\n"
"    background-color: rgba(35, 35, 35, 0.8);    /* Fondo de los indicadores (como checkboxes o radio buttons) */\n"
"    border: 1px solid rgba(255, 255, 255, 0.08); /* Borde sutil para los indicadores */\n"
"    padding: 4px;                              /* Espaciado interno para indicadores */\n"
"}\n"
"\n"
"QGroupBox::indicator:checked {\n"
"    background-"
                        "color: rgba(100, 149, 237, 0.4); /* Fondo al estar chequeado (ej. checkbox) */\n"
"    border: 1px solid rgba(255, 255, 255, 0.1); /* Borde m\303\241s marcado para el estado chequeado */\n"
"}\n"
""));
        btnPlaybackMode = new QPushButton(centralwidget);
        btnPlaybackMode->setObjectName("btnPlaybackMode");
        btnPlaybackMode->setGeometry(QRect(580, 436, 34, 34));
        btnPlaybackMode->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-radius: 15px;  /* Hace que los bordes del bot\303\263n sean redondeados */\n"
"    min-width: 30px;      /* Establece el ancho m\303\255nimo del bot\303\263n */\n"
"    max-width: 30px;      /* Establece el ancho m\303\241ximo del bot\303\263n */\n"
"    min-height: 30px;     /* Establece la altura m\303\255nima del bot\303\263n */\n"
"    max-height: 30px;     /* Establece la altura m\303\241xima del bot\303\263n */\n"
"    border: 2px solid black;  /* Crea un borde s\303\263lido negro de 2 p\303\255xeles */\n"
"    background-color: #6A6A6A;  /* Establece el color de fondo a #6A6A6A */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #555555;  /* Color ligeramente m\303\241s oscuro cuando se presiona */\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #C0C0C0; /* Color cuando se pasa el mouse */\n"
"}"));
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName("splitter");
        splitter->setGeometry(QRect(10, 10, 271, 401));
        splitter->setStyleSheet(QString::fromUtf8("QSplitter {\n"
"    background-color: rgba(20, 20, 20, 0.95);\n"
"}\n"
"\n"
"QSplitter::handle {\n"
"    background-color: rgba(40, 40, 40, 0.95);\n"
"    border: 1px solid rgba(255, 255, 255, 0.1);\n"
"    width: 4px;\n"
"}\n"
"\n"
"QSplitter::handle:hover {\n"
"    background-color: rgba(100, 149, 237, 0.4); \n"
"}\n"
"\n"
"QSplitter::handle:pressed {\n"
"    background-color: rgba(100, 149, 237, 0.6);\n"
"}"));
        splitter->setOrientation(Qt::Orientation::Vertical);
        treeView = new QTreeView(splitter);
        treeView->setObjectName("treeView");
        treeView->setFont(font2);
        treeView->setContextMenuPolicy(Qt::ContextMenuPolicy::DefaultContextMenu);
        treeView->setStyleSheet(QString::fromUtf8("QTreeView {\n"
"    background-color: rgba(20, 20, 20, 0.95);\n"
"    border: 1px solid rgba(255, 255, 255, 0.1);\n"
"    color: #D0D0D0;\n"
"    selection-background-color: rgba(100, 149, 237, 0.3);\n"
"    selection-color: #FFFFFF;\n"
"}\n"
"\n"
"QTreeView::item {\n"
"    padding: 4px;\n"
"    border: none;\n"
"}\n"
"\n"
"QTreeView::item:hover {\n"
"    background-color: rgba(100, 149, 237, 0.2);\n"
"}\n"
"\n"
"QTreeView::item:selected {\n"
"    background-color: rgba(100, 149, 237, 0.3);\n"
"    color: #FFFFFF;\n"
"}\n"
"\n"
"QTreeView::branch {\n"
"    background-color: transparent;\n"
"}\n"
"\n"
"QTreeView::branch:has-children:!has-siblings:closed,\n"
"QTreeView::branch:closed:has-children:has-siblings {\n"
"    image: url(:/icons/branch-closed.png);\n"
"}\n"
"\n"
"QTreeView::branch:open:has-children:!has-siblings,\n"
"QTreeView::branch:open:has-children:has-siblings {\n"
"    image: url(:/icons/branch-open.png);\n"
"}\n"
"\n"
"QTreeView::branch:selected {\n"
"    background-color: rgba(100, 149, 237, 0.3"
                        ");\n"
"}\n"
"\n"
"/* Estilo para la barra de desplazamiento */\n"
"QTreeView QScrollBar:vertical {\n"
"    background: rgba(20, 20, 20, 0.95);\n"
"    width: 8px;\n"
"    margin: 0px;\n"
"}\n"
"\n"
"QTreeView QScrollBar::handle:vertical {\n"
"    background: rgba(100, 149, 237, 0.3);\n"
"    min-height: 20px;\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QTreeView QScrollBar::handle:vertical:hover {\n"
"    background: rgba(100, 149, 237, 0.5);\n"
"}\n"
"\n"
"QTreeView QScrollBar::add-line:vertical,\n"
"QTreeView QScrollBar::sub-line:vertical {\n"
"    height: 0px;\n"
"}\n"
"\n"
"QTreeView QScrollBar::add-page:vertical,\n"
"QTreeView QScrollBar::sub-page:vertical {\n"
"    background: none;\n"
"}\n"
"\n"
"/* Estilo para el header */\n"
"QHeaderView::section {\n"
"    background-color: rgba(30, 30, 30, 0.95);\n"
"    color: #D0D0D0;\n"
"    padding: 4px;\n"
"    border: 1px solid rgba(255, 255, 255, 0.1);\n"
"}\n"
"\n"
"QHeaderView::section:hover {\n"
"    background-color: rgba(100, 149, 237, 0.2);\n"
"}"));
        treeView->setAnimated(true);
        treeView->setHeaderHidden(false);
        splitter->addWidget(treeView);
        playlistWidget = new QListWidget(splitter);
        playlistWidget->setObjectName("playlistWidget");
        playlistWidget->setFont(font1);
        playlistWidget->setStyleSheet(QString::fromUtf8("QListWidget {\n"
"    background-color: rgba(20, 20, 20, 0.95);\n"
"    border: 1px solid rgba(255, 255, 255, 0.1);\n"
"    color: #D0D0D0;\n"
"}\n"
"\n"
"QListWidget::item {\n"
"    padding: 4px;\n"
"    border: none;\n"
"}\n"
"\n"
"QListWidget::item:hover {\n"
"    background-color: rgba(100, 149, 237, 0.2);\n"
"}\n"
"\n"
"QListWidget::item:selected {\n"
"    background-color: rgba(100, 149, 237, 0.3);\n"
"    color: #FFFFFF;\n"
"}\n"
"\n"
"QListWidget::item:selected:active {\n"
"    background-color: rgba(100, 149, 237, 0.4);\n"
"}\n"
"\n"
"/* Estilo para la barra de desplazamiento vertical */\n"
"QListWidget QScrollBar:vertical {\n"
"    background: rgba(20, 20, 20, 0.95);\n"
"    width: 8px;\n"
"    margin: 0px;\n"
"}\n"
"\n"
"QListWidget QScrollBar::handle:vertical {\n"
"    background: rgba(100, 149, 237, 0.3);\n"
"    min-height: 20px;\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QListWidget QScrollBar::handle:vertical:hover {\n"
"    background: rgba(100, 149, 237, 0.5);\n"
"}\n"
"\n"
"QListWidget QScro"
                        "llBar::add-line:vertical,\n"
"QListWidget QScrollBar::sub-line:vertical {\n"
"    height: 0px;\n"
"}\n"
"\n"
"QListWidget QScrollBar::add-page:vertical,\n"
"QListWidget QScrollBar::sub-page:vertical {\n"
"    background: none;\n"
"}\n"
"\n"
"/* Estilo para la barra de desplazamiento horizontal */\n"
"QListWidget QScrollBar:horizontal {\n"
"    background: rgba(20, 20, 20, 0.95);\n"
"    height: 8px;\n"
"    margin: 0px;\n"
"}\n"
"\n"
"QListWidget QScrollBar::handle:horizontal {\n"
"    background: rgba(100, 149, 237, 0.3);\n"
"    min-width: 20px;\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QListWidget QScrollBar::handle:horizontal:hover {\n"
"    background: rgba(100, 149, 237, 0.5);\n"
"}\n"
"\n"
"QListWidget QScrollBar::add-line:horizontal,\n"
"QListWidget QScrollBar::sub-line:horizontal {\n"
"    width: 0px;\n"
"}\n"
"\n"
"QListWidget QScrollBar::add-page:horizontal,\n"
"QListWidget QScrollBar::sub-page:horizontal {\n"
"    background: none;\n"
"}\n"
"\n"
"/* Estilo para el \303\255tem que se est\303\241 re"
                        "produciendo actualmente */\n"
"QListWidget::item:selected:!active {\n"
"    background-color: rgba(100, 149, 237, 0.3);\n"
"    color: #FFFFFF;\n"
"    font-weight: bold;\n"
"    border-left: 2px solid rgba(100, 149, 237, 0.8);\n"
"}"));
        splitter->addWidget(playlistWidget);
        btnShuffle = new QPushButton(centralwidget);
        btnShuffle->setObjectName("btnShuffle");
        btnShuffle->setGeometry(QRect(340, 436, 34, 34));
        btnShuffle->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-radius: 15px;  /* Hace que los bordes del bot\303\263n sean redondeados */\n"
"    min-width: 30px;      /* Establece el ancho m\303\255nimo del bot\303\263n */\n"
"    max-width: 30px;      /* Establece el ancho m\303\241ximo del bot\303\263n */\n"
"    min-height: 30px;     /* Establece la altura m\303\255nima del bot\303\263n */\n"
"    max-height: 30px;     /* Establece la altura m\303\241xima del bot\303\263n */\n"
"    border: 2px solid black;  /* Crea un borde s\303\263lido negro de 2 p\303\255xeles */\n"
"    background-color: #6A6A6A;  /* Establece el color de fondo a #6A6A6A */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #555555;  /* Color ligeramente m\303\241s oscuro cuando se presiona */\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #C0C0C0; /* Color cuando se pasa el mouse */\n"
"}"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1024, 28));
        menubar->setFont(font1);
        menuOPen = new QMenu(menubar);
        menuOPen->setObjectName("menuOPen");
        menuOPen->setFont(font1);
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuOPen->menuAction());
        menuOPen->addAction(actionOpen_File);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpen_File->setText(QCoreApplication::translate("MainWindow", "Open Folder", nullptr));
        btnStop->setText(QString());
        btnNext->setText(QString());
        btnPrev->setText(QString());
        fileName->setText(QCoreApplication::translate("MainWindow", "Choose a folder to start", nullptr));
        currentTime->setText(QCoreApplication::translate("MainWindow", "##:##", nullptr));
        totalTime->setText(QCoreApplication::translate("MainWindow", "##:##", nullptr));
        btnMute->setText(QString());
        btnPlayPause->setText(QString());
        groupBox->setTitle(QString());
        btnPlaybackMode->setText(QString());
        btnShuffle->setText(QString());
        menuOPen->setTitle(QCoreApplication::translate("MainWindow", "Open", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
