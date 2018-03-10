/****************************************************************************
** Meta object code from reading C++ file 'QGSDownloader.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Download/QGSDownloader.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QGSDownloader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QGSDownloader_t {
    QByteArrayData data[12];
    char stringdata0[120];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QGSDownloader_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QGSDownloader_t qt_meta_stringdata_QGSDownloader = {
    {
QT_MOC_LITERAL(0, 0, 13), // "QGSDownloader"
QT_MOC_LITERAL(1, 14, 16), // "downloadProgress"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 13), // "bytesReceived"
QT_MOC_LITERAL(4, 46, 10), // "bytesTotal"
QT_MOC_LITERAL(5, 57, 8), // "finished"
QT_MOC_LITERAL(6, 66, 5), // "error"
QT_MOC_LITERAL(7, 72, 5), // "Error"
QT_MOC_LITERAL(8, 78, 9), // "sslErrors"
QT_MOC_LITERAL(9, 88, 16), // "QList<QSslError>"
QT_MOC_LITERAL(10, 105, 6), // "errors"
QT_MOC_LITERAL(11, 112, 7) // "timeout"

    },
    "QGSDownloader\0downloadProgress\0\0"
    "bytesReceived\0bytesTotal\0finished\0"
    "error\0Error\0sslErrors\0QList<QSslError>\0"
    "errors\0timeout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QGSDownloader[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06 /* Public */,
       5,    0,   44,    2, 0x06 /* Public */,
       6,    1,   45,    2, 0x06 /* Public */,
       8,    1,   48,    2, 0x06 /* Public */,
      11,    0,   51,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    6,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void,

       0        // eod
};

void QGSDownloader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QGSDownloader *_t = static_cast<QGSDownloader *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->downloadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 1: _t->finished(); break;
        case 2: _t->error((*reinterpret_cast< Error(*)>(_a[1]))); break;
        case 3: _t->sslErrors((*reinterpret_cast< const QList<QSslError>(*)>(_a[1]))); break;
        case 4: _t->timeout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QSslError> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (QGSDownloader::*_t)(qint64 , qint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSDownloader::downloadProgress)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QGSDownloader::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSDownloader::finished)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (QGSDownloader::*_t)(Error );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSDownloader::error)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (QGSDownloader::*_t)(const QList<QSslError> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSDownloader::sslErrors)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (QGSDownloader::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSDownloader::timeout)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject QGSDownloader::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QGSDownloader.data,
      qt_meta_data_QGSDownloader,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QGSDownloader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QGSDownloader::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QGSDownloader.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QGSDownloader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void QGSDownloader::downloadProgress(qint64 _t1, qint64 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QGSDownloader::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void QGSDownloader::error(Error _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QGSDownloader::sslErrors(const QList<QSslError> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QGSDownloader::timeout()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
