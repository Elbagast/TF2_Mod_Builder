#include "entity_manager.hpp"

#include "entity_id.hpp"

#include "signal_entity.hpp"

#include "internal/entity.hpp"
#include "internal/abstract_entity_name.hpp"
#include "internal/abstract_entity_type.hpp"
#include "internal/abstract_entity_tooltip.hpp"
#include "internal/abstract_entity_icon.hpp"

#include "internal/abstract_entity_maker.hpp"
#include "internal/entity_handle.hpp"
#include "internal/command_history.hpp"
#include "internal/observer_manager.hpp"
#include "internal/entity_factory.hpp"
#include "internal/entity_collection.hpp"
#include "internal/entity_commands.hpp"

#include <algorithm>
#include <cassert>

namespace sak
{
  //---------------------------------------------------------------------------
  // Entity_Manager::Implementation
  //---------------------------------------------------------------------------
  //

  class Entity_Manager::Implementation
  {
  private:
    // Data Members
    //============================================================
    Command_History m_command_history;
    Observer_Manager m_observers;
    Entity_Factory m_factory;
    Entity_Collection m_entity_collection;

  public:
    // Special 6
    //============================================================
    // Intialise by passing in a collection of Entity makers to install. We
    // won't be able to add to this list or remove from it later.
    explicit Implementation(std::vector<Entity_Definition> const& a_defs);
    ~Implementation();

    Implementation(Implementation const&) = delete;
    Implementation& operator=(Implementation const&) = delete;

    Implementation(Implementation &&) = delete;
    Implementation& operator=(Implementation &&) = delete;

    // Interface
    //============================================================

    // Observers
    //------------------------------------------------------------
    // Is this observer in the collection?
    bool has_observer(Abstract_Observer* a_observer) const;

    // How many observers are currently held?
    std::size_t observer_count() const;

    // Get all the currently held observers.
    std::vector<Abstract_Observer*> observers() const;

    // Add an object that will rely on the Project's signals. If
    // nulltpr or already present, nothing happens.
    void add_observer(Abstract_Observer* a_observer);

    // Remove an object that will rely on the Project's signals. If
    // nulltpr or not present, nothing happens.
    void remove_observer(Abstract_Observer* a_observer);

    // Clear all the observers so that nothing relies on changes to this.
    void clear_observers();


    // Command History
    //------------------------------------------------------------
    // Can we currently call undo?
    bool can_undo() const;

    // Can we currently call redo?
    bool can_redo() const;

    // How many times can undo() be called?
    std::size_t undo_count() const;

    // How many times can redo() be called?
    std::size_t redo_count() const;

    // Undo the last command issued. Return true if succeeded.
    bool undo();

    // Redo the last undone command. Return true if succeeded.
    bool redo();

    // Clear the undo/redo history.
    void clear_history();


    // Entity Collection
    //------------------------------------------------------------

    // Are there any entities in this Project?
    bool is_empty() const;

    // How many entities are in this Project?
    std::size_t count() const;

    // Does this id appear in the data?
    bool has(Entity_ID a_id) const;

    // Get the index of the data associated with the supplied id. This is the current position
    // in the project's collection of data for this type of data. If the id is null or invalid,
    // the returned index is equal to count().
    std::size_t index(Entity_ID a_id) const;

    // Get the id at this index. If the index is invalid a null id is returned.
    Entity_ID get_at(std::size_t a_index) const;

    // Get all the ids in data order
    std::vector<Entity_ID> get_all() const;


    // Entity Types
    //------------------------------------------------------------

    // Does the project contain any entities of this type?
    bool has_type(std::string const& a_type) const;

    // How many entities of a given type are in this Project?
    std::size_t count_of(std::string const& a_type) const;

    // Get all the Entities of a given type. If the type is invalid then the result is empty.
    std::vector<Entity_ID> get_all_of(std::string const& a_type) const;

    // Is this a valid Entity Type?
    bool can_make(std::string const& a_type) const;

    // Get all of the valid Entity types.
    std::vector<std::string> get_all_types() const;


    // Entity Collection Editing
    //------------------------------------------------------------

