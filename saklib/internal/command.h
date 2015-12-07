#ifndef SAKLIB_INTERNAL_COMMAND_H
#define SAKLIB_INTERNAL_COMMAND_H

#ifndef SAKLIB_INTERNAL_COMMAND__FWD_H
#include "command__fwd.h"
#endif

#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif

namespace saklib
{
    namespace internal
    {
        //---------------------------------------------------------------------------
        // Command
        //---------------------------------------------------------------------------
        // Abstract base class for encapsulating commands with a state-lock to allow
        // execution/unexecution to be called only once, since calling it only once
        // is all that is appropriate.

        class Command
        {
        public:
            // Special 6
            //============================================================
            Command();
            virtual ~Command() = 0;

            // Interface
            //============================================================
            // Check if can_execute() is true then call v_execute() and return true, else
            // do nothing and return false.
            bool execute();
            // Check if can_unexecute() is true then call v_unexecute() and return true, else
            // do nothing and return false.
            bool unexecute();

            // Has the Command not been exectuted or unexecuted?
            bool is_initial_state() const;
            // Has the Command not been exectuted?
            bool is_executed() const;
            // Has the Command not been unexecuted?
            bool is_unexecuted() const;

            // Can the Command not been executed?
            bool can_execute() const;
            // Can the Command not been unexecuted?
            bool can_unexecute() const;

        protected:
            // Virtuals
            //============================================================
            virtual void v_execute() = 0;
            virtual void v_unexecute() = 0;

        private:
            // Data Members
            //============================================================
            enum class State;

            State m_state;
        };

        /*
        What would a totally templated Command look like?
        - Actor = Type to act on
        - Type to recieve
        - Type (Actor::*Value_Getter)() const
        - bool (Actor::*Value_Setter)(Type const&)
        - Success Assertion
        */
        template
                <
                typename Actor,
                typename Value,
                typename Getter_Return,
                Getter_Return (Actor::*Value_Getter)() const,
                typename Setter_Return,
                typename Setter_Arg,
                Setter_Return (Actor::*Value_Setter)(Setter_Arg)
                >

        class Command_Simple_Stored_Get_Set :
                public Command
        {
        public:
            using actor_type = Actor;
            using value_type = Value;
            using getter_return_type = Getter_Return;
            using setter_return_type = Setter_Return;
            using setter_arg_type = Setter_Arg;

            // Special 6
            //============================================================
            Command_Simple_Stored_Get_Set(actor_type const& a_actor, value_type const& a_value):
                Command(),
                m_actor(a_actor),
                m_old_value((m_actor.*Value_Getter)()),
                m_new_value(a_value)
            {}
            ~Command_Simple_Stored_Get_Set() override = default;

        protected:
            // Virtuals
            //============================================================
            void v_execute() override
            {
                (m_actor.*Value_Setter)(m_new_value);
            }
            void v_unexecute() override
            {
                (m_actor.*Value_Setter)(m_old_value);
            }
        private:
            actor_type m_actor;
            value_type m_old_value;
            value_type m_new_value;
        };

        // type deducing maker function...
        // Doesn't work right now.


        template
                <
                typename Actor,
                typename Value,
                typename Getter_Return,
                typename Getter_Function,
                typename Setter_Return,
                typename Setter_Arg,
                typename Setter_Function
                >
        std::unique_ptr<Command> make_command_simple_stored_get_set(Actor const& a_actor, Getter_Function a_getter, Setter_Function a_setter, Value const& a_value)
        {
            return std::unique_ptr<Command>(new Command_Simple_Stored_Get_Set<Actor, Value, Getter_Return, &a_getter, Setter_Return, Setter_Arg, &a_setter>(a_actor, a_value));
        }


    } // namespace internal
} // namespace saklib

#endif // SAKLIB_INTERNAL_COMMAND_H
