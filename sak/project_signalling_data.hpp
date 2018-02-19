#ifndef SAK_PROJECT_SIGNALLING_DATA_HPP
#define SAK_PROJECT_SIGNALLING_DATA_HPP

#ifndef SAK_PROJECT_SIGNALLING_DATA_FWD_HPP
#include "project_signalling_data_fwd.hpp"
#endif

#ifndef SAK_TAG_FWD_HPP
#include "tag_fwd.hpp"
#endif

#ifndef SAK_HANDLE_HPP
#include "handle.hpp"
#endif

#ifndef SAK_PROJECT_HANDLE_DATA_HPP
#include "project_handle_data.hpp"
#endif

#ifndef SAK_PROJECT_SIGNALBOX_DATA_HPP
#include "project_signalbox_data.hpp"
#endif

#ifndef SAK_PROJECT_HANDLE_FACTORY_HPP
#include "project_handle_factory.hpp"
#endif

#ifndef FLAMINGO_TYPELIST_HPP
#include <flamingo/typelist.hpp>
#endif

#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif

#ifndef INCLUDE_STD_VECTOR
#define INCLUDE_STD_VECTOR
#include <vector>
#endif

#ifndef INCLUDE_QT_QSTRING
#define INCLUDE_QT_QSTRING
#include <QString>
#endif

namespace sak
{
  namespace internal
  {
    //---------------------------------------------------------------------------
    // Project_Signalling_Data_Part_Imp<List, Index, End>
    //---------------------------------------------------------------------------
    // Declaration and default arguments for the template class that builds the
    // template chain.
    template
    <
      typename T_List,
      std::size_t T_List_Index = 0,
      std::size_t T_List_Last = (flamingo::typelist_size_v<T_List> - 1)//,
      //std::size_t T_Member_Index = 0,
      //std::size_t T_Member_Last = (Class_Def_Size_v<flamingo::typelist_at_t<T_List,T_List_Index>> - 1 )
    >
    class Project_Signalling_Data_Part_Imp;

