/****************************************************************************
** Meta object code from reading C++ file 'QGSDownloadTaskGenerationTask.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Builder/QGSDownloadTaskGenerationTask.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QGSDownloadTaskGenerationTask.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QGSDownloadTaskGenerationTask_t {
    QByteArrayData data[11];
    char stringdata0[184];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QGSDownloadTaskGenerationTask_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QGSDownloadTaskGenerationTask_t qt_meta_stringdata_QGSDownloadTaskGenerationTask = {
    {
QT_MOC_LITERAL(0, 0, 29), // "QGSDownloadTaskGenerationTask"
QT_MOC_LITERAL(1, 30, 21), // "generationTaskStarted"
QT_MOC_LITERAL(2, 52, 0), // ""
QT_MOC_LITERAL(3, 53, 8), // "QGSTask*"
QT_MOC_LITERAL(4, 62, 4), // "task"
QT_MOC_LITERAL(5, 67, 22), // "generationTaskFinished"
QT_MOC_LITERAL(6, 90, 20), // "generationTaskStoped"
QT_MOC_LITERAL(7, 111, 22), // "generationTaskCanceled"
QT_MOC_LITERAL(8, 134, 27), // "generationTaskDownloadError"
QT_MOC_LITERAL(9, 162, 15), // "QGSNetworkError"
QT_MOC_LITERAL(10, 178, 5) // "error"

    },
    "QGSDownloadTaskGenerationTask\0"
    "generationTaskStarted\0\0QGSTask*\0task\0"
    "generationTaskFinished\0generationTaskStoped\0"
    "generationTaskCanceled\0"
    "generationTaskDownloadError\0QGSNetworkError\0"
    "error"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QGSDownloadTaskGenerationTask[] = {

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
       1,    1,   39,    2, 0x06 /* Public */,
       5,    1,   42,    2, 0x06 /* Public */,
       6,    1,   45,    2, 0x06 /* Public */,
       7,    1,   48,    2, 0x06 /* Public */,
       8,    2,   51,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 3,   10,    4,

       0        // eod
};

void QGSDownloadTaskGenerationTask::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QGSDownloadTaskGenerationTask *_t = static_cast<QGSDownloadTaskGenerationTask *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->generationTaskStarted((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
        case 1: _t->generationTaskFinished((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
        case 2: _t->generationTaskStoped((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
        case 3: _t->generationTaskCanceled((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
        case 4: _t->generationTaskDownloadError((*reinterpret_cast< QGSNetworkError(*)>(_a[1])),(*reinterpret_cast< QGSTask*(*)>(_a[2]))); break;
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
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSNetworkError >(); break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSTask* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (QGSDownloadTaskGenerationTask::*_t)(QGSTask * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSDownloadTaskGenerationTask::generationTaskStarted)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QGSDownloadTaskGenerationTask::*_t)(QGSTask * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSDownloadTaskGenerationTask::generationTaskFinished)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (QGSDownloadTaskGenerationTask::*_t)(QGSTask * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSDownloadTaskGenerationTask::generationTaskStoped)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (QGSDownloadTaskGenerationTask::*_t)(QGSTask * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSDownloadTaskGenerationTask::generationTaskCanceled)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (QGSDownloadTaskGenerationTask::*_t)(QGSNetworkError , QGSTask * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSDownloadTaskGenerationTask::generationTaskDownloadError)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject QGSDownloadTaskGenerationTask::staticMetaObject = {
    { &QGSTask::staticMetaObject, qt_meta_stringdata_QGSDownloadTaskGenerationTask.data,
      qt_meta_data_QGSDownloadTaskGenerationTask,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QGSDownloadTaskGenerationTask::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QGSDownloadTaskGenerationTask::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QGSDownloadTaskGenerationTask.stringdata0))
        return static_cast<void*>(this);
    return QGSTask::qt_metacast(_clname);
}

int QGSDownloadTaskGenerationTask::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGSTask::qt_metacall(_c, _id, _a);
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
void QGSDownloadTaskGenerationTask::generationTaskStarted(QGSTask * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QGSDownloadTaskGenerationTask::generationTaskFinished(QGSTask * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QGSDownloadTaskGenerationTask::generationTaskStoped(QGSTask * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QGSDownloadTaskGenerationTask::generationTaskCanceled(QGSTask * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QGSDownloadTaskGenerationTask::generationTaskDownloadError(QGSNetworkError _t1, QGSTask * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
