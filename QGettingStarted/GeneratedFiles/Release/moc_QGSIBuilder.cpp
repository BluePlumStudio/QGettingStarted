/****************************************************************************
** Meta object code from reading C++ file 'QGSIBuilder.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Builder/QGSIBuilder.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QGSIBuilder.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QGSIBuilder_t {
    QByteArrayData data[15];
    char stringdata0[243];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QGSIBuilder_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QGSIBuilder_t qt_meta_stringdata_QGSIBuilder = {
    {
QT_MOC_LITERAL(0, 0, 11), // "QGSIBuilder"
QT_MOC_LITERAL(1, 12, 19), // "downloadTaskStarted"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 15), // "QGSDownloadInfo"
QT_MOC_LITERAL(4, 49, 12), // "downloadInfo"
QT_MOC_LITERAL(5, 62, 20), // "downloadTaskFinished"
QT_MOC_LITERAL(6, 83, 18), // "downloadTaskStoped"
QT_MOC_LITERAL(7, 102, 20), // "downloadTaskCanceled"
QT_MOC_LITERAL(8, 123, 28), // "downloadTaskDownloadProgress"
QT_MOC_LITERAL(9, 152, 13), // "bytesReceived"
QT_MOC_LITERAL(10, 166, 10), // "bytesTotal"
QT_MOC_LITERAL(11, 177, 25), // "downloadTaskDownloadError"
QT_MOC_LITERAL(12, 203, 15), // "QGSNetworkError"
QT_MOC_LITERAL(13, 219, 5), // "error"
QT_MOC_LITERAL(14, 225, 17) // "downloadTaskError"

    },
    "QGSIBuilder\0downloadTaskStarted\0\0"
    "QGSDownloadInfo\0downloadInfo\0"
    "downloadTaskFinished\0downloadTaskStoped\0"
    "downloadTaskCanceled\0downloadTaskDownloadProgress\0"
    "bytesReceived\0bytesTotal\0"
    "downloadTaskDownloadError\0QGSNetworkError\0"
    "error\0downloadTaskError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QGSIBuilder[] = {

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
       5,    1,   52,    2, 0x06 /* Public */,
       6,    1,   55,    2, 0x06 /* Public */,
       7,    1,   58,    2, 0x06 /* Public */,
       8,    3,   61,    2, 0x06 /* Public */,
      11,    2,   68,    2, 0x06 /* Public */,
      14,    1,   73,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong, 0x80000000 | 3,    9,   10,    4,
    QMetaType::Void, 0x80000000 | 12, 0x80000000 | 3,   13,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void QGSIBuilder::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QGSIBuilder *_t = static_cast<QGSIBuilder *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->downloadTaskStarted((*reinterpret_cast< QGSDownloadInfo(*)>(_a[1]))); break;
        case 1: _t->downloadTaskFinished((*reinterpret_cast< QGSDownloadInfo(*)>(_a[1]))); break;
        case 2: _t->downloadTaskStoped((*reinterpret_cast< QGSDownloadInfo(*)>(_a[1]))); break;
        case 3: _t->downloadTaskCanceled((*reinterpret_cast< QGSDownloadInfo(*)>(_a[1]))); break;
        case 4: _t->downloadTaskDownloadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< QGSDownloadInfo(*)>(_a[3]))); break;
        case 5: _t->downloadTaskDownloadError((*reinterpret_cast< QGSNetworkError(*)>(_a[1])),(*reinterpret_cast< QGSDownloadInfo(*)>(_a[2]))); break;
        case 6: _t->downloadTaskError((*reinterpret_cast< QGSDownloadInfo(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSDownloadInfo >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSDownloadInfo >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSDownloadInfo >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSDownloadInfo >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSDownloadInfo >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSDownloadInfo >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSNetworkError >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSDownloadInfo >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (QGSIBuilder::*_t)(QGSDownloadInfo );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSIBuilder::downloadTaskStarted)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QGSIBuilder::*_t)(QGSDownloadInfo );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSIBuilder::downloadTaskFinished)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (QGSIBuilder::*_t)(QGSDownloadInfo );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSIBuilder::downloadTaskStoped)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (QGSIBuilder::*_t)(QGSDownloadInfo );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSIBuilder::downloadTaskCanceled)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (QGSIBuilder::*_t)(qint64 , qint64 , QGSDownloadInfo );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSIBuilder::downloadTaskDownloadProgress)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (QGSIBuilder::*_t)(QGSNetworkError , QGSDownloadInfo );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSIBuilder::downloadTaskDownloadError)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (QGSIBuilder::*_t)(QGSDownloadInfo );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSIBuilder::downloadTaskError)) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject QGSIBuilder::staticMetaObject = {
    { &QGSTask::staticMetaObject, qt_meta_stringdata_QGSIBuilder.data,
      qt_meta_data_QGSIBuilder,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QGSIBuilder::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QGSIBuilder::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QGSIBuilder.stringdata0))
        return static_cast<void*>(this);
    return QGSTask::qt_metacast(_clname);
}

int QGSIBuilder::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGSTask::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void QGSIBuilder::downloadTaskStarted(QGSDownloadInfo _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QGSIBuilder::downloadTaskFinished(QGSDownloadInfo _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QGSIBuilder::downloadTaskStoped(QGSDownloadInfo _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QGSIBuilder::downloadTaskCanceled(QGSDownloadInfo _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QGSIBuilder::downloadTaskDownloadProgress(qint64 _t1, qint64 _t2, QGSDownloadInfo _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QGSIBuilder::downloadTaskDownloadError(QGSNetworkError _t1, QGSDownloadInfo _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QGSIBuilder::downloadTaskError(QGSDownloadInfo _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
