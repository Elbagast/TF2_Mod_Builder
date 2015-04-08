#ifndef QSTRING_OPERATIONS_H
#define QSTRING_OPERATIONS_H

#include "../types.h"
#include <QString>

namespace Saklib
{
    namespace Qtlib
    {
        inline QString to_QString(size_type value)          { return QString(Saklib::to_String(value).c_str()); }

        inline QString to_QString(Bool value)               { return QString(Saklib::to_String(value).c_str()); }
        inline QString to_QString(Int value)                { return QString(Saklib::to_String(value).c_str()); }
        inline QString to_QString(Double value)             { return QString(Saklib::to_String(value).c_str()); }
        inline QString to_QString(String const& value)      { return QString(value.c_str()); }
        inline QString to_QString(Path const& value)        { return QString(value.string().c_str()); }
        //inline QString to_QString(ElementID const& value) { return QString(to_String(value).c_str()); }

        inline Bool to_Bool(QString const& value)           { return value.toInt() > 0 ? true : false; }
        inline Int to_Int(QString const& value)             { return value.toInt(); }
        inline Double to_Double(QString const& value)       { return value.toDouble(); }
        inline String to_String(QString const& value)       { return value.toStdString(); }
        inline Path to_Path(QString const& value)           { return Path(value.toStdString()); }
        //inline ElementID to_ElementID(QVariant const& value)  { return to_ElementID(value.toStdString()); }

    } // namespace Qtlib
} // namespace Saklib

#endif // QSTRING_OPERATIONS_H

