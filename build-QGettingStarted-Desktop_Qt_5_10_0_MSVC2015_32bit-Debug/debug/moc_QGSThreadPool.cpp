/****************************************************************************
** Meta object code from reading C++ file 'QGSThreadPool.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QGettingStarted/Util/QGSThreadPool.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QGSThreadPool.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QGSThreadPool_t {
    QByteArrayData data[6];
    char stringdata0[54];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QGSThreadPool_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QGSThreadPool_t qt_meta_stringdata_QGSThreadPool = {
    {
QT_MOC_LITERAL(0, 0, 13), // "QGSThreadPool"
QT_MOC_LITERAL(1, 14, 11), // "taskStarted"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 8), // "QGSTask*"
QT_MOC_LITERAL(4, 36, 4), // "task"
QT_MOC_LITERAL(5, 41, 12) // "taskFinished"

    },
    "QGSThreadPool\0taskStarted\0\0QGSTask*\0"
    "task\0taskFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QGSThreadPool[] = {

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
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void QGSThreadPool::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QGSThreadPool *_t = static_cast<QGSThreadPool *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->taskStarted((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
        case 1: _t->taskFinished((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
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
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (QGSThreadPool::*_t)(QGSTask * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSThreadPool::taskStarted)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QGSThreadPool::*_t)(QGSTask * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSThreadPool::taskFinished)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject QGSThreadPool::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_QGSThreadPool.data,
      qt_meta_data_QGSThreadPool,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QGSThreadPool::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QGSThreadPool::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QGSThreadPool.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int QGSThreadPool::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
void QGSThreadPool::taskStarted(QGSTask * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QGSThreadPool::taskFinished(QGSTask * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
