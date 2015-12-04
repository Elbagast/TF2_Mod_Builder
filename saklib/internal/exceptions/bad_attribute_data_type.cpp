#include "bad_attribute_data_type.h"

//---------------------------------------------------------------------------
// Bad_Attribute_Data_Type
//---------------------------------------------------------------------------

// Special 6
//============================================================
saklib::internal::Bad_Attribute_Data_Type::Bad_Attribute_Data_Type():
    std::bad_cast(),
    m_attempted_type(),
    m_actual_type(),
    m_what()
{
    m_what += "Bad_Attribute_Type";
}

saklib::internal::Bad_Attribute_Data_Type::Bad_Attribute_Data_Type(std::string const& a_attempted_type):
    std::bad_cast(),
    m_attempted_type(a_attempted_type),
    m_actual_type(),
    m_what()
{
    m_what += "Bad_Attribute_Type attempted=\"";
    m_what += m_attempted_type;
    m_what += "\"";
}


saklib::internal::Bad_Attribute_Data_Type::Bad_Attribute_Data_Type(std::string const& a_attempted_type, std::string const& a_actual_type):
    std::bad_cast(),
    m_attempted_type(a_attempted_type),
    m_actual_type(a_actual_type),
    m_what()
{
    m_what += "Bad_Attribute_Type attempted=\"";
    m_what += m_attempted_type;
    m_what += "\" actual=\"";
    m_what += m_attempted_type;
    m_what += "\"";
}

saklib::internal::Bad_Attribute_Data_Type::~Bad_Attribute_Data_Type() = default;

// Interface
//============================================================
char const* saklib::internal::Bad_Attribute_Data_Type::what() const
{
    return m_what.c_str();
}

std::string const& saklib::internal::Bad_Attribute_Data_Type::get_attempted_type() const
{
    return m_attempted_type;
}

std::string const& saklib::internal::Bad_Attribute_Data_Type::get_actual_type() const
{
    return m_actual_type;
}
