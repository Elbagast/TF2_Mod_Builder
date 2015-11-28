#ifndef QVARIANT_OPERATIONS
#define QVARIANT_OPERATIONS

#include "../types.h"
#include <QVariant>

namespace saklib
{
    namespace Qtlib
    {
        inline QVariant to_QVariant(Bool value)                 { return QVariant(value); }
        inline QVariant to_QVariant(Int value)                  { return QVariant(value); }
        inline QVariant to_QVariant(Double value)               { return QVariant(value); }
        inline QVariant to_QVariant(String const& value)        { return QVariant(value.c_str()); }
        inline QVariant to_QVariant(Path const& value)          { return QVariant(value.string().c_str()); }
        //inline QVariant to_QVariant(ElementID const& value)     { return QVariant(); } // hmmmmm

        inline Bool to_Bool(QVariant const& value)              { return value.toBool(); }
        inline Int to_Int(QVariant const& value)                { return value.toInt(); }
        inline Double to_Double(QVariant const& value)          { return value.toDouble(); }
        inline String to_String(QVariant const& value)          { return value.toString().toStdString(); }
        inline Path to_Path(QVariant const& value)              { return Path(to_String(value)); }
        //inline ElementID to_String(QVariant const& value)       { return ElementID(); }

    } // namespace Qtlib
} // namespace saklib

#endif // QVARIANT_OPERATIONS

