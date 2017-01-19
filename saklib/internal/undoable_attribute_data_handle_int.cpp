#include "undoable_attribute_data_handle_int.h"

#include "undoable_attribute_data_handle.h"

#include "command_history.h"
#include "command.h"

//---------------------------------------------------------------------------
// Undoable_Attribute_Data_Handle_Integral_Type<T>
//---------------------------------------------------------------------------

// Special 6
//============================================================
template <typename T>
saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::Undoable_Attribute_Data_Handle_Integral_Type():
    m_attribute_handle(),
    mp_command_history(nullptr)
{
}

template <typename T>
saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::Undoable_Attribute_Data_Handle_Integral_Type(Attribute_Data_Handle_Integral_Type<T> const& a_attribute_handle, Command_History& ar_command_history):
    m_attribute_handle(a_attribute_handle),
    mp_command_history(&ar_command_history)
{
    assert(m_attribute_handle.is_valid());
}

template <typename T>
saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::Undoable_Attribute_Data_Handle_Integral_Type(Attribute_Data_Handle_Integral_Type<T> && a_attribute_handle, Command_History& ar_command_history):
    m_attribute_handle(std::move(a_attribute_handle)),
    mp_command_history(&ar_command_history)
{
    assert(m_attribute_handle.is_valid());
}

template <typename T>
saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::~Undoable_Attribute_Data_Handle_Integral_Type() = default;

template <typename T>
saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::Undoable_Attribute_Data_Handle_Integral_Type(Undoable_Attribute_Data_Handle_Integral_Type<T> const& other) = default;

template <typename T>
saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>& saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::operator=(Undoable_Attribute_Data_Handle_Integral_Type<T> const& other) = default;

template <typename T>
saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::Undoable_Attribute_Data_Handle_Integral_Type(Undoable_Attribute_Data_Handle_Integral_Type<T> && other):
    m_attribute_handle(std::move(other.m_attribute_handle)),
    mp_command_history(std::move(other.mp_command_history))
{
    other.mp_command_history = nullptr;
}

template <typename T>
saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>& saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::operator=(Undoable_Attribute_Data_Handle_Integral_Type<T> && other)
{
    if (&other != this)
    {
        m_attribute_handle = std::move(other.m_attribute_handle);
        mp_command_history = std::move(other.mp_command_history);

        other.mp_command_history = nullptr;
    }
    return *this;
}

// Interface
//============================================================
template <typename T>
bool saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::is_valid() const
{
    return m_attribute_handle.is_valid();
}

template <typename T>
bool saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::is_null() const
{
    return m_attribute_handle.is_null();
}

template <typename T>
typename saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::handle_type saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::cget_element_handle() const
{
    return m_attribute_handle.cget_element_handle();
}

template <typename T>
std::size_t saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::cget_element_reference_count() const
{
    return m_attribute_handle.cget_element_reference_count();
}

template <typename T>
std::size_t saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::cget_attribute_index() const
{
    return m_attribute_handle.cget_attribute_index();
}

// Attribute_Data Wrapper Interface
//============================================================

template <typename T>
std::string const& saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::cget_name() const
{
    return m_attribute_handle.cget_name();
}

template <typename T>
std::string const& saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::cget_type() const
{
    return m_attribute_handle.cget_type();
}

template <typename T>
std::string saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::cget_value_string() const
{
    return m_attribute_handle.cget_value_string();
}

template <typename T>
typename saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::int_type saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::cget_value() const
{
    return m_attribute_handle.cget_value();
}

template <typename T>
bool saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::can_set_value_to(int_type a_value) const
{
    return m_attribute_handle.can_set_value_to(a_value);
}

template <typename T>
bool saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::try_set_value(int_type a_value)
{
    if (can_set_value_to(a_value))
    {
        set_value(a_value);
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
void saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::set_value(int_type a_value)
{
    // Command intercept

    using Command_Attribute_Data_Handle_Int_Set_Value = Command_Simple_Stored_Get_Set
    <
    Attribute_Data_Handle_Integral_Type<T>,
    Attribute_Data_Handle_Integral_Type<T>::int_type,
    Attribute_Data_Handle_Integral_Type<T>::int_type,
    &Attribute_Data_Handle_Integral_Type<T>::cget_value,
    void,
    Attribute_Data_Handle_Integral_Type<T>::int_type,
    &Attribute_Data_Handle_Integral_Type<T>::set_value
    >;

    get_command_history().emplace_execute<Command_Attribute_Data_Handle_Int_Set_Value>(m_attribute_handle, a_value);
}

template <typename T>
typename saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::int_type saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::cget_lowest_value() const
{
    return m_attribute_handle.cget_lowest_value();
}

template <typename T>
typename saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::int_type saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::cget_highest_value() const
{
    return m_attribute_handle.cget_highest_value();
}

// Comparison Operators
//============================================================

template <typename T>
bool saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::operator==(Undoable_Attribute_Data_Handle_Integral_Type<T> const& rhs)
{
    return m_attribute_handle == rhs.m_attribute_handle;
}

template <typename T>
bool saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::operator!=(Undoable_Attribute_Data_Handle_Integral_Type<T> const& rhs)
{
    return m_attribute_handle != rhs.m_attribute_handle;
}

template <typename T>
bool saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::operator<(Undoable_Attribute_Data_Handle_Integral_Type<T> const& rhs)
{
    return m_attribute_handle < rhs.m_attribute_handle;
}

template <typename T>
bool saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::operator>(Undoable_Attribute_Data_Handle_Integral_Type<T> const& rhs)
{
    return m_attribute_handle > rhs.m_attribute_handle;
}

template <typename T>
bool saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::operator<=(Undoable_Attribute_Data_Handle_Integral_Type<T> const& rhs)
{
    return m_attribute_handle <= rhs.m_attribute_handle;
}

template <typename T>
bool saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::operator>=(Undoable_Attribute_Data_Handle_Integral_Type<T> const& rhs)
{
    return m_attribute_handle >= rhs.m_attribute_handle;
}

// Comparison Operators to Untyped Handle
//============================================================
template <typename T>
bool saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::operator==(Undoable_Attribute_Data_Handle const& rhs)
{
    return m_attribute_handle == rhs.m_attribute_handle;
}

template <typename T>
bool saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::operator!=(Undoable_Attribute_Data_Handle const& rhs)
{
    return m_attribute_handle != rhs.m_attribute_handle;
}

// Comparison Operators for compare to the null handle
//============================================================

template <typename T>
bool saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::operator==(Null_Integer_ID_Type const& )
{
    return is_null();
}

template <typename T>
bool saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::operator!=(Null_Integer_ID_Type const& )
{
    return is_valid();
}

// Protected Helpers
//============================================================

template <typename T>
saklib::internal::Command_History& saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::get_command_history()
{
    if (is_valid())
    {
        return *mp_command_history;
    }
    else
    {
        throw Bad_Data_Handle();
    }
}

template <typename T>
saklib::internal::Command_History const& saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T>::cget_command_history() const
{
    if (is_valid())
    {
        return *mp_command_history;
    }
    else
    {
        throw Bad_Data_Handle();
    }
}

// Forced Instantiation
//============================================================
// include char types?
template saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<short>;
template saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<unsigned short>;
template saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<int>;
template saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<unsigned int>;
template saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<long>;
template saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<unsigned long>;
template saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<long long>;
template saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<unsigned long long>;
