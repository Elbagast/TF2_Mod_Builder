#include "command.hpp"
// Private Data
//============================================================
enum class generic::abstract::Command::State
{
    Initial,
    Executed,
    Unexecuted
};

// Special 6
//============================================================
generic::abstract::Command::Command():
    m_state{State::Initial}
{
}

generic::abstract::Command::~Command() = default;

// Interface
//============================================================
bool generic::abstract::Command::execute()
{
    // only act if the command wasn't already exectued
    if (can_execute())
    {
        m_state = State::Executed;
        do_execute();
        return true;
    }
    else
    {
        return false;
    }
}

bool generic::abstract::Command::unexecute()
{
    // only act if there if the command was already executed
    if (can_unexecute())
    {
        m_state = State::Unexecuted;
        do_unexecute();
        return true;
    }
    else
    {
        return false;
    }
}

bool generic::abstract::Command::is_initial_state() const
{
    return m_state == State::Initial;
}

bool generic::abstract::Command::is_executed() const
{
    return m_state == State::Executed;
}

bool generic::abstract::Command::is_unexecuted() const
{
    return m_state == State::Unexecuted;
}

bool generic::abstract::Command::can_execute() const
{
    return m_state != State::Executed;
}

bool generic::abstract::Command::can_unexecute() const
{
    return m_state == State::Executed;
}
