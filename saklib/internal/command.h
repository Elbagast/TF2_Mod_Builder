#ifndef SAKLIB_INTERNAL_COMMAND_H
#define SAKLIB_INTERNAL_COMMAND_H

#ifndef SAKLIB_INTERNAL_COMMAND__FWD_H
#include "command__fwd.h"
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
    } // namespace internal
} // namespace saklib

#endif // SAKLIB_INTERNAL_COMMAND_H
