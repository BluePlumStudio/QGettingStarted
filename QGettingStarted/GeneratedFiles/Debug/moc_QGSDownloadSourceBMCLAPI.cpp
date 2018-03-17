/****************************************************************************
** Meta object code from reading C++ file 'QGSDownloadSourceBMCLAPI.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Download/QGSDownloadSourceBMCLAPI.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QGSDownloadSourceBMCLAPI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QGSDownloadSourceBMCLAPI_t {
    QByteArrayData data[1];
    char stringdata0[25];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QGSDownloadSourceBMCLAPI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QGSDownloadSourceBMCLAPI_t qt_meta_stringdata_QGSDownloadSourceBMCLAPI = {
    {
QT_MOC_LITERAL(0, 0, 24) // "QGSDownloadSourceBMCLAPI"

    },
    "QGSDownloadSourceBMCLAPI"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QGSDownloadSourceBMCLAPI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void QGSDownloadSourceBMCLAPI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject QGSDownloadSourceBMCLAPI::staticMetaObject = {
    { &QGSIDownloadSource::staticMetaObject, qt_meta_stringdata_QGSDownloadSourceBMCLAPI.data,
      qt_meta_data_QGSDownloadSourceBMCLAPI,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QGSDownloadSourceBMCLAPI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QGSDownloadSourceBMCLAPI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QGSDownloadSourceBMCLAPI.stringdata0))
        return static_cast<void*>(this);
    return QGSIDownloadSource::qt_metacast(_clname);
}

int QGSDownloadSourceBMCLAPI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGSIDownloadSource::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
