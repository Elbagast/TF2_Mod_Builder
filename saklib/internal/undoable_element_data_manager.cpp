#include "undoable_element_data_manager.h"

#include "undoable_element_data_handle.h"
//#include "element_data.h"
//#include "all_attribute_data_.h"

#include "element_data_handle.h"
//#include "all_attribute_data_handle.h"

//#include "exceptions/bad_element_data_type.h"

//#include <limits>

#include "command.h"

//---------------------------------------------------------------------------
// Undoable_Element_Data_Manager
//---------------------------------------------------------------------------

// Interface
//============================================================
bool saklib::internal::Undoable_Element_Data_Manager::has_element(handle_type const& a_handle) const
{
    return m_manager.has_element(a_handle);
}

saklib::internal::Undoable_Element_Data_Handle saklib::internal::Undoable_Element_Data_Manager::make_element_handle(handle_type const& a_handle)
{
    if (has_element(a_handle))
    {
        return Undoable_Element_Data_Handle(m_manager.make_element_handle(a_handle), m_command_history);
    }
    else
    {
        return Undoable_Element_Data_Handle();
    }
}

saklib::internal::Undoable_Element_Data_Handle saklib::internal::Undoable_Element_Data_Manager::make_element(Element_Data_Definition_Handle&& a_definition_handle)
{
    if (a_definition_handle.is_valid())
    {
        auto l_element_handle = m_manager.make_element(std::forward<Element_Data_Definition_Handle>(a_definition_handle));
        assert(l_element_handle.is_valid());
        return Undoable_Element_Data_Handle(std::move(l_element_handle), m_command_history);
    }
    else
    {
        return Undoable_Element_Data_Handle();
    }
}

std::size_t saklib::internal::Undoable_Element_Data_Manager::cget_reference_count(handle_type const& a_handle) const
{
    return m_manager.cget_reference_count(a_handle);
}

std::vector<saklib::internal::Undoable_Element_Data_Manager::handle_type> saklib::internal::Undoable_Element_Data_Manager::cget_all_handles() const
{
    return m_manager.cget_all_handles();
}

std::vector<saklib::internal::Undoable_Element_Data_Handle> saklib::internal::Undoable_Element_Data_Manager::make_all_element_handles()
{
    auto all_handles = m_manager.make_all_element_handles();
    std::vector<Undoable_Element_Data_Handle> l_result{};
    l_result.reserve(all_handles.size());
    for (auto const& l_handle : all_handles)
    {
        l_result.emplace_back(std::move(l_handle), m_command_history);
    }
    return l_result;
}


// Will calling undo do anything?
bool saklib::internal::Undoable_Element_Data_Manager::can_undo() const
{
    return m_command_history.can_undo();
}
// Will calling redo do anything?
bool saklib::internal::Undoable_Element_Data_Manager::can_redo() const
{
    return m_command_history.can_redo();
}

// How many commands are stored?
std::size_t saklib::internal::Undoable_Element_Data_Manager::cget_command_count() const
{
    return m_command_history.cget_command_count();
}
// Is the container empty?
bool saklib::internal::Undoable_Element_Data_Manager::has_commands() const
{
    return m_command_history.has_commands();
}

// How many times can undo() be called?
std::size_t saklib::internal::Undoable_Element_Data_Manager::cget_undo_count() const
{
    return m_command_history.cget_undo_count();
}
// How many times can redo() be called?
std::size_t saklib::internal::Undoable_Element_Data_Manager::cget_redo_count() const
{
    return m_command_history.cget_redo_count();
}
/*
std::size_t saklib::internal::Undoable_Element_Data_Manager::cget_undo_count_maximum() const
{
    return m_command_history.cget_undo_count_maximum();
}
*/
// Call unexecute() in the current command and step back one in the history.
bool saklib::internal::Undoable_Element_Data_Manager::undo()
{
    return m_command_history.undo();
}
// Step forward one in the history and call execute() on that command.
bool saklib::internal::Undoable_Element_Data_Manager::redo()
{
    return m_command_history.redo();
}

// Clear all stored commands.
void saklib::internal::Undoable_Element_Data_Manager::clear()
{
    m_command_history.clear();
}

