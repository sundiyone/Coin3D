/****************************************************************************
** Meta object code from reading C++ file 'ContextMenu.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../quarter4/src/Quarter/ContextMenu.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ContextMenu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SIM__Coin3D__Quarter__ContextMenu_t {
    QByteArrayData data[7];
    char stringdata0[108];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SIM__Coin3D__Quarter__ContextMenu_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SIM__Coin3D__Quarter__ContextMenu_t qt_meta_stringdata_SIM__Coin3D__Quarter__ContextMenu = {
    {
QT_MOC_LITERAL(0, 0, 33), // "SIM::Coin3D::Quarter::Context..."
QT_MOC_LITERAL(1, 34, 16), // "changeRenderMode"
QT_MOC_LITERAL(2, 51, 0), // ""
QT_MOC_LITERAL(3, 52, 8), // "QAction*"
QT_MOC_LITERAL(4, 61, 6), // "action"
QT_MOC_LITERAL(5, 68, 16), // "changeStereoMode"
QT_MOC_LITERAL(6, 85, 22) // "changeTransparencyType"

    },
    "SIM::Coin3D::Quarter::ContextMenu\0"
    "changeRenderMode\0\0QAction*\0action\0"
    "changeStereoMode\0changeTransparencyType"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SIM__Coin3D__Quarter__ContextMenu[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a /* Public */,
       5,    1,   32,    2, 0x0a /* Public */,
       6,    1,   35,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void SIM::Coin3D::Quarter::ContextMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ContextMenu *_t = static_cast<ContextMenu *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changeRenderMode((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 1: _t->changeStereoMode((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 2: _t->changeTransparencyType((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject SIM::Coin3D::Quarter::ContextMenu::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SIM__Coin3D__Quarter__ContextMenu.data,
      qt_meta_data_SIM__Coin3D__Quarter__ContextMenu,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SIM::Coin3D::Quarter::ContextMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SIM::Coin3D::Quarter::ContextMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SIM__Coin3D__Quarter__ContextMenu.stringdata0))
        return static_cast<void*>(const_cast< ContextMenu*>(this));
    return QObject::qt_metacast(_clname);
}

int SIM::Coin3D::Quarter::ContextMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