    // Undoable make a new entity using the supplied typestring. If the typestring is invalid the returned
    // id is null, otherwise it is the id of the new entity.
    Entity_ID try_add(Signal_Source a_source, std::string const& a_type);

    // Undoable remove entity. Return true if the operation resulted in an undoable command.
    bool try_remove(Signal_Source a_source, Entity_ID a_id);

    // Request that the editor for this entity be opened or switched to.
    bool try_request_editor(Signal_Source a_source, Entity_ID a_id);

    // Request that the focus change to this entity.
    bool try_request_outliner(Signal_Source a_source, Entity_ID a_id);


    // Entity Names
    //------------------------------------------------------------

    // Does this name appear in the data?
    bool has_name(std::string const&) const;

    // Get the name of the data associated with the supplied id. If the id is null or invalid,
    // the returned name is empty, which names cannot be.
    std::string name(Entity_ID a_id) const;

    // Get the id with this name. If the name is invalid a null id is returned.
    Entity_ID get_named(std::string const& a_name) const;

    // Get all the objects names in data order
    std::vector<std::string> get_all_names() const;

    // Attempt an undoable change to the name of the data associated with the supplied id. If
    // the id is valid and the supplied value results in a change to the data, signals are emitted
    // telling everything to update this name, and true is returned. If the id is null or
    // invalid, nothing happens and false is returned. Success does not indicate that the name
    // is set to what has been supplied, but that the name has changed.
    bool try_set_name(Signal_Source a_source, Entity_ID a_id, std::string const& a_name);



    // Entity System Data
    //------------------------------------------------------------

    // Get the type of a given entity. If the id is null or invalid the string is empty.
    std::string type(Entity_ID a_id) const;

    // Get the tooltip for a given entity. If the id is null or invalid the string is empty.
    std::string tooltip(Entity_ID a_id) const;

    // Get the iconpath for a given entity. If the id is null or invalid the string is empty.
    std::string iconpath(Entity_ID a_id) const;
  };
}

// Special 6
//============================================================
// Intialise by passing in a collection of Entity makers to install. We
// won't be able to add to this list or remove from it later.
sak::Entity_Manager::Implementation::Implementation(std::vector<Entity_Definition> const& a_defs) :
  m_command_history{},
  m_observers{},
  m_factory{},
  m_entity_collection{}
{
  // add each maker the the factory
  for (auto const& l_def : a_defs)
  {
    m_factory.add_maker(Abstract_Entity_Maker::from_definition(l_def));
  }
}

sak::Entity_Manager::Implementation::~Implementation() = default;


// Interface
//============================================================

// Observers
//------------------------------------------------------------
// Is this observer in the collection?
bool sak::Entity_Manager::Implementation::has_observer(Abstract_Observer* a_observer) const
{
  return m_observers.has(a_observer);
}

// How many observers are currently held?
std::size_t sak::Entity_Manager::Implementation::observer_count() const
{
  return m_observers.count();
}

// Get all the currently held observers.
std::vector<sak::Abstract_Observer*> sak::Entity_Manager::Implementation::observers() const
{
  return m_observers.observers();
}

// Add an object that will rely on the Project's signals. If
// nulltpr or already present, nothing happens.
void sak::Entity_Manager::Implementation::add_observer(Abstract_Observer* a_observer)
{
  m_observers.add(a_observer);
}

// Remove an object that will rely on the Project's signals. If
// nulltpr or not present, nothing happens.
void sak::Entity_Manager::Implementation::remove_observer(Abstract_Observer* a_observer)
{
  m_observers.remove(a_observer);
}

// Clear all the observers so that nothing relies on changes to this.
void sak::Entity_Manager::Implementation::clear_observers()
{
  m_observers.clear();
}

// Command History
//------------------------------------------------------------
// Can we currently call undo?
bool sak::Entity_Manager::Implementation::can_undo() const
{
  return m_command_history.can_undo();
}

// Can we currently call redo?
bool sak::Entity_Manager::Implementation::can_redo() const
{
  return m_command_history.can_redo();
}

// How many times can undo() be called?
std::size_t sak::Entity_Manager::Implementation::undo_count() const
{
  return m_command_history.undo_count();
}