    //------------------------------------------------------------------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    // Project_Signalling_Data_Part_Imp<List, Index, End>
    //---------------------------------------------------------------------------
    // For a type that isn't the last member or the type at the end of the list.
    template <std::size_t LI, std::size_t LL, typename...Args>
    class Project_Signalling_Data_Part_Imp<flamingo::typelist<Args...>,LI,LL> :
        public Project_Signalling_Data_Part_Imp<flamingo::typelist<Args...>,LI+1,LL>
    {
      // Typedefs
      //============================================================
      using Inh = Project_Signalling_Data_Part_Imp<flamingo::typelist<Args...>,LI+1,LL>;

      using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,LI>;
      using Data_Type = Data<Type>;
      using Handle_Type = Handle<Type>;
      using Tag_Type = Tag<Type>;
      //static constexpr std::size_t const index = MI;
      //using Index_Tag_Type = Index_Tag<index>;
      //using Member_Value_Type = Data_Member_Value_Type<index,Data_Type>;

      static_assert(Class_Def_Size_v<Type> != 0, "Cannot use data with no members.");
      static_assert(Class_Def_Size_v<Type> == (ML+1), "Bad last index.");

    public:
      // Special 6
      //============================================================
      Project_Signalling_Data_Part_Imp();
      ~Project_Signalling_Data_Part_Imp();

      Project_Signalling_Data_Part_Imp(Project_Signalling_Data_Part_Imp const&);
      Project_Signalling_Data_Part_Imp& operator=(Project_Signalling_Data_Part_Imp const&);

      Project_Signalling_Data_Part_Imp(Project_Signalling_Data_Part_Imp &&);
      Project_Signalling_Data_Part_Imp& operator=(Project_Signalling_Data_Part_Imp &&);

      // Interface
      //============================================================

      // Handle Interface
      //------------------------------------------------------------
      // Are there any objects in this Project?
      bool is_empty(Tag_Type&&) const;

      // How many objects are in this Project?
      std::size_t count(Tag_Type&&) const;

      // Does this handle appear in the data?
      bool has_handle(Handle_Type const&) const;

      // Does this name appear in the data?
      bool has_handle_named(Tag_Type&&, QString const&) const;

      // Get the handle at this index. If the index is invalid a null handle is returned.
      Handle_Type get_handle_at(Tag_Type&&, std::size_t a_index) const;

      // Get the handle with this name. If the name is invalid a null handle is returned.
      Handle_Type get_handle_named(Tag_Type&&, QString const&) const;

      // Get all the handles in data order
      std::vector<Handle_Type> get_handles(Tag_Type&&) const;

      // Get all the handles names in data order
      std::vector<QString> get_names(Tag_Type&&) const;

      // Editing Interface - these may result in signals
      //------------------------------------------------------------
      // Undoable add a new object made using the default parameters. The name will be modified if it is
      // currently in use by another object. Return true if the operation resulted in an undoable command.
      bool add_default(Tag_Type&&, Signal_Source a_source);

      // Undoable add a new object using the supplied data. This data is assigned a new handle. The name will
      // be modified if it is currently in use by another object. Return true if the operationn resulted in an undoable command.
      bool add_emplace(Signal_Source a_source, Data_Type&& a_data);

      // Undoable add a new object using the supplied handle. The name will be modified if it is currently in
      // use by another object. Return true if the operation resulted in an undoable command. If this handle
      // is invalid or already in the data then nothing happens and returns false.
      bool add(Signal_Source a_source, Handle_Type const& a_handle);

      // Undoable remove object. Return true if the operation resulted in an undoable command. If this handle
      // is invalid or already in the data then nothing happens and returns false. Handle data is not deleted
      // until the last handle for it is deleted.
      bool remove(Signal_Source a_source, Handle_Type const& a_handle);

      // Undoable change a handles name. Returns true if this call results in a change being made.
      // If the name supplied is already in use then the supplied name will be altered.
      bool change_name(Signal_Source a_source, Handle_Type const& a_handle, QString const& a_name);

      // Undoable change an object's member value. Returns true if this call results in a change being made.
      // Does nothing and returns false if this handle is invalid or not in the data, or if the supplied value
      // doesn't result in data being changed.
      //bool change_data_at(Index_Tag_Type&&, Signal_Source a_source, Handle_Type const& a_handle, Member_Value_Type const& a_value);

      // Request that the editor for this file be opened or switched to.
      void request_editor(Signal_Source a_source, Handle_Type const& a_handle);

      // Request that the focus change to this object.
      void request_outliner(Signal_Source a_source, Handle_Type const& a_handle);

      // Factory Interface
      //------------------------------------------------------------
      // The default name of handles made by this.
      QString default_name(Tag_Type&&) const;

      // Make a null handle.
      Handle_Type make_null(Tag_Type&&) const;

      // Make a handle with data that is default initialised and has
      // the default new name.
      Handle_Type make_default(Tag_Type&&) const;

      // Make a handle with the supplied data. If the name is empty
      // it will be given the default new name.
      Handle_Type make_emplace(Data_Type&& a_data) const;

      using Inh::is_empty;
      using Inh::count;
      using Inh::has_handle;
      using Inh::has_handle_at;
      using Inh::get_handle_named;
      using Inh::get_handles;
      using Inh::get_names;

      using Inh::add_default;
      using Inh::add_emplace;
      using Inh::add;
      using Inh::remove;
      using Inh::change_name;
      using Inh::request_editor;
      using Inh::request_outliner;

      using Inh::default_name;
      using Inh::make_null;
      using Inh::make_default;
      using Inh::make_emplace;

    protected:
      // Internal Interface
      //============================================================
      // Access the factory so other parts can use it.
      using Inh::factory;
      using Inh::cfactory;

      // Access the handles for direct manipulation.
      using Inh::handle_data;
      using Inh::chandle_data;

      // Access the signalboxes so signals can be emitted.
      using Inh::signalbox_data;
      using Inh::csignalbox_data;
    };

