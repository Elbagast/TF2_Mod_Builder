#include "undoable_attribute_data_handle_bool.h"

#include "undoable_attribute_data_handle.h"

#include "command_history.h"
#include "command.h"
/*
#include "command_attribute_data_boolean_type.h"

namespace saklib
{
    namespace internal
    {
        class Command_Attribute_Data_Handle_Bool_Set_Value :
                public Command
        {
        public:
            Command_Attribute_Data_Handle_Bool_Set_Value(Attribute_Data_Handle_Bool const& a_attribute_handle, bool a_new_value);
            ~Command_Attribute_Data_Handle_Bool_Set_Value() override;

        protected:
            void v_execute() override;
            void v_unexecute() override;
        private:
            Attribute_Data_Handle_Bool m_attribute_handle;
            bool m_old_value;
            bool m_new_value;
        };
    }
}

saklib::internal::Command_Attribute_Data_Handle_Bool_Set_Value::Command_Attribute_Data_Handle_Bool_Set_Value(Attribute_Data_Handle_Bool const& a_attribute_handle, bool a_new_value):
    m_attribute_handle(a_attribute_handle),
    m_old_value(m_attribute_handle.cget_value()),
    m_new_value(a_new_value)
{}

saklib::internal::Command_Attribute_Data_Handle_Bool_Set_Value::~Command_Attribute_Data_Handle_Bool_Set_Value() = default;

void saklib::internal::Command_Attribute_Data_Handle_Bool_Set_Value::v_execute()
{
    m_attribute_handle.set_value(m_new_value);
}

void saklib::internal::Command_Attribute_Data_Handle_Bool_Set_Value::v_unexecute()
{
    m_attribute_handle.set_value(m_old_value);
}

*/
//---------------------------------------------------------------------------
// Undoable_Attribute_Data_Handle_Boolean_Type<T>
//---------------------------------------------------------------------------

// Special 6
//============================================================
template <typename T>
saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<T>::Undoable_Attribute_Data_Handle_Boolean_Type():
    m_attribute_handle(),
    mp_command_history(nullptr)
{
}

template <typename T>
saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<T>::Undoable_Attribute_Data_Handle_Boolean_Type(Attribute_Data_Handle_Boolean_Type<T> const& a_attribute_handle, Command_History& ar_command_history):
    m_attribute_handle(a_attribute_handle),
    mp_command_history(&ar_command_history)
{
    assert(m_attribute_handle.is_valid());
}

template <typename T>
saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<T>::Undoable_Attribute_Data_Handle_Boolean_Type(Attribute_Data_Handle_Boolean_Type<T> && a_attribute_handle, Command_History& ar_command_history):
    m_attribute_handle(std::move(a_attribute_handle)),
    mp_command_history(&ar_command_history)
{
    assert(m_attribute_handle.is_valid());
}

template <typename T>
saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<T>::~Undoable_Attribute_Data_Handle_Boolean_Type() = default;

template <typename T>
saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<T>::Undoable_Attribute_Data_Handle_Boolean_Type(Undoable_Attribute_Data_Handle_Boolean_Type<T> const& other) = default;

template <typename T>
saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<T>& saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<T>::operator=(Undoable_Attribute_Data_Handle_Boolean_Type<T> const& other) = default;

template <typename T>
saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<T>::Undoable_Attribute_Data_Handle_Boolean_Type(Undoable_Attribute_Data_Handle_Boolean_Type<T> && other):
    m_attribute_handle(std::move(other.m_attribute_handle)),
    mp_command_history(std::move(other.mp_command_history))
{
    other.mp_command_history = nullptr;
}

template <typename T>
saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<T>& saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<T>::operator=(Undoable_Attribute_Data_Handle_Boolean_Type<T> && other)
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
bool saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<T>::is_valid() const
{
    return m_attribute_handle.is_valid();
}

template <typename T>
bool saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<T>::is_null() const
{
    return m_attribute_handle.is_null();
}

template <typename T>
typename saklib::internal::Undoable_Attribute_Data_Handle_Bool::handle_type saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<T>::cget_element_handle() const
{
    return m_attribute_handle.cget_element_handle();
}

