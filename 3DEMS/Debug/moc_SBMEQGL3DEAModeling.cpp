/****************************************************************************
** Meta object code from reading C++ file 'SBMEQGL3DEAModeling.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SBMEQGL3DEAModeling.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SBMEQGL3DEAModeling.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SBMEQGL3DEAModeling_t {
    QByteArrayData data[22];
    char stringdata[375];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_SBMEQGL3DEAModeling_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_SBMEQGL3DEAModeling_t qt_meta_stringdata_SBMEQGL3DEAModeling = {
    {
QT_MOC_LITERAL(0, 0, 19),
QT_MOC_LITERAL(1, 20, 28),
QT_MOC_LITERAL(2, 49, 0),
QT_MOC_LITERAL(3, 50, 7),
QT_MOC_LITERAL(4, 58, 7),
QT_MOC_LITERAL(5, 66, 9),
QT_MOC_LITERAL(6, 76, 9),
QT_MOC_LITERAL(7, 86, 9),
QT_MOC_LITERAL(8, 96, 23),
QT_MOC_LITERAL(9, 120, 25),
QT_MOC_LITERAL(10, 146, 18),
QT_MOC_LITERAL(11, 165, 30),
QT_MOC_LITERAL(12, 196, 2),
QT_MOC_LITERAL(13, 199, 30),
QT_MOC_LITERAL(14, 230, 2),
QT_MOC_LITERAL(15, 233, 21),
QT_MOC_LITERAL(16, 255, 4),
QT_MOC_LITERAL(17, 260, 25),
QT_MOC_LITERAL(18, 286, 29),
QT_MOC_LITERAL(19, 316, 10),
QT_MOC_LITERAL(20, 327, 31),
QT_MOC_LITERAL(21, 359, 14)
    },
    "SBMEQGL3DEAModeling\0m_signalRefreshLeftRightView\0"
    "\0GLfloat\0scaling\0rotationX\0rotationY\0"
    "rotationZ\0m_signalNewPointSampled\0"
    "m_slotRefreshWithMainView\0m_slotRefreshModel\0"
    "m_slotRefreshWithFocalDistance\0FD\0"
    "m_slotRefreshWithPupilDistance\0PD\0"
    "m_slotRefreshWithFovy\0Fovy\0"
    "m_slotRefreshWithColorBar\0"
    "m_slotRefreshWithColoringFlag\0iscoloring\0"
    "m_slotRefreshWithColoringRadius\0"
    "ColoringRadius\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SBMEQGL3DEAModeling[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   64,    2, 0x06,
       8,    0,   73,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       9,    4,   74,    2, 0x08,
      10,    0,   83,    2, 0x08,
      11,    1,   84,    2, 0x08,
      13,    1,   87,    2, 0x08,
      15,    1,   90,    2, 0x08,
      17,    0,   93,    2, 0x08,
      18,    1,   94,    2, 0x08,
      20,    1,   97,    2, 0x08,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3,    4,    5,    6,    7,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3,    4,    5,    6,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Void, QMetaType::Float,   21,

       0        // eod
};

void SBMEQGL3DEAModeling::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SBMEQGL3DEAModeling *_t = static_cast<SBMEQGL3DEAModeling *>(_o);
        switch (_id) {
        case 0: _t->m_signalRefreshLeftRightView((*reinterpret_cast< GLfloat(*)>(_a[1])),(*reinterpret_cast< GLfloat(*)>(_a[2])),(*reinterpret_cast< GLfloat(*)>(_a[3])),(*reinterpret_cast< GLfloat(*)>(_a[4]))); break;
        case 1: _t->m_signalNewPointSampled(); break;
        case 2: _t->m_slotRefreshWithMainView((*reinterpret_cast< GLfloat(*)>(_a[1])),(*reinterpret_cast< GLfloat(*)>(_a[2])),(*reinterpret_cast< GLfloat(*)>(_a[3])),(*reinterpret_cast< GLfloat(*)>(_a[4]))); break;
        case 3: _t->m_slotRefreshModel(); break;
        case 4: _t->m_slotRefreshWithFocalDistance((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->m_slotRefreshWithPupilDistance((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->m_slotRefreshWithFovy((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->m_slotRefreshWithColorBar(); break;
        case 8: _t->m_slotRefreshWithColoringFlag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->m_slotRefreshWithColoringRadius((*reinterpret_cast< float(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SBMEQGL3DEAModeling::*_t)(GLfloat , GLfloat , GLfloat , GLfloat );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SBMEQGL3DEAModeling::m_signalRefreshLeftRightView)) {
                *result = 0;
            }
        }
        {
            typedef void (SBMEQGL3DEAModeling::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SBMEQGL3DEAModeling::m_signalNewPointSampled)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject SBMEQGL3DEAModeling::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_SBMEQGL3DEAModeling.data,
      qt_meta_data_SBMEQGL3DEAModeling,  qt_static_metacall, 0, 0}
};


const QMetaObject *SBMEQGL3DEAModeling::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SBMEQGL3DEAModeling::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SBMEQGL3DEAModeling.stringdata))
        return static_cast<void*>(const_cast< SBMEQGL3DEAModeling*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int SBMEQGL3DEAModeling::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void SBMEQGL3DEAModeling::m_signalRefreshLeftRightView(GLfloat _t1, GLfloat _t2, GLfloat _t3, GLfloat _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SBMEQGL3DEAModeling::m_signalNewPointSampled()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
