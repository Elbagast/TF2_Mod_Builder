#ifndef SAK_SHARED_INTERFACE_TRAITS_HPP
#define SAK_SHARED_INTERFACE_TRAITS_HPP

#include "fwd/object.hpp"
#include "fwd/interface_traits.hpp"
#include "manager.hpp"
#include "extended_manager.hpp"
#include "interface.hpp"

namespace sak
{
  class Project;

  namespace shared
  {
    //---------------------------------------------------------------------------
    // shared::interface_traits
    //---------------------------------------------------------------------------
    template <typename T, typename...Ms>
    class interface_traits<object<T,Ms...>>
    {
    public:
      using object_type = object<T,Ms...>;
      using interface_type = interface<object_type>;
      using const_interface_type = const_interface<object_type>;
      using handle_type = handle<object_type>;
      using extended_handle_type = extended_handle<object_type>;

      interface_traits():
        m_project{nullptr}
      {}
      explicit interface_traits(Project* a_project):
        m_project{a_project}
      {}

      interface_type get(extended_handle_type const& a_handle, handle_type& a_data)
      {
          assert(m_project != nullptr);
          return interface_type(a_handle, a_data, m_project);
      }
      const_interface_type cget(extended_handle_type const& a_handle, handle_type const& a_data) const
      {
          assert(m_project != nullptr);
          return const_interface_type(a_handle, a_data);
      }
    private:
      Project* m_project;
    };
  }
}
/*
template <typename T, typename...Ms>
sak::shared::interface_traits<object<T,Ms...>>::interface_traits():
    m_project{nullptr}
{}

template <typename T, typename...Ms>
sak::shared::interface_traits<object<T,Ms...>>::interface_traits(Project* a_project):
    m_project{a_project}
{}

template <typename T, typename...Ms>
typename sak::shared::interface_traits<object<T,Ms...>>::interface_type sak::shared::interface_traits<object<T,Ms...>>::get(extended_handle const& a_handle, handle& a_data)
{
    assert(m_project != nullptr);
    return interface_type(a_handle, a_data, m_project);
}

template <typename T, typename...Ms>
typename sak::shared::interface_traits<object<T,Ms...>>::const_interface_type sak::shared::interface_traits<object<T,Ms...>>::cget(extended_handle const& a_handle, handle const& a_data) const
{
    assert(m_project != nullptr);
    return const_interface_type(a_handle, a_data);
}
*/
#endif // SAK_SHARED_INTERFACE_TRAITS_HPP
