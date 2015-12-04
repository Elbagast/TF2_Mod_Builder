#include "attribute_data_handle_bool.h"

#include "attribute_data_bool.h"

// Special 6
//============================================================
saklib::internal::Attribute_Data_Handle_Bool::Attribute_Data_Handle_Bool():
    m_reference_counter(),
    m_attribute_index(0)
{
}

saklib::internal::Attribute_Data_Handle_Bool::Attribute_Data_Handle_Bool(reference_counter_type const& a_reference_counter, std::size_t a_index):
    m_reference_counter(a_reference_counter),
    m_attribute_index(a_index)
{
}

saklib::internal::Attribute_Data_Handle_Bool::Attribute_Data_Handle_Bool(reference_counter_type&& a_reference_counter, std::size_t a_index):
    m_reference_counter(std::move(a_reference_counter)),
    m_attribute_index(a_index)
{
}

saklib::internal::Attribute_Data_Handle_Bool::~Attribute_Data_Handle_Bool() = default;

saklib::internal::Attribute_Data_Handle_Bool::Attribute_Data_Handle_Bool(Attribute_Data_Handle_Bool const& other) = default;

saklib::internal::Attribute_Data_Handle_Bool& saklib::internal::Attribute_Data_Handle_Bool::operator=(Attribute_Data_Handle_Bool const& other) = default;

saklib::internal::Attribute_Data_Handle_Bool::Attribute_Data_Handle_Bool(Attribute_Data_Handle_Bool && other):
    m_reference_counter(std::move(other.m_reference_counter)),
    m_attribute_index(std::move(other.m_attribute_index))
{
    other.m_attribute_index = 0;
}

saklib::internal::Attribute_Data_Handle_Bool& saklib::internal::Attribute_Data_Handle_Bool::operator=(Attribute_Data_Handle_Bool && other)
{
    if (&other != this)
    {
        m_reference_counter = std::move(other.m_reference_counter);
        m_attribute_index = std::move(other.m_attribute_index);

        other.m_attribute_index = 0;
    }
    return *this;
}

// Interface
//============================================================
bool saklib::internal::Attribute_Data_Handle_Bool::is_valid() const
{
    return m_reference_counter.is_valid();
}

bool saklib::internal::Attribute_Data_Handle_Bool::is_null() const
{
    return m_reference_counter.is_null();
}

saklib::internal::Attribute_Data_Handle_Bool::handle_type saklib::internal::Attribute_Data_Handle_Bool::cget_element_handle() const
{
    return m_reference_counter.cget_handle();
}

std::size_t saklib::internal::Attribute_Data_Handle_Bool::cget_element_reference_count() const
{
    return cget_storage().cget_reference_count(m_reference_counter.cget_handle());
}

std::size_t saklib::internal::Attribute_Data_Handle_Bool::cget_attribute_index() const
{
    return m_attribute_index;
}

// Attribute_Data Wrapper Interface
//============================================================
std::string const& saklib::internal::Attribute_Data_Handle_Bool::cget_name() const
{
    return cget_attribute().cget_name();
}

std::string const& saklib::internal::Attribute_Data_Handle_Bool::cget_type() const
{
    return cget_attribute().cget_type();
}

std::string saklib::internal::Attribute_Data_Handle_Bool::cget_value_string() const
{
    return cget_attribute().cget_value_string();
}

bool saklib::internal::Attribute_Data_Handle_Bool::cget_value() const
{
    return cget_attribute().cget_value();
}

bool saklib::internal::Attribute_Data_Handle_Bool::can_set_value_to(bool a_value) const
{
    return cget_attribute().can_set_value_to(a_value);
}

bool saklib::internal::Attribute_Data_Handle_Bool::try_set_value(bool a_value)
{
    return get_attribute().try_set_value(a_value);
}

void saklib::internal::Attribute_Data_Handle_Bool::set_value(bool a_value)
{
    get_attribute().set_value(a_value);
}

// Comparison Operators
//============================================================

bool saklib::internal::Attribute_Data_Handle_Bool::operator==(Attribute_Data_Handle_Bool const& rhs)
{
    return (m_reference_counter == rhs.m_reference_counter) && (m_attribute_index == rhs.m_attribute_index);
}

bool saklib::internal::Attribute_Data_Handle_Bool::operator!=(Attribute_Data_Handle_Bool const& rhs)
{
    return (m_reference_counter != rhs.m_reference_counter) && (m_attribute_index != rhs.m_attribute_index);
}

bool saklib::internal::Attribute_Data_Handle_Bool::operator<(Attribute_Data_Handle_Bool const& rhs)
{
    return (m_reference_counter < rhs.m_reference_counter) && (m_attribute_index < rhs.m_attribute_index);
}

bool saklib::internal::Attribute_Data_Handle_Bool::operator>(Attribute_Data_Handle_Bool const& rhs)
{
    return (m_reference_counter > rhs.m_reference_counter) && (m_attribute_index > rhs.m_attribute_index);
}

bool saklib::internal::Attribute_Data_Handle_Bool::operator<=(Attribute_Data_Handle_Bool const& rhs)
{
    return (m_reference_counter <= rhs.m_reference_counter) && (m_attribute_index <= rhs.m_attribute_index);
}

bool saklib::internal::Attribute_Data_Handle_Bool::operator>=(Attribute_Data_Handle_Bool const& rhs)
{
    return (m_reference_counter >= rhs.m_reference_counter) && (m_attribute_index >= rhs.m_attribute_index);
}
/*
// Comparison Operators to Untyped Handle
//============================================================
bool saklib::internal::Attribute_Data_Handle_Bool::operator==(Attribute_Data_Handle const& rhs)
{
    return m_attribute_handle == rhs;
}

bool saklib::internal::Attribute_Data_Handle_Bool::operator!=(Attribute_Data_Handle const& rhs)
{
    return m_attribute_handle != rhs;
}
*/
// Comparison Operators for compare to the null handle
//============================================================
bool saklib::internal::Attribute_Data_Handle_Bool::operator==(Null_Handle_Type const& )
{
    return is_null();
}

bool saklib::internal::Attribute_Data_Handle_Bool::operator!=(Null_Handle_Type const& )
{
    return is_valid();
}

// Protected Helpers
//============================================================
saklib::internal::Attribute_Data_Handle_Bool::storage_type& saklib::internal::Attribute_Data_Handle_Bool::get_storage()
{
    if (is_valid())
    {
        return *(m_reference_counter.get_storage());
    }
    else
    {
        throw Bad_Data_Handle();
    }
}

saklib::internal::Attribute_Data_Handle_Bool::storage_type const& saklib::internal::Attribute_Data_Handle_Bool::cget_storage() const
{
    if (is_valid())
    {
        return *(m_reference_counter.cget_storage());
    }
    else
    {
        throw Bad_Data_Handle();
    }
}

saklib::internal::Element_Data& saklib::internal::Attribute_Data_Handle_Bool::get_element()
{
    return get_storage().get_data(m_reference_counter.cget_handle());
}

saklib::internal::Element_Data const& saklib::internal::Attribute_Data_Handle_Bool::cget_element() const
{
    return cget_storage().cget_data(m_reference_counter.cget_handle());
}

saklib::internal::Attribute_Data_Bool& saklib::internal::Attribute_Data_Handle_Bool::get_attribute()
{
    return get_element().get_attribute_at(m_attribute_index).get_bool();
}

saklib::internal::Attribute_Data_Bool const& saklib::internal::Attribute_Data_Handle_Bool::cget_attribute() const
{
    return cget_element().cget_attribute_at(m_attribute_index).cget_bool();
}