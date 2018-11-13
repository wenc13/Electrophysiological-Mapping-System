/****************************************************************************
** Meta object code from reading C++ file 'SBMEECGAcquisitionObj.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SBMEECGAcquisitionObj.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SBMEECGAcquisitionObj.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SBMEECGAcquisitionObj_t {
    QByteArrayData data[7];
    char stringdata[168];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_SBMEECGAcquisitionObj_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_SBMEECGAcquisitionObj_t qt_meta_stringdata_SBMEECGAcquisitionObj = {
    {
QT_MOC_LITERAL(0, 0, 21),
QT_MOC_LITERAL(1, 22, 29),
QT_MOC_LITERAL(2, 52, 0),
QT_MOC_LITERAL(3, 53, 33),
QT_MOC_LITERAL(4, 87, 27),
QT_MOC_LITERAL(5, 115, 25),
QT_MOC_LITERAL(6, 141, 25)
    },
    "SBMEECGAcquisitionObj\0"
    "m_signalAcqObjCreateDeviceErr\0\0"
    "m_signalAcqObjInitializeDeviceErr\0"
    "m_signalAcqObjReadDeviceErr\0"
    "m_signalAcqObjDataFlowErr\0"
    "m_slotECGAcquisitionStart\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SBMEECGAcquisitionObj[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06,
       3,    0,   40,    2, 0x06,
       4,    0,   41,    2, 0x06,
       5,    0,   42,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       6,    0,   43,    2, 0x08,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void SBMEECGAcquisitionObj::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SBMEECGAcquisitionObj *_t = static_cast<SBMEECGAcquisitionObj *>(_o);
        switch (_id) {
        case 0: _t->m_signalAcqObjCreateDeviceErr(); break;
        case 1: _t->m_signalAcqObjInitializeDeviceErr(); break;
        case 2: _t->m_signalAcqObjReadDeviceErr(); break;
        case 3: _t->m_signalAcqObjDataFlowErr(); break;
        case 4: _t->m_slotECGAcquisitionStart(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SBMEECGAcquisitionObj::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SBMEECGAcquisitionObj::m_signalAcqObjCreateDeviceErr)) {
                *result = 0;
            }
        }
        {
            typedef void (SBMEECGAcquisitionObj::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SBMEECGAcquisitionObj::m_signalAcqObjInitializeDeviceErr)) {
                *result = 1;
            }
        }
        {
            typedef void (SBMEECGAcquisitionObj::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SBMEECGAcquisitionObj::m_signalAcqObjReadDeviceErr)) {
                *result = 2;
            }
        }
        {
            typedef void (SBMEECGAcquisitionObj::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SBMEECGAcquisitionObj::m_signalAcqObjDataFlowErr)) {
                *result = 3;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject SBMEECGAcquisitionObj::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SBMEECGAcquisitionObj.data,
      qt_meta_data_SBMEECGAcquisitionObj,  qt_static_metacall, 0, 0}
};


const QMetaObject *SBMEECGAcquisitionObj::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SBMEECGAcquisitionObj::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SBMEECGAcquisitionObj.stringdata))
        return static_cast<void*>(const_cast< SBMEECGAcquisitionObj*>(this));
    return QObject::qt_metacast(_clname);
}

int SBMEECGAcquisitionObj::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void SBMEECGAcquisitionObj::m_signalAcqObjCreateDeviceErr()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void SBMEECGAcquisitionObj::m_signalAcqObjInitializeDeviceErr()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void SBMEECGAcquisitionObj::m_signalAcqObjReadDeviceErr()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void SBMEECGAcquisitionObj::m_signalAcqObjDataFlowErr()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
