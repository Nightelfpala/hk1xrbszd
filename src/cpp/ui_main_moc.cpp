/****************************************************************************
** Meta object code from reading C++ file 'ui_main.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../headers/ui_main.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ui_main.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_mainDisplay[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x08,
      24,   12,   12,   12, 0x08,
      30,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_mainDisplay[] = {
    "mainDisplay\0\0openFile()\0oF2()\0"
    "interpretNext()\0"
};

void mainDisplay::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        mainDisplay *_t = static_cast<mainDisplay *>(_o);
        switch (_id) {
        case 0: _t->openFile(); break;
        case 1: _t->oF2(); break;
        case 2: _t->interpretNext(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData mainDisplay::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject mainDisplay::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_mainDisplay,
      qt_meta_data_mainDisplay, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &mainDisplay::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *mainDisplay::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *mainDisplay::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_mainDisplay))
        return static_cast<void*>(const_cast< mainDisplay*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int mainDisplay::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE