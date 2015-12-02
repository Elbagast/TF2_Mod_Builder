#include "command.h"

// Private Data
//============================================================
enum class saklib::internal::Command::State
{
    Initial,
    Executed,
    Unexecuted
};

// Special 6
//============================================================
saklib::internal::Command::Command():
    m_state{State::Initial}
{
}

saklib::internal::Command::~Command() = default;

// Interface
//============================================================
bool saklib::internal::Command::execute()
{
    // only act if the command wasn't already exectued
    if (can_execute())
    {
        m_state = State::Executed;
        v_execute();
        return true;
    }
    else
    {
        return false;
    }
}

bool saklib::internal::Command::unexecute()
{
    // only act if there if the command was already executed
    if (can_unexecute())
    {
        m_state = State::Unexecuted;
        v_unexecute();
        return true;
    }
    else
    {
        return false;
    }
}

bool saklib::internal::Command::is_initial_state() const
{
    return m_state == State::Initial;
}

bool saklib::internal::Command::is_executed() const
{
    return m_state == State::Executed;
}

bool saklib::internal::Command::is_unexecuted() const
{
    return m_state == State::Unexecuted;
}

bool saklib::internal::Command::can_execute() const
{
    return m_state != State::Executed;
}

bool saklib::internal::Command::can_unexecute() const
{
    return m_state == State::Executed;
}
