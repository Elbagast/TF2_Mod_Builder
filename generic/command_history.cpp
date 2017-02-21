#include "command_history.h"

// Special 6
//============================================================

generic::Command_History::Command_History():
    m_container{},
    m_next_undo(m_container.end()),
    m_next_redo(m_container.end())
{}

generic::Command_History::~Command_History() = default;

// Default move
//Command_History(Command_History && a_other) = default;
//Command_History& operator=(Command_History && a_other) = default;

// Interface
//============================================================

// Take ownership of the given command pointer, adding it to the top of the queue and calling
// the Command::execute() on it.
void generic::Command_History::add_execute(command_type* a_command)
{
    add_execute(std::move(std::unique_ptr<command_type>(a_command)));
}
void generic::Command_History::add_execute(std::unique_ptr<command_type>& a_command)
{
    // capture the pointer without releasing it.
    std::unique_ptr<command_type> l_command{nullptr};
    std::swap(l_command, a_command);
    add_execute(std::move(l_command));
}
void generic::Command_History::add_execute(std::unique_ptr<command_type>&& a_command)
{
    // Chop off everything between m_next_redo and the end.
    // If m_next_redo is already at the end, this does nothing.
    m_next_redo = m_container.erase(m_next_redo, m_container.end());

    // Insert the command at m_next_redo, and set m_next_undo to point to that position.
    // If we don't reassign it then m_position would point to m_container.end(), which is not dereferenceable.
    m_next_undo = m_container.insert(m_next_redo, std::forward<std::unique_ptr<command_type>>(a_command));
    // Set m_next_redo to point to the new end.
    m_next_redo = m_container.end();

    // Call execute() on the inserted command.
    m_next_undo->get()->execute();
}

// Will calling undo do anything?
bool generic::Command_History::can_undo() const
{
    if (!has_commands() && m_next_undo != m_next_redo) // kind of obscure condition...
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Will calling redo do anything?
bool generic::Command_History::can_redo() const
{
    if (!has_commands() && m_next_redo != m_container.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

// How many commands are stored?
std::size_t generic::Command_History::cget_command_count() const
{
    return m_container.size();
}

// Is the container empty?
bool generic::Command_History::has_commands() const
{
    return m_container.empty();
}

// How many times can undo() be called?
std::size_t generic::Command_History::cget_undo_count() const
{
    // If there are no commands, or only one command but it is already undone,
    if (m_container.empty() || m_next_undo == m_next_redo)
        return 0;
    // else the class should maintain m_next_redo == (m_next_undo +1),
    else
        // So we need to use m_next_redo to get an accurate count
        return std::distance(m_container.begin(), const_iterator(m_next_redo));
}
// How many times can redo() be called?
std::size_t generic::Command_History::cget_redo_count() const
{
    // This one is simpler than undo count
    return std::distance(const_iterator(m_next_redo), m_container.end());
}

// Call unexecute() in the current command and step back one in the history.
bool generic::Command_History::undo()
{
    if (can_undo())
    {
        // call unexecute
        m_next_undo->get()->unexecute();

        m_next_redo = m_next_undo;
        // step undo backward until it reaches the begining
        if (m_next_undo != m_container.begin())
        {
            --m_next_undo;
        }
        return true;
    }
    else
    {
        return false;
    }
}
// Step forward one in the history and call execute() on that command.
bool generic::Command_History::redo()
{
    if (can_redo())
    {
        // call execute
        m_next_redo->get()->execute();

        m_next_undo = m_next_redo;
        // step redo forward until it reaches the end
        if (m_next_redo != m_container.end())
        {
            ++m_next_redo;
        }
        return true;
    }
    else
    {
        return false;
    }
}

// Clear all stored commands.
void generic::Command_History::clear()
{
    // Clear the underlying container.
    m_container.clear();

    // Reset the iterators.
    m_next_undo = m_container.end();
    m_next_redo = m_container.end();
}
