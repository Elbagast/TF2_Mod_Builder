#ifndef SAK_SHARED_COMMAND_HPP
#define SAK_SHARED_COMMAND_HPP

#include "fwd/command.hpp"
#include "object.hpp"
#include "manager.hpp"
#include "extended_manager.hpp"
#include "../project.hpp"
#include <generic/command.hpp>

namespace sak
{
  namespace shared
  {
    //---------------------------------------------------------------------------
    // command_assign<T,Index>
    //---------------------------------------------------------------------------
    // Class that derives from generic::command that wraps the assignement of a
    // member's data.

    template <std::size_t Index, typename T, typename...Ms>
    class command_assign<object<T,Ms...>,Index> :
        public generic::abstract::Command
    {
    public:
      using inherited_type = generic::abstract::Command;
      using object_type = object<T,Ms...>;
      using member_type = mf::object_member_t<object_type,Index>;
      using value_type = typename member_type::value_type;

      using extended_handle_type = extended_handle<object_type>;

      command_assign(Project* a_project, extended_handle_type const& a_ehandle, value_type const& a_value):
        inherited_type(),
        m_project{a_project},
        m_ehandle{a_ehandle},
        m_new_value{a_value},
        // get the basic handle, then get the data held, then get the member, then get the value
        m_old_value{m_ehandle.cget_handle().cget().cat<Index>().cget()}
      {}

      ~command_assign() override = default;
    protected:
        void do_execute() override final
        {
          // open the handle, then the common data, then set that part of it.
          m_ehandle.get_handle().get().at<Index>().get() = m_new_value;
          m_project->get_signalbox()->changed_at(m_ehandle,Index); // outbound signal to project
        }
        void do_unexecute() override final
        {
          // open the handle, then the common data, then set that part of it.
          m_ehandle.get_handle().get().at<Index>().get() = m_old_value;
          m_project->get_signalbox()->changed_at(m_ehandle,Index); // outbound signal to project
        }
    private:
        Project* m_project;
        extended_handle_type m_ehandle;
        value_type m_new_value;
        value_type m_old_value;
    };

    template <typename T, std::size_t Index>
    decltype(auto) make_command_assign(Project* a_project, typename command_assign<T,Index>::extended_handle_type const& a_ehandle, typename command_assign<T,Index>::value_type const& a_value)
    {
      return std::unique_ptr<typename command_assign<T,Index>::inherited_type>(std::make_unique<command_assign<T,Index>>(a_project, a_ehandle, a_value).release());
    }


    //---------------------------------------------------------------------------
    // command_added<T>
    //---------------------------------------------------------------------------
    // Class that derives from generic::command that wraps the addition of an
    // object to the project.

    template <typename T, typename...Ms>
    class command_added<object<T,Ms...>> :
        public generic::abstract::Command
    {
    public:
      using inherited_type = generic::abstract::Command;
      using object_type = object<T,Ms...>;
      using extended_handle_type = extended_handle<object_type>;

      command_added(Project* a_project, extended_handle_type const& a_ehandle):
        inherited_type(),
        m_project{a_project},
        m_ehandle{a_ehandle}
      {}

      command_added(Project* a_project, extended_handle_type && a_ehandle):
        inherited_type(),
        m_project{a_project},
        m_ehandle{std::move(a_ehandle)}
      {}

      ~command_added() override = default;
    protected:
        void do_execute() override final
        {
          m_project->get_signalbox()->added(m_ehandle); // outbound signal to project
        }
        void do_unexecute() override final
        {
          m_project->get_signalbox()->removed(m_ehandle); // outbound signal to project
        }
    private:
        Project* m_project;
        extended_handle_type m_ehandle;
    };

    template <typename T>
    decltype(auto) make_command_added(Project* a_project, extended_handle<T> const& a_ehandle)
    {
      return std::unique_ptr<typename command_added<T>::inherited_type>(std::make_unique<command_added<T>>(a_project,a_ehandle).release());
    }

    template <typename T>
    decltype(auto) make_command_added(Project* a_project, extended_handle<T> && a_ehandle)
    {
      return std::unique_ptr<typename command_added<T>::inherited_type>(std::make_unique<command_added<T>>(a_project,std::move(a_ehandle)).release());
    }


    //---------------------------------------------------------------------------
    // command_removed<T>
    //---------------------------------------------------------------------------
    // Class that derives from generic::command that wraps the addition of an
    // object to the project.

    template <typename T, typename...Ms>
    class command_removed<object<T,Ms...>> :
        public generic::abstract::Command
    {
    public:
      using inherited_type = generic::abstract::Command;
      using object_type = object<T,Ms...>;
      using extended_handle_type = extended_handle<object_type>;

      command_removed(Project* a_project, extended_handle_type const& a_ehandle):
        inherited_type(),
        m_project{a_project},
        m_ehandle{a_ehandle}
      {}

      command_removed(Project* a_project, extended_handle_type && a_ehandle):
        inherited_type(),
        m_project{a_project},
        m_ehandle{std::move(a_ehandle)}
      {}

      ~command_removed() override = default;
    protected:
        void do_execute() override final
        {
          m_project->get_signalbox()->removed(m_ehandle); // outbound signal to project
        }
        void do_unexecute() override final
        {
          m_project->get_signalbox()->added(m_ehandle); // outbound signal to project
        }
    private:
        Project* m_project;
        extended_handle_type m_ehandle;
    };

    template <typename T>
    decltype(auto) make_command_removed(Project* a_project, extended_handle<T> const& a_ehandle)
    {
      return std::unique_ptr<typename command_removed<T>::inherited_type>(std::make_unique<command_removed<T>>(a_project,a_ehandle).release());
    }

    template <typename T>
    decltype(auto) make_command_removed(extended_handle<T> && a_ehandle)
    {
      return std::unique_ptr<typename command_removed<T>::inherited_type>(Project* a_project, std::make_unique<command_removed<T>>(a_project,std::move(a_ehandle)).release());
    }

  } // namespace shared
} // namespace sak


#endif // SAK_SHARED_COMMAND_HPP
