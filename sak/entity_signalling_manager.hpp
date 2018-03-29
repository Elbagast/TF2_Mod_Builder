#ifndef SAK_ENTITY_SIGNALLING_MANAGER_HPP
#define SAK_ENTITY_SIGNALLING_MANAGER_HPP

#ifndef SAK_ENTITY_SIGNALLING_MANAGER_FWD_HPP
#include "entity_signalling_manager_fwd.hpp"
#endif

#ifndef SAK_ENTITY_MANAGER_HPP
#include "entity_manager.hpp"
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

namespace sak
{
  class Abstract_Project_Signal;

  //---------------------------------------------------------------------------
  // Entity_Manager
  //---------------------------------------------------------------------------
  // Manage a collection of unique Entities. All will have unique ids and data,
  // and Entity_Handle ensures the data persists even when it is removed from
  // here so that the data can be used elsewhere or added back in.


  class Entity_Manager
  {
  private:
    // Data Members
    //============================================================
    std::vector<Entity_Handle> m_data;

  public:
    // Special 6
    //============================================================
    Entity_Signalling_Manager();
    ~Entity_Signalling_Manager();

    // Block copying because we hold lots of unique_ptrs.
    Entity_Signalling_Manager(Entity_Signalling_Manager const& a_other) = delete;
    Entity_Signalling_Manager& operator=(Entity_Signalling_Manager const& a_other) = delete;

    // Block moving because things will hold a pointer to this.
    Entity_Signalling_Manager(Entity_Signalling_Manager && a_other) = delete;
    Entity_Signalling_Manager& operator=(Entity_Signalling_Manager && a_other) = delete;

    // Interface
    //============================================================
    // Is this currently empty?
    bool empty() const;

    // Does this id correspond to a currently active Entity?
    bool has(Entity_ID a_id) const;

    // How many active Entities are there?
    std::size_t count() const;

    // Get all the ids for the data.
    std::vector<Entity_ID> all_ids() const;

    // Get all of the handles.
    std::vector<Entity_Handle> all_handles() const;

    // Get data for a given id. If the id is not present then the handle
    // is a null handle.
    Entity_Handle get(Entity_ID a_id) const;

    // Get the handle at a given index. If the index is invalid then the
    // handle is a null handle.
    Entity_Handle get_at(std::size_t a_index) const;

    // Add this handle to the data if it is not already present and return
    // true. If it is already present or is a null handle, nothing happens
    // and false is returned.
    bool add(Entity_Handle const& a_handle);

    // Remove and destroy this id and its data. If the id is currently used
    // in this the data is removed and true is returned. If the id is not
    // present or is invalid, nothing happens and false is returned.
    bool remove(Entity_ID a_id);

    // Remove and return the data associated with this id. If the id is
    // currently used the handle is taken out of the data so that it can
    // be returned. If the id is not present of is invalid, nothing happens
    // and a null handle is returned.
    Entity_Handle extract(Entity_ID a_id);

    // Destroy all the data. After this the data is empty.
    void clear();
  };
}

#endif // ENTITY_SIGNALLING_MANAGER_HPP
