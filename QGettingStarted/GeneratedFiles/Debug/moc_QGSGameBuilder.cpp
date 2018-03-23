/****************************************************************************
** Meta object code from reading C++ file 'QGSGameBuilder.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GameBuilder/QGSGameBuilder.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QGSGameBuilder.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QGSGameBuilder_t {
    QByteArrayData data[11];
    char stringdata0[171];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QGSGameBuilder_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QGSGameBuilder_t qt_meta_stringdata_QGSGameBuilder = {
    {
QT_MOC_LITERAL(0, 0, 14), // "QGSGameBuilder"
QT_MOC_LITERAL(1, 15, 23), // "slotDownloadTaskStarted"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 8), // "QGSTask*"
QT_MOC_LITERAL(4, 49, 4), // "task"
QT_MOC_LITERAL(5, 54, 24), // "slotDownloadTaskFinished"
QT_MOC_LITERAL(6, 79, 22), // "slotDownloadTaskStoped"
QT_MOC_LITERAL(7, 102, 24), // "slotDownloadTaskCanceled"
QT_MOC_LITERAL(8, 127, 21), // "slotDownloadTaskError"
QT_MOC_LITERAL(9, 149, 15), // "QGSNetworkError"
QT_MOC_LITERAL(10, 165, 5) // "error"

    },
    "QGSGameBuilder\0slotDownloadTaskStarted\0"
    "\0QGSTask*\0task\0slotDownloadTaskFinished\0"
    "slotDownloadTaskStoped\0slotDownloadTaskCanceled\0"
    "slotDownloadTaskError\0QGSNetworkError\0"
    "error"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QGSGameBuilder[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x08 /* Private */,
       5,    1,   42,    2, 0x08 /* Private */,
       6,    1,   45,    2, 0x08 /* Private */,
       7,    1,   48,    2, 0x08 /* Private */,
       8,    2,   51,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 3,   10,    4,

       0        // eod
};

void QGSGameBuilder::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QGSGameBuilder *_t = static_cast<QGSGameBuilder *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotDownloadTaskStarted((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
        case 1: _t->slotDownloadTaskFinished((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
        case 2: _t->slotDownloadTaskStoped((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
        case 3: _t->slotDownloadTaskCanceled((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
        case 4: _t->slotDownloadTaskError((*reinterpret_cast< QGSNetworkError(*)>(_a[1])),(*reinterpret_cast< QGSTask*(*)>(_a[2]))); break;
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
        }
    }
}

const QMetaObject QGSGameBuilder::staticMetaObject = {
    { &QGSIGameBuilder::staticMetaObject, qt_meta_stringdata_QGSGameBuilder.data,
      qt_meta_data_QGSGameBuilder,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QGSGameBuilder::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QGSGameBuilder::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QGSGameBuilder.stringdata0))
        return static_cast<void*>(this);
    return QGSIGameBuilder::qt_metacast(_clname);
}

int QGSGameBuilder::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGSIGameBuilder::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
