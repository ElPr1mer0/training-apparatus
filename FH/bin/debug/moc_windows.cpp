/****************************************************************************
** Meta object code from reading C++ file 'windows.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../windows.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'windows.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WINDOWS_t {
    QByteArrayData data[20];
    char stringdata0[362];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WINDOWS_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WINDOWS_t qt_meta_stringdata_WINDOWS = {
    {
QT_MOC_LITERAL(0, 0, 7), // "WINDOWS"
QT_MOC_LITERAL(1, 8, 17), // "SetRegisterWindow"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 13), // "SetLoginValue"
QT_MOC_LITERAL(4, 41, 5), // "login"
QT_MOC_LITERAL(5, 47, 16), // "SetPasswordValue"
QT_MOC_LITERAL(6, 64, 8), // "password"
QT_MOC_LITERAL(7, 73, 24), // "SendRegistrationDataToDB"
QT_MOC_LITERAL(8, 98, 15), // "SetSignInWindow"
QT_MOC_LITERAL(9, 114, 18), // "SendSignInDataToDB"
QT_MOC_LITERAL(10, 133, 20), // "SignInButBackClicked"
QT_MOC_LITERAL(11, 154, 14), // "SetPrintWindow"
QT_MOC_LITERAL(12, 169, 25), // "PrintWindowButBackClicked"
QT_MOC_LITERAL(13, 195, 13), // "SetHomeWindow"
QT_MOC_LITERAL(14, 209, 24), // "HomeButPrintSpeedClicked"
QT_MOC_LITERAL(15, 234, 27), // "HomeButReactionSpeedClicked"
QT_MOC_LITERAL(16, 262, 23), // "SetCreateTrainingWindow"
QT_MOC_LITERAL(17, 286, 22), // "SetReactionSpeedWindow"
QT_MOC_LITERAL(18, 309, 25), // "ReactionSpeedWindowClosed"
QT_MOC_LITERAL(19, 335, 26) // "CreateTrainingWindowClosed"

    },
    "WINDOWS\0SetRegisterWindow\0\0SetLoginValue\0"
    "login\0SetPasswordValue\0password\0"
    "SendRegistrationDataToDB\0SetSignInWindow\0"
    "SendSignInDataToDB\0SignInButBackClicked\0"
    "SetPrintWindow\0PrintWindowButBackClicked\0"
    "SetHomeWindow\0HomeButPrintSpeedClicked\0"
    "HomeButReactionSpeedClicked\0"
    "SetCreateTrainingWindow\0SetReactionSpeedWindow\0"
    "ReactionSpeedWindowClosed\0"
    "CreateTrainingWindowClosed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WINDOWS[] = {

 // content:
       8,       // revision
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
       3,    1,   95,    2, 0x08 /* Private */,
       5,    1,   98,    2, 0x08 /* Private */,
       7,    0,  101,    2, 0x08 /* Private */,
       8,    0,  102,    2, 0x08 /* Private */,
       9,    0,  103,    2, 0x08 /* Private */,
      10,    0,  104,    2, 0x08 /* Private */,
      11,    0,  105,    2, 0x08 /* Private */,
      12,    0,  106,    2, 0x08 /* Private */,
      13,    0,  107,    2, 0x08 /* Private */,
      14,    0,  108,    2, 0x08 /* Private */,
      15,    0,  109,    2, 0x08 /* Private */,
      16,    0,  110,    2, 0x08 /* Private */,
      17,    0,  111,    2, 0x08 /* Private */,
      18,    0,  112,    2, 0x08 /* Private */,
      19,    0,  113,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    6,
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

void WINDOWS::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WINDOWS *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SetRegisterWindow(); break;
        case 1: _t->SetLoginValue((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->SetPasswordValue((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->SendRegistrationDataToDB(); break;
        case 4: _t->SetSignInWindow(); break;
        case 5: _t->SendSignInDataToDB(); break;
        case 6: _t->SignInButBackClicked(); break;
        case 7: _t->SetPrintWindow(); break;
        case 8: _t->PrintWindowButBackClicked(); break;
        case 9: _t->SetHomeWindow(); break;
        case 10: _t->HomeButPrintSpeedClicked(); break;
        case 11: _t->HomeButReactionSpeedClicked(); break;
        case 12: _t->SetCreateTrainingWindow(); break;
        case 13: _t->SetReactionSpeedWindow(); break;
        case 14: _t->ReactionSpeedWindowClosed(); break;
        case 15: _t->CreateTrainingWindowClosed(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WINDOWS::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_WINDOWS.data,
    qt_meta_data_WINDOWS,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WINDOWS::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WINDOWS::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WINDOWS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int WINDOWS::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
