#include "handle.hpp"

#include "data_definitions.hpp"
#include "class_definitions.hpp"
#include "data.hpp"

#include <cassert>

//---------------------------------------------------------------------------
// Handle<T_Class_Def>
//---------------------------------------------------------------------------

// Construct a null Handle. It does not reference any data and has no
// associated manager. This can only be changed by copy or move #
// assignment to this.
template <typename T>
sak::Handle<T>::Handle():
  m_data{},
  m_id{0}
{
  // This had better be emtpy.
  assert(m_data == nullptr);
  assert(!m_id);
}

template <typename T>
sak::Handle<T>::Handle(std::shared_ptr<Element_Type>&& a_data, std::size_t a_id_value):
  Handle{std::move(a_data),ID_Type{a_id_value}}
{
}

template <typename T>
sak::Handle<T>::Handle(std::shared_ptr<Element_Type>&& a_data, ID_Type a_id):
  m_data{std::move(a_data)},
  m_id{a_id}
{
  // Shouldn't be making a handle with empty data. You bad person.
  assert(m_data != nullptr);
  assert(m_id);
}

template <typename T>
sak::Handle<T>::~Handle() = default;

template <typename T>
sak::Handle<T>::Handle(Handle const& /*a_other*/) = default;

template <typename T>
typename sak::Handle<T>& sak::Handle<T>::operator=(Handle const& /*a_other*/) = default;

template <typename T>
sak::Handle<T>::Handle(Handle && a_other):
  m_data{std::move(a_other.m_data)},
  m_id{std::move(a_other.m_id)}
{
  a_other.m_id.reset();

  // Other had better be emtpy.
  assert(a_other.m_data == nullptr);
  assert(!(a_other.m_id));
}

template <typename T>
typename sak::Handle<T>& sak::Handle<T>::operator=(Handle && a_other)
{
  this->m_data = std::move(a_other.m_data);
  this->m_id = a_other.m_id;
  a_other.m_id.reset();

  // Other had better be emtpy.
  assert(a_other.m_data == nullptr);
  assert(!(a_other.m_id));

  return *this;
}


// Modify
//============================================================
// Make this Handle into a null Handle.
template <typename T>
void sak::Handle<T>::reset() noexcept
{
  m_data.reset();
  m_id.reset();
  // This had better be emtpy.
  assert(m_data == nullptr);
  assert(!m_id);
}

// Swap the Handle data.
template <typename T>
void sak::Handle<T>::swap(Handle<T>& a_other) noexcept
{
  std::swap(m_data, a_other.m_data);
  sak::swap(m_id, a_other.m_id);
}

// Observe
//============================================================
// Get the Handle's id value. If the Handle is a null Handle this is a
// null id value.
template <typename T>
typename sak::Handle<T>::ID_Type sak::Handle<T>::id() const noexcept
{
  return m_id;
}

// How many times is this object referenced? If the Handle is a null
// Handle then this returns 0.
template <typename T>
long sak::Handle<T>::use_count() const noexcept
{
  return m_data.use_count();
}

// Access the underlying pointer. If the Handle is a null Handle then
// this returns nullptr.
template <typename T>
typename sak::Handle<T>::Element_Type* sak::Handle<T>::get() const noexcept
{
  return m_data.get();
}

// Dereference the stored pointer. If the Handle is a null Handle then
// the behaviour is undefined.
template <typename T>
typename sak::Handle<T>::Element_Type& sak::Handle<T>::operator*() const noexcept
{
  return *m_data;
}

// Dereference the stored pointer. If the Handle is a null Handle then
// this returns nullptr.
template <typename T>
typename sak::Handle<T>::Element_Type* sak::Handle<T>::operator->() const noexcept
{
  return m_data.get();
}

// Member Operators
//============================================================
// Return true if the Handle is valid.
template <typename T>
sak::Handle<T>::operator bool() const noexcept
{
  return m_id && m_data != nullptr;
}

// Compare
template <typename T>
bool sak::Handle<T>::operator==(Handle const& a_other) const noexcept
{
  // We only compare the ids. This isn't going to detect handles
  // made by different factories.
  return m_id == a_other.m_id;
  //return m_id == a_other.m_id && m_data == a_other.m_data;
}

template <typename T>
bool sak::Handle<T>::operator<(Handle const& a_other) const noexcept
{
  // We only compare the ids. This isn't going to detect handles
  // made by different factories.
  return m_id < a_other.m_id;
  //return m_id < a_other.m_id && m_data < a_other.m_data;
}

// Forced Instantiations
//============================================================
template class sak::Handle<sak::File_Definition>;
template class sak::Handle<sak::Texture_Definition>;
template class sak::Handle<sak::Material_Definition>;
