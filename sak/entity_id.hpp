#ifndef SAK_ENTITY_ID_HPP
#define SAK_ENTITY_ID_HPP

#ifndef SAK_ENTITY_ID_FWD_HPP
#include "entity_id_fwd.hpp"
#endif

#ifndef INCLUDE_STD_LIMITS
#define INCLUDE_STD_LIMITS
#include <limits>
#endif

#ifndef INCLUDE_STD_UTILITY
#define INCLUDE_STD_UTILITY
#include <utility>
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Entity_ID
  //---------------------------------------------------------------------------
  // Since the id is just an integral value, we use an enum class to make a new
  // integral type rather than a full class. An id with a value of 0 is a null
  // id, and does not represent an entity.

  enum class Entity_ID : Entity_ID_Value_Type
  {
    Null = 0u,
    First_Valid = 1u,
    Last_Valid = std::numeric_limits<Entity_ID_Value_Type>::max()
  };

  // Comparison Operators
  //============================================================
  constexpr bool operator==(Entity_ID a_lhs, Entity_ID a_rhs) noexcept;
  constexpr bool operator!=(Entity_ID a_lhs, Entity_ID a_rhs) noexcept;

  constexpr bool operator<(Entity_ID a_lhs, Entity_ID a_rhs) noexcept;
  constexpr bool operator>(Entity_ID a_lhs, Entity_ID a_rhs) noexcept;
  constexpr bool operator<=(Entity_ID a_lhs, Entity_ID a_rhs) noexcept;
  constexpr bool operator>=(Entity_ID a_lhs, Entity_ID a_rhs) noexcept;

  // Interface
  //============================================================
  // Make an Entity_ID using the supplied value. If the value is zero, then the
  // resulting Entity_ID is a null id.
  constexpr Entity_ID make_entity_id(Entity_ID_Value_Type a_value) noexcept;

  // Explicitly make an Entity_ID that has a value of zero, a null id.
  constexpr Entity_ID make_null_entity_id() noexcept;

  // Get the underlying value of an Entity_ID.
  constexpr Entity_ID_Value_Type entity_id_value(Entity_ID a_id) noexcept;

  // Is the supplied Entity_ID a null id?;
  constexpr bool is_null(Entity_ID a_id) noexcept;

  // Is the supplied Entity_ID not a null id?
  constexpr bool not_null(Entity_ID a_id) noexcept;

  // Make the supplied Entity_ID into a null id.
  constexpr void reset(Entity_ID& a_id) noexcept;

  // Swap two Entity_IDs
  void swap(Entity_ID& a_lhs, Entity_ID& a_rhs) noexcept;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Entity_ID
//---------------------------------------------------------------------------

// Comparison Operators
//============================================================
constexpr bool sak::operator==(Entity_ID a_lhs, Entity_ID a_rhs) noexcept
{
  return entity_id_value(a_lhs) == entity_id_value(a_rhs);
}

constexpr bool sak::operator!=(Entity_ID a_lhs, Entity_ID a_rhs) noexcept
{
  return entity_id_value(a_lhs) != entity_id_value(a_rhs);
}

constexpr bool sak::operator<(Entity_ID a_lhs, Entity_ID a_rhs) noexcept
{
  return entity_id_value(a_lhs) < entity_id_value(a_rhs);
}

constexpr bool sak::operator>(Entity_ID a_lhs, Entity_ID a_rhs) noexcept
{
  return entity_id_value(a_lhs) > entity_id_value(a_rhs);
}

constexpr bool sak::operator<=(Entity_ID a_lhs, Entity_ID a_rhs) noexcept
{
  return entity_id_value(a_lhs) <= entity_id_value(a_rhs);
}

constexpr bool sak::operator>=(Entity_ID a_lhs, Entity_ID a_rhs) noexcept
{
  return entity_id_value(a_lhs) >= entity_id_value(a_rhs);
}

// Interface
//============================================================
// Make an Entity_ID using the supplied value. If the value is zero, then the
// resulting Entity_ID is a null id.
constexpr sak::Entity_ID sak::make_entity_id(Entity_ID_Value_Type a_value) noexcept
{
  return static_cast<Entity_ID>(a_value);
}

// Explicitly make an Entity_ID that has a value of zero, a null id.
constexpr sak::Entity_ID sak::make_null_entity_id() noexcept
{
  return Entity_ID{Entity_ID::Null};
}

// Get the underlying value of an Entity_ID.
constexpr sak::Entity_ID_Value_Type sak::entity_id_value(Entity_ID a_id) noexcept
{
  return static_cast<Entity_ID_Value_Type>(a_id);
}

// Is the supplied Entity_ID a null id?
constexpr bool sak::is_null(Entity_ID a_id) noexcept
{
  return a_id == Entity_ID::Null;
}

// Is the supplied Entity_ID not a null id?
constexpr bool sak::not_null(Entity_ID a_id) noexcept
{
  return a_id != Entity_ID::Null;
}

// Make the supplied Entity_ID into a null id.
constexpr void sak::reset(Entity_ID& a_id) noexcept
{
  a_id = Entity_ID::Null;
}

// Swap two Entity_IDs
inline void sak::swap(Entity_ID& a_lhs, Entity_ID& a_rhs) noexcept
{
  std::swap(a_lhs, a_rhs);
}

#endif // SAK_ENTITY_ID_HPP
