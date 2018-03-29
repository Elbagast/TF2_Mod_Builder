#ifndef SAK_ENTITY_PART_MANAGER_HPP
#define SAK_ENTITY_PART_MANAGER_HPP

#ifndef SAK_ENTITY_PART_MANAGER_FWD_HPP
#include "entity_part_manager_fwd.hpp"
#endif

#ifndef SAK_ENTITY_ID_HPP
#include "entity_id.hpp"
#endif

#ifndef INCLUDE_STD_MAP
#define INCLUDE_STD_MAP
#include <map>
#endif

#ifndef INCLUDE_STD_VECTOR
#define INCLUDE_STD_VECTOR
#include <vector>
#endif

#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif

namespace sak
{  
  //---------------------------------------------------------------------------
  // Entity_Part_Manager<T_Part>
  //---------------------------------------------------------------------------
  // Simple holder for all instances of part of a Entities. Data is accessed
  // through it and deleted from it when the reference counting part reaches 0.
  // T_Part should have a member function compatible with the signature:
  // Entity_ID id() const

  template <typename T_Part>
  class Entity_Part_Manager
  {
  private:
    // Data Members
    //============================================================
    std::map<Entity_ID, std::unique_ptr<T_Part>> m_data;

  public:
    // Special 6
    //============================================================
    Entity_Part_Manager();
    ~Entity_Part_Manager();

    // No copying because we hold pointers to things that should
    // only exist once.
    Entity_Part_Manager(Entity_Part_Manager const& a_other) = delete;
    Entity_Part_Manager& operator=(Entity_Part_Manager const& a_other) = delete;

    // No moving because things will hold a pointer to this.
    Entity_Part_Manager(Entity_Part_Manager && a_other) = delete;
    Entity_Part_Manager& operator=(Entity_Part_Manager && a_other) = delete;

    // Interface
    //============================================================
    // Is this currently empty?
    bool empty() const;

    // Do we have data for this id?
    bool has(Entity_ID a_id) const;

    // How many data entries are there?
    std::size_t count() const;

    // Get all the ids for the data.
    std::vector<Entity_ID> all_ids() const;

    // Get all of the data. Calling delete on the pointers will break things
    // so don't do that. Entity parts should know their own Entity_ID so
    // returning that as well is redundant.
    std::vector<T_Part*> all_data() const;

    // Get data for a given id. If the id is not present, the returned
    // pointer is nullptr.
    T_Part* get(Entity_ID a_id);

    // Constant data access for a given id. Behaviour is as get.
    T_Part const* cget(Entity_ID a_id) const;

    // Add new data. If the id is not already present and is not null,
    // and the data is not nullptr, the data is moved into this with the
    // id as the key and true is returned. If these conditions are not met
    // nothing happens and false is returned.
    bool add(Entity_ID a_id, std::unique_ptr<T_Part>&& a_data);

    // Remove and destroy this id and its data. If the id is currently used
    // in this the data is removed and true is returned. If the id is not
    // present or is invalid, nothing happens and false is returned.
    bool remove(Entity_ID a_id);

    // Remove and return the data associated with this id. If the id is
    // currently used the data pointer is taken from the data, the id, data
    // pair is removed and destroyed and the data returned. If the id is
    // not present of is invalid, nothing happens and a nullptr is returned.
    std::unique_ptr<T_Part> extract(Entity_ID a_id);

