#include "fixed_settings.h"
#include <QStandardPaths>
#include <QDir>
//---------------------------------------------------------------------------
// Fixed_Settings
//---------------------------------------------------------------------------
// Things that are needed in various places but don't change.
// Strings are in ut8 format.

QString sak::Fixed_Settings::application_name()
{
    static QString const s_value{"TF2 Mod Builder"};
    return s_value;
}

QString sak::Fixed_Settings::project_file_extension()
{
    static QString const s_value{u8".sakpro"};
    return s_value;
}

QString sak::Fixed_Settings::default_project_name()
{
    static QString const s_value{u8"untitled"};
    return s_value;
}

namespace
{
    QString build_default_project_location()
    {
        QString l_result{QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)};
        l_result.append(QDir::separator());
        l_result.append(sak::Fixed_Settings::application_name());
        return l_result;
    }
}

QString sak::Fixed_Settings::default_project_location()
{
    //static QString const s_value{build_default_project_location()};
    static QString const s_value{u8"D:\\Temp\\sak"};
    return s_value;
}
