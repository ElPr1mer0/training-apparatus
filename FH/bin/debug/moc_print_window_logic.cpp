/****************************************************************************
** Meta object code from reading C++ file 'print_window_logic.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../print_window_logic.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'print_window_logic.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PRINT_WINDOW_LOGIC_t {
    QByteArrayData data[20];
    char stringdata0[328];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PRINT_WINDOW_LOGIC_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PRINT_WINDOW_LOGIC_t qt_meta_stringdata_PRINT_WINDOW_LOGIC = {
    {
QT_MOC_LITERAL(0, 0, 18), // "PRINT_WINDOW_LOGIC"
QT_MOC_LITERAL(1, 19, 27), // "GetCreateTrainingComponents"
QT_MOC_LITERAL(2, 47, 0), // ""
QT_MOC_LITERAL(3, 48, 12), // "QPushButton*"
QT_MOC_LITERAL(4, 61, 10), // "QLineEdit*"
QT_MOC_LITERAL(5, 72, 7), // "QLabel*"
QT_MOC_LITERAL(6, 80, 13), // "QTextBrowser*"
QT_MOC_LITERAL(7, 94, 17), // "ButAddFileClicked"
QT_MOC_LITERAL(8, 112, 17), // "ButAddWordClicked"
QT_MOC_LITERAL(9, 130, 24), // "ButCreateTrainingClicked"
QT_MOC_LITERAL(10, 155, 24), // "ButDeleteLastWordClicked"
QT_MOC_LITERAL(11, 180, 20), // "ButDeleteWordClicked"
QT_MOC_LITERAL(12, 201, 18), // "LdFieldTextChanged"
QT_MOC_LITERAL(13, 220, 15), // "ButStartClicked"
QT_MOC_LITERAL(14, 236, 22), // "ButLoadTrainingClicked"
QT_MOC_LITERAL(15, 259, 30), // "BoxTrainingCurrentIndexChanged"
QT_MOC_LITERAL(16, 290, 5), // "IsWin"
QT_MOC_LITERAL(17, 296, 6), // "OnTime"
QT_MOC_LITERAL(18, 303, 11), // "OnPauseTime"
QT_MOC_LITERAL(19, 315, 12) // "OnUpdateData"

    },
    "PRINT_WINDOW_LOGIC\0GetCreateTrainingComponents\0"
    "\0QPushButton*\0QLineEdit*\0QLabel*\0"
    "QTextBrowser*\0ButAddFileClicked\0"
    "ButAddWordClicked\0ButCreateTrainingClicked\0"
    "ButDeleteLastWordClicked\0ButDeleteWordClicked\0"
    "LdFieldTextChanged\0ButStartClicked\0"
    "ButLoadTrainingClicked\0"
    "BoxTrainingCurrentIndexChanged\0IsWin\0"
    "OnTime\0OnPauseTime\0OnUpdateData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PRINT_WINDOW_LOGIC[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,   11,   84,    2, 0x0a /* Public */,
       7,    0,  107,    2, 0x08 /* Private */,
       8,    0,  108,    2, 0x08 /* Private */,
       9,    0,  109,    2, 0x08 /* Private */,
      10,    0,  110,    2, 0x08 /* Private */,
      11,    0,  111,    2, 0x08 /* Private */,
      12,    1,  112,    2, 0x08 /* Private */,
      13,    0,  115,    2, 0x08 /* Private */,
      14,    0,  116,    2, 0x08 /* Private */,
      15,    1,  117,    2, 0x08 /* Private */,
      16,    0,  120,    2, 0x08 /* Private */,
      17,    0,  121,    2, 0x08 /* Private */,
      18,    0,  122,    2, 0x08 /* Private */,
      19,    0,  123,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 4, 0x80000000 | 4, 0x80000000 | 4, 0x80000000 | 4, 0x80000000 | 5, 0x80000000 | 6,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PRINT_WINDOW_LOGIC::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PRINT_WINDOW_LOGIC *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->GetCreateTrainingComponents((*reinterpret_cast< QPushButton*(*)>(_a[1])),(*reinterpret_cast< QPushButton*(*)>(_a[2])),(*reinterpret_cast< QPushButton*(*)>(_a[3])),(*reinterpret_cast< QPushButton*(*)>(_a[4])),(*reinterpret_cast< QPushButton*(*)>(_a[5])),(*reinterpret_cast< QLineEdit*(*)>(_a[6])),(*reinterpret_cast< QLineEdit*(*)>(_a[7])),(*reinterpret_cast< QLineEdit*(*)>(_a[8])),(*reinterpret_cast< QLineEdit*(*)>(_a[9])),(*reinterpret_cast< QLabel*(*)>(_a[10])),(*reinterpret_cast< QTextBrowser*(*)>(_a[11]))); break;
        case 1: _t->ButAddFileClicked(); break;
        case 2: _t->ButAddWordClicked(); break;
        case 3: _t->ButCreateTrainingClicked(); break;
        case 4: _t->ButDeleteLastWordClicked(); break;
        case 5: _t->ButDeleteWordClicked(); break;
        case 6: _t->LdFieldTextChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->ButStartClicked(); break;
        case 8: _t->ButLoadTrainingClicked(); break;
        case 9: _t->BoxTrainingCurrentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->IsWin(); break;
        case 11: _t->OnTime(); break;
        case 12: _t->OnPauseTime(); break;
        case 13: _t->OnUpdateData(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PRINT_WINDOW_LOGIC::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_PRINT_WINDOW_LOGIC.data,
    qt_meta_data_PRINT_WINDOW_LOGIC,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PRINT_WINDOW_LOGIC::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PRINT_WINDOW_LOGIC::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PRINT_WINDOW_LOGIC.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PRINT_WINDOW_LOGIC::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
