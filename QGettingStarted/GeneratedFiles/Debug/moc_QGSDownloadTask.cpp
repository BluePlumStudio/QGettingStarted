/****************************************************************************
** Meta object code from reading C++ file 'QGSDownloadTask.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Download/QGSDownloadTask.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QGSDownloadTask.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QGSDownloadTask_t {
    QByteArrayData data[22];
    char stringdata0[273];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QGSDownloadTask_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QGSDownloadTask_t qt_meta_stringdata_QGSDownloadTask = {
    {
QT_MOC_LITERAL(0, 0, 15), // "QGSDownloadTask"
QT_MOC_LITERAL(1, 16, 16), // "downloadProgress"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 13), // "bytesReceived"
QT_MOC_LITERAL(4, 48, 10), // "bytesTotal"
QT_MOC_LITERAL(5, 59, 8), // "QGSTask*"
QT_MOC_LITERAL(6, 68, 4), // "task"
QT_MOC_LITERAL(7, 73, 13), // "downloadError"
QT_MOC_LITERAL(8, 87, 15), // "QGSNetworkError"
QT_MOC_LITERAL(9, 103, 5), // "error"
QT_MOC_LITERAL(10, 109, 9), // "sslErrors"
QT_MOC_LITERAL(11, 119, 16), // "QList<QSslError>"
QT_MOC_LITERAL(12, 136, 6), // "errors"
QT_MOC_LITERAL(13, 143, 12), // "slotFinished"
QT_MOC_LITERAL(14, 156, 14), // "QGSDownloader*"
QT_MOC_LITERAL(15, 171, 10), // "downloader"
QT_MOC_LITERAL(16, 182, 20), // "slotDownloadProgress"
QT_MOC_LITERAL(17, 203, 18), // "bytesNewlyReceived"
QT_MOC_LITERAL(18, 222, 17), // "slotDownloadError"
QT_MOC_LITERAL(19, 240, 13), // "slotSslErrors"
QT_MOC_LITERAL(20, 254, 14), // "slotRedirected"
QT_MOC_LITERAL(21, 269, 3) // "url"

    },
    "QGSDownloadTask\0downloadProgress\0\0"
    "bytesReceived\0bytesTotal\0QGSTask*\0"
    "task\0downloadError\0QGSNetworkError\0"
    "error\0sslErrors\0QList<QSslError>\0"
    "errors\0slotFinished\0QGSDownloader*\0"
    "downloader\0slotDownloadProgress\0"
    "bytesNewlyReceived\0slotDownloadError\0"
    "slotSslErrors\0slotRedirected\0url"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QGSDownloadTask[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   54,    2, 0x06 /* Public */,
       7,    2,   61,    2, 0x06 /* Public */,
      10,    2,   66,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    1,   71,    2, 0x08 /* Private */,
      16,    4,   74,    2, 0x08 /* Private */,
      18,    2,   83,    2, 0x08 /* Private */,
      19,    2,   88,    2, 0x08 /* Private */,
      20,    2,   93,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong, 0x80000000 | 5,    3,    4,    6,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 5,    9,    6,
    QMetaType::Void, 0x80000000 | 11, 0x80000000 | 5,   12,    6,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong, QMetaType::LongLong, 0x80000000 | 14,   17,    3,    4,   15,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 14,    9,   15,
    QMetaType::Void, 0x80000000 | 11, 0x80000000 | 14,   12,   15,
    QMetaType::Void, QMetaType::QUrl, 0x80000000 | 14,   21,   15,

       0        // eod
};

void QGSDownloadTask::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QGSDownloadTask *_t = static_cast<QGSDownloadTask *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->downloadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< QGSTask*(*)>(_a[3]))); break;
        case 1: _t->downloadError((*reinterpret_cast< QGSNetworkError(*)>(_a[1])),(*reinterpret_cast< QGSTask*(*)>(_a[2]))); break;
        case 2: _t->sslErrors((*reinterpret_cast< const QList<QSslError>(*)>(_a[1])),(*reinterpret_cast< QGSTask*(*)>(_a[2]))); break;
        case 3: _t->slotFinished((*reinterpret_cast< QGSDownloader*(*)>(_a[1]))); break;
        case 4: _t->slotDownloadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< qint64(*)>(_a[3])),(*reinterpret_cast< QGSDownloader*(*)>(_a[4]))); break;
        case 5: _t->slotDownloadError((*reinterpret_cast< QGSNetworkError(*)>(_a[1])),(*reinterpret_cast< QGSDownloader*(*)>(_a[2]))); break;
        case 6: _t->slotSslErrors((*reinterpret_cast< const QList<QSslError>(*)>(_a[1])),(*reinterpret_cast< QGSDownloader*(*)>(_a[2]))); break;
        case 7: _t->slotRedirected((*reinterpret_cast< const QUrl(*)>(_a[1])),(*reinterpret_cast< QGSDownloader*(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSTask* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSTask* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSTask* >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QSslError> >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSDownloader* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 3:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSDownloader* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSDownloader* >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSDownloader* >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QSslError> >(); break;
            }
            break;
        case 7:
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
            typedef void (QGSDownloadTask::*_t)(qint64 , qint64 , QGSTask * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSDownloadTask::downloadProgress)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QGSDownloadTask::*_t)(QGSNetworkError , QGSTask * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSDownloadTask::downloadError)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (QGSDownloadTask::*_t)(const QList<QSslError> & , QGSTask * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSDownloadTask::sslErrors)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject QGSDownloadTask::staticMetaObject = {
    { &QGSTask::staticMetaObject, qt_meta_stringdata_QGSDownloadTask.data,
      qt_meta_data_QGSDownloadTask,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QGSDownloadTask::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QGSDownloadTask::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QGSDownloadTask.stringdata0))
        return static_cast<void*>(this);
    return QGSTask::qt_metacast(_clname);
}

int QGSDownloadTask::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGSTask::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void QGSDownloadTask::downloadProgress(qint64 _t1, qint64 _t2, QGSTask * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QGSDownloadTask::downloadError(QGSNetworkError _t1, QGSTask * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QGSDownloadTask::sslErrors(const QList<QSslError> & _t1, QGSTask * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
