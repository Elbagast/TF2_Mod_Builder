#ifndef SAK_PROJECT_INTERFACE_HPP
#define SAK_PROJECT_INTERFACE_HPP

#ifndef SAK_PROJECT_INTERFACE_FWD_HPP
#include "project_interface_fwd.hpp"
#endif

#ifndef SAK_ABSTRACT_PROJECT_INTERFACE_HPP
#include "abstract_project_interface.hpp"
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

#ifndef SAK_PROJECT_HANDLE_FACTORY_HPP
#include "project_handle_factory.hpp"
#endif

#ifndef SAK_PROJECT_HANDLE_DATA_HPP
#include "project_handle_data.hpp"
#endif

#ifndef SAK_PROJECT_SIGNALBOX_DATA_HPP
#include "project_signalbox_data.hpp"
#endif

#ifndef SAK_COMMAND_HISTORY_HPP
#include "command_history.hpp"
#endif

#ifndef SAK_PROJECT_COMMANDS_HPP
#include "project_commands.hpp"
#endif

#ifndef INCLUDE_QT_QSTRING
#define INCLUDE_QT_QSTRING
#include <QString>
#endif

#ifndef INCLUDE_QT_QFILEINFO
#define INCLUDE_QT_QFILEINFO
#include <QFileInfo>
#endif

#ifndef INCLUDE_QT_QDIR
#define INCLUDE_QT_QDIR
#include <QDir>
#endif

namespace sak 
{
  //---------------------------------------------------------------------------
  // Section_Interface_Imp<List,LI,LL>
  //---------------------------------------------------------------------------
  // Declaration and default arguments for the template class that builds the
  // template chain.
  template
  <
    typename T_List,
    std::size_t T_List_Index = 0,
    std::size_t T_List_Size = (flamingo::typelist_size_v<T_List>) // for list size N, is N
  >
  class Section_Interface_Imp;

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Section_Interface_Imp<List,LI,LS>
  //---------------------------------------------------------------------------
  // For a type in the list, build its interface.

