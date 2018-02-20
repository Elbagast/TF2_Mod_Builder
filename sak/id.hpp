#ifndef SAK_ID_HPP
#define SAK_ID_HPP

#ifndef SAK_ID_FWD_HPP
#include "id_fwd.hpp"
#endif

#ifndef INCLUDE_STD_CSTDDEF
#define INCLUDE_STD_CSTDDEF
#include <cstddef>
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // ID<T_Class_Def>
  //---------------------------------------------------------------------------
  // Bind an id value to a type.

  template <typename T>
  class ID
  {
  public:
    // Typedefs
    //============================================================
    using Value_Type = std::size_t;

    // Special 6
    //============================================================
    ID() noexcept;
    ID(Value_Type a_value) noexcept;
    ~ID() noexcept;

    ID(ID const&) noexcept;
    ID& operator=(ID const&) noexcept;

    ID(ID &&) noexcept;
    ID& operator=(ID &&) noexcept;

    // Modify
    //============================================================
    // Make this id into a null id.
    void reset() noexcept;

    // Swap the id data.
    void swap(ID& a_other) noexcept;

    // Observe
    //============================================================
    // Get the underlying value.
    Value_Type value() const noexcept;

    // Member Operators
    //============================================================
    // Return true if the ID is not null.
    explicit operator bool() const noexcept;

    // Compare
    bool operator==(ID const& a_other) const noexcept;
    bool operator<(ID const& a_other) const noexcept;

  private:
    Value_Type m_value;
  };

  // Comparison Operators
  //============================================================
  //template <typename T>
  //bool operator==(ID<T> const& a_lhs, ID<T> const& a_rhs) noexcept;
  template <typename T>
  bool operator!=(ID<T> const& a_lhs, ID<T> const& a_rhs) noexcept;

  //template <typename T>
  //bool operator<(ID<T> const& a_lhs, ID<T> const& a_rhs) noexcept;
  template <typename T>
  bool operator>(ID<T> const& a_lhs, ID<T> const& a_rhs) noexcept;
  template <typename T>
  bool operator<=(ID<T> const& a_lhs, ID<T> const& a_rhs) noexcept;
  template <typename T>
  bool operator>=(ID<T> const& a_lhs, ID<T> const& a_rhs) noexcept;

  // Non-member Interface
  //============================================================
  template <typename T>
  void swap(ID<T>& a_lhs, ID<T>& a_rhs) noexcept;

  // Excplicit state identifiers. A Handle is null if it has a null id, which
  // means it is not being used to reference data.
  template <typename T>
  bool is_null(ID<T> const& a_id) noexcept;

  template <typename T>
  bool not_null(ID<T> const& a_id) noexcept;

} // namespace sak

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// ID<T_Class_Def>
//---------------------------------------------------------------------------
// Bind an id value to a type.

// Special 6
//============================================================
template <typename T>
sak::ID<T>::ID() noexcept:
  m_value{0}
{
}

template <typename T>
sak::ID<T>::ID(Value_Type a_value) noexcept:
  m_value{a_value}
{
}

template <typename T>
sak::ID<T>::~ID() noexcept = default;

template <typename T>
sak::ID<T>::ID(ID const&) noexcept = default;

template <typename T>
sak::ID<T>& sak::ID<T>::operator=(ID const&) noexcept = default;

template <typename T>
sak::ID<T>::ID(ID &&) noexcept = default;

template <typename T>
sak::ID<T>& sak::ID<T>::operator=(ID &&) noexcept = default;

// Modify
//============================================================
// Make this id into a null id.
template <typename T>
void sak::ID<T>::reset() noexcept
{
  m_value = 0;
}

// Swap the id data.
template <typename T>
void sak::ID<T>::swap(ID& a_other) noexcept
{
  std::swap(m_value, a_other.m_value);
}

// Observe
//============================================================
// Get the underlying value.
template <typename T>
typename sak::ID<T>::Value_Type sak::ID<T>::value() const noexcept
{
  return m_value;
}

// Member Operators
//============================================================
// Return true if the ID is not null.
template <typename T>
sak::ID<T>::operator bool() const noexcept
{
  return m_value != 0;
}

// Compare
template <typename T>
bool sak::ID<T>::operator==(ID const& a_other) const noexcept
{
  return m_value == a_other.m_value;
}

template <typename T>
bool sak::ID<T>::operator<(ID const& a_other) const noexcept
{
  return m_value < a_other.m_value;
}

// Comparison Operators
//============================================================
template <typename T>
bool sak::operator!=(ID<T> const& a_lhs, ID<T> const& a_rhs) noexcept
{
  return std::rel_ops::operator !=(a_lhs, a_rhs);
}

template <typename T>
bool sak::operator>(ID<T> const& a_lhs, ID<T> const& a_rhs) noexcept
{
  return std::rel_ops::operator >(a_lhs, a_rhs);
}
template <typename T>
bool sak::operator<=(ID<T> const& a_lhs, ID<T> const& a_rhs) noexcept
{
  return std::rel_ops::operator <=(a_lhs, a_rhs);
}

template <typename T>
bool sak::operator>=(ID<T> const& a_lhs, ID<T> const& a_rhs) noexcept
{
  return std::rel_ops::operator >=(a_lhs, a_rhs);
}

// Non-member Interface
//============================================================
template <typename T>
void sak::swap(ID<T>& a_lhs, ID<T>& a_rhs) noexcept
{
  a_lhs.swap(a_rhs);
}

// Excplicit state identifiers. A Handle is null if it has a null id, which
// means it is not being used to reference data.
template <typename T>
bool sak::is_null(ID<T> const& a_id) noexcept
{
  return !static_cast<bool>(a_id);
}

template <typename T>
bool sak::not_null(ID<T> const& a_id) noexcept
{
  return static_cast<bool>(a_id);
}

#endif // SAK_ID_HPP
