#include "undoable_element_data_handle.h"

#include "undoable_attribute_data_handle.h"

#include "command_history.h"
#include "command.h"

namespace saklib
{
    namespace internal
    {
        class Command_Element_Data_Handle_Set_Name :
                public Command
        {
        public:
            Command_Element_Data_Handle_Set_Name(Element_Data_Handle const& a_element_handle, std::string const& a_new_name);
            ~Command_Element_Data_Handle_Set_Name() override;

        protected:
            void v_execute() override;
            void v_unexecute() override;
        private:
            Element_Data_Handle m_element_handle;
            std::string m_old_name;
            std::string m_new_name;
        };
    }
}

saklib::internal::Command_Element_Data_Handle_Set_Name::Command_Element_Data_Handle_Set_Name(Element_Data_Handle const& a_element_handle, std::string const& a_new_name):
    m_element_handle(a_element_handle),
    m_old_name(m_element_handle.cget_name()),
    m_new_name(a_new_name)
{}

saklib::internal::Command_Element_Data_Handle_Set_Name::~Command_Element_Data_Handle_Set_Name() = default;

void saklib::internal::Command_Element_Data_Handle_Set_Name::v_execute()
{
    m_element_handle.set_name(m_new_name);
}

void saklib::internal::Command_Element_Data_Handle_Set_Name::v_unexecute()
{
    m_element_handle.set_name(m_old_name);
}


//---------------------------------------------------------------------------
// Undoable_Element_Data_Handle
//---------------------------------------------------------------------------
// Special 6
//============================================================
saklib::internal::Undoable_Element_Data_Handle::Undoable_Element_Data_Handle():
    m_element_handle(),
    mp_command_history(nullptr)
{
}

saklib::internal::Undoable_Element_Data_Handle::Undoable_Element_Data_Handle(Element_Data_Handle const& a_data_handle, Command_History& ar_command_history):
    m_element_handle(a_data_handle),
    mp_command_history(&ar_command_history)
{
}

saklib::internal::Undoable_Element_Data_Handle::Undoable_Element_Data_Handle(Element_Data_Handle && a_data_handle, Command_History& ar_command_history):
    m_element_handle(std::move(a_data_handle)),
    mp_command_history(&ar_command_history)
{
}

saklib::internal::Undoable_Element_Data_Handle::~Undoable_Element_Data_Handle() = default;

saklib::internal::Undoable_Element_Data_Handle::Undoable_Element_Data_Handle(Undoable_Element_Data_Handle const& other) = default;

saklib::internal::Undoable_Element_Data_Handle& saklib::internal::Undoable_Element_Data_Handle::operator=(Undoable_Element_Data_Handle const& other) = default;

saklib::internal::Undoable_Element_Data_Handle::Undoable_Element_Data_Handle(Undoable_Element_Data_Handle && other):
    m_element_handle(std::move(other.m_element_handle)),
    mp_command_history(std::move(other.mp_command_history))
{
    other.mp_command_history = nullptr;
}

saklib::internal::Undoable_Element_Data_Handle& saklib::internal::Undoable_Element_Data_Handle::operator=(Undoable_Element_Data_Handle && other)
{
    if (&other != this)
    {
        m_element_handle = std::move(other.m_element_handle);
        mp_command_history = std::move(other.mp_command_history);

        other.mp_command_history = nullptr;
    }
    return *this;
}

// Interface
//============================================================
bool saklib::internal::Undoable_Element_Data_Handle::is_valid() const
{
    return m_element_handle.is_valid();
}

bool saklib::internal::Undoable_Element_Data_Handle::is_null() const
{
    return m_element_handle.is_null();
}

saklib::internal::Undoable_Element_Data_Handle::handle_type saklib::internal::Undoable_Element_Data_Handle::cget_handle() const
{
    return m_element_handle.cget_handle();
}

std::size_t saklib::internal::Undoable_Element_Data_Handle::cget_reference_count() const
{
    return m_element_handle.cget_reference_count();
}

// Element_Data Wrapper Interface
//============================================================
std::string const& saklib::internal::Undoable_Element_Data_Handle::cget_type() const
{
    return m_element_handle.cget_type();
}

std::string const& saklib::internal::Undoable_Element_Data_Handle::cget_name() const
{
    return m_element_handle.cget_name();
}

bool saklib::internal::Undoable_Element_Data_Handle::set_name(std::string const& a_name)
{
    // This should actually issue a command
    if (cget_name() != a_name)
    {
        get_command_history().emplace_execute<Command_Element_Data_Handle_Set_Name>(m_element_handle, a_name);
        return true;
    }
    else
    {
        return false;
    }
}

std::size_t saklib::internal::Undoable_Element_Data_Handle::cget_attribute_count() const
{
    return m_element_handle.cget_attribute_count();
}

saklib::internal::Undoable_Attribute_Data_Handle saklib::internal::Undoable_Element_Data_Handle::cget_attribute_at(std::size_t a_index) const
{
    if(is_valid() && a_index < cget_attribute_count())
    {
        return Undoable_Attribute_Data_Handle(m_element_handle.cget_attribute_at(a_index), mp_command_history);
    }
    else
    {
        return Undoable_Attribute_Data_Handle();
    }
}

std::vector<saklib::internal::Undoable_Attribute_Data_Handle> saklib::internal::Undoable_Element_Data_Handle::cget_attributes() const
{
    std::size_t l_attribute_count = cget_attribute_count();
    std::vector<Undoable_Attribute_Data_Handle> l_result{};
    for (std::size_t index = 0; index != l_attribute_count; ++index)
    {
        l_result.push_back(cget_attribute_at(index));
    }
    return l_result;
}

// Comparison Operators
//============================================================
bool saklib::internal::Undoable_Element_Data_Handle::operator==(Undoable_Element_Data_Handle const& rhs)
{
    return m_element_handle == rhs.m_element_handle;
}

bool saklib::internal::Undoable_Element_Data_Handle::operator!=(Undoable_Element_Data_Handle const& rhs)
{
    return m_element_handle != rhs.m_element_handle;
}

bool saklib::internal::Undoable_Element_Data_Handle::operator<(Undoable_Element_Data_Handle const& rhs)
{
    return m_element_handle < rhs.m_element_handle;
}

bool saklib::internal::Undoable_Element_Data_Handle::operator>(Undoable_Element_Data_Handle const& rhs)
{
    return m_element_handle > rhs.m_element_handle;
}

bool saklib::internal::Undoable_Element_Data_Handle::operator<=(Undoable_Element_Data_Handle const& rhs)
{
    return m_element_handle <= rhs.m_element_handle;
}

bool saklib::internal::Undoable_Element_Data_Handle::operator>=(Undoable_Element_Data_Handle const& rhs)
{
    return m_element_handle >= rhs.m_element_handle;
}

// Comparison Operators for compare to the null handle
//============================================================
bool saklib::internal::Undoable_Element_Data_Handle::operator==(Null_Handle_Type const& )
{
    return is_null();
}

bool saklib::internal::Undoable_Element_Data_Handle::operator!=(Null_Handle_Type const& )
{
    return is_valid();
}

// Protected Helpers
//============================================================
saklib::internal::Command_History& saklib::internal::Undoable_Element_Data_Handle::get_command_history()
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

saklib::internal::Command_History const& saklib::internal::Undoable_Element_Data_Handle::cget_command_history() const
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