  template <std::size_t LI, std::size_t LS, typename...Args>
  class Section_Interface_Imp<flamingo::typelist<Args...>,LI,LS> :
      public Section_Interface_Imp<flamingo::typelist<Args...>,LI+1>
  {
    using Inh = Section_Interface_Imp<flamingo::typelist<Args...>,LI+1>;
    using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,LI>;
    using Data_Type = Data<Type>;
    using ID_Type = ID<Type>;
    using Handle_Type = Handle<Type>;
    using Tag_Type = Tag<Type>;

    static_assert(Class_Def_Size_v<Type> != 0, "Cannot use data with no members.");
  public:

    // Special 6
    //============================================================
    Section_Interface_Imp();
    ~Section_Interface_Imp() override;

    Section_Interface_Imp(Section_Interface_Imp const&) = delete;
    Section_Interface_Imp& operator=(Section_Interface_Imp const&) = delete;

    Section_Interface_Imp(Section_Interface_Imp &&);
    Section_Interface_Imp& operator=(Section_Interface_Imp &&);

    // Interface
    //============================================================

    // Collection Interface
    //------------------------------------------------------------
    // Are there any objects in this Project?
    bool is_empty(Tag_Type&&) const override final;

    // How many objects are in this Project?
    std::size_t count(Tag_Type&&) const override final;

    // Does this id appear in the data?
    bool has(ID_Type const& a_id) const override final;

    // Does this name appear in the data?
    bool has_name(Tag_Type&&, QString const&) const override final;

    // Get the id at this index. If the index is invalid a null id is returned.
    ID_Type get_at(Tag_Type&&, std::size_t a_index) const override final;

    // Get the id with this name. If the name is invalid a null id is returned.
    ID_Type get_named(Tag_Type&&, QString const&) const override final;

    // Get all the ids in data order
    std::vector<ID_Type> get_ids(Tag_Type&&) const override final;

    // Get all the handles names in data order
    std::vector<QString> get_names(Tag_Type&&) const override final;

    // Data Interface
    //------------------------------------------------------------
    // Attempt to get the index of the data associated with the supplied id. This is the current
    // position in the project's collection of data for this type of index. If the id is valid,
    // the returned pair consists of true and the index. If the id is null or invalid, the
    // returned pair consists of false and zero.
    std::size_t get_index(ID_Type const& a_id) const override final;

    // Attempt to get the name for the data associated with the supplied id. If the id is valid,
    // the returned pair consists of true and the name value. If the id is null or invalid, the
    // returned pair consists of false and an empty string.
    QString get_name(ID_Type const& a_id) const override final;

    // Data Editing Interface
    //------------------------------------------------------------
    // Attempt an undoable change to the name of the data associated with the supplied id. If
    // the id is valid and the supplied value results in a change to the data, signals are emitted
    // telling everything to update this name, and true is returned. If the id is null or
    // invalid, nothing happens and false is returned. Success does not indicate that the name
    // is set to what has been supplied, but that the name has changed.
    bool try_set_name(Signal_Source a_source, ID_Type const& a_id, QString const& a_name) override final;

    // Collection Editing Interface
    //------------------------------------------------------------
    // Undoable add a new object made using the default parameters. Returns the id of the new
    // data.
    ID_Type add_default(Tag_Type&&, Signal_Source a_source) override final;

    // Undoable add a new object using the supplied handle. The name will be modified if it is currently in
    // use by another object. Return true if the operation resulted in an undoable command. If this handle
    // is invalid or already in the data then nothing happens and returns false.
    //bool try_add(Signal_Source a_source, ID_Type const& a_id) override final;

    // Undoable remove object. Return true if the operation resulted in an undoable command. If this handle
    // is invalid or already in the data then nothing happens and returns false. Handle data is not deleted
    // until the last handle for it is deleted.
    bool try_remove(Signal_Source a_source, ID_Type const& a_id) override final;

    // Request that the editor for this file be opened or switched to.
    bool try_request_editor(Signal_Source a_source, ID_Type const& a_id) override final;

    // Request that the focus change to this object.
    bool try_request_outliner(Signal_Source a_source, ID_Type const& a_id) override final;

  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Section_Interface_Imp<List,LS,LS>
  //---------------------------------------------------------------------------
  // At the end of the list inherit the abstract interface. This bit is also
  // where all the data goes so everything that inherits it can use it.

  template <std::size_t LS, typename...Args>
  class Section_Interface_Imp<flamingo::typelist<Args...>,LS,LS> :
      public Abstract_Project_Interface_Imp<Args...>
  {
    using Inh = Abstract_Project_Interface_Imp<Args...>;
  public:
    // Special 6
    //============================================================
    Section_Interface_Imp();
    ~Section_Interface_Imp() override;

    Section_Interface_Imp(Section_Interface_Imp const&) = delete;
    Section_Interface_Imp& operator=(Section_Interface_Imp const&) = delete;

    Section_Interface_Imp(Section_Interface_Imp &&);
    Section_Interface_Imp& operator=(Section_Interface_Imp &&);

  protected:
    // Internal Interface
    //============================================================
    // Access to the data members for all the classes that inherit
    // this.

    Project_Handle_Factory_Imp<Args...>& get_handle_factory();
    Project_Handle_Factory_Imp<Args...> const& cget_handle_factory() const;

    Project_Handle_Data_Imp<Args...>& get_handle_data();
    Project_Handle_Data_Imp<Args...> const& cget_handle_data() const;

    Project_Signalbox_Data_Imp<Args...>& get_signalbox_data();
    Project_Signalbox_Data_Imp<Args...> const& cget_signalbox_data() const;

    Command_History& get_command_history();
    Command_History const& cget_command_history() const;

  private:
    // Data Members
    //============================================================
    Project_Handle_Factory_Imp<Args...> m_handle_factory;
    Project_Handle_Data_Imp<Args...> m_handle_data;
    Project_Signalbox_Data_Imp<Args...> m_signalbox_data;
    Command_History m_command_history;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Member_Interface_Imp<List,LI,MI,LL,ML>
  //---------------------------------------------------------------------------
  // Declaration and default arguments for the template class that builds the
  // template chain.

  template
  <
    typename T_List,
    std::size_t T_List_Index = 0,
    std::size_t T_Member_Index = 0,
    std::size_t T_List_Last = (flamingo::typelist_size_v<T_List> - 1 ), // for count N, is N-1
    std::size_t T_Member_Last = (Class_Def_Size_v<flamingo::typelist_at_t<T_List,T_List_Index>>) // for count N, is N
  >
  class Member_Interface_Imp;

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Member_Interface_Imp<List,LI,MI,LL,ML>
  //---------------------------------------------------------------------------
  // For a member that isn't the last in a type that isn't the last in the list.

  template <std::size_t LI, std::size_t MI, std::size_t LL, std::size_t ML, typename...Args>
  class Member_Interface_Imp<flamingo::typelist<Args...>,LI,MI,LL,ML> :
      public Member_Interface_Imp<flamingo::typelist<Args...>,LI,MI+1>
  {
    using Inh = Member_Interface_Imp<flamingo::typelist<Args...>,LI,MI+1>;
    using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,LI>;
    using Data_Type = Data<Type>;
    using Handle_Type = Handle<Type>;
    using ID_Type = ID<Type>;
    static constexpr std::size_t const index = MI;
    using Index_Tag_Type = Index_Tag<index>;
    using Member_Value_Type = Data_Member_Value_Type<index,Data_Type>;

    static_assert(Class_Def_Size_v<Type> != 0, "Cannot use data with no members.");
  public:

    // Special 6
    //============================================================
    Member_Interface_Imp();
    ~Member_Interface_Imp() override;

    Member_Interface_Imp(Member_Interface_Imp const&) = delete;
    Member_Interface_Imp& operator=(Member_Interface_Imp const&) = delete;

    Member_Interface_Imp(Member_Interface_Imp &&);
    Member_Interface_Imp& operator=(Member_Interface_Imp &&);

    // Interface
    //============================================================
    // Attempt to get the data value for the member at this index in the data associated with the
    // supplied id. If the id is valid, the returned pair consists of true and the data value. If
    // the id is null or invalid, the returned pair consists of false and a default constructed
    // value.
    std::pair<bool,Member_Value_Type> try_get(Index_Tag_Type&&, ID_Type const& a_id) const override final;

    // Attempt an undoable change to the data value for the member at this index in the data
    // associated with the supplied id. If the id is valid and the supplied value results in a
    // change to the data (e.g. does not compare the same as the current), signals are emitted
    // telling everything to update this value, and true is returned. If the id is null or
    // invalid, nothing happens and false is returned.
    bool try_set(Index_Tag_Type&&, ID_Type const& a_id, Member_Value_Type const& a_value) const override final;

  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Member_Interface_Imp<List,LI,ML,LL,ML>
  //---------------------------------------------------------------------------
  // For a member that is the last in a type that isn't the last in the list.
  // Start building the members for the next type in the list.

  template <std::size_t LI, std::size_t LL, std::size_t ML, typename...Args>
  class Member_Interface_Imp<flamingo::typelist<Args...>,LI,ML,LL,ML> :
      public Member_Interface_Imp<flamingo::typelist<Args...>,LI+1>
  {
  public:
    // Special 6
    //============================================================
    Member_Interface_Imp();
    ~Member_Interface_Imp() override;

    Member_Interface_Imp(Member_Interface_Imp const&) = delete;
    Member_Interface_Imp& operator=(Member_Interface_Imp const&) = delete;

    Member_Interface_Imp(Member_Interface_Imp &&);
    Member_Interface_Imp& operator=(Member_Interface_Imp &&);

  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Member_Interface_Imp<List,LL,ML,LL,ML>
  //---------------------------------------------------------------------------
  // For a member that is the last in the last type in the list. This is the
  // end of the template chain. Inherit the section data so that it is below
  // all the members.

  template <std::size_t LL, std::size_t ML, typename...Args>
  class Member_Interface_Imp<flamingo::typelist<Args...>,LL,ML,LL,ML> :
      public Section_Interface_Imp<flamingo::typelist<Args...>>
  {
  public:
    // Special 6
    //============================================================
    Member_Interface_Imp();
    ~Member_Interface_Imp() override;

    Member_Interface_Imp(Member_Interface_Imp const&) = delete;
    Member_Interface_Imp& operator=(Member_Interface_Imp const&) = delete;

    Member_Interface_Imp(Member_Interface_Imp &&);
    Member_Interface_Imp& operator=(Member_Interface_Imp &&);

  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Project_Interface_Imp<List,LS,LS>
  //---------------------------------------------------------------------------
  // The top interface implements everything that isn't section or member
  // dependent and supplies a means of accessing the section and member
  // interfaces.

  template <typename T, typename...Args>
  class Project_Interface_Imp :
      public Member_Interface_Imp<flamingo::typelist<T,Args...>>
  {
    using Inh = Member_Interface_Imp<flamingo::typelist<T,Args...>>;
    using Base_Type = Abstract_Project_Interface_Imp<T,Args...>;
  public:
    // Typedefs
    //============================================================
    using Typelist_Type = flamingo::typelist<T,Args...>;
    static_assert(flamingo::typelist_all_unique_v<Typelist_Type>,
                  "Cannot have repeating types in the supplied template arguments.");

    using Signalbox_Type = typename Base_Type::Signalbox_Type;

    template  <typename U>
    using Section_Interface_Type =
    Section_Interface_Imp
    <
      Typelist_Type,
      flamingo::typelist_find_v<Typelist_Type, U>
    >;

    template  <std::size_t I>
    using Section_Interface_At =
    Section_Interface_Imp
    <
      Typelist_Type,
      I
    >;

    template <typename U, std::size_t I>
    using Member_Interface_Type =
    Member_Interface_Imp
    <
      Typelist_Type,
      flamingo::typelist_find_v<Typelist_Type, U>,
      I
    >;

    // Special 6
    //============================================================
    explicit Project_Interface_Imp(QString const& a_filepath);
    ~Project_Interface_Imp() override;

    Project_Interface_Imp(Project_Interface_Imp const&) = delete;
    Project_Interface_Imp& operator=(Project_Interface_Imp const&) = delete;

    Project_Interface_Imp(Project_Interface_Imp &&);
    Project_Interface_Imp& operator=(Project_Interface_Imp &&);

    // Interface
    //============================================================

    // Virtuals
    //------------------------------------------------------------
    void save() const override final;

    void load() override final;

    // Data that is fixed on contruction.
    QString name() const override final;

    QString location() const override final;

    QString filepath() const override final;

    // Can we currently call undo?
    bool can_undo() const override final;

    // Can we currently call redo?
    bool can_redo() const override final;

    // How many times can undo() be called?
    std::size_t undo_count() const override final;

    // How many times can redo() be called?
    std::size_t redo_count() const override final;

    // Undo the last command issued.
    bool undo() override final;

    // Redo the last undone command in the command history
    bool redo() override final;

    // Clear the undo/redo history.
    void clear_history() override final;

    // Does this name appear in the data?
    bool has_name(QString const& a_name) const override final;

    // Get all the objects names in data order
    std::vector<QString> get_all_names() const override final;

    // Alter the supplied name so that it is unique among the existing data names
    void fix_name(QString& a_name) const override final;

    // Add an object that will rely on the Project's signals. If
    // nulltpr or already present, nothing happens.
    void add_signalbox(Signalbox_Type* a_signalbox) override final;

    // Remove an object that will rely on the Project's signals. If
    // nulltpr or not present, nothing happens.
    void remove_signalbox(Signalbox_Type* a_signalbox) override final;

    // Clear all the signalboxes so that nothing relies on changes to this.
    void clear_signalboxes() override final;

    // Section Interface Access
    //------------------------------------------------------------

    template <typename U>
    Section_Interface_Type<U>* get_section()
    {
      static_assert(flamingo::typelist_find_v<Typelist_Type,U> != flamingo::typelist_size_v<Typelist_Type>,
                    "Cannot make interface, type not present.");
      return this;
    }

    template <typename U>
    Section_Interface_Type<U> const* cget_section() const
    {
      static_assert(flamingo::typelist_find_v<Typelist_Type,U> != flamingo::typelist_size_v<Typelist_Type>,
                    "Cannot make interface, type not present.");
      return this;
    }

    template <std::size_t I>
    Section_Interface_At<I>* get_section_at()
    {
      static_assert(I < flamingo::typelist_size_v<Typelist_Type>,
                    "Cannot make interface, type index is out of range.");
      return this;
    }

    template <std::size_t I>
    Section_Interface_At<I> const* cget_section_at() const
    {
      static_assert(I < flamingo::typelist_size_v<Typelist_Type>,
                    "Cannot make interface, type index is out of range.");
      return this;
    }

    template <typename U, std::size_t I>
    Member_Interface_Type<U,I>* get_member()
    {
      static_assert(flamingo::typelist_find_v<Typelist_Type,U> != flamingo::typelist_size_v<Typelist_Type>,
                    "Cannot make interface, type not present.");
      static_assert(I < Class_Def_Size_v<U>,
                    "Cannot make interface, member index is out of range.");
      return this;
    }

    template <typename U, std::size_t I>
    Member_Interface_Type<U,I> const* cget_member() const
    {
      static_assert(flamingo::typelist_find_v<Typelist_Type,U> != flamingo::typelist_size_v<Typelist_Type>,
                    "Cannot make interface, type not present.");
      static_assert(I < Class_Def_Size_v<U>,
                    "Cannot make interface, member index is out of range.");
      return this;
    }

  private:
    QFileInfo m_filepath;
  };
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Implementations
//
//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Section_Interface_Imp<List,LI,LS>
//---------------------------------------------------------------------------
// For a type in the list, build its interface.

// Special 6
//============================================================
template <std::size_t LI, std::size_t LS, typename...Args>
sak::Section_Interface_Imp<flamingo::typelist<Args...>,LI,LS>::Section_Interface_Imp() = default;

template <std::size_t LI, std::size_t LS, typename...Args>
sak::Section_Interface_Imp<flamingo::typelist<Args...>,LI,LS>::~Section_Interface_Imp() = default;

template <std::size_t LI, std::size_t LS, typename...Args>
sak::Section_Interface_Imp<flamingo::typelist<Args...>,LI,LS>::Section_Interface_Imp(Section_Interface_Imp &&) = default;

template <std::size_t LI, std::size_t LS, typename...Args>
sak::Section_Interface_Imp<flamingo::typelist<Args...>,LI,LS>& sak::Section_Interface_Imp<flamingo::typelist<Args...>,LI,LS>::operator=(Section_Interface_Imp &&) = default;

// Interface
//============================================================

// Collection Interface
//------------------------------------------------------------
// Are there any objects in this Project?
template <std::size_t LI, std::size_t LS, typename...Args>
bool sak::Section_Interface_Imp<flamingo::typelist<Args...>,LI,LS>::is_empty(Tag_Type&&) const
{
  return cget_handle_data().cget_section_at<LI>()->is_empty(Tag_Type{});
}

// How many objects are in this Project?
template <std::size_t LI, std::size_t LS, typename...Args>
std::size_t sak::Section_Interface_Imp<flamingo::typelist<Args...>,LI,LS>::count(Tag_Type&&) const
{
  return cget_handle_data().cget_section_at<LI>()->count(Tag_Type{});
}

// Does this id appear in the data?
template <std::size_t LI, std::size_t LS, typename...Args>
bool sak::Section_Interface_Imp<flamingo::typelist<Args...>,LI,LS>::has(ID_Type const& a_id) const
{
  return cget_handle_data().cget_section_at<LI>()->has(a_id);
}

// Does this name appear in the data?
template <std::size_t LI, std::size_t LS, typename...Args>
bool sak::Section_Interface_Imp<flamingo::typelist<Args...>,LI,LS>::has_name(Tag_Type&&, QString const& a_name) const
{
  return cget_handle_data().cget_section_at<LI>()->has_name(Tag_Type{}, a_name);
}

// Get the id at this index. If the index is invalid a null id is returned.
template <std::size_t LI, std::size_t LS, typename...Args>
typename sak::Section_Interface_Imp<flamingo::typelist<Args...>,LI,LS>::ID_Type sak::Section_Interface_Imp<flamingo::typelist<Args...>,LI,LS>::get_at(Tag_Type&&, std::size_t a_index) const
{
  return cget_handle_data().cget_section_at<LI>()->get_at(Tag_Type{}, a_index);
}

// Get the id with this name. If the name is invalid a null id is returned.
template <std::size_t LI, std::size_t LS, typename...Args>
typename sak::Section_Interface_Imp<flamingo::typelist<Args...>,LI,LS>::ID_Type sak::Section_Interface_Imp<flamingo::typelist<Args...>,LI,LS>::get_named(Tag_Type&&, QString const& a_name) const
{
  return cget_handle_data().cget_section_at<LI>()->get_named(Tag_Type{}, a_name);
}

// Get all the ids in data order
template <std::size_t LI, std::size_t LS, typename...Args>
std::vector<typename sak::Section_Interface_Imp<flamingo::typelist<Args...>,LI,LS>::ID_Type> sak::Section_Interface_Imp<flamingo::typelist<Args...>,LI,LS>::get_ids(Tag_Type&&) const
{
  return cget_handle_data().cget_section_at<LI>()->get_ids(Tag_Type{});
}

// Get all the handles names in data order
template <std::size_t LI, std::size_t LS, typename...Args>
std::vector<QString> sak::Section_Interface_Imp<flamingo::typelist<Args...>,LI,LS>::get_names(Tag_Type&&) const
{
  return cget_handle_data().cget_section_at<LI>()->get_names(Tag_Type{});
}

// Data Interface
//------------------------------------------------------------
// Attempt to get the index of the data associated with the supplied id. This is the current
// position in the project's collection of data for this type of index. If the id is valid,
// the returned pair consists of true and the index. If the id is null or invalid, the
// returned pair consists of false and zero.
template <std::size_t LI, std::size_t LS, typename...Args>
std::size_t sak::Section_Interface_Imp<flamingo::typelist<Args...>,LI,LS>::get_index(ID_Type const& a_id) const
{
  return cget_handle_data().cget_section_at<LI>()->index(a_id);
}

// Attempt to get the name for the data associated with the supplied id. If the id is valid,
// the returned pair consists of true and the name value. If the id is null or invalid, the
// returned pair consists of false and an empty string.
template <std::size_t LI, std::size_t LS, typename...Args>
QString sak::Section_Interface_Imp<flamingo::typelist<Args...>,LI,LS>::get_name(ID_Type const& a_id) const
{
  return cget_handle_data().cget_section_at<LI>()->name(a_id);
}

// Data Editing Interface
//------------------------------------------------------------
// Attempt an undoable change to the name of the data associated with the supplied id. If
// the id is valid and the supplied value results in a change to the data, signals are emitted
// telling everything to update this name, and true is returned. If the id is null or
// invalid, nothing happens and false is returned. Success does not indicate that the name
// is set to what has been supplied, but that the name has changed.
template <std::size_t LI, std::size_t LS, typename...Args>
bool sak::Section_Interface_Imp<flamingo::typelist<Args...>,LI,LS>::try_set_name(Signal_Source a_source, ID_Type const& a_id, QString const& a_name)
{
  // Get the handle for the data. If the id is null or invalid, this is a null handle.
  auto l_handle = cget_handle_data().cget_section<Type>()->get_handle(a_id);

  // If the data is valid and the not equal to the current name
  if(l_handle && l_handle->cname() != a_name)
  {
    // Copy the name
    QString l_name{a_name};
    // Fix it
    cget_handle_data().fix_name(l_name);
    // If the fixed name is still unequal to the current name
    if (l_handle->cname() != l_name)
    {
      // Make a command to change to this name
      get_command_history().add_execute(make_command_change_name<LI>(a_source,
                                                                     get_handle_data(),
                                                                     get_signalbox_data(),
                                                                     l_handle,
                                                                     l_name));

      return true;
    }

  }

  // If we failed all the conditions, do nothing and return false.
  return false;
}

// Collection Editing Interface
//------------------------------------------------------------
// Undoable add a new object made using the default parameters. Returns the id of the new
// data.
template <std::size_t LI, std::size_t LS, typename...Args>
typename sak::Section_Interface_Imp<flamingo::typelist<Args...>,LI,LS>::ID_Type sak::Section_Interface_Imp<flamingo::typelist<Args...>,LI,LS>::add_default(Tag_Type&&, Signal_Source a_source)
{
  // Make a default handle.
  auto l_handle = get_handle_factory().get_section_at<LI>()->make_default(Tag_Type{});
  // Fix the name.
  cget_handle_data().fix_name(l_handle->name());

  // Now have data that can be added via a command.
  get_command_history().add_execute( make_command_added<LI>(a_source,
                                                            get_handle_data(),
                                                            get_signalbox_data(),
                                                            l_handle) );

  // Return the id
  return l_handle.id();
}

// Undoable add a new object using the supplied handle. The name will be modified if it is currently in
// use by another object. Return true if the operation resulted in an undoable command. If this handle
// is invalid or already in the data then nothing happens and returns false.
//template <std::size_t LI, std::size_t LS, typename...Args>
//bool sak::Section_Interface_Imp<flamingo::typelist<Args...>,LI,LS>::try_add(Signal_Source a_source, ID_Type const& a_id)
//{
  //TODO
  //return false;
//}

// Undoable remove object. Return true if the operation resulted in an undoable command. If this handle
// is invalid or already in the data then nothing happens and returns false. Handle data is not deleted
// until the last handle for it is deleted.
template <std::size_t LI, std::size_t LS, typename...Args>
bool sak::Section_Interface_Imp<flamingo::typelist<Args...>,LI,LS>::try_remove(Signal_Source a_source, ID_Type const& a_id)
{
  // ASSUMING NOTHING HOLDS HANDLES AS MEMBERS
  //TODO
  return false;
}

// Request that the editor for this file be opened or switched to.
template <std::size_t LI, std::size_t LS, typename...Args>
bool sak::Section_Interface_Imp<flamingo::typelist<Args...>,LI,LS>::try_request_editor(Signal_Source a_source, ID_Type const& a_id)
{
  // If the data is valid and the not equal to the current name
  if(a_id && cget_handle_data().cget_section_at<LI>()->has(a_id))
  {
    get_signalbox_data().get_section_at<LI>()->requests_editor(a_source, a_id, cget_handle_data().cget_section_at<LI>()->index(a_id));
    return true;
  }
  else
  {
    return false;
  }
}

// Request that the focus change to this object.
template <std::size_t LI, std::size_t LS, typename...Args>
bool sak::Section_Interface_Imp<flamingo::typelist<Args...>,LI,LS>::try_request_outliner(Signal_Source a_source, ID_Type const& a_id)
{
  // If the data is valid and the not equal to the current name
  if(a_id && cget_handle_data().cget_section_at<LI>()->has(a_id))
  {
    get_signalbox_data().get_section_at<LI>()->requests_outliner(a_source, a_id, cget_handle_data().cget_section_at<LI>()->index(a_id));
    return true;
  }
  else
  {
    return false;
  }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Section_Interface_Imp<List,LS,LS>
//---------------------------------------------------------------------------
// At the end of the list inherit the abstract interface. This bit is also
// where all the data goes so everything that inherits it can use it.

// Special 6
//============================================================
template <std::size_t LS, typename...Args>
sak::Section_Interface_Imp<flamingo::typelist<Args...>,LS,LS>::Section_Interface_Imp() :
  m_handle_factory{},
  m_handle_data{},
  m_signalbox_data{},
  m_command_history{}
{}

template <std::size_t LS, typename...Args>
sak::Section_Interface_Imp<flamingo::typelist<Args...>,LS,LS>::~Section_Interface_Imp() = default;

template <std::size_t LS, typename...Args>
sak::Section_Interface_Imp<flamingo::typelist<Args...>,LS,LS>::Section_Interface_Imp(Section_Interface_Imp &&) = default;

template <std::size_t LS, typename...Args>
sak::Section_Interface_Imp<flamingo::typelist<Args...>,LS,LS>& sak::Section_Interface_Imp<flamingo::typelist<Args...>,LS,LS>::operator=(Section_Interface_Imp &&) = default;

// Internal Interface
//============================================================
// Access to the data members for all the classes that inherit
// this.

template <std::size_t LS, typename...Args>
sak::Project_Handle_Factory_Imp<Args...>& sak::Section_Interface_Imp<flamingo::typelist<Args...>,LS,LS>::get_handle_factory()
{
  return m_handle_factory;
}

template <std::size_t LS, typename...Args>
sak::Project_Handle_Factory_Imp<Args...> const& sak::Section_Interface_Imp<flamingo::typelist<Args...>,LS,LS>::cget_handle_factory() const
{
  return m_handle_factory;
}

template <std::size_t LS, typename...Args>
sak::Project_Handle_Data_Imp<Args...>& sak::Section_Interface_Imp<flamingo::typelist<Args...>,LS,LS>::get_handle_data()
{
  return m_handle_data;
}

template <std::size_t LS, typename...Args>
sak::Project_Handle_Data_Imp<Args...> const& sak::Section_Interface_Imp<flamingo::typelist<Args...>,LS,LS>::cget_handle_data() const
{
  return m_handle_data;
}

template <std::size_t LS, typename...Args>
sak::Project_Signalbox_Data_Imp<Args...>& sak::Section_Interface_Imp<flamingo::typelist<Args...>,LS,LS>::get_signalbox_data()
{
  return m_signalbox_data;
}

template <std::size_t LS, typename...Args>
sak::Project_Signalbox_Data_Imp<Args...> const& sak::Section_Interface_Imp<flamingo::typelist<Args...>,LS,LS>::cget_signalbox_data() const
{
  return m_signalbox_data;
}

template <std::size_t LS, typename...Args>
sak::Command_History& sak::Section_Interface_Imp<flamingo::typelist<Args...>,LS,LS>::get_command_history()
{
  return m_command_history;
}

template <std::size_t LS, typename...Args>
sak::Command_History const& sak::Section_Interface_Imp<flamingo::typelist<Args...>,LS,LS>::cget_command_history() const
{
  return m_command_history;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Member_Interface_Imp<List,LI,MI,LL,ML>
//---------------------------------------------------------------------------
// For a member that isn't the last in a type that isn't the last in the list.

// Special 6
//============================================================
template <std::size_t LI, std::size_t MI, std::size_t LL, std::size_t ML, typename...Args>
sak::Member_Interface_Imp<flamingo::typelist<Args...>,LI,MI,LL,ML>::Member_Interface_Imp() = default;

template <std::size_t LI, std::size_t MI, std::size_t LL, std::size_t ML, typename...Args>
sak::Member_Interface_Imp<flamingo::typelist<Args...>,LI,MI,LL,ML>::~Member_Interface_Imp() = default;

template <std::size_t LI, std::size_t MI, std::size_t LL, std::size_t ML, typename...Args>
sak::Member_Interface_Imp<flamingo::typelist<Args...>,LI,MI,LL,ML>::Member_Interface_Imp(Member_Interface_Imp &&) = default;

template <std::size_t LI, std::size_t MI, std::size_t LL, std::size_t ML, typename...Args>
sak::Member_Interface_Imp<flamingo::typelist<Args...>,LI,MI,LL,ML>& sak::Member_Interface_Imp<flamingo::typelist<Args...>,LI,MI,LL,ML>::operator=(Member_Interface_Imp &&) = default;

// Interface
//============================================================
// Attempt to get the data value for the member at this index in the data associated with the
// supplied id. If the id is valid, the returned pair consists of true and the data value. If
// the id is null or invalid, the returned pair consists of false and a default constructed
// value.
template <std::size_t LI, std::size_t MI, std::size_t LL, std::size_t ML, typename...Args>
std::pair<bool,typename sak::Member_Interface_Imp<flamingo::typelist<Args...>,LI,MI,LL,ML>::Member_Value_Type> sak::Member_Interface_Imp<flamingo::typelist<Args...>,LI,MI,LL,ML>::try_get(Index_Tag_Type&&, ID_Type const& a_id) const
{
  // Get the handle for the data. If the id is null or invalid, this is a null handle.
  auto l_handle = cget_handle_data().cget_section<Type>()->get_handle(a_id);

  // If the data is valid...
  if(l_handle)
  {
    // Return a pair with the value.
    return std::make_pair(true, l_handle->cmember_at<index>());
  }
  else
  {
    // Else return a fail pair.
    return std::make_pair(false, Member_Value_Type{});
  }
}

// Attempt an undoable change to the data value for the member at this index in the data
// associated with the supplied id. If the id is valid and the supplied value results in a
// change to the data (e.g. does not compare the same as the current), signals are emitted
// telling everything to update this value, and true is returned. If the id is null or
// invalid, nothing happens and false is returned.
template <std::size_t LI, std::size_t MI, std::size_t LL, std::size_t ML, typename...Args>
bool sak::Member_Interface_Imp<flamingo::typelist<Args...>,LI,MI,LL,ML>::try_set(Index_Tag_Type&&, ID_Type const& a_id, Member_Value_Type const& a_value) const
{
  // Get the handle for the data. If the id is null or invalid, this is a null handle.
  auto l_handle = cget_handle_data().cget_section<Type>()->get_handle(a_id);

  // If the data is valid, and the new value does not compare equal to the current value...
  if(l_handle && l_handle->cmember_at<index>() != a_value)
  {
    // Make and execute the appropriate command.

    //TODO

    return true;
  }
  else
  {
    // Else return false
    return false;
  }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Member_Interface_Imp<List,LI,ML,LL,ML>
//---------------------------------------------------------------------------
// For a member that is the last in a type that isn't the last in the list.
// Start building the members for the next type in the list.

// Special 6
//============================================================
template <std::size_t LI, std::size_t LL, std::size_t ML, typename...Args>
sak::Member_Interface_Imp<flamingo::typelist<Args...>,LI,ML,LL,ML>::Member_Interface_Imp() = default;

template <std::size_t LI, std::size_t LL, std::size_t ML, typename...Args>
sak::Member_Interface_Imp<flamingo::typelist<Args...>,LI,ML,LL,ML>::~Member_Interface_Imp() = default;

template <std::size_t LI, std::size_t LL, std::size_t ML, typename...Args>
sak::Member_Interface_Imp<flamingo::typelist<Args...>,LI,ML,LL,ML>::Member_Interface_Imp(Member_Interface_Imp &&) = default;

template <std::size_t LI, std::size_t LL, std::size_t ML, typename...Args>
sak::Member_Interface_Imp<flamingo::typelist<Args...>,LI,ML,LL,ML>& sak::Member_Interface_Imp<flamingo::typelist<Args...>,LI,ML,LL,ML>::operator=(Member_Interface_Imp &&) = default;

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Member_Interface_Imp<List,LL,ML,LL,ML>
//---------------------------------------------------------------------------
// For a member that is the last in the last type in the list. This is the
// end of the template chain. Inherit the section data so that it is below
// all the members.

// Special 6
//============================================================
template <std::size_t LL, std::size_t ML, typename...Args>
sak::Member_Interface_Imp<flamingo::typelist<Args...>,LL,ML,LL,ML>::Member_Interface_Imp() = default;

template <std::size_t LL, std::size_t ML, typename...Args>
sak::Member_Interface_Imp<flamingo::typelist<Args...>,LL,ML,LL,ML>::~Member_Interface_Imp() = default;

template <std::size_t LL, std::size_t ML, typename...Args>
sak::Member_Interface_Imp<flamingo::typelist<Args...>,LL,ML,LL,ML>::Member_Interface_Imp(Member_Interface_Imp &&) = default;

template <std::size_t LL, std::size_t ML, typename...Args>
sak::Member_Interface_Imp<flamingo::typelist<Args...>,LL,ML,LL,ML>& sak::Member_Interface_Imp<flamingo::typelist<Args...>,LL,ML,LL,ML>::operator=(Member_Interface_Imp &&) = default;


//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Project_Interface_Imp<List,LS,LS>
//---------------------------------------------------------------------------
// The top interface implements everything that isn't section or member
// dependent and supplies a means of accessing the section and member
// interfaces.

// Special 6
//============================================================
template <typename T, typename...Args>
sak::Project_Interface_Imp<T,Args...>::Project_Interface_Imp(QString const& a_filepath) :
  m_filepath{a_filepath}
{
  // If we want to make sure it exists, do it here.
}

template <typename T, typename...Args>
sak::Project_Interface_Imp<T,Args...>::~Project_Interface_Imp() = default;

template <typename T, typename...Args>
sak::Project_Interface_Imp<T,Args...>::Project_Interface_Imp(Project_Interface_Imp &&) = default;

template <typename T, typename...Args>
sak::Project_Interface_Imp<T,Args...>& sak::Project_Interface_Imp<T,Args...>::operator=(Project_Interface_Imp &&) = default;

// Interface
//============================================================

// Virtuals
//------------------------------------------------------------
template <typename T, typename...Args>
void sak::Project_Interface_Imp<T,Args...>::save() const
{
  //TODO
}

template <typename T, typename...Args>
void sak::Project_Interface_Imp<T,Args...>::load()
{
  //TODO
}

// Data that is fixed on contruction.
template <typename T, typename...Args>
QString sak::Project_Interface_Imp<T,Args...>::name() const
{
  return m_filepath.baseName();
}

template <typename T, typename...Args>
QString sak::Project_Interface_Imp<T,Args...>::location() const
{
  return m_filepath.absoluteDir().absolutePath();
}

template <typename T, typename...Args>
QString sak::Project_Interface_Imp<T,Args...>::filepath() const
{
  return m_filepath.absoluteFilePath();
}

// Can we currently call undo?
template <typename T, typename...Args>
bool sak::Project_Interface_Imp<T,Args...>::can_undo() const
{
  return this->cget_command_history().can_undo();
}

// Can we currently call redo?
template <typename T, typename...Args>
bool sak::Project_Interface_Imp<T,Args...>::can_redo() const
{
  return this->cget_command_history().can_redo();
}

// How many times can undo() be called?
template <typename T, typename...Args>
std::size_t sak::Project_Interface_Imp<T,Args...>::undo_count() const
{
  return this->cget_command_history().undo_count();
}

// How many times can redo() be called?
template <typename T, typename...Args>
std::size_t sak::Project_Interface_Imp<T,Args...>::redo_count() const
{
  return this->cget_command_history().redo_count();
}

// Undo the last command issued.
template <typename T, typename...Args>
bool sak::Project_Interface_Imp<T,Args...>::undo()
{
  return this->get_command_history().undo();
}

// Redo the last undone command in the command history
template <typename T, typename...Args>
bool sak::Project_Interface_Imp<T,Args...>::redo()
{
  return this->get_command_history().redo();
}

// Clear the undo/redo history.
template <typename T, typename...Args>
void sak::Project_Interface_Imp<T,Args...>::clear_history()
{
  return this->get_command_history().clear();
}

// Does this name appear in the data?
template <typename T, typename...Args>
bool sak::Project_Interface_Imp<T,Args...>::has_name(QString const& a_name) const
{
  return this->cget_handle_data().has_name(a_name);
}

// Get all the objects names in data order
template <typename T, typename...Args>
std::vector<QString> sak::Project_Interface_Imp<T,Args...>::get_all_names() const
{
  return this->cget_handle_data().get_all_names();
}

// Alter the supplied name so that it is unique among the existing data names
template <typename T, typename...Args>
void sak::Project_Interface_Imp<T,Args...>::fix_name(QString& a_name) const
{
  return this->cget_handle_data().fix_name(a_name);
}

// Add an object that will rely on the Project's signals. If
// nulltpr or already present, nothing happens.
template <typename T, typename...Args>
void sak::Project_Interface_Imp<T,Args...>::add_signalbox(Signalbox_Type* a_signalbox)
{
  this->get_signalbox_data().add_signalbox(a_signalbox);
}

// Remove an object that will rely on the Project's signals. If
// nulltpr or not present, nothing happens.
template <typename T, typename...Args>
void sak::Project_Interface_Imp<T,Args...>::remove_signalbox(Signalbox_Type* a_signalbox)
{
  this->get_signalbox_data().remove_signalbox(a_signalbox);
}

// Clear all the signalboxes so that nothing relies on changes to this.
template <typename T, typename...Args>
void sak::Project_Interface_Imp<T,Args...>::clear_signalboxes()
{
  this->get_signalbox_data().clear_signalboxes();
}

#endif // SAK_PROJECT_INTERFACE_HPP
