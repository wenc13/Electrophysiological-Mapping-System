/****************************************************************************
** Meta object code from reading C++ file 'SBMEColorMappingBar.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SBMEColorMappingBar.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SBMEColorMappingBar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SBMEColorMappingBar_t {
    QByteArrayData data[3];
    char stringdata[43];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_SBMEColorMappingBar_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_SBMEColorMappingBar_t qt_meta_stringdata_SBMEColorMappingBar = {
    {
QT_MOC_LITERAL(0, 0, 19),
QT_MOC_LITERAL(1, 20, 20),
QT_MOC_LITERAL(2, 41, 0)
    },
    "SBMEColorMappingBar\0m_signalValueChanged\0"
    "\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SBMEColorMappingBar[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06,

 // signals: parameters
    QMetaType::Void,

       0        // eod
};

void SBMEColorMappingBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SBMEColorMappingBar *_t = static_cast<SBMEColorMappingBar *>(_o);
        switch (_id) {
        case 0: _t->m_signalValueChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SBMEColorMappingBar::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SBMEColorMappingBar::m_signalValueChanged)) {
                *result = 0;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject SBMEColorMappingBar::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SBMEColorMappingBar.data,
      qt_meta_data_SBMEColorMappingBar,  qt_static_metacall, 0, 0}
};


const QMetaObject *SBMEColorMappingBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SBMEColorMappingBar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SBMEColorMappingBar.stringdata))
        return static_cast<void*>(const_cast< SBMEColorMappingBar*>(this));
    return QWidget::qt_metacast(_clname);
}

int SBMEColorMappingBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void SBMEColorMappingBar::m_signalValueChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
