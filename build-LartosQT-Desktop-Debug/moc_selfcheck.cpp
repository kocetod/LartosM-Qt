/****************************************************************************
** Meta object code from reading C++ file 'selfcheck.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../LartosM-Qt/selfcheck.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'selfcheck.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SelfCheck_t {
    QByteArrayData data[18];
    char stringdata0[271];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SelfCheck_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SelfCheck_t qt_meta_stringdata_SelfCheck = {
    {
QT_MOC_LITERAL(0, 0, 9), // "SelfCheck"
QT_MOC_LITERAL(1, 10, 20), // "setDayCamInitialized"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 24), // "setThermalCamInitialized"
QT_MOC_LITERAL(4, 57, 17), // "setLrfInitialized"
QT_MOC_LITERAL(5, 75, 17), // "setGpsInitialized"
QT_MOC_LITERAL(6, 93, 17), // "setDmcInitialized"
QT_MOC_LITERAL(7, 111, 21), // "setPantiltInitialized"
QT_MOC_LITERAL(8, 133, 11), // "checkStatus"
QT_MOC_LITERAL(9, 145, 14), // "openLangWindow"
QT_MOC_LITERAL(10, 160, 11), // "checkDayCam"
QT_MOC_LITERAL(11, 172, 15), // "checkThermalCam"
QT_MOC_LITERAL(12, 188, 8), // "checkLrf"
QT_MOC_LITERAL(13, 197, 8), // "checkGps"
QT_MOC_LITERAL(14, 206, 8), // "checkDmc"
QT_MOC_LITERAL(15, 215, 12), // "checkPantilt"
QT_MOC_LITERAL(16, 228, 20), // "initializationFailed"
QT_MOC_LITERAL(17, 249, 21) // "startLoadingAnimation"

    },
    "SelfCheck\0setDayCamInitialized\0\0"
    "setThermalCamInitialized\0setLrfInitialized\0"
    "setGpsInitialized\0setDmcInitialized\0"
    "setPantiltInitialized\0checkStatus\0"
    "openLangWindow\0checkDayCam\0checkThermalCam\0"
    "checkLrf\0checkGps\0checkDmc\0checkPantilt\0"
    "initializationFailed\0startLoadingAnimation"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SelfCheck[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x08 /* Private */,
       3,    0,   95,    2, 0x08 /* Private */,
       4,    0,   96,    2, 0x08 /* Private */,
       5,    0,   97,    2, 0x08 /* Private */,
       6,    0,   98,    2, 0x08 /* Private */,
       7,    0,   99,    2, 0x08 /* Private */,
       8,    0,  100,    2, 0x08 /* Private */,
       9,    0,  101,    2, 0x08 /* Private */,
      10,    0,  102,    2, 0x08 /* Private */,
      11,    0,  103,    2, 0x08 /* Private */,
      12,    0,  104,    2, 0x08 /* Private */,
      13,    0,  105,    2, 0x08 /* Private */,
      14,    0,  106,    2, 0x08 /* Private */,
      15,    0,  107,    2, 0x08 /* Private */,
      16,    0,  108,    2, 0x08 /* Private */,
      17,    0,  109,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SelfCheck::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SelfCheck *_t = static_cast<SelfCheck *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setDayCamInitialized(); break;
        case 1: _t->setThermalCamInitialized(); break;
        case 2: _t->setLrfInitialized(); break;
        case 3: _t->setGpsInitialized(); break;
        case 4: _t->setDmcInitialized(); break;
        case 5: _t->setPantiltInitialized(); break;
        case 6: _t->checkStatus(); break;
        case 7: _t->openLangWindow(); break;
        case 8: _t->checkDayCam(); break;
        case 9: _t->checkThermalCam(); break;
        case 10: _t->checkLrf(); break;
        case 11: _t->checkGps(); break;
        case 12: _t->checkDmc(); break;
        case 13: _t->checkPantilt(); break;
        case 14: _t->initializationFailed(); break;
        case 15: _t->startLoadingAnimation(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject SelfCheck::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SelfCheck.data,
      qt_meta_data_SelfCheck,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SelfCheck::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SelfCheck::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SelfCheck.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int SelfCheck::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
