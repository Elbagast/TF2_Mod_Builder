#ifndef SAK_HANDLE_HPP
#define SAK_HANDLE_HPP

#ifndef SAK_HANDLE_FWD_HPP
#include "handle_fwd.hpp"
#endif

#ifndef SAK_DATA_FWD_HPP
#include "data_fwd.hpp"
#endif

#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Handle<T_Class_Def>
  //---------------------------------------------------------------------------
  // So it turns of the seperated out Handle class does things we don't need.
  // We just want to associate a single object with a single ID value that gets
  // reference counted. This means a Handle is just a shared_ptr with an ID.

  // Could do all sorts of buggery with an id type as a template varaible but
  // we don't need to so don't bother.

  // Need to include section_data.hpp to actually use the data...

  template <typename T_Class_Def>
  class Handle
  {
  public:
    // Typedefs
    //============================================================
    using Element_Type = Data<T_Class_Def>;
    using ID_Type = std::size_t;

    // Special 6
    //============================================================
    Handle();
    Handle(std::shared_ptr<Element_Type>&& a_data, ID_Type a_id);
    ~Handle();

    Handle(Handle const& a_other);
    Handle& operator=(Handle const& a_other);

    Handle(Handle && a_other);
    Handle& operator=(Handle && a_other);

    // Modify
    //============================================================
    // Make this Handle into a null Handle.
    void reset() noexcept;

    // Swap the Handle data.
    void swap(Handle& a_other) noexcept;

    // Observe
    //============================================================
    // Get the Handle's id value. If the Handle is a null Handle this is a
    // null id value.
    ID_Type id() const noexcept;

    // How many times is this object referenced? If the Handle is a null
    // Handle then this returns 0.
    long use_count() const noexcept;

    // Access the underlying pointer. If the Handle is a null Handle then
    // this returns nullptr.
    Element_Type* get() const noexcept;

    // Dereference the stored pointer. If the Handle is a null Handle then
    // the behaviour is undefined.
    Element_Type& operator*() const noexcept;

    // Dereference the stored pointer. If the Handle is a null Handle then
    // this returns nullptr.
    Element_Type* operator->() const noexcept;

    // Member Operators
    //============================================================
    // Return true if the Handle is valid.
    explicit operator bool() const noexcept;

    // Compare
    bool operator==(Handle const& a_other) const noexcept;
    bool operator<(Handle const& a_other) const noexcept;

  private:
    // Data Members
    //============================================================
    std::shared_ptr<Element_Type> m_data;
    ID_Type m_id;
  };

  // Comparison Operators
  //============================================================
  //template <typename T>
  //bool operator==(Handle<T> const& a_lhs, Handle<T> const& a_rhs) noexcept;
  template <typename T>
  bool operator!=(Handle<T> const& a_lhs, Handle<T> const& a_rhs) noexcept;

  //template <typename T>
  //bool operator<(Handle<T> const& a_lhs, Handle<T> const& a_rhs) noexcept;
  template <typename T>
  bool operator>(Handle<T> const& a_lhs, Handle<T> const& a_rhs) noexcept;
  template <typename T>
  bool operator<=(Handle<T> const& a_lhs, Handle<T> const& a_rhs) noexcept;
  template <typename T>
  bool operator>=(Handle<T> const& a_lhs, Handle<T> const& a_rhs) noexcept;

  // Non-member Interface
  //============================================================
  template <typename T>
  void swap(Handle<T>& a_lhs, Handle<T>& a_rhs) noexcept;

  // Excplicit state identifiers. A Handle is null if it has a null id, which
  // means it is not being used to reference data.
  template <typename T>
  bool is_null(Handle<T> const& a_Handle) noexcept;

  template <typename T>
  bool not_null(Handle<T> const& a_Handle) noexcept;

} // namespace sak

// Comparison Operators
//============================================================
template <typename T>
bool sak::operator!=(Handle<T> const& a_lhs, Handle<T> const& a_rhs) noexcept
{
  return std::rel_ops::operator !=(a_lhs, a_rhs);
}

template <typename T>
bool sak::operator>(Handle<T> const& a_lhs, Handle<T> const& a_rhs) noexcept
{
  return std::rel_ops::operator >(a_lhs, a_rhs);
}
template <typename T>
bool sak::operator<=(Handle<T> const& a_lhs, Handle<T> const& a_rhs) noexcept
{
  return std::rel_ops::operator <=(a_lhs, a_rhs);
}

template <typename T>
bool sak::operator>=(Handle<T> const& a_lhs, Handle<T> const& a_rhs) noexcept
{
  return std::rel_ops::operator >=(a_lhs, a_rhs);
}


// Non-member Interface
//============================================================
template <typename T>
void sak::swap(Handle<T>& a_lhs, Handle<T>& a_rhs) noexcept
{
  a_lhs.swap(a_rhs);
}

// Excplicit state identifiers. A Handle is null if it has a null id, which
// means it is not being used to reference data.
template <typename T>
bool sak::is_null(Handle<T> const& a_handle) noexcept
{
  return !static_cast<bool>(a_handle);
}

template <typename T>
bool sak::not_null(Handle<T> const& a_handle) noexcept
{
  return static_cast<bool>(a_handle);
}

#endif // SAK_HANDLE_HPP