    // Destroy all the data. After this the data is empty.
    void clear();
  };
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Entity_Part_Manager<T_Part>
//---------------------------------------------------------------------------
// Simple holder for all instances of part of a Entities. Data is accessed
// through it and deleted from it when the reference counting part reaches 0.
// T_Part should have a member function compatible with the signature:
// Entity_ID id() const

// Special 6
//============================================================
template <typename T>
sak::Entity_Part_Manager<T>::Entity_Part_Manager() = default;

template <typename T>
sak::Entity_Part_Manager<T>::~Entity_Part_Manager() = default;

// Interface
//============================================================
// Is this currently empty?
template <typename T>
bool sak::Entity_Part_Manager<T>::empty() const
{
  // Forward the call.
  return m_data.empty();
}

// Do we have data for this id?
template <typename T>
bool sak::Entity_Part_Manager<T>::has(Entity_ID a_id) const
{
  // If the id is a null id then stop now.
  if (is_null(a_id))
  {
    return false;
  }

  // Try and find the id.
  return m_data.find(a_id) != m_data.cend();
}

// How many data entries are there?
template <typename T>
std::size_t sak::Entity_Part_Manager<T>::count() const
{
  // Forward the call.
  return m_data.size();
}

// Get all the ids for the data.
template <typename T>
std::vector<sak::Entity_ID> sak::Entity_Part_Manager<T>::all_ids() const
{
  // Make a result container.
  std::vector<Entity_ID> l_result{};

  // Reserve memory for the number of data entries.
  l_result.reserve(m_data.size());

  // For each pair in the map, add the id(key) to the result.
  for (auto const& l_item : m_data)
  {
    l_result.push_back(l_item.first);
  }

  // Return the result container. It could be empty.
  return l_result;
}

// Get all of the data. Calling delete on the pointers will break things
// so don't do that. Entity parts should know their own Entity_ID so
// returning that as well is redundant.
template <typename T>
std::vector<T*> sak::Entity_Part_Manager<T>::all_data() const
{
  // Make a result container.
  std::vector<T*> l_result{};

  // Reserve memory for the number of data entries.
  l_result.reserve(m_data.size());

  // For each pair in the map, add the data ptr to the result.
  for (auto const& l_item : m_data)
  {
    l_result.push_back(l_item.second.get());
  }

  // Return the result container. It could be empty.
  return l_result;
}

// Get data for a given id. If the id is not present, the returned
// pointer is nullptr.
template <typename T>
T* sak::Entity_Part_Manager<T>::get(Entity_ID a_id)
{
  // If the id is a null id then stop now.
  if (is_null(a_id))
  {
    return nullptr;
  }

  // Find the id.
  auto l_found = m_data.find(a_id);

  // If it was not found return nullptr.
  if (l_found == m_data.cend())
  {
    return nullptr;
  }
  // Else return the data.
  else
  {
    return l_found->second.get();
  }
}

// Constant data access for a given id. Behaviour is as get.
template <typename T>
T const* sak::Entity_Part_Manager<T>::cget(Entity_ID a_id) const
{
  // If the id is a null id then stop now.
  if (is_null(a_id))
  {
    return nullptr;
  }

  // Find the id.
  auto l_found = m_data.find(a_id);

  // If it was not found return nullptr.
  if (l_found == m_data.cend())
  {
    return nullptr;
  }
  // Else return the data.
  else
  {
    return l_found->second.get();
  }
}

// Add new data. If the id is not already present and is not null,
// and the data is not nullptr, the data is moved into this with the
// id as the key and true is returned. If these conditions are not met
// nothing happens and false is returned.
template <typename T>
bool sak::Entity_Part_Manager<T>::add(Entity_ID a_id, std::unique_ptr<T>&& a_data)
{
  // If the id is a null id then stop now.
  if (is_null(a_id))
  {
    return false;
  }

  // Find the id.
  auto l_found = m_data.find(a_id);

  // If we didn't find id, and the data's id matches this id
  if (l_found == m_data.cend() && a_id == a_data->id())
  {
    // Make an id:data pair by moving in the data.
    m_data.emplace(a_id, std::move(a_data));
    return true;
  }
  // Else do nothing
  else
  {
    return false;
  }
}

// Remove and destroy this id and its data. If the id is currently used
// in this the data is removed and true is returned. If the id is not
// present or is invalid, nothing happens and false is returned.
template <typename T>
bool sak::Entity_Part_Manager<T>::remove(Entity_ID a_id)
{
  // If the id is a null id then stop now.
  if (is_null(a_id))
  {
    return false;
  }

  // Find the id.
  auto l_found = m_data.find(a_id);

  // If we found it destory the data.
  if (l_found == m_data.cend())
  {
    m_data.erase(a_id);
    return true;
  }
  // Else do nothing
  else
  {
    return false;
  }
}

// Remove and return the data associated with this id. If the id is
// currently used the data pointer is taken from the data, the id, data
// pair is removed and destroyed and the data returned. If the id is
// not present of is invalid, nothing happens and a nullptr is returned.
template <typename T>
std::unique_ptr<T> sak::Entity_Part_Manager<T>::extract(Entity_ID a_id)
{
  // Make a result object to swap into.
  std::unique_ptr<T> l_result{};

  // If the id is a null id then stop now.
  if (is_null(a_id))
  {
    return l_result;
  }

  // Find the id.
  auto l_found = m_data.find(a_id);

  // If we found it swap the data into our result object and destroy
  // the data in this.
  if (l_found == m_data.cend())
  {
    std::swap(l_result, l_found->second);
    m_data.erase(a_id);
  }

  // Return the result that could be a nullptr or some data.
  return l_result
}

// Destroy all the data. After this the data is empty.
template <typename T>
void sak::Entity_Part_Manager<T>::clear()
{
  // Forward the call.
  m_data.clear();
}

#endif // SAK_ENTITY_PART_MANAGER_HPP
