#include "file.h"


sak::Component::Component():
    m_name{},
    m_description{}
{}
sak::Component::Component(QString const& a_name, QString const& a_description):
    m_name{a_name},
    m_description{a_description}
{}

QString const& sak::Component::cget_name() const
{
    return m_name;
}
QString const& sak::Component::cget_description() const
{
    return m_description;
}

void sak::Component::set_name(QString const& a_name)
{
    m_name = a_name;
}
void sak::Component::set_description(QString const& a_description)
{
    m_description = a_description;
}
sak::File::File():
    Component()
{}
sak::File::File(QString const& a_name, QString const& a_description):
    Component(a_name, a_description)
{}

