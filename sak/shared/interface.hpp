#ifndef SAK_SHARED_INTERFACE_HPP
#define SAK_SHARED_INTERFACE_HPP

#include "fwd/interface.hpp"
#include "object.hpp"
#include "fwd/manager.hpp"
#include "fwd/extended_manager.hpp"

namespace sak
{
  class Project;

  namespace shared
  {
    namespace internal
    {
      //---------------------------------------------------------------------------
      // shared::internal::fixup_value<T,I>
      //---------------------------------------------------------------------------
      // Seperating out the call to constrain the name so we can hide the workings.

      template <typename T, std::size_t Index>
      struct do_set
      {
        using object_type = T;
        using extended_handle_type = extended_handle<object_type>;
        using member_type = mf::object_member_t<object_type, Index>;
        using value_type = typename member_type::value_type;

        void operator()(value_type const& a_value, extended_handle_type const& a_ehandle, Project* a_project) const;
      };

      template <typename T>
      struct do_set<T,0>
      {
        using object_type = T;
        using extended_handle_type = extended_handle<object_type>;
        using member_type = mf::object_member_t<object_type, 0>;
        using value_type = typename member_type::value_type;

        void operator()(value_type const& a_value, extended_handle_type const& a_ehandle, Project* a_project) const;
      };
    }

    // since these classes only use references and pointers, we are fine with them being exposed. The
    // bit that does the work is hidden.

    //---------------------------------------------------------------------------
    // shared::member_interface<T>
    //---------------------------------------------------------------------------
    template <typename T, std::size_t Index>
    class member_interface
    {
    public:
      using object_type = T;

      using handle_type = handle<object_type>;
      using extended_handle_type = extended_handle<object_type>;
      using member_type = mf::object_member_t<object_type, Index>;
      using value_type = typename member_type::value_type;

      member_interface(extended_handle_type& a_ehandle, Project* a_project):
        m_ehandle{a_ehandle},
        m_project{a_project}
      {}

      void set(value_type const& a_value)
      {
        internal::do_set<object_type, Index>()(a_value, m_ehandle, m_project);
      }

      private:
        extended_handle_type& m_ehandle;
        Project* m_project;
    };

    //---------------------------------------------------------------------------
    // shared::interface<T>
    //---------------------------------------------------------------------------
    template <typename T>
    class interface
    {
    public:
      using object_type = T;

      using handle_type = handle<object_type>;
      using extended_handle_type = extended_handle<object_type>;

      interface(extended_handle_type& a_ehandle, handle_type& a_handle, Project* a_project):
        m_ehandle{a_ehandle},
        m_project{a_project}
      {}

      template <std::size_t I>
      member_interface<object_type, I> at()
      {
        return member_interface<object_type,I>(m_ehandle, m_project);
      }

    private:
      extended_handle_type& m_ehandle;
      Project* m_project;
    };
  }
}

#endif // SAK_SHARED_INTERFACE_HPP
