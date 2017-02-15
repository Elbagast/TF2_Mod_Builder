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
        Component():
            m_name{},
            m_description{}
        {}
        Component(QString const& a_name, QString const& a_description):
            m_name{a_name},
            m_description{a_description}
        {}

        QString const& cget_name() const { return m_name; }
        QString const& cget_description() const { return m_description; }

        void set_name(QString const& a_name) { m_name = a_name; }
        void set_description(QString const& a_description) { m_description = a_description; }
    private:
        QString m_name;
        QString m_description;
    };
    class File : public Component
    {
    public:
        File():
            Component()
        {}
        File(QString const& a_name, QString const& a_description):
            Component(a_name, a_description)
        {}
    };
}

#endif // FILE_H
