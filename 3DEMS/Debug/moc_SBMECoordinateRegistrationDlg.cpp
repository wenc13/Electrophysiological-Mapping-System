/****************************************************************************
** Meta object code from reading C++ file 'SBMECoordinateRegistrationDlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SBMECoordinateRegistrationDlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SBMECoordinateRegistrationDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SBMECoordinateRegistrationDlg_t {
    QByteArrayData data[7];
    char stringdata[135];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_SBMECoordinateRegistrationDlg_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_SBMECoordinateRegistrationDlg_t qt_meta_stringdata_SBMECoordinateRegistrationDlg = {
    {
QT_MOC_LITERAL(0, 0, 29),
QT_MOC_LITERAL(1, 30, 21),
QT_MOC_LITERAL(2, 52, 0),
QT_MOC_LITERAL(3, 53, 23),
QT_MOC_LITERAL(4, 77, 17),
QT_MOC_LITERAL(5, 95, 19),
QT_MOC_LITERAL(6, 115, 18)
    },
    "SBMECoordinateRegistrationDlg\0"
    "m_signalToGetNDIPoint\0\0m_signalToGetModelPoint\0"
    "m_slotGetNDIPoint\0m_slotGetModelPoint\0"
    "m_slotSartRegister\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SBMECoordinateRegistrationDlg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06,
       3,    0,   40,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       4,    0,   41,    2, 0x08,
       5,    0,   42,    2, 0x08,
       6,    0,   43,    2, 0x08,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SBMECoordinateRegistrationDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SBMECoordinateRegistrationDlg *_t = static_cast<SBMECoordinateRegistrationDlg *>(_o);
        switch (_id) {
        case 0: _t->m_signalToGetNDIPoint(); break;
        case 1: _t->m_signalToGetModelPoint(); break;
        case 2: _t->m_slotGetNDIPoint(); break;
        case 3: _t->m_slotGetModelPoint(); break;
        case 4: _t->m_slotSartRegister(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SBMECoordinateRegistrationDlg::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SBMECoordinateRegistrationDlg::m_signalToGetNDIPoint)) {
                *result = 0;
            }
        }
        {
            typedef void (SBMECoordinateRegistrationDlg::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SBMECoordinateRegistrationDlg::m_signalToGetModelPoint)) {
                *result = 1;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject SBMECoordinateRegistrationDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SBMECoordinateRegistrationDlg.data,
      qt_meta_data_SBMECoordinateRegistrationDlg,  qt_static_metacall, 0, 0}
};


const QMetaObject *SBMECoordinateRegistrationDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SBMECoordinateRegistrationDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SBMECoordinateRegistrationDlg.stringdata))
        return static_cast<void*>(const_cast< SBMECoordinateRegistrationDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int SBMECoordinateRegistrationDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void SBMECoordinateRegistrationDlg::m_signalToGetNDIPoint()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void SBMECoordinateRegistrationDlg::m_signalToGetModelPoint()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
