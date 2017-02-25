#include "file.hpp"

//---------------------------------------------------------------------------
// File
//---------------------------------------------------------------------------
//
sak::File::File():
    Common_Data{},
    m_buildpath{},
    m_sourcepath{}
{}

sak::File::File(QString const& a_name, QString const& a_description):
    Common_Data{a_name, a_description},
    m_buildpath{},
    m_sourcepath{}
{}

sak::File::~File() = default;


QString const& sak::File::cget_buildpath() const
{
    return m_buildpath;
}

QString const& sak::File::cget_sourcepath() const
{
    return m_sourcepath;
}

void sak::File::set_buildpath(QString const& a_buildpath)
{
    m_buildpath = a_buildpath;
}

void sak::File::set_sourcepath(QString const& a_sourcepath)
{
    m_sourcepath = a_sourcepath;
}
