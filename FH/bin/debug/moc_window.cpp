/****************************************************************************
** Meta object code from reading C++ file 'window.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../window.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WINDOW_t {
    QByteArrayData data[17];
    char stringdata0[270];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WINDOW_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WINDOW_t qt_meta_stringdata_WINDOW = {
    {
QT_MOC_LITERAL(0, 0, 6), // "WINDOW"
QT_MOC_LITERAL(1, 7, 15), // "SetSignInWindow"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 17), // "SetRegisterWindow"
QT_MOC_LITERAL(4, 42, 13), // "SetHomeWindow"
QT_MOC_LITERAL(5, 56, 8), // "QWidget*"
QT_MOC_LITERAL(6, 65, 14), // "SetPrintWindow"
QT_MOC_LITERAL(7, 80, 23), // "SetCreateTrainingWindow"
QT_MOC_LITERAL(8, 104, 22), // "SetReactionSpeedWindow"
QT_MOC_LITERAL(9, 127, 13), // "SetLoginValue"
QT_MOC_LITERAL(10, 141, 5), // "login"
QT_MOC_LITERAL(11, 147, 16), // "SetPasswordValue"
QT_MOC_LITERAL(12, 164, 8), // "password"
QT_MOC_LITERAL(13, 173, 24), // "SendRegistrationDataToDB"
QT_MOC_LITERAL(14, 198, 18), // "SendSignInDataToDB"
QT_MOC_LITERAL(15, 217, 25), // "PrintWindowButBackClicked"
QT_MOC_LITERAL(16, 243, 26) // "CreateTrainingWindowClosed"

    },
    "WINDOW\0SetSignInWindow\0\0SetRegisterWindow\0"
    "SetHomeWindow\0QWidget*\0SetPrintWindow\0"
    "SetCreateTrainingWindow\0SetReactionSpeedWindow\0"
    "SetLoginValue\0login\0SetPasswordValue\0"
    "password\0SendRegistrationDataToDB\0"
    "SendSignInDataToDB\0PrintWindowButBackClicked\0"
    "CreateTrainingWindowClosed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WINDOW[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x0a /* Public */,
       3,    0,   75,    2, 0x0a /* Public */,
       4,    1,   76,    2, 0x0a /* Public */,
       6,    0,   79,    2, 0x0a /* Public */,
       7,    0,   80,    2, 0x0a /* Public */,
       8,    0,   81,    2, 0x0a /* Public */,
       9,    1,   82,    2, 0x0a /* Public */,
      11,    1,   85,    2, 0x0a /* Public */,
      13,    0,   88,    2, 0x0a /* Public */,
      14,    0,   89,    2, 0x0a /* Public */,
      15,    0,   90,    2, 0x0a /* Public */,
      16,    0,   91,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void WINDOW::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WINDOW *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SetSignInWindow(); break;
        case 1: _t->SetRegisterWindow(); break;
        case 2: _t->SetHomeWindow((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 3: _t->SetPrintWindow(); break;
        case 4: _t->SetCreateTrainingWindow(); break;
        case 5: _t->SetReactionSpeedWindow(); break;
        case 6: _t->SetLoginValue((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->SetPasswordValue((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->SendRegistrationDataToDB(); break;
        case 9: _t->SendSignInDataToDB(); break;
        case 10: _t->PrintWindowButBackClicked(); break;
        case 11: _t->CreateTrainingWindowClosed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WINDOW::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_WINDOW.data,
    qt_meta_data_WINDOW,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WINDOW::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WINDOW::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WINDOW.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int WINDOW::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
