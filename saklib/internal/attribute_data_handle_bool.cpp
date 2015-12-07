#include "attribute_data_handle_bool.h"

#include "attribute_data_bool.h"

#ifndef SAKLIB_INTERNAL_BAD_DATA_HANDLE_H
#include "exceptions/bad_data_handle.h"
#endif

#ifndef INCLUDE_STD_CASSERT
#define INCLUDE_STD_CASSERT
#include <cassert>
#endif


// Special 6
//============================================================
template <typename T>
saklib::internal::Attribute_Data_Handle_Boolean_Type<T>::Attribute_Data_Handle_Boolean_Type():
    m_attribute_handle()
{
}

template <typename T>
saklib::internal::Attribute_Data_Handle_Boolean_Type<T>::Attribute_Data_Handle_Boolean_Type(Attribute_Data_Handle const& a_attribute_handle):
    m_attribute_handle(a_attribute_handle)
{
    assert(m_attribute_handle.is_valid());
    assert(m_attribute_handle.is_bool_type<T>());
}

template <typename T>
saklib::internal::Attribute_Data_Handle_Boolean_Type<T>::Attribute_Data_Handle_Boolean_Type(Attribute_Data_Handle && a_attribute_handle):
    m_attribute_handle(std::move(a_attribute_handle))
{
    assert(m_attribute_handle.is_valid());
    assert(m_attribute_handle.is_bool_type<T>());
}

template <typename T>
saklib::internal::Attribute_Data_Handle_Boolean_Type<T>::~Attribute_Data_Handle_Boolean_Type() = default;

template <typename T>
saklib::internal::Attribute_Data_Handle_Boolean_Type<T>::Attribute_Data_Handle_Boolean_Type(Attribute_Data_Handle_Boolean_Type<T> const& other) = default;

template <typename T>
saklib::internal::Attribute_Data_Handle_Boolean_Type<T>& saklib::internal::Attribute_Data_Handle_Boolean_Type<T>::operator=(Attribute_Data_Handle_Boolean_Type<T> const& other) = default;

template <typename T>
saklib::internal::Attribute_Data_Handle_Boolean_Type<T>::Attribute_Data_Handle_Boolean_Type(Attribute_Data_Handle_Boolean_Type<T> && other):
    m_attribute_handle(std::move(other.m_attribute_handle))
{
}

template <typename T>
saklib::internal::Attribute_Data_Handle_Boolean_Type<T>& saklib::internal::Attribute_Data_Handle_Boolean_Type<T>::operator=(Attribute_Data_Handle_Boolean_Type<T> && other)
{
    if (&other != this)
    {
        m_attribute_handle = std::move(other.m_attribute_handle);
    }
    return *this;
}

// Interface
//============================================================
template <typename T>
bool saklib::internal::Attribute_Data_Handle_Boolean_Type<T>::is_valid() const
{
    return m_attribute_handle.is_valid();
}

template <typename T>
bool saklib::internal::Attribute_Data_Handle_Boolean_Type<T>::is_null() const
{
    return m_attribute_handle.is_null();
}

template <typename T>
typename saklib::internal::Attribute_Data_Handle_Boolean_Type<T>::handle_type saklib::internal::Attribute_Data_Handle_Boolean_Type<T>::cget_element_handle() const
{
    return m_attribute_handle.cget_element_handle();
}

template <typename T>
std::size_t saklib::internal::Attribute_Data_Handle_Boolean_Type<T>::cget_element_reference_count() const
{
    return m_attribute_handle.cget_element_reference_count();
}

template <typename T>
std::size_t saklib::internal::Attribute_Data_Handle_Boolean_Type<T>::cget_attribute_index() const
{
    return m_attribute_handle.cget_attribute_index();
}

template <typename T>
saklib::internal::Element_Data_Manager& saklib::internal::Attribute_Data_Handle_Boolean_Type<T>::get_manager()
{
    return m_attribute_handle.get_manager();
}

template <typename T>
saklib::internal::Element_Data_Manager const& saklib::internal::Attribute_Data_Handle_Boolean_Type<T>::cget_manager() const
{
    return m_attribute_handle.cget_manager();
}


// Attribute_Data Wrapper Interface
//============================================================
template <typename T>
std::string const& saklib::internal::Attribute_Data_Handle_Boolean_Type<T>::cget_name() const
{
    return cget_attribute_bool().cget_name();
}

