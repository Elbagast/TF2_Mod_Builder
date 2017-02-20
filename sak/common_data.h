#ifndef SAK_COMMON_DATA_H
#define SAK_COMMON_DATA_H

#include <QString>

namespace sak
{
    //---------------------------------------------------------------------------
    // Common_Data
    //---------------------------------------------------------------------------
    // This class contains all of the data that is always present in Project
    // components.
    //
    // The name is maintained as being unique among all objects of a given
    // component type within a Project regardless of whether it is automatically
    // generated or supplied by the user.
    //
    // Description is always user supplied. Its purpose is as a helper identifier
    // within the Project, and is used as the Outliner tooltip.

    class Common_Data
    {
    public:
        Common_Data();
        explicit Common_Data(QString const& a_name, QString const& a_description = QString());

        QString const& cget_name() const;
        QString const& cget_description() const;

        void set_name(QString const& a_name);
        void set_description(QString const& a_description);
    private:
        QString m_name;
        QString m_description;
    };
}

#endif // SAK_COMMON_DATA_H
