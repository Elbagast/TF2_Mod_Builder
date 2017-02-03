#include "directory_name_validator.h"

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
        static QString const s_ms_reserved{u8"<>:\"/\\|?*"};
        for (auto const& l_char : a_string)
        {
            // test for invalids
            if (l_char.isNull() // char is null
                || !l_char.isPrint() // char is not printable
                || has_char(s_ms_reserved, l_char) // char is in the reserved list
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