    //------------------------------------------------------------------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    // Project_Signalling_Data_Part_Imp<List, End, End>
    //---------------------------------------------------------------------------
    // For a type that isn't at the end of the list.
    template <std::size_t End, typename...Args>
    class Project_Signalling_Data_Part_Imp<flamingo::typelist<Args...>,End,End>
    {
      // Typedefs
      //============================================================
      using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,End>;
      using Handle_Type = Handle<Type>;
      using Data_Type = Data<Type>;
      using Tag_Type = Tag<Type>;

    public:
      using Signalbox_Type = typename Project_Signalbox_Data_Imp<Args...>::Signalbox_Type;

      // Special 6
      //============================================================
      Project_Signalling_Data_Part_Imp();
      ~Project_Signalling_Data_Part_Imp();

      Project_Signalling_Data_Part_Imp(Project_Signalling_Data_Part_Imp const&);
      Project_Signalling_Data_Part_Imp& operator=(Project_Signalling_Data_Part_Imp const&);

      Project_Signalling_Data_Part_Imp(Project_Signalling_Data_Part_Imp &&);
      Project_Signalling_Data_Part_Imp& operator=(Project_Signalling_Data_Part_Imp &&);

      // Interface
      //============================================================

      // Names Interface
      //------------------------------------------------------------
      // Does this name appear in the data?
      bool has_name(QString const& a_name) const;
      // Get all the objects names in alphabetical order. The true
      // types that are associated with the names are ignored.
      std::vector<QString> get_all_names() const;
      // Alter the supplied name so that it is unique among the
      // existing data names.
      void fix_name(QString& a_name) const;

      // Signalbox Interface
      //------------------------------------------------------------
      // Add an object that will rely on the Project's signals. If nulltpr, nothing happens.
      void add_signalbox(Signalbox_Type* a_signalbox);

      // Remove an object that will rely on the Project's signals. If nulltpr, nothing happens.
      void remove_signalbox(Signalbox_Type* a_signalbox);

      // Clear all the signalboxes so that nothing relies on changes to this.
      void clear_signalboxes();

      // Handle Interface
      //------------------------------------------------------------
      // Are there any objects in this Project?
      bool is_empty(Tag_Type&&) const;

      // How many objects are in this Project?
      std::size_t count(Tag_Type&&) const;

      // Does this handle appear in the data?
      bool has_handle(Handle_Type const&) const;

      // Does this name appear in the data?
      bool has_handle_named(Tag_Type&&, QString const&) const;

      // Get the handle at this index. If the index is invalid a null handle is returned.
      Handle_Type get_handle_at(Tag_Type&&, std::size_t a_index) const;

      // Get the handle with this name. If the name is invalid a null handle is returned.
      Handle_Type get_handle_named(Tag_Type&&, QString const&) const;

      // Get all the handles in data order
      std::vector<Handle_Type> get_handles(Tag_Type&&) const;

      // Get all the handles names in data order
      std::vector<QString> get_names(Tag_Type&&) const;

      // Editing Interface - these may result in signals
      //------------------------------------------------------------
      // Undoable add a new object made using the default parameters. The name will be modified if it is
      // currently in use by another object. Return true if the operation resulted in an undoable command.
      bool add_default(Tag_Type&&, Signal_Source a_source);

      // Undoable add a new object using the supplied data. This data is assigned a new handle. The name will
      // be modified if it is currently in use by another object. Return true if the operationn resulted in an undoable command.
      bool add_emplace(Signal_Source a_source, Data_Type&& a_data);

      // Undoable add a new object using the supplied handle. The name will be modified if it is currently in
      // use by another object. Return true if the operation resulted in an undoable command. If this handle
      // is invalid or already in the data then nothing happens and returns false.
      bool add(Signal_Source a_source, Handle_Type const& a_handle);