// How many times can redo() be called?
std::size_t sak::Entity_Manager::Implementation::redo_count() const
{
  return m_command_history.redo_count();
}

// Undo the last command issued. Return true if succeeded.
bool sak::Entity_Manager::Implementation::undo()
{
  return m_command_history.undo();
}

// Redo the last undone command. Return true if succeeded.
bool sak::Entity_Manager::Implementation::redo()
{
  return m_command_history.redo();
}

// Clear the undo/redo history.
void sak::Entity_Manager::Implementation::clear_history()
{
  m_command_history.clear();
}

// Entity Collection
//------------------------------------------------------------

// Are there any entities in this Project?
bool sak::Entity_Manager::Implementation::is_empty() const
{
  return m_entity_collection.is_empty();
}

// How many entities are in this Project?
std::size_t sak::Entity_Manager::Implementation::count() const
{
  return m_entity_collection.count();
}

// Does this id appear in the data?
bool sak::Entity_Manager::Implementation::has(Entity_ID a_id) const
{
  return m_entity_collection.has(a_id);
}

// Get the index of the data associated with the supplied id. This is the current position
// in the project's collection of data for this type of data. If the id is null or invalid,
// the returned index is equal to count().
std::size_t sak::Entity_Manager::Implementation::index(Entity_ID a_id) const
{
  return m_entity_collection.index(a_id);
}

// Get the id at this index. If the index is invalid a null id is returned.
sak::Entity_ID sak::Entity_Manager::Implementation::get_at(std::size_t a_index) const
{
  return m_entity_collection.get_at(a_index);
}

// Get all the ids in data order
std::vector<sak::Entity_ID> sak::Entity_Manager::Implementation::get_all() const
{
  return m_entity_collection.get_all();
}


// Entity Types
//------------------------------------------------------------

// Does the project contain any entities of this type?
bool sak::Entity_Manager::Implementation::has_type(std::string const& a_type) const
{
  return m_entity_collection.has_type(a_type);
}

// How many entities of a given type are in this Project?
std::size_t sak::Entity_Manager::Implementation::count_of(std::string const& a_type) const
{
  return m_entity_collection.count_of(a_type);
}

// Get all the Entities of a given type. If the type is invalid then the result is empty.
std::vector<sak::Entity_ID> sak::Entity_Manager::Implementation::get_all_of(std::string const& a_type) const
{
  return m_entity_collection.get_all_of(a_type);
}

// Is this a valid Entity Type?
bool sak::Entity_Manager::Implementation::can_make(std::string const& a_type) const
{
  return m_factory.has_type(a_type);
}

// Get all of the valid Entity types.
std::vector<std::string> sak::Entity_Manager::Implementation::get_all_types() const
{
  return m_factory.all_types();
}


// Entity Collection Editing
//------------------------------------------------------------

// Undoable make a new entity using the supplied typestring. If the typestring is invalid the returned
// id is null, otherwise it is the id of the new entity.
sak::Entity_ID sak::Entity_Manager::Implementation::try_add(Signal_Source a_source, std::string const& a_type)
{
  // If the factory doesn't have this type, we fail.
  if (m_factory.has_type(a_type) == false)
  {
    return make_null_entity_id();
  }

  // We have the type so make one of it.
  auto l_handle = m_factory.make_entity(a_type);

  // Factory fail test.
  assert(not_null(l_handle));

  // Handle is not somehow already present.
  assert(!m_entity_collection.has_handle(l_handle));

  // Copy the name
  std::string l_name{l_handle->cname_component()->get_name()};

  // Fix it if necessary
  if (m_entity_collection.has_name(l_name))
  {
    m_entity_collection.fix_name(l_name);
  }

  // Better not have this name
  assert(!m_entity_collection.has_name(l_name));

  // Set the new name
  l_handle->name_component()->set_name(l_name);

  // Make and execute the command.
  m_command_history.emplace_execute<Command_Entity_Add>(a_source, m_observers, l_handle, m_entity_collection);

  // Return the id of the handle we just added.
  return l_handle.id();
}

