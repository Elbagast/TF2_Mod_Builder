#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE_BOOL__INLINE_H
#define SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE_BOOL__INLINE_H

#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE_BOOL_H
#include "attribute_data_handle_bool.h"
#endif

#ifndef SAKLIB_INTERNAL_BAD_DATA_HANDLE_H
#include "exceptions/bad_data_handle.h"
#endif

#ifndef INCLUDE_STD_CASSERT
#define INCLUDE_STD_CASSERT
#include <cassert>
#endif


// Special 6
//============================================================
template <typename T, typename M>
saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>::Attribute_Data_Handle_Boolean_Type():
    mp_manager(nullptr),
    m_reference_counter(),
    m_attribute_index(0)
{
}

template <typename T, typename M>
saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>::Attribute_Data_Handle_Boolean_Type(manager_type* ap_manager, reference_counter_type const& a_reference_counter, std::size_t a_index):
    mp_manager(ap_manager),
    m_reference_counter(a_reference_counter),
    m_attribute_index(a_index)
{
    assert(mp_manager != nullptr);
    assert(cget_manager().has_element(cget_element_handle()));
    assert(cget_manager().element_cget_attribute_count(cget_element_handle()) > cget_attribute_index());
    assert(cget_manager().attribute_is_bool_type<T>(cget_element_handle(), cget_attribute_index()));
}

template <typename T, typename M>
saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>::Attribute_Data_Handle_Boolean_Type(manager_type* ap_manager, reference_counter_type&& a_reference_counter, std::size_t a_index):
    mp_manager(ap_manager),
    m_reference_counter(std::move(a_reference_counter)),
    m_attribute_index(a_index)
{
    assert(mp_manager != nullptr);
    assert(cget_manager().has_element(cget_element_handle()));
    assert(cget_manager().element_cget_attribute_count(cget_element_handle()) > cget_attribute_index());
    assert(cget_manager().attribute_is_bool_type<T>(cget_element_handle(), cget_attribute_index()));
}

template <typename T, typename M>
saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>::~Attribute_Data_Handle_Boolean_Type() = default;

template <typename T, typename M>
saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>::Attribute_Data_Handle_Boolean_Type(Attribute_Data_Handle_Boolean_Type<T,M> const& other) = default;

template <typename T, typename M>
saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>& saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>::operator=(Attribute_Data_Handle_Boolean_Type<T,M> const& other) = default;

template <typename T, typename M>
saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>::Attribute_Data_Handle_Boolean_Type(Attribute_Data_Handle_Boolean_Type<T,M> && other):
    mp_manager(std::move(other.mp_manager)),
    m_reference_counter(std::move(other.m_reference_counter)),
    m_attribute_index(std::move(other.m_attribute_index))
{
    other.mp_manager = nullptr;
    other.m_attribute_index = 0;
}

template <typename T, typename M>
saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>& saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>::operator=(Attribute_Data_Handle_Boolean_Type<T,M> && other)
{
    if (&other != this)
    {
        mp_manager = std::move(other.mp_manager);
        m_reference_counter = std::move(other.m_reference_counter);
        m_attribute_index = std::move(other.m_attribute_index);

        other.mp_manager = nullptr;
        other.m_attribute_index = 0;
    }
    return *this;
}

// Interface
//============================================================
template <typename T, typename M>
bool saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>::is_valid() const
{
    return (mp_manager != nullptr) && (m_reference_counter.is_valid());
}

template <typename T, typename M>
bool saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>::is_null() const
{
    return (mp_manager == nullptr) && (m_reference_counter.is_null());
}

template <typename T, typename M>
typename saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>::handle_type saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>::cget_element_handle() const
{
    return m_reference_counter.cget_handle();
}

template <typename T, typename M>
std::size_t saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>::cget_element_reference_count() const
{
    return cget_storage().cget_reference_count(m_reference_counter.cget_handle());
}

template <typename T, typename M>
std::size_t saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>::cget_attribute_index() const
{
    return m_attribute_index;
}

template <typename T, typename M>
typename saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>::manager_type& saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>::get_manager()
{
    if (is_valid())
    {
        return *mp_manager;
    }
    else
    {
        throw Bad_Data_Handle();
    }
}

