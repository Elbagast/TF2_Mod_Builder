#include "undoable_attribute_data_handle_int.h"

#include "undoable_attribute_data_handle.h"


#include "command_history.h"
#include "command.h"

namespace saklib
{
    namespace internal
    {
        class Command_Attribute_Data_Handle_Int_Set_Value :
                public Command
        {
        public:
            Command_Attribute_Data_Handle_Int_Set_Value(Attribute_Data_Handle_Int const& a_attribute_handle, int a_new_value);
            ~Command_Attribute_Data_Handle_Int_Set_Value() override;

        protected:
            void v_execute() override;
            void v_unexecute() override;
        private:
            Attribute_Data_Handle_Int m_attribute_handle;
            int m_old_value;
            int m_new_value;
        };
    }
}

saklib::internal::Command_Attribute_Data_Handle_Int_Set_Value::Command_Attribute_Data_Handle_Int_Set_Value(Attribute_Data_Handle_Int const& a_attribute_handle, int a_new_value):
    m_attribute_handle(a_attribute_handle),
    m_old_value(m_attribute_handle.cget_value()),
    m_new_value(a_new_value)
{}

saklib::internal::Command_Attribute_Data_Handle_Int_Set_Value::~Command_Attribute_Data_Handle_Int_Set_Value() = default;

void saklib::internal::Command_Attribute_Data_Handle_Int_Set_Value::v_execute()
{
    m_attribute_handle.set_value(m_new_value);
}

void saklib::internal::Command_Attribute_Data_Handle_Int_Set_Value::v_unexecute()
{
    m_attribute_handle.set_value(m_old_value);
}

//---------------------------------------------------------------------------
// Undoable_Attribute_Data_Handle_Int
//---------------------------------------------------------------------------

// Special 6
//============================================================
saklib::internal::Undoable_Attribute_Data_Handle_Int::Undoable_Attribute_Data_Handle_Int():
    m_attribute_handle(),
    mp_command_history(nullptr)
{
}

saklib::internal::Undoable_Attribute_Data_Handle_Int::Undoable_Attribute_Data_Handle_Int(Attribute_Data_Handle_Int const& a_attribute_handle, Command_History* ap_command_history):
    m_attribute_handle(a_attribute_handle),
    mp_command_history(ap_command_history)
{
}

saklib::internal::Undoable_Attribute_Data_Handle_Int::Undoable_Attribute_Data_Handle_Int(Attribute_Data_Handle_Int && a_attribute_handle, Command_History* ap_command_history):
    m_attribute_handle(std::move(a_attribute_handle)),
    mp_command_history(ap_command_history)
{
}

saklib::internal::Undoable_Attribute_Data_Handle_Int::~Undoable_Attribute_Data_Handle_Int() = default;

saklib::internal::Undoable_Attribute_Data_Handle_Int::Undoable_Attribute_Data_Handle_Int(Undoable_Attribute_Data_Handle_Int const& other) = default;

saklib::internal::Undoable_Attribute_Data_Handle_Int& saklib::internal::Undoable_Attribute_Data_Handle_Int::operator=(Undoable_Attribute_Data_Handle_Int const& other) = default;

saklib::internal::Undoable_Attribute_Data_Handle_Int::Undoable_Attribute_Data_Handle_Int(Undoable_Attribute_Data_Handle_Int && other):
    m_attribute_handle(std::move(other.m_attribute_handle)),
    mp_command_history(std::move(other.mp_command_history))
{
    other.mp_command_history = nullptr;
}

saklib::internal::Undoable_Attribute_Data_Handle_Int& saklib::internal::Undoable_Attribute_Data_Handle_Int::operator=(Undoable_Attribute_Data_Handle_Int && other)
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

bool saklib::internal::Undoable_Attribute_Data_Handle_Int::is_valid() const
{
    return m_attribute_handle.is_valid();
}

bool saklib::internal::Undoable_Attribute_Data_Handle_Int::is_null() const
{
    return m_attribute_handle.is_null();
}

saklib::internal::Undoable_Attribute_Data_Handle_Int::handle_type saklib::internal::Undoable_Attribute_Data_Handle_Int::cget_element_handle() const
{
    return m_attribute_handle.cget_element_handle();
}

std::size_t saklib::internal::Undoable_Attribute_Data_Handle_Int::cget_element_reference_count() const
{
    return m_attribute_handle.cget_element_reference_count();
}

