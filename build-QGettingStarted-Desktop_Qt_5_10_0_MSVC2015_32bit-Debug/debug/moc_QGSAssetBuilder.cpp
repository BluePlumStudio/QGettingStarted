/****************************************************************************
** Meta object code from reading C++ file 'QGSAssetBuilder.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QGettingStarted/Builder/QGSAssetBuilder.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QGSAssetBuilder.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QGSAssetBuilder_t {
    QByteArrayData data[20];
    char stringdata0[329];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QGSAssetBuilder_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QGSAssetBuilder_t qt_meta_stringdata_QGSAssetBuilder = {
    {
QT_MOC_LITERAL(0, 0, 15), // "QGSAssetBuilder"
QT_MOC_LITERAL(1, 16, 13), // "templateStart"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 8), // "QGSTask*"
QT_MOC_LITERAL(4, 40, 4), // "task"
QT_MOC_LITERAL(5, 45, 12), // "templateStop"
QT_MOC_LITERAL(6, 58, 14), // "templateCancel"
QT_MOC_LITERAL(7, 73, 23), // "slotDownloadTaskStarted"
QT_MOC_LITERAL(8, 97, 24), // "slotDownloadTaskFinished"
QT_MOC_LITERAL(9, 122, 22), // "slotDownloadTaskStoped"
QT_MOC_LITERAL(10, 145, 24), // "slotDownloadTaskCanceled"
QT_MOC_LITERAL(11, 170, 21), // "slotDownloadTaskError"
QT_MOC_LITERAL(12, 192, 32), // "slotDownloadTaskDownloadProgress"
QT_MOC_LITERAL(13, 225, 13), // "bytesReceived"
QT_MOC_LITERAL(14, 239, 10), // "bytesTotal"
QT_MOC_LITERAL(15, 250, 29), // "slotDownloadTaskDownloadError"
QT_MOC_LITERAL(16, 280, 15), // "QGSNetworkError"
QT_MOC_LITERAL(17, 296, 5), // "error"
QT_MOC_LITERAL(18, 302, 13), // "slotEraseTask"
QT_MOC_LITERAL(19, 316, 12) // "slotFinished"

    },
    "QGSAssetBuilder\0templateStart\0\0QGSTask*\0"
    "task\0templateStop\0templateCancel\0"
    "slotDownloadTaskStarted\0"
    "slotDownloadTaskFinished\0"
    "slotDownloadTaskStoped\0slotDownloadTaskCanceled\0"
    "slotDownloadTaskError\0"
    "slotDownloadTaskDownloadProgress\0"
    "bytesReceived\0bytesTotal\0"
    "slotDownloadTaskDownloadError\0"
    "QGSNetworkError\0error\0slotEraseTask\0"
    "slotFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QGSAssetBuilder[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x09 /* Protected */,
       5,    1,   77,    2, 0x09 /* Protected */,
       6,    1,   80,    2, 0x09 /* Protected */,
       7,    1,   83,    2, 0x08 /* Private */,
       8,    1,   86,    2, 0x08 /* Private */,
       9,    1,   89,    2, 0x08 /* Private */,
      10,    1,   92,    2, 0x08 /* Private */,
      11,    1,   95,    2, 0x08 /* Private */,
      12,    3,   98,    2, 0x08 /* Private */,
      15,    2,  105,    2, 0x08 /* Private */,
      18,    1,  110,    2, 0x08 /* Private */,
      19,    0,  113,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong, 0x80000000 | 3,   13,   14,    4,
    QMetaType::Void, 0x80000000 | 16, 0x80000000 | 3,   17,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

       0        // eod
};

void QGSAssetBuilder::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QGSAssetBuilder *_t = static_cast<QGSAssetBuilder *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->templateStart((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
        case 1: _t->templateStop((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
        case 2: _t->templateCancel((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
        case 3: _t->slotDownloadTaskStarted((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
        case 4: _t->slotDownloadTaskFinished((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
        case 5: _t->slotDownloadTaskStoped((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
        case 6: _t->slotDownloadTaskCanceled((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
        case 7: _t->slotDownloadTaskError((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
        case 8: _t->slotDownloadTaskDownloadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< QGSTask*(*)>(_a[3]))); break;
        case 9: _t->slotDownloadTaskDownloadError((*reinterpret_cast< QGSNetworkError(*)>(_a[1])),(*reinterpret_cast< QGSTask*(*)>(_a[2]))); break;
        case 10: _t->slotEraseTask((*reinterpret_cast< QGSTask*(*)>(_a[1]))); break;
        case 11: _t->slotFinished(); break;
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
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSTask* >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
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
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSTask* >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGSNetworkError >(); break;
            case 1:
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
    }
}

const QMetaObject QGSAssetBuilder::staticMetaObject = {
    { &QGSIBuilder::staticMetaObject, qt_meta_stringdata_QGSAssetBuilder.data,
      qt_meta_data_QGSAssetBuilder,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QGSAssetBuilder::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QGSAssetBuilder::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QGSAssetBuilder.stringdata0))
        return static_cast<void*>(this);
    return QGSIBuilder::qt_metacast(_clname);
}

int QGSAssetBuilder::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGSIBuilder::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
