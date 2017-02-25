#ifndef SAK_FILE_INTERFACE_TRAITS_HPP
#define SAK_FILE_INTERFACE_TRAITS_HPP

#include "fwd/interface_traits.hpp"
#include "fwd/manager.hpp"
#include "fwd/extended_manager.hpp"
#include "fwd/interface.hpp"

namespace sak
{
  class Project;

  namespace file
  {
    //---------------------------------------------------------------------------
    // file::interface_traits
    //---------------------------------------------------------------------------
    class interface_traits
    {
    public:
        using interface_type = interface;
        using const_interface_type = const_interface;

        interface_traits();
        explicit interface_traits(Project* a_project);

        interface_type get(extended_handle const& a_handle, handle& a_data);
        const_interface_type cget(extended_handle const& a_handle, handle const& a_data) const;
    private:
        Project* m_project;
    };
  }
}

#endif // SAK_FILE_INTERFACE_TRAITS_HPP
