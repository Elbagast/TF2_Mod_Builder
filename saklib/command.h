#ifndef COMMAND_H
#define COMMAND_H

namespace Saklib
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
    /*
    // Forward arguments to construct the templated Command_Class without having to use operator new manually
    template <typename Command_Class, typename... Args>
    up_Command make_up_Command(Args&&... args)
    {
        return up_Command(new Command_Class(std::forward<Args>(args)...)));
    }
    */
} // namespace Saklib

#endif // COMMAND_H
