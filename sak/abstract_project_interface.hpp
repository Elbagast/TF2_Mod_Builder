#ifndef SAK_ABSTRACT_PROJECT_INTERFACE_HPP
#define SAK_ABSTRACT_PROJECT_INTERFACE_HPP

#ifndef SAK_ABSTRACT_PROJECT_INTERFACE_FWD_HPP
#include "abstract_project_interface_fwd.hpp"
#endif

#ifndef SAK_ABSTRACT_PROJECT_SIGNALBOX_FWD_HPP
#include "abstract_project_signalbox_fwd.hpp"
#endif

#ifndef SAK_SECTION_INTERFACE_FWD_HPP
#include "section_interface_fwd.hpp"
#endif

#ifndef SAK_HANDLE_FWD_HPP
#include "handle_fwd.hpp"
#endif

#ifndef SAK_TAG_FWD_HPP
#include "tag_fwd.hpp"
#endif

#ifndef SAK_SIGNAL_SOURCE_FWD_HPP
#include "signal_source_fwd.hpp"
#endif

#ifndef SAK_CLASS_DEFINITIONS_HPP
#include "class_definitions.hpp"
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

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  namespace internal
  {
    //---------------------------------------------------------------------------
    // Abstract_Project_Interface_Part_Imp<List,LI,LL,MI,ML>
    //---------------------------------------------------------------------------
    // Declaration and default arguments for the template class that builds the
    // template chain.
    template
    <
      typename T_List,
      std::size_t T_List_Index = 0,
      std::size_t T_List_Last = (flamingo::typelist_size_v<T_List> - 1 ),
      std::size_t T_Member_Index = 0,
      std::size_t T_Member_Last = (Class_Def_Size_v<flamingo::typelist_at_t<T_List,T_List_Index>> - 1 )
    >
    class Abstract_Project_Interface_Part_Imp;

    //------------------------------------------------------------------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    // Abstract_Project_Interface_Part_Imp<List,LI,LL,MI,ML>
    //---------------------------------------------------------------------------
    // For a member that isn't the last in a type that isn't the last in the list.
    template <std::size_t LI, std::size_t LL, std::size_t MI, std::size_t ML, typename...Args>
    class Abstract_Project_Interface_Part_Imp<flamingo::typelist<Args...>,LI,LL,MI,ML> :
        protected Abstract_Project_Interface_Part_Imp<flamingo::typelist<Args...>,LI,LL,MI+1,ML>
    {
      using Inh = Abstract_Project_Interface_Part_Imp<flamingo::typelist<Args...>,LI,LL,MI+1,ML>;
      using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,LI>;
      using Data_Type = Data<Type>;
      using Handle_Type = Handle<Type>;
      static constexpr std::size_t const index = MI;
      using Index_Tag_Type = Index_Tag<index>;
      using Member_Value_Type = Data_Member_Value_Type<index,Data_Type>;

      static_assert(Class_Def_Size_v<Type> != 0, "Cannot use data with no members.");
      static_assert(Class_Def_Size_v<Type> == (ML+1), "Bad last index.");
    public:

      // Special 6
      //============================================================
      ~Abstract_Project_Interface_Part_Imp() override = 0;

      // Interface
      //============================================================

      // Undoable change an object's member value. Returns true if this call results in a change being made.
      // Does nothing and returns false if this handle is invalid or not in the data, or if the supplied value
      // doesn't result in data being changed.
      virtual bool change_data_at(Index_Tag_Type&&, Signal_Source a_source, Handle_Type const& a_handle, Member_Value_Type const& a_value) = 0;

      using Inh::is_empty;
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
      using Inh::change_data_at;
      using Inh::request_editor;
      using Inh::request_outliner;
    };

    //------------------------------------------------------------------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    // Abstract_Project_Interface_Part_Imp<List,LI,LL,ML,ML>
    //---------------------------------------------------------------------------
    // For the last member in a type that isn't the last in the list.
    template <std::size_t LI, std::size_t LL, std::size_t ML, typename...Args>
    class Abstract_Project_Interface_Part_Imp<flamingo::typelist<Args...>,LI,LL,ML,ML> :
        protected Abstract_Project_Interface_Part_Imp<flamingo::typelist<Args...>,LI+1>
        // The rest of the parameters should default correctly
    {
      using Inh = Abstract_Project_Interface_Part_Imp<flamingo::typelist<Args...>,LI+1>;
      using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,LI>;
      using Data_Type = Data<Type>;
      using Handle_Type = Handle<Type>;
      using Tag_Type = Tag<Type>;
      static constexpr std::size_t const index = ML;
      using Index_Tag_Type = Index_Tag<index>;
      using Member_Value_Type = Data_Member_Value_Type<index,Data_Type>;

      static_assert(Class_Def_Size_v<Type> != 0, "Cannot use data with no members.");
      static_assert(Class_Def_Size_v<Type> == (ML+1), "Bad last index.");
    public:

      // Special 6
      //============================================================
      ~Abstract_Project_Interface_Part_Imp() override = 0;

      // Interface
      //============================================================

      // Are there any objects in this Project?
      virtual bool is_empty(Tag_Type&&) const = 0;
      // How many objects are in this Project?
      virtual std::size_t count(Tag_Type&&) const = 0;

      // Does this handle appear in the data?
      virtual bool has_handle(Handle_Type const&) const = 0;
      // Does this name appear in the data?
      virtual bool has_handle_named(Tag_Type&&, QString const&) const = 0;

      // Get the handle at this index. If the index is invalid a null handle is returned.
      virtual Handle_Type get_handle_at(Tag_Type&&, std::size_t a_index) const = 0;
      // Get the handle with this name. If the name is invalid a null handle is returned.
      virtual Handle_Type get_handle_named(Tag_Type&&, QString const&) const = 0;

      // Get all the handles in data order
      virtual std::vector<Handle_Type> get_handles(Tag_Type&&) const = 0;
      // Get all the handles names in data order
      virtual std::vector<QString> get_names(Tag_Type&&) const = 0;

      // Make a new object using the default parameters. Project's data management system owns it
      // but it is not part of the Project. Does not trigger any commands.
      virtual Handle_Type make_default(Tag_Type&&) const = 0;
      // Make a new object using the supplied data. Project's data management system owns it but
      // it is not part of the Project. Does not trigger any commands.
      virtual Handle_Type make_emplace(Data_Type&& a_data) const = 0;

      // Undoable add a new object made using the default parameters. The name will be modified if it is
      // currently in use by another object. Return true if the operation resulted in an undoable command.
      virtual bool add_default(Tag_Type&&, Signal_Source a_source) = 0;
      // Undoable add a new object using the supplied data. This data is assigned a new handle. The name will
      // be modified if it is currently in use by another object. Return true if the operationn resulted in an undoable command.
      virtual bool add_emplace(Signal_Source a_source, Data_Type&& a_data) = 0;
      // Undoable add a new object using the supplied handle. The name will be modified if it is currently in
      // use by another object. Return true if the operation resulted in an undoable command. If this handle
      // is invalid or already in the data then nothing happens and returns false.
      virtual bool add(Signal_Source a_source, Handle_Type const& a_handle) = 0;
      // Undoable remove object. Return true if the operation resulted in an undoable command. If this handle
      // is invalid or already in the data then nothing happens and returns false. Handle data is not deleted
      // until the last handle for it is deleted.
      virtual bool remove(Signal_Source a_source, Handle_Type const& a_handle) = 0;

      // Undoable change a handles name. Returns true if this call results in a change being made.
      // If the name supplied is already in use then the supplied name will be altered.
      virtual bool change_name(Signal_Source a_source, Handle_Type const& a_handle, QString const& a_name) = 0;

      // Undoable change an object's member value. Returns true if this call results in a change being made.
      // Does nothing and returns false if this handle is invalid or not in the data, or if the supplied value
      // doesn't result in data being changed.
      virtual bool change_data_at(Index_Tag_Type&&, Signal_Source a_source, Handle_Type const& a_handle, Member_Value_Type const& a_value) = 0;

      // Request that the editor for this file be opened or switched to.
      virtual void request_editor(Signal_Source a_source, Handle_Type const& a_handle) = 0;
      // Request that the focus change to this object.
      virtual void request_outliner(Signal_Source a_source, Handle_Type const& a_handle) = 0;


      using Inh::is_empty;
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
      using Inh::change_data_at;
      using Inh::request_editor;
      using Inh::request_outliner;
    };
    //------------------------------------------------------------------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    // Abstract_Project_Interface_Part_Imp<List,LL,LL,ML,ML>
    //---------------------------------------------------------------------------
    // For the last member in the last type.
    template <std::size_t LL, std::size_t ML, typename...Args>
    class Abstract_Project_Interface_Part_Imp<flamingo::typelist<Args...>,LL,LL,ML,ML>
    {
      using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,LL>;
      using Data_Type = Data<Type>;
      using Handle_Type = Handle<Type>;
      using Tag_Type = Tag<Type>;
      static constexpr std::size_t const index = ML;
      using Index_Tag_Type = Index_Tag<index>;
      using Member_Value_Type = Data_Member_Value_Type<index,Data_Type>;

      static_assert(Class_Def_Size_v<Type> != 0, "Cannot use data with no members.");
      static_assert(Class_Def_Size_v<Type> == (ML+1), "Bad last index.");
    public:

      // Special 6
      //============================================================
      virtual ~Abstract_Project_Interface_Part_Imp() = 0;

      // Interface
      //============================================================

      // Are there any objects in this Project?
      virtual bool is_empty(Tag_Type&&) const = 0;
      // How many objects are in this Project?
      virtual std::size_t count(Tag_Type&&) const = 0;

      // Does this handle appear in the data?
      virtual bool has_handle(Handle_Type const&) const = 0;
      // Does this name appear in the data?
      virtual bool has_handle_named(Tag_Type&&, QString const&) const = 0;

      // Get the handle at this index. If the index is invalid a null handle is returned.
      virtual Handle_Type get_handle_at(Tag_Type&&, std::size_t a_index) const = 0;
      // Get the handle with this name. If the name is invalid a null handle is returned.
      virtual Handle_Type get_handle_named(Tag_Type&&, QString const&) const = 0;

      // Get all the handles in data order
      virtual std::vector<Handle_Type> get_handles(Tag_Type&&) const = 0;
      // Get all the handles names in data order
      virtual std::vector<QString> get_names(Tag_Type&&) const = 0;

      // Make a new object using the default parameters. Project's data management system owns it
      // but it is not part of the Project. Does not trigger any commands.
      virtual Handle_Type make_default(Tag_Type&&) const = 0;
      // Make a new object using the supplied data. Project's data management system owns it but
      // it is not part of the Project. Does not trigger any commands.
      virtual Handle_Type make_emplace(Data_Type&& a_data) const = 0;

      // Undoable add a new object made using the default parameters. The name will be modified if it is
      // currently in use by another object. Return true if the operation resulted in an undoable command.
      virtual bool add_default(Tag_Type&&, Signal_Source a_source) = 0;
      // Undoable add a new object using the supplied data. This data is assigned a new handle. The name will
      // be modified if it is currently in use by another object. Return true if the operationn resulted in an undoable command.
      virtual bool add_emplace(Signal_Source a_source, Data_Type&& a_data) = 0;
      // Undoable add a new object using the supplied handle. The name will be modified if it is currently in
      // use by another object. Return true if the operation resulted in an undoable command. If this handle
      // is invalid or already in the data then nothing happens and returns false.
      virtual bool add(Signal_Source a_source, Handle_Type const& a_handle) = 0;
      // Undoable remove object. Return true if the operation resulted in an undoable command. If this handle
      // is invalid or already in the data then nothing happens and returns false. Handle data is not deleted
      // until the last handle for it is deleted.
      virtual bool remove(Signal_Source a_source, Handle_Type const& a_handle) = 0;

      // Undoable change a handles name. Returns true if this call results in a change being made.
      // If the name supplied is already in use then the supplied name will be altered.
      virtual bool change_name(Signal_Source a_source, Handle_Type const& a_handle, QString const& a_name) = 0;

      // Undoable change an object's member value. Returns true if this call results in a change being made.
      // Does nothing and returns false if this handle is invalid or not in the data, or if the supplied value
      // doesn't result in data being changed.
      virtual bool change_data_at(Index_Tag_Type&&, Signal_Source a_source, Handle_Type const& a_handle, Member_Value_Type const& a_value) = 0;

      // Request that the editor for this file be opened or switched to.
      virtual void request_editor(Signal_Source a_source, Handle_Type const& a_handle) = 0;
      // Request that the focus change to this object.
      virtual void request_outliner(Signal_Source a_source, Handle_Type const& a_handle) = 0;
    };

  } // namespace internal

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  template <typename T, typename...Args>
  class Abstract_Project_Interface_Imp :
      protected internal::Abstract_Project_Interface_Part_Imp<flamingo::typelist<T,Args...>>
  {
    using Inh = internal::Abstract_Project_Interface_Part_Imp<flamingo::typelist<T,Args...>>;
  public:
    // Typedefs
    //============================================================
    using Typelist_Type = flamingo::typelist<T,Args...>;
    using Signalbox_Type = Abstract_Project_Signalbox_Imp<T,Args...>;

    // Special 6
    //============================================================
    ~Abstract_Project_Interface_Imp() override = 0;

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

    // Add an object that will rely on the Project's signals. If
    // nulltpr or already present, nothing happens.
    virtual void add_signalbox(Signalbox_Type* a_signalbox) = 0;
    // Remove an object that will rely on the Project's signals. If
    // nulltpr or not present, nothing happens.
    virtual void remove_signalbox(Signalbox_Type* a_signalbox) = 0;
    // Clear all the signalboxes so that nothing relies on changes to this.
    virtual void clear_signalboxes() = 0;

    using Inh::is_empty;
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
    using Inh::change_data_at;
    using Inh::request_editor;
    using Inh::request_outliner;

    // Functions are as follows, with overloads for each Type in
    // the arguments <T,Args...>:
    //------------------------------------------------------------

    // Are there any objects in this Project?
    //virtual bool is_empty(Tag_Type&&) const = 0;

    // How many objects are in this Project?
    //virtual std::size_t count(Tag_Type&&) const = 0;

    // Does this handle appear in the data?
    //virtual bool has_handle(Handle_Type const&) const = 0;

    // Does this name appear in the data?
    //virtual bool has_handle_named(Tag_Type&&, QString const&) const = 0;

    // Get the handle at this index. If the index is invalid a null handle is returned.
    //virtual Handle_Type get_handle_at(Tag_Type&&, std::size_t a_index) const = 0;

    // Get the handle with this name. If the name is invalid a null handle is returned.
    //virtual Handle_Type get_handle_named(Tag_Type&&, QString const&) const = 0;

    // Get all the handles in data order
    //virtual std::vector<Handle_Type> get_handles(Tag_Type&&) const = 0;

    // Get all the handles names in data order
    //virtual std::vector<QString> get_names(Tag_Type&&) const = 0;

    // Make a new object using the default parameters. Project's data management system owns it
    // but it is not part of the Project. Does not trigger any commands.
    //virtual Handle_Type make_default(Tag_Type&&) const = 0;

    // Make a new object using the supplied data. Project's data management system owns it but
    // it is not part of the Project. Does not trigger any commands.
    //virtual Handle_Type make_emplace(Data_Type&& a_data) const = 0;

    // Undoable add a new object made using the default parameters. The name will be modified if it is
    // currently in use by another object. Return true if the operation resulted in an undoable command.
    //virtual bool add_default(Tag_Type&&, Signal_Source a_source) = 0;

    // Undoable add a new object using the supplied data. This data is assigned a new handle. The name will
    // be modified if it is currently in use by another object. Return true if the operationn resulted in an undoable command.
    //virtual bool add_emplace(Signal_Source a_source, Data_Type&& a_data) = 0;

    // Undoable add a new object using the supplied handle. The name will be modified if it is currently in
    // use by another object. Return true if the operation resulted in an undoable command. If this handle
    // is invalid or already in the data then nothing happens and returns false.
    //virtual bool add(Signal_Source a_source, Handle_Type const& a_handle) = 0;

    // Undoable remove object. Return true if the operation resulted in an undoable command. If this handle
    // is invalid or already in the data then nothing happens and returns false. Handle data is not deleted
    // until the last handle for it is deleted.
    //virtual bool remove(Signal_Source a_source, Handle_Type const& a_handle) = 0;

    // Undoable change a handles name. Returns true if this call results in a change being made.
    // If the name supplied is already in use then the supplied name will be altered.
    //virtual bool change_name(Signal_Source a_source, Handle_Type const& a_handle, QString const& a_name) = 0;

    // Undoable change an object's member value. Returns true if this call results in a change being made.
    // Does nothing and returns false if this handle is invalid or not in the data, or if the supplied value
    // doesn't result in data being changed.
    // For each member of a given T, where Index_Tag_Type is Index_Tag<Member_Index>.
    //virtual bool change_data_at(Index_Tag_Type&&, Signal_Source a_source, Handle_Type const& a_handle, Member_Value_Type const& a_value) = 0;

    // Request that the editor for this file be opened or switched to.
    //virtual void request_editor(Signal_Source a_source, Handle_Type const& a_handle) = 0;

    // Request that the focus change to this object.
    //virtual void request_outliner(Signal_Source a_source, Handle_Type const& a_handle) = 0;
  };
  //------------------------------------------------------------------------------------------------------------------------------------------------------


  //---------------------------------------------------------------------------
  // Abstract_Project_Interface
  //---------------------------------------------------------------------------
  // Factory function to make a type that implements this interface.

  //std::unique_ptr<Abstract_Project_Interface> make_project_interface(Project_Data&& a_data);


} // namespace sak

