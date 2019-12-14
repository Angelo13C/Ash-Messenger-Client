/****************************************************************************
** Meta object code from reading C++ file 'translatormanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/Other/translatormanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'translatormanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TranslatorManager_t {
    QByteArrayData data[8];
    char stringdata0[75];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TranslatorManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TranslatorManager_t qt_meta_stringdata_TranslatorManager = {
    {
QT_MOC_LITERAL(0, 0, 17), // "TranslatorManager"
QT_MOC_LITERAL(1, 18, 11), // "setLanguage"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 8), // "Location"
QT_MOC_LITERAL(4, 40, 8), // "location"
QT_MOC_LITERAL(5, 49, 4), // "AUTO"
QT_MOC_LITERAL(6, 54, 14), // "UNITED_KINGDOM"
QT_MOC_LITERAL(7, 69, 5) // "ITALY"

    },
    "TranslatorManager\0setLanguage\0\0Location\0"
    "location\0AUTO\0UNITED_KINGDOM\0ITALY"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TranslatorManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       1,   22, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // enums: name, alias, flags, count, data
       3,    3, 0x2,    3,   27,

 // enum data: key, value
       5, uint(TranslatorManager::Location::AUTO),
       6, uint(TranslatorManager::Location::UNITED_KINGDOM),
       7, uint(TranslatorManager::Location::ITALY),

       0        // eod
};

void TranslatorManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TranslatorManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setLanguage((*reinterpret_cast< const Location(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TranslatorManager::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_TranslatorManager.data,
    qt_meta_data_TranslatorManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TranslatorManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TranslatorManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TranslatorManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int TranslatorManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
