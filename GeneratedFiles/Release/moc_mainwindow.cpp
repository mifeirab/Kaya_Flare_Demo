/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[17];
    char stringdata0[413];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 13), // "dir_path_save"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 34), // "on_scan_grabber_pushButton_cl..."
QT_MOC_LITERAL(4, 61, 37), // "on_connect_grabber_pushButton..."
QT_MOC_LITERAL(5, 99, 38), // "on_connect_camera_pushButton_..."
QT_MOC_LITERAL(6, 138, 34), // "on_start_camera_pushButton_cl..."
QT_MOC_LITERAL(7, 173, 33), // "on_stop_camera_pushButton_cli..."
QT_MOC_LITERAL(8, 207, 34), // "on_allocate_Ram_pushButton_cl..."
QT_MOC_LITERAL(9, 242, 32), // "on_save_image_pushButton_clicked"
QT_MOC_LITERAL(10, 275, 34), // "on_show_image_pushButton_2_cl..."
QT_MOC_LITERAL(11, 310, 26), // "on_dict_pushButton_clicked"
QT_MOC_LITERAL(12, 337, 9), // "show_path"
QT_MOC_LITERAL(13, 347, 6), // "String"
QT_MOC_LITERAL(14, 354, 3), // "str"
QT_MOC_LITERAL(15, 358, 31), // "on_Del_Cache_pushButton_clicked"
QT_MOC_LITERAL(16, 390, 22) // "on_radioButton_clicked"

    },
    "MainWindow\0dir_path_save\0\0"
    "on_scan_grabber_pushButton_clicked\0"
    "on_connect_grabber_pushButton_clicked\0"
    "on_connect_camera_pushButton_2_clicked\0"
    "on_start_camera_pushButton_clicked\0"
    "on_stop_camera_pushButton_clicked\0"
    "on_allocate_Ram_pushButton_clicked\0"
    "on_save_image_pushButton_clicked\0"
    "on_show_image_pushButton_2_clicked\0"
    "on_dict_pushButton_clicked\0show_path\0"
    "String\0str\0on_Del_Cache_pushButton_clicked\0"
    "on_radioButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   82,    2, 0x08 /* Private */,
       4,    0,   83,    2, 0x08 /* Private */,
       5,    0,   84,    2, 0x08 /* Private */,
       6,    0,   85,    2, 0x08 /* Private */,
       7,    0,   86,    2, 0x08 /* Private */,
       8,    0,   87,    2, 0x08 /* Private */,
       9,    0,   88,    2, 0x08 /* Private */,
      10,    0,   89,    2, 0x08 /* Private */,
      11,    0,   90,    2, 0x08 /* Private */,
      12,    1,   91,    2, 0x08 /* Private */,
      15,    0,   94,    2, 0x08 /* Private */,
      16,    0,   95,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dir_path_save((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->on_scan_grabber_pushButton_clicked(); break;
        case 2: _t->on_connect_grabber_pushButton_clicked(); break;
        case 3: _t->on_connect_camera_pushButton_2_clicked(); break;
        case 4: _t->on_start_camera_pushButton_clicked(); break;
        case 5: _t->on_stop_camera_pushButton_clicked(); break;
        case 6: _t->on_allocate_Ram_pushButton_clicked(); break;
        case 7: _t->on_save_image_pushButton_clicked(); break;
        case 8: _t->on_show_image_pushButton_2_clicked(); break;
        case 9: _t->on_dict_pushButton_clicked(); break;
        case 10: _t->show_path((*reinterpret_cast< String(*)>(_a[1]))); break;
        case 11: _t->on_Del_Cache_pushButton_clicked(); break;
        case 12: _t->on_radioButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (MainWindow::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::dir_path_save)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::dir_path_save(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
