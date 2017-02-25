#include "common_data.hpp"

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

sak::Common_Data::Common_Data():
    m_name{},
    m_description{}
{}

sak::Common_Data::Common_Data(QString const& a_name, QString const& a_description):
    m_name{a_name},
    m_description{a_description}
{}

sak::Common_Data::~Common_Data() = default;

QString const& sak::Common_Data::cget_name() const
{
    return m_name;
}
QString const& sak::Common_Data::cget_description() const
{
    return m_description;
}

void sak::Common_Data::set_name(QString const& a_name)
{
    m_name = a_name;
}
void sak::Common_Data::set_description(QString const& a_description)
{
    m_description = a_description;
}
