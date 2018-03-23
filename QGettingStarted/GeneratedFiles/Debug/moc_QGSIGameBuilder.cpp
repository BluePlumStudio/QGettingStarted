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
    QByteArrayData data[12];
    char stringdata0[178];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QGSIGameBuilder_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QGSIGameBuilder_t qt_meta_stringdata_QGSIGameBuilder = {
    {
QT_MOC_LITERAL(0, 0, 15), // "QGSIGameBuilder"
QT_MOC_LITERAL(1, 16, 19), // "downloadTaskStarted"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 8), // "QGSTask*"
QT_MOC_LITERAL(4, 46, 4), // "task"
QT_MOC_LITERAL(5, 51, 20), // "downloadTaskFinished"
QT_MOC_LITERAL(6, 72, 18), // "downloadTaskStoped"
QT_MOC_LITERAL(7, 91, 20), // "downloadTaskCanceled"
QT_MOC_LITERAL(8, 112, 25), // "downloadTaskDownloadError"
QT_MOC_LITERAL(9, 138, 15), // "QGSNetworkError"
QT_MOC_LITERAL(10, 154, 5), // "error"
QT_MOC_LITERAL(11, 160, 17) // "downloadTaskError"

    },
    "QGSIGameBuilder\0downloadTaskStarted\0"
    "\0QGSTask*\0task\0downloadTaskFinished\0"
    "downloadTaskStoped\0downloadTaskCanceled\0"
    "downloadTaskDownloadError\0QGSNetworkError\0"
    "error\0downloadTaskError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QGSIGameBuilder[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       5,    1,   47,    2, 0x06 /* Public */,
       6,    1,   50,    2, 0x06 /* Public */,
       7,    1,   53,    2, 0x06 /* Public */,
       8,    2,   56,    2, 0x06 /* Public */,
      11,    1,   61,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 3,   10,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void QGSIGameBuilder::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QGSIGameBuilder *_t = static_cast<QGSIGameBuilder *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->downloadTaskStarted((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
        case 1: _t->downloadTaskFinished((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
        case 2: _t->downloadTaskStoped((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
        case 3: _t->downloadTaskCanceled((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
        case 4: _t->downloadTaskDownloadError((*reinterpret_cast< QGSNetworkError(*)>(_a[1])),(*reinterpret_cast< QGSTask*(*)>(_a[2]))); break;
        case 5: _t->downloadTaskError((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSTask* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSTask* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSTask* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSTask* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSTask* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSTask* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (QGSIGameBuilder::*_t)(QGSTask * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSIGameBuilder::downloadTaskStarted)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QGSIGameBuilder::*_t)(QGSTask * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSIGameBuilder::downloadTaskFinished)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (QGSIGameBuilder::*_t)(QGSTask * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSIGameBuilder::downloadTaskStoped)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (QGSIGameBuilder::*_t)(QGSTask * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSIGameBuilder::downloadTaskCanceled)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (QGSIGameBuilder::*_t)(QGSNetworkError , QGSTask * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSIGameBuilder::downloadTaskDownloadError)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (QGSIGameBuilder::*_t)(QGSTask * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSIGameBuilder::downloadTaskError)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject QGSIGameBuilder::staticMetaObject = {
    { &QGSTask::staticMetaObject, qt_meta_stringdata_QGSIGameBuilder.data,
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
    return QGSTask::qt_metacast(_clname);
}

int QGSIGameBuilder::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGSTask::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void QGSIGameBuilder::downloadTaskStarted(QGSTask * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QGSIGameBuilder::downloadTaskFinished(QGSTask * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QGSIGameBuilder::downloadTaskStoped(QGSTask * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QGSIGameBuilder::downloadTaskCanceled(QGSTask * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QGSIGameBuilder::downloadTaskDownloadError(QGSNetworkError _t1, QGSTask * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QGSIGameBuilder::downloadTaskError(QGSTask * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
