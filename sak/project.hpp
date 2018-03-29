#ifndef SAK_PROJECT_HPP
#define SAK_PROJECT_HPP

#ifndef SAK_PROJECT_FWD_HPP
#include "project_fwd.hpp"
#endif

#ifndef SAK_ABSTRACT_OBSERVER_FWD_HPP
#include "abstract_observer_fwd.hpp"
#endif

#ifndef SAK_ABSTRACT_SIGNAL_FWD_HPP
#include "abstract_signal_fwd.hpp"
#endif

#ifndef SAK_ENTITY_ID_FWD_HPP
#include "entity_id_fwd.hpp"
#endif

#ifndef SAK_VARIANT_FWD_HPP
#include "variant_fwd.hpp"
#endif

#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif

#ifndef INCLUDE_STD_VECTOR
#define INCLUDE_STD_VECTOR
#include <vector>
#endif

class QString;

namespace sak
{
  //---------------------------------------------------------------------------
  // Project
  //---------------------------------------------------------------------------
  // A Project contains a number of entities.
  class Project
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
    explicit Project(QString const& a_filepath);
    ~Project();

    Project(Project const&) = delete;
    Project& operator=(Project const&) = delete;

    Project(Project &&) = delete;
    Project& operator=(Project &&) = delete;

    // Interface
    //============================================================

    // Observers
    //------------------------------------------------------------
    // Add an object that will rely on the Project's signals. If
    // nulltpr or already present, nothing happens.
    void add_observer(Abstract_Observer* a_observer);

    // Remove an object that will rely on the Project's signals. If
    // nulltpr or not present, nothing happens.
    void remove_observer(Abstract_Observer* a_observer);

    // Clear all the observers so that nothing relies on changes to this.
    void clear_observers();


    // Overall Data
    //------------------------------------------------------------
    void save() const;

    void load();

    // Data that is fixed on contruction.
    QString name() const;

    QString location() const;

    QString filepath() const;


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
    bool has_type(QString const& a_type) const;

    // How many entities of a given type are in this Project?
    std::size_t count_of(QString const& a_type) const;

    // Get all the Entities of a given type. If the type is invalid then the result is empty.
    std::vector<Entity_ID> get_all_of(QString const& a_type) const;

    // Is this a valid Entity Type?
    bool can_make(QString const& a_type) const;

    // Get all of the valid Entity types.
    std::vector<QString> get_all_types() const;


    // Entity Collection Editing
    //------------------------------------------------------------

    // Undoable make a new entity using the supplied typestring. If the typestring is invalid the returned
    // id is null, otherwise it is the id of the new entity.
    Entity_ID try_add(Signal_Source a_source, QString const& a_type);

    // Undoable remove entity. Return true if the operation resulted in an undoable command.
    bool try_remove(Signal_Source a_source, Entity_ID a_id);

    // Request that the editor for this entity be opened or switched to.
    bool try_request_editor(Signal_Source a_source, Entity_ID a_id);

    // Request that the focus change to this entity.
    bool try_request_outliner(Signal_Source a_source, Entity_ID a_id);


    // Entity Names
    //------------------------------------------------------------

    // Does this name appear in the data?
    bool has_name(QString const& a_name) const;

    // Get the name of the data associated with the supplied id. If the id is null or invalid,
    // the returned name is empty, which names cannot be.
    QString name(Entity_ID a_id) const;

    // Get the id with this name. If the name is invalid a null id is returned.
    Entity_ID get_named(QString const& a_name) const;

    // Get all the objects names in data order
    std::vector<QString> get_all_names() const;

    // Attempt an undoable change to the name of the data associated with the supplied id. If
    // the id is valid and the supplied value results in a change to the data, signals are emitted
    // telling everything to update this name, and true is returned. If the id is null or
    // invalid, nothing happens and false is returned. Success does not indicate that the name
    // is set to what has been supplied, but that the name has changed.
    bool try_set_name(Signal_Source a_source, Entity_ID a_id, QString const& a_name);



    // Entity System Data
    //------------------------------------------------------------

    // Get the type of a given entity. If the id is null or invalid the string is empty.
    QString type(Entity_ID a_id) const;

    // Get the iconpath for a given entity. If the id is null or invalid the string is empty.
    QString iconpath(Entity_ID a_id) const;


/*
    // Entity Member Data
    //------------------------------------------------------------
    // Get the member count for an entity.
    std::size_t member_count(Entity_ID a_id) const;

    // Type try_get_member_type(Entity_ID a_id, std::size_t a_index) const;

    // Attempt to get the data value for the member at this index in the data associated with the
    // supplied id. If the id is valid and index is valid for that entity, the returned variant
    // contains the data value in the proper type. If id is null or invalid, or the index is invalid
    // for a valid id, the variant is invalid.
    Variant try_get_member(Entity_ID a_id, std::size_t a_index) const;

    // As try_get except the member is found by matching to the name and not its index. If the name
    // is empty or not present, the returned variant is invalid.
    Variant try_get_member_named(Entity_ID a_id, QString const& a_name) const;

    // Attempt an undoable change to the data value for the member at this index in the data
    // associated with the supplied id. If the id is valid, the index is valid for that entity, and
    // the variant is the right data type, then the change is made and true is returned. If the id
    // is null or invalid, or the variant is the wrong type, nothing happens and false is returned.
    bool try_set_member(Signal_Source a_source, Entity_ID a_id, std::size_t a_index, Variant const& a_value);

    // As try_set except the member is found by matching to the name and not its index. If the name
    // is empty or not present, the operation fails and returns false.
    bool try_set_member_named(Signal_Source a_source, Entity_ID a_id, QString const& a_name, Variant const& a_value);
*/
  };
}

#endif // SAK_PROJECT_HPP
