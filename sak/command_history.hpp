#ifndef SAK_COMMAND_HISTORY_HPP
#define SAK_COMMAND_HISTORY_HPP

#ifndef SAK_COMMAND_HISTORY_FWD_HPP
#include "command_history_fwd.hpp"
#endif

#ifndef SAK_ABSTRACT_COMMAND_FWD_HPP
#include "abstract_command_fwd.hpp"
#endif

#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif

#ifndef INCLUDE_STD_LIST
#define INCLUDE_STD_LIST
#include <list>
#endif

#ifndef INCLUDE_STD_VECTOR
#define INCLUDE_STD_VECTOR
#include <vector>
#endif

#ifndef INCLUDE_STD_TYPE_TRAITS
#define INCLUDE_STD_TYPE_TRAITS
#include <type_traits>
#endif

namespace sak
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
    Command_History(Command_History const& a_other) = delete;
    Command_History& operator=(Command_History const& a_other) = delete;

    // Default move
    Command_History(Command_History && a_other);
    Command_History& operator=(Command_History && a_other);

    // Interface
    //============================================================

    // Take ownership of the given command pointer, adding it to the top of the queue and calling
    // the command_type::execute() on it.
    void add_execute(Abstract_Command* a_command);
    void add_execute(std::unique_ptr<Abstract_Command>& a_command);
    void add_execute(std::unique_ptr<Abstract_Command>&& a_command);

    // Forward arguments to construct the templated Command_Class without having to use operator new manually
    template <typename T_Command_Class>
    void add_execute(std::unique_ptr<T_Command_Class>&& a_command)
    {
      static_assert(std::is_base_of<Abstract_Command, T_Command_Class>::value, "Cannot add_execute this pointer, the class is not derived from Abstract_Command.");
      add_execute(std::unique_ptr<Abstract_Command>(a_command.release()));
    }

    // Forward arguments to construct the templated Command_Class without having to use operator new manually
    template <typename T_Command_Class, typename... Args>
    void emplace_execute(Args&&... a_args)
    {
      static_assert(std::is_base_of<Abstract_Command, T_Command_Class>::value, "Cannot emplace_execute this data, the class is not derived from Abstract_Command.");
      add_execute(std::unique_ptr<Abstract_Command>(std::make_unique<T_Command_Class>(std::forward<Args>(a_args)...)).release());
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
    using container_type = std::list < std::unique_ptr<Abstract_Command> >;
    using iterator = container_type::iterator;
    using const_iterator = container_type::const_iterator;
    using difference_type = container_type::difference_type;

    // Data Members
    //============================================================
    container_type m_container;
    iterator m_position;
  };
}

#endif // SAK_COMMAND_HISTORY_HPP
