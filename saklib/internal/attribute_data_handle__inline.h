#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE__INLINE_H
#define SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE__INLINE_H

#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE_H
#include "attribute_data_handle.h"
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
template <typename M>
saklib::internal::Attribute_Data_Handle<M>::Attribute_Data_Handle():
    mp_manager(nullptr),
    m_reference_counter(),
    m_attribute_index(0)
{
}

template <typename M>
saklib::internal::Attribute_Data_Handle<M>::Attribute_Data_Handle(manager_type* ap_manager, reference_counter_type const& a_reference_counter, std::size_t a_index):
    mp_manager(ap_manager),
    m_reference_counter(a_reference_counter),
    m_attribute_index(a_index)
{
    assert(mp_manager != nullptr);
    assert(cget_manager().has_element(cget_element_handle()));
    assert(cget_manager().element_cget_attribute_count(cget_element_handle()) > cget_attribute_index());
}

template <typename M>
saklib::internal::Attribute_Data_Handle<M>::Attribute_Data_Handle(manager_type* ap_manager, reference_counter_type&& a_reference_counter, std::size_t a_index):
    mp_manager(ap_manager),
    m_reference_counter(std::move(a_reference_counter)),
    m_attribute_index(a_index)
{
    assert(mp_manager != nullptr);
    assert(cget_manager().has_element(cget_element_handle()));
    assert(cget_manager().element_cget_attribute_count(cget_element_handle()) > cget_attribute_index());
}

template <typename M>
saklib::internal::Attribute_Data_Handle<M>::~Attribute_Data_Handle() = default;

template <typename M>
saklib::internal::Attribute_Data_Handle<M>::Attribute_Data_Handle(Attribute_Data_Handle<M> const& other) = default;

template <typename M>
saklib::internal::Attribute_Data_Handle<M>& saklib::internal::Attribute_Data_Handle<M>::operator=(Attribute_Data_Handle<M> const& other) = default;

template <typename M>
saklib::internal::Attribute_Data_Handle<M>::Attribute_Data_Handle(Attribute_Data_Handle<M> && other):
    mp_manager(std::move(other.mp_manager)),
    m_reference_counter(std::move(other.m_reference_counter)),
    m_attribute_index(std::move(other.m_attribute_index))
{
    other.mp_manager = nullptr;
    other.m_attribute_index = 0;
}

template <typename M>
saklib::internal::Attribute_Data_Handle<M>& saklib::internal::Attribute_Data_Handle<M>::operator=(Attribute_Data_Handle<M> && other)
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
template <typename M>
bool saklib::internal::Attribute_Data_Handle<M>::is_valid() const
{
    return (mp_manager != nullptr) && (m_reference_counter.is_valid());
}

template <typename M>
bool saklib::internal::Attribute_Data_Handle<M>::is_null() const
{
    return (mp_manager == nullptr) && (m_reference_counter.is_null());
}

template <typename M>
typename saklib::internal::Attribute_Data_Handle<M>::handle_type saklib::internal::Attribute_Data_Handle<M>::cget_element_handle() const
{
    return m_reference_counter.cget_handle();
}

template <typename M>
std::size_t saklib::internal::Attribute_Data_Handle<M>::cget_element_reference_count() const
{
    return cget_storage().cget_reference_count(m_reference_counter.cget_handle());
}

template <typename M>
std::size_t saklib::internal::Attribute_Data_Handle<M>::cget_attribute_index() const
{
    return m_attribute_index;
}

template <typename M>
typename saklib::internal::Attribute_Data_Handle<M>::manager_type& saklib::internal::Attribute_Data_Handle<M>::get_manager()
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

template <typename M>
typename saklib::internal::Attribute_Data_Handle<M>::manager_type const& saklib::internal::Attribute_Data_Handle<M>::cget_manager() const
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
template <typename M>
std::string const& saklib::internal::Attribute_Data_Handle<M>::cget_name() const
{
    return cget_manager().attribute_cget_name(cget_element_handle(), cget_attribute_index());
}

template <typename M>
std::string const& saklib::internal::Attribute_Data_Handle<M>::cget_type() const
{
    return cget_manager().attribute_cget_type(cget_element_handle(), cget_attribute_index());
}

template <typename M>
std::string saklib::internal::Attribute_Data_Handle<M>::cget_value_string() const
{
    return cget_manager().attribute_cget_value_string(cget_element_handle(), cget_attribute_index());
}

template <typename M>
bool saklib::internal::Attribute_Data_Handle<M>::is_bool() const
{
    return cget_manager().attribute_is_bool(cget_element_handle(), cget_attribute_index());
}