template <typename T>
std::string const& saklib::internal::Attribute_Data_Handle_Boolean_Type<T>::cget_type() const
{
    return cget_attribute_bool().cget_type();
}

template <typename T>
std::string saklib::internal::Attribute_Data_Handle_Boolean_Type<T>::cget_value_string() const
{
    return cget_attribute_bool().cget_value_string();
}

template <typename T>
typename saklib::internal::Attribute_Data_Handle_Boolean_Type<T>::bool_type saklib::internal::Attribute_Data_Handle_Boolean_Type<T>::cget_value() const
{
    return cget_attribute_bool().cget_value();
}

template <typename T>
bool saklib::internal::Attribute_Data_Handle_Boolean_Type<T>::can_set_value_to(bool_type a_value) const
{
    return cget_attribute_bool().can_set_value_to(a_value);
}

template <typename T>
bool saklib::internal::Attribute_Data_Handle_Boolean_Type<T>::try_set_value(bool_type a_value)
{
    return get_attribute_bool().try_set_value(a_value);
}

template <typename T>
void saklib::internal::Attribute_Data_Handle_Boolean_Type<T>::set_value(bool_type a_value)
{
    get_attribute_bool().set_value(a_value);
}

// Comparison Operators
//============================================================
template <typename T>
bool saklib::internal::Attribute_Data_Handle_Boolean_Type<T>::operator==(Attribute_Data_Handle_Boolean_Type<T> const& rhs)
{
    return (m_attribute_handle == rhs.m_attribute_handle);
}

template <typename T>
bool saklib::internal::Attribute_Data_Handle_Boolean_Type<T>::operator!=(Attribute_Data_Handle_Boolean_Type<T> const& rhs)
{
    return (m_attribute_handle != rhs.m_attribute_handle);
}

template <typename T>
bool saklib::internal::Attribute_Data_Handle_Boolean_Type<T>::operator<(Attribute_Data_Handle_Boolean_Type<T> const& rhs)
{
    return (m_attribute_handle < rhs.m_attribute_handle);
}

template <typename T>
bool saklib::internal::Attribute_Data_Handle_Boolean_Type<T>::operator>(Attribute_Data_Handle_Boolean_Type<T> const& rhs)
{
    return (m_attribute_handle > rhs.m_attribute_handle);
}

template <typename T>
bool saklib::internal::Attribute_Data_Handle_Boolean_Type<T>::operator<=(Attribute_Data_Handle_Boolean_Type<T> const& rhs)
{
    return (m_attribute_handle <= rhs.m_attribute_handle);
}

template <typename T>
bool saklib::internal::Attribute_Data_Handle_Boolean_Type<T>::operator>=(Attribute_Data_Handle_Boolean_Type<T> const& rhs)
{
    return (m_attribute_handle >= rhs.m_attribute_handle);
}

// Comparison Operators to Untyped Handle
//============================================================
template <typename T>
bool saklib::internal::Attribute_Data_Handle_Boolean_Type<T>::operator==(Attribute_Data_Handle const& rhs)
{
    return m_attribute_handle == rhs;
}

template <typename T>
bool saklib::internal::Attribute_Data_Handle_Boolean_Type<T>::operator!=(Attribute_Data_Handle const& rhs)
{
    return m_attribute_handle != rhs;
}

// Comparison Operators for compare to the null handle
//============================================================
template <typename T>
bool saklib::internal::Attribute_Data_Handle_Boolean_Type<T>::operator==(Null_Handle_Type const& )
{
    return is_null();
}

template <typename T>
bool saklib::internal::Attribute_Data_Handle_Boolean_Type<T>::operator!=(Null_Handle_Type const& )
{
    return is_valid();
}

// Protected Helpers
//============================================================
template <typename T>
saklib::internal::Attribute_Data_Boolean_Type<T>& saklib::internal::Attribute_Data_Handle_Boolean_Type<T>::get_attribute_bool()
{
    return m_attribute_handle.get_attribute().get_bool_type<T>();
}

template <typename T>
saklib::internal::Attribute_Data_Boolean_Type<T> const& saklib::internal::Attribute_Data_Handle_Boolean_Type<T>::cget_attribute_bool() const
{
    return m_attribute_handle.cget_attribute().cget_bool_type<T>();
}

// Forced Instantiation
//============================================================
template saklib::internal::Attribute_Data_Handle_Boolean_Type<bool>;
