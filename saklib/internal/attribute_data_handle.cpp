#include "attribute_data_handle.h"

#include "element_data_manager.h"
#include "all_attribute_data_handle.h"

#ifndef SAKLIB_INTERNAL_BAD_DATA_HANDLE_H
#include "exceptions/bad_data_handle.h"
#endif

#ifndef INCLUDE_STD_CASSERT
#define INCLUDE_STD_CASSERT
#include <cassert>
#endif


// Special 6
//============================================================
saklib::internal::Attribute_Data_Handle::Attribute_Data_Handle():
    m_element_handle(),
    m_attribute_index(0)
{
}

saklib::internal::Attribute_Data_Handle::Attribute_Data_Handle(Element_Data_Handle const& a_element_handle, std::size_t a_index):
    m_element_handle(a_element_handle),
    m_attribute_index(a_index)
{
    assert(m_element_handle.is_valid());
    assert(m_element_handle.has_attribute(a_index));
}

saklib::internal::Attribute_Data_Handle::Attribute_Data_Handle(Element_Data_Handle && a_element_handle, std::size_t a_index):
    m_element_handle(std::move(a_element_handle)),
    m_attribute_index(a_index)
{
    assert(m_element_handle.is_valid());
    assert(m_element_handle.has_attribute(a_index));
}

saklib::internal::Attribute_Data_Handle::~Attribute_Data_Handle() = default;

saklib::internal::Attribute_Data_Handle::Attribute_Data_Handle(Attribute_Data_Handle const& other) = default;

saklib::internal::Attribute_Data_Handle& saklib::internal::Attribute_Data_Handle::operator=(Attribute_Data_Handle const& other) = default;

saklib::internal::Attribute_Data_Handle::Attribute_Data_Handle(Attribute_Data_Handle && other):
    m_element_handle(std::move(other.m_element_handle)),
    m_attribute_index(std::move(other.m_attribute_index))
{
    other.m_attribute_index = 0;
}

saklib::internal::Attribute_Data_Handle& saklib::internal::Attribute_Data_Handle::operator=(Attribute_Data_Handle && other)
{
    if (&other != this)
    {
        m_element_handle = std::move(other.m_element_handle);
        m_attribute_index = std::move(other.m_attribute_index);

        other.m_attribute_index = 0;
    }
    return *this;
}

// Interface
//============================================================
bool saklib::internal::Attribute_Data_Handle::is_valid() const
{
    return m_element_handle.is_valid();
}

bool saklib::internal::Attribute_Data_Handle::is_null() const
{
    return m_element_handle.is_null();
}

saklib::internal::Attribute_Data_Handle::handle_type saklib::internal::Attribute_Data_Handle::cget_element_handle() const
{
    return m_element_handle.cget_handle();
}

std::size_t saklib::internal::Attribute_Data_Handle::cget_element_reference_count() const
{
    return m_element_handle.cget_reference_count();
}

std::size_t saklib::internal::Attribute_Data_Handle::cget_attribute_index() const
{
    return m_attribute_index;
}

saklib::internal::Element_Data_Manager& saklib::internal::Attribute_Data_Handle::get_manager()
{
    return m_element_handle.get_manager();
}

saklib::internal::Element_Data_Manager const& saklib::internal::Attribute_Data_Handle::cget_manager() const
{
    return m_element_handle.cget_manager();
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
    return is_bool_type<bool>();
}

saklib::internal::Attribute_Data_Handle_Boolean_Type<bool> saklib::internal::Attribute_Data_Handle::cget_bool() const
{
    return cget_bool_type<bool>();
}

template <typename T>
bool saklib::internal::Attribute_Data_Handle::is_bool_type() const
{
    return cget_attribute().is_bool_type<T>();
}

template <typename T>
saklib::internal::Attribute_Data_Handle_Boolean_Type<T> saklib::internal::Attribute_Data_Handle::cget_bool_type() const
{
    if (is_bool_type<T>())
    {
        return Attribute_Data_Handle_Boolean_Type<T>(*this);
    }
    else
    {
        return Attribute_Data_Handle_Boolean_Type<T>();
    }
}


template bool saklib::internal::Attribute_Data_Handle::is_bool_type<bool>() const;
template saklib::internal::Attribute_Data_Handle_Boolean_Type<bool> saklib::internal::Attribute_Data_Handle::cget_bool_type<bool>() const;


bool saklib::internal::Attribute_Data_Handle::is_int() const
{
    return is_int_type<int>();
}

saklib::internal::Attribute_Data_Handle_Integral_Type<int> saklib::internal::Attribute_Data_Handle::cget_int() const
{
    return cget_int_type<int>();
}

template <typename T>
bool saklib::internal::Attribute_Data_Handle::is_int_type() const
{
    return cget_attribute().is_int_type<T>();
}

