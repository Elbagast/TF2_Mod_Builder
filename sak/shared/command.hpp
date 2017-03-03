#ifndef SAK_SHARED_COMMAND_HPP
#define SAK_SHARED_COMMAND_HPP

#include "fwd/command.hpp"
#include <generic/command.hpp>
#include "object.hpp"
#include "manager.hpp"
#include "extended_manager.hpp"
#include "signalbox.hpp"
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
        using signalbox_type = shared::abstract::signalbox<object_type>;
        using extended_handle_type = extended_handle<object_type>;

        // Special 6
        //============================================================
        signalling_command(signalbox_type& a_signalbox, extended_handle_type const& a_ehandle):
          inherited_type(),
          m_signalbox{a_signalbox},
          m_ehandle{a_ehandle}
        {}

        signalling_command(signalbox_type& a_signalbox, extended_handle_type && a_ehandle):
          inherited_type(),
          m_signalbox{a_signalbox},
          m_ehandle{std::move(a_ehandle)}
        {}

        ~signalling_command() override = default;

      protected:
        // Virtuals
        //============================================================
        void do_execute() override = 0;
        void do_unexecute() override = 0;

        // Data Members
        //============================================================
        signalbox_type& m_signalbox;
        extended_handle_type m_ehandle;
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
      command_assign(signalbox_type& a_signalbox, extended_handle_type const& a_ehandle, value_type const& a_value):
        inherited_type(a_signalbox, a_ehandle),
        m_new_value{a_value},
        // get the basic handle, then get the data held, then get the member, then get the value
        m_old_value{m_ehandle.cget_handle().cget().cat<Index>().cget()}
      {}

      ~command_assign() override final = default;

    protected:
      // Virtuals
      //============================================================
      void do_execute() override final
      {
        // open the handle, then the common data, then set that part of it.
        m_ehandle.get_handle().get().at<Index>().get() = m_new_value;
        m_signalbox.changed_at(m_ehandle, Index); // outbound signal.
        //dispatch_signals<object_type>::changed_at(m_project, m_ehandle, Index); // outbound signal.
      }
      void do_unexecute() override final
      {
        // open the handle, then the common data, then set that part of it.
        m_ehandle.get_handle().get().at<Index>().get() = m_old_value;
        m_signalbox.changed_at(m_ehandle, Index); // outbound signal.
        //dispatch_signals<object_type>::changed_at(m_project, m_ehandle, Index); // outbound signal.
      }

    private:
      // Data Members
      //============================================================
      value_type m_new_value;
      value_type m_old_value;
    };

    template <typename T, std::size_t Index>
    decltype(auto) make_command_assign(abstract::signalbox<T>& a_signalbox, typename command_assign<T,Index>::extended_handle_type const& a_ehandle, typename command_assign<T,Index>::value_type const& a_value)
    {
      return std::unique_ptr<abstract::command>(std::make_unique<command_assign<T,Index>>(a_signalbox, a_ehandle, a_value).release());
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
      command_added(signalbox_type& a_signalbox, extended_handle_type const& a_ehandle):
        inherited_type(a_signalbox, a_ehandle)
      {}

      command_added(signalbox_type& a_signalbox, extended_handle_type && a_ehandle):
        inherited_type(a_signalbox, std::move(a_ehandle))
      {}

      ~command_added() override final = default;

    protected:
      // Virtuals
      //============================================================
      void do_execute() override final
      {
        m_signalbox.added(m_ehandle); // outbound signal.
      }
      void do_unexecute() override final
      {
        m_signalbox.removed(m_ehandle); // outbound signal.
      }
    };

    template <typename T>
    decltype(auto) make_command_added(abstract::signalbox<T>& a_signalbox, extended_handle<T> const& a_ehandle)
    {
      return std::unique_ptr<abstract::command>(std::make_unique<command_added<T>>(a_signalbox,a_ehandle).release());
    }

    template <typename T>
    decltype(auto) make_command_added(abstract::signalbox<T>& a_signalbox, extended_handle<T> && a_ehandle)
    {
      return std::unique_ptr<abstract::command>(std::make_unique<command_added<T>>(a_signalbox,std::move(a_ehandle)).release());
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
      command_removed(signalbox_type& a_signalbox, extended_handle_type const& a_ehandle):
        inherited_type(a_signalbox, a_ehandle)
      {}

      command_removed(signalbox_type& a_signalbox, extended_handle_type && a_ehandle):
        inherited_type(a_signalbox, std::move(a_ehandle))
      {}

      ~command_removed() override final = default;

    protected:
      // Virtuals
      //============================================================
      void do_execute() override final
      {
        m_signalbox.removed(m_ehandle); // outbound signal.
      }
      void do_unexecute() override final
      {
        m_signalbox.added(m_ehandle); // outbound signal.
      }
    };

    template <typename T>
    decltype(auto) make_command_removed(abstract::signalbox<T>& a_signalbox, extended_handle<T> const& a_ehandle)
    {
      return std::unique_ptr<abstract::command>(std::make_unique<command_removed<T>>(a_signalbox,a_ehandle).release());
    }

    template <typename T>
    decltype(auto) make_command_removed(abstract::signalbox<T>& a_signalbox, extended_handle<T> && a_ehandle)
    {
      return std::unique_ptr<abstract::command>(std::make_unique<command_removed<T>>(a_signalbox,std::move(a_ehandle)).release());
    }

  } // namespace shared
} // namespace sak

#endif // SAK_SHARED_COMMAND_HPP
