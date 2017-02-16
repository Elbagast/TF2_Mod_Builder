#ifndef FILE_H
#define FILE_H

#include "fwd_file.h"

#include <QString>

namespace sak
{
    //---------------------------------------------------------------------------
    // Component
    //---------------------------------------------------------------------------
    // temp classes
    class Component
    {
    public:
        Component();
        explicit Component(QString const& a_name, QString const& a_description = QString());

        QString const& cget_name() const;
        QString const& cget_description() const;

        void set_name(QString const& a_name);
        void set_description(QString const& a_description);
    private:
        QString m_name;
        QString m_description;
    };
    class File : public Component
    {
    public:
        File();
        explicit File(QString const& a_name, QString const& a_description = QString());
    };
}

#endif // FILE_H
