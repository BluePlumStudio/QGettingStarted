/****************************************************************************
** Meta object code from reading C++ file 'QGSTask.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QGettingStarted/Util/QGSTask.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QGSTask.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QGSTask_t {
    QByteArrayData data[15];
    char stringdata0[122];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QGSTask_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QGSTask_t qt_meta_stringdata_QGSTask = {
    {
QT_MOC_LITERAL(0, 0, 7), // "QGSTask"
QT_MOC_LITERAL(1, 8, 7), // "started"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 8), // "QGSTask*"
QT_MOC_LITERAL(4, 26, 4), // "task"
QT_MOC_LITERAL(5, 31, 8), // "finished"
QT_MOC_LITERAL(6, 40, 6), // "stoped"
QT_MOC_LITERAL(7, 47, 8), // "canceled"
QT_MOC_LITERAL(8, 56, 5), // "error"
QT_MOC_LITERAL(9, 62, 5), // "start"
QT_MOC_LITERAL(10, 68, 4), // "stop"
QT_MOC_LITERAL(11, 73, 6), // "cancel"
QT_MOC_LITERAL(12, 80, 13), // "templateStart"
QT_MOC_LITERAL(13, 94, 12), // "templateStop"
QT_MOC_LITERAL(14, 107, 14) // "templateCancel"

    },
    "QGSTask\0started\0\0QGSTask*\0task\0finished\0"
    "stoped\0canceled\0error\0start\0stop\0"
    "cancel\0templateStart\0templateStop\0"
    "templateCancel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QGSTask[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       5,    1,   72,    2, 0x06 /* Public */,
       6,    1,   75,    2, 0x06 /* Public */,
       7,    1,   78,    2, 0x06 /* Public */,
       8,    1,   81,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   84,    2, 0x0a /* Public */,
      10,    0,   85,    2, 0x0a /* Public */,
      11,    0,   86,    2, 0x0a /* Public */,
      12,    1,   87,    2, 0x09 /* Protected */,
      13,    1,   90,    2, 0x09 /* Protected */,
      14,    1,   93,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void QGSTask::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QGSTask *_t = static_cast<QGSTask *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->started((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
        case 1: _t->finished((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
        case 2: _t->stoped((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
        case 3: _t->canceled((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
        case 4: _t->error((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
        case 5: _t->start(); break;
        case 6: _t->stop(); break;
        case 7: _t->cancel(); break;
        case 8: _t->templateStart((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
        case 9: _t->templateStop((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
        case 10: _t->templateCancel((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
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
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSTask* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSTask* >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSTask* >(); break;
            }
            break;
        case 10:
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
            typedef void (QGSTask::*_t)(QGSTask * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSTask::started)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QGSTask::*_t)(QGSTask * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSTask::finished)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (QGSTask::*_t)(QGSTask * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSTask::stoped)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (QGSTask::*_t)(QGSTask * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSTask::canceled)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (QGSTask::*_t)(QGSTask * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QGSTask::error)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject QGSTask::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QGSTask.data,
      qt_meta_data_QGSTask,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QGSTask::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QGSTask::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QGSTask.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QGSTask::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void QGSTask::started(QGSTask * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QGSTask::finished(QGSTask * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QGSTask::stoped(QGSTask * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QGSTask::canceled(QGSTask * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QGSTask::error(QGSTask * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
