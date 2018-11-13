/****************************************************************************
** Meta object code from reading C++ file 'SBMENDIRomFileDlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SBMENDIRomFileDlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SBMENDIRomFileDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SBMENDIRomFileDlg_t {
    QByteArrayData data[9];
    char stringdata[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_SBMENDIRomFileDlg_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_SBMENDIRomFileDlg_t qt_meta_stringdata_SBMENDIRomFileDlg = {
    {
QT_MOC_LITERAL(0, 0, 17),
QT_MOC_LITERAL(1, 18, 22),
QT_MOC_LITERAL(2, 41, 0),
QT_MOC_LITERAL(3, 42, 18),
QT_MOC_LITERAL(4, 61, 3),
QT_MOC_LITERAL(5, 65, 6),
QT_MOC_LITERAL(6, 72, 14),
QT_MOC_LITERAL(7, 87, 12),
QT_MOC_LITERAL(8, 100, 13)
    },
    "SBMENDIRomFileDlg\0m_signalRomFileChanged\0"
    "\0m_slotOnClickTable\0row\0column\0"
    "m_slotOnBrowse\0m_slotOnSave\0m_slotOnClose\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SBMENDIRomFileDlg[] = {

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
       1,    0,   39,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       3,    2,   40,    2, 0x08,
       6,    0,   45,    2, 0x08,
       7,    0,   46,    2, 0x08,
       8,    0,   47,    2, 0x08,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SBMENDIRomFileDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SBMENDIRomFileDlg *_t = static_cast<SBMENDIRomFileDlg *>(_o);
        switch (_id) {
        case 0: _t->m_signalRomFileChanged(); break;
        case 1: _t->m_slotOnClickTable((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->m_slotOnBrowse(); break;
        case 3: _t->m_slotOnSave(); break;
        case 4: _t->m_slotOnClose(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SBMENDIRomFileDlg::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SBMENDIRomFileDlg::m_signalRomFileChanged)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject SBMENDIRomFileDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SBMENDIRomFileDlg.data,
      qt_meta_data_SBMENDIRomFileDlg,  qt_static_metacall, 0, 0}
};


const QMetaObject *SBMENDIRomFileDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SBMENDIRomFileDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SBMENDIRomFileDlg.stringdata))
        return static_cast<void*>(const_cast< SBMENDIRomFileDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int SBMENDIRomFileDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void SBMENDIRomFileDlg::m_signalRomFileChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
