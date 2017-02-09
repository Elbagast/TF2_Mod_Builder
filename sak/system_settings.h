#ifndef SYSTEM_SETTINGS_H
#define SYSTEM_SETTINGS_H

class QString;
#include <QString>

namespace sak
{
    class TF2_Settings{};
    class SFM_Settings{};
    //---------------------------------------------------------------------------
    // System_Settings
    //---------------------------------------------------------------------------
    // Settings that are used by the application that the user can change.

    //uh-oh. it's the dreaded data class...
    class System_Settings
    {
    public:
        // Create a settings object with the hard-coded default values.
        static System_Settings factory_default();

        QString const& default_project_location() const;
        void set_default_project_location(QString const& a_directory);

        QString const& get_tf2_location() const;
        void set_tf2_location(QString const& a_directory);

        QString const& get_sfm_location() const;
        void set_sfm_location(QString const& a_directory);

    private:
        QString m_default_project_location;
        QString m_tf2_location;
        QString m_sfm_location;
        TF2_Settings m_tf2_settings;
        SFM_Settings m_sfm_settings;
    };

    class Texture;
    // ok going to need to think about how to split up the tools.
    // Generic:

    class Thing_Data;
    class Thing_Maker
    {
    public:
        virtual ~Thing_Maker() = default;

        // Use the data to make the results i.e. compile
        virtual void make_thing(Thing_Data const& a_thing) = 0;
    };
}

#endif // SYSTEM_SETTINGS_H
