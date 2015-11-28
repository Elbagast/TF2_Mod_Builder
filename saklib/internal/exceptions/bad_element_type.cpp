#include "bad_element_type.h"


saklib::internal::Bad_Element_Type::Bad_Element_Type(String const& a_type):
    std::out_of_range(nullptr),
    m_type(a_type),
    m_what()
{
    m_what += "Bad_Element_Type type=\"";
    m_what += m_type;
    m_what += "\"";
}

saklib::internal::Bad_Element_Type::~Bad_Element_Type() = default;

char const* saklib::internal::Bad_Element_Type::what() const
{
    return m_what.c_str();
}

saklib::internal::String const& saklib::internal::Bad_Element_Type::get_type() const
{
    return m_type;
}
