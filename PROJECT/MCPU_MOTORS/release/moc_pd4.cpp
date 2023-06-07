/****************************************************************************
** Meta object code from reading C++ file 'pd4.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../SOURCE/DRIVER/NANOTEC/pd4.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pd4.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_pd4Nanotec_t {
    const uint offsetsAndSize[68];
    char stringdata0[603];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_pd4Nanotec_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_pd4Nanotec_t qt_meta_stringdata_pd4Nanotec = {
    {
QT_MOC_LITERAL(0, 10), // "pd4Nanotec"
QT_MOC_LITERAL(11, 7), // "txToCan"
QT_MOC_LITERAL(19, 0), // ""
QT_MOC_LITERAL(20, 5), // "canId"
QT_MOC_LITERAL(26, 4), // "data"
QT_MOC_LITERAL(31, 31), // "CiA402_SwitchOnDisabledCallback"
QT_MOC_LITERAL(63, 30), // "CiA402_ReadyToSwitchOnCallback"
QT_MOC_LITERAL(94, 31), // "CiA402_OperationEnabledCallback"
QT_MOC_LITERAL(126, 20), // "CiA402_FaultCallback"
QT_MOC_LITERAL(147, 25), // "CiA402_SwitchedOnCallback"
QT_MOC_LITERAL(173, 25), // "initPd4ZeroSettingCommand"
QT_MOC_LITERAL(199, 18), // "pd4ZeroSettingLoop"
QT_MOC_LITERAL(218, 25), // "initPd4PositioningCommand"
QT_MOC_LITERAL(244, 18), // "pd4PositioningLoop"
QT_MOC_LITERAL(263, 13), // "statusHandler"
QT_MOC_LITERAL(277, 9), // "rxFromCan"
QT_MOC_LITERAL(287, 14), // "rxAsyncFromCan"
QT_MOC_LITERAL(302, 19), // "workflowUploadNanoj"
QT_MOC_LITERAL(322, 25), // "workflowInitializeHandler"
QT_MOC_LITERAL(348, 22), // "subRoutineUploadVector"
QT_MOC_LITERAL(371, 15), // "_OD_InitVector*"
QT_MOC_LITERAL(387, 7), // "pVector"
QT_MOC_LITERAL(395, 5), // "bool*"
QT_MOC_LITERAL(401, 7), // "changed"
QT_MOC_LITERAL(409, 8), // "uploadOk"
QT_MOC_LITERAL(418, 27), // "subRoutineWriteRegisterList"
QT_MOC_LITERAL(446, 25), // "QList<canOpenDictionary>*"
QT_MOC_LITERAL(472, 7), // "podList"
QT_MOC_LITERAL(480, 22), // "subDisableNanojProgram"
QT_MOC_LITERAL(503, 20), // "subReadDigitalInputs"
QT_MOC_LITERAL(524, 22), // "subReadPositionEncoder"
QT_MOC_LITERAL(547, 27), // "subActivateQuickStopCommand"
QT_MOC_LITERAL(575, 21), // "subNanojProgramUpload"
QT_MOC_LITERAL(597, 5) // "force"

    },
    "pd4Nanotec\0txToCan\0\0canId\0data\0"
    "CiA402_SwitchOnDisabledCallback\0"
    "CiA402_ReadyToSwitchOnCallback\0"
    "CiA402_OperationEnabledCallback\0"
    "CiA402_FaultCallback\0CiA402_SwitchedOnCallback\0"
    "initPd4ZeroSettingCommand\0pd4ZeroSettingLoop\0"
    "initPd4PositioningCommand\0pd4PositioningLoop\0"
    "statusHandler\0rxFromCan\0rxAsyncFromCan\0"
    "workflowUploadNanoj\0workflowInitializeHandler\0"
    "subRoutineUploadVector\0_OD_InitVector*\0"
    "pVector\0bool*\0changed\0uploadOk\0"
    "subRoutineWriteRegisterList\0"
    "QList<canOpenDictionary>*\0podList\0"
    "subDisableNanojProgram\0subReadDigitalInputs\0"
    "subReadPositionEncoder\0"
    "subActivateQuickStopCommand\0"
    "subNanojProgramUpload\0force"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_pd4Nanotec[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,  146,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    0,  151,    2, 0x08,    4 /* Private */,
       6,    0,  152,    2, 0x08,    5 /* Private */,
       7,    0,  153,    2, 0x08,    6 /* Private */,
       8,    0,  154,    2, 0x08,    7 /* Private */,
       9,    0,  155,    2, 0x08,    8 /* Private */,
      10,    0,  156,    2, 0x08,    9 /* Private */,
      11,    0,  157,    2, 0x08,   10 /* Private */,
      12,    0,  158,    2, 0x08,   11 /* Private */,
      13,    0,  159,    2, 0x08,   12 /* Private */,
      14,    0,  160,    2, 0x08,   13 /* Private */,
      15,    2,  161,    2, 0x08,   14 /* Private */,
      16,    2,  166,    2, 0x08,   17 /* Private */,
      17,    0,  171,    2, 0x08,   20 /* Private */,
      18,    0,  172,    2, 0x08,   21 /* Private */,
      19,    3,  173,    2, 0x08,   22 /* Private */,
      25,    2,  180,    2, 0x08,   26 /* Private */,
      28,    0,  185,    2, 0x08,   29 /* Private */,
      29,    0,  186,    2, 0x08,   30 /* Private */,
      30,    0,  187,    2, 0x08,   31 /* Private */,
      31,    0,  188,    2, 0x08,   32 /* Private */,
      32,    1,  189,    2, 0x08,   33 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::UShort, QMetaType::QByteArray,    3,    4,

 // slots: parameters
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UShort, QMetaType::QByteArray,    3,    4,
    QMetaType::Void, QMetaType::UShort, QMetaType::QByteArray,    3,    4,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UShort, 0x80000000 | 20, 0x80000000 | 22, 0x80000000 | 22,   21,   23,   24,
    QMetaType::UShort, 0x80000000 | 26, 0x80000000 | 22,   27,   24,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UShort, QMetaType::Bool,   33,

       0        // eod
};

