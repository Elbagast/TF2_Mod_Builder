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

#ifndef SAK_DATA_TYPE_FWD_HPP
#include "data_type_fwd.hpp"
#endif

#ifndef SAK_ENTITY_ID_FWD_HPP
#include "entity_id_fwd.hpp"
#endif

#ifndef SAK_SIGNAL_SOURCE_FWD_HPP
#include "signal_source_fwd.hpp"
#endif

#ifndef SAK_STRING_FWD_HPP
#include "string_fwd.hpp"
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

#ifndef INCLUDE_STD_STRING
#define INCLUDE_STD_STRING
#include <string>
#endif

#ifndef INCLUDE_STD_VECTOR
#define INCLUDE_STD_VECTOR
#include <vector>
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

    // Is this observer present?
    bool has_observer(Abstract_Observer* a_observer) const;

    // How many observers are currently held?
    std::size_t observer_count() const;

    // Get all the currently held observers.
    std::vector<Abstract_Observer*> all_observer() const;

    // Add an object that will rely on the Project's signals. If
    // nullptr or already present, nothing happens.
    void add_observer(Abstract_Observer* a_observer);

    // Remove an object that will rely on the Project's signals. If
    // nulltpr or not present, nothing happens.
    void remove_observer(Abstract_Observer* a_observer);

    // Remove all the observers so that nothing relies on changes to this.
    void remove_all_observer();


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


    // Entity Factory
    //------------------------------------------------------------

    // Can we make an entity of this type?
    bool can_make_type(String const& a_type) const;

    // Get all of the entity types that can be made.
    std::vector<String> all_can_make() const;

    // If we wanted factory editing....


    // Entitys
    //------------------------------------------------------------

    // Are there currently any entities?
    bool is_empty() const;

    // How many entities are there currently?
    std::size_t count() const;

    // Are there currently any entities of this type?
    bool has_type(String const& a_type) const;

    // How many entities of this type are there currently?
    std::size_t count_type(String const& a_type) const;

    // Does this entity currently exist?
    bool has(Entity_ID a_id) const;

    // Get all the ids of currently active entities.
    std::vector<Entity_ID> all() const;

    // Get all the ids of a given type. If the type is invalid or not present
    // the result is empty.
    std::vector<Entity_ID> all_type(String const& a_type) const;

    // Undoable make and add a new entity of the given type. If the type is
    // valid the a new entity is added, the history is changed, observers are
    // notifed of the change, and the returned it is that of the new entity.
    // Undoing will remove this entity and the id becomes invalid. If the type
    // is invalid then nothing happens and the returned it is a null id.
    Entity_ID add(Signal_Source a_source, String const& a_type);

    // Undoable remove an entity. If the id is valid then the entity is
    // removed, all links to it are set to null ids, and the history is
    // changed, observers are informed of the cahnges, and true is returned.
    // Undoing will add back the entity and reconnect all broken links. If the
    // id is invalid then nothing happens and false is returned.
    bool remove(Signal_Source a_source, Entity_ID a_id);

    // Request that the editor for this entity be opened or switched to. This
    // only informs the observers.
    bool request_editor(Signal_Source a_source, Entity_ID a_id);

    // Request that the focus change to this entity. This only informs the
    // observers.
    bool request_outliner(Signal_Source a_source, Entity_ID a_id);


    // Entity System Data
    //------------------------------------------------------------

    // Get the type of a given entity. If the id is null or invalid the string
    // is empty.
    String type(Entity_ID a_id) const;

    // Get the tooltip for a given entity. If the id is null or invalid the
    // string is empty.
    String tooltip(Entity_ID a_id) const;

    // Get the iconpath for a given entity. If the id is null or invalid the
    // string is empty.
    String iconpath(Entity_ID a_id) const;


    // Entity Names
    //------------------------------------------------------------
    // All entities have a name that allows users to identify them rather than
    // using the id. The manager makes sure each entity has a unique name.

    // Get the name of the data associated with the supplied id. If the id is
    // null or invalid, the returned name is empty, which names cannot be.
    String name(Entity_ID a_id) const;

    // Undoable change an entity's name. If the id is valid and the supplied
    // name is different from the current name, then if the supplied name is
    // not already the name of another entity the name is changed to that, but
    // if it is already used the name is changed to an altered version of the
    // supplied name, the history is changed, observers are informed, true is
    // returned. Undoing will change the entity name back to what it was
    // previously. If the id is invalid or the name is equal to the entity's
    // current name then nothing happens and false is returned.
    bool set_name(Signal_Source a_source, Entity_ID a_id, String const& a_name);


    // Entity Member Data
    //------------------------------------------------------------
    // An entity may or may not have a number of data mambers, the configuration
    // of which is fixed on construction, but the user may edit the data values
    // in an undoable manner. Each member has a name that is unique among the
    // members the owner entity has. Each member has a specific type that has
    // constraints on what the value can be set to.

    // Does this entity have any data members? Returns false if the id is null
    // or invalid.
    bool has_members(Entity_ID a_id) const;

    // How many data members does this entity have? Returns 0 if the id is null
    // or invalid, or the entity has no members.
    std::size_t member_count(Entity_ID a_id) const;

    // Get the name of this entity's data member with this index. If the
    // entity is null or invalid, or is valid but the index is invalid, the
    // returned string is empty.
    String member_name(Entity_ID a_id, std::size_t a_index) const;

    // Get the type of this entity's data member with this index. If the
    // entity is null or invalid, or is valid but the index is invalid, the
    // returned type is Data_Type::Invalid.
    Data_Type member_type(Entity_ID a_id, std::size_t a_index) const;

    // Get the value of the entity's data member with this index. If the
    // entity is null or invalid, or is valid but the index is invalid, the
    // returned string is an invalid variant.
    Variant member_value(Entity_ID a_id, std::size_t a_index) const;

    // Undoable change an entity member value. If the id is valid, the index
    // is valid for that entity, the variant type is the same as the member
    // data type, and the member value can be set to the variant value
    // according to the member's constraints the operation succeeds and the
    // member value is changed to the supplied value, the history is changed,
    // observers are informed, true is returned. If any of the conditions are
    // not met then the operation fails and false is returned.
    bool set_member_value(Entity_ID a_id, std::size_t a_index, Variant const& a_variant) const;

    // Get the entity member's default value. If the member does not exist
    // the returend variant is invalid.
    Variant member_default_value(Entity_ID a_id, std::size_t a_index) const;

    // If the entity member is a numeric type, get its maximum value. If the
    // member doesn't exist or is not one of these types, the returend variant
    // is invalid.
    Variant member_max_value(Entity_ID a_id, std::size_t a_index) const;

    // If the entity member is a numeric type, get its minimum value. If the
    // member doesn't exist or is not one of these types, the returend variant
    // is invalid.
    Variant member_min_value(Entity_ID a_id, std::size_t a_index) const;

    // If the entity member is a float or double, get its significant figure
    // number. If the member doesn't exist or is not one of these types, -1 is
    // returned.
    int member_sig_figs(Entity_ID a_id, std::size_t a_index) const;

    // If the entity member is a string or path, get its maximum length. If
    // the member doesn't exist or is not one of these types, -1 is returned.
    int member_max_length(Entity_ID a_id, std::size_t a_index) const;






  };
}

#endif // SAK_ENTITY_MANAGER_HPP