      // Undoable remove object. Return true if the operation resulted in an undoable command. If this handle
      // is invalid or already in the data then nothing happens and returns false. Handle data is not deleted
      // until the last handle for it is deleted.
      bool remove(Signal_Source a_source, Handle_Type const& a_handle);

      // Undoable change a handles name. Returns true if this call results in a change being made.
      // If the name supplied is already in use then the supplied name will be altered.
      bool change_name(Signal_Source a_source, Handle_Type const& a_handle, QString const& a_name);

      // Undoable change an object's member value. Returns true if this call results in a change being made.
      // Does nothing and returns false if this handle is invalid or not in the data, or if the supplied value
      // doesn't result in data being changed.
      //bool change_data_at(Index_Tag_Type&&, Signal_Source a_source, Handle_Type const& a_handle, Member_Value_Type const& a_value);

      // Request that the editor for this file be opened or switched to.
      void request_editor(Signal_Source a_source, Handle_Type const& a_handle);

      // Request that the focus change to this object.
      void request_outliner(Signal_Source a_source, Handle_Type const& a_handle);

      // Factory Interface
      //------------------------------------------------------------
      // The default name of handles made by this.
      QString default_name(Tag_Type&&) const;

      // Make a null handle.
      Handle_Type make_null(Tag_Type&&) const;

      // Make a handle with data that is default initialised and has
      // the default new name.
      Handle_Type make_default(Tag_Type&&) const;

      // Make a handle with the supplied data. If the name is empty
      // it will be given the default new name.
      Handle_Type make_emplace(Data_Type&& a_data) const;

    protected:
      // Internal Interface
      //============================================================
      // Access the factory so other parts can use it.
      Project_Handle_Factory_Imp<Args...>& factory(Tag_Type&&);
      Project_Handle_Factory_Imp<Args...> const& cfactory(Tag_Type&&) const;

      // Access the handles for direct manipulation.
      Project_Handle_Data_Imp<Args...>& handle_data(Tag_Type&&);
      Project_Handle_Data_Imp<Args...> const& chandle_data(Tag_Type&&) const;

      // Access the signalboxes so signals can be emitted.
      Project_Signalbox_Data_Imp<Args...>& signalbox_data();
      Project_Signalbox_Data_Imp<Args...>const & csignalbox_data() const;
    private:
      // Data Members
      //============================================================
      Project_Handle_Factory_Imp<Args...> m_handle_factory;
      Project_Handle_Data_Imp<Args...> m_handle_data;
      Project_Signalbox_Data_Imp<Args...> m_signalbox_data;
    };

    //------------------------------------------------------------------------------------------------------------------------------------------------------
    // Now add the members
    //---------------------------------------------------------------------------
    // Project_Signalling_Data_Member_Part_Imp<List, LI, LL, MI, ML>
    //---------------------------------------------------------------------------
    // Declaration and default arguments for the template class that builds the
    // template chain.
    template
    <
      typename T_List,
      std::size_t T_List_Index = 0,
      std::size_t T_List_Last = (flamingo::typelist_size_v<T_List> - 1),
      std::size_t T_Member_Index = 0,
      std::size_t T_Member_Last = (Class_Def_Size_v<flamingo::typelist_at_t<T_List,T_List_Index>> - 1 )
    >
    class Project_Signalling_Data_Member_Part_Imp;

