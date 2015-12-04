#include "undoable_attribute_data_handle_bool.h"

#include "undoable_attribute_data_handle.h"

#include "command_history.h"
#include "command.h"

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


//---------------------------------------------------------------------------
// Undoable_Attribute_Data_Handle_Bool
//---------------------------------------------------------------------------

// Special 6
//============================================================

saklib::internal::Undoable_Attribute_Data_Handle_Bool::Undoable_Attribute_Data_Handle_Bool():
    m_attribute_handle(),
    mp_command_history(nullptr)
{
}

saklib::internal::Undoable_Attribute_Data_Handle_Bool::Undoable_Attribute_Data_Handle_Bool(Attribute_Data_Handle_Bool const& a_attribute_handle, Command_History* ap_command_history):
    m_attribute_handle(a_attribute_handle),
    mp_command_history(ap_command_history)
{
}

saklib::internal::Undoable_Attribute_Data_Handle_Bool::Undoable_Attribute_Data_Handle_Bool(Attribute_Data_Handle_Bool && a_attribute_handle, Command_History* ap_command_history):
    m_attribute_handle(std::move(a_attribute_handle)),
    mp_command_history(ap_command_history)
{
}

saklib::internal::Undoable_Attribute_Data_Handle_Bool::~Undoable_Attribute_Data_Handle_Bool() = default;

saklib::internal::Undoable_Attribute_Data_Handle_Bool::Undoable_Attribute_Data_Handle_Bool(Undoable_Attribute_Data_Handle_Bool const& other) = default;

saklib::internal::Undoable_Attribute_Data_Handle_Bool& saklib::internal::Undoable_Attribute_Data_Handle_Bool::operator=(Undoable_Attribute_Data_Handle_Bool const& other) = default;

saklib::internal::Undoable_Attribute_Data_Handle_Bool::Undoable_Attribute_Data_Handle_Bool(Undoable_Attribute_Data_Handle_Bool && other):
    m_attribute_handle(std::move(other.m_attribute_handle)),
    mp_command_history(std::move(other.mp_command_history))
{
    other.mp_command_history = nullptr;
}

saklib::internal::Undoable_Attribute_Data_Handle_Bool& saklib::internal::Undoable_Attribute_Data_Handle_Bool::operator=(Undoable_Attribute_Data_Handle_Bool && other)
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

bool saklib::internal::Undoable_Attribute_Data_Handle_Bool::is_valid() const
{
    return m_attribute_handle.is_valid();
}

bool saklib::internal::Undoable_Attribute_Data_Handle_Bool::is_null() const
{
    return m_attribute_handle.is_null();
}

saklib::internal::Undoable_Attribute_Data_Handle_Bool::handle_type saklib::internal::Undoable_Attribute_Data_Handle_Bool::cget_element_handle() const
{
    return m_attribute_handle.cget_element_handle();
}

std::size_t saklib::internal::Undoable_Attribute_Data_Handle_Bool::cget_element_reference_count() const
{
    return m_attribute_handle.cget_element_reference_count();
}

std::size_t saklib::internal::Undoable_Attribute_Data_Handle_Bool::cget_attribute_index() const
{
    return m_attribute_handle.cget_attribute_index();
}

// Attribute_Data Wrapper Interface
//============================================================
std::string const& saklib::internal::Undoable_Attribute_Data_Handle_Bool::cget_name() const
{
    return m_attribute_handle.cget_name();
}

std::string const& saklib::internal::Undoable_Attribute_Data_Handle_Bool::cget_type() const
{
    return m_attribute_handle.cget_type();
}

std::string saklib::internal::Undoable_Attribute_Data_Handle_Bool::cget_value_string() const
{
    return m_attribute_handle.cget_value_string();
}

bool saklib::internal::Undoable_Attribute_Data_Handle_Bool::cget_value() const
{
    return m_attribute_handle.cget_value();
}

bool saklib::internal::Undoable_Attribute_Data_Handle_Bool::can_set_value_to(bool a_value) const
{
    return m_attribute_handle.can_set_value_to(a_value);
}
/*
bool saklib::internal::Undoable_Attribute_Data_Handle_Bool::try_set_value(bool a_value)
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
*/
bool saklib::internal::Undoable_Attribute_Data_Handle_Bool::set_value(bool a_value)
{
    if (can_set_value_to(a_value))
    {
        get_command_history().emplace_execute<Command_Attribute_Data_Handle_Bool__Set_Value>(m_attribute_handle, a_value);
        //get_command_history().emplace_execute<Command_Attribute_Data_Handle_Bool_Set_Value>(m_attribute_handle, a_value);
        return true;
    }
    else
    {
        return false;
    }
}

// Comparison Operators
//============================================================

bool saklib::internal::Undoable_Attribute_Data_Handle_Bool::operator==(Undoable_Attribute_Data_Handle_Bool const& rhs)
{
    return m_attribute_handle == rhs.m_attribute_handle;
}

bool saklib::internal::Undoable_Attribute_Data_Handle_Bool::operator!=(Undoable_Attribute_Data_Handle_Bool const& rhs)
{
    return m_attribute_handle != rhs.m_attribute_handle;
}

bool saklib::internal::Undoable_Attribute_Data_Handle_Bool::operator<(Undoable_Attribute_Data_Handle_Bool const& rhs)
{
    return m_attribute_handle < rhs.m_attribute_handle;
}

bool saklib::internal::Undoable_Attribute_Data_Handle_Bool::operator>(Undoable_Attribute_Data_Handle_Bool const& rhs)
{
    return m_attribute_handle > rhs.m_attribute_handle;
}

bool saklib::internal::Undoable_Attribute_Data_Handle_Bool::operator<=(Undoable_Attribute_Data_Handle_Bool const& rhs)
{
    return m_attribute_handle <= rhs.m_attribute_handle;
}

bool saklib::internal::Undoable_Attribute_Data_Handle_Bool::operator>=(Undoable_Attribute_Data_Handle_Bool const& rhs)
{
    return m_attribute_handle >= rhs.m_attribute_handle;
}
/*
// Comparison Operators to Untyped Handle
//============================================================
bool saklib::internal::Undoable_Attribute_Data_Handle_Bool::operator==(Undoable_Attribute_Data_Handle const& rhs)
{
    return m_attribute_handle == rhs.m_attribute_handle;
}

bool saklib::internal::Undoable_Attribute_Data_Handle_Bool::operator!=(Undoable_Attribute_Data_Handle const& rhs)
{
    return m_attribute_handle != rhs.m_attribute_handle;
}
*/
// Comparison Operators for compare to the null handle
//============================================================
bool saklib::internal::Undoable_Attribute_Data_Handle_Bool::operator==(Null_Handle_Type const& rhs)
{
    return m_attribute_handle == rhs;
}

bool saklib::internal::Undoable_Attribute_Data_Handle_Bool::operator!=(Null_Handle_Type const& rhs)
{
    return m_attribute_handle != rhs;
}

// Protected Helpers
//============================================================
saklib::internal::Command_History& saklib::internal::Undoable_Attribute_Data_Handle_Bool::get_command_history()
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

saklib::internal::Command_History const& saklib::internal::Undoable_Attribute_Data_Handle_Bool::cget_command_history() const
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
