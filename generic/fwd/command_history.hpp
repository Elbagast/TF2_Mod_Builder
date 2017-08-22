#ifndef GENERIC_FWD_COMMAND_HISTORY_HPP
#define GENERIC_FWD_COMMAND_HISTORY_HPP

namespace generic
{
    //---------------------------------------------------------------------------
    // Command_History
    //---------------------------------------------------------------------------
    // Queue-like container that manages a history of commands and supports undo/redo functionality on the
    // Command objects.

    // Position in the history is tracked with an iterator that points to position the next last command
    // that was executed (consequently also the next command that undo will be called on).

    // If you want commands that give more information you should probably make a different version of this
    // class that uses a different base Command class.

    class Command_History;
}


#endif // GENERIC_FWD_COMMAND_HISTORY_HPP
