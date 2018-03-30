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
    QByteArrayData data[22];
    char stringdata0[230];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QGSDownloader_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QGSDownloader_t qt_meta_stringdata_QGSDownloader = {
    {
QT_MOC_LITERAL(0, 0, 13), // "QGSDownloader"
QT_MOC_LITERAL(1, 14, 8), // "finished"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 14), // "QGSDownloader*"
QT_MOC_LITERAL(4, 39, 10), // "downloader"
QT_MOC_LITERAL(5, 50, 6), // "stoped"
QT_MOC_LITERAL(6, 57, 8), // "canceled"
QT_MOC_LITERAL(7, 66, 16), // "downloadProgress"
QT_MOC_LITERAL(8, 83, 18), // "bytesNewlyReceived"
QT_MOC_LITERAL(9, 102, 13), // "bytesReceived"
QT_MOC_LITERAL(10, 116, 10), // "bytesTotal"
QT_MOC_LITERAL(11, 127, 13), // "downloadError"
QT_MOC_LITERAL(12, 141, 15), // "QGSNetworkError"
QT_MOC_LITERAL(13, 157, 5), // "error"
QT_MOC_LITERAL(14, 163, 9), // "sslErrors"
QT_MOC_LITERAL(15, 173, 16), // "QList<QSslError>"
QT_MOC_LITERAL(16, 190, 6), // "errors"
QT_MOC_LITERAL(17, 197, 10), // "redirected"
QT_MOC_LITERAL(18, 208, 3), // "url"
QT_MOC_LITERAL(19, 212, 5), // "start"
QT_MOC_LITERAL(20, 218, 4), // "stop"
QT_MOC_LITERAL(21, 223, 6) // "cancel"

    },
    "QGSDownloader\0finished\0\0QGSDownloader*\0"
    "downloader\0stoped\0canceled\0downloadProgress\0"
    "bytesNewlyReceived\0bytesReceived\0"
    "bytesTotal\0downloadError\0QGSNetworkError\0"
    "error\0sslErrors\0QList<QSslError>\0"
    "errors\0redirected\0url\0start\0stop\0"
    "cancel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QGSDownloader[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       5,    1,   67,    2, 0x06 /* Public */,
       6,    1,   70,    2, 0x06 /* Public */,
       7,    4,   73,    2, 0x06 /* Public */,
      11,    2,   82,    2, 0x06 /* Public */,
      14,    2,   87,    2, 0x06 /* Public */,
      17,    2,   92,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      19,    0,   97,    2, 0x0a /* Public */,
      20,    0,   98,    2, 0x0a /* Public */,
      21,    0,   99,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong, QMetaType::LongLong, 0x80000000 | 3,    8,    9,   10,    4,
    QMetaType::Void, 0x80000000 | 12, 0x80000000 | 3,   13,    4,
    QMetaType::Void, 0x80000000 | 15, 0x80000000 | 3,   16,    4,
    QMetaType::Void, QMetaType::QUrl, 0x80000000 | 3,   18,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QGSDownloader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QGSDownloader *_t = static_cast<QGSDownloader *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->finished((*reinterpret_cast< QGSDownloader*(*)>(_a[1]))); break;
        case 1: _t->stoped((*reinterpret_cast< QGSDownloader*(*)>(_a[1]))); break;
        case 2: _t->canceled((*reinterpret_cast< QGSDownloader*(*)>(_a[1]))); break;
        case 3: _t->downloadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< qint64(*)>(_a[3])),(*reinterpret_cast< QGSDownloader*(*)>(_a[4]))); break;
        case 4: _t->downloadError((*reinterpret_cast< QGSNetworkError(*)>(_a[1])),(*reinterpret_cast< QGSDownloader*(*)>(_a[2]))); break;
        case 5: _t->sslErrors((*reinterpret_cast< const QList<QSslError>(*)>(_a[1])),(*reinterpret_cast< QGSDownloader*(*)>(_a[2]))); break;
        case 6: _t->redirected((*reinterpret_cast< const QUrl(*)>(_a[1])),(*reinterpret_cast< QGSDownloader*(*)>(_a[2]))); break;
        case 7: _t->start(); break;
        case 8: _t->stop(); break;
        case 9: _t->cancel(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSDownloader* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSDownloader* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSDownloader* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 3:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSDownloader* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSDownloader* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSDownloader* >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QSslError> >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSDownloader* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (QGSDownloader::*_t)(QGSDownloader * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSDownloader::finished)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QGSDownloader::*_t)(QGSDownloader * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSDownloader::stoped)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (QGSDownloader::*_t)(QGSDownloader * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSDownloader::canceled)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (QGSDownloader::*_t)(qint64 , qint64 , qint64 , QGSDownloader * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSDownloader::downloadProgress)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (QGSDownloader::*_t)(QGSNetworkError , QGSDownloader * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSDownloader::downloadError)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (QGSDownloader::*_t)(const QList<QSslError> & , QGSDownloader * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSDownloader::sslErrors)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (QGSDownloader::*_t)(const QUrl & , QGSDownloader * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSDownloader::redirected)) {
                *result = 6;
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
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void QGSDownloader::finished(QGSDownloader * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QGSDownloader::stoped(QGSDownloader * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QGSDownloader::canceled(QGSDownloader * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QGSDownloader::downloadProgress(qint64 _t1, qint64 _t2, qint64 _t3, QGSDownloader * _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QGSDownloader::downloadError(QGSNetworkError _t1, QGSDownloader * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QGSDownloader::sslErrors(const QList<QSslError> & _t1, QGSDownloader * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QGSDownloader::redirected(const QUrl & _t1, QGSDownloader * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
