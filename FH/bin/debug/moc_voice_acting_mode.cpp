/****************************************************************************
** Meta object code from reading C++ file 'voice_acting_mode.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../voice_acting_mode.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'voice_acting_mode.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VOICE_ACTING_MODE_t {
    QByteArrayData data[14];
    char stringdata0[142];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VOICE_ACTING_MODE_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VOICE_ACTING_MODE_t qt_meta_stringdata_VOICE_ACTING_MODE = {
    {
QT_MOC_LITERAL(0, 0, 17), // "VOICE_ACTING_MODE"
QT_MOC_LITERAL(1, 18, 22), // "SetVoiceSettingsWindow"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 5), // "Speak"
QT_MOC_LITERAL(4, 48, 4), // "Stop"
QT_MOC_LITERAL(5, 53, 8), // "SetSpeed"
QT_MOC_LITERAL(6, 62, 5), // "speed"
QT_MOC_LITERAL(7, 68, 9), // "SetVolume"
QT_MOC_LITERAL(8, 78, 6), // "volume"
QT_MOC_LITERAL(9, 85, 11), // "SetLanguage"
QT_MOC_LITERAL(10, 97, 8), // "language"
QT_MOC_LITERAL(11, 106, 13), // "LocaleChanged"
QT_MOC_LITERAL(12, 120, 6), // "locale"
QT_MOC_LITERAL(13, 127, 14) // "ButTestClicked"

    },
    "VOICE_ACTING_MODE\0SetVoiceSettingsWindow\0"
    "\0Speak\0Stop\0SetSpeed\0speed\0SetVolume\0"
    "volume\0SetLanguage\0language\0LocaleChanged\0"
    "locale\0ButTestClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VOICE_ACTING_MODE[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a /* Public */,
       3,    0,   55,    2, 0x0a /* Public */,
       4,    0,   56,    2, 0x0a /* Public */,
       5,    1,   57,    2, 0x0a /* Public */,
       7,    1,   60,    2, 0x0a /* Public */,
       9,    1,   63,    2, 0x0a /* Public */,
      11,    1,   66,    2, 0x0a /* Public */,
      13,    0,   69,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::QLocale,   12,
    QMetaType::Void,

       0        // eod
};

void VOICE_ACTING_MODE::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VOICE_ACTING_MODE *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SetVoiceSettingsWindow(); break;
        case 1: _t->Speak(); break;
        case 2: _t->Stop(); break;
        case 3: _t->SetSpeed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->SetVolume((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->SetLanguage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->LocaleChanged((*reinterpret_cast< const QLocale(*)>(_a[1]))); break;
        case 7: _t->ButTestClicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VOICE_ACTING_MODE::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_VOICE_ACTING_MODE.data,
    qt_meta_data_VOICE_ACTING_MODE,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VOICE_ACTING_MODE::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VOICE_ACTING_MODE::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VOICE_ACTING_MODE.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int VOICE_ACTING_MODE::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
