#ifndef SAK_SHARED_INTERFACE_HPP
#define SAK_SHARED_INTERFACE_HPP

#include "fwd/interface.hpp"
#include "object.hpp"
#include "command.hpp"
#include "manager.hpp"
#include "extended_manager.hpp"
#include <QString>

namespace sak
{
  class Project;

  namespace shared
  {
    //---------------------------------------------------------------------------
    // shared::interface
    //---------------------------------------------------------------------------
    template <typename T, typename...Ms>
    class interface<object<T,Ms...>>
    {
    public:
      using object_type = object<T,Ms...>;

      using handle_type = handle<object_type>;
      using extended_handle_type = extended_handle<object_type>;

      template <std::size_t Index>
      class member_interface
      {
      public:
        using member_type = mf::object_member_t<object_type, Index>;
        using value_type = typename member_type::value_type;

        member_interface(extended_handle_type const& a_ehandle, handle_type& a_handle, Project* a_project):
          m_ehandle{a_ehandle},
          m_handle{a_handle},
          m_project{a_project}
        {}

        void set(value_type const& a_value)
        {
          // If it is the same as the name we already have, we don't bother making a change.
          if (a_value == cget())
          {
              return;
          }
          value_type l_value{a_value};
          fixup_value<Index>(l_value);

          m_project->emplace_execute(make_command_assign<object_type, Index>(m_project, m_ehandle, l_value));
        }

        value_type const& cget() const
        {
          return m_handle.cget().cat<I>().cget();
        }

        private:
          extended_handle_type const& m_ehandle;
          handle_type& m_handle;
          Project* m_project;

        template <std::size_t I2>
        void fixup_value(value_type& a_value)
        {
          return a_value;
        }

        template <>
        void fixup_value<0>(value_type& a_value)
        {
          // We must make sure the name does not already exist among the other names.
          auto l_names = m_project->get_all_file_names();
          // Get rid of the name of this one, since it is going to change.
          auto l_old_name_found = std::find(l_names.cbegin(), l_names.cend(), m_handle.cget().cat<0>().cget());
          l_names.erase(l_old_name_found);

          QString l_final_name{a_name};
          uniqueify_name(l_final_name, l_names);
        }
      };

      interface(extended_handle_type const& a_ehandle, handle_type& a_handle, Project* a_project):
        m_ehandle{a_ehandle},
        m_handle{a_handle},
        m_project{a_project}
      {}

      template <std::size_t I>
      member_interface<I> at()
      {
        return member_interface<I>(m_ehandle, m_handle, m_project);
      }

      template <std::size_t I>
      decltype(auto) cat() const
      {
        return m_handle.cget().cat<I>();
      }

    private:
      extended_handle_type const& m_ehandle;
      handle_type& m_handle;
      Project* m_project;
    };


    //---------------------------------------------------------------------------
    // shared::const_interface
    //---------------------------------------------------------------------------
     template <typename T, typename...Ms>
    class const_interface<object<T,Ms...>>
    {
    public:
      using object_type = object<T,Ms...>;

      using handle_type = handle<object_type>;
      using extended_handle_type = extended_handle<object_type>;

      const_interface(extended_handle_type const& a_ehandle, handle_type const& a_handle)://, Project* a_project):
        m_ehandle{a_ehandle},
        m_handle{a_handle}//,
        //m_project{a_project}
      {}

      template <std::size_t I>
      decltype(auto) cat() const
      {
        return m_handle.cget().cat<I>();
      }

    private:
      extended_handle_type const& m_ehandle;
      handle_type const& m_handle;
      //Project* m_project;
    };
  }
}

#endif // SAK_SHARED_INTERFACE_HPP