    //------------------------------------------------------------------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    // Project_Signalling_Data_Member_Part_Imp<List,LI,LL,MI,ML>
    //---------------------------------------------------------------------------
    // For a member that isn't the last in a type that isn't the last in the list.
    template <std::size_t LI, std::size_t LL, std::size_t MI, std::size_t ML, typename...Args>
    class Project_Signalling_Data_Member_Part_Imp<flamingo::typelist<Args...>,LI,LL,MI,ML> :
        public Project_Signalling_Data_Member_Part_Imp<flamingo::typelist<Args...>,LI,LL,MI+1,ML>
    {
      using Inh = Project_Signalling_Data_Member_Part_Imp<flamingo::typelist<Args...>,LI,LL,MI+1,ML>;
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
      Project_Signalling_Data_Member_Part_Imp();
      ~Project_Signalling_Data_Member_Part_Imp();

      Project_Signalling_Data_Member_Part_Imp(Project_Signalling_Data_Member_Part_Imp const&);
      Project_Signalling_Data_Member_Part_Imp& operator=(Project_Signalling_Data_Member_Part_Imp const&);

      Project_Signalling_Data_Member_Part_Imp(Project_Signalling_Data_Member_Part_Imp &&);
      Project_Signalling_Data_Member_Part_Imp& operator=(Project_Signalling_Data_Member_Part_Imp &&);

      // Interface
      //============================================================

      // Undoable change an object's member value. Returns true if this call results in a change being made.
      // Does nothing and returns false if this handle is invalid or not in the data, or if the supplied value
      // doesn't result in data being changed.
      bool change_data_at(Index_Tag_Type&&, Signal_Source a_source, Handle_Type const& a_handle, Member_Value_Type const& a_value);
      using Inh::change_data_at;

    protected:
      // Internal Interface
      //============================================================
      // Access the factory so other parts can use it.
      using Inh::factory;
      using Inh::cfactory;

      // Access the handles for direct manipulation.
      using Inh::handle_data;
      using Inh::chandle_data;

      // Access the signalboxes so signals can be emitted.
      using Inh::signalbox_data;
      using Inh::csignalbox_data;
    };

    //------------------------------------------------------------------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    // Project_Signalling_Data_Member_Part_Imp<List,LI,LL,ML,ML>
    //---------------------------------------------------------------------------
    // For the last member in a type that isn't the last in the list.
    template <std::size_t LI, std::size_t LL, std::size_t ML, typename...Args>
    class Project_Signalling_Data_Member_Part_Imp<flamingo::typelist<Args...>,LI,LL,ML,ML> :
        public Project_Signalling_Data_Member_Part_Imp<flamingo::typelist<Args...>,LI+1>
        // The rest of the parameters should default correctly
    {
      using Inh = Project_Signalling_Data_Member_Part_Imp<flamingo::typelist<Args...>,LI+1>;
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
      Project_Signalling_Data_Member_Part_Imp();
      ~Project_Signalling_Data_Member_Part_Imp();

      Project_Signalling_Data_Member_Part_Imp(Project_Signalling_Data_Member_Part_Imp const&);
      Project_Signalling_Data_Member_Part_Imp& operator=(Project_Signalling_Data_Member_Part_Imp const&);

      Project_Signalling_Data_Member_Part_Imp(Project_Signalling_Data_Member_Part_Imp &&);
      Project_Signalling_Data_Member_Part_Imp& operator=(Project_Signalling_Data_Member_Part_Imp &&);

      // Interface
      //============================================================

      // Undoable change an object's member value. Returns true if this call results in a change being made.
      // Does nothing and returns false if this handle is invalid or not in the data, or if the supplied value
      // doesn't result in data being changed.
      bool change_data_at(Index_Tag_Type&&, Signal_Source a_source, Handle_Type const& a_handle, Member_Value_Type const& a_value);
      using Inh::change_data_at;

    protected:
      // Internal Interface
      //============================================================
      // Access the factory so other parts can use it.
      using Inh::factory;
      using Inh::cfactory;

      // Access the handles for direct manipulation.
      using Inh::handle_data;
      using Inh::chandle_data;

      // Access the signalboxes so signals can be emitted.
      using Inh::signalbox_data;
      using Inh::csignalbox_data;
    };

