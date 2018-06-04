/****************************************************************************
** Meta object code from reading C++ file 'autocell.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../projet_LO21/autocell.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'autocell.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AutoCellDim1_t {
    QByteArrayData data[15];
    char stringdata0[160];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AutoCellDim1_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AutoCellDim1_t qt_meta_stringdata_AutoCellDim1 = {
    {
QT_MOC_LITERAL(0, 0, 12), // "AutoCellDim1"
QT_MOC_LITERAL(1, 13, 22), // "synchronizeNumToNumBit"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 1), // "i"
QT_MOC_LITERAL(4, 39, 22), // "synchronizeNumBitToNum"
QT_MOC_LITERAL(5, 62, 14), // "cellActivation"
QT_MOC_LITERAL(6, 77, 5), // "index"
QT_MOC_LITERAL(7, 83, 5), // "simul"
QT_MOC_LITERAL(8, 89, 9), // "simul_pap"
QT_MOC_LITERAL(9, 99, 7), // "boucler"
QT_MOC_LITERAL(10, 107, 8), // "etat_rnd"
QT_MOC_LITERAL(11, 116, 8), // "symetric"
QT_MOC_LITERAL(12, 125, 10), // "export_xml"
QT_MOC_LITERAL(13, 136, 11), // "charger_xml"
QT_MOC_LITERAL(14, 148, 11) // "stop_thread"

    },
    "AutoCellDim1\0synchronizeNumToNumBit\0"
    "\0i\0synchronizeNumBitToNum\0cellActivation\0"
    "index\0simul\0simul_pap\0boucler\0etat_rnd\0"
    "symetric\0export_xml\0charger_xml\0"
    "stop_thread"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AutoCellDim1[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x08 /* Private */,
       4,    0,   72,    2, 0x08 /* Private */,
       5,    1,   73,    2, 0x08 /* Private */,
       7,    0,   76,    2, 0x08 /* Private */,
       8,    0,   77,    2, 0x08 /* Private */,
       9,    0,   78,    2, 0x08 /* Private */,
      10,    0,   79,    2, 0x08 /* Private */,
      11,    0,   80,    2, 0x08 /* Private */,
      12,    0,   81,    2, 0x08 /* Private */,
      13,    0,   82,    2, 0x08 /* Private */,
      14,    0,   83,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AutoCellDim1::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AutoCellDim1 *_t = static_cast<AutoCellDim1 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->synchronizeNumToNumBit((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->synchronizeNumBitToNum(); break;
        case 2: _t->cellActivation((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 3: _t->simul(); break;
        case 4: _t->simul_pap(); break;
        case 5: _t->boucler(); break;
        case 6: _t->etat_rnd(); break;
        case 7: _t->symetric(); break;
        case 8: _t->export_xml(); break;
        case 9: _t->charger_xml(); break;
        case 10: _t->stop_thread(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject AutoCellDim1::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AutoCellDim1.data,
      qt_meta_data_AutoCellDim1,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *AutoCellDim1::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AutoCellDim1::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AutoCellDim1.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int AutoCellDim1::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
struct qt_meta_stringdata_AutoCellDim2_t {
    QByteArrayData data[9];
    char stringdata0[80];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AutoCellDim2_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AutoCellDim2_t qt_meta_stringdata_AutoCellDim2 = {
    {
QT_MOC_LITERAL(0, 0, 12), // "AutoCellDim2"
QT_MOC_LITERAL(1, 13, 14), // "cellActivation"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 5), // "index"
QT_MOC_LITERAL(4, 35, 5), // "simul"
QT_MOC_LITERAL(5, 41, 9), // "simul_pap"
QT_MOC_LITERAL(6, 51, 7), // "boucler"
QT_MOC_LITERAL(7, 59, 8), // "etat_rnd"
QT_MOC_LITERAL(8, 68, 11) // "stop_thread"

    },
    "AutoCellDim2\0cellActivation\0\0index\0"
    "simul\0simul_pap\0boucler\0etat_rnd\0"
    "stop_thread"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AutoCellDim2[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x08 /* Private */,
       4,    0,   47,    2, 0x08 /* Private */,
       5,    0,   48,    2, 0x08 /* Private */,
       6,    0,   49,    2, 0x08 /* Private */,
       7,    0,   50,    2, 0x08 /* Private */,
       8,    0,   51,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QModelIndex,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AutoCellDim2::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AutoCellDim2 *_t = static_cast<AutoCellDim2 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->cellActivation((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 1: _t->simul(); break;
        case 2: _t->simul_pap(); break;
        case 3: _t->boucler(); break;
        case 4: _t->etat_rnd(); break;
        case 5: _t->stop_thread(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject AutoCellDim2::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AutoCellDim2.data,
      qt_meta_data_AutoCellDim2,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *AutoCellDim2::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AutoCellDim2::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AutoCellDim2.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int AutoCellDim2::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
