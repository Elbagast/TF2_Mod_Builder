#ifndef SAK_ENTITY_COMMANDS_HPP
#define SAK_ENTITY_COMMANDS_HPP

// This Header's Forward Header
//============================================================
#ifndef SAK_ENTITY_COMMANDS_FWD_HPP
#include "entity_commands_fwd.hpp"
#endif

// SAK Forwarding Headers
//============================================================
#ifndef SAK_SIGNAL_FWD_HPP
#include "../signal_fwd.hpp"
#endif

#ifndef SAK_OBSERVER_MANAGER_FWD_HPP
#include "observer_manager_fwd.hpp"
#endif

#ifndef SAK_ENTITY_COLLECTION_FWD_HPP
#include "entity_collection_fwd.hpp"
#endif

// SAK Headers
//============================================================
#ifndef SAK_ABSTRACT_COMMAND_HPP
#include "abstract_command.hpp"
#endif

#ifndef SAK_ENTITY_HANDLE_HPP
#include "entity_handle.hpp"
#endif

#ifndef SAK_STRING_HPP
#include "../string.hpp"
#endif

// Standard Headers
//============================================================

namespace sak
{
  //---------------------------------------------------------------------------
  // Abstract_Signalling_Command
  //---------------------------------------------------------------------------
  // Abstract base class for commands that will hold some observers to notify
  // with signals. It's an implementation aid.

  class Abstract_Signalling_Command :
      public Abstract_Command
  {
  private:
    // Data Members
    //============================================================
    Observer_Manager& m_observers;

  public:
    // Special 6
    //============================================================
    Abstract_Signalling_Command(Signal_Source a_source, Observer_Manager& a_observers);
    ~Abstract_Signalling_Command() override = 0;

    // NO COPYING
    Abstract_Signalling_Command(Abstract_Signalling_Command const& a_other) = delete;
    Abstract_Signalling_Command& operator=(Abstract_Signalling_Command const& a_other) = delete;

    // NO MOVING
    Abstract_Signalling_Command(Abstract_Signalling_Command && a_other) = delete;
    Abstract_Signalling_Command& operator=(Abstract_Signalling_Command && a_other) = delete;

  protected:
    // Interface
    //============================================================
    using Abstract_Command::source;

    // Send a signal to the held observers.
    void send(Signal const& a_signal);

    // Virtuals
    //============================================================
    void do_execute() override = 0;
    void do_unexecute() override = 0;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Abstract_Entity_Signalling_Command
  //---------------------------------------------------------------------------
  // Abstract base class for commands that will hold some observers to notify
  // with signals. It's an implementation aid.

  class Abstract_Entity_Signalling_Command :
      public Abstract_Signalling_Command
  {
  private:
    // Data Members
    //============================================================
    Entity_Handle m_handle;
  public:
    // Special 6
    //============================================================
    Abstract_Entity_Signalling_Command(Signal_Source a_source,
                                       Observer_Manager& a_observers,
                                       Entity_Handle const& a_handle);
    ~Abstract_Entity_Signalling_Command() override = 0;

    // NO COPYING
    Abstract_Entity_Signalling_Command(Abstract_Entity_Signalling_Command const& a_other) = delete;
    Abstract_Entity_Signalling_Command& operator=(Abstract_Entity_Signalling_Command const& a_other) = delete;

    // NO MOVING
    Abstract_Entity_Signalling_Command(Abstract_Entity_Signalling_Command && a_other) = delete;
    Abstract_Entity_Signalling_Command& operator=(Abstract_Entity_Signalling_Command && a_other) = delete;

  protected:
    // Interface
    //============================================================
    using Abstract_Signalling_Command::source;
    using Abstract_Signalling_Command::send;

    // Access the held handle.
    Entity_Handle& handle();
    Entity_Handle const& chandle() const;

    Entity_ID id() const;

    // Virtuals
    //============================================================
    void do_execute() override = 0;
    void do_unexecute() override = 0;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Command_Entity_Add
  //---------------------------------------------------------------------------

  class Command_Entity_Add :
      public Abstract_Entity_Signalling_Command
  {
  private:
    // Data Members
    //============================================================
    Entity_Collection& m_collection;

  public:
    // Special 6
    //============================================================
    Command_Entity_Add(Signal_Source a_source,
                       Observer_Manager& a_observers,
                       Entity_Handle const& a_handle,
                       Entity_Collection& a_collection);
    ~Command_Entity_Add() override final;

    // NO COPYING
    Command_Entity_Add(Command_Entity_Add const& a_other) = delete;
    Command_Entity_Add& operator=(Command_Entity_Add const& a_other) = delete;

    // NO MOVING
    Command_Entity_Add(Command_Entity_Add && a_other) = delete;
    Command_Entity_Add& operator=(Command_Entity_Add && a_other) = delete;

  protected:
    // Virtuals
    //============================================================
    void do_execute() override final;
    void do_unexecute() override final;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Command_Entity_Remove
  //---------------------------------------------------------------------------

  class Command_Entity_Remove :
      public Abstract_Entity_Signalling_Command
  {
  private:
    // Data Members
    //============================================================
    Entity_Collection& m_collection;

  public:
    // Special 6
    //============================================================
    Command_Entity_Remove(Signal_Source a_source,
                          Observer_Manager& a_observers,
                          Entity_Handle const& a_handle,
                          Entity_Collection& a_collection);
    ~Command_Entity_Remove() override final;

    // NO COPYING
    Command_Entity_Remove(Command_Entity_Remove const& a_other) = delete;
    Command_Entity_Remove& operator=(Command_Entity_Remove const& a_other) = delete;

    // NO MOVING
    Command_Entity_Remove(Command_Entity_Remove && a_other) = delete;
    Command_Entity_Remove& operator=(Command_Entity_Remove && a_other) = delete;

  protected:
    // Virtuals
    //============================================================
    void do_execute() override final;
    void do_unexecute() override final;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Command_Entity_Name_Change
  //---------------------------------------------------------------------------

  class Command_Entity_Name_Change :
      public Abstract_Entity_Signalling_Command
  {
  private:
    // Data Members
    //============================================================
    String m_old_name;
    String m_new_name;
  public:
    // Special 6
    //============================================================
    Command_Entity_Name_Change(Signal_Source a_source,
                               Observer_Manager& a_observers,
                               Entity_Handle const& a_handle,
                               String const& a_name);
    ~Command_Entity_Name_Change() override final;

    // NO COPYING
    Command_Entity_Name_Change(Command_Entity_Name_Change const& a_other) = delete;
    Command_Entity_Name_Change& operator=(Command_Entity_Name_Change const& a_other) = delete;

    // NO MOVING
    Command_Entity_Name_Change(Command_Entity_Name_Change && a_other) = delete;
    Command_Entity_Name_Change& operator=(Command_Entity_Name_Change && a_other) = delete;

  protected:
    // Virtuals
    //============================================================
    void do_execute() override final;
    void do_unexecute() override final;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

}

#endif // SAK_ENTITY_COMMANDS_HPP
