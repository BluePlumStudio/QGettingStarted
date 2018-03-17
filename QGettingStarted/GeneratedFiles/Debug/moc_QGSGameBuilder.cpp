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
    QByteArrayData data[16];
    char stringdata0[227];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QGSGameBuilder_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QGSGameBuilder_t qt_meta_stringdata_QGSGameBuilder = {
    {
QT_MOC_LITERAL(0, 0, 14), // "QGSGameBuilder"
QT_MOC_LITERAL(1, 15, 17), // "slotDownloadStart"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 12), // "DownloadInfo"
QT_MOC_LITERAL(4, 47, 12), // "downloadInfo"
QT_MOC_LITERAL(5, 60, 20), // "slotDownloadProgress"
QT_MOC_LITERAL(6, 81, 13), // "bytesReceived"
QT_MOC_LITERAL(7, 95, 10), // "bytesTotal"
QT_MOC_LITERAL(8, 106, 20), // "slotDownloadFinished"
QT_MOC_LITERAL(9, 127, 19), // "slotDownloadTimeout"
QT_MOC_LITERAL(10, 147, 17), // "slotDownloadError"
QT_MOC_LITERAL(11, 165, 20), // "QGSDownloader::Error"
QT_MOC_LITERAL(12, 186, 5), // "error"
QT_MOC_LITERAL(13, 192, 12), // "slotFinished"
QT_MOC_LITERAL(14, 205, 9), // "slotError"
QT_MOC_LITERAL(15, 215, 11) // "errorString"

    },
    "QGSGameBuilder\0slotDownloadStart\0\0"
    "DownloadInfo\0downloadInfo\0"
    "slotDownloadProgress\0bytesReceived\0"
    "bytesTotal\0slotDownloadFinished\0"
    "slotDownloadTimeout\0slotDownloadError\0"
    "QGSDownloader::Error\0error\0slotFinished\0"
    "slotError\0errorString"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QGSGameBuilder[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x08 /* Private */,
       5,    3,   52,    2, 0x08 /* Private */,
       8,    1,   59,    2, 0x08 /* Private */,
       9,    1,   62,    2, 0x08 /* Private */,
      10,    2,   65,    2, 0x08 /* Private */,
      13,    0,   70,    2, 0x08 /* Private */,
      14,    1,   71,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong, 0x80000000 | 3,    6,    7,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 11, 0x80000000 | 3,   12,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   15,

       0        // eod
};

void QGSGameBuilder::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QGSGameBuilder *_t = static_cast<QGSGameBuilder *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotDownloadStart((*reinterpret_cast< const DownloadInfo(*)>(_a[1]))); break;
        case 1: _t->slotDownloadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< const DownloadInfo(*)>(_a[3]))); break;
        case 2: _t->slotDownloadFinished((*reinterpret_cast< const DownloadInfo(*)>(_a[1]))); break;
        case 3: _t->slotDownloadTimeout((*reinterpret_cast< const DownloadInfo(*)>(_a[1]))); break;
        case 4: _t->slotDownloadError((*reinterpret_cast< QGSDownloader::Error(*)>(_a[1])),(*reinterpret_cast< const DownloadInfo(*)>(_a[2]))); break;
        case 5: _t->slotFinished(); break;
        case 6: _t->slotError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
