#include "file_interface_traits.h"
#include "file_interface.h"
#include <cassert>

sak::File_Interface_Traits::File_Interface_Traits():
    m_project{nullptr}
{}

sak::File_Interface_Traits::File_Interface_Traits(Project* a_project):
    m_project{a_project}
{}

sak::File_Interface_Traits::interface_type sak::File_Interface_Traits::get(handle_type const& a_handle, basic_handle_type& a_data)
{
    assert(m_project != nullptr);
    return interface_type(a_handle, a_data, m_project);
}

sak::File_Interface_Traits::const_interface_type sak::File_Interface_Traits::cget(handle_type const& a_handle, basic_handle_type const& a_data) const
{
    assert(m_project != nullptr);
    return const_interface_type(a_handle, a_data);
}
