#ifndef SAK_PROJECT_COMMANDS_HPP
#define SAK_PROJECT_COMMANDS_HPP

#ifndef SAK_PROJECT_COMMANDS_FWD_HPP
#include "project_commands_fwd.hpp"
#endif

#ifndef SAK_ABSTRACT_COMMAND_HPP
#include "abstract_command.hpp"
#endif

#ifndef SAK_CLASS_DEFINITIONS_HPP
#include "class_definitions.hpp"
#endif

#ifndef SAK_TAG_HPP
#include "tag.hpp"
#endif

#ifndef SAK_ID_HPP
#include "id.hpp"
#endif

#ifndef SAK_DATA_HPP
#include "data.hpp"
#endif

#ifndef SAK_HANDLE_HPP
#include "handle.hpp"
#endif

#ifndef SAK_SIGNAL_SOURCE_HPP
#include "signal_source.hpp"
#endif

#ifndef SAK_PROJECT_HANDLE_DATA_HPP
#include "project_handle_data.hpp"
#endif

#ifndef SAK_PROJECT_SIGNALBOX_DATA_HPP
#include "project_signalbox_data.hpp"
#endif

#ifndef FLAMINGO_TYPELIST_HPP
#include <flamingo/typelist.hpp>
#endif

#ifndef INCLUDE_STD_CASSERT
#define INCLUDE_STD_CASSERT
#include <cassert>
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Project_Command_Base<List, Index>
  //---------------------------------------------------------------------------
  // Base class for implementing commands relating to a given handle type. It
  // implements the common data that each command will need.

  template <std::size_t LI, typename...Args>
  class Project_Command_Base<flamingo::typelist<Args...>,LI> :
      public Abstract_Command
  {
    // Typedefs
    //============================================================
    using Inh = Abstract_Command;
    using Typelist_Type = flamingo::typelist<Args...>;
    using Type = flamingo::typelist_at_t<Typelist_Type,LI>;
    using Data_Type = Data<Type>;
    using ID_Type = ID<Type>;
    using Handle_Type = Handle<Type>;
    using Tag_Type = Tag<Type>;

  public:
    // Special 6
    //============================================================
    Project_Command_Base(Signal_Source a_source, Project_Handle_Data_Imp<Args...>& a_handle_data, Project_Signalbox_Data_Imp<Args...>& a_signalbox_data, Handle_Type const& a_handle) :
      Inh{a_source},
      m_handle_data{a_handle_data},
      m_signalbox_data{a_signalbox_data},
      m_handle{a_handle}
    {
      // the supplied handle had better be valid.
      assert(m_handle);
    }

    ~Project_Command_Base() override = default;

    Project_Command_Base(Project_Command_Base const&) = delete;
    Project_Command_Base& operator=(Project_Command_Base const&) = delete;

    Project_Command_Base(Project_Command_Base &&) = default;
    Project_Command_Base& operator=(Project_Command_Base &&) = default;

  protected:
    // Virtuals
    //============================================================
    void do_execute() override = 0;
    void do_unexecute() override = 0;

    // Internal Interface
    //============================================================
    Project_Handle_Data_Imp<Args...>& get_handle_data()
    {
      return m_handle_data;
    }

    Project_Handle_Data_Imp<Args...> const & cget_handle_data() const
    {
      return m_handle_data;
    }

    Project_Signalbox_Data_Imp<Args...>& get_signalbox_data()
    {
      return m_signalbox_data;
    }

    Project_Signalbox_Data_Imp<Args...> const & cget_signalbox_data() const
    {
      return m_signalbox_data;
    }

    Handle_Type& get_handle()
    {
      return m_handle;
    }

    Handle_Type const & cget_handle() const
    {
      return m_handle;
    }

  private:
    // Data Members
    //============================================================
    Project_Handle_Data_Imp<Args...>& m_handle_data;
    Project_Signalbox_Data_Imp<Args...>& m_signalbox_data;
    Handle_Type m_handle;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Project_Command_Change_Name<List, Index>
  //---------------------------------------------------------------------------
  // Base class for implementing commands relating to a given handle type. It
  // implements the common data that each command will need.
  template <std::size_t LI, typename...Args>
  class Project_Command_Change_Name<flamingo::typelist<Args...>,LI> :
      public Project_Command_Base<flamingo::typelist<Args...>,LI>
  {
    // Typedefs
    //============================================================
    using Inh = Project_Command_Base<flamingo::typelist<Args...>,LI>;
    using Typelist_Type = flamingo::typelist<Args...>;
    using Type = flamingo::typelist_at_t<Typelist_Type,LI>;
    using Data_Type = Data<Type>;
    using ID_Type = ID<Type>;
    using Handle_Type = Handle<Type>;
    using Tag_Type = Tag<Type>;

  public:
    // Special 6
    //============================================================
    Project_Command_Change_Name(Signal_Source a_source,
                                Project_Handle_Data_Imp<Args...>& a_handle_data,
                                Project_Signalbox_Data_Imp<Args...>& a_signalbox_data,
                                Handle_Type const& a_handle,
                                QString const& a_name) :
      Inh{a_source, a_handle_data, a_signalbox_data, a_handle},
      m_old_name{cget_handle()->cname()},
      m_new_name{a_name}
    {
      // The supplied names had better have been vetted already.
      assert(m_old_name != m_new_name);
      // old name is in the data
      assert(cget_handle_data().has_name(m_old_name));
      // new name is not in the data
      assert(!cget_handle_data().has_name(m_new_name));
    }

    ~Project_Command_Change_Name() override = default;

    Project_Command_Change_Name(Project_Command_Change_Name const&) = delete;
    Project_Command_Change_Name& operator=(Project_Command_Change_Name const&) = delete;

    Project_Command_Change_Name(Project_Command_Change_Name &&) = default;
    Project_Command_Change_Name& operator=(Project_Command_Change_Name &&) = default;

  protected:
    // Virtuals
    //============================================================
    void do_execute() override final
    {
      // The handle had better still be valid.
      assert(cget_handle_data().cget_section_at<LI>()->has_handle(cget_handle()));

      // old name is in the data
      assert(cget_handle_data().has_name(m_old_name));
      // new name is not in the data
      assert(!cget_handle_data().has_name(m_new_name));

      get_handle()->name() = m_new_name;

      do_signal();

      // old name is not in the data
      assert(!cget_handle_data().has_name(m_old_name));
      // new name is in the data
      assert(cget_handle_data().has_name(m_new_name));
    }
    void do_unexecute() override final
    {
      // The handle had better still be valid.
      assert(cget_handle_data().cget_section_at<LI>()->has_handle(cget_handle()));

      // old name is not in the data
      assert(!cget_handle_data().has_name(m_old_name));
      // new name is in the data
      assert(cget_handle_data().has_name(m_new_name));

      get_handle()->name() = m_old_name;

      do_signal();

      // old name is in the data
      assert(cget_handle_data().has_name(m_old_name));
      // new name is not in the data
      assert(!cget_handle_data().has_name(m_new_name));
    }

  private:
    void do_signal()
    {
      get_signalbox_data().get_section_at<LI>()->changed_name(this->source(),
                                                           cget_handle().id(),
                                                           cget_handle_data().cget_section_at<LI>()->index(cget_handle().id()));
    }

    // Data Members
    //============================================================
    QString m_old_name;
    QString m_new_name;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  template <std::size_t I, typename...Args>
  std::unique_ptr<Abstract_Command> make_command_change_name(Signal_Source a_source,
                                                             Project_Handle_Data_Imp<Args...>& a_handle_data,
                                                             Project_Signalbox_Data_Imp<Args...>& a_signalbox_data,
                                                             Handle<flamingo::typelist_at_t<flamingo::typelist<Args...>,I>> const& a_handle,
                                                             QString const& a_name)
  {
    return std::unique_ptr<Abstract_Command>
    {
      std::make_unique<Project_Command_Change_Name<flamingo::typelist<Args...>,I>>(a_source,
                                                                                   a_handle_data,
                                                                                   a_signalbox_data,
                                                                                   a_handle,
                                                                                   a_name).release()
    };
  }

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Project_Command_Added<List, Index>
  //---------------------------------------------------------------------------
  // The supplied handle is to be added to the data. It should not be referenced
  // by anything at the point of this command's construction, and if the command
  // is undone it is assumed that all changes to the data that resulted in
  // references to this handle have also been undone.

  template <std::size_t LI, typename...Args>
  class Project_Command_Added<flamingo::typelist<Args...>,LI> :
      public Project_Command_Base<flamingo::typelist<Args...>,LI>
  {
    // Typedefs
    //============================================================
    using Inh = Project_Command_Base<flamingo::typelist<Args...>,LI>;
    using Typelist_Type = flamingo::typelist<Args...>;
    using Type = flamingo::typelist_at_t<Typelist_Type,LI>;
    using Data_Type = Data<Type>;
    using ID_Type = ID<Type>;
    using Handle_Type = Handle<Type>;
    using Tag_Type = Tag<Type>;

  public:
    // Special 6
    //============================================================
    Project_Command_Added(Signal_Source a_source,
                                Project_Handle_Data_Imp<Args...>& a_handle_data,
                                Project_Signalbox_Data_Imp<Args...>& a_signalbox_data,
                                Handle_Type const& a_handle) :
      Inh{a_source, a_handle_data, a_signalbox_data, a_handle},
      m_index{a_handle_data.cget_section_at<LI>()->future_index(a_handle->cname())} // The postition the handle will be inserted at and removed from
    {
    }

    ~Project_Command_Added() override = default;

    Project_Command_Added(Project_Command_Added const&) = delete;
    Project_Command_Added& operator=(Project_Command_Added const&) = delete;

    Project_Command_Added(Project_Command_Added &&) = default;
    Project_Command_Added& operator=(Project_Command_Added &&) = default;

  protected:
    // Virtuals
    //============================================================
    void do_execute() override final
    {
      // The handle must be valid.
      assert(cget_handle());
      // It must not be present in the data.
      assert(cget_handle_data().cget_section_at<LI>()->has_handle(cget_handle()) == false);

      auto l_index = get_handle_data().get_section_at<LI>()->add(cget_handle());
      assert(m_index == l_index);

      // It must be present in the data.
      assert(cget_handle_data().cget_section_at<LI>()->has_handle(cget_handle()) == true);
      // It must be at the index.
      assert(cget_handle_data().cget_section_at<LI>()->get_at(Tag_Type{}, m_index) == cget_handle().id());

      // Signal the change
      get_signalbox_data().get_section_at<LI>()->added(this->source(),cget_handle().id(),m_index);
    }
    void do_unexecute() override final
    {
      // The handle must be valid.
      assert(cget_handle());
      // It must be present in the data.
      assert(cget_handle_data().cget_section_at<LI>()->has_handle(cget_handle()) == true);
      // It must be at the index.
      assert(cget_handle_data().cget_section_at<LI>()->get_at(Tag_Type{}, m_index) == cget_handle().id());

      auto l_result = get_handle_data().get_section_at<LI>()->remove(Tag_Type{}, m_index);
      assert(l_result);

      // It must not be present in the data.
      assert(cget_handle_data().cget_section_at<LI>()->has_handle(cget_handle()) == false);

      // Signal the change
      get_signalbox_data().get_section_at<LI>()->removed(this->source(),cget_handle().id(),m_index);
    }

  private:

    // Data Members
    //============================================================
    std::size_t m_index;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  template <std::size_t I, typename...Args>
  std::unique_ptr<Abstract_Command> make_command_added(Signal_Source a_source,
                                                       Project_Handle_Data_Imp<Args...>& a_handle_data,
                                                       Project_Signalbox_Data_Imp<Args...>& a_signalbox_data,
                                                       Handle<flamingo::typelist_at_t<flamingo::typelist<Args...>,I>> const& a_handle)
  {
    return std::unique_ptr<Abstract_Command>
    {
      std::make_unique<Project_Command_Added<flamingo::typelist<Args...>,I>>(a_source,
                                                                             a_handle_data,
                                                                             a_signalbox_data,
                                                                             a_handle).release()
    };
  }

} // namespace sak

#endif // SAK_PROJECT_COMMANDS_HPP
