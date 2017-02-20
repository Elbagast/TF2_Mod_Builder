#include "file.h"

//---------------------------------------------------------------------------
// File
//---------------------------------------------------------------------------
//
sak::File::File():
    m_common_data{}
{}


sak::File::File(QString const& a_name, QString const& a_description):
    m_common_data{a_name, a_description}
{}

sak::Common_Data& sak::File::get_common_data()
{
    return m_common_data;
}

sak::Common_Data const& sak::File::cget_common_data() const
{
    return m_common_data;
}
