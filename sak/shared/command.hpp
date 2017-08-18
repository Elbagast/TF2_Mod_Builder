#ifndef SAK_SHARED_COMMAND_HPP
#define SAK_SHARED_COMMAND_HPP

#include "fwd/command.hpp"
#include <generic/command.hpp>
#include "object.hpp"
#include "manager.hpp"
#include "data_manager.hpp"
#include <generic/command.hpp>

namespace sak
{
  namespace shared
  {
    namespace abstract
    {
      //---------------------------------------------------------------------------
      // abstract::signalling_command<T>
      //---------------------------------------------------------------------------
      // Base class to contain shared typedefs and data members for commands on
      // objects via handles.

      template <typename T>
      class signalling_command :
          public command
      {
      public:
        // Typedefs
        //============================================================
        using inherited_type = command;
        using object_type = T;
        using data_manager_type = shared::data_manager<object_type>;
        using handle_type = handle<object_type>;

        // Special 6
        //============================================================
        signalling_command(data_manager_type& a_data_manager, handle_type const& a_handle):
          inherited_type(),
          m_data_manager{a_data_manager},
          m_handle{a_handle}
        {}

        signalling_command(data_manager_type& a_data_manager, handle_type && a_handle):
          inherited_type(),
          m_data_manager{a_data_manager},
          m_handle{std::move(a_handle)}
        {}

        ~signalling_command() override = default;

      protected:
        // Virtuals
        //============================================================
        void do_execute() override = 0;
        void do_unexecute() override = 0;

        // Data Members
        //============================================================
        data_manager_type& m_data_manager;
        handle_type m_handle;
      };
    }

    //---------------------------------------------------------------------------
    // command_assign<T,Index>
    //---------------------------------------------------------------------------
    // Class that derives from generic::command that wraps the assignement of a
    // member's data.

    template <typename T, std::size_t Index>
    class command_assign :
        public abstract::signalling_command<T>
    {
    public:
      // Typedefs
      //============================================================
      using inherited_type = abstract::signalling_command<T>;
      using member_type = mf::object_member_t<object_type,Index>;
      using value_type = typename member_type::value_type;

      // Special 6
      //============================================================
      command_assign(data_manager_type& a_data_manager, handle_type const& a_handle, value_type const& a_value):
        inherited_type(a_data_manager, a_handle),
        m_new_value{a_value},
        // get the basic handle, then get the data held, then get the member, then get the value
        m_old_value{m_handle.cget().cat<Index>().cget()}
      {}

      ~command_assign() override final = default;

    protected:
      // Virtuals
      //============================================================
      void do_execute() override final
      {
        // open the handle, then the common data, then set that part of it.
        m_handle.get().at<Index>().get() = m_new_value;
        m_data_manager.changed_at(m_handle, Index); // outbound signal.
        //dispatch_signals<object_type>::changed_at(m_project, m_handle, Index); // outbound signal.
      }
      void do_unexecute() override final
      {
        // open the handle, then the common data, then set that part of it.
        m_handle.get().at<Index>().get() = m_old_value;
        m_data_manager.changed_at(m_handle, Index); // outbound signal.
        //dispatch_signals<object_type>::changed_at(m_project, m_handle, Index); // outbound signal.
      }

    private:
      // Data Members
      //============================================================
      value_type m_new_value;
      value_type m_old_value;
    };

    template <typename T, std::size_t Index>
    decltype(auto) make_command_assign(data_manager<T>& a_data_manager, typename command_assign<T,Index>::handle_type const& a_handle, typename command_assign<T,Index>::value_type const& a_value)
    {
      return std::unique_ptr<abstract::command>(std::make_unique<command_assign<T,Index>>(a_data_manager, a_handle, a_value).release());
    }


    //---------------------------------------------------------------------------
    // command_added<T>
    //---------------------------------------------------------------------------
    // Class that derives from generic::command that wraps the addition of an
    // object to the project.

    template <typename T>
    class command_added :
        public abstract::signalling_command<T>
    {
    public:
      // Typedefs
      //============================================================
      using inherited_type = abstract::signalling_command<T>;

      // Special 6
      //============================================================
      command_added(data_manager_type& a_data_manager, handle_type const& a_handle):
        inherited_type(a_data_manager, a_handle)
      {}

      command_added(data_manager_type& a_data_manager, handle_type && a_handle):
        inherited_type(a_data_manager, std::move(a_handle))
      {}

      ~command_added() override final = default;

    protected:
      // Virtuals
      //============================================================
      void do_execute() override final
      {
        m_data_manager.added(m_handle); // outbound signal.
      }
      void do_unexecute() override final
      {
        m_data_manager.removed(m_handle); // outbound signal.
      }
    };

    template <typename T>
    decltype(auto) make_command_added(data_manager<T>& a_data_manager, handle<T> const& a_handle)
    {
      return std::unique_ptr<abstract::command>(std::make_unique<command_added<T>>(a_data_manager,a_handle).release());
    }

    template <typename T>
    decltype(auto) make_command_added(data_manager<T>& a_data_manager, handle<T> && a_handle)
    {
      return std::unique_ptr<abstract::command>(std::make_unique<command_added<T>>(a_data_manager,std::move(a_handle)).release());
    }


    //---------------------------------------------------------------------------
    // command_removed<T>
    //---------------------------------------------------------------------------
    // Class that derives from generic::command that wraps the addition of an
    // object to the project.

    template <typename T>
    class command_removed :
        public abstract::signalling_command<T>
    {
    public:
      // Typedefs
      //============================================================
      using inherited_type = abstract::signalling_command<T>;

      // Special 6
      //============================================================
      command_removed(data_manager_type& a_data_manager, handle_type const& a_handle):
        inherited_type(a_data_manager, a_handle)
      {}

      command_removed(data_manager_type& a_data_manager, handle_type && a_handle):
        inherited_type(a_data_manager, std::move(a_handle))
      {}

      ~command_removed() override final = default;

    protected:
      // Virtuals
      //============================================================
      void do_execute() override final
      {
        m_data_manager.removed(m_handle); // outbound signal.
      }
      void do_unexecute() override final
      {
        m_data_manager.added(m_handle); // outbound signal.
      }
    };

    template <typename T>
    decltype(auto) make_command_removed(data_manager<T>& a_data_manager, handle<T> const& a_handle)
    {
      return std::unique_ptr<abstract::command>(std::make_unique<command_removed<T>>(a_data_manager,a_handle).release());
    }

    template <typename T>
    decltype(auto) make_command_removed(data_manager<T>& a_data_manager, handle<T> && a_handle)
    {
      return std::unique_ptr<abstract::command>(std::make_unique<command_removed<T>>(a_data_manager,std::move(a_handle)).release());
    }

  } // namespace shared
} // namespace sak

#endif // SAK_SHARED_COMMAND_HPP