    //------------------------------------------------------------------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    // Project_Signalling_Data_Member_Part_Imp<List,LL,LL,ML,ML>
    //---------------------------------------------------------------------------
    // For the last member in the last type.
    template <std::size_t LL, std::size_t ML, typename...Args>
    class Project_Signalling_Data_Member_Part_Imp<flamingo::typelist<Args...>,LL,LL,ML,ML> :
        public Project_Signalling_Data_Part_Imp<flamingo::typelist<Args...>> // now all the data
    {
      using Inh = Project_Signalling_Data_Part_Imp<flamingo::typelist<Args...>>;
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
      Project_Signalling_Data_Member_Part_Imp();
      ~Project_Signalling_Data_Member_Part_Imp();

      Project_Signalling_Data_Member_Part_Imp(Project_Signalling_Data_Member_Part_Imp const&);
      Project_Signalling_Data_Member_Part_Imp& operator=(Project_Signalling_Data_Member_Part_Imp const&);

      Project_Signalling_Data_Member_Part_Imp(Project_Signalling_Data_Member_Part_Imp &&);
      Project_Signalling_Data_Member_Part_Imp& operator=(Project_Signalling_Data_Member_Part_Imp &&);

      // Interface
      //============================================================

      // Undoable change an object's member value. Returns true if this call results in a change being made.
      // Does nothing and returns false if this handle is invalid or not in the data, or if the supplied value
      // doesn't result in data being changed.
      bool change_data_at(Index_Tag_Type&&, Signal_Source a_source, Handle_Type const& a_handle, Member_Value_Type const& a_value);

    protected:
      // Internal Interface
      //============================================================
      // Access the factory so other parts can use it.
      using Inh::factory;
      using Inh::cfactory;

      // Access the handles for direct manipulation.
      using Inh::handle_data;
      using Inh::chandle_data;

      // Access the signalboxes so signals can be emitted.
      using Inh::signalbox_data;
      using Inh::csignalbox_data;
    };
  } // namespace internal

  //---------------------------------------------------------------------------
  // Project_Signalling_Data_Imp<T,Args...>
  //---------------------------------------------------------------------------

