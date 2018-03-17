/****************************************************************************
** Meta object code from reading C++ file 'QGSIGameBuilder.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GameBuilder/QGSIGameBuilder.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QGSIGameBuilder.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QGSIGameBuilder_t {
    QByteArrayData data[15];
    char stringdata0[194];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QGSIGameBuilder_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QGSIGameBuilder_t qt_meta_stringdata_QGSIGameBuilder = {
    {
QT_MOC_LITERAL(0, 0, 15), // "QGSIGameBuilder"
QT_MOC_LITERAL(1, 16, 13), // "downloadStart"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 12), // "DownloadInfo"
QT_MOC_LITERAL(4, 44, 12), // "downloadInfo"
QT_MOC_LITERAL(5, 57, 16), // "downloadProgress"
QT_MOC_LITERAL(6, 74, 13), // "bytesReceived"
QT_MOC_LITERAL(7, 88, 10), // "bytesTotal"
QT_MOC_LITERAL(8, 99, 16), // "downloadFinished"
QT_MOC_LITERAL(9, 116, 15), // "downloadtimeout"
QT_MOC_LITERAL(10, 132, 13), // "downloadError"
QT_MOC_LITERAL(11, 146, 20), // "QGSDownloader::Error"
QT_MOC_LITERAL(12, 167, 5), // "error"
QT_MOC_LITERAL(13, 173, 8), // "finished"
QT_MOC_LITERAL(14, 182, 11) // "errorString"

    },
    "QGSIGameBuilder\0downloadStart\0\0"
    "DownloadInfo\0downloadInfo\0downloadProgress\0"
    "bytesReceived\0bytesTotal\0downloadFinished\0"
    "downloadtimeout\0downloadError\0"
    "QGSDownloader::Error\0error\0finished\0"
    "errorString"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QGSIGameBuilder[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       5,    3,   52,    2, 0x06 /* Public */,
       8,    1,   59,    2, 0x06 /* Public */,
       9,    1,   62,    2, 0x06 /* Public */,
      10,    2,   65,    2, 0x06 /* Public */,
      13,    0,   70,    2, 0x06 /* Public */,
      12,    1,   71,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong, 0x80000000 | 3,    6,    7,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 11, 0x80000000 | 3,   12,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   14,

       0        // eod
};

void QGSIGameBuilder::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QGSIGameBuilder *_t = static_cast<QGSIGameBuilder *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->downloadStart((*reinterpret_cast< const DownloadInfo(*)>(_a[1]))); break;
        case 1: _t->downloadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< const DownloadInfo(*)>(_a[3]))); break;
        case 2: _t->downloadFinished((*reinterpret_cast< const DownloadInfo(*)>(_a[1]))); break;
        case 3: _t->downloadtimeout((*reinterpret_cast< const DownloadInfo(*)>(_a[1]))); break;
        case 4: _t->downloadError((*reinterpret_cast< QGSDownloader::Error(*)>(_a[1])),(*reinterpret_cast< const DownloadInfo(*)>(_a[2]))); break;
        case 5: _t->finished(); break;
        case 6: _t->error((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (QGSIGameBuilder::*_t)(const DownloadInfo );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSIGameBuilder::downloadStart)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QGSIGameBuilder::*_t)(qint64 , qint64 , const DownloadInfo );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSIGameBuilder::downloadProgress)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (QGSIGameBuilder::*_t)(const DownloadInfo );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSIGameBuilder::downloadFinished)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (QGSIGameBuilder::*_t)(const DownloadInfo );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSIGameBuilder::downloadtimeout)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (QGSIGameBuilder::*_t)(QGSDownloader::Error , const DownloadInfo );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSIGameBuilder::downloadError)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (QGSIGameBuilder::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSIGameBuilder::finished)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (QGSIGameBuilder::*_t)(const QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSIGameBuilder::error)) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject QGSIGameBuilder::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QGSIGameBuilder.data,
      qt_meta_data_QGSIGameBuilder,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QGSIGameBuilder::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QGSIGameBuilder::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QGSIGameBuilder.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QGSIGameBuilder::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void QGSIGameBuilder::downloadStart(const DownloadInfo _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QGSIGameBuilder::downloadProgress(qint64 _t1, qint64 _t2, const DownloadInfo _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QGSIGameBuilder::downloadFinished(const DownloadInfo _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QGSIGameBuilder::downloadtimeout(const DownloadInfo _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QGSIGameBuilder::downloadError(QGSDownloader::Error _t1, const DownloadInfo _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QGSIGameBuilder::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void QGSIGameBuilder::error(const QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
