#include "command_history.hpp"
#include <cassert>
#include <iterator>
#include "abstract_command.hpp"

// Special 6
//============================================================

sak::Command_History::Command_History():
  m_container{},
  m_position{m_container.begin()} // position marks the next command to be executed. position-1 is the next to be unexecuted.
{}

sak::Command_History::~Command_History() = default;

// Default move
sak::Command_History::Command_History(Command_History && a_other) = default;
sak::Command_History& sak::Command_History::operator=(Command_History && a_other) = default;

// Interface
//============================================================

// Take ownership of the given command pointer, adding it to the top of the queue and calling
// the Command::execute() on it.
void sak::Command_History::add_execute(Abstract_Command* a_command)
{
  add_execute(std::move(std::unique_ptr<Abstract_Command>(a_command)));
}
void sak::Command_History::add_execute(std::unique_ptr<Abstract_Command>& a_command)
{
  // capture the pointer without releasing it.
  std::unique_ptr<Abstract_Command> l_command{nullptr};
  std::swap(l_command, a_command);
  add_execute(std::move(l_command));
}
void sak::Command_History::add_execute(std::unique_ptr<Abstract_Command>&& a_command)
{
  // Chop off everything between m_position and the end.
  // If m_position is already at the end, this does nothing.
  // [begin, .. m_position, .. end) -> [begin, m_position)
  m_position = m_container.erase(m_position, m_container.end());
  assert(m_position == m_container.end());
  // Add the command to the end.
  m_container.push_back(std::forward<std::unique_ptr<Abstract_Command>>(a_command));
  m_container.back().get()->execute();
  // must update m_position
  m_position = m_container.end();
  assert(can_undo());
  assert(!can_redo());
}

// Will calling undo do anything?
bool sak::Command_History::can_undo() const
{
  return !m_container.empty() && m_position != m_container.cbegin();
}

// Will calling redo do anything?
bool sak::Command_History::can_redo() const
{
  return !m_container.empty() && m_position != m_container.cend();
}

// How many commands are stored?
std::size_t sak::Command_History::command_count() const
{
  return m_container.size();
}

// Is the container empty?
bool sak::Command_History::has_commands() const
{
  return m_container.empty();
}

// How many times can undo() be called?
std::size_t sak::Command_History::undo_count() const
{
  return std::distance(m_container.cbegin(), Const_Iterator(m_position));
}
// How many times can redo() be called?
std::size_t sak::Command_History::redo_count() const
{
  return std::distance(Const_Iterator(m_position), m_container.cend());
}

// Call unexecute() in the current command and step back one in the history.
bool sak::Command_History::undo()
{
  if (can_undo())
  {
    // Since we know we can undo, step back one and undo it.
    std::advance(m_position, -1);
    m_position->get()->unexecute();
    return true;
  }
  else
  {
    return false;
  }
}
// Step forward one in the history and call execute() on that command.
bool sak::Command_History::redo()
{
  if (can_redo())
  {
    // Since we know we can redo, redo and step forward.
    // Since logic relys on m_postition, and that logic may be called
    // during execute, we copy it and update it, then call vai the copy.
    auto l_position = m_position;
    std::advance(m_position, 1);
    l_position->get()->execute();
    return true;
}
else
{
    return false;
  }
}

// Clear all stored commands.
void sak::Command_History::clear()
{
  // Clear the underlying container.
  m_container.clear();
  m_position = m_container.begin();
}
