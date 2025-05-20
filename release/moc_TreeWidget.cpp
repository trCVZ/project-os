/****************************************************************************
** Meta object code from reading C++ file 'TreeWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.15)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../TreeWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TreeWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.15. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TreeWidget_t {
    QByteArrayData data[12];
    char stringdata0[155];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TreeWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TreeWidget_t qt_meta_stringdata_TreeWidget = {
    {
QT_MOC_LITERAL(0, 0, 10), // "TreeWidget"
QT_MOC_LITERAL(1, 11, 19), // "SIGNAL_RightClicked"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(4, 49, 21), // "SIGNAL_Statut_Fichier"
QT_MOC_LITERAL(5, 71, 23), // "slot_currentItemChanged"
QT_MOC_LITERAL(6, 95, 9), // "p_Current"
QT_MOC_LITERAL(7, 105, 16), // "slot_itemClicked"
QT_MOC_LITERAL(8, 122, 6), // "p_Item"
QT_MOC_LITERAL(9, 129, 13), // "onItemChanged"
QT_MOC_LITERAL(10, 143, 4), // "item"
QT_MOC_LITERAL(11, 148, 6) // "column"

    },
    "TreeWidget\0SIGNAL_RightClicked\0\0"
    "QTreeWidgetItem*\0SIGNAL_Statut_Fichier\0"
    "slot_currentItemChanged\0p_Current\0"
    "slot_itemClicked\0p_Item\0onItemChanged\0"
    "item\0column"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TreeWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06 /* Public */,
       4,    1,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    2,   47,    2, 0x0a /* Public */,
       7,    2,   52,    2, 0x0a /* Public */,
       9,    2,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    6,    2,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    8,    2,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,   10,   11,

       0        // eod
};

void TreeWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TreeWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->SIGNAL_RightClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->SIGNAL_Statut_Fichier((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->slot_currentItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 3: _t->slot_itemClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->onItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TreeWidget::*)(QTreeWidgetItem * , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TreeWidget::SIGNAL_RightClicked)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TreeWidget::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TreeWidget::SIGNAL_Statut_Fichier)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TreeWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QTreeWidget::staticMetaObject>(),
    qt_meta_stringdata_TreeWidget.data,
    qt_meta_data_TreeWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TreeWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TreeWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TreeWidget.stringdata0))
        return static_cast<void*>(this);
    return QTreeWidget::qt_metacast(_clname);
}

int TreeWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void TreeWidget::SIGNAL_RightClicked(QTreeWidgetItem * _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TreeWidget::SIGNAL_Statut_Fichier(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
