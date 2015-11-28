#include "bad_attribute_type.h"


saklib::internal::Bad_Attribute_Type::Bad_Attribute_Type(String const& a_attempted_type, String const& a_actual_type):
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

saklib::internal::Bad_Attribute_Type::~Bad_Attribute_Type() = default;

char const* saklib::internal::Bad_Attribute_Type::what() const
{
    return m_what.c_str();
}

saklib::internal::String const& saklib::internal::Bad_Attribute_Type::get_attempted_type() const
{
    return m_attempted_type;
}

saklib::internal::String const& saklib::internal::Bad_Attribute_Type::get_actual_type() const
{
    return m_actual_type;
}
