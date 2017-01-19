#include "undoable_attribute_data_handle.h"

#include "undoable_attribute_data_handle_bool.h"
#include "undoable_attribute_data_handle_int.h"

//---------------------------------------------------------------------------
// Undoable_Attribute_Data_Handle
//---------------------------------------------------------------------------

// Special 6
//============================================================
saklib::internal::Undoable_Attribute_Data_Handle::Undoable_Attribute_Data_Handle():
    m_attribute_handle(),
    mp_command_history(nullptr)
{
}

saklib::internal::Undoable_Attribute_Data_Handle::Undoable_Attribute_Data_Handle(Attribute_Data_Handle const& a_attribute_handle, Command_History& ar_command_history):
    m_attribute_handle(a_attribute_handle),
    mp_command_history(&ar_command_history)
{
    assert(is_valid());
}

saklib::internal::Undoable_Attribute_Data_Handle::Undoable_Attribute_Data_Handle(Attribute_Data_Handle&& a_attribute_handle, Command_History& ar_command_history):
    m_attribute_handle(std::move(a_attribute_handle)),
    mp_command_history(&ar_command_history)
{
    assert(is_valid());
}

saklib::internal::Undoable_Attribute_Data_Handle::~Undoable_Attribute_Data_Handle() = default;

saklib::internal::Undoable_Attribute_Data_Handle::Undoable_Attribute_Data_Handle(Undoable_Attribute_Data_Handle const& other) = default;
saklib::internal::Undoable_Attribute_Data_Handle& saklib::internal::Undoable_Attribute_Data_Handle::operator=(Undoable_Attribute_Data_Handle const& other) = default;

saklib::internal::Undoable_Attribute_Data_Handle::Undoable_Attribute_Data_Handle(Undoable_Attribute_Data_Handle && other):
    m_attribute_handle(std::move(other.m_attribute_handle)),
    mp_command_history(std::move(other.mp_command_history))
{
    other.mp_command_history = nullptr;
}

saklib::internal::Undoable_Attribute_Data_Handle& saklib::internal::Undoable_Attribute_Data_Handle::operator=(Undoable_Attribute_Data_Handle && other)
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
bool saklib::internal::Undoable_Attribute_Data_Handle::is_valid() const
{
    return m_attribute_handle.is_valid() && mp_command_history != nullptr;
}

bool saklib::internal::Undoable_Attribute_Data_Handle::is_null() const
{
    return m_attribute_handle.is_null();
}

saklib::internal::Undoable_Attribute_Data_Handle::handle_type saklib::internal::Undoable_Attribute_Data_Handle::cget_element_handle() const
{
    return m_attribute_handle.cget_element_handle();
}

std::size_t saklib::internal::Undoable_Attribute_Data_Handle::cget_element_reference_count() const
{
    return m_attribute_handle.cget_element_reference_count();
}

std::size_t saklib::internal::Undoable_Attribute_Data_Handle::cget_attribute_index() const
{
    return m_attribute_handle.cget_attribute_index();
}

// Attribute_Data Wrapper Interface
//============================================================
std::string const& saklib::internal::Undoable_Attribute_Data_Handle::cget_name() const
{
    return m_attribute_handle.cget_name();
}

std::string const& saklib::internal::Undoable_Attribute_Data_Handle::cget_type() const
{
    return m_attribute_handle.cget_type();
}

std::string saklib::internal::Undoable_Attribute_Data_Handle::cget_value_string() const
{
    return m_attribute_handle.cget_value_string();
}

bool saklib::internal::Undoable_Attribute_Data_Handle::is_bool() const
{
    return is_bool_type<bool>();
}

saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<bool> saklib::internal::Undoable_Attribute_Data_Handle::cget_bool() const
{
    return cget_bool_type<bool>();
}

template <typename T>
bool saklib::internal::Undoable_Attribute_Data_Handle::is_bool_type() const
{
    return m_attribute_handle.is_bool_type<T>();
}

template <typename T>
saklib::internal::Undoable_Attribute_Data_Handle_Boolean_Type<T> saklib::internal::Undoable_Attribute_Data_Handle::cget_bool_type() const
{
    if (is_bool_type<T>())
    {
        return Undoable_Attribute_Data_Handle_Boolean_Type<T>(m_attribute_handle.cget_bool_type<T>(), *mp_command_history);
    }
    else
    {
        return Undoable_Attribute_Data_Handle_Boolean_Type<T>();
    }
}

bool saklib::internal::Undoable_Attribute_Data_Handle::is_int() const
{
    return is_int_type<int>();
}

saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<int> saklib::internal::Undoable_Attribute_Data_Handle::cget_int() const
{
    return cget_int_type<int>();
}

template <typename T>
bool saklib::internal::Undoable_Attribute_Data_Handle::is_int_type() const
{
    return m_attribute_handle.is_int_type<T>();
}

template <typename T>
saklib::internal::Undoable_Attribute_Data_Handle_Integral_Type<T> saklib::internal::Undoable_Attribute_Data_Handle::cget_int_type() const
{
    if (is_int_type<T>())
    {
        return Undoable_Attribute_Data_Handle_Integral_Type<T>(m_attribute_handle.cget_int_type<T>(), *mp_command_history);
    }
    else
    {
        return Undoable_Attribute_Data_Handle_Integral_Type<T>();
    }
}

// Comparison Operators
//============================================================
bool saklib::internal::Undoable_Attribute_Data_Handle::operator==(Undoable_Attribute_Data_Handle const& rhs)
{
    return (m_attribute_handle == rhs.m_attribute_handle) && (mp_command_history == rhs.mp_command_history);
}

bool saklib::internal::Undoable_Attribute_Data_Handle::operator!=(Undoable_Attribute_Data_Handle const& rhs)
{
    return (m_attribute_handle != rhs.m_attribute_handle) && (mp_command_history != rhs.mp_command_history);
}

bool saklib::internal::Undoable_Attribute_Data_Handle::operator<(Undoable_Attribute_Data_Handle const& rhs)
{
    return (m_attribute_handle < rhs.m_attribute_handle) && (mp_command_history < rhs.mp_command_history);
}

bool saklib::internal::Undoable_Attribute_Data_Handle::operator>(Undoable_Attribute_Data_Handle const& rhs)
{
    return (m_attribute_handle > rhs.m_attribute_handle) && (mp_command_history > rhs.mp_command_history);
}

bool saklib::internal::Undoable_Attribute_Data_Handle::operator<=(Undoable_Attribute_Data_Handle const& rhs)
{
    return (m_attribute_handle <= rhs.m_attribute_handle) && (mp_command_history <= rhs.mp_command_history);
}

bool saklib::internal::Undoable_Attribute_Data_Handle::operator>=(Undoable_Attribute_Data_Handle const& rhs)
{
    return (m_attribute_handle >= rhs.m_attribute_handle) && (mp_command_history >= rhs.mp_command_history);
}

// Comparison Operators for compare to the null handle
//============================================================
bool saklib::internal::Undoable_Attribute_Data_Handle::operator==(Null_Integer_ID_Type const& )
{
    return is_null();
}

bool saklib::internal::Undoable_Attribute_Data_Handle::operator!=(Null_Integer_ID_Type const& )
{
    return is_valid();
}

// Protected Helpers
//============================================================
saklib::internal::Command_History& saklib::internal::Undoable_Attribute_Data_Handle::get_command_history()
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

saklib::internal::Command_History const& saklib::internal::Undoable_Attribute_Data_Handle::cget_command_history() const
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