//------------------------------------------------------------------------------------------------------------------------------------------------------

template <std::size_t LI, std::size_t LL, std::size_t MI, std::size_t ML, typename...Args>
sak::internal::Abstract_Project_Interface_Part_Imp<flamingo::typelist<Args...>,LI,LL,MI,ML>::~Abstract_Project_Interface_Part_Imp() = default;

template <std::size_t LI, std::size_t LL, std::size_t ML, typename...Args>
sak::internal::Abstract_Project_Interface_Part_Imp<flamingo::typelist<Args...>,LI,LL,ML,ML>::~Abstract_Project_Interface_Part_Imp() = default;

template <std::size_t LL, std::size_t ML, typename...Args>
sak::internal::Abstract_Project_Interface_Part_Imp<flamingo::typelist<Args...>,LL,LL,ML,ML>::~Abstract_Project_Interface_Part_Imp() = default;

template <typename T, typename...Args>
sak::Abstract_Project_Interface_Imp<T,Args...>::~Abstract_Project_Interface_Imp() = default;

/*
Planning an implementation:
- Path read functions
  - Path data
- History functions
  - History data
- Handle read functions
  - Handle data
- Handle factory functions
  - Handle Factory
    - Name access
      - Handle data
- Handle edit functions
  - History data
  - Sending signals
    - Signalbox data
  - Name access
    - Handle data

Data dependencies:
- Path data
- History data
- Signalbox data
- Factory data
- Handle data<T>...

*/

#endif // SAK_ABSTRACT_PROJECT_INTERFACE_HPP