template <typename M>
bool saklib::internal::Attribute_Data_Handle<M>::is_int() const
{
    return cget_manager().attribute_is_int(cget_element_handle(), cget_attribute_index());
}

template <typename M>
saklib::internal::Attribute_Data_Handle_Boolean_Type<bool, M> saklib::internal::Attribute_Data_Handle<M>::cget_bool() const
{
    return cget_manager().attribute_cget_bool(cget_element_handle(), cget_attribute_index());
}

template <typename M>
saklib::internal::Attribute_Data_Handle_Integral_Type<int, M> saklib::internal::Attribute_Data_Handle<M>::cget_int() const
{
    return cget_manager().attribute_cget_int(cget_element_handle(), cget_attribute_index());
}

template <typename M>
template <typename T>
bool saklib::internal::Attribute_Data_Handle<M>::is_bool_type() const
{
    return cget_manager().attribute_is_bool_type<T>(cget_element_handle(), cget_attribute_index());
}

template <typename M>
template <typename T>
bool saklib::internal::Attribute_Data_Handle<M>::is_int_type() const
{
    return cget_manager().attribute_is_int_type<T>(cget_element_handle(), cget_attribute_index());
}

template <typename M>
template <typename T>
saklib::internal::Attribute_Data_Handle_Boolean_Type<T, M> const& saklib::internal::Attribute_Data_Handle<M>::cget_bool_type() const
{
    return cget_manager().attribute_cget_bool_type<T>(cget_element_handle(), cget_attribute_index());
}

template <typename M>
template <typename T>
saklib::internal::Attribute_Data_Handle_Integral_Type<T, M> const& saklib::internal::Attribute_Data_Handle<M>::cget_int_type() const
{
    return cget_manager().attribute_cget_int_type<T>(cget_element_handle(), cget_attribute_index());
}





// Comparison Operators
//============================================================
template <typename M>
bool saklib::internal::Attribute_Data_Handle<M>::operator==(Attribute_Data_Handle<M> const& rhs)
{
    return (mp_manager == rhs.mp_manager) && (m_reference_counter == rhs.m_reference_counter) && (m_attribute_index == rhs.m_attribute_index);
}

template <typename M>
bool saklib::internal::Attribute_Data_Handle<M>::operator!=(Attribute_Data_Handle<M> const& rhs)
{
    return (mp_manager != rhs.mp_manager) && (m_reference_counter != rhs.m_reference_counter) && (m_attribute_index != rhs.m_attribute_index);
}

template <typename M>
bool saklib::internal::Attribute_Data_Handle<M>::operator<(Attribute_Data_Handle<M> const& rhs)
{
    return (mp_manager < rhs.mp_manager) && (m_reference_counter < rhs.m_reference_counter) && (m_attribute_index < rhs.m_attribute_index);
}

template <typename M>
bool saklib::internal::Attribute_Data_Handle<M>::operator>(Attribute_Data_Handle<M> const& rhs)
{
    return (mp_manager > rhs.mp_manager) && (m_reference_counter > rhs.m_reference_counter) && (m_attribute_index > rhs.m_attribute_index);
}

template <typename M>
bool saklib::internal::Attribute_Data_Handle<M>::operator<=(Attribute_Data_Handle<M> const& rhs)
{
    return (mp_manager <= rhs.mp_manager) && (m_reference_counter <= rhs.m_reference_counter) && (m_attribute_index <= rhs.m_attribute_index);
}

template <typename M>
bool saklib::internal::Attribute_Data_Handle<M>::operator>=(Attribute_Data_Handle<M> const& rhs)
{
    return (mp_manager >= rhs.mp_manager) && (m_reference_counter >= rhs.m_reference_counter) && (m_attribute_index >= rhs.m_attribute_index);
}
/*
// Comparison Operators to Untyped Handle
//============================================================
template <typename M>
bool saklib::internal::Attribute_Data_Handle<M>::operator==(Attribute_Data_Handle const& rhs)
{
    return m_attribute_handle == rhs;
}

template <typename M>
bool saklib::internal::Attribute_Data_Handle<M>::operator!=(Attribute_Data_Handle const& rhs)
{
    return m_attribute_handle != rhs;
}
*/
// Comparison Operators for compare to the null handle
//============================================================
template <typename M>
bool saklib::internal::Attribute_Data_Handle<M>::operator==(Null_Handle_Type const& )
{
    return is_null();
}

template <typename M>
bool saklib::internal::Attribute_Data_Handle<M>::operator!=(Null_Handle_Type const& )
{
    return is_valid();
}

#endif // SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE__INLINE_H

