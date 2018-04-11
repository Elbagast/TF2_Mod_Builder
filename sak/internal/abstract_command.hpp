﻿#ifndef SAK_ABSTRACT_COMMAND_HPP
#define SAK_ABSTRACT_COMMAND_HPP

// This Header's Forward Header
//============================================================
#ifndef SAK_ABSTRACT_COMMAND_FWD_HPP
#include "abstract_command_fwd.hpp"
#endif

// SAK Headers
//============================================================
#ifndef SAK_SIGNAL_SOURCE_FWD_HPP
#include "../signal_source_fwd.hpp"
#endif

// Standard Headers
//============================================================
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
  private:
    // Data Members
    //============================================================
    enum class State;

    State m_state;
    Signal_Source m_source;

  public:
    // Special 6
    //============================================================
    explicit Abstract_Command(Signal_Source a_source);
    virtual ~Abstract_Command() = 0;

    // NO COPYING
    Abstract_Command(Abstract_Command const& a_other) = delete;
    Abstract_Command& operator=(Abstract_Command const& a_other) = delete;

    // NO MOVING
    Abstract_Command(Abstract_Command && a_other) = delete;
    Abstract_Command& operator=(Abstract_Command && a_other) = delete;

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
    // Has the Command been exectuted?
    bool is_executed() const;
    // Has the Command been unexecuted?
    bool is_unexecuted() const;

    // Can the Command be executed?
    bool can_execute() const;
    // Can the Command be unexecuted?
    bool can_unexecute() const;

  protected:
    // Virtuals
    //============================================================
    virtual void do_execute() = 0;
    virtual void do_unexecute() = 0;

    Signal_Source source() const;

  };
} // namespace sak

#endif // SAK_ABSTRACT_COMMAND_HPP