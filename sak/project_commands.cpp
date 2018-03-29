#include "project_commands.hpp"

#include "entity.hpp"
#include "entity_handle.hpp"
#include "entity_manager.hpp"

#include "observer_manager.hpp"

#include "entity_added_signal.hpp"
#include "entity_removed_signal.hpp"
#include "entity_name_changed_signal.hpp"

#include <cassert>

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Abstract_Signalling_Command
//---------------------------------------------------------------------------

// Special 6
//============================================================
sak::Abstract_Signalling_Command::Abstract_Signalling_Command(Signal_Source a_source, Observer_Manager& a_observers) :
  Abstract_Command(a_source),
  m_observers{a_observers}
{
}

sak::Abstract_Signalling_Command::~Abstract_Signalling_Command() = default;

// Interface
//============================================================
// Send a signal to the held observers.
void sak::Abstract_Signalling_Command::send(Abstract_Signal const& a_signal)
{
  m_observers.send(a_signal);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Abstract_Entity_Signalling_Command
//---------------------------------------------------------------------------
// Abstract base class for commands that will hold some observers to notify
// with signals. It's an implementation aid.

// Special 6
//============================================================
sak::Abstract_Entity_Signalling_Command::Abstract_Entity_Signalling_Command(Signal_Source a_source,
                                                                            Observer_Manager& a_observers,
                                                                            Entity_Handle const& a_handle) :
  Abstract_Signalling_Command(a_source, a_observers),
  m_handle{a_handle}
{
  assert(not_null(m_handle));
}

sak::Abstract_Entity_Signalling_Command::~Abstract_Entity_Signalling_Command() = default;

// Access the held handle.
sak::Entity_Handle& sak::Abstract_Entity_Signalling_Command::handle()
{
  return m_handle;
}

sak::Entity_Handle const& sak::Abstract_Entity_Signalling_Command::chandle() const
{
  return m_handle;
}

sak::Entity_ID sak::Abstract_Entity_Signalling_Command::id() const
{
  return m_handle.id();
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Command_Entity_Add
//---------------------------------------------------------------------------

// Interface
//============================================================
// Determine whether a command can be issued with these arguments. Returns
// true if the given handle is not found in the given entity vector.
bool sak::Command_Entity_Add::valid_arguments(Entity_Handle const& a_handle, Entity_Manager const& a_entity_manager)
{
  return not_null(a_handle) && a_entity_manager.has_handle(a_handle);
}

// Special 6
//============================================================
sak::Command_Entity_Add::Command_Entity_Add(Signal_Source a_source,
                                            Observer_Manager& a_observers,
                                            Entity_Handle const& a_handle,
                                            Entity_Manager& a_entity_manager) :
  Abstract_Entity_Signalling_Command(a_source, a_observers, a_handle),
  m_entity_manager{a_entity_manager}
{
  assert(valid_arguments(this->chandle(), m_entity_manager));
}

sak::Command_Entity_Add::~Command_Entity_Add() = default;

// Virtuals
//============================================================
void sak::Command_Entity_Add::do_execute()
{
  // Better not have this handle.
  assert(!m_entity_manager.has_handle(this->chandle()));
  assert(m_entity_manager.can_add(this->chandle()));

  // Do the change.
  m_entity_manager.add(this->chandle());

  // Better have this handle.
  assert(m_entity_manager.has_handle(this->chandle()));
  assert(m_entity_manager.can_remove(this->chandle()));

  // Make and send the signal.
  Entity_Added_Signal l_signal{this->source(), this->chandle().id()};
  this->send(l_signal);
}

void sak::Command_Entity_Add::do_unexecute()
{
  // Better have this handle.
  assert(m_entity_manager.has_handle(this->chandle()));
  assert(m_entity_manager.can_remove(this->chandle()));

  // Do the change.
  m_entity_manager.remove(this->chandle());

  // Better not have this handle.
  assert(!m_entity_manager.has_handle(this->chandle()));
  assert(m_entity_manager.can_add(this->chandle()));

  // Make and send the signal.
  Entity_Removed_Signal l_signal{this->source(), this->chandle().id()};
  this->send(l_signal);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Command_Entity_Remove
//---------------------------------------------------------------------------

// Interface
//============================================================
// Determine whether a command can be issued with these arguments. Returns
// true if the given handle is found in the given entity vector.
bool sak::Command_Entity_Remove::valid_arguments(Entity_Handle const& a_handle, Entity_Manager const& a_entity_manager)
{
  return not_null(a_handle) && !a_entity_manager.has_handle(a_handle);
}

// Special 6
//============================================================
sak::Command_Entity_Remove::Command_Entity_Remove(Signal_Source a_source,
                                                  Observer_Manager& a_observers,
                                                  Entity_Handle const& a_handle,
                                                  Entity_Manager& a_entity_manager) :
  Abstract_Entity_Signalling_Command(a_source, a_observers, a_handle),
  m_entity_manager{a_entity_manager}
{
  assert(valid_arguments(this->chandle(), m_entity_manager));
}

sak::Command_Entity_Remove::~Command_Entity_Remove() = default;

// Virtuals
//============================================================
void sak::Command_Entity_Remove::do_execute()
{
  // Better have this handle.
  assert(m_entity_manager.has_handle(this->chandle()));
  assert(m_entity_manager.can_remove(this->chandle()));

  // Do the change.
  m_entity_manager.remove(this->chandle());

  // Better not have this handle.
  assert(!m_entity_manager.has_handle(this->chandle()));
  assert(m_entity_manager.can_add(this->chandle()));

  // Make and send the signal.
  Entity_Removed_Signal l_signal{this->source(), this->chandle().id()};
  this->send(l_signal);

  // NO DEALING WITH CONNECTIONS RIGHT NOW
}

void sak::Command_Entity_Remove::do_unexecute()
{
  // Better not have this handle.
  assert(!m_entity_manager.has_handle(this->chandle()));
  assert(m_entity_manager.can_add(this->chandle()));

  // Do the change.
  m_entity_manager.add(this->chandle());

  // Better have this handle.
  assert(m_entity_manager.has_handle(this->chandle()));
  assert(m_entity_manager.can_remove(this->chandle()));

  // Make and send the signal.
  Entity_Added_Signal l_signal{this->source(), this->chandle().id()};
  this->send(l_signal);

  // NO DEALING WITH CONNECTIONS RIGHT NOW
}
//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Command_Entity_Name_Change
//---------------------------------------------------------------------------

// Interface
//============================================================
// Determine whether a command can be issued with these arguments. Returns
// true if the name is not the same as that in the handle
bool sak::Command_Entity_Name_Change::valid_arguments(Entity_Handle const& a_handle, QString const& a_name)
{
  return not_null(a_handle) && a_handle->cname_component()->get_name() != a_name;
}

// Special 6
//============================================================
sak::Command_Entity_Name_Change::Command_Entity_Name_Change(Signal_Source a_source,
                                                            Observer_Manager& a_observers,
                                                            Entity_Handle const& a_handle,
                                                            QString const& a_name) :
  Abstract_Entity_Signalling_Command(a_source, a_observers, a_handle),
  m_old_name{a_handle->cname_component()->get_name()},
  m_new_name{a_name}
{
}

sak::Command_Entity_Name_Change::~Command_Entity_Name_Change() = default;

// Virtuals
//============================================================
void sak::Command_Entity_Name_Change::do_execute()
{
  // The name had better be the old name.
  assert(this->chandle()->cname_component()->get_name() == m_old_name);

  // Set the name to the new name.
  this->handle()->name_component()->set_name(m_new_name);

  // The name had better be the new name now.
  assert(this->chandle()->cname_component()->get_name() == m_new_name);

  // Make and send the signal.
  Entity_Name_Changed_Signal l_signal{this->source(), this->id(), m_old_name, m_new_name};
  this->send(l_signal);
}

void sak::Command_Entity_Name_Change::do_unexecute()
{
  // The name had better be the new name.
  assert(this->chandle()->cname_component()->get_name() == m_new_name);

  // Set the name to the old name.
  this->handle()->name_component()->set_name(m_old_name);

  // The name had better be the old name now.
  assert(this->chandle()->cname_component()->get_name() == m_old_name);

  // Make and send the signal.
  Entity_Name_Changed_Signal l_signal{this->source(), this->id(), m_new_name, m_old_name};
  this->send(l_signal);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
