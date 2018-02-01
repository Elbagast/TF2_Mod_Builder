#ifndef SECTION_INTERFACE_HPP
#define SECTION_INTERFACE_HPP

#ifndef SAK_SECTION_INTERFACE_FWD_HPP
#include "section_interface_fwd.hpp"
#endif

#ifndef SAK_Handle_FWD_HPP
#include "Handle_fwd.hpp"
#endif

#ifndef SAK_SECTION_DATA_MANAGER_FWD_HPP
#include "section_data_manager_fwd.hpp"
#endif

#ifndef SAK_COMMAND_HISTORY_FWD_HPP
#include "command_history_fwd.hpp"
#endif

#ifndef SAK_SECTION_DATA_HPP
#include "section_data.hpp"
#endif

#ifndef INCLUDE_STD_VECTOR
#define INCLUDE_STD_VECTOR
#include <vector>
#endif

namespace sak
{
  namespace internal
  {
    //---------------------------------------------------------------------------
    // Do_Change_At<T,I>
    //---------------------------------------------------------------------------
    // The change behaviour seperated out so that the name can be treated in a
    // unique way.

    template <std::size_t Index, typename T>
    class Do_Change_At
    {
    public:
      // Typedefs
      //============================================================
      using Data_Type = T;
      using Data_Manager_Type = Section_Data_Manager<T>;
      using Handle_Type = Handle<T>;
      using Member_Value_Type = Section_Data_Member_Value_Type<Index,Data_Type>;

      // Interface
      //============================================================
      bool operator()(
          Data_Manager_Type* a_data_manager,
          Command_History* a_command_history,
          Handle_Type const& a_handle,
          Member_Value_Type const& a_value);
    };


    template <typename T>
    class Do_Change_At<0,T>
    {
    public:
      // Typedefs
      //============================================================
      using Data_Type = T;
      using Data_Manager_Type = Section_Data_Manager<T>;
      using Handle_Type = Handle<T>;
      using Member_Value_Type = Section_Data_Member_Value_Type<0,Data_Type>;

      // Interface
      //============================================================
      bool operator()(
          Data_Manager_Type* a_data_manager,
          Command_History* a_command_history,
          Handle_Type const& a_handle,
          Member_Value_Type const& a_value);
    };
  }


  //---------------------------------------------------------------------------
  // Section_Interface<T>
  //---------------------------------------------------------------------------
  // Supply an interface to send signals back to the Project. This allows us to
  // hide the signalling methods from the templates so we can have template
  // classes only expose things that need to be exposed.
  template <typename T>
  class Section_Interface
  {
  public:
    using Data_Type = T;
    using Data_Manager_Type = Section_Data_Manager<T>;
    using Handle_Type = Handle<T>;

    // Special 6
    //============================================================
    Section_Interface(Data_Manager_Type* a_data_manager, Command_History* a_command_history);
    ~Section_Interface();

    Section_Interface(Section_Interface const&);
    Section_Interface& operator=(Section_Interface const&);

    Section_Interface(Section_Interface &&);
    Section_Interface& operator=(Section_Interface &&);

    // Interface
    //============================================================
    // Everything you can do with a data_class derived object.

    // Are there any objects in this Project?
    bool is_empty() const;
    bool not_empty() const;

    // How many objects are in this Project?
    std::size_t count() const;

    // Get the objects at this index
    Handle_Type get_at(std::size_t a_index) const;

    // Get all the objects
    std::vector<Handle_Type> get_all() const;

    // Get all the object names
    std::vector<QString> get_all_names() const;

    // Make a new object using the default parameters. Project's data management system owns it
    // but it is not part of the Project. Does not trigger any commands.
    Handle_Type make_default();

    // Make a new object using the supplied data. Project's data management system owns it but
    // it is not part of the Project. Does not trigger any commands.
    Handle_Type make_emplace(Data_Type&& a_data);

    // Undoable add a new object made using the default parameters. The name will be modified if it is
    // currently in use by another object.
    void add_default();

    // Undoable add a new object using the supplied data. This data is assigned a new handle. The name will
    // be modified if it is currently in use by another object.
    void add_emplace(Data_Type&& a_data);

    // Undoable add a new object using the supplied handle. The name will be modified if it is currently in
    // use by another object. If this handle is invalid or already in the data then nothing happens.
    void add(Handle_Type const& a_handle);

    // Undoable remove object. If this handle is invalid or not in the data nothing happens.
    // Data is not deleted until the last reference is deleted.
    void remove(Handle_Type const& a_handle);

    // Undoable change an object's member value. Returns true if this call results in a change being made.
    // Does nothing and returns false if this handle is invalid or not in the data, or if the supplied value
    // doesn't result in data being changed.
    template <std::size_t Index>
    bool change_at(Handle_Type const& a_handle, Section_Data_Member_Value_Type<Index,Data_Type> const& a_value)
    {
      return internal::Do_Change_At<Index,Data_Type>()(m_data_manager, m_command_history, a_handle, a_value);
    }

    // Request that the editor for this file be opened or switched to.
    void request_editor(Handle_Type const& a_handle);

    // Request that the focus change to this object.
    void request_focus(Handle_Type const& a_handle);

  private:
    // Data Members
    //============================================================
    Data_Manager_Type* m_data_manager;
    Command_History* m_command_history;
  };
}

#endif // SECTION_INTERFACE_HPP
