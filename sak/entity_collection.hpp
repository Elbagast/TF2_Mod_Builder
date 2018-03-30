#ifndef SAK_ENTITY_COLLECTION_HPP
#define SAK_ENTITY_COLLECTION_HPP

#ifndef SAK_ENTITY_COLLECTION_FWD_HPP
#include "entity_collection_fwd.hpp"
#endif

#ifndef SAK_ENTITY_ID_HPP
#include "entity_id.hpp"
#endif

#ifndef SAK_ENTITY_HANDLE_HPP
#include "entity_handle.hpp"
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
  // Entity_Collection
  //---------------------------------------------------------------------------
  // Manage a collection of unique Entities. All will have unique ids and data,
  // and Entity_Handle ensures the data persists even when it is removed from
  // here so that the data can be used elsewhere or added back in.

  class Entity_Collection
  {
  private:
    // Data Members
    //============================================================
    std::vector<Entity_Handle> m_data;

  public:
    // Special 6
    //============================================================
    Entity_Collection();
    ~Entity_Collection();

    // Block copying because we hold lots of unique_ptrs.
    Entity_Collection(Entity_Collection const& a_other) = delete;
    Entity_Collection& operator=(Entity_Collection const& a_other) = delete;

    // Block moving because things will hold a pointer to this.
    Entity_Collection(Entity_Collection && a_other) = delete;
    Entity_Collection& operator=(Entity_Collection && a_other) = delete;

    // Interface
    //============================================================
    // Is this currently empty?
    bool is_empty() const;

    // How many active Entities are there?
    std::size_t count() const;

    // Does this id correspond to a currently active Entity?
    bool has(Entity_ID a_id) const;

    // Does this handle correspond to a currently active Entity?
    bool has_handle(Entity_Handle const& a_handle) const;

    // Get the index for the Entity with this id. If the id is null or not
    // present the result is equal to count().
    std::size_t index(Entity_ID a_id) const;

    // Get the index for the Entity with this handle. If the handle is null or not
    // present the result is equal to count().
    std::size_t index_handle(Entity_Handle const& a_handle) const;

    // Get all the ids for the data.
    std::vector<Entity_ID> all_ids() const;

    // Get all of the handles.
    std::vector<Entity_Handle> all_handles() const;

    // Get data for a given id. If the id is not present then the handle
    // is a null handle.
    Entity_Handle get_handle(Entity_ID a_id) const;

    // Get the id for the Entity at this index. If the index is invalid the
    // returned id is a null id.
    Entity_ID get_at(std::size_t a_index) const;

    // Get the handle for the Entity at this index. If the index is invalid the
    // returned handle is a null handle.
    Entity_Handle get_handle_at(std::size_t a_index) const;

    // Is there an entity with this name?
    bool has_name(std::string const& a_name) const;

    // Alter this name so that it is not equal to any present in the data.
    void fix_name(std::string& a_name) const;

    // Get all of the Entity names in alphabetical order.
    std::vector<std::string> get_all_names() const;

    // Get the id for the Entity that has this name. If the name is not found the
    // returned id is null.
    Entity_ID get_named(std::string const& a_name) const;

    // Get the handle for the Entity that has this name. If the name is not found the
    // returned handle is null.
    Entity_Handle get_handle_named(std::string const& a_name) const;

    // Get all of the ids for the Entities in sorted order.
    std::vector<Entity_ID> get_all() const;

    // Get all of the handles for the Entities in sorted order.
    std::vector<Entity_Handle> get_all_handles() const;

    // Can this handle be added? Return true if it is not present.
    bool can_add(Entity_Handle const& a_handle) const;

    // Attempt to add this handle. If it cannot be added nothing happens and
    // count() is returned. If it can it is added and the index it ends up
    // at is returned.
    std::size_t add(Entity_Handle const& a_handle);

    // Can this handle be added? Return true if it is present.
    bool can_remove(Entity_Handle const& a_handle) const;

    // Attempt to remove this handle. If it can be removed it is and the index
    // it was at is returned. If it can't npthing happens and count() is returned.
    std::size_t remove(Entity_Handle const& a_handle);

    // Does the project contain any entities of this type?
    bool has_type(std::string const& a_type) const;

    // Get the number of Entities that have this type.
    std::size_t count_of(std::string const& a_type) const;

    // Get all the ids of Entities of a given type.
    std::vector<Entity_ID> get_all_of(std::string const& a_type) const;

    // Get all the handles of Entities of a given type.
    std::vector<Entity_Handle> get_all_of_handles(std::string const& a_type) const;
  };
}

#endif // SAK_ENTITY_COLLECTION_HPP
