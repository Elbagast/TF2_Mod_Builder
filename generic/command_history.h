#ifndef COMMAND_HISTORY_H
#define COMMAND_HISTORY_H

#include <memory>
#include <list>
#include <vector>
#include <type_traits>
#include "command.h"

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

    class Command_History
    {
    public:
        using command_type = abstract::Command;

        // Special 6
        //============================================================
        Command_History();
        ~Command_History();

        // NO COPYING
        Command_History(Command_History const& a_other) = delete;
        Command_History& operator=(Command_History const& a_other) = delete;

        // Default move
        //Command_History(Command_History && a_other);
        //Command_History& operator=(Command_History && a_other);

        // Interface
        //============================================================

        // Take ownership of the given command pointer, adding it to the top of the queue and calling
        // the command_type::execute() on it.
        void add_execute(command_type* a_command);
        void add_execute(std::unique_ptr<command_type>& a_command);
        void add_execute(std::unique_ptr<command_type>&& a_command);

        // Forward arguments to construct the templated Command_Class without having to use operator new manually
        template <typename Command_Class>
        void add_execute(std::unique_ptr<Command_Class>&& a_command)
        {
            static_cast(std::is_base_of<command_type, Command_Class>::value, "Cannot add_execute this pointer, the class is not derived from Command_History::command_type.");
            add_execute(std::unique_ptr<command_type>(a_command.release()));
        }

        // Forward arguments to construct the templated Command_Class without having to use operator new manually
        template <typename Command_Class, typename... Args>
        void emplace_execute(Args&&... a_args)
        {
            static_cast(std::is_base_of<command_type, Command_Class>::value, "Cannot emplace_execute this data, the class is not derived from Command_History::command_type.");
            add_execute(std::unique_ptr<command_type>(std::make_unique<Command_Class>(std::forward<Args>(a_args)...)).release());
        }

        // Will calling undo do anything?
        bool can_undo() const;
        // Will calling redo do anything?
        bool can_redo() const;

        // How many commands are stored?
        std::size_t command_count() const;
        // Is the container empty?
        bool has_commands() const;

        // How many times can undo() be called?
        std::size_t undo_count() const;
        // How many times can redo() be called?
        std::size_t redo_count() const;

        // Call unexecute() in the current command and step back one in the history.
        bool undo();
        // Step forward one in the history and call execute() on that command.
        bool redo();

        // Clear all stored commands.
        void clear();

    private:
        using container_type = std::list < std::unique_ptr<command_type> >;
        using iterator = container_type::iterator;
        using const_iterator = container_type::const_iterator;
        using difference_type = container_type::difference_type;

        // Data Members
        //============================================================
        container_type m_container;
        iterator m_position;
    };
}


#endif // COMMAND_HISTORY_H
