/****************************************************************************
** Meta object code from reading C++ file 'SBMENDIProgramOptionDlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SBMENDIProgramOptionDlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SBMENDIProgramOptionDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SBMENDIProgramOptionDlg_t {
    QByteArrayData data[7];
    char stringdata[114];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_SBMENDIProgramOptionDlg_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_SBMENDIProgramOptionDlg_t qt_meta_stringdata_SBMENDIProgramOptionDlg = {
    {
QT_MOC_LITERAL(0, 0, 23),
QT_MOC_LITERAL(1, 24, 17),
QT_MOC_LITERAL(2, 42, 0),
QT_MOC_LITERAL(3, 43, 14),
QT_MOC_LITERAL(4, 58, 19),
QT_MOC_LITERAL(5, 78, 21),
QT_MOC_LITERAL(6, 100, 12)
    },
    "SBMENDIProgramOptionDlg\0m_slotOnLogToFile\0"
    "\0m_slotOnBrowse\0m_slotOnBeepOnError\0"
    "m_slotOnBeepOnWarning\0m_slotAccept\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SBMENDIProgramOptionDlg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08,
       3,    0,   40,    2, 0x08,
       4,    0,   41,    2, 0x08,
       5,    0,   42,    2, 0x08,
       6,    0,   43,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SBMENDIProgramOptionDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SBMENDIProgramOptionDlg *_t = static_cast<SBMENDIProgramOptionDlg *>(_o);
        switch (_id) {
        case 0: _t->m_slotOnLogToFile(); break;
        case 1: _t->m_slotOnBrowse(); break;
        case 2: _t->m_slotOnBeepOnError(); break;
        case 3: _t->m_slotOnBeepOnWarning(); break;
        case 4: _t->m_slotAccept(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject SBMENDIProgramOptionDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SBMENDIProgramOptionDlg.data,
      qt_meta_data_SBMENDIProgramOptionDlg,  qt_static_metacall, 0, 0}
};


const QMetaObject *SBMENDIProgramOptionDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SBMENDIProgramOptionDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SBMENDIProgramOptionDlg.stringdata))
        return static_cast<void*>(const_cast< SBMENDIProgramOptionDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int SBMENDIProgramOptionDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
