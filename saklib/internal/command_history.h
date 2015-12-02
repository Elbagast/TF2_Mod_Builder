#ifndef SAKLIB_INTERNAL_COMMAND_HISTORY_H
#define SAKLIB_INTERNAL_COMMAND_HISTORY_H

#ifndef SAKLIB_INTERNAL_COMMAND_HISTORY__FWD_H
#include "command_history__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_COMMAND_H
#include "command.h"
#endif

#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif

#ifndef INCLUDE_STD_LIST
#define INCLUDE_STD_LIST
#include <list>
#endif


namespace saklib
{
    namespace internal
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
            // Special 6
            //============================================================
            Command_History();
            ~Command_History();

            // NO COPYING
            Command_History(Command_History const& other) = delete;
            Command_History& operator=(Command_History const& other) = delete;

            // Implicit default move

            // Interface
            //============================================================

            // Take ownership of the given command pointer, adding it to the top of the queue and calling
            // the Command::execute() on it.
            void add_execute(Command* command);
            void add_execute(std::unique_ptr<Command>& command);
            void add_execute(std::unique_ptr<Command>&& command);

            // Forward arguments to construct the templated Command_Class without having to use operator new manually
            template <typename Command_Class, typename... Args>
            void emplace_execute(Args&&... args)
            {
                add_execute(std::unique_ptr<Command>(new Command_Class(std::forward<Args>(args)...)));
            }

            // Will calling undo do anything?
            bool can_undo() const;
            // Will calling redo do anything?
            bool can_redo() const;

            // How many commands are stored?
            std::size_t cget_command_count() const;
            // Is the container empty?
            bool has_commands() const;

            // How many times can undo() be called?
            std::size_t cget_undo_count() const;
            // How many times can redo() be called?
            std::size_t cget_redo_count() const;

            std::size_t cget_undo_count_maximum() const;

            // Call unexecute() in the current command and step back one in the history.
            bool undo();
            // Step forward one in the history and call execute() on that command.
            bool redo();

            // Clear all stored commands.
            void clear();

            // Signals that are currently all dummies
            void signal_command_added();
            void signal_undo();
            void signal_redo();
            void signal_clear();

        private:
            using container_type = std::list < std::unique_ptr<Command> >;
            using iterator = container_type::iterator;
            using const_iterator = container_type::const_iterator;
            using difference_type = container_type::difference_type;

            // Data Members
            //============================================================
            container_type m_container;

            iterator m_next_undo;
            iterator m_next_redo;
        };
    } // namespace internal
} // namespace saklib

#endif // SAKLIB_INTERNAL_COMMAND_HISTORY_H
