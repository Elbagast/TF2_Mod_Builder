#ifndef SAK_ENTITY_MANAGER_HPP
#define SAK_ENTITY_MANAGER_HPP

// This Header's Forward Header
//============================================================
#ifndef SAK_ENTITY_MANAGER_FWD_HPP
#include "entity_manager_fwd.hpp"
#endif

// SAK Forwarding Headers
//============================================================
#ifndef SAK_ABSTRACT_OBSERVER_FWD_HPP
#include "abstract_observer_fwd.hpp"
#endif

#ifndef SAK_SIGNAL_SOURCE_FWD_HPP
#include "signal_source_fwd.hpp"
#endif

#ifndef SAK_ENTITY_ID_FWD_HPP
#include "entity_id_fwd.hpp"
#endif

#ifndef SAK_VARIANT_FWD_HPP
#include "variant_fwd.hpp"
#endif

// SAK Headers
//============================================================
#ifndef SAK_ENTITY_DEFINITION_HPP
#include "entity_definition.hpp"
#endif

// Standard Headers
//============================================================
#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif

#ifndef INCLUDE_STD_VECTOR
#define INCLUDE_STD_VECTOR
#include <vector>
#endif

#ifndef INCLUDE_STD_STRING
#define INCLUDE_STD_STRING
#include <string>
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Entity_Manager
  //---------------------------------------------------------------------------
  // Hold a collection of entities and manage everything required to manipulate
  // it in a manner that allows undoing changes and informing observers that
  // rely on the data. Must be initialised with a factory that will make the
  // required Entity types. Uses the pimpl idiom to insulate users from changes
  // to what is a complicated object.

  class Entity_Manager
  {
  private:
    // Data Members
    //============================================================
    class Implementation;
    std::unique_ptr<Implementation> m_imp;

    Implementation& imp()               { return *m_imp; }
    Implementation const& cimp() const  { return *m_imp; }

  public:
    // Special 6
    //============================================================
    // Intialise by passing in a collection of Entity makers to install. We
    // won't be able to add to this list or remove from it later.
    explicit Entity_Manager(std::vector<Entity_Definition> const& a_defs);
    ~Entity_Manager();

    // No copying.
    Entity_Manager(Entity_Manager const&) = delete;
    Entity_Manager& operator=(Entity_Manager const&) = delete;

    // Can move since data is a pointer.
    Entity_Manager(Entity_Manager &&);
    Entity_Manager& operator=(Entity_Manager &&);

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
    bool has_name(std::string const& a_name) const;

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

#endif // SAK_ENTITY_MANAGER_HPP
