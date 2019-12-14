/****************************************************************************
** Meta object code from reading C++ file 'authenticationsystem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/Messaging/authenticationsystem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'authenticationsystem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AuthenticationSystem_t {
    QByteArrayData data[11];
    char stringdata0[142];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AuthenticationSystem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AuthenticationSystem_t qt_meta_stringdata_AuthenticationSystem = {
    {
QT_MOC_LITERAL(0, 0, 20), // "AuthenticationSystem"
QT_MOC_LITERAL(1, 21, 10), // "loginEmail"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 5), // "email"
QT_MOC_LITERAL(4, 39, 8), // "password"
QT_MOC_LITERAL(5, 48, 12), // "qmlAreaLogin"
QT_MOC_LITERAL(6, 61, 13), // "registerEmail"
QT_MOC_LITERAL(7, 75, 15), // "qmlAreaRegister"
QT_MOC_LITERAL(8, 91, 20), // "AuthenticationErrors"
QT_MOC_LITERAL(9, 112, 8), // "NO_ERROR"
QT_MOC_LITERAL(10, 121, 20) // "WRONG_PASSWORD_EMAIL"

    },
    "AuthenticationSystem\0loginEmail\0\0email\0"
    "password\0qmlAreaLogin\0registerEmail\0"
    "qmlAreaRegister\0AuthenticationErrors\0"
    "NO_ERROR\0WRONG_PASSWORD_EMAIL"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AuthenticationSystem[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       1,   38, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    3,   24,    2, 0x02 /* Public */,
       6,    3,   31,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QObjectStar,    3,    4,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QObjectStar,    3,    4,    7,

 // enums: name, alias, flags, count, data
       8,    8, 0x2,    2,   43,

 // enum data: key, value
       9, uint(AuthenticationSystem::AuthenticationErrors::NO_ERROR),
      10, uint(AuthenticationSystem::AuthenticationErrors::WRONG_PASSWORD_EMAIL),

       0        // eod
};

void AuthenticationSystem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AuthenticationSystem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->loginEmail((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QObject*(*)>(_a[3]))); break;
        case 1: _t->registerEmail((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QObject*(*)>(_a[3]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject AuthenticationSystem::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_AuthenticationSystem.data,
    qt_meta_data_AuthenticationSystem,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AuthenticationSystem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AuthenticationSystem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AuthenticationSystem.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int AuthenticationSystem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
