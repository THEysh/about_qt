/****************************************************************************
** Meta object code from reading C++ file 'Item_Interface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Item_Interface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Item_Interface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Item_Interface_t {
    QByteArrayData data[1];
    char stringdata0[15];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Item_Interface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Item_Interface_t qt_meta_stringdata_Item_Interface = {
    {
QT_MOC_LITERAL(0, 0, 14) // "Item_Interface"

    },
    "Item_Interface"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Item_Interface[] = {

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

void Item_Interface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject Item_Interface::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Item_Interface.data,
      qt_meta_data_Item_Interface,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Item_Interface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Item_Interface::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Item_Interface.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Item_Interface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_C_QPixmapItem_t {
    QByteArrayData data[1];
    char stringdata0[14];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_C_QPixmapItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_C_QPixmapItem_t qt_meta_stringdata_C_QPixmapItem = {
    {
QT_MOC_LITERAL(0, 0, 13) // "C_QPixmapItem"

    },
    "C_QPixmapItem"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_C_QPixmapItem[] = {

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

void C_QPixmapItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject C_QPixmapItem::staticMetaObject = {
    { &Item_Interface::staticMetaObject, qt_meta_stringdata_C_QPixmapItem.data,
      qt_meta_data_C_QPixmapItem,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *C_QPixmapItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *C_QPixmapItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_C_QPixmapItem.stringdata0))
        return static_cast<void*>(this);
    return Item_Interface::qt_metacast(_clname);
}

int C_QPixmapItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Item_Interface::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
