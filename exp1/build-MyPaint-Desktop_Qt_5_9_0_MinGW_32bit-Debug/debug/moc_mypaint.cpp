/****************************************************************************
** Meta object code from reading C++ file 'mypaint.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MyPaint/mypaint.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mypaint.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyPaint_t {
    QByteArrayData data[23];
    char stringdata0[170];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyPaint_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyPaint_t qt_meta_stringdata_MyPaint = {
    {
QT_MOC_LITERAL(0, 0, 7), // "MyPaint"
QT_MOC_LITERAL(1, 8, 7), // "SavePic"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 8), // "Ellipses"
QT_MOC_LITERAL(4, 26, 4), // "Line"
QT_MOC_LITERAL(5, 31, 5), // "Line1"
QT_MOC_LITERAL(6, 37, 5), // "Line2"
QT_MOC_LITERAL(7, 43, 5), // "Rects"
QT_MOC_LITERAL(8, 49, 7), // "Polygon"
QT_MOC_LITERAL(9, 57, 4), // "Seed"
QT_MOC_LITERAL(10, 62, 7), // "OpenPic"
QT_MOC_LITERAL(11, 70, 8), // "LineType"
QT_MOC_LITERAL(12, 79, 9), // "LineType5"
QT_MOC_LITERAL(13, 89, 9), // "LineType7"
QT_MOC_LITERAL(14, 99, 9), // "ColorType"
QT_MOC_LITERAL(15, 109, 10), // "ColorType1"
QT_MOC_LITERAL(16, 120, 10), // "ColorType2"
QT_MOC_LITERAL(17, 131, 3), // "Cut"
QT_MOC_LITERAL(18, 135, 4), // "Move"
QT_MOC_LITERAL(19, 140, 9), // "Setcenter"
QT_MOC_LITERAL(20, 150, 5), // "Scale"
QT_MOC_LITERAL(21, 156, 6), // "Rotate"
QT_MOC_LITERAL(22, 163, 6) // "Bezier"

    },
    "MyPaint\0SavePic\0\0Ellipses\0Line\0Line1\0"
    "Line2\0Rects\0Polygon\0Seed\0OpenPic\0"
    "LineType\0LineType5\0LineType7\0ColorType\0"
    "ColorType1\0ColorType2\0Cut\0Move\0Setcenter\0"
    "Scale\0Rotate\0Bezier"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyPaint[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  119,    2, 0x0a /* Public */,
       3,    0,  120,    2, 0x0a /* Public */,
       4,    0,  121,    2, 0x0a /* Public */,
       5,    0,  122,    2, 0x0a /* Public */,
       6,    0,  123,    2, 0x0a /* Public */,
       7,    0,  124,    2, 0x0a /* Public */,
       8,    0,  125,    2, 0x0a /* Public */,
       9,    0,  126,    2, 0x0a /* Public */,
      10,    0,  127,    2, 0x0a /* Public */,
      11,    0,  128,    2, 0x0a /* Public */,
      12,    0,  129,    2, 0x0a /* Public */,
      13,    0,  130,    2, 0x0a /* Public */,
      14,    0,  131,    2, 0x0a /* Public */,
      15,    0,  132,    2, 0x0a /* Public */,
      16,    0,  133,    2, 0x0a /* Public */,
      17,    0,  134,    2, 0x0a /* Public */,
      18,    0,  135,    2, 0x0a /* Public */,
      19,    0,  136,    2, 0x0a /* Public */,
      20,    0,  137,    2, 0x0a /* Public */,
      21,    0,  138,    2, 0x0a /* Public */,
      22,    0,  139,    2, 0x0a /* Public */,

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MyPaint::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyPaint *_t = static_cast<MyPaint *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SavePic(); break;
        case 1: _t->Ellipses(); break;
        case 2: _t->Line(); break;
        case 3: _t->Line1(); break;
        case 4: _t->Line2(); break;
        case 5: _t->Rects(); break;
        case 6: _t->Polygon(); break;
        case 7: _t->Seed(); break;
        case 8: _t->OpenPic(); break;
        case 9: _t->LineType(); break;
        case 10: _t->LineType5(); break;
        case 11: _t->LineType7(); break;
        case 12: _t->ColorType(); break;
        case 13: _t->ColorType1(); break;
        case 14: _t->ColorType2(); break;
        case 15: _t->Cut(); break;
        case 16: _t->Move(); break;
        case 17: _t->Setcenter(); break;
        case 18: _t->Scale(); break;
        case 19: _t->Rotate(); break;
        case 20: _t->Bezier(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MyPaint::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MyPaint.data,
      qt_meta_data_MyPaint,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MyPaint::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyPaint::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyPaint.stringdata0))
        return static_cast<void*>(const_cast< MyPaint*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MyPaint::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 21;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
