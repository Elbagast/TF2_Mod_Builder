#ifndef COMMAND_HISTORY_H
#define COMMAND_HISTORY_H

#include "types.h"
#include "command.h"
#include <list>

namespace Saklib
{
    // Forward Declarations
    //============================================================
    //class Command;

    /*
    Command_History
    ====================================================================================================
    Queue-like container that manages a history of commands and supports undo/redo functionality on the
    Command objects.

    Position in the history is tracked with an iterator that points to position the next last command
    that was executed (consequently also the next command that undo will be called on).
    */
    class Command_History
    {
    public:
        using container_type = std::list < Uptr<Command> >;
        using size_type = std::size_t;
        
        // Special 6
        //============================================================
        Command_History();
        ~Command_History() = default;

        // NO COPYING
        Command_History(Command_History const& other) = delete;
        Command_History& operator=(Command_History const& other) = delete;

        // Implicit default move

        // Interface
        //============================================================

        // Take ownership of the given command pointer, adding it to the top of the queue and calling 
        // the Command::execute() on it.
        void add_execute(Command* command);
		void add_execute(Uptr<Command>& command);
		void add_execute(Uptr<Command>&& command);

        // Forward arguments to construct the templated Command_Class without having to use operator new manually
        template <typename Command_Class, typename... Args>
        void emplace_execute(Args&&... args)
        {
            add_execute(Uptr<Command>(new Command_Class(std::forward<Args>(args)...)));
        }

        // Will calling undo do anything?
        bool can_undo() const;
        // Will calling redo do anything?
        bool can_redo() const;

        // How many commands are stored?
        size_type size() const      { return m_container.size(); }
        // Is the container empty?
        bool empty() const          { return m_container.empty(); }

        // Access the underlying container
        //container_type& container()             { return m_container; }
        //container_type const& container() const { return m_container; }
        // This is kinda pointless without pretty information functions in Command...

        // How many times can undo() be called()?
        size_type undo_count() const;
        // How many times can redo() be called()?
        size_type redo_count() const;
        
        // Should these return bool for success? or *this?

        // Call unexecute() in the current command and step back one in the history.
        void undo();
        // Step forward one in the history and call execute() on that command.
        void redo();

        // Clear all stored commands.
        void clear();

    private:
        using iterator = container_type::iterator;
        using const_iterator = container_type::const_iterator;
        using difference_type = container_type::difference_type;

        // Data Members
        //============================================================
        container_type m_container;

        iterator m_next_undo;
        iterator m_next_redo;
    };
} // namespace Saklib

#endif // COMMAND_HISTORY_H
