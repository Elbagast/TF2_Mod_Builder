#include "attribute_data_handle.h"

#ifndef SAKLIB_INTERNAL_ALL_ATTRIBUTE_DATA_HANDLE_H
#include "all_attribute_data_handle.h"
#endif

//---------------------------------------------------------------------------
// Attribute_Data_Handle
//---------------------------------------------------------------------------

// Special 6
//============================================================
saklib::internal::Attribute_Data_Handle::Attribute_Data_Handle():
    m_reference_counter(),
    m_attribute_index(0)
{
}

saklib::internal::Attribute_Data_Handle::Attribute_Data_Handle(reference_counter_type const& a_reference_counter, std::size_t a_index):
    m_reference_counter(a_reference_counter),
    m_attribute_index(a_index)
{
}

saklib::internal::Attribute_Data_Handle::Attribute_Data_Handle(reference_counter_type && a_reference_counter, std::size_t a_index):
    m_reference_counter(std::move(a_reference_counter)),
    m_attribute_index(a_index)
{
}

saklib::internal::Attribute_Data_Handle::~Attribute_Data_Handle() = default;

saklib::internal::Attribute_Data_Handle::Attribute_Data_Handle(Attribute_Data_Handle const& other) = default;
saklib::internal::Attribute_Data_Handle& saklib::internal::Attribute_Data_Handle::operator=(Attribute_Data_Handle const& other) = default;

saklib::internal::Attribute_Data_Handle::Attribute_Data_Handle(Attribute_Data_Handle && other):
    m_reference_counter(std::move(other.m_reference_counter)),
    m_attribute_index(std::move(other.m_attribute_index))
{
    other.m_attribute_index = 0;
}

saklib::internal::Attribute_Data_Handle& saklib::internal::Attribute_Data_Handle::operator=(Attribute_Data_Handle && other)
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
bool saklib::internal::Attribute_Data_Handle::is_valid() const
{
    return m_reference_counter.is_valid();
}

bool saklib::internal::Attribute_Data_Handle::is_null() const
{
    return m_reference_counter.is_null();
}

saklib::internal::Attribute_Data_Handle::handle_type saklib::internal::Attribute_Data_Handle::cget_element_handle() const
{
    return m_reference_counter.cget_handle();
}

std::size_t saklib::internal::Attribute_Data_Handle::cget_element_reference_count() const
{
    return cget_storage().cget_reference_count(m_reference_counter.cget_handle());
}

std::size_t saklib::internal::Attribute_Data_Handle::cget_attribute_index() const
{
    return m_attribute_index;
}

// Attribute_Data Wrapper Interface
//============================================================
std::string const& saklib::internal::Attribute_Data_Handle::cget_name() const
{
    return cget_attribute().cget_name();
}

std::string const& saklib::internal::Attribute_Data_Handle::cget_type() const
{
    return cget_attribute().cget_type();
}

std::string saklib::internal::Attribute_Data_Handle::cget_value_string() const
{
    return cget_attribute().cget_value_string();
}

bool saklib::internal::Attribute_Data_Handle::is_bool() const
{
    return cget_attribute().is_bool();
}

bool saklib::internal::Attribute_Data_Handle::is_int() const
{
    return cget_attribute().is_int();
}

saklib::internal::Attribute_Data_Handle_Bool saklib::internal::Attribute_Data_Handle::cget_bool() const
{
    return Attribute_Data_Handle_Bool(m_reference_counter, m_attribute_index);
}

saklib::internal::Attribute_Data_Handle_Int saklib::internal::Attribute_Data_Handle::cget_int() const
{
    return Attribute_Data_Handle_Int(m_reference_counter, m_attribute_index);
}

// Comparison Operators
//============================================================
bool saklib::internal::Attribute_Data_Handle::operator==(Attribute_Data_Handle const& rhs)
{
    return (m_reference_counter == rhs.m_reference_counter) && (m_attribute_index == rhs.m_attribute_index);
}

bool saklib::internal::Attribute_Data_Handle::operator!=(Attribute_Data_Handle const& rhs)
{
    return (m_reference_counter != rhs.m_reference_counter) && (m_attribute_index != rhs.m_attribute_index);
}

bool saklib::internal::Attribute_Data_Handle::operator<(Attribute_Data_Handle const& rhs)
{
    return (m_reference_counter < rhs.m_reference_counter) && (m_attribute_index < rhs.m_attribute_index);
}

bool saklib::internal::Attribute_Data_Handle::operator>(Attribute_Data_Handle const& rhs)
{
    return (m_reference_counter > rhs.m_reference_counter) && (m_attribute_index > rhs.m_attribute_index);
}

bool saklib::internal::Attribute_Data_Handle::operator<=(Attribute_Data_Handle const& rhs)
{
    return (m_reference_counter <= rhs.m_reference_counter) && (m_attribute_index <= rhs.m_attribute_index);
}

bool saklib::internal::Attribute_Data_Handle::operator>=(Attribute_Data_Handle const& rhs)
{
    return (m_reference_counter >= rhs.m_reference_counter) && (m_attribute_index >= rhs.m_attribute_index);
}

// Comparison Operators for compare to the null handle
//============================================================
bool saklib::internal::Attribute_Data_Handle::operator==(Null_Handle_Type const& )
{
    return is_null();
}

bool saklib::internal::Attribute_Data_Handle::operator!=(Null_Handle_Type const& )
{
    return is_valid();
}

// Protected Helpers
//============================================================
saklib::internal::Attribute_Data_Handle::storage_type& saklib::internal::Attribute_Data_Handle::get_storage()
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

saklib::internal::Attribute_Data_Handle::storage_type const& saklib::internal::Attribute_Data_Handle::cget_storage() const
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

saklib::internal::Element_Data& saklib::internal::Attribute_Data_Handle::get_element()
{
    return get_storage().get_data(m_reference_counter.cget_handle());
}

saklib::internal::Element_Data const& saklib::internal::Attribute_Data_Handle::cget_element() const
{
    return cget_storage().cget_data(m_reference_counter.cget_handle());
}

saklib::internal::Attribute_Data& saklib::internal::Attribute_Data_Handle::get_attribute()
{
    return get_element().get_attribute_at(m_attribute_index);
}

saklib::internal::Attribute_Data const& saklib::internal::Attribute_Data_Handle::cget_attribute() const
{
    return cget_element().cget_attribute_at(m_attribute_index);
}
