#ifndef SAK_ENTITY_HANDLE_HPP
#define SAK_ENTITY_HANDLE_HPP

// This Header's Forward Header
//============================================================
#ifndef SAK_ENTITY_HANDLE_FWD_HPP
#include "entity_handle_fwd.hpp"
#endif

// SAK Forwarding Headers
//============================================================
#ifndef SAK_ENTITY_FWD_HPP
#include "entity_fwd.hpp"
#endif

#ifndef SAK_ENTITY_ID_FWD_HPP
#include "../entity_id_fwd.hpp"
#endif

// Standard Headers
//============================================================
#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Entity_Handle
  //---------------------------------------------------------------------------
  // We want a reference counting system so we use the one in std::shared_ptr,
  // but this means we are stuck using single instance objects rather than
  // distributed objects. This also locks out certain std::shared_ptr functions
  // that don't make sense for our usage.

  class Entity_Handle
  {
  private:
    // Data Members
    //============================================================
    std::shared_ptr<Entity> m_data;

  public:
    // Special 6
    //============================================================
    Entity_Handle();
    explicit Entity_Handle(Entity&& a_entity);
    explicit Entity_Handle(std::shared_ptr<Entity>&& a_entity);
    ~Entity_Handle();

    Entity_Handle(Entity_Handle const& a_other);
    Entity_Handle& operator=(Entity_Handle const& a_other);

    Entity_Handle(Entity_Handle && a_other);
    Entity_Handle& operator=(Entity_Handle && a_other);

    // Modify
    //============================================================
    // Make this Handle into a null Handle.
    void reset() noexcept;

    // Swap the Handle data.
    void swap(Entity_Handle& a_other) noexcept;

    // Observe
    //============================================================
    // Get the Handle's id value. If the Handle is a null Handle this is a
    // null id value.
    Entity_ID id() const noexcept;

    // How many times is this object referenced? If the Handle is a null
    // Handle then this returns 0.
    long use_count() const noexcept;

    // Access the underlying pointer. If the Handle is a null Handle then
    // this returns nullptr.
    Entity* get() const noexcept;

    // Dereference the stored pointer. If the Handle is a null Handle then
    // the behaviour is undefined.
    Entity& operator*() const noexcept;

    // Dereference the stored pointer. If the Handle is a null Handle then
    // this returns nullptr.
    Entity* operator->() const noexcept;

    // Member Operators
    //============================================================
    // Return true if the Handle is not a null handle.
    explicit operator bool() const noexcept;
  };

  // Comparison Operators
  //============================================================
  // Handles are ordered by Enity_ID and nothing else.

  bool operator==(Entity_Handle const& a_lhs, Entity_Handle const& a_rhs) noexcept;
  bool operator!=(Entity_Handle const& a_lhs, Entity_Handle const& a_rhs) noexcept;

  bool operator<(Entity_Handle const& a_lhs, Entity_Handle const& a_rhs) noexcept;
  bool operator>(Entity_Handle const& a_lhs, Entity_Handle const& a_rhs) noexcept;
  bool operator<=(Entity_Handle const& a_lhs, Entity_Handle const& a_rhs) noexcept;
  bool operator>=(Entity_Handle const& a_lhs, Entity_Handle const& a_rhs) noexcept;

  // Non-member Interface
  //============================================================
  void swap(Entity_Handle& a_lhs, Entity_Handle& a_rhs) noexcept;

  // Explicit state identifiers. A Handle is null if it has a null id, which
  // means it is not being used to reference data.
  bool is_null(Entity_Handle const& a_handle) noexcept;

  bool not_null(Entity_Handle const& a_handle) noexcept;

  // Get the id of a handle. If the handle is null then the id is a null handle.
  Entity_ID id(Entity_Handle const& a_handle) noexcept;

} // namespace sak

//------------------------------------------------------------------------------------------------------------------------------------------------------

#endif // SAK_ENTITY_HANDLE_HPP
