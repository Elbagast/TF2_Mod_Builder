#include "handle_factory.hpp"

#include "handle.hpp"
#include "section_data.hpp"

#include <cassert>

//---------------------------------------------------------------------------
// Handle_Factory<T>
//---------------------------------------------------------------------------
// Object that makes Handle<T> by encapsulating the production of id values.

// Special 6
//============================================================
template <typename T>
sak::Handle_Factory<T>::Handle_Factory() noexcept:
  m_next_id{0}
{}
template <typename T>
sak::Handle_Factory<T>::~Handle_Factory() noexcept = default;


template <typename T>
sak::Handle_Factory<T>::Handle_Factory(Handle_Factory const& a_other) noexcept = default;

template <typename T>
sak::Handle_Factory<T>& sak::Handle_Factory<T>::operator=(Handle_Factory const& a_other) noexcept = default;


template <typename T>
sak::Handle_Factory<T>::Handle_Factory(Handle_Factory && a_other) noexcept = default;

template <typename T>
sak::Handle_Factory<T>& sak::Handle_Factory<T>::operator=(Handle_Factory && a_other) noexcept = default;

// Interface
//============================================================
// Explicitly make a null handle.
template <typename T>
sak::Handle<T> sak::Handle_Factory<T>::make_null_handle()
{
  return Handle<T>();
}

// Make a new handle with the supplied data. This data will be associated
// with the returned handle's id value until all handles referencing it
// are destroyed.
template <typename T>
sak::Handle<T> sak::Handle_Factory<T>::make_handle(std::shared_ptr<T>&& a_data)
{
  ++m_next_id;
  // Check if we ran out of ids.
  // Should probably throw an exception here.
  assert(m_next_id != 0);
  return Handle<T>(std::move(a_data), m_next_id);
}

// Explicit instantiations
//============================================================
template class sak::File_Handle_Factory;
template class sak::Texture_Handle_Factory;
