/****************************************************************************
** Meta object code from reading C++ file 'coordinatesystem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../LartosM-Qt/coordinatesystem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'coordinatesystem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CoordinateSystem_t {
    QByteArrayData data[20];
    char stringdata0[404];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CoordinateSystem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CoordinateSystem_t qt_meta_stringdata_CoordinateSystem = {
    {
QT_MOC_LITERAL(0, 0, 16), // "CoordinateSystem"
QT_MOC_LITERAL(1, 17, 29), // "setCoordinateSystemParameters"
QT_MOC_LITERAL(2, 47, 0), // ""
QT_MOC_LITERAL(3, 48, 14), // "on_wgs_pressed"
QT_MOC_LITERAL(4, 63, 20), // "on_krasovsky_pressed"
QT_MOC_LITERAL(5, 84, 17), // "on_utm_xy_pressed"
QT_MOC_LITERAL(6, 102, 13), // "on_bl_pressed"
QT_MOC_LITERAL(7, 116, 28), // "on_btnChooseCoordSys_pressed"
QT_MOC_LITERAL(8, 145, 16), // "setWgsStyleSheet"
QT_MOC_LITERAL(9, 162, 22), // "setKrasovskyStyleSheet"
QT_MOC_LITERAL(10, 185, 16), // "setUtmStyleSheet"
QT_MOC_LITERAL(11, 202, 15), // "setBlStyleSheet"
QT_MOC_LITERAL(12, 218, 18), // "setZone1StyleSheet"
QT_MOC_LITERAL(13, 237, 18), // "setZone2StyleSheet"
QT_MOC_LITERAL(14, 256, 25), // "btnChooseCoordSys_pressed"
QT_MOC_LITERAL(15, 282, 26), // "btnChooseCoordSys_released"
QT_MOC_LITERAL(16, 309, 26), // "btnChooseCoordSys_selected"
QT_MOC_LITERAL(17, 336, 18), // "on_zone_35_pressed"
QT_MOC_LITERAL(18, 355, 18), // "on_zone_34_pressed"
QT_MOC_LITERAL(19, 374, 29) // "on_btnChooseCoordSys_released"

    },
    "CoordinateSystem\0setCoordinateSystemParameters\0"
    "\0on_wgs_pressed\0on_krasovsky_pressed\0"
    "on_utm_xy_pressed\0on_bl_pressed\0"
    "on_btnChooseCoordSys_pressed\0"
    "setWgsStyleSheet\0setKrasovskyStyleSheet\0"
    "setUtmStyleSheet\0setBlStyleSheet\0"
    "setZone1StyleSheet\0setZone2StyleSheet\0"
    "btnChooseCoordSys_pressed\0"
    "btnChooseCoordSys_released\0"
    "btnChooseCoordSys_selected\0"
    "on_zone_35_pressed\0on_zone_34_pressed\0"
    "on_btnChooseCoordSys_released"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CoordinateSystem[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  104,    2, 0x08 /* Private */,
       3,    0,  105,    2, 0x08 /* Private */,
       4,    0,  106,    2, 0x08 /* Private */,
       5,    0,  107,    2, 0x08 /* Private */,
       6,    0,  108,    2, 0x08 /* Private */,
       7,    0,  109,    2, 0x08 /* Private */,
       8,    0,  110,    2, 0x08 /* Private */,
       9,    0,  111,    2, 0x08 /* Private */,
      10,    0,  112,    2, 0x08 /* Private */,
      11,    0,  113,    2, 0x08 /* Private */,
      12,    0,  114,    2, 0x08 /* Private */,
      13,    0,  115,    2, 0x08 /* Private */,
      14,    0,  116,    2, 0x08 /* Private */,
      15,    0,  117,    2, 0x08 /* Private */,
      16,    0,  118,    2, 0x08 /* Private */,
      17,    0,  119,    2, 0x08 /* Private */,
      18,    0,  120,    2, 0x08 /* Private */,
      19,    0,  121,    2, 0x08 /* Private */,

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
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CoordinateSystem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CoordinateSystem *_t = static_cast<CoordinateSystem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setCoordinateSystemParameters(); break;
        case 1: _t->on_wgs_pressed(); break;
        case 2: _t->on_krasovsky_pressed(); break;
        case 3: _t->on_utm_xy_pressed(); break;
        case 4: _t->on_bl_pressed(); break;
        case 5: _t->on_btnChooseCoordSys_pressed(); break;
        case 6: _t->setWgsStyleSheet(); break;
        case 7: _t->setKrasovskyStyleSheet(); break;
        case 8: _t->setUtmStyleSheet(); break;
        case 9: _t->setBlStyleSheet(); break;
        case 10: _t->setZone1StyleSheet(); break;
        case 11: _t->setZone2StyleSheet(); break;
        case 12: _t->btnChooseCoordSys_pressed(); break;
        case 13: _t->btnChooseCoordSys_released(); break;
        case 14: _t->btnChooseCoordSys_selected(); break;
        case 15: _t->on_zone_35_pressed(); break;
        case 16: _t->on_zone_34_pressed(); break;
        case 17: _t->on_btnChooseCoordSys_released(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject CoordinateSystem::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CoordinateSystem.data,
      qt_meta_data_CoordinateSystem,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CoordinateSystem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CoordinateSystem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CoordinateSystem.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int CoordinateSystem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