template <typename T>
saklib::internal::Attribute_Data_Handle_Integral_Type<T> saklib::internal::Attribute_Data_Handle::cget_int_type() const
{
    if (is_int_type<T>())
    {
        return Attribute_Data_Handle_Integral_Type<T>(*this);
    }
    else
    {
        return Attribute_Data_Handle_Integral_Type<T>();
    }
}

template bool saklib::internal::Attribute_Data_Handle::is_int_type<short>() const;
template saklib::internal::Attribute_Data_Handle_Integral_Type<short> saklib::internal::Attribute_Data_Handle::cget_int_type<short>() const;
template bool saklib::internal::Attribute_Data_Handle::is_int_type<unsigned short>() const;
template saklib::internal::Attribute_Data_Handle_Integral_Type<unsigned short> saklib::internal::Attribute_Data_Handle::cget_int_type<unsigned short>() const;

template bool saklib::internal::Attribute_Data_Handle::is_int_type<int>() const;
template saklib::internal::Attribute_Data_Handle_Integral_Type<int> saklib::internal::Attribute_Data_Handle::cget_int_type<int>() const;
template bool saklib::internal::Attribute_Data_Handle::is_int_type<unsigned int>() const;
template saklib::internal::Attribute_Data_Handle_Integral_Type<unsigned int> saklib::internal::Attribute_Data_Handle::cget_int_type<unsigned int>() const;

template bool saklib::internal::Attribute_Data_Handle::is_int_type<long>() const;
template saklib::internal::Attribute_Data_Handle_Integral_Type<long> saklib::internal::Attribute_Data_Handle::cget_int_type<long>() const;
template bool saklib::internal::Attribute_Data_Handle::is_int_type<unsigned long>() const;
template saklib::internal::Attribute_Data_Handle_Integral_Type<unsigned long> saklib::internal::Attribute_Data_Handle::cget_int_type<unsigned long>() const;

template bool saklib::internal::Attribute_Data_Handle::is_int_type<long long>() const;
template saklib::internal::Attribute_Data_Handle_Integral_Type<long long> saklib::internal::Attribute_Data_Handle::cget_int_type<long long>() const;
template bool saklib::internal::Attribute_Data_Handle::is_int_type<unsigned long long>() const;
template saklib::internal::Attribute_Data_Handle_Integral_Type<unsigned long long> saklib::internal::Attribute_Data_Handle::cget_int_type<unsigned long long>() const;



// Comparison Operators
//============================================================
bool saklib::internal::Attribute_Data_Handle::operator==(Attribute_Data_Handle const& rhs)
{
    return (m_element_handle == rhs.m_element_handle) && (m_attribute_index == rhs.m_attribute_index);
}

bool saklib::internal::Attribute_Data_Handle::operator!=(Attribute_Data_Handle const& rhs)
{
    return (m_element_handle != rhs.m_element_handle) && (m_attribute_index != rhs.m_attribute_index);
}

bool saklib::internal::Attribute_Data_Handle::operator<(Attribute_Data_Handle const& rhs)
{
    return (m_element_handle < rhs.m_element_handle) && (m_attribute_index < rhs.m_attribute_index);
}

bool saklib::internal::Attribute_Data_Handle::operator>(Attribute_Data_Handle const& rhs)
{
    return (m_element_handle > rhs.m_element_handle) && (m_attribute_index > rhs.m_attribute_index);
}

bool saklib::internal::Attribute_Data_Handle::operator<=(Attribute_Data_Handle const& rhs)
{
    return (m_element_handle <= rhs.m_element_handle) && (m_attribute_index <= rhs.m_attribute_index);
}

bool saklib::internal::Attribute_Data_Handle::operator>=(Attribute_Data_Handle const& rhs)
{
    return (m_element_handle >= rhs.m_element_handle) && (m_attribute_index >= rhs.m_attribute_index);
}
/*
// Comparison Operators to Untyped Handle
//============================================================

bool saklib::internal::Attribute_Data_Handle::operator==(Attribute_Data_Handle const& rhs)
{
    return m_attribute_handle == rhs;
}


bool saklib::internal::Attribute_Data_Handle::operator!=(Attribute_Data_Handle const& rhs)
{
    return m_attribute_handle != rhs;
}
*/
// Comparison Operators for compare to the null handle
//============================================================
bool saklib::internal::Attribute_Data_Handle::operator==(Null_Integer_ID_Type const& )
{
    return is_null();
}

bool saklib::internal::Attribute_Data_Handle::operator!=(Null_Integer_ID_Type const& )
{
    return is_valid();
}

// Protected Helpers
//============================================================
saklib::internal::Attribute_Data& saklib::internal::Attribute_Data_Handle::get_attribute()
{
    return m_element_handle.get_element().get_attribute_at(m_attribute_index);
}

saklib::internal::Attribute_Data const& saklib::internal::Attribute_Data_Handle::cget_attribute() const
{
    return m_element_handle.cget_element().cget_attribute_at(m_attribute_index);
}
