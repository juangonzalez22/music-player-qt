/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../music-player-qt/mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtGui/qscreen.h>
#include <QtNetwork/QSslPreSharedKeyAuthenticator>
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "durationChanged",
    "",
    "duration",
    "positionChanged",
    "position",
    "on_btnMute_clicked",
    "on_actionOpen_File_triggered",
    "on_btnPrev_clicked",
    "on_btnNext_clicked",
    "on_btnStop_clicked",
    "on_sldrVolume_valueChanged",
    "value",
    "on_btnPlayPause_clicked",
    "on_sldrSeek_sliderMoved",
    "on_sldrSeek_sliderReleased",
    "on_treeView_clicked",
    "QModelIndex",
    "index",
    "on_playlistWidget_doubleClicked",
    "setupMarquee",
    "text",
    "startMarquee",
    "stopMarquee",
    "focusOutEvent",
    "QFocusEvent*",
    "event",
    "focusInEvent",
    "playPlaceholderVideo",
    "updateMarqueePosition",
    "onMediaStatusChanged",
    "QMediaPlayer::MediaStatus",
    "status",
    "on_btnPlaybackMode_clicked",
    "on_btnShuffle_clicked"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  152,    2, 0x08,    1 /* Private */,
       4,    1,  155,    2, 0x08,    3 /* Private */,
       6,    0,  158,    2, 0x08,    5 /* Private */,
       7,    0,  159,    2, 0x08,    6 /* Private */,
       8,    0,  160,    2, 0x08,    7 /* Private */,
       9,    0,  161,    2, 0x08,    8 /* Private */,
      10,    0,  162,    2, 0x08,    9 /* Private */,
      11,    1,  163,    2, 0x08,   10 /* Private */,
      13,    0,  166,    2, 0x08,   12 /* Private */,
      14,    1,  167,    2, 0x08,   13 /* Private */,
      15,    0,  170,    2, 0x08,   15 /* Private */,
      16,    1,  171,    2, 0x08,   16 /* Private */,
      19,    1,  174,    2, 0x08,   18 /* Private */,
      20,    1,  177,    2, 0x08,   20 /* Private */,
      22,    0,  180,    2, 0x08,   22 /* Private */,
      23,    0,  181,    2, 0x08,   23 /* Private */,
      24,    1,  182,    2, 0x08,   24 /* Private */,
      27,    1,  185,    2, 0x08,   26 /* Private */,
      28,    0,  188,    2, 0x08,   28 /* Private */,
      29,    0,  189,    2, 0x08,   29 /* Private */,
      30,    1,  190,    2, 0x08,   30 /* Private */,
      33,    0,  193,    2, 0x08,   32 /* Private */,
      34,    0,  194,    2, 0x08,   33 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::LongLong,    3,
    QMetaType::Void, QMetaType::LongLong,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 25,   26,
    QMetaType::Void, 0x80000000 | 25,   26,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 31,   32,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'durationChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qint64, std::false_type>,
        // method 'positionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qint64, std::false_type>,
        // method 'on_btnMute_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionOpen_File_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnPrev_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnNext_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnStop_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_sldrVolume_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_btnPlayPause_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_sldrSeek_sliderMoved'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_sldrSeek_sliderReleased'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_treeView_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>,
        // method 'on_playlistWidget_doubleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>,
        // method 'setupMarquee'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'startMarquee'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'stopMarquee'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'focusOutEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QFocusEvent *, std::false_type>,
        // method 'focusInEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QFocusEvent *, std::false_type>,
        // method 'playPlaceholderVideo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateMarqueePosition'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onMediaStatusChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMediaPlayer::MediaStatus, std::false_type>,
        // method 'on_btnPlaybackMode_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnShuffle_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->durationChanged((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1]))); break;
        case 1: _t->positionChanged((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1]))); break;
        case 2: _t->on_btnMute_clicked(); break;
        case 3: _t->on_actionOpen_File_triggered(); break;
        case 4: _t->on_btnPrev_clicked(); break;
        case 5: _t->on_btnNext_clicked(); break;
        case 6: _t->on_btnStop_clicked(); break;
        case 7: _t->on_sldrVolume_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 8: _t->on_btnPlayPause_clicked(); break;
        case 9: _t->on_sldrSeek_sliderMoved((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 10: _t->on_sldrSeek_sliderReleased(); break;
        case 11: _t->on_treeView_clicked((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 12: _t->on_playlistWidget_doubleClicked((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 13: _t->setupMarquee((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 14: _t->startMarquee(); break;
        case 15: _t->stopMarquee(); break;
        case 16: _t->focusOutEvent((*reinterpret_cast< std::add_pointer_t<QFocusEvent*>>(_a[1]))); break;
        case 17: _t->focusInEvent((*reinterpret_cast< std::add_pointer_t<QFocusEvent*>>(_a[1]))); break;
        case 18: _t->playPlaceholderVideo(); break;
        case 19: _t->updateMarqueePosition(); break;
        case 20: _t->onMediaStatusChanged((*reinterpret_cast< std::add_pointer_t<QMediaPlayer::MediaStatus>>(_a[1]))); break;
        case 21: _t->on_btnPlaybackMode_clicked(); break;
        case 22: _t->on_btnShuffle_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 23;
    }
    return _id;
}
QT_WARNING_POP