template <typename T>
std::size_t saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<T>::cget_element_reference_count() const
{
    return m_attribute_handle.cget_element_reference_count();
}

template <typename T>
std::size_t saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<T>::cget_attribute_index() const
{
    return m_attribute_handle.cget_attribute_index();
}

// Attribute_Data Wrapper Interface
//============================================================
template <typename T>
std::string const& saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<T>::cget_name() const
{
    return m_attribute_handle.cget_name();
}

template <typename T>
std::string const& saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<T>::cget_type() const
{
    return m_attribute_handle.cget_type();
}

template <typename T>
std::string saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<T>::cget_value_string() const
{
    return m_attribute_handle.cget_value_string();
}

template <typename T>
typename saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<T>::bool_type saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<T>::cget_value() const
{
    return m_attribute_handle.cget_value();
}

template <typename T>
bool saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<T>::can_set_value_to(bool_type a_value) const
{
    return m_attribute_handle.can_set_value_to(a_value);
}

template <typename T>
bool saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<T>::try_set_value(bool_type a_value)
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
void saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<T>::set_value(bool_type a_value)
{
    // Command intercept

    using Command_Attribute_Data_Handle_Bool_Set_Value = Command_Simple_Stored_Get_Set
    <
    Attribute_Data_Handle_Boolean_Type<T>,
    Attribute_Data_Handle_Boolean_Type<T>::bool_type,
    Attribute_Data_Handle_Boolean_Type<T>::bool_type,
    &Attribute_Data_Handle_Boolean_Type<T>::cget_value,
    void,
    Attribute_Data_Handle_Boolean_Type<T>::bool_type,
    &Attribute_Data_Handle_Boolean_Type<T>::set_value
    >;

    get_command_history().emplace_execute<Command_Attribute_Data_Handle_Bool_Set_Value>(m_attribute_handle, a_value);
}

// Comparison Operators
//============================================================

template <typename T>
bool saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<T>::operator==(Undoable_Attribute_Data_Handle_Boolean_Type<T> const& rhs)
{
    return m_attribute_handle == rhs.m_attribute_handle;
}

template <typename T>
bool saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<T>::operator!=(Undoable_Attribute_Data_Handle_Boolean_Type<T> const& rhs)
{
    return m_attribute_handle != rhs.m_attribute_handle;
}

template <typename T>
bool saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<T>::operator<(Undoable_Attribute_Data_Handle_Boolean_Type<T> const& rhs)
{
    return m_attribute_handle < rhs.m_attribute_handle;
}

template <typename T>
bool saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<T>::operator>(Undoable_Attribute_Data_Handle_Boolean_Type<T> const& rhs)
{
    return m_attribute_handle > rhs.m_attribute_handle;
}

template <typename T>
bool saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<T>::operator<=(Undoable_Attribute_Data_Handle_Boolean_Type<T> const& rhs)
{
    return m_attribute_handle <= rhs.m_attribute_handle;
}

template <typename T>
bool saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<T>::operator>=(Undoable_Attribute_Data_Handle_Boolean_Type<T> const& rhs)
{
    return m_attribute_handle >= rhs.m_attribute_handle;
}
// Comparison Operators to Untyped Handle
//============================================================
template <typename T>
bool saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<T>::operator==(Undoable_Attribute_Data_Handle const& rhs)
{
    return m_attribute_handle == rhs.m_attribute_handle;
}

template <typename T>
bool saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<T>::operator!=(Undoable_Attribute_Data_Handle const& rhs)
{
    return m_attribute_handle != rhs.m_attribute_handle;
}

// Comparison Operators for compare to the null handle
//============================================================
template <typename T>
bool saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<T>::operator==(Null_Handle_Type const& rhs)
{
    return m_attribute_handle == rhs;
}

template <typename T>
bool saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<T>::operator!=(Null_Handle_Type const& rhs)
{
    return m_attribute_handle != rhs;
}

// Protected Helpers
//============================================================
template <typename T>
saklib::internal::Command_History& saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<T>::get_command_history()
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
saklib::internal::Command_History const& saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<T>::cget_command_history() const
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
template saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<bool>;
