/****************************************************************************
** Meta object code from reading C++ file 'samplingthread.h'
**
** Created: Tue Dec 18 21:58:12 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../samplingthread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'samplingthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SamplingThread[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x0a,
      37,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SamplingThread[] = {
    "SamplingThread\0\0setAmplitude(double)\0"
    "setFrequency(double)\0"
};

void SamplingThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SamplingThread *_t = static_cast<SamplingThread *>(_o);
        switch (_id) {
        case 0: _t->setAmplitude((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->setFrequency((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SamplingThread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SamplingThread::staticMetaObject = {
    { &QwtSamplingThread::staticMetaObject, qt_meta_stringdata_SamplingThread,
      qt_meta_data_SamplingThread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SamplingThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SamplingThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SamplingThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SamplingThread))
        return static_cast<void*>(const_cast< SamplingThread*>(this));
    return QwtSamplingThread::qt_metacast(_clname);
}

int SamplingThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QwtSamplingThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