  template <typename T, typename...Args>
  class Project_Signalling_Data_Imp :
      protected internal::Project_Signalling_Data_Member_Part_Imp<flamingo::typelist<T,Args...>>
  {
    // Typedefs
    //============================================================
    using Inh = internal::Project_Signalling_Data_Member_Part_Imp<flamingo::typelist<T,Args...>>;
  public:
    // Special 6
    //============================================================
    Project_Signalling_Data_Imp();
    ~Project_Signalling_Data_Imp();

    Project_Signalling_Data_Imp(Project_Signalling_Data_Imp const&);
    Project_Signalling_Data_Imp& operator=(Project_Signalling_Data_Imp const&);

    Project_Signalling_Data_Imp(Project_Signalling_Data_Imp &&);
    Project_Signalling_Data_Imp& operator=(Project_Signalling_Data_Imp &&);

    // Interface
    //============================================================
    // Names Interface
    //------------------------------------------------------------
    // Does this name appear in the data?
    //bool has_name(QString const& a_name) const;
    using Inh::has_name;

    // Get all the objects names in alphabetical order. The true
    // types that are associated with the names are ignored.
    //std::vector<QString> get_all_names() const;
    using Inh::get_all_names;

    // Alter the supplied name so that it is unique among the
    // existing data names.
    //void fix_name(QString& a_name) const;
    using Inh::fix_name;

    // Signalbox Interface
    //------------------------------------------------------------
    // Add an object that will rely on the Project's signals. If nulltpr, nothing happens.
    //void add_signalbox(Signalbox_Type* a_signalbox);
    using Inh::add_signalbox;

    // Remove an object that will rely on the Project's signals. If nulltpr, nothing happens.
    //void remove_signalbox(Signalbox_Type* a_signalbox);
    using Inh::remove_signalbox;

    // Clear all the signalboxes so that nothing relies on changes to this.
    //void clear_signalboxes();
    using Inh::clear_signalboxes;

    // Handle Interface
    //------------------------------------------------------------
    // Are there any objects in this Project?
    //bool is_empty(Tag_Type&&) const;
    using Inh::is_empty;

    // How many objects are in this Project?
    //std::size_t count(Tag_Type&&) const;
    using Inh::count;

    // Does this handle appear in the data?
    //bool has_handle(Handle_Type const&) const;
    using Inh::has_handle;

    // Does this name appear in the data?
    //bool has_handle_named(Tag_Type&&, QString const&) const;
    using Inh::has_handle_named;

    // Get the handle at this index. If the index is invalid a null handle is returned.
    //Handle_Type get_handle_at(Tag_Type&&, std::size_t a_index) const;
    using Inh::get_handle_at;

    // Get the handle with this name. If the name is invalid a null handle is returned.
    //Handle_Type get_handle_named(Tag_Type&&, QString const&) const;
    using Inh::get_handle_named;

    // Get all the handles in data order
    //std::vector<Handle_Type> get_handles(Tag_Type&&) const;
    using Inh::get_handles;

    // Get all the handles names in data order
    //std::vector<QString> get_names(Tag_Type&&) const;
    using Inh::get_names;

    // Editing Interface - these may result in signals
    //------------------------------------------------------------
    // Undoable add a new object made using the default parameters. The name will be modified if it is
    // currently in use by another object. Return true if the operation resulted in an undoable command.
    //bool add_default(Tag_Type&&, Signal_Source a_source);
    using Inh::add_default;

    // Undoable add a new object using the supplied data. This data is assigned a new handle. The name will
    // be modified if it is currently in use by another object. Return true if the operationn resulted in an undoable command.
    //bool add_emplace(Signal_Source a_source, Data_Type&& a_data);
    using Inh::add_emplace;

    // Undoable add a new object using the supplied handle. The name will be modified if it is currently in
    // use by another object. Return true if the operation resulted in an undoable command. If this handle
    // is invalid or already in the data then nothing happens and returns false.
    //bool add(Signal_Source a_source, Handle_Type const& a_handle);
    using Inh::add;

    // Undoable remove object. Return true if the operation resulted in an undoable command. If this handle
    // is invalid or already in the data then nothing happens and returns false. Handle data is not deleted
    // until the last handle for it is deleted.
    //bool remove(Signal_Source a_source, Handle_Type const& a_handle);
    using Inh::remove;

    // Undoable change a handles name. Returns true if this call results in a change being made.
    // If the name supplied is already in use then the supplied name will be altered.
    //bool change_name(Signal_Source a_source, Handle_Type const& a_handle, QString const& a_name);
    using Inh::change_name;

    // Undoable change an object's member value. Returns true if this call results in a change being made.
    // Does nothing and returns false if this handle is invalid or not in the data, or if the supplied value
    // doesn't result in data being changed.
    //bool change_data_at(Index_Tag_Type&&, Signal_Source a_source, Handle_Type const& a_handle, Member_Value_Type const& a_value);
    using Inh::change_data_at;

    // Request that the editor for this file be opened or switched to.
    //void request_editor(Signal_Source a_source, Handle_Type const& a_handle);
    using Inh::request_editor;

    // Request that the focus change to this object.
    //void request_outliner(Signal_Source a_source, Handle_Type const& a_handle);
    using Inh::request_outliner;

    // Factory Interface
    //------------------------------------------------------------
    // The default name of handles made by this.
    //QString default_name(Tag_Type&&) const;
    using Inh::default_name;

    // Make a null handle.
    //Handle_Type make_null(Tag_Type&&) const;
    using Inh::make_null;

    // Make a handle with data that is default initialised and has
    // the default new name.
    //Handle_Type make_default(Tag_Type&&) const;
    using Inh::make_default;

    // Make a handle with the supplied data. If the name is empty
    // it will be given the default new name.
    //Handle_Type make_emplace(Data_Type&& a_data) const;
    using Inh::make_emplace;

  };
  //------------------------------------------------------------------------------------------------------------------------------------------------------

} // namespace sak

#endif // SAK_PROJECT_SIGNALLING_DATA_HPP
