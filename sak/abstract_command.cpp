#include "abstract_command.hpp"

// Private Data
//============================================================
enum class sak::Abstract_Command::State
{
  Initial,
  Executed,
  Unexecuted
};

// Special 6
//============================================================
sak::Abstract_Command::Abstract_Command(Signal_Source a_source):
  m_state{State::Initial},
  m_source{a_source}
{
}

sak::Abstract_Command::~Abstract_Command() = default;

// Interface
//============================================================
bool sak::Abstract_Command::execute()
{
  // only act if the command wasn't already exectued
  if (can_execute())
  {
    m_state = State::Executed;
    do_execute();
    m_source = Signal_Source::Undo;
    return true;
  }
  else
  {
    return false;
  }
}

bool sak::Abstract_Command::unexecute()
{
  // only act if there if the command was already executed
  if (can_unexecute())
  {
    m_state = State::Unexecuted;
    do_unexecute();
    m_source = Signal_Source::Redo;
    return true;
  }
  else
  {
    return false;
  }
}

bool sak::Abstract_Command::is_initial_state() const
{
  return m_state == State::Initial;
}

bool sak::Abstract_Command::is_executed() const
{
  return m_state == State::Executed;
}

bool sak::Abstract_Command::is_unexecuted() const
{
  return m_state == State::Unexecuted;
}

bool sak::Abstract_Command::can_execute() const
{
  return m_state != State::Executed;
}

bool sak::Abstract_Command::can_unexecute() const
{
  return m_state == State::Executed;
}

sak::Signal_Source sak::Abstract_Command::source() const
{
  return m_source;
}
