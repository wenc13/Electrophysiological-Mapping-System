/****************************************************************************
** Meta object code from reading C++ file 'SBMEStereoProjectorControlPanelDlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SBMEStereoProjectorControlPanelDlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SBMEStereoProjectorControlPanelDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SBMEStereoProjectorControlPanelDlg_t {
    QByteArrayData data[11];
    char stringdata[207];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_SBMEStereoProjectorControlPanelDlg_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_SBMEStereoProjectorControlPanelDlg_t qt_meta_stringdata_SBMEStereoProjectorControlPanelDlg = {
    {
QT_MOC_LITERAL(0, 0, 34),
QT_MOC_LITERAL(1, 35, 28),
QT_MOC_LITERAL(2, 64, 0),
QT_MOC_LITERAL(3, 65, 2),
QT_MOC_LITERAL(4, 68, 28),
QT_MOC_LITERAL(5, 97, 2),
QT_MOC_LITERAL(6, 100, 19),
QT_MOC_LITERAL(7, 120, 4),
QT_MOC_LITERAL(8, 125, 29),
QT_MOC_LITERAL(9, 155, 29),
QT_MOC_LITERAL(10, 185, 20)
    },
    "SBMEStereoProjectorControlPanelDlg\0"
    "m_signalFocusDistanceChanged\0\0FD\0"
    "m_signalPupilDistanceChanged\0PD\0"
    "m_signalFovyChanged\0Fovy\0"
    "m_slotPopChangedFocusDistance\0"
    "m_slotPopChangedPupilDistance\0"
    "m_slotPopChangedFovy\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SBMEStereoProjectorControlPanelDlg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06,
       4,    1,   47,    2, 0x06,
       6,    1,   50,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       8,    1,   53,    2, 0x08,
       9,    1,   56,    2, 0x08,
      10,    1,   59,    2, 0x08,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    7,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    7,

       0        // eod
};

void SBMEStereoProjectorControlPanelDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SBMEStereoProjectorControlPanelDlg *_t = static_cast<SBMEStereoProjectorControlPanelDlg *>(_o);
        switch (_id) {
        case 0: _t->m_signalFocusDistanceChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->m_signalPupilDistanceChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->m_signalFovyChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->m_slotPopChangedFocusDistance((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->m_slotPopChangedPupilDistance((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->m_slotPopChangedFovy((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SBMEStereoProjectorControlPanelDlg::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SBMEStereoProjectorControlPanelDlg::m_signalFocusDistanceChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (SBMEStereoProjectorControlPanelDlg::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SBMEStereoProjectorControlPanelDlg::m_signalPupilDistanceChanged)) {
                *result = 1;
            }
        }
        {
            typedef void (SBMEStereoProjectorControlPanelDlg::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SBMEStereoProjectorControlPanelDlg::m_signalFovyChanged)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject SBMEStereoProjectorControlPanelDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SBMEStereoProjectorControlPanelDlg.data,
      qt_meta_data_SBMEStereoProjectorControlPanelDlg,  qt_static_metacall, 0, 0}
};


const QMetaObject *SBMEStereoProjectorControlPanelDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SBMEStereoProjectorControlPanelDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SBMEStereoProjectorControlPanelDlg.stringdata))
        return static_cast<void*>(const_cast< SBMEStereoProjectorControlPanelDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int SBMEStereoProjectorControlPanelDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void SBMEStereoProjectorControlPanelDlg::m_signalFocusDistanceChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SBMEStereoProjectorControlPanelDlg::m_signalPupilDistanceChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SBMEStereoProjectorControlPanelDlg::m_signalFovyChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
