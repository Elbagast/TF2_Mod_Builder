#include "entity_manager.hpp"

#include "entity.hpp"
#include "name_utilities.hpp"

#include <algorithm>

#include <QString>
//---------------------------------------------------------------------------
// Entity_Manager
//---------------------------------------------------------------------------
// Manage a collection of unique Entities. All will have unique ids and data,
// and Entity_Handle ensures the data persists even when it is removed from
// here so that the data can be used elsewhere or added back in.

// Special 6
//============================================================
sak::Entity_Manager::Entity_Manager() = default;

sak::Entity_Manager::~Entity_Manager() = default;

// Interface
//============================================================
// Is this currently empty?
bool sak::Entity_Manager::is_empty() const
{
  return m_data.empty();
}

// How many active Entities are there?
std::size_t sak::Entity_Manager::count() const
{
  return m_data.size();
}

namespace
{
  decltype(auto) do_find_id(std::vector<sak::Entity_Handle> const& a_handles, sak::Entity_ID a_id)
  {
    return std::find_if(a_handles.cbegin(),
                        a_handles.cend(),
                        [a_id](sak::Entity_Handle const& a_handle){ return a_handle.id() == a_id; });
  }

  bool do_has_id(std::vector<sak::Entity_Handle> const& a_handles, sak::Entity_ID a_id)
  {
    return do_find_id(a_handles, a_id) != a_handles.cend();
  }


  decltype(auto) do_find_handle(std::vector<sak::Entity_Handle> const& a_handles, sak::Entity_Handle const& a_handle)
  {
    return std::find(a_handles.cbegin(), a_handles.cend(), a_handle);
  }

  bool do_has_handle(std::vector<sak::Entity_Handle> const& a_handles, sak::Entity_Handle const& a_handle)
  {
    return do_find_handle(a_handles, a_handle) != a_handles.cend();
  }

  decltype(auto) do_find_name(std::vector<sak::Entity_Handle> const& a_handles, QString const& a_name)
  {
    return std::find_if(a_handles.cbegin(),
                        a_handles.cend(),
                        [&a_name](sak::Entity_Handle const& a_handle){ return a_handle->cname_component()->get_name() == a_name; });
  }

  bool do_has_name(std::vector<sak::Entity_Handle> const& a_handles, QString const& a_name)
  {
    return do_find_name(a_handles, a_name) != a_handles.cend();
  }
}

// Does this id correspond to a currently active Entity?
bool sak::Entity_Manager::has(Entity_ID a_id) const
{
  return do_has_id(m_data, a_id);
}

// Does this handle correspond to a currently active Entity?
bool sak::Entity_Manager::has_handle(Entity_Handle const& a_handle) const
{
  return do_has_handle(m_data, a_handle);
}

// Get the index for the Entity with this id. If the id is null or not
// present the result is equal to count().
std::size_t sak::Entity_Manager::index(Entity_ID a_id) const
{
  return static_cast<std::size_t>(std::distance(m_data.cbegin(), do_find_id(m_data, a_id)));
}

// Get the index for the Entity with this handle. If the handle is null or not
// present the result is equal to count().
std::size_t sak::Entity_Manager::index_handle(Entity_Handle const& a_handle) const
{
  return static_cast<std::size_t>(std::distance(m_data.cbegin(), do_find_handle(m_data, a_handle)));
}

// Get all the ids for the data.
std::vector<sak::Entity_ID> sak::Entity_Manager::all_ids() const
{
  std::vector<Entity_ID> l_result{};
  l_result.reserve(m_data.size());
  for (auto const& l_handle : m_data)
  {
    l_result.push_back(l_handle.id());
  }
  return l_result;
}

// Get all of the handles.
std::vector<sak::Entity_Handle> sak::Entity_Manager::all_handles() const
{
  return m_data;
}

// Get data for a given id. If the id is not present then the handle
// is a null handle.
sak::Entity_Handle sak::Entity_Manager::get_handle(Entity_ID a_id) const
{
  auto l_found = do_find_id(m_data, a_id);
  if (l_found != m_data.cend())
  {
    return *l_found;
  }
  else
  {
    return Entity_Handle{};
  }
}

// Get the id for the Entity at this index. If the index is invalid the
// returned id is a null id.
sak::Entity_ID sak::Entity_Manager::get_at(std::size_t a_index) const
{
  if (a_index < m_data.size())
  {
    return m_data.at(a_index).id();
  }
  else
  {
    return make_null_entity_id();
  }
}

// Get the handle for the Entity at this index. If the index is invalid the
// returned handle is a null handle.
sak::Entity_Handle sak::Entity_Manager::get_handle_at(std::size_t a_index) const
{
  if (a_index < m_data.size())
  {
    return m_data.at(a_index);
  }
  else
  {
    return Entity_Handle{};
  }
}

// Is there an entity with this name?
bool sak::Entity_Manager::has_name(QString const& a_name) const
{
  return do_has_name(m_data, a_name);
}

