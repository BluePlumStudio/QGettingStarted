/****************************************************************************
** Meta object code from reading C++ file 'QGSIAccount.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../LaunchOptions/QGSIAccount.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QGSIAccount.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QGSIAccount_t {
    QByteArrayData data[8];
    char stringdata0[78];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QGSIAccount_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QGSIAccount_t qt_meta_stringdata_QGSIAccount = {
    {
QT_MOC_LITERAL(0, 0, 11), // "QGSIAccount"
QT_MOC_LITERAL(1, 12, 8), // "finished"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 11), // "QGSAuthInfo"
QT_MOC_LITERAL(4, 34, 8), // "authInfo"
QT_MOC_LITERAL(5, 43, 5), // "error"
QT_MOC_LITERAL(6, 49, 15), // "QGSNetworkError"
QT_MOC_LITERAL(7, 65, 12) // "networkError"

    },
    "QGSIAccount\0finished\0\0QGSAuthInfo\0"
    "authInfo\0error\0QGSNetworkError\0"
    "networkError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QGSIAccount[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,
       5,    1,   27,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void QGSIAccount::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QGSIAccount *_t = static_cast<QGSIAccount *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->finished((*reinterpret_cast< QGSAuthInfo(*)>(_a[1]))); break;
        case 1: _t->error((*reinterpret_cast< QGSNetworkError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSAuthInfo >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSNetworkError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (QGSIAccount::*_t)(QGSAuthInfo );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSIAccount::finished)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QGSIAccount::*_t)(QGSNetworkError );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSIAccount::error)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject QGSIAccount::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QGSIAccount.data,
      qt_meta_data_QGSIAccount,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QGSIAccount::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QGSIAccount::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QGSIAccount.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QGSIAccount::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void QGSIAccount::finished(QGSAuthInfo _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QGSIAccount::error(QGSNetworkError _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
