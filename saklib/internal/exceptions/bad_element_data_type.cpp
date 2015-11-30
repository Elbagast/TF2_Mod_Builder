#include "bad_element_data_type.h"

//---------------------------------------------------------------------------
// Bad_Element_Data_Type
//---------------------------------------------------------------------------

// Special 6
//============================================================
saklib::internal::Bad_Element_Data_Type::Bad_Element_Data_Type(std::string const& a_type):
    std::out_of_range(nullptr),
    m_type(a_type),
    m_what()
{
    m_what += "Bad_Element_Type type=\"";
    m_what += m_type;
    m_what += "\"";
}

saklib::internal::Bad_Element_Data_Type::~Bad_Element_Data_Type() = default;

// Interface
//============================================================
char const* saklib::internal::Bad_Element_Data_Type::what() const
{
    return m_what.c_str();
}

std::string const& saklib::internal::Bad_Element_Data_Type::get_type() const
{
    return m_type;
}