template <typename T, typename M>
typename saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>::manager_type const& saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>::cget_manager() const
{
    if (is_valid())
    {
        return *mp_manager;
    }
    else
    {
        throw Bad_Data_Handle();
    }
}


// Attribute_Data Wrapper Interface
//============================================================
template <typename T, typename M>
std::string const& saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>::cget_name() const
{
    return cget_manager().attribute_cget_name(cget_element_handle(), cget_attribute_index());
}

template <typename T, typename M>
std::string const& saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>::cget_type() const
{
    return cget_manager().attribute_cget_type(cget_element_handle(), cget_attribute_index());
}

template <typename T, typename M>
std::string saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>::cget_value_string() const
{
    return cget_manager().attribute_cget_value_string(cget_element_handle(), cget_attribute_index());
}

template <typename T, typename M>
typename saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>::bool_type saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>::cget_value() const
{
    return cget_manager().attribute_bool_type_cget_value<T>(cget_element_handle(), cget_attribute_index());
}

template <typename T, typename M>
bool saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>::can_set_value_to(bool_type a_value) const
{
    return cget_manager().attribute_bool_type_can_set_value_to<T>(cget_element_handle(), cget_attribute_index(), a_value);
}

template <typename T, typename M>
bool saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>::try_set_value(bool_type a_value)
{
    return cget_manager().attribute_bool_type_try_set_value<T>(cget_element_handle(), cget_attribute_index(), a_value);
}

template <typename T, typename M>
void saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>::set_value(bool_type a_value)
{
    return cget_manager().attribute_bool_type_set_value<T>(cget_element_handle(), cget_attribute_index(), a_value);
}

// Comparison Operators
//============================================================
template <typename T, typename M>
bool saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>::operator==(Attribute_Data_Handle_Boolean_Type<T,M> const& rhs)
{
    return (mp_manager == rhs.mp_manager) && (m_reference_counter == rhs.m_reference_counter) && (m_attribute_index == rhs.m_attribute_index);
}

template <typename T, typename M>
bool saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>::operator!=(Attribute_Data_Handle_Boolean_Type<T,M> const& rhs)
{
    return (mp_manager != rhs.mp_manager) && (m_reference_counter != rhs.m_reference_counter) && (m_attribute_index != rhs.m_attribute_index);
}

template <typename T, typename M>
bool saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>::operator<(Attribute_Data_Handle_Boolean_Type<T,M> const& rhs)
{
    return (mp_manager < rhs.mp_manager) && (m_reference_counter < rhs.m_reference_counter) && (m_attribute_index < rhs.m_attribute_index);
}

template <typename T, typename M>
bool saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>::operator>(Attribute_Data_Handle_Boolean_Type<T,M> const& rhs)
{
    return (mp_manager > rhs.mp_manager) && (m_reference_counter > rhs.m_reference_counter) && (m_attribute_index > rhs.m_attribute_index);
}

template <typename T, typename M>
bool saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>::operator<=(Attribute_Data_Handle_Boolean_Type<T,M> const& rhs)
{
    return (mp_manager <= rhs.mp_manager) && (m_reference_counter <= rhs.m_reference_counter) && (m_attribute_index <= rhs.m_attribute_index);
}

template <typename T, typename M>
bool saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>::operator>=(Attribute_Data_Handle_Boolean_Type<T,M> const& rhs)
{
    return (mp_manager >= rhs.mp_manager) && (m_reference_counter >= rhs.m_reference_counter) && (m_attribute_index >= rhs.m_attribute_index);
}
/*
// Comparison Operators to Untyped Handle
//============================================================
template <typename T, typename M>
bool saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>::operator==(Attribute_Data_Handle const& rhs)
{
    return m_attribute_handle == rhs;
}

template <typename T, typename M>
bool saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>::operator!=(Attribute_Data_Handle const& rhs)
{
    return m_attribute_handle != rhs;
}
*/
// Comparison Operators for compare to the null handle
//============================================================
template <typename T, typename M>
bool saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>::operator==(Null_Handle_Type const& )
{
    return is_null();
}

template <typename T, typename M>
bool saklib::internal::Attribute_Data_Handle_Boolean_Type<T,M>::operator!=(Null_Handle_Type const& )
{
    return is_valid();
}

#endif // SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE_BOOL__INLINE_H

