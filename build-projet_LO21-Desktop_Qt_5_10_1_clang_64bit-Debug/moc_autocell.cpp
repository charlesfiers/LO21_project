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
struct qt_meta_stringdata_AutoCell_t {
    QByteArrayData data[15];
    char stringdata0[153];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AutoCell_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AutoCell_t qt_meta_stringdata_AutoCell = {
    {
QT_MOC_LITERAL(0, 0, 8), // "AutoCell"
QT_MOC_LITERAL(1, 9, 22), // "synchronizeNumToNumBit"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 1), // "i"
QT_MOC_LITERAL(4, 35, 22), // "synchronizeNumBitToNum"
QT_MOC_LITERAL(5, 58, 14), // "cellActivation"
QT_MOC_LITERAL(6, 73, 5), // "index"
QT_MOC_LITERAL(7, 79, 5), // "simul"
QT_MOC_LITERAL(8, 85, 6), // "simul2"
QT_MOC_LITERAL(9, 92, 7), // "boucler"
QT_MOC_LITERAL(10, 100, 8), // "etat_rnd"
QT_MOC_LITERAL(11, 109, 8), // "symetric"
QT_MOC_LITERAL(12, 118, 10), // "export_xml"
QT_MOC_LITERAL(13, 129, 11), // "charger_xml"
QT_MOC_LITERAL(14, 141, 11) // "stop_thread"

    },
    "AutoCell\0synchronizeNumToNumBit\0\0i\0"
    "synchronizeNumBitToNum\0cellActivation\0"
    "index\0simul\0simul2\0boucler\0etat_rnd\0"
    "symetric\0export_xml\0charger_xml\0"
    "stop_thread"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AutoCell[] = {

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

void AutoCell::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AutoCell *_t = static_cast<AutoCell *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->synchronizeNumToNumBit((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->synchronizeNumBitToNum(); break;
        case 2: _t->cellActivation((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 3: _t->simul(); break;
        case 4: _t->simul2(); break;
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

QT_INIT_METAOBJECT const QMetaObject AutoCell::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AutoCell.data,
      qt_meta_data_AutoCell,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *AutoCell::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AutoCell::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AutoCell.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int AutoCell::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