std::size_t saklib::internal::Undoable_Attribute_Data_Handle_Int::cget_attribute_index() const
{
    return m_attribute_handle.cget_attribute_index();
}

// Attribute_Data Wrapper Interface
//============================================================
std::string const& saklib::internal::Undoable_Attribute_Data_Handle_Int::cget_name() const
{
    return m_attribute_handle.cget_name();
}

std::string const& saklib::internal::Undoable_Attribute_Data_Handle_Int::cget_type() const
{
    return m_attribute_handle.cget_type();
}

std::string saklib::internal::Undoable_Attribute_Data_Handle_Int::cget_value_string() const
{
    return m_attribute_handle.cget_value_string();
}

int saklib::internal::Undoable_Attribute_Data_Handle_Int::cget_value() const
{
    return m_attribute_handle.cget_value();
}

bool saklib::internal::Undoable_Attribute_Data_Handle_Int::can_set_value_to(int a_value) const
{
    return m_attribute_handle.can_set_value_to(a_value);
}
/*
bool saklib::internal::Undoable_Attribute_Data_Handle_Int::try_set_value(int a_value)
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
bool saklib::internal::Undoable_Attribute_Data_Handle_Int::set_value(int a_value)
{
    if (can_set_value_to(a_value))
    {
        get_command_history().emplace_execute<Command_Attribute_Data_Handle_Int_Set_Value>(m_attribute_handle, a_value);
        return true;
    }
    else
    {
        return false;
    }
}

int saklib::internal::Undoable_Attribute_Data_Handle_Int::cget_lowest_value() const
{
    return m_attribute_handle.cget_lowest_value();
}

int saklib::internal::Undoable_Attribute_Data_Handle_Int::cget_highest_value() const
{
    return m_attribute_handle.cget_highest_value();
}

// Comparison Operators
//============================================================
bool saklib::internal::Undoable_Attribute_Data_Handle_Int::operator==(Undoable_Attribute_Data_Handle_Int const& rhs)
{
    return m_attribute_handle == rhs.m_attribute_handle;
}

bool saklib::internal::Undoable_Attribute_Data_Handle_Int::operator!=(Undoable_Attribute_Data_Handle_Int const& rhs)
{
    return m_attribute_handle != rhs.m_attribute_handle;
}

bool saklib::internal::Undoable_Attribute_Data_Handle_Int::operator<(Undoable_Attribute_Data_Handle_Int const& rhs)
{
    return m_attribute_handle < rhs.m_attribute_handle;
}

bool saklib::internal::Undoable_Attribute_Data_Handle_Int::operator>(Undoable_Attribute_Data_Handle_Int const& rhs)
{
    return m_attribute_handle > rhs.m_attribute_handle;
}

bool saklib::internal::Undoable_Attribute_Data_Handle_Int::operator<=(Undoable_Attribute_Data_Handle_Int const& rhs)
{
    return m_attribute_handle <= rhs.m_attribute_handle;
}

bool saklib::internal::Undoable_Attribute_Data_Handle_Int::operator>=(Undoable_Attribute_Data_Handle_Int const& rhs)
{
    return m_attribute_handle >= rhs.m_attribute_handle;
}
/*
// Comparison Operators to Untyped Handle
//============================================================
bool saklib::internal::Undoable_Attribute_Data_Handle_Int::operator==(Undoable_Attribute_Data_Handle const& rhs)
{
    return m_attribute_handle == rhs.m_attribute_handle;
}

bool saklib::internal::Undoable_Attribute_Data_Handle_Int::operator!=(Undoable_Attribute_Data_Handle const& rhs)
{
    return m_attribute_handle != rhs.m_attribute_handle;
}
*/
// Comparison Operators for compare to the null handle
//============================================================
bool saklib::internal::Undoable_Attribute_Data_Handle_Int::operator==(Null_Handle_Type const& )
{
    return is_null();
}

bool saklib::internal::Undoable_Attribute_Data_Handle_Int::operator!=(Null_Handle_Type const& )
{
    return is_valid();
}

// Protected Helpers
//============================================================
saklib::internal::Command_History& saklib::internal::Undoable_Attribute_Data_Handle_Int::get_command_history()
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

saklib::internal::Command_History const& saklib::internal::Undoable_Attribute_Data_Handle_Int::cget_command_history() const
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
