#ifndef COMMAND_H
#define COMMAND_H

namespace saklib
{
    /*
    Command
    ====================================================================================================
    Abstract base class for encapsulating commands with a state-lock to allow execution/unexecution to
    be called only once, since calling it only once is all that is appropriate.

    Should it call execute() on construction?
    */
    class Command
    {
    public:
        enum class State
        {
            Initial,
            Executed,
            Unexecuted
        };

        Command() :
            m_state(State::Initial)
        {}
        virtual ~Command() = default;

        void execute()
        { 
            // only act if the command wasn't already exectued
            if (can_execute())
            {
                m_state = State::Executed;
                v_execute();
            }
        }
        void unexecute()
        { 
            // only act if there if the command was already executed
            if (can_unexecute())
            {
                m_state = State::Unexecuted;
                v_unexecute();
            }
        }
        State state() const { return m_state; }

        bool can_execute() const    { return m_state != State::Executed; }
        bool can_unexecute() const  { return m_state == State::Executed; }

    protected:
        virtual void v_execute() = 0;
        virtual void v_unexecute() = 0;

    private:
        State m_state;
    };

} // namespace saklib

#endif // COMMAND_H
