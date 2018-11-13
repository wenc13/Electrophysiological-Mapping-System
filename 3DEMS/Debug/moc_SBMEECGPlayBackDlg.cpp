/****************************************************************************
** Meta object code from reading C++ file 'SBMEECGPlayBackDlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SBMEECGPlayBackDlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SBMEECGPlayBackDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SBMEECGPlayBackDlg_t {
    QByteArrayData data[8];
    char stringdata[131];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_SBMEECGPlayBackDlg_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_SBMEECGPlayBackDlg_t qt_meta_stringdata_SBMEECGPlayBackDlg = {
    {
QT_MOC_LITERAL(0, 0, 18),
QT_MOC_LITERAL(1, 19, 20),
QT_MOC_LITERAL(2, 40, 0),
QT_MOC_LITERAL(3, 41, 4),
QT_MOC_LITERAL(4, 46, 23),
QT_MOC_LITERAL(5, 70, 21),
QT_MOC_LITERAL(6, 92, 16),
QT_MOC_LITERAL(7, 109, 20)
    },
    "SBMEECGPlayBackDlg\0m_signalPlayBackTime\0"
    "\0int*\0m_slotPlayBackTimeBegin\0"
    "m_slotPlayBackTimeEnd\0m_slotPlayBackOK\0"
    "m_slotPlayBackCancel\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SBMEECGPlayBackDlg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       4,    1,   42,    2, 0x08,
       5,    1,   45,    2, 0x08,
       6,    0,   48,    2, 0x08,
       7,    0,   49,    2, 0x08,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SBMEECGPlayBackDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SBMEECGPlayBackDlg *_t = static_cast<SBMEECGPlayBackDlg *>(_o);
        switch (_id) {
        case 0: _t->m_signalPlayBackTime((*reinterpret_cast< int*(*)>(_a[1]))); break;
        case 1: _t->m_slotPlayBackTimeBegin((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->m_slotPlayBackTimeEnd((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->m_slotPlayBackOK(); break;
        case 4: _t->m_slotPlayBackCancel(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SBMEECGPlayBackDlg::*_t)(int * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SBMEECGPlayBackDlg::m_signalPlayBackTime)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject SBMEECGPlayBackDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SBMEECGPlayBackDlg.data,
      qt_meta_data_SBMEECGPlayBackDlg,  qt_static_metacall, 0, 0}
};


const QMetaObject *SBMEECGPlayBackDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SBMEECGPlayBackDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SBMEECGPlayBackDlg.stringdata))
        return static_cast<void*>(const_cast< SBMEECGPlayBackDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int SBMEECGPlayBackDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void SBMEECGPlayBackDlg::m_signalPlayBackTime(int * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
