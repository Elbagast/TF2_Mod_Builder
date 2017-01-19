#include "bad_data_handle.h"

//---------------------------------------------------------------------------
// Bad_Element_Data_Type
//---------------------------------------------------------------------------

// Special 6
//============================================================
saklib::internal::Bad_Data_Handle::Bad_Data_Handle():
    std::out_of_range("Bad_Data_Handle"),
    m_type(),
    m_what("Bad_Data_Handle"),
    m_value()
{
}

saklib::internal::Bad_Data_Handle::Bad_Data_Handle(std::string const& a_type, Integer_ID_Value_Type a_value):
    std::out_of_range("Bad_Data_Handle"),
    m_type(a_type),
    m_what(),
    m_value(a_value)
{
    m_what += "Bad_Data_Handle type=\"";
    m_what += m_type;
    m_what += "\" value=\"";
    m_what += std::to_string(m_value);
    m_what += "\"";
}

saklib::internal::Bad_Data_Handle::~Bad_Data_Handle() = default;

// Interface
//============================================================
char const* saklib::internal::Bad_Data_Handle::what() const
{
    return m_what.c_str();
}

std::string const& saklib::internal::Bad_Data_Handle::get_type() const
{
    return m_type;
}

saklib::internal::Integer_ID_Value_Type saklib::internal::Bad_Data_Handle::cget_handle_value() const
{
    return m_value;
}
