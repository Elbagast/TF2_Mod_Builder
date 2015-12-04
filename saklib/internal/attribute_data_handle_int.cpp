#include "attribute_data_handle_int.h"

#include "attribute_data_int.h"

//---------------------------------------------------------------------------
// Attribute_Data_Handle_Int
//---------------------------------------------------------------------------

// Special 6
//============================================================
template <typename T>
saklib::internal::Attribute_Data_Handle_Integral_Type<T>::Attribute_Data_Handle_Integral_Type():
    m_reference_counter(),
    m_attribute_index(0)
{
}

template <typename T>
saklib::internal::Attribute_Data_Handle_Integral_Type<T>::Attribute_Data_Handle_Integral_Type(reference_counter_type const& a_reference_counter, std::size_t a_index):
    m_reference_counter(a_reference_counter),
    m_attribute_index(a_index)
{
}

template <typename T>
saklib::internal::Attribute_Data_Handle_Integral_Type<T>::Attribute_Data_Handle_Integral_Type(reference_counter_type&& a_reference_counter, std::size_t a_index):
    m_reference_counter(std::move(a_reference_counter)),
    m_attribute_index(a_index)
{
}

template <typename T>
saklib::internal::Attribute_Data_Handle_Integral_Type<T>::~Attribute_Data_Handle_Integral_Type() = default;

template <typename T>
saklib::internal::Attribute_Data_Handle_Integral_Type<T>::Attribute_Data_Handle_Integral_Type(Attribute_Data_Handle_Integral_Type const& other) = default;

template <typename T>
saklib::internal::Attribute_Data_Handle_Integral_Type<T>& saklib::internal::Attribute_Data_Handle_Integral_Type<T>::operator=(Attribute_Data_Handle_Integral_Type const& other) = default;

template <typename T>
saklib::internal::Attribute_Data_Handle_Integral_Type<T>::Attribute_Data_Handle_Integral_Type(Attribute_Data_Handle_Integral_Type && other):
    m_reference_counter(std::move(other.m_reference_counter)),
    m_attribute_index(std::move(other.m_attribute_index))
{
    other.m_attribute_index = 0;
}

template <typename T>
saklib::internal::Attribute_Data_Handle_Integral_Type<T>& saklib::internal::Attribute_Data_Handle_Integral_Type<T>::operator=(Attribute_Data_Handle_Integral_Type && other)
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
template <typename T>
bool saklib::internal::Attribute_Data_Handle_Integral_Type<T>::is_valid() const
{
    return m_reference_counter.is_valid();
}

template <typename T>
bool saklib::internal::Attribute_Data_Handle_Integral_Type<T>::is_null() const
{
    return m_reference_counter.is_null();
}

template <typename T>
typename saklib::internal::Attribute_Data_Handle_Integral_Type<T>::handle_type saklib::internal::Attribute_Data_Handle_Integral_Type<T>::cget_element_handle() const
{
    return m_reference_counter.cget_handle();
}

template <typename T>
std::size_t saklib::internal::Attribute_Data_Handle_Integral_Type<T>::cget_element_reference_count() const
{
    return cget_storage().cget_reference_count(m_reference_counter.cget_handle());
}

template <typename T>
std::size_t saklib::internal::Attribute_Data_Handle_Integral_Type<T>::cget_attribute_index() const
{
    return m_attribute_index;
}

// Attribute_Data Wrapper Interface
//============================================================
template <typename T>
std::string const& saklib::internal::Attribute_Data_Handle_Integral_Type<T>::cget_name() const
{
    return cget_attribute().cget_name();
}

template <typename T>
std::string const& saklib::internal::Attribute_Data_Handle_Integral_Type<T>::cget_type() const
{
    return cget_attribute().cget_type();
}

template <typename T>
std::string saklib::internal::Attribute_Data_Handle_Integral_Type<T>::cget_value_string() const
{
    return cget_attribute().cget_value_string();
}

template <typename T>
typename saklib::internal::Attribute_Data_Handle_Integral_Type<T>::int_type saklib::internal::Attribute_Data_Handle_Integral_Type<T>::cget_value() const
{
    return cget_attribute().cget_value();
}

template <typename T>
bool saklib::internal::Attribute_Data_Handle_Integral_Type<T>::can_set_value_to(int_type a_value) const
{
    return cget_attribute().can_set_value_to(a_value);
}

template <typename T>
bool saklib::internal::Attribute_Data_Handle_Integral_Type<T>::try_set_value(int_type a_value)
{
    return get_attribute().try_set_value(a_value);
}

template <typename T>
void saklib::internal::Attribute_Data_Handle_Integral_Type<T>::set_value(int_type a_value)
{
    get_attribute().set_value(a_value);
}

