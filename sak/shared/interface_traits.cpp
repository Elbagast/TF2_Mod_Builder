#include "interface_traits.hpp"
#include "interface.hpp"
#include <cassert>

sak::file::interface_traits::interface_traits():
    m_project{nullptr}
{}

sak::file::interface_traits::interface_traits(Project* a_project):
    m_project{a_project}
{}

sak::file::interface_traits::interface_type sak::file::interface_traits::get(extended_handle const& a_handle, handle& a_data)
{
    assert(m_project != nullptr);
    return interface_type(a_handle, a_data, m_project);
}

sak::file::interface_traits::const_interface_type sak::file::interface_traits::cget(extended_handle const& a_handle, handle const& a_data) const
{
    assert(m_project != nullptr);
    return const_interface_type(a_handle, a_data);
}
