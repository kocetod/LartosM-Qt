/****************************************************************************
** Meta object code from reading C++ file 'mediabrowser.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../LartosM-Qt/mediabrowser.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mediabrowser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MediaBrowser_t {
    QByteArrayData data[11];
    char stringdata0[191];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MediaBrowser_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MediaBrowser_t qt_meta_stringdata_MediaBrowser = {
    {
QT_MOC_LITERAL(0, 0, 12), // "MediaBrowser"
QT_MOC_LITERAL(1, 13, 23), // "on_imageBrowser_clicked"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 5), // "index"
QT_MOC_LITERAL(4, 44, 18), // "on_btnCopy_pressed"
QT_MOC_LITERAL(5, 63, 19), // "on_btnCopy_released"
QT_MOC_LITERAL(6, 83, 18), // "on_btnBack_pressed"
QT_MOC_LITERAL(7, 102, 19), // "on_btnBack_released"
QT_MOC_LITERAL(8, 122, 23), // "on_imageBrowser_pressed"
QT_MOC_LITERAL(9, 146, 21), // "on_btnCopyAll_pressed"
QT_MOC_LITERAL(10, 168, 22) // "on_btnCopyAll_released"

    },
    "MediaBrowser\0on_imageBrowser_clicked\0"
    "\0index\0on_btnCopy_pressed\0on_btnCopy_released\0"
    "on_btnBack_pressed\0on_btnBack_released\0"
    "on_imageBrowser_pressed\0on_btnCopyAll_pressed\0"
    "on_btnCopyAll_released"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MediaBrowser[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x08 /* Private */,
       4,    0,   57,    2, 0x08 /* Private */,
       5,    0,   58,    2, 0x08 /* Private */,
       6,    0,   59,    2, 0x08 /* Private */,
       7,    0,   60,    2, 0x08 /* Private */,
       8,    1,   61,    2, 0x08 /* Private */,
       9,    0,   64,    2, 0x08 /* Private */,
      10,    0,   65,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QModelIndex,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    3,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MediaBrowser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MediaBrowser *_t = static_cast<MediaBrowser *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_imageBrowser_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 1: _t->on_btnCopy_pressed(); break;
        case 2: _t->on_btnCopy_released(); break;
        case 3: _t->on_btnBack_pressed(); break;
        case 4: _t->on_btnBack_released(); break;
        case 5: _t->on_imageBrowser_pressed((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 6: _t->on_btnCopyAll_pressed(); break;
        case 7: _t->on_btnCopyAll_released(); break;
        default: ;
        }
    }
}

const QMetaObject MediaBrowser::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MediaBrowser.data,
      qt_meta_data_MediaBrowser,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MediaBrowser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MediaBrowser::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MediaBrowser.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int MediaBrowser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
