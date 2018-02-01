#ifndef SAK_ABSTRACT_PROJECT_INTERFACE_HPP
#define SAK_ABSTRACT_PROJECT_INTERFACE_HPP

#include <cstddef>
#include "abstract_project_signalbox.hpp"

#ifndef SAK_SECTION_INTERFACE_FWD_HPP
#include "section_interface_fwd.hpp"
#endif

#ifndef SAK_HANDLE_FWD_HPP
#include "handle_fwd.hpp"
#endif

#ifndef SAK_SECTION_DATA_MANAGER_FWD_HPP
#include "section_data_manager_fwd.hpp"
#endif

#ifndef SAK_SECTION_DATA_HPP
#include "section_data.hpp"
#endif

#ifndef INCLUDE_STD_VECTOR
#define INCLUDE_STD_VECTOR
#include <vector>
#endif

class QString;

namespace sak
{
  template <typename T>
  class Section_Tag
  {
  };

  template <std::size_t I>
  class Section_Member_Tag
  {
  };



  //---------------------------------------------------------------------------
  // Abstract_Section_Member_Interface<T, Index, Last>
  //---------------------------------------------------------------------------
  // Interface for each member of T.

  template <typename T, std::size_t Index, std::size_t Last = (Section_Data_Size_v<T> - 1)>
  class Abstract_Section_Member_Interface :
      public Abstract_Section_Member_Interface<T, Index+1, Last>
  {
  public:
    // Special 6
    //============================================================
    virtual ~Abstract_Section_Member_Interface() = 0;

    // Virtuals
    //============================================================

    // Undoable change an object's member value. Returns true if this call results in a change being made.
    // Does nothing and returns false if this handle is invalid or not in the data, or if the supplied value
    // doesn't result in data being changed.
    virtual bool change_at( Section_Member_Tag<Index>&&,
                            Handle<T> const& a_handle,
                            Section_Data_Member_Value_Type<Index,T> const& a_value
                           ) = 0;

    using Abstract_Section_Member_Interface<T, Index+1, Last>::change_at;
  };

  template <typename T, std::size_t Last>
  class Abstract_Section_Member_Interface<T, Last, Last>
  {
  public:
    // Special 6
    //============================================================
    virtual ~Abstract_Section_Member_Interface() = 0;

    // Virtuals
    //============================================================

    virtual bool change_at( Section_Member_Tag<Last>&&,
                            Handle<T> const& a_handle,
                            Section_Data_Member_Value_Type<Last,T> const& a_value
                           ) = 0;
  };

  //---------------------------------------------------------------------------
  // Abstract_Section_Interface<T>
  //---------------------------------------------------------------------------
  // The sub interface for a section of a project.

  template <typename T>
  class Abstract_Section_Interface :
      public virtual Abstract_Section_Member_Interface<T,0>
  {
  public:
    using Data_Type = T;
    using Data_Manager_Type = Section_Data_Manager<T>;
    using Handle_Type = Handle<T>;

    // Special 6
    //============================================================
    virtual ~Abstract_Section_Interface() = 0;

    // Interface
    //============================================================
    // Everything you can do with a data_class derived object.

    // Are there any objects in this Project?
    bool is_empty(Section_Tag<T>&&) const;
    bool not_empty(Section_Tag<T>&&) const;

    // How many objects are in this Project?
    std::size_t count(Section_Tag<T>&&) const;

    // Get the objects at this index
    Handle_Type get_at(std::size_t a_index) const;

    // Get all the objects
    std::vector<Handle_Type> get_all(Section_Tag<T>&&) const;

    // Get all the object names
    std::vector<QString> get_all_names(Section_Tag<T>&&) const;

    // Make a new object using the default parameters. Project's data management system owns it
    // but it is not part of the Project. Does not trigger any commands.
    Handle_Type make_default(Section_Tag<T>&&);

    // Make a new object using the supplied data. Project's data management system owns it but
    // it is not part of the Project. Does not trigger any commands.
    Handle_Type make_emplace(Data_Type&& a_data);

    // Undoable add a new object made using the default parameters. The name will be modified if it is
    // currently in use by another object.
    void add_default(Section_Tag<T>&&);

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
    using Abstract_Section_Member_Interface<T,0>::change_at;

    // Request that the editor for this file be opened or switched to.
    void request_editor(Handle_Type const& a_handle);

    // Request that the focus change to this object.
    void request_focus(Handle_Type const& a_handle);
  };

  //---------------------------------------------------------------------------
  // Abstract_Project_Interface
  //---------------------------------------------------------------------------
  // The full interface class for project data.

  class Abstract_Project_Interface :
      public virtual Abstract_Section_Interface<File_Data>,
      public virtual Abstract_Section_Interface<Texture_Data>
  {
  public:
    // Special 6
    //============================================================
    virtual ~Abstract_Project_Interface() = 0;

    // Interface
    //============================================================
    // Data that is fixed on contruction.
    virtual QString name() const = 0;
    virtual QString location() const = 0;
    virtual QString filepath() const = 0;

    // Add an object that will rely on the Project's signals. If nulltpr, nothing happens.
    virtual void add_signalbox(Abstract_Project_Signalbox* a_signalbox) = 0;

    // Remove an object that will rely on the Project's signals. If nulltpr, nothing happens.
    virtual void remove_signalbox(Abstract_Project_Signalbox* a_signalbox) = 0;

    // Clear all the signalboxes so that nothing relies on changes to this.
    virtual void clear_signalboxes() = 0;

    // Can we currently call undo?
    virtual bool can_undo() const = 0;

    // Can we currently call redo?
    virtual bool can_redo() const = 0;

    // How many times can undo() be called?
    virtual std::size_t undo_count() const = 0;

    // How many times can redo() be called?
    virtual std::size_t redo_count() const = 0;

    // Undo the last command issued.
    virtual void undo() = 0;

    // Redo the last undone command in the command history
    virtual void redo() = 0;

    // Clear the undo/redo history.
    virtual void clear_history() = 0;
  };
}

#endif // SAK_ABSTRACT_PROJECT_INTERFACE_HPP
