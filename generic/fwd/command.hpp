#ifndef GENERIC_FWD_COMMAND_HPP
#define GENERIC_FWD_COMMAND_HPP

namespace generic
{
    namespace abstract
    {
        //---------------------------------------------------------------------------
        // abstract::Command
        //---------------------------------------------------------------------------
        // Abstract base class for encapsulating commands with a state-lock to allow
        // execution/unexecution to be called only once, since calling it only once
        // is all that is appropriate.

        class Command;

    } // namespace abstract
} // namespace generic

#endif // GENERIC_FWD_COMMAND_HPP
