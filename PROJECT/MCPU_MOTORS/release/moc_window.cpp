/****************************************************************************
** Meta object code from reading C++ file 'window.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../SOURCE/WINDOW/window.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_debugWindow_t {
    const uint offsetsAndSize[34];
    char stringdata0[189];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_debugWindow_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_debugWindow_t qt_meta_stringdata_debugWindow = {
    {
QT_MOC_LITERAL(0, 11), // "debugWindow"
QT_MOC_LITERAL(12, 12), // "onInitButton"
QT_MOC_LITERAL(25, 0), // ""
QT_MOC_LITERAL(26, 10), // "updateData"
QT_MOC_LITERAL(37, 12), // "updateStatus"
QT_MOC_LITERAL(50, 18), // "onDebugClearButton"
QT_MOC_LITERAL(69, 16), // "onLogClearButton"
QT_MOC_LITERAL(86, 10), // "assignData"
QT_MOC_LITERAL(97, 9), // "rxFromCan"
QT_MOC_LITERAL(107, 5), // "canId"
QT_MOC_LITERAL(113, 4), // "data"
QT_MOC_LITERAL(118, 7), // "txToCan"
QT_MOC_LITERAL(126, 10), // "timerEvent"
QT_MOC_LITERAL(137, 12), // "QTimerEvent*"
QT_MOC_LITERAL(150, 2), // "ev"
QT_MOC_LITERAL(153, 30), // "on_logEnableCheck_stateChanged"
QT_MOC_LITERAL(184, 4) // "arg1"

    },
    "debugWindow\0onInitButton\0\0updateData\0"
    "updateStatus\0onDebugClearButton\0"
    "onLogClearButton\0assignData\0rxFromCan\0"
    "canId\0data\0txToCan\0timerEvent\0"
    "QTimerEvent*\0ev\0on_logEnableCheck_stateChanged\0"
    "arg1"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_debugWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   74,    2, 0x0a,    1 /* Public */,
       3,    0,   75,    2, 0x0a,    2 /* Public */,
       4,    0,   76,    2, 0x0a,    3 /* Public */,
       5,    0,   77,    2, 0x0a,    4 /* Public */,
       6,    0,   78,    2, 0x0a,    5 /* Public */,
       7,    0,   79,    2, 0x0a,    6 /* Public */,
       8,    2,   80,    2, 0x0a,    7 /* Public */,
      11,    2,   85,    2, 0x0a,   10 /* Public */,
      12,    1,   90,    2, 0x0a,   13 /* Public */,
      15,    1,   93,    2, 0x08,   15 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UShort, QMetaType::QByteArray,    9,   10,
    QMetaType::Void, QMetaType::UShort, QMetaType::QByteArray,    9,   10,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, QMetaType::Int,   16,

       0        // eod
};

void debugWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<debugWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onInitButton(); break;
        case 1: _t->updateData(); break;
        case 2: _t->updateStatus(); break;
        case 3: _t->onDebugClearButton(); break;
        case 4: _t->onLogClearButton(); break;
        case 5: _t->assignData(); break;
        case 6: _t->rxFromCan((*reinterpret_cast< ushort(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 7: _t->txToCan((*reinterpret_cast< ushort(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 8: _t->timerEvent((*reinterpret_cast< QTimerEvent*(*)>(_a[1]))); break;
        case 9: _t->on_logEnableCheck_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject debugWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_debugWindow.offsetsAndSize,
    qt_meta_data_debugWindow,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_debugWindow_t
, QtPrivate::TypeAndForceComplete<debugWindow, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<ushort, std::false_type>, QtPrivate::TypeAndForceComplete<QByteArray, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<ushort, std::false_type>, QtPrivate::TypeAndForceComplete<QByteArray, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QTimerEvent *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>


>,
    nullptr
} };


const QMetaObject *debugWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *debugWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_debugWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int debugWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
