/****************************************************************************
** Meta object code from reading C++ file 'QGSLibraryBuilder.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Builder/QGSLibraryBuilder.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QGSLibraryBuilder.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QGSLibraryBuilder_t {
    QByteArrayData data[17];
    char stringdata0[289];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QGSLibraryBuilder_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QGSLibraryBuilder_t qt_meta_stringdata_QGSLibraryBuilder = {
    {
QT_MOC_LITERAL(0, 0, 17), // "QGSLibraryBuilder"
QT_MOC_LITERAL(1, 18, 23), // "slotDownloadTaskStarted"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 8), // "QGSTask*"
QT_MOC_LITERAL(4, 52, 4), // "task"
QT_MOC_LITERAL(5, 57, 24), // "slotDownloadTaskFinished"
QT_MOC_LITERAL(6, 82, 22), // "slotDownloadTaskStoped"
QT_MOC_LITERAL(7, 105, 24), // "slotDownloadTaskCanceled"
QT_MOC_LITERAL(8, 130, 21), // "slotDownloadTaskError"
QT_MOC_LITERAL(9, 152, 32), // "slotDownloadTaskDownloadProgress"
QT_MOC_LITERAL(10, 185, 13), // "bytesReceived"
QT_MOC_LITERAL(11, 199, 10), // "bytesTotal"
QT_MOC_LITERAL(12, 210, 29), // "slotDownloadTaskDownloadError"
QT_MOC_LITERAL(13, 240, 15), // "QGSNetworkError"
QT_MOC_LITERAL(14, 256, 5), // "error"
QT_MOC_LITERAL(15, 262, 13), // "slotEraseTask"
QT_MOC_LITERAL(16, 276, 12) // "slotFinished"

    },
    "QGSLibraryBuilder\0slotDownloadTaskStarted\0"
    "\0QGSTask*\0task\0slotDownloadTaskFinished\0"
    "slotDownloadTaskStoped\0slotDownloadTaskCanceled\0"
    "slotDownloadTaskError\0"
    "slotDownloadTaskDownloadProgress\0"
    "bytesReceived\0bytesTotal\0"
    "slotDownloadTaskDownloadError\0"
    "QGSNetworkError\0error\0slotEraseTask\0"
    "slotFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QGSLibraryBuilder[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x08 /* Private */,
       5,    1,   62,    2, 0x08 /* Private */,
       6,    1,   65,    2, 0x08 /* Private */,
       7,    1,   68,    2, 0x08 /* Private */,
       8,    1,   71,    2, 0x08 /* Private */,
       9,    3,   74,    2, 0x08 /* Private */,
      12,    2,   81,    2, 0x08 /* Private */,
      15,    1,   86,    2, 0x08 /* Private */,
      16,    0,   89,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong, 0x80000000 | 3,   10,   11,    4,
    QMetaType::Void, 0x80000000 | 13, 0x80000000 | 3,   14,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

       0        // eod
};

void QGSLibraryBuilder::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QGSLibraryBuilder *_t = static_cast<QGSLibraryBuilder *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotDownloadTaskStarted((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
        case 1: _t->slotDownloadTaskFinished((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
        case 2: _t->slotDownloadTaskStoped((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
        case 3: _t->slotDownloadTaskCanceled((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
        case 4: _t->slotDownloadTaskError((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
        case 5: _t->slotDownloadTaskDownloadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< QGSTask*(*)>(_a[3]))); break;
        case 6: _t->slotDownloadTaskDownloadError((*reinterpret_cast< QGSNetworkError(*)>(_a[1])),(*reinterpret_cast< QGSTask*(*)>(_a[2]))); break;
        case 7: _t->slotEraseTask((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
        case 8: _t->slotFinished(); break;
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
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSTask* >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSNetworkError >(); break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSTask* >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSTask* >(); break;
            }
            break;
        }
    }
}

const QMetaObject QGSLibraryBuilder::staticMetaObject = {
    { &QGSIBuilder::staticMetaObject, qt_meta_stringdata_QGSLibraryBuilder.data,
      qt_meta_data_QGSLibraryBuilder,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QGSLibraryBuilder::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QGSLibraryBuilder::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QGSLibraryBuilder.stringdata0))
        return static_cast<void*>(this);
    return QGSIBuilder::qt_metacast(_clname);
}

int QGSLibraryBuilder::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGSIBuilder::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
