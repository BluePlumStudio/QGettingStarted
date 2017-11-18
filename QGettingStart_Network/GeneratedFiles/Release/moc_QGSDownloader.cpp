/****************************************************************************
** Meta object code from reading C++ file 'QGSDownloader.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QGSDownloader.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QGSDownloader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QGSDownloader_t {
    QByteArrayData data[8];
    char stringdata0[94];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QGSDownloader_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QGSDownloader_t qt_meta_stringdata_QGSDownloader = {
    {
QT_MOC_LITERAL(0, 0, 13), // "QGSDownloader"
QT_MOC_LITERAL(1, 14, 16), // "downloadFinished"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 5), // "error"
QT_MOC_LITERAL(4, 38, 10), // "ReplyError"
QT_MOC_LITERAL(5, 49, 10), // "replyError"
QT_MOC_LITERAL(6, 60, 16), // "downloadProgress"
QT_MOC_LITERAL(7, 77, 16) // "DownloadProgress"

    },
    "QGSDownloader\0downloadFinished\0\0error\0"
    "ReplyError\0replyError\0downloadProgress\0"
    "DownloadProgress"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QGSDownloader[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    1,   30,    2, 0x06 /* Public */,
       6,    1,   33,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 7,    6,

       0        // eod
};

void QGSDownloader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QGSDownloader *_t = static_cast<QGSDownloader *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->downloadFinished(); break;
        case 1: _t->error((*reinterpret_cast< ReplyError(*)>(_a[1]))); break;
        case 2: _t->downloadProgress((*reinterpret_cast< DownloadProgress(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QGSDownloader::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QGSDownloader::downloadFinished)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QGSDownloader::*_t)(ReplyError );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QGSDownloader::error)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (QGSDownloader::*_t)(DownloadProgress );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QGSDownloader::downloadProgress)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject QGSDownloader::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QGSDownloader.data,
      qt_meta_data_QGSDownloader,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QGSDownloader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QGSDownloader::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QGSDownloader.stringdata0))
        return static_cast<void*>(const_cast< QGSDownloader*>(this));
    return QObject::qt_metacast(_clname);
}

int QGSDownloader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void QGSDownloader::downloadFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void QGSDownloader::error(ReplyError _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QGSDownloader::downloadProgress(DownloadProgress _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