// Undoable remove entity. Return true if the operation resulted in an undoable command.
bool sak::Entity_Manager::Implementation::try_remove(Signal_Source a_source, Entity_ID a_id)
{
  // Get the handle for this id.
  auto l_handle = m_entity_collection.get_handle(a_id);

  // If this id doesn't exist, we fail
  if (is_null(l_handle))
  {
    return false;
  }

  // Handle is not null.
  assert(not_null(l_handle));

  // Handle is already present.
  assert(m_entity_collection.has_handle(l_handle));

  // Make and execute the command.
  m_command_history.emplace_execute<Command_Entity_Remove>(a_source, m_observers, l_handle, m_entity_collection);

  // Return success.
  return true;
}

// Request that the editor for this entity be opened or switched to.
bool sak::Entity_Manager::Implementation::try_request_editor(Signal_Source a_source, Entity_ID a_id)
{
  // If this id doesn't exist, we fail
  if (this->has(a_id) == false)
  {
    return false;
  }

  // Make a signal to request outliner focus.
  auto l_outliner_signal = make_signal_entity_outliner_request(a_source, a_id);

  // Send the signal out.
  m_observers.send(l_outliner_signal);

  // Make a signal to request the editor
  auto l_editor_signal = make_signal_entity_editor_request(a_source, a_id);

  // Send the signal out.
  m_observers.send(l_editor_signal);

  return true;
}

// Request that the focus change to this entity.
bool sak::Entity_Manager::Implementation::try_request_outliner(Signal_Source a_source, Entity_ID a_id)
{
  // If this id doesn't exist, we fail
  if (this->has(a_id) == false)
  {
    return false;
  }
  // Make a signal to request outliner focus.
  auto l_outliner_signal = make_signal_entity_outliner_request(a_source, a_id);

  // Send the signal out.
  m_observers.send(l_outliner_signal);

  return true;
}


// Entity Names
//------------------------------------------------------------

// Does this name appear in the data?
bool sak::Entity_Manager::Implementation::has_name(std::string const& a_name) const
{
  return m_entity_collection.has_name(a_name);
}

// Get all the objects names in data order
std::vector<std::string> sak::Entity_Manager::Implementation::get_all_names() const
{
  return m_entity_collection.get_all_names();
}

// Get the name of the data associated with the supplied id. If the id is null or invalid,
// the returned name is empty, which names cannot be.
std::string sak::Entity_Manager::Implementation::name(Entity_ID a_id) const
{
  auto l_handle = m_entity_collection.get_handle(a_id);

  if (not_null(l_handle))
  {
    return l_handle->cname_component()->get_name();
  }
  else
  {
    return std::string{};
  }
}

// Attempt an undoable change to the name of the data associated with the supplied id. If
// the id is valid and the supplied value results in a change to the data, signals are emitted
// telling everything to update this name, and true is returned. If the id is null or
// invalid, nothing happens and false is returned. Success does not indicate that the name
// is set to what has been supplied, but that the name has changed.
bool sak::Entity_Manager::Implementation::try_set_name(Signal_Source a_source, Entity_ID a_id, std::string const& a_name)
{
  // Get the handle for this id.
  auto l_handle = m_entity_collection.get_handle(a_id);

  // If this id doesn't exist, fail
  if (is_null(l_handle))
  {
    return false;
  }

  // If the name is the same as it already is, fail
  if (a_name == l_handle->cname_component()->get_name())
  {
    return false;
  }

  // Copy the name
  std::string l_name{a_name};

  // Fix it if necessary
  if (m_entity_collection.has_name(l_name))
  {
    m_entity_collection.fix_name(l_name);
  }

  // Better not have this now altered name.
  // Failing here means fix_name didn't do its job.
  assert(!m_entity_collection.has_name(l_name));

  // Better not match this altered name.
  assert(l_name != l_handle->cname_component()->get_name());

  // Make and execute the command using the fixed name.
  m_command_history.emplace_execute<Command_Entity_Name_Change>(a_source, m_observers, l_handle, l_name);

  // Return success.
  return true;
}


// Entity System Data
//------------------------------------------------------------

// Get the type of a given entity. If the id is null or invalid the string is empty.
std::string sak::Entity_Manager::Implementation::type(Entity_ID a_id) const
{
  auto l_handle = m_entity_collection.get_handle(a_id);

  if (not_null(l_handle))
  {
    return l_handle->ctype_component()->type();
  }
  else
  {
    return std::string{};
  }
}

