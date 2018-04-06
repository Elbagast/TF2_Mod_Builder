#ifndef SAK_SECTION_COMMAND_HPP
#define SAK_SECTION_COMMAND_HPP

#ifndef SAK_SECTION_COMMAND_FWD_HPP
#include "section_command_fwd.hpp"
#endif

#ifndef SAK_ABSTRACT_COMMAND_HPP
#include "abstract_command.hpp"
#endif

#ifndef SAK_SECTION_DATA_HPP
#include "section_data.hpp"
#endif

#ifndef SAK_HANDLE_HPP
#include "handle.hpp"
#endif

#ifndef SAK_SECTION_DATA_MANAGER_HPP
#include "section_data_manager.hpp"
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Abstract_Signalling_Command<T>
  //---------------------------------------------------------------------------
  // Base class to contain shared typedefs and data members for commands on
  // objects via handles.

  template <typename T>
  class Abstract_Signalling_Command :
      public Abstract_Command
  {
  public:
    // Typedefs
    //============================================================
    using Data_Type = T;
    using Data_Manager_Type = Section_Data_Manager<Data_Type>;
    using Handle_Type = Handle<Data_Type>;

    // Special 6
    //============================================================
    Abstract_Signalling_Command(Data_Manager_Type* a_data_manager, Handle_Type const& a_handle):
      Abstract_Command(),
      m_data_manager{a_data_manager},
      m_handle{a_handle}
    {}

    Abstract_Signalling_Command(Data_Manager_Type* a_data_manager, Handle_Type && a_handle):
      Abstract_Command(),
      m_data_manager{a_data_manager},
      m_handle{std::move(a_handle)}
    {}

    ~Abstract_Signalling_Command() override = default;

  protected:
    // Virtuals
    //============================================================
    void do_execute() override = 0;
    void do_unexecute() override = 0;

    // Data Members
    //============================================================
    Data_Manager_Type* m_data_manager;
    Handle_Type m_handle;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Command_Assign<Index,T>
  //---------------------------------------------------------------------------
  // Class that derives from Abstract_Command that wraps the assignement of a
  // member's data.

  template <std::size_t Index, typename T>
  class Command_Assign :
      public Abstract_Signalling_Command<T>
  {
  public:
    // Typedefs
    //============================================================
    using Value_Type = Section_Data_Member_Value_Type<Index,Data_Type>;

    // Special 6
    //============================================================
    Command_Assign(Data_Manager_Type* a_data_manager, Handle_Type const& a_handle, Value_Type const& a_value):
      Abstract_Signalling_Command<T>(a_data_manager, a_handle),
      m_new_value{a_value},
      m_old_value{m_handle->cmember_at<Index>()}
    {}

    ~Command_Assign() override final = default;

  protected:
    // Virtuals
    //============================================================
    void do_execute() override final
    {
      // open the handle, then the common data, then set that part of it.
      m_handle->member_at<Index>() = m_new_value;
      m_data_manager->changed_at(m_handle, Index); // outbound signal.
      //dispatch_signals<Data_Type>::changed_at(m_project, m_handle, Index); // outbound signal.
    }
    void do_unexecute() override final
    {
      // open the handle, then the common data, then set that part of it.
      m_handle->member_at<Index>() = m_old_value;
      m_data_manager->changed_at(m_handle, Index); // outbound signal.
      //dispatch_signals<Data_Type>::changed_at(m_project, m_handle, Index); // outbound signal.
    }

  private:
    // Data Members
    //============================================================
    Value_Type m_new_value;
    Value_Type m_old_value;
  };

  template <std::size_t Index, typename T>
  decltype(auto) make_command_assign(typename Command_Assign<Index,T>::Data_Manager_Type* a_data_manager,
                                     typename Command_Assign<Index,T>::Handle_Type const& a_handle,
                                     typename Command_Assign<Index,T>::Value_Type const& a_value)
  {
    return std::unique_ptr<Abstract_Command>(std::make_unique<Command_Assign<Index,T>>(a_data_manager, a_handle, a_value).release());
  }

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Command_Added<T>
  //---------------------------------------------------------------------------
  // Class that derives from Abstract_Command that wraps the addition of an
  // object to the project.

  template <typename T>
  class Command_Added :
      public Abstract_Signalling_Command<T>
  {
  public:
    // Special 6
    //============================================================
    Command_Added(Data_Manager_Type* a_data_manager, Handle_Type const& a_handle):
      Abstract_Signalling_Command<T>(a_data_manager, a_handle)
    {}

    Command_Added(Data_Manager_Type* a_data_manager, Handle_Type && a_handle):
      Abstract_Signalling_Command<T>(a_data_manager, std::move(a_handle))
    {}

    ~Command_Added() override final = default;

  protected:
    // Virtuals
    //============================================================
    void do_execute() override final
    {
      assert(!m_data_manager->has_handle(m_handle));
      m_data_manager->added(m_handle); // outbound signal.
      assert(m_data_manager->has_handle(m_handle));
    }
    void do_unexecute() override final
    {
      assert(m_data_manager->has_handle(m_handle));
      m_data_manager->removed(m_handle); // outbound signal.
      assert(!m_data_manager->has_handle(m_handle));
    }
  };

  template <typename T>
  decltype(auto) make_command_added(typename Command_Added<T>::Data_Manager_Type* a_data_manager,
                                    typename Command_Added<T>::Handle_Type const& a_handle)
  {
    return std::unique_ptr<Abstract_Command>(std::make_unique<Command_Added<T>>(a_data_manager,a_handle).release());
  }

  template <typename T>
  decltype(auto) make_command_added(typename Command_Added<T>::Data_Manager_Type* a_data_manager,
                                    typename Command_Added<T>::Handle_Type && a_handle)
  {
    return std::unique_ptr<Abstract_Command>(std::make_unique<Command_Added<T>>(a_data_manager,std::move(a_handle)).release());
  }

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Command_Removed<T>
  //---------------------------------------------------------------------------
  // Class that derives from Abstract_Command that wraps the removal of an
  // object to the project.

  template <typename T>
  class Command_Removed :
      public Abstract_Signalling_Command<T>
  {
  public:
    // Special 6
    //============================================================
    Command_Removed(Data_Manager_Type* a_data_manager, Handle_Type const& a_handle):
      Abstract_Signalling_Command<T>(a_data_manager, a_handle)
    {}

    Command_Removed(Data_Manager_Type* a_data_manager, Handle_Type && a_handle):
      Abstract_Signalling_Command<T>(a_data_manager, std::move(a_handle))
    {}

    ~Command_Removed() override final = default;

  protected:
    // Virtuals
    //============================================================
    void do_execute() override final
    {
      assert(m_data_manager->has_handle(m_handle));
      m_data_manager->removed(m_handle); // outbound signal.
      assert(!m_data_manager->has_handle(m_handle));
    }
    void do_unexecute() override final
    {
      assert(!m_data_manager->has_handle(m_handle));
      m_data_manager->added(m_handle); // outbound signal.
      assert(m_data_manager->has_handle(m_handle));
    }
  private:
  };

  template <typename T>
  decltype(auto) make_command_removed(typename Command_Removed<T>::Data_Manager_Type* a_data_manager,
                                      typename Command_Removed<T>::Handle_Type const& a_handle)
  {
    return std::unique_ptr<Abstract_Command>(std::make_unique<Command_Removed<T>>(a_data_manager,a_handle).release());
  }

  template <typename T>
  decltype(auto) make_command_removed(typename Command_Removed<T>::Data_Manager_Type* a_data_manager,
                                      typename Command_Removed<T>::Handle_Type && a_handle)
  {
    return std::unique_ptr<Abstract_Command>(std::make_unique<Command_Removed<T>>(a_data_manager,std::move(a_handle)).release());
  }

} // namespace sak

#endif // SAK_SECTION_COMMAND_HPP
