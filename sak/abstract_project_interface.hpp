#ifndef SAK_ABSTRACT_PROJECT_INTERFACE_HPP
#define SAK_ABSTRACT_PROJECT_INTERFACE_HPP

#ifndef SAK_ABSTRACT_PROJECT_INTERFACE_FWD_HPP
#include "abstract_project_interface_fwd.hpp"
#endif

#ifndef SAK_ABSTRACT_PROJECT_SIGNALBOX_FWD_HPP
#include "abstract_project_signalbox_fwd.hpp"
#endif
//#include "abstract_project_signalbox.hpp"

#ifndef SAK_SECTION_INTERFACE_FWD_HPP
#include "section_interface_fwd.hpp"
#endif

#ifndef SAK_HANDLE_FWD_HPP
#include "handle_fwd.hpp"
#endif

#ifndef SAK_TAG_FWD_HPP
#include "tag_fwd.hpp"
#endif

#ifndef SAK_PROJECT_DATA_FWD_HPP
#include "project_data_fwd.hpp"
#endif

#ifndef SAK_DATA_HPP
#include "data.hpp"
#endif

#ifndef FLAMINGO_TYPELIST_HPP
#include <flamingo/typelist.hpp>
#endif

#ifndef INCLUDE_STD_VECTOR
#define INCLUDE_STD_VECTOR
#include <vector>
#endif

#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif

class QString;
/*
Virtual inheritance creates a massive overhead, and this class is to be used in
only one place. So how do we remove it?

if
A has 3 members
B has 1 members
C has 2 members

Top<A,B,C>
  - rest of the interface
  - using lower
  Part<List<A,B,C>,0,2,0,2> - List index, List size-1, member index, member count-1
    - A<0> interface
    - using lower
    Part<List<A,B,C>,0,2,1,2>
      - A<1> interface
      - using lower
      Part<List<A,B,C>,0,2,2,2>
        - A<2> interface - last one
        - A interface
        - using lower
        Part<List<A,B,C>,1,2,0,0>
          - B<0> interface - last one
          - B interface
          - using lower
          Part<List<A,B,C>,2,2,0,1>
            - C<0> interface
            - using lower
            Part<List<A,B,C>,2,2,1,1>
              - A<1> interface - last one
              - C interface - last one


*/

namespace sak
{
  //---------------------------------------------------------------------------
  // Abstract_Section_Member_Interface<T>
  //---------------------------------------------------------------------------
  // The interface for the member of a managed type.

  template <std::size_t Index, typename T>
  class Abstract_Section_Member_Interface
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
    virtual bool change_at( Index_Tag<Index>&&,
                            Handle<T> const& a_handle,
                            Data_Member_Value_Type<Index,Data<T>> const& a_value
                           ) = 0;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Abstract_Chained_Member_Interface<T, Index, Last>
  //---------------------------------------------------------------------------
  // Combine the interfaces of all of the members of a given type.