// Get the tooltip for a given entity. If the id is null or invalid the string is empty.
std::string sak::Entity_Manager::Implementation::tooltip(Entity_ID a_id) const
{
  auto l_handle = m_entity_collection.get_handle(a_id);

  if (not_null(l_handle))
  {
    return l_handle->ctooltip_component()->tooltip();
  }
  else
  {
    return std::string{};
  }
}

// Get the iconpath for a given entity. If the id is null or invalid the string is empty.
std::string sak::Entity_Manager::Implementation::iconpath(Entity_ID a_id) const
{
  auto l_handle = m_entity_collection.get_handle(a_id);

  if (not_null(l_handle))
  {
    return l_handle->cicon_component()->iconpath();
  }
  else
  {
    return std::string{};
  }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------
// sak::Entity_Manager
//---------------------------------------------------------------------------
// A Project contains a number of entities.

// Special 6
//============================================================
// Intialise by passing in a collection of Entity makers to install. We
// won't be able to add to this list or remove from it later.
sak::Entity_Manager::Entity_Manager(std::vector<Entity_Definition> const& a_defs) :
  m_imp{std::make_unique<Implementation>(a_defs)}
{
}

sak::Entity_Manager::~Entity_Manager() = default;

// Can move since data is a pointer.
sak::Entity_Manager::Entity_Manager(Entity_Manager &&) = default;
sak::Entity_Manager& sak::Entity_Manager::operator=(Entity_Manager &&) = default;

// Interface
//============================================================

// Observers
//------------------------------------------------------------// Is this observer in the collection?
bool sak::Entity_Manager::has_observer(Abstract_Observer* a_observer) const
{
  return cimp().has_observer(a_observer);
}

// How many observers are currently held?
std::size_t sak::Entity_Manager::observer_count() const
{
  return cimp().observer_count();
}

// Get all the currently held observers.
std::vector<sak::Abstract_Observer*> sak::Entity_Manager::observers() const
{
  return cimp().observers();
}

// Add an object that will rely on the Project's signals. If
// nulltpr or already present, nothing happens.
void sak::Entity_Manager::add_observer(Abstract_Observer* a_observer)
{
  imp().add_observer(a_observer);
}

// Remove an object that will rely on the Project's signals. If
// nulltpr or not present, nothing happens.
void sak::Entity_Manager::remove_observer(Abstract_Observer* a_observer)
{
  imp().remove_observer(a_observer);
}

// Clear all the observers so that nothing relies on changes to this.
void sak::Entity_Manager::clear_observers()
{
  imp().clear_observers();
}


// Command History
//------------------------------------------------------------
// Can we currently call undo?
bool sak::Entity_Manager::can_undo() const
{
  return cimp().can_undo();
}

// Can we currently call redo?
bool sak::Entity_Manager::can_redo() const
{
  return cimp().can_redo();
}

// How many times can undo() be called?
std::size_t sak::Entity_Manager::undo_count() const
{
  return cimp().undo_count();
}

// How many times can redo() be called?
std::size_t sak::Entity_Manager::redo_count() const
{
  return cimp().redo_count();
}

// Undo the last command issued. Return true if succeeded.
bool sak::Entity_Manager::undo()
{
  return imp().undo();
}

// Redo the last undone command. Return true if succeeded.
bool sak::Entity_Manager::redo()
{
  return imp().redo();
}

// Clear the undo/redo history.
void sak::Entity_Manager::clear_history()
{
  imp().clear_history();
}

// Entity Collection
//------------------------------------------------------------

// Are there any entities in this Project?
bool sak::Entity_Manager::is_empty() const
{
  return cimp().is_empty();
}

// How many entities are in this Project?
std::size_t sak::Entity_Manager::count() const
{
  return cimp().count();
}

// Does this id appear in the data?
bool sak::Entity_Manager::has(Entity_ID a_id) const
{
  return cimp().has(a_id);
}

// Get the index of the data associated with the supplied id. This is the current position
// in the project's collection of data for this type of data. If the id is null or invalid,
// the returned index is equal to count().
std::size_t sak::Entity_Manager::index(Entity_ID a_id) const
{
  return cimp().index(a_id);
}

// Get the id at this index. If the index is invalid a null id is returned.
sak::Entity_ID sak::Entity_Manager::get_at(std::size_t a_index) const
{
  return cimp().get_at(a_index);
}

// Get all the ids in data order
std::vector<sak::Entity_ID> sak::Entity_Manager::get_all() const
{
  return cimp().get_all();
}


// Entity Types
//------------------------------------------------------------

// Does the project contain any entities of this type?
bool sak::Entity_Manager::has_type(std::string const& a_type) const
{
  return cimp().has_type(a_type);
}

// How many entities of a given type are in this Project?
std::size_t sak::Entity_Manager::count_of(std::string const& a_type) const
{
  return cimp().count_of(a_type);
}

// Get all the Entities of a given type. If the type is invalid then the result is empty.
std::vector<sak::Entity_ID> sak::Entity_Manager::get_all_of(std::string const& a_type) const
{
  return cimp().get_all_of(a_type);
}

// Is this a valid Entity Type?
bool sak::Entity_Manager::can_make(std::string const& a_type) const
{
  return cimp().can_make(a_type);
}

// Get all of the valid Entity types.
std::vector<std::string> sak::Entity_Manager::get_all_types() const
{
  return cimp().get_all_types();
}

// Entity Collection Editing
//------------------------------------------------------------

// Undoable make a new entity using the supplied typestring. If the typestring is invalid the returned
// id is null, otherwise it is the id of the new entity.
sak::Entity_ID sak::Entity_Manager::try_add(Signal_Source a_source, std::string const& a_type)
{
  return imp().try_add(a_source, a_type);
}

// Undoable remove entity. Return true if the operation resulted in an undoable command.
bool sak::Entity_Manager::try_remove(Signal_Source a_source, Entity_ID a_id)
{
  return imp().try_remove(a_source, a_id);
}

// Request that the editor for this entity be opened or switched to.
bool sak::Entity_Manager::try_request_editor(Signal_Source a_source, Entity_ID a_id)
{
  return imp().try_request_editor(a_source, a_id);
}

// Request that the focus change to this entity.
bool sak::Entity_Manager::try_request_outliner(Signal_Source a_source, Entity_ID a_id)
{
  return imp().try_request_outliner(a_source, a_id);
}

// Entity Names
//------------------------------------------------------------

// Does this name appear in the data?
bool sak::Entity_Manager::has_name(std::string const& a_name) const
{
  return cimp().has_name(a_name);
}

// Get all the objects names in data order
std::vector<std::string> sak::Entity_Manager::get_all_names() const
{
  return cimp().get_all_names();
}


// Get the name of the data associated with the supplied id. If the id is null or invalid,
// the returned name is empty, which names cannot be.
std::string sak::Entity_Manager::name(Entity_ID a_id) const
{
  return cimp().name(a_id);
}

// Attempt an undoable change to the name of the data associated with the supplied id. If
// the id is valid and the supplied value results in a change to the data, signals are emitted
// telling everything to update this name, and true is returned. If the id is null or
// invalid, nothing happens and false is returned. Success does not indicate that the name
// is set to what has been supplied, but that the name has changed.
bool sak::Entity_Manager::try_set_name(Signal_Source a_source, Entity_ID a_id, std::string const& a_name)
{
  return imp().try_set_name(a_source, a_id, a_name);
}


// Entity System Data
//------------------------------------------------------------

// Get the type of a given entity. If the id is null or invalid the string is empty.
std::string sak::Entity_Manager::type(Entity_ID a_id) const
{
  return cimp().type(a_id);
}

// Get the tooltip for a given entity. If the id is null or invalid the string is empty.
std::string sak::Entity_Manager::tooltip(Entity_ID a_id) const
{
  return cimp().tooltip(a_id);
}

// Get the iconpath for a given entity. If the id is null or invalid the string is empty.
std::string sak::Entity_Manager::iconpath(Entity_ID a_id) const
{
  return cimp().iconpath(a_id);
}
