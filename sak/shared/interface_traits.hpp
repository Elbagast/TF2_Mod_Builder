#ifndef SAK_SHARED_INTERFACE_TRAITS_HPP
#define SAK_SHARED_INTERFACE_TRAITS_HPP

#include "fwd/object.hpp"
#include "fwd/interface_traits.hpp"
#include "fwd/interface.hpp"
#include "fwd/manager.hpp"
#include "fwd/extended_manager.hpp"
#include <sak/project/fwd/object.hpp>

namespace sak
{
  namespace shared
  {
    //---------------------------------------------------------------------------
    // shared::interface_traits<T>
    //---------------------------------------------------------------------------

    template <typename T>
    class interface_traits
    {
    public:
      // Typedefs
      //============================================================
      using object_type = T;
      using handle_type = handle<object_type>;
      using extended_handle_type = extended_handle<object_type>;
      using interface_type = interface<object_type>;
      //using const_interface_type = const_interface<object_type>;
      using const_interface_type = object_type const&;

      // Special 6
      //============================================================
      interface_traits();
      explicit interface_traits(project::object* a_project);

      // Public Interface
      //============================================================
      interface_type get(extended_handle_type& a_handle, handle_type& a_data);
      const_interface_type cget(extended_handle_type const& a_handle, handle_type const& a_data) const;
    private:
      // Data Members
      //============================================================
      project::object* m_project;
    };
  }
}

#endif // SAK_SHARED_INTERFACE_TRAITS_HPP
