/****************************************************************************
** Meta object code from reading C++ file 'SBMEECGControlPanelDlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SBMEECGControlPanelDlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SBMEECGControlPanelDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SBMEECGControlPanelDlg_t {
    QByteArrayData data[10];
    char stringdata[157];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_SBMEECGControlPanelDlg_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_SBMEECGControlPanelDlg_t qt_meta_stringdata_SBMEECGControlPanelDlg = {
    {
QT_MOC_LITERAL(0, 0, 22),
QT_MOC_LITERAL(1, 23, 28),
QT_MOC_LITERAL(2, 52, 0),
QT_MOC_LITERAL(3, 53, 6),
QT_MOC_LITERAL(4, 60, 4),
QT_MOC_LITERAL(5, 65, 8),
QT_MOC_LITERAL(6, 74, 28),
QT_MOC_LITERAL(7, 103, 5),
QT_MOC_LITERAL(8, 109, 24),
QT_MOC_LITERAL(9, 134, 21)
    },
    "SBMEECGControlPanelDlg\0"
    "m_signalSelectedECGtoDispaly\0\0ECGnum\0"
    "int*\0ECGIndex\0m_slotCheckBoxesStateChanged\0"
    "state\0m_slotSelectedECGChanged\0"
    "m_slotOKButtonEnabled\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SBMEECGControlPanelDlg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       6,    1,   39,    2, 0x08,
       8,    0,   42,    2, 0x08,
       9,    1,   43,    2, 0x08,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,

       0        // eod
};

void SBMEECGControlPanelDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SBMEECGControlPanelDlg *_t = static_cast<SBMEECGControlPanelDlg *>(_o);
        switch (_id) {
        case 0: _t->m_signalSelectedECGtoDispaly((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int*(*)>(_a[2]))); break;
        case 1: _t->m_slotCheckBoxesStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->m_slotSelectedECGChanged(); break;
        case 3: _t->m_slotOKButtonEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SBMEECGControlPanelDlg::*_t)(int , int * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SBMEECGControlPanelDlg::m_signalSelectedECGtoDispaly)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject SBMEECGControlPanelDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SBMEECGControlPanelDlg.data,
      qt_meta_data_SBMEECGControlPanelDlg,  qt_static_metacall, 0, 0}
};


const QMetaObject *SBMEECGControlPanelDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SBMEECGControlPanelDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SBMEECGControlPanelDlg.stringdata))
        return static_cast<void*>(const_cast< SBMEECGControlPanelDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int SBMEECGControlPanelDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void SBMEECGControlPanelDlg::m_signalSelectedECGtoDispaly(int _t1, int * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
