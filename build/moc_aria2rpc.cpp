/****************************************************************************
** Meta object code from reading C++ file 'aria2rpc.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../aria2rpc.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'aria2rpc.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Aria2RPC_t {
    QByteArrayData data[9];
    char stringdata0[52];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Aria2RPC_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Aria2RPC_t qt_meta_stringdata_Aria2RPC = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Aria2RPC"
QT_MOC_LITERAL(1, 9, 6), // "addUri"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 3), // "uri"
QT_MOC_LITERAL(4, 21, 2), // "id"
QT_MOC_LITERAL(5, 24, 6), // "remove"
QT_MOC_LITERAL(6, 31, 3), // "gid"
QT_MOC_LITERAL(7, 35, 5), // "pause"
QT_MOC_LITERAL(8, 41, 10) // "tellStatus"

    },
    "Aria2RPC\0addUri\0\0uri\0id\0remove\0gid\0"
    "pause\0tellStatus"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Aria2RPC[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x0a /* Public */,
       5,    1,   39,    2, 0x0a /* Public */,
       7,    1,   42,    2, 0x0a /* Public */,
       8,    1,   45,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,

       0        // eod
};

void Aria2RPC::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Aria2RPC *_t = static_cast<Aria2RPC *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addUri((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->remove((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->pause((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->tellStatus((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Aria2RPC::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Aria2RPC.data,
      qt_meta_data_Aria2RPC,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Aria2RPC::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Aria2RPC::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Aria2RPC.stringdata0))
        return static_cast<void*>(const_cast< Aria2RPC*>(this));
    return QObject::qt_metacast(_clname);
}

int Aria2RPC::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