// Alter this name so that it is not equal to any present in the data.
void sak::Entity_Manager::fix_name(QString& a_name) const
{
  auto l_names = this->get_all_names();

  uniqueify_name(a_name, l_names);
}

// Get all of the Entity names in alphabetical order.
std::vector<QString> sak::Entity_Manager::get_all_names() const
{
  std::vector<QString> l_result{};
  l_result.reserve(m_data.size());
  for (auto const& l_handle : m_data)
  {
    l_result.push_back(l_handle->cname_component()->get_name());
  }
  // Sort the names into alphabetical order.
  std::sort(l_result.begin(), l_result.end());
  return l_result;
}

// Get the id for the Entity that has this name. If the name is not found the
// returned id is null.
sak::Entity_ID sak::Entity_Manager::get_named(QString const& a_name) const
{
  auto l_found = do_find_name(m_data, a_name);
  if (l_found != m_data.cend())
  {
    return l_found->id();
  }
  else
  {
    return make_null_entity_id();
  }
}

// Get the handle for the Entity that has this name. If the name is not found the
// returned handle is null.
sak::Entity_Handle sak::Entity_Manager::get_handle_named(QString const& a_name) const
{
  auto l_found = do_find_name(m_data, a_name);
  if (l_found != m_data.cend())
  {
    return *l_found;
  }
  else
  {
    return Entity_Handle{};
  }
}

// Get all of the ids for the Entities in sorted order.
std::vector<sak::Entity_ID> sak::Entity_Manager::get_all() const
{
  std::vector<Entity_ID> l_result{};
  l_result.reserve(m_data.size());
  for (auto const& l_handle : m_data)
  {
    l_result.push_back(l_handle.id());
  }
  return l_result;
}

// Get all of the handles for the Entities in sorted order.
std::vector<sak::Entity_Handle> sak::Entity_Manager::get_all_handles() const
{
  std::vector<Entity_Handle> l_result{};
  l_result.reserve(m_data.size());
  for (auto const& l_handle : m_data)
  {
    l_result.push_back(l_handle);
  }
  return l_result;
}

// Can this handle be added? Return true if it is not present.
bool sak::Entity_Manager::can_add(Entity_Handle const& a_handle) const
{
  return not_null(a_handle) && !do_has_handle(m_data, a_handle);
}

// Attempt to add this handle. If it cannot be added nothing happens and
// count() is returned. If it can it is added and the index it ends up
// at is returned.
std::size_t sak::Entity_Manager::add(Entity_Handle const& a_handle)
{
  if (this->can_add(a_handle))
  {
    m_data.push_back(a_handle);
    std::sort(m_data.begin(), m_data.end());
    return this->index_handle(a_handle);
  }
  else
  {
    return this->count();
  }
}

// Can this handle be added? Return true if it is present.
bool sak::Entity_Manager::can_remove(Entity_Handle const& a_handle) const
{
  return not_null(a_handle) && do_has_handle(m_data, a_handle);
}

// Attempt to remove this handle. If it can be removed it is and the index
// it was at is returned. If it can't npthing happens and count() is returned.
std::size_t sak::Entity_Manager::remove(Entity_Handle const& a_handle)
{
  if (this->can_remove(a_handle))
  {
    auto l_result = this->index_handle(a_handle);

    m_data.erase(std::remove(m_data.begin(), m_data.end(), a_handle));

    return l_result;
  }
  else
  {
    return this->count();
  }
}

// Does the project contain any entities of this type?
bool sak::Entity_Manager::has_type(QString const& a_type) const
{
  return std::find_if(m_data.cbegin(), m_data.cend(),
                      [&a_type](Entity_Handle const& a_handle) { return a_handle->ctype_component()->get_type() == a_type; }) != m_data.cend();

}

// Get the number of Entities that have this type.
std::size_t sak::Entity_Manager::count_of(QString const& a_type) const
{
  std::size_t l_result{0u};
  for (auto const& l_handle : m_data)
  {
    if (l_handle->ctype_component()->get_type() == a_type)
    {
      ++l_result;
    }
  }
  return l_result;
}

// Get all the ids of Entities of a given type.
std::vector<sak::Entity_ID> sak::Entity_Manager::get_all_of(QString const& a_type) const
{
  std::vector<Entity_ID> l_result{};
  for (auto const& l_handle : m_data)
  {
    if (l_handle->ctype_component()->get_type() == a_type)
    {
      l_result.push_back(l_handle.id());
    }
  }
  return l_result;
}

// Get all the handles of Entities of a given type.
std::vector<sak::Entity_Handle> sak::Entity_Manager::get_all_of_handles(QString const& a_type) const
{
  std::vector<Entity_Handle> l_result{};
  for (auto const& l_handle : m_data)
  {
    if (l_handle->ctype_component()->get_type() == a_type)
    {
      l_result.push_back(l_handle);
    }
  }
  return l_result;
}
