#ifndef SAK_SHARED_INTERFACE_HPP
#define SAK_SHARED_INTERFACE_HPP

#include "fwd/interface.hpp"
#include "object.hpp"
#include "fwd/manager.hpp"
#include "fwd/extended_manager.hpp"
#include <sak/project/fwd/object.hpp>
#include "project_access.hpp"

namespace sak
{
  class Project;

  namespace shared
  {
    // since these classes only use references and pointers, we are fine with them being exposed. The
    // bit that does the work is hidden.

    //---------------------------------------------------------------------------
    // shared::interface<T>
    //---------------------------------------------------------------------------
    template <typename T>
    class interface
    {
    public:
      using object_type = T;
      using member_value_variant = typename object_type::member_value_variant;

      using handle_type = handle<object_type>;
      using extended_handle_type = extended_handle<object_type>;

      interface(project::object& a_project, extended_handle_type& a_ehandle):
        m_ehandle{a_ehandle},
        m_project{a_project}
      {}

      template <std::size_t I>
      void set(typename mf::object_member_t<object_type, I>::value_type const& a_value)
      {
        project_access<object_type>::change_at(&m_project, m_ehandle, I, member_value_variant(a_value));
      }

    private:
      project::object& m_project;
      extended_handle_type& m_ehandle;
    };
  }
}

#endif // SAK_SHARED_INTERFACE_HPP
