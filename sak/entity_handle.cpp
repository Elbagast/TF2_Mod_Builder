#include "entity_handle.hpp"

#include "entity_id.hpp"
#include "entity.hpp"

#include <cassert>

//---------------------------------------------------------------------------
// Handle<T_Class_Def>
//---------------------------------------------------------------------------

// Construct a null Handle. It does not reference any data and has no
// associated manager. This can only be changed by copy or move #
// assignment to this.
sak::Entity_Handle::Entity_Handle():
  m_data{}
{
  // This had better be emtpy.
  assert(m_data == nullptr);
}

sak::Entity_Handle::Entity_Handle(std::shared_ptr<Entity>&& a_data):
  m_data{std::move(a_data)}
{
  // This had better not be emtpy.
  assert(m_data != nullptr);
}

sak::Entity_Handle::~Entity_Handle() = default;

sak::Entity_Handle::Entity_Handle(Entity_Handle const& /*a_other*/) = default;

sak::Entity_Handle& sak::Entity_Handle::operator=(Entity_Handle const& /*a_other*/) = default;

sak::Entity_Handle::Entity_Handle(Entity_Handle && /*a_other*/) = default;

sak::Entity_Handle& sak::Entity_Handle::operator=(Entity_Handle && /*a_other*/) = default;

// Modify
//============================================================
// Make this Handle into a null Handle.
void sak::Entity_Handle::reset() noexcept
{
  m_data.reset();
  // This had better be emtpy.
  assert(m_data == nullptr);
}

// Swap the Handle data.
void sak::Entity_Handle::swap(Entity_Handle& a_other) noexcept
{
  std::swap(m_data, a_other.m_data);
}

// Observe
//============================================================
// Get the Handle's id value. If the Handle is a null Handle this is a
// null id value.
sak::Entity_ID sak::Entity_Handle::id() const noexcept
{
  if (m_data != nullptr)
  {
    return m_data->id();
  }
  else
  {
    return make_null_entity_id();
  }
}

// How many times is this object referenced? If the Handle is a null
// Handle then this returns 0.
long sak::Entity_Handle::use_count() const noexcept
{
  return m_data.use_count();
}

// Access the underlying pointer. If the Handle is a null Handle then
// this returns nullptr.
sak::Entity* sak::Entity_Handle::get() const noexcept
{
  return m_data.get();
}

// Dereference the stored pointer. If the Handle is a null Handle then
// the behaviour is undefined.
sak::Entity& sak::Entity_Handle::operator*() const noexcept
{
  return *m_data;
}

// Dereference the stored pointer. If the Handle is a null Handle then
// this returns nullptr.
sak::Entity* sak::Entity_Handle::operator->() const noexcept
{
  return m_data.get();
}

// Member Operators
//============================================================
// Return true if the Handle is valid.
sak::Entity_Handle::operator bool() const noexcept
{
  return m_data != nullptr;
}

// Comparison Operators
//============================================================
// Handles are ordered by Enity_ID and nothing else.

bool sak::operator==(Entity_Handle const& a_lhs, Entity_Handle const& a_rhs) noexcept
{
  return a_lhs.id() == a_rhs.id();
}

bool sak::operator!=(Entity_Handle const& a_lhs, Entity_Handle const& a_rhs) noexcept
{
  return a_lhs.id() != a_rhs.id();
}

bool sak::operator<(Entity_Handle const& a_lhs, Entity_Handle const& a_rhs) noexcept
{
  return a_lhs.id() < a_rhs.id();
}

bool sak::operator>(Entity_Handle const& a_lhs, Entity_Handle const& a_rhs) noexcept
{
  return a_lhs.id() > a_rhs.id();
}

bool sak::operator<=(Entity_Handle const& a_lhs, Entity_Handle const& a_rhs) noexcept
{
  return a_lhs.id() <= a_rhs.id();
}

bool sak::operator>=(Entity_Handle const& a_lhs, Entity_Handle const& a_rhs) noexcept
{
  return a_lhs.id() >= a_rhs.id();
}


// Non-member Interface
//============================================================
void sak::swap(Entity_Handle& a_lhs, Entity_Handle& a_rhs) noexcept
{
  a_lhs.swap(a_rhs);
}

// Excplicit state identifiers. A Handle is null if it has a null id, which
// means it is not being used to reference data.
bool sak::is_null(Entity_Handle const& a_handle) noexcept
{
  return !static_cast<bool>(a_handle);
}

bool sak::not_null(Entity_Handle const& a_handle) noexcept
{
  return static_cast<bool>(a_handle);
}

// Get the id of a handle. If the handle is null then the id is a null handle.
sak::Entity_ID sak::id(Entity_Handle const& a_handle) noexcept
{
  return a_handle.id();
}