  // Since there is no member at End index, we must stop at the Last index,
  // otherwise the function reveal will have no functions to reveal.
  template <typename T, std::size_t Index = 0, std::size_t Last = (Data_Size_v<Data<T>> - 1)>
  class Abstract_Chained_Member_Interface :
      protected virtual Abstract_Chained_Member_Interface<T,Index+1,Last>,
      protected virtual Abstract_Section_Member_Interface<Index,T>
  {
    static_assert(Data_Size_v<Data<T>> != 0, "Cannot use data with no members.");

    using Inh1 = Abstract_Chained_Member_Interface<T,Index+1,Last>;
    using Inh2 = Abstract_Section_Member_Interface<Index,T>;
  public:
    ~Abstract_Chained_Member_Interface() override = 0;

    using Inh1::change_at;
    using Inh2::change_at;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  // For the last, inherit and reveal the individual interface.
  template <typename T, std::size_t Last>
  class Abstract_Chained_Member_Interface<T,Last,Last>:
      protected virtual Abstract_Section_Member_Interface<Last,T>
  {
    static_assert(Data_Size_v<Data<T>> == (Last+1), "Bad last index.");

    using Inh = Abstract_Section_Member_Interface<Last,T>;
  public:
    ~Abstract_Chained_Member_Interface() override = 0;

    using Inh::change_at;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Abstract_Section_Interface<T>
  //---------------------------------------------------------------------------
  // The full interface for a single type that the project manages. It includes
  // all of the member interfaces.

  template <typename T>
  class Abstract_Section_Interface :
      protected virtual Abstract_Chained_Member_Interface<T,0>
  {
    static_assert(Data_Size_v<Data<T>> != 0, "Cannot use data with no members.");

    using Inh = Abstract_Chained_Member_Interface<T,0>;
  public:
    // Special 6
    //============================================================
    ~Abstract_Section_Interface() override = 0;

    // Interface
    //============================================================
    // Everything you can do with a data_class derived object.

    // Are there any objects in this Project?
    virtual bool is_empty(Tag<T>&&) const = 0;
    virtual bool not_empty(Tag<T>&&) const = 0;
    // How many objects are in this Project?
    virtual std::size_t count(Tag<T>&&) const = 0;

    // Does this handle appear in the data?
    virtual bool has_handle(Handle<T> const&) const = 0;
    // Does this name appear in the data?
    virtual bool has_handle_named(Tag<T>&&, QString const&) const = 0;

    // Get the handle at this index. If the index is invalid a null handle is returned.
    virtual Handle<T> get_handle_at(Tag<T>&&, std::size_t a_index) const = 0;
    // Get the handle with this name. If the name is invalid a null handle is returned.
    virtual Handle<T> get_handle_named(Tag<T>&&, QString const&) const = 0;

    // Get all the handles in data order
    virtual std::vector<Handle<T>> get_handles(Tag<T>&&) const = 0;
    // Get all the handles names in data order
    virtual std::vector<QString> get_names(Tag<T>&&) const = 0;

    // Make a new object using the default parameters. Project's data management system owns it
    // but it is not part of the Project. Does not trigger any commands.
    virtual Handle<T> make_default(Tag<T>&&) const = 0;
    // Make a new object using the supplied data. Project's data management system owns it but
    // it is not part of the Project. Does not trigger any commands.
    virtual Handle<T> make_emplace(Data<T>&& a_data) const = 0;

    // Undoable add a new object made using the default parameters. The name will be modified if it is
    // currently in use by another object. Return true if the operation resulted in an undoable command.
    virtual bool add_default(Tag<T>&&) = 0;
    // Undoable add a new object using the supplied data. This data is assigned a new handle. The name will
    // be modified if it is currently in use by another object. Return true if the operationn resulted in an undoable command.
    virtual bool add_emplace(Data<T>&& a_data) = 0;
    // Undoable add a new object using the supplied handle. The name will be modified if it is currently in
    // use by another object. Return true if the operation resulted in an undoable command. If this handle
    // is invalid or already in the data then nothing happens and returns false.
    virtual bool add(Handle<T> const& a_handle) = 0;
    // Undoable remove object. Return true if the operation resulted in an undoable command. If this handle
    // is invalid or already in the data then nothing happens and returns false. Handle data is not deleted
    // until the last handle for it is deleted.
    virtual bool remove(Handle<T> const& a_handle) = 0;

    // Undoable change a handles name. Returns true if this call results in a change being made.
    // If the name supplied is already in use then the supplied name will be altered.
    virtual bool change_name(Handle<T> const& a_handle, QString const& a_name) = 0;

    // Undoable change an object's member value. Returns true if this call results in a change being made.
    // Does nothing and returns false if this handle is invalid or not in the data, or if the supplied value
    // doesn't result in data being changed.
    using Inh::change_at;

    // Request that the editor for this file be opened or switched to.
    virtual void request_editor(Handle<T> const& a_handle) = 0;
    // Request that the focus change to this object.
    virtual void request_focus(Handle<T> const& a_handle) = 0;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Abstract_Chained_Interface<Args...>
  //---------------------------------------------------------------------------
  // Combine the interfaces of all of the members of a given type.

  template <typename T, typename ...Args>
  class Abstract_Chained_Interface;

  // Since there is no member at End index, we must stop at the Last index,
  // otherwise the function reveal will have no functions to reveal.
  template <typename T>
  class Abstract_Chained_Interface<T> :
      protected virtual Abstract_Section_Interface<T>
  {
    using Inh = Abstract_Section_Interface<T>;
  public:
    // Special 6
    //============================================================
    ~Abstract_Chained_Interface() override = 0;

    // Interface
    //============================================================
    using Inh::is_empty;
    using Inh::not_empty;
    using Inh::count;
    using Inh::has_handle;
    using Inh::has_handle_named;
    using Inh::get_handle_at;
    using Inh::get_handle_named;
    using Inh::get_handles;
    using Inh::get_names;
    using Inh::make_default;
    using Inh::make_emplace;
    using Inh::add_default;
    using Inh::add_emplace;
    using Inh::add;
    using Inh::remove;
    using Inh::change_name;
    using Inh::change_at;
    using Inh::request_editor;
    using Inh::request_focus;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  // For at least 2, we inherit one and use it's functions, then chain the next
  // and expose its functions too.
  template <typename T, typename R, typename...Args>
  class Abstract_Chained_Interface<T,R,Args...>:
      protected virtual Abstract_Chained_Interface<T>,
      protected virtual Abstract_Chained_Interface<R, Args...>
  {
    using Inh1 = Abstract_Chained_Interface<T>;
    using Inh2 = Abstract_Chained_Interface<R, Args...>;
  public:
    // Special 6
    //============================================================
    ~Abstract_Chained_Interface() override = 0;

    // Interface
    //============================================================
    using Inh1::is_empty;
    using Inh1::not_empty;
    using Inh1::count;
    using Inh1::has_handle;
    using Inh1::has_handle_named;
    using Inh1::get_handle_at;
    using Inh1::get_handle_named;
    using Inh1::get_handles;
    using Inh1::get_names;
    using Inh1::make_default;
    using Inh1::make_emplace;
    using Inh1::add_default;
    using Inh1::add_emplace;
    using Inh1::add;
    using Inh1::remove;
    using Inh1::change_name;
    using Inh1::change_at;
    using Inh1::request_editor;
    using Inh1::request_focus;

    using Inh2::is_empty;
    using Inh2::not_empty;
    using Inh2::count;
    using Inh2::has_handle;
    using Inh2::has_handle_named;
    using Inh2::get_handle_at;
    using Inh2::get_handle_named;
    using Inh2::get_handles;
    using Inh2::get_names;
    using Inh2::make_default;
    using Inh2::make_emplace;
    using Inh2::add_default;
    using Inh2::add_emplace;
    using Inh2::add;
    using Inh2::remove;
    using Inh2::change_name;
    using Inh2::change_at;
    using Inh2::request_editor;
    using Inh2::request_focus;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Abstract_Project_Save_Interface
  //---------------------------------------------------------------------------
  class Abstract_Project_Save_Interface
  {
  public:
    // Special 6
    //============================================================
    virtual ~Abstract_Project_Save_Interface() = 0;

    // Virtuals
    //============================================================
    virtual void save() const = 0;
    virtual void load() = 0;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Abstract_Project_Path_Interface
  //---------------------------------------------------------------------------
  class Abstract_Project_Path_Interface
  {
  public:
    // Special 6
    //============================================================
    virtual ~Abstract_Project_Path_Interface() = 0;

    // Virtuals
    //============================================================
    // Data that is fixed on contruction.
    virtual QString name() const = 0;
    virtual QString location() const = 0;
    virtual QString filepath() const = 0;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Abstract_Project_History_Interface
  //---------------------------------------------------------------------------
  // The interface of the project that is not part of the sections.
  class Abstract_Project_History_Interface
  {
  public:
    // Special 6
    //============================================================
    virtual ~Abstract_Project_History_Interface() = 0;

    // Virtuals
    //============================================================
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

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Abstract_Project_Name_Interface
  //---------------------------------------------------------------------------
  // The interface of the project relating to data names.
  class Abstract_Project_Name_Interface
  {
  public:
    // Special 6
    //============================================================
    virtual ~Abstract_Project_Name_Interface() = 0;

    // Virtuals
    //============================================================
    // Does this name appear in the data?
    virtual bool has_name(QString const&) const = 0;
    // Get all the objects names in data order
    virtual std::vector<QString> get_all_names() const = 0;
    // Alter the supplied name so that it is unique among the existing data names
    virtual void fix_name(QString&) const = 0;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Abstract_Project_Signalbox_Interface
  //---------------------------------------------------------------------------
  // The interface of the project that is not part of the sections.
  template <typename T, typename...Args>
  class Abstract_Project_Signalbox_Interface
  {
  public:
    // Special 6
    //============================================================
    virtual ~Abstract_Project_Signalbox_Interface() = 0;

    // Virtuals
    //============================================================
    // Add an object that will rely on the Project's signals. If nulltpr, nothing happens.
    virtual void add_signalbox(Abstract_Signalbox<T,Args...>* a_signalbox) = 0;
    // Remove an object that will rely on the Project's signals. If nulltpr, nothing happens.
    virtual void remove_signalbox(Abstract_Signalbox<T,Args...>* a_signalbox) = 0;
    // Clear all the signalboxes so that nothing relies on changes to this.
    virtual void clear_signalboxes() = 0;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Abstract_Project_Chained_Interface<T,Args...>
  //---------------------------------------------------------------------------
  // Inheritance is private because we don't want to be splitting this up...
  template <typename T, typename...Args>
  class Abstract_Project_Chained_Interface:
      //protected virtual Abstract_Project_Save_Interface,
      //protected virtual Abstract_Project_Path_Interface,
      //protected virtual Abstract_Project_History_Interface,
      //protected virtual Abstract_Project_Name_Interface,
      //protected virtual Abstract_Project_Signalbox_Interface<T,Args...>,
      protected virtual Abstract_Chained_Interface<T,Args...>
  {
  public:
    // Typedefs
    //============================================================
    using Section_Typelist = flamingo::typelist<T,Args...>;
    using Signalbox_Type = Abstract_Signalbox<T,Args...>;

    // Special 6
    //============================================================
    ~Abstract_Project_Chained_Interface() override = 0;

    // Virtuals
    //============================================================
    virtual void save() const = 0;
    virtual void load() = 0;

    // Data that is fixed on contruction.
    virtual QString name() const = 0;
    virtual QString location() const = 0;
    virtual QString filepath() const = 0;

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

    // Does this name appear in the data?
    virtual bool has_name(QString const&) const = 0;
    // Get all the objects names in data order
    virtual std::vector<QString> get_all_names() const = 0;
    // Alter the supplied name so that it is unique among the existing data names
    virtual void fix_name(QString&) const = 0;

    // Virtuals
    //============================================================
    // Add an object that will rely on the Project's signals. If nulltpr, nothing happens.
    virtual void add_signalbox(Abstract_Signalbox<T,Args...>* a_signalbox) = 0;
    // Remove an object that will rely on the Project's signals. If nulltpr, nothing happens.
    virtual void remove_signalbox(Abstract_Signalbox<T,Args...>* a_signalbox) = 0;
    // Clear all the signalboxes so that nothing relies on changes to this.
    virtual void clear_signalboxes() = 0;

    /*
    using Abstract_Project_Save_Interface::save;
    using Abstract_Project_Save_Interface::load;

    using Abstract_Project_Path_Interface::name;
    using Abstract_Project_Path_Interface::location;
    using Abstract_Project_Path_Interface::filepath;

    using Abstract_Project_History_Interface::can_undo;
    using Abstract_Project_History_Interface::can_redo;
    using Abstract_Project_History_Interface::undo_count;
    using Abstract_Project_History_Interface::redo_count;
    using Abstract_Project_History_Interface::undo;
    using Abstract_Project_History_Interface::redo;
    using Abstract_Project_History_Interface::clear_history;

    using Abstract_Project_Name_Interface::has_name;
    using Abstract_Project_Name_Interface::get_all_names;
    using Abstract_Project_Name_Interface::fix_name;

    using Abstract_Project_Signalbox_Interface<T,Args...>::add_signalbox;
    using Abstract_Project_Signalbox_Interface<T,Args...>::remove_signalbox;
    using Abstract_Project_Signalbox_Interface<T,Args...>::clear_signalboxes;
    */
    // All of the following will have an overload for each type
    using Abstract_Chained_Interface<T,Args...>::is_empty;
    using Abstract_Chained_Interface<T,Args...>::not_empty;
    using Abstract_Chained_Interface<T,Args...>::count;
    using Abstract_Chained_Interface<T,Args...>::has_handle;
    using Abstract_Chained_Interface<T,Args...>::has_handle_named;
    //using Abstract_Chained_Interface<T,Args...>::fix_name;
    using Abstract_Chained_Interface<T,Args...>::get_handle_at;
    using Abstract_Chained_Interface<T,Args...>::get_handle_named;
    using Abstract_Chained_Interface<T,Args...>::get_handles;
    using Abstract_Chained_Interface<T,Args...>::get_names;
    using Abstract_Chained_Interface<T,Args...>::make_default;
    using Abstract_Chained_Interface<T,Args...>::make_emplace;
    using Abstract_Chained_Interface<T,Args...>::add_default;
    using Abstract_Chained_Interface<T,Args...>::add_emplace;
    using Abstract_Chained_Interface<T,Args...>::add;
    using Abstract_Chained_Interface<T,Args...>::remove;
    using Abstract_Chained_Interface<T,Args...>::change_name;
    // change_at has an overload for each member for each type.
    using Abstract_Chained_Interface<T,Args...>::change_at;
    using Abstract_Chained_Interface<T,Args...>::request_editor;
    using Abstract_Chained_Interface<T,Args...>::request_focus;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Abstract_Project_Interface
  //---------------------------------------------------------------------------
  // Factory function to make a type that implements this interface.

  std::unique_ptr<Abstract_Project_Interface> make_project_interface(Project_Data&& a_data);
}

#endif // SAK_ABSTRACT_PROJECT_INTERFACE_HPP
