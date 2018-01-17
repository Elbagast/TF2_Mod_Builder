#ifndef SAK_ABSTRACT_COMMAND_HPP
#define SAK_ABSTRACT_COMMAND_HPP

#ifndef SAK_ABSTRACT_COMMAND_FWD_HPP
#include "abstract_command_fwd.hpp"
#endif

#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Abstract_Command
  //---------------------------------------------------------------------------
  // Abstract base class for encapsulating commands with a state-lock to allow
  // execution/unexecution to be called only once, since calling it only once
  // is all that is appropriate.

  class Abstract_Command
  {
  public:
    // Special 6
    //============================================================
    Abstract_Command();
    virtual ~Abstract_Command() = 0;

    // Interface
    //============================================================
    // Check if can_execute() is true then call do_execute() and return true, else
    // do nothing and return false.
    bool execute();
    // Check if can_unexecute() is true then call do_unexecute() and return true, else
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
    virtual void do_execute() = 0;
    virtual void do_unexecute() = 0;

  private:
    // Data Members
    //============================================================
    enum class State;

    State m_state;
  };
} // namespace sak

#endif // SAK_ABSTRACT_COMMAND_HPP
