#include "directory_name_validator.hpp"

namespace
{
    // is this string a valid directory name?
    // For sanity's sake we will apply the following constraints:
    /*
    - No leading spaces
    - MSDN reserved <>:"/\|?*
    - NUL
    - No control characters
    */
    // assuming not emp

    QString const c_ms_reserved{u8"<>:\"/\\|?*[]"};

    bool has_char(QString const& a_string, QChar a_char)
    {
        for (auto const& l_char : a_string)
        {
            if (l_char == a_char)
            {
                return true;
            }
        }
        return false;
    }

    bool has_invalid_char(QString const& a_string)
    {
        for (auto const& l_char : a_string)
        {
            // test for invalids
            if (l_char.isNull() // char is null
                || !l_char.isPrint() // char is not printable
                || has_char(c_ms_reserved, l_char) // char is in the reserved list
                )
            {
                return true;
            }
        }
        return false;
    }

    bool is_valid_directory_name(QString const& a_string)
    {
        if (!a_string.isEmpty() // not empty
            && !a_string.at(0).isSpace() // no leading space
            && a_string != "." // not this
            && a_string != ".." // not  this
            && !has_invalid_char(a_string) // no chars we don't want
            )
        {
            return true;
        }
        else
        {
            return false;
        }
    }



}

//---------------------------------------------------------------------------
// Directory_Name_Validator
//---------------------------------------------------------------------------
// Determines whether a QString is a valid directory name or not.

// Special 6
//============================================================
qtlib::Directory_Name_Validator::~Directory_Name_Validator() = default;

// QValidator overrides
//============================================================
//void qtlib::Directory_Name_Validator::fixup(QString& a_input) const;

QValidator::State qtlib::Directory_Name_Validator::validate(QString& a_input, int& /*a_position*/) const
{
    if (is_valid_directory_name(a_input))
    {
        return QValidator::Acceptable;
    }
    else
    {
        return QValidator::Invalid;
    }
}

// Interface
//============================================================
// Produce a string that describes the first error found in string that
// stops it from being valid. String is empty if no errors.
QString qtlib::Directory_Name_Validator::first_error(QString& a_string)
{
    if (a_string.isEmpty())
    {
        return QString(u8"Project name cannot be nothing.");
    }
    else if (a_string.at(0).isSpace())
    {
        return QString(u8"Project name cannot have any leading spaces.");
    }
    else if (a_string == u8".")
    {
        return QString(u8"Project name cannot be \".\"");
    }
    else if (a_string == u8"..")
    {
        return QString(u8"Project name cannot be \".\"");
    }
    else
    {
        for (auto const& l_char : a_string)
        {
            if (l_char.isNull() // char is null
                || !l_char.isPrint() // char is not printable
                )
            {
                return QString(u8"Project name cannot contain control characters.");
            }
            else if (has_char(c_ms_reserved, l_char)) // char is in the reserved list
            {
                return QString(u8"Project name cannot contain the character \"").append(l_char).append(u8"\"");
            }
        }
        return QString();
    }
}
