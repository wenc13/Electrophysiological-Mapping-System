/****************************************************************************
** Meta object code from reading C++ file 'SBMEECGAcquisitionDlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SBMEECGAcquisitionDlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SBMEECGAcquisitionDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SBMEECGAcquisitionDlg_t {
    QByteArrayData data[20];
    char stringdata[437];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_SBMEECGAcquisitionDlg_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_SBMEECGAcquisitionDlg_t qt_meta_stringdata_SBMEECGAcquisitionDlg = {
    {
QT_MOC_LITERAL(0, 0, 21),
QT_MOC_LITERAL(1, 22, 24),
QT_MOC_LITERAL(2, 47, 0),
QT_MOC_LITERAL(3, 48, 20),
QT_MOC_LITERAL(4, 69, 33),
QT_MOC_LITERAL(5, 103, 26),
QT_MOC_LITERAL(6, 130, 25),
QT_MOC_LITERAL(7, 156, 19),
QT_MOC_LITERAL(8, 176, 14),
QT_MOC_LITERAL(9, 191, 18),
QT_MOC_LITERAL(10, 210, 4),
QT_MOC_LITERAL(11, 215, 27),
QT_MOC_LITERAL(12, 243, 31),
QT_MOC_LITERAL(13, 275, 25),
QT_MOC_LITERAL(14, 301, 23),
QT_MOC_LITERAL(15, 325, 23),
QT_MOC_LITERAL(16, 349, 23),
QT_MOC_LITERAL(17, 373, 23),
QT_MOC_LITERAL(18, 397, 16),
QT_MOC_LITERAL(19, 414, 21)
    },
    "SBMEECGAcquisitionDlg\0m_signalStartAcquisition\0"
    "\0m_signalStartProcess\0"
    "m_signalECGControlPanelDlgEnabled\0"
    "m_slotStartDataAcquisition\0"
    "m_slotStopDataAcquisition\0m_slotSetInputRange\0"
    "m_slotPlayBack\0m_slotPlayBackTime\0"
    "int*\0m_slotDialogCreateDeviceErr\0"
    "m_slotDialogInitializeDeviceErr\0"
    "m_slotDialogReadDeviceErr\0"
    "m_slotDialogOpenFileErr\0m_slotDialogDataFlowErr\0"
    "m_slotDialogDrawECGData\0m_slotDialogSelectedECG\0"
    "m_slotARTTimeout\0m_slotPlayBackTimeout\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SBMEECGAcquisitionDlg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x06,
       3,    0,  100,    2, 0x06,
       4,    1,  101,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       5,    0,  104,    2, 0x08,
       6,    0,  105,    2, 0x08,
       7,    1,  106,    2, 0x08,
       8,    0,  109,    2, 0x08,
       9,    1,  110,    2, 0x08,
      11,    0,  113,    2, 0x08,
      12,    0,  114,    2, 0x08,
      13,    0,  115,    2, 0x08,
      14,    0,  116,    2, 0x08,
      15,    0,  117,    2, 0x08,
      16,    0,  118,    2, 0x08,
      17,    2,  119,    2, 0x08,
      18,    0,  124,    2, 0x08,
      19,    0,  125,    2, 0x08,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 10,    2,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SBMEECGAcquisitionDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SBMEECGAcquisitionDlg *_t = static_cast<SBMEECGAcquisitionDlg *>(_o);
        switch (_id) {
        case 0: _t->m_signalStartAcquisition(); break;
        case 1: _t->m_signalStartProcess(); break;
        case 2: _t->m_signalECGControlPanelDlgEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->m_slotStartDataAcquisition(); break;
        case 4: _t->m_slotStopDataAcquisition(); break;
        case 5: _t->m_slotSetInputRange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->m_slotPlayBack(); break;
        case 7: _t->m_slotPlayBackTime((*reinterpret_cast< int*(*)>(_a[1]))); break;
        case 8: _t->m_slotDialogCreateDeviceErr(); break;
        case 9: _t->m_slotDialogInitializeDeviceErr(); break;
        case 10: _t->m_slotDialogReadDeviceErr(); break;
        case 11: _t->m_slotDialogOpenFileErr(); break;
        case 12: _t->m_slotDialogDataFlowErr(); break;
        case 13: _t->m_slotDialogDrawECGData(); break;
        case 14: _t->m_slotDialogSelectedECG((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int*(*)>(_a[2]))); break;
        case 15: _t->m_slotARTTimeout(); break;
        case 16: _t->m_slotPlayBackTimeout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SBMEECGAcquisitionDlg::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SBMEECGAcquisitionDlg::m_signalStartAcquisition)) {
                *result = 0;
            }
        }
        {
            typedef void (SBMEECGAcquisitionDlg::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SBMEECGAcquisitionDlg::m_signalStartProcess)) {
                *result = 1;
            }
        }
        {
            typedef void (SBMEECGAcquisitionDlg::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SBMEECGAcquisitionDlg::m_signalECGControlPanelDlgEnabled)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject SBMEECGAcquisitionDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SBMEECGAcquisitionDlg.data,
      qt_meta_data_SBMEECGAcquisitionDlg,  qt_static_metacall, 0, 0}
};


const QMetaObject *SBMEECGAcquisitionDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SBMEECGAcquisitionDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SBMEECGAcquisitionDlg.stringdata))
        return static_cast<void*>(const_cast< SBMEECGAcquisitionDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int SBMEECGAcquisitionDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void SBMEECGAcquisitionDlg::m_signalStartAcquisition()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void SBMEECGAcquisitionDlg::m_signalStartProcess()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void SBMEECGAcquisitionDlg::m_signalECGControlPanelDlgEnabled(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
