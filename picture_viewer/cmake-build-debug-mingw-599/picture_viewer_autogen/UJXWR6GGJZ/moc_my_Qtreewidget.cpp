/****************************************************************************
** Meta object code from reading C++ file 'my_Qtreewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/some_function/my_Qtreewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'my_Qtreewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_My_Qtreewidget_t {
    QByteArrayData data[10];
    char stringdata0[139];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_My_Qtreewidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_My_Qtreewidget_t qt_meta_stringdata_My_Qtreewidget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "My_Qtreewidget"
QT_MOC_LITERAL(1, 15, 14), // "on_itemClicked"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(4, 48, 4), // "item"
QT_MOC_LITERAL(5, 53, 15), // "on_itemExpanded"
QT_MOC_LITERAL(6, 69, 16), // "on_itemCollapsed"
QT_MOC_LITERAL(7, 86, 19), // "on_directoryChanged"
QT_MOC_LITERAL(8, 106, 11), // "changedPath"
QT_MOC_LITERAL(9, 118, 20) // "on_itemDoubleClicked"

    },
    "My_Qtreewidget\0on_itemClicked\0\0"
    "QTreeWidgetItem*\0item\0on_itemExpanded\0"
    "on_itemCollapsed\0on_directoryChanged\0"
    "changedPath\0on_itemDoubleClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_My_Qtreewidget[] = {

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
       9,    1,   51,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void My_Qtreewidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        My_Qtreewidget *_t = static_cast<My_Qtreewidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_itemClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 1: _t->on_itemExpanded((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->on_itemCollapsed((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 3: _t->on_directoryChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->on_itemDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject My_Qtreewidget::staticMetaObject = {
    { &QTreeWidget::staticMetaObject, qt_meta_stringdata_My_Qtreewidget.data,
      qt_meta_data_My_Qtreewidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *My_Qtreewidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *My_Qtreewidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_My_Qtreewidget.stringdata0))
        return static_cast<void*>(this);
    return QTreeWidget::qt_metacast(_clname);
}

int My_Qtreewidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
