#include "interface_traits.hpp"

#include "manager.hpp"
#include "extended_manager.hpp"
#include "interface.hpp"

//---------------------------------------------------------------------------
// shared::interface_traits<T>
//---------------------------------------------------------------------------
// Special 6
//============================================================
template <typename T>
sak::shared::interface_traits<T>::interface_traits():
    m_project{nullptr}
{}

template <typename T>
sak::shared::interface_traits<T>::interface_traits(project::object* a_project):
    m_project{a_project}
{}

// Public Interface
//============================================================
template <typename T>
typename sak::shared::interface_traits<T>::interface_type sak::shared::interface_traits<T>::get(extended_handle_type& a_handle, handle_type& a_data)
{
    assert(m_project != nullptr);
    return interface_type(*m_project, a_handle);
}
/*
template <typename T>
typename sak::shared::interface_traits<T>::const_interface_type sak::shared::interface_traits<T>::cget(extended_handle_type const& a_handle, handle_type const& a_data) const
{
    assert(m_project != nullptr);
    return const_interface_type(a_handle, a_data);
}
*/

template <typename T>
typename sak::shared::interface_traits<T>::const_interface_type sak::shared::interface_traits<T>::cget(extended_handle_type const& a_handle, handle_type const& a_data) const
{
    assert(m_project != nullptr);
    return a_data.cget();
    //return const_interface_type(a_handle, a_data);
}


// Forced Instantiations
//============================================================
template sak::file::interface_traits;
template sak::texture::interface_traits;
