#include "entity_factory.hpp"

#include "abstract_entity_maker.hpp"
#include "entity.hpp"
#include "../entity_id.hpp"
#include "entity_handle.hpp"

#include <cassert>

//---------------------------------------------------------------------------
// Entity_Factory
//---------------------------------------------------------------------------
// Make an entity using the supplied id. If the id is null the handle is null
// and no entity data was created.

// Special 6
//============================================================
// Create with a set of built in Entity makers.
sak::Entity_Factory::Entity_Factory() :
  m_next_id{0u},
  m_makers{}
{
}

sak::Entity_Factory::~Entity_Factory() = default;

sak::Entity_Factory::Entity_Factory(Entity_Factory &&) = default;
sak::Entity_Factory& sak::Entity_Factory::operator=(Entity_Factory &&) = default;

// Interface
//============================================================
// Is this a type of Entity we can make?
bool sak::Entity_Factory::has_type(String const& a_type) const
{
  return m_makers.find(a_type) != m_makers.cend();
}

// Get all of the available Entity types.
std::vector<sak::String> sak::Entity_Factory::all_types() const
{
  std::vector<String> l_result{};
  l_result.reserve(m_makers.size());
  for (auto const& l_pair : m_makers)
  {
    l_result.push_back(l_pair.first);
  }
  return l_result;
}

// Make this kind of Entity. It will have its name set to the type and the
// data is default initialised to empty. If the returned handle is destroyed
// before being copied or moved, the Entity data is also destroyed. If the
// type supplied is not one that can be made, then the handle is a null
// handle.
sak::Entity_Handle sak::Entity_Factory::make_entity(String const& a_type) const
{
  // Stop if empty.
  if (a_type.is_empty())
  {
    return Entity_Handle{};
  }

  // Find the type
  auto l_found = m_makers.find(a_type);

  // If found, make a handle
  if (l_found != m_makers.cend())
  {
    // Make an id to use.
    auto l_id = make_entity_id(++m_next_id);

    // Better have a valid id.
    assert(not_null(l_id));

    // Make a handle using the id.
    return Entity_Handle{l_found->second->make_entity(l_id)};
  }
  // Else return a null handle.
  else
  {
    return Entity_Handle{};
  }
}

// Attempt to add this maker to the collection. If it's type is not already
// present it will be added and true is returned. If a maker with the same
// type is already present nothing happens and false is returned.
bool sak::Entity_Factory::add_maker(std::unique_ptr<Abstract_Entity_Maker>&& a_maker)
{
  if (a_maker && !this->has_type(a_maker->type()))
  {
    m_makers.emplace(a_maker->type(), std::move(a_maker));
    return true;
  }
  else
  {
    return false;
  }
}

// Attempt to remove the maker with this type. If one is found, it is removed
// from the data and returned. If it is not found, a nullptr is returned.
std::unique_ptr<sak::Abstract_Entity_Maker> sak::Entity_Factory::remove_maker(String const& a_type)
{
  // Initialise the result to nullptr.
  std::unique_ptr<Abstract_Entity_Maker> l_result{};

  // Find the type.
  auto l_found = m_makers.find(a_type);

  // If found, swap the data
  if (l_found != m_makers.cend())
  {
    // Swap the data into the result variable.
    std::swap(l_result, l_found->second);

    // Remove the key:value pair from the data.
    m_makers.erase(l_found);
  }
  // Return the result, which may be data or nullptr.
  return l_result;
}
