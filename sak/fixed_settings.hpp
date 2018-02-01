#ifndef FIXED_SETTINGS_HPP
#define FIXED_SETTINGS_HPP

class QString;

namespace sak
{
  //---------------------------------------------------------------------------
  // Fixed_Settings
  //---------------------------------------------------------------------------
  // Things that are needed in various places but don't change.
  struct Fixed_Settings
  {
    static QString application_name();
    static QString project_file_extension();
    static QString default_project_name();
    static QString default_project_location();
  };
}

#endif // FIXED_SETTINGS_HPP