void pd4Nanotec::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<pd4Nanotec *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->txToCan((*reinterpret_cast< ushort(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 1: { ushort _r = _t->CiA402_SwitchOnDisabledCallback();
            if (_a[0]) *reinterpret_cast< ushort*>(_a[0]) = std::move(_r); }  break;
        case 2: { ushort _r = _t->CiA402_ReadyToSwitchOnCallback();
            if (_a[0]) *reinterpret_cast< ushort*>(_a[0]) = std::move(_r); }  break;
        case 3: { ushort _r = _t->CiA402_OperationEnabledCallback();
            if (_a[0]) *reinterpret_cast< ushort*>(_a[0]) = std::move(_r); }  break;
        case 4: { ushort _r = _t->CiA402_FaultCallback();
            if (_a[0]) *reinterpret_cast< ushort*>(_a[0]) = std::move(_r); }  break;
        case 5: { ushort _r = _t->CiA402_SwitchedOnCallback();
            if (_a[0]) *reinterpret_cast< ushort*>(_a[0]) = std::move(_r); }  break;
        case 6: { ushort _r = _t->initPd4ZeroSettingCommand();
            if (_a[0]) *reinterpret_cast< ushort*>(_a[0]) = std::move(_r); }  break;
        case 7: { ushort _r = _t->pd4ZeroSettingLoop();
            if (_a[0]) *reinterpret_cast< ushort*>(_a[0]) = std::move(_r); }  break;
        case 8: { ushort _r = _t->initPd4PositioningCommand();
            if (_a[0]) *reinterpret_cast< ushort*>(_a[0]) = std::move(_r); }  break;
        case 9: { ushort _r = _t->pd4PositioningLoop();
            if (_a[0]) *reinterpret_cast< ushort*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->statusHandler(); break;
        case 11: _t->rxFromCan((*reinterpret_cast< ushort(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 12: _t->rxAsyncFromCan((*reinterpret_cast< ushort(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 13: { ushort _r = _t->workflowUploadNanoj();
            if (_a[0]) *reinterpret_cast< ushort*>(_a[0]) = std::move(_r); }  break;
        case 14: { ushort _r = _t->workflowInitializeHandler();
            if (_a[0]) *reinterpret_cast< ushort*>(_a[0]) = std::move(_r); }  break;
        case 15: { ushort _r = _t->subRoutineUploadVector((*reinterpret_cast< _OD_InitVector*(*)>(_a[1])),(*reinterpret_cast< bool*(*)>(_a[2])),(*reinterpret_cast< bool*(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< ushort*>(_a[0]) = std::move(_r); }  break;
        case 16: { ushort _r = _t->subRoutineWriteRegisterList((*reinterpret_cast< QList<canOpenDictionary>*(*)>(_a[1])),(*reinterpret_cast< bool*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< ushort*>(_a[0]) = std::move(_r); }  break;
        case 17: { ushort _r = _t->subDisableNanojProgram();
            if (_a[0]) *reinterpret_cast< ushort*>(_a[0]) = std::move(_r); }  break;
        case 18: { ushort _r = _t->subReadDigitalInputs();
            if (_a[0]) *reinterpret_cast< ushort*>(_a[0]) = std::move(_r); }  break;
        case 19: { ushort _r = _t->subReadPositionEncoder();
            if (_a[0]) *reinterpret_cast< ushort*>(_a[0]) = std::move(_r); }  break;
        case 20: { ushort _r = _t->subActivateQuickStopCommand();
            if (_a[0]) *reinterpret_cast< ushort*>(_a[0]) = std::move(_r); }  break;
        case 21: { ushort _r = _t->subNanojProgramUpload((*reinterpret_cast< bool(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< ushort*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (pd4Nanotec::*)(ushort , QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&pd4Nanotec::txToCan)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject pd4Nanotec::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_pd4Nanotec.offsetsAndSize,
    qt_meta_data_pd4Nanotec,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_pd4Nanotec_t
, QtPrivate::TypeAndForceComplete<pd4Nanotec, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<ushort, std::false_type>, QtPrivate::TypeAndForceComplete<QByteArray, std::false_type>
, QtPrivate::TypeAndForceComplete<ushort, std::false_type>, QtPrivate::TypeAndForceComplete<ushort, std::false_type>, QtPrivate::TypeAndForceComplete<ushort, std::false_type>, QtPrivate::TypeAndForceComplete<ushort, std::false_type>, QtPrivate::TypeAndForceComplete<ushort, std::false_type>, QtPrivate::TypeAndForceComplete<ushort, std::false_type>, QtPrivate::TypeAndForceComplete<ushort, std::false_type>, QtPrivate::TypeAndForceComplete<ushort, std::false_type>, QtPrivate::TypeAndForceComplete<ushort, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<ushort, std::false_type>, QtPrivate::TypeAndForceComplete<QByteArray, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<ushort, std::false_type>, QtPrivate::TypeAndForceComplete<QByteArray, std::false_type>, QtPrivate::TypeAndForceComplete<ushort, std::false_type>, QtPrivate::TypeAndForceComplete<ushort, std::false_type>, QtPrivate::TypeAndForceComplete<ushort, std::false_type>, QtPrivate::TypeAndForceComplete<_OD_InitVector *, std::false_type>, QtPrivate::TypeAndForceComplete<bool *, std::false_type>, QtPrivate::TypeAndForceComplete<bool *, std::false_type>, QtPrivate::TypeAndForceComplete<ushort, std::false_type>, QtPrivate::TypeAndForceComplete<QList<canOpenDictionary> *, std::false_type>, QtPrivate::TypeAndForceComplete<bool *, std::false_type>, QtPrivate::TypeAndForceComplete<ushort, std::false_type>, QtPrivate::TypeAndForceComplete<ushort, std::false_type>, QtPrivate::TypeAndForceComplete<ushort, std::false_type>, QtPrivate::TypeAndForceComplete<ushort, std::false_type>, QtPrivate::TypeAndForceComplete<ushort, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>


>,
    nullptr
} };


const QMetaObject *pd4Nanotec::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *pd4Nanotec::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_pd4Nanotec.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int pd4Nanotec::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 22)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 22;
    }
    return _id;
}

// SIGNAL 0
void pd4Nanotec::txToCan(ushort _t1, QByteArray _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