template <typename T>
typename saklib::internal::Attribute_Data_Handle_Integral_Type<T>::int_type saklib::internal::Attribute_Data_Handle_Integral_Type<T>::cget_lowest_value() const
{
    return cget_attribute().cget_lowest_value();
}

template <typename T>
typename saklib::internal::Attribute_Data_Handle_Integral_Type<T>::int_type saklib::internal::Attribute_Data_Handle_Integral_Type<T>::cget_highest_value() const
{
    return cget_attribute().cget_highest_value();
}

// Comparison Operators
//============================================================
template <typename T>
bool saklib::internal::Attribute_Data_Handle_Integral_Type<T>::operator==(Attribute_Data_Handle_Integral_Type const& rhs)
{
    return (m_reference_counter == rhs.m_reference_counter) && (m_attribute_index == rhs.m_attribute_index);
}

template <typename T>
bool saklib::internal::Attribute_Data_Handle_Integral_Type<T>::operator!=(Attribute_Data_Handle_Integral_Type const& rhs)
{
    return (m_reference_counter != rhs.m_reference_counter) && (m_attribute_index != rhs.m_attribute_index);
}

template <typename T>
bool saklib::internal::Attribute_Data_Handle_Integral_Type<T>::operator<(Attribute_Data_Handle_Integral_Type const& rhs)
{
    return (m_reference_counter < rhs.m_reference_counter) && (m_attribute_index < rhs.m_attribute_index);
}

template <typename T>
bool saklib::internal::Attribute_Data_Handle_Integral_Type<T>::operator>(Attribute_Data_Handle_Integral_Type const& rhs)
{
    return (m_reference_counter > rhs.m_reference_counter) && (m_attribute_index > rhs.m_attribute_index);
}

template <typename T>
bool saklib::internal::Attribute_Data_Handle_Integral_Type<T>::operator<=(Attribute_Data_Handle_Integral_Type const& rhs)
{
    return (m_reference_counter <= rhs.m_reference_counter) && (m_attribute_index <= rhs.m_attribute_index);
}

template <typename T>
bool saklib::internal::Attribute_Data_Handle_Integral_Type<T>::operator>=(Attribute_Data_Handle_Integral_Type const& rhs)
{
    return (m_reference_counter >= rhs.m_reference_counter) && (m_attribute_index >= rhs.m_attribute_index);
}
/*
// Comparison Operators to Untyped Handle
//============================================================
bool saklib::internal::Attribute_Data_Handle_Integral_Type<T>::operator==(Attribute_Data_Handle_Integral_Type const& rhs)
{
    return m_attribute_handle == rhs;
}

bool saklib::internal::Attribute_Data_Handle_Integral_Type<T>::operator!=(Attribute_Data_Handle_Integral_Type const& rhs)
{
    return m_attribute_handle != rhs;
}
*/
// Comparison Operators for compare to the null handle
//============================================================
template <typename T>
bool saklib::internal::Attribute_Data_Handle_Integral_Type<T>::operator==(Null_Handle_Type const& )
{
    return is_null();
}

template <typename T>
bool saklib::internal::Attribute_Data_Handle_Integral_Type<T>::operator!=(Null_Handle_Type const& )
{
    return is_valid();
}

// Protected Helpers
//============================================================
template <typename T>
typename saklib::internal::Attribute_Data_Handle_Integral_Type<T>::storage_type& saklib::internal::Attribute_Data_Handle_Integral_Type<T>::get_storage()
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

template <typename T>
typename saklib::internal::Attribute_Data_Handle_Integral_Type<T>::storage_type const& saklib::internal::Attribute_Data_Handle_Integral_Type<T>::cget_storage() const
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

template <typename T>
saklib::internal::Element_Data& saklib::internal::Attribute_Data_Handle_Integral_Type<T>::get_element()
{
    return get_storage().get_data(m_reference_counter.cget_handle());
}

template <typename T>
saklib::internal::Element_Data const& saklib::internal::Attribute_Data_Handle_Integral_Type<T>::cget_element() const
{
    return cget_storage().cget_data(m_reference_counter.cget_handle());
}

template <typename T>
typename saklib::internal::Attribute_Data_Handle_Integral_Type<T>::attribute_data_type& saklib::internal::Attribute_Data_Handle_Integral_Type<T>::get_attribute()
{
    return get_element().get_attribute_at(m_attribute_index).get_int();
}

template <typename T>
typename saklib::internal::Attribute_Data_Handle_Integral_Type<T>::attribute_data_type const& saklib::internal::Attribute_Data_Handle_Integral_Type<T>::cget_attribute() const
{
    return cget_element().cget_attribute_at(m_attribute_index).cget_int();
}


template saklib::internal::Attribute_Data_Handle_Integral_Type<int>;
//template saklib::internal::Attribute_Data_Handle_Integral_Type<unsigned int>; // need to templatise Attribute_Data getters
