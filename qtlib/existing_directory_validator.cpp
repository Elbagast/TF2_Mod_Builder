#include "existing_directory_validator.h"

#include <QDir>

namespace
{
    // is this an existing directory?
    bool is_existing_directory(QString const& a_string)
    {
        return QDir(a_string).exists();
    }

}


//---------------------------------------------------------------------------
// Existing_Directory_Validator
//---------------------------------------------------------------------------
// Determines whether a QString is currently existing directory or not.

// Special 6
//============================================================
qtlib::Existing_Directory_Validator::~Existing_Directory_Validator() = default;

// QValidator overrides
//============================================================
//void qtlib::Directory_Name_Validator::fixup(QString& a_input) const;

QValidator::State qtlib::Existing_Directory_Validator::validate(QString& a_input, int& /*a_position*/) const
{
    if (is_existing_directory(a_input))
    {
        return QValidator::Acceptable;
    }
    else
    {
        return QValidator::Invalid;
    }
}
