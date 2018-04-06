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

#ifndef SAK_ID_FWD_HPP
#include "id_fwd.hpp"
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
Ok, now decide what you want for each part. So what do we want?
- Stop users directly editing data.
  - Use dumb ids instead of handles.
    - Also stops reference count changes outside the data.
  - Return values for everything .
- Allow everything to be called with bad ids.
  - Return a pair of bool and value.
    - On sucess the bool is true and the value is the data.
    - On fail the bool is false and the value is default constructed (or anything).
- Editing functions return a bool
  - True if the arguments produced a change in the data that will propagate out.
  - False if any arguments were invalid or did not result in a change.
*/

namespace sak
{
  //---------------------------------------------------------------------------
  // Abstract_Member_Interface_Imp<List,LI,MI,LL,ML>
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
  class Abstract_Member_Interface_Imp;

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Abstract_Member_Interface_Imp<List,LI,MI,LL,ML>
  //---------------------------------------------------------------------------
  // For a member that isn't the last in a type that isn't the last in the list.

  template <std::size_t LI, std::size_t MI, std::size_t LL, std::size_t ML, typename...Args>
  class Abstract_Member_Interface_Imp<flamingo::typelist<Args...>,LI,MI,LL,ML> :
      protected Abstract_Member_Interface_Imp<flamingo::typelist<Args...>,LI,MI+1>
  {
    using Inh = Abstract_Member_Interface_Imp<flamingo::typelist<Args...>,LI,MI+1>;
    using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,LI>;
    using Data_Type = Data<Type>;
    using ID_Type = ID<Type>;
    static constexpr std::size_t const index = MI;
    using Index_Tag_Type = Index_Tag<index>;

    static_assert(Class_Def_Size_v<Type> != 0, "Cannot use data with no members.");
  public:
    using Member_Value_Type = Data_Member_Value_Type<index,Data_Type>;

    // Special 6
    //============================================================
    ~Abstract_Member_Interface_Imp() override = 0;

    // Interface
    //============================================================
    // Attempt to get the data value for the member at this index in the data associated with the
    // supplied id. If the id is valid, the returned pair consists of true and the data value. If
    // the id is null or invalid, the returned pair consists of false and a default constructed
    // value.
    virtual std::pair<bool,Member_Value_Type> try_get(Index_Tag_Type&&, ID_Type const& a_id) const = 0;

    // Attempt an undoable change to the data value for the member at this index in the data
    // associated with the supplied id. If the id is valid and the supplied value results in a
    // change to the data (e.g. does not compare the same as the current), signals are emitted
    // telling everything to update this value, and true is returned. If the id is null or
    // invalid, nothing happens and false is returned.
    virtual bool try_set(Index_Tag_Type&&, ID_Type const& a_id, Member_Value_Type const& a_value) const = 0;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Abstract_Member_Interface_Imp<List,LI,ML,LL,ML>
  //---------------------------------------------------------------------------
  // For a member that is the last in a type that isn't the last in the list.

  template <std::size_t LI, std::size_t LL, std::size_t ML, typename...Args>
  class Abstract_Member_Interface_Imp<flamingo::typelist<Args...>,LI,ML,LL,ML> :
      protected Abstract_Member_Interface_Imp<flamingo::typelist<Args...>,LI+1>
  {
  public:
    // Special 6
    //============================================================
    ~Abstract_Member_Interface_Imp() override = 0;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Abstract_Member_Interface_Imp<List,LL,ML,LL,ML>
  //---------------------------------------------------------------------------
  // For a member that is the last in the last type in the list. This is the
  // end of the template chain.

  template <std::size_t LL, std::size_t ML, typename...Args>
  class Abstract_Member_Interface_Imp<flamingo::typelist<Args...>,LL,ML,LL,ML>
  {
  public:
    // Special 6
    //============================================================
    virtual ~Abstract_Member_Interface_Imp() = 0;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Abstract_Section_Interface_Imp<List,LI,LL>
  //---------------------------------------------------------------------------
  // Declaration and default arguments for the template class that builds the
  // template chain.
  template
  <
      typename T_List,
      std::size_t T_List_Index = 0,
      std::size_t T_List_Size = (flamingo::typelist_size_v<T_List>) // for list size N, is N
  >
  class Abstract_Section_Interface_Imp;

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Abstract_Section_Interface_Imp<List,LI,LS>
  //---------------------------------------------------------------------------
  // For a type in the list, build its interface.

  template <std::size_t LI, std::size_t LS, typename...Args>
  class Abstract_Section_Interface_Imp<flamingo::typelist<Args...>,LI,LS> :
      protected Abstract_Section_Interface_Imp<flamingo::typelist<Args...>,LI+1>
  {
    using Inh = Abstract_Section_Interface_Imp<flamingo::typelist<Args...>,LI+1>;
    using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,LI>;
    using Data_Type = Data<Type>;
    using ID_Type = ID<Type>;
    //using Handle_Type = Handle<Type>;
    using Tag_Type = Tag<Type>;

    static_assert(Class_Def_Size_v<Type> != 0, "Cannot use data with no members.");
  public:

    // Special 6
    //============================================================
    virtual ~Abstract_Section_Interface_Imp() = 0;

    // Interface
    //============================================================

    // Collection Interface
    //------------------------------------------------------------
    // Are there any objects in this Project?
    virtual bool is_empty(Tag_Type&&) const = 0;

    // How many objects are in this Project?
    virtual std::size_t count(Tag_Type&&) const = 0;

    // Does this id appear in the data?
    virtual bool has(ID_Type const& a_id) const = 0;

    // Does this name appear in the data?
    virtual bool has_name(Tag_Type&&, QString const&) const = 0;

    // Get the id at this index. If the index is invalid a null id is returned.
    virtual ID_Type get_at(Tag_Type&&, std::size_t a_index) const = 0;

    // Get the id with this name. If the name is invalid a null id is returned.
    virtual ID_Type get_named(Tag_Type&&, QString const&) const = 0;

    // Get all the ids in data order
    virtual std::vector<ID_Type> get_ids(Tag_Type&&) const = 0;

    // Get all the handles names in data order
    virtual std::vector<QString> get_names(Tag_Type&&) const = 0;

    // Data Interface
    //------------------------------------------------------------
    // Get the index of the data associated with the supplied id. This is the current position
    // in the project's collection of data for this type of data. If the id is null or invalid,
    // the returned index is equal to count().
    virtual std::size_t get_index(ID_Type const& a_id) const = 0;

    // Get the name of the data associated with the supplied id. If the id is null or invalid,
    // the returned name is empty, which names cannot be.
    virtual QString get_name(ID_Type const& a_id) const = 0;

    // Data Editing Interface
    //------------------------------------------------------------
    // Attempt an undoable change to the name of the data associated with the supplied id. If
    // the id is valid and the supplied value results in a change to the data, signals are emitted
    // telling everything to update this name, and true is returned. If the id is null or
    // invalid, nothing happens and false is returned. Success does not indicate that the name
    // is set to what has been supplied, but that the name has changed.
    virtual bool try_set_name(Signal_Source a_source, ID_Type const& a_id, QString const& a_name) = 0;

    // Collection Editing Interface
    //------------------------------------------------------------
    // Undoable add a new object made using the default parameters. Returns the id of the new
    // data.
    virtual ID_Type add_default(Tag_Type&&, Signal_Source a_source) = 0;

    // Undoable add a new object using the supplied handle. The name will be modified if it is currently in
    // use by another object. Return true if the operation resulted in an undoable command. If this handle
    // is invalid or already in the data then nothing happens and returns false.
    //virtual bool try_add(Signal_Source a_source, ID_Type const& a_id) = 0;

    // Undoable remove object. Return true if the operation resulted in an undoable command. If this handle
    // is invalid or already in the data then nothing happens and returns false. Handle data is not deleted
    // until the last handle for it is deleted.
    virtual bool try_remove(Signal_Source a_source, ID_Type const& a_id) = 0;

    // Request that the editor for this file be opened or switched to.
    virtual bool try_request_editor(Signal_Source a_source, ID_Type const& a_id) = 0;

    // Request that the focus change to this object.
    virtual bool try_request_outliner(Signal_Source a_source, ID_Type const& a_id) = 0;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Abstract_Section_Interface_Imp<List,LS,LS>
  //---------------------------------------------------------------------------
  // At the end of the list start building the member interfaces.
  template <std::size_t LS, typename...Args>
  class Abstract_Section_Interface_Imp<flamingo::typelist<Args...>,LS,LS> :
      protected Abstract_Member_Interface_Imp<flamingo::typelist<Args...>>
  {
  public:
    // Special 6
    //============================================================
    virtual ~Abstract_Section_Interface_Imp() = 0;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Abstract_Project_Interface_Imp<List,LS,LS>
  //---------------------------------------------------------------------------
  // The top interface implements everything that isn't section or member
  // dependent and supplies a means of accessing the section and member
  // interfaces.

  template <typename T, typename...Args>
  class Abstract_Project_Interface_Imp :
      protected Abstract_Section_Interface_Imp<flamingo::typelist<T,Args...>>
  {
    using Inh = Abstract_Section_Interface_Imp<flamingo::typelist<T,Args...>>;
  public:
    // Typedefs
    //============================================================
    using Typelist_Type = flamingo::typelist<T,Args...>;
    static_assert(flamingo::typelist_all_unique_v<Typelist_Type>,
                  "Cannot have repeating types in the supplied template arguments.");

    using Signalbox_Type = Abstract_Project_Signalbox_Imp<T,Args...>;

  private:
    // Internal Interface
    //============================================================
    template  <typename U>
    using Abstract_Section_Interface_Type =
    Abstract_Section_Interface_Imp
    <
      Typelist_Type,
      flamingo::typelist_find_v<Typelist_Type, U>
    >;

    template <typename U, std::size_t I>
    using Abstract_Member_Interface_Type =
    Abstract_Member_Interface_Imp
    <
      Typelist_Type,
      flamingo::typelist_find_v<Typelist_Type, U>,
      I
    >;

    template <typename U, std::size_t I>
    using Member_Value_Type = typename Abstract_Member_Interface_Type<U,I>::Member_Value_Type;

    // static_assert Helpers
    //------------------------------------------------------------

    template <typename U>
    static constexpr bool const has_type = flamingo::typelist_find_v<Typelist_Type,U> != flamingo::typelist_size_v<Typelist_Type>;

    template <typename U, std::size_t I>
    static constexpr bool const has_member = has_type<U> && (I < Class_Def_Size_v<U>);

    // Section Interface Access
    //------------------------------------------------------------

    template <typename U>
    Abstract_Section_Interface_Type<U>* section()
    {
      static_assert(has_type<U>, "Bad type for Abstract_Project_Interface_Imp<...>::section");
      return this;
    }

    template <typename U>
    Abstract_Section_Interface_Type<U> const* csection() const
    {
      static_assert(has_type<U>, "Bad type for Abstract_Project_Interface_Imp<...>::csection");
      return this;
    }

    template <typename U, std::size_t I>
    Abstract_Member_Interface_Type<U,I>* member()
    {
      static_assert(has_type<U>, "Bad type for Abstract_Project_Interface_Imp<...>::member");
      static_assert(has_member<U,I>, "Bad member index for Abstract_Project_Interface_Imp<...>::member");
      return this;
    }

    template <typename U, std::size_t I>
    Abstract_Member_Interface_Type<U,I> const* cmember() const
    {
      static_assert(has_type<U>, "Bad type for Abstract_Project_Interface_Imp<...>::cmember");
      static_assert(has_member<U,I>, "Bad member index for Abstract_Project_Interface_Imp<...>::cmember");
      return this;
    }


  public:
    // Special 6
    //============================================================
    ~Abstract_Project_Interface_Imp() override = 0;

    // Interface
    //============================================================

    // Virtuals
    //------------------------------------------------------------
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

    // Undo the last command issued. Return true if succeeded.
    virtual bool undo() = 0;

    // Redo the last undone command. Return true if succeeded.
    virtual bool redo() = 0;

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


    // Collection Interface
    //------------------------------------------------------------
    // Are there any objects in this Project?
    template <typename U>
    bool is_empty(Tag<U>&&) const
    {
      static_assert(has_type<U>, "Bad type for Abstract_Project_Interface_Imp<...>::is_empty");
      return csection<U>()->is_empty(Tag<U>{});
    }

    // How many objects are in this Project?
    template <typename U>
    std::size_t count(Tag<U>&&) const
    {
      static_assert(has_type<U>, "Bad type for Abstract_Project_Interface_Imp<...>::count");
      return csection<U>()->count(Tag<U>{});
    }

    // Does this id appear in the data?
    template <typename U>
    bool has(ID<U> const& a_id) const
    {
      static_assert(has_type<U>, "Bad type for Abstract_Project_Interface_Imp<...>::has");
      return csection<U>()->has(a_id);
    }

    // Does this name appear in the data?
    template <typename U>
    bool has_name(Tag<U>&&, QString const& a_name) const
    {
      static_assert(has_type<U>, "Bad type for Abstract_Project_Interface_Imp<...>::has_name");
      return csection<U>()->has_name(Tag<U>{}, a_name);
    }

    // Get the id at this index. If the index is invalid a null id is returned.
    template <typename U>
    ID<U> get_at(Tag<U>&&, std::size_t a_index) const
    {
      static_assert(has_type<U>, "Bad type for Abstract_Project_Interface_Imp<...>::get_at");
      return csection<U>()->get_at(Tag<U>{}, a_index);
    }

    // Get the id with this name. If the name is invalid a null id is returned.
    template <typename U>
    ID<U> get_named(Tag<U>&&, QString const& a_name) const
    {
      static_assert(has_type<U>, "Bad type for Abstract_Project_Interface_Imp<...>::get_named");
      return csection<U>()->get_named(Tag<U>{}, a_name);
    }

    // Get all the ids in data order
    template <typename U>
    std::vector<ID<U>> get_ids(Tag<U>&&) const
    {
      static_assert(has_type<U>, "Bad type for Abstract_Project_Interface_Imp<...>::get_ids");
      return csection<U>()->get_ids(Tag<U>{});
    }

    // Get all the handles names in data order
    template <typename U>
    std::vector<QString> get_names(Tag<U>&&) const
    {
      static_assert(has_type<U>, "Bad type for Abstract_Project_Interface_Imp<...>::get_names");
      return csection<U>()->get_names(Tag<U>{});
    }

    // Data Interface
    //------------------------------------------------------------
    // Get the index of the data associated with the supplied id. This is the current position
    // in the project's collection of data for this type of data. If the id is null or invalid,
    // the returned index is equal to count().
    template <typename U>
    std::size_t get_index(ID<U> const& a_id) const
    {
      static_assert(has_type<U>, "Bad type for Abstract_Project_Interface_Imp<...>::get_index");
      return csection<U>()->get_index(a_id);
    }

    // Get the name of the data associated with the supplied id. If the id is null or invalid,
    // the returned name is empty, which names cannot be.
    template <typename U>
    QString get_name(ID<U> const& a_id) const
    {
      static_assert(has_type<U>, "Bad type for Abstract_Project_Interface_Imp<...>::get_name");
      return csection<U>()->get_name(a_id);
    }

    // Data Editing Interface
    //------------------------------------------------------------
    // Attempt an undoable change to the name of the data associated with the supplied id. If
    // the id is valid and the supplied value results in a change to the data, signals are emitted
    // telling everything to update this name, and true is returned. If the id is null or
    // invalid, nothing happens and false is returned. Success does not indicate that the name
    // is set to what has been supplied, but that the name has changed.
    template <typename U>
    bool try_set_name(Signal_Source a_source, ID<U> const& a_id, QString const& a_name)
    {
      static_assert(has_type<U>, "Bad type for Abstract_Project_Interface_Imp<...>::try_set_name");
      return section<U>()->try_set_name(a_source, a_id, a_name);
    }

    // Collection Editing Interface
    //------------------------------------------------------------
    // Undoable add a new object made using the default parameters. Returns the id of the new
    // data.
    template <typename U>
    ID<U> add_default(Tag<U>&&, Signal_Source a_source)
    {
      static_assert(has_type<U>, "Bad type for Abstract_Project_Interface_Imp<...>::add_default");
      return section<U>()->add_default(Tag<U>{}, a_source);
    }

    // Undoable add a new object using the supplied handle. The name will be modified if it is currently in
    // use by another object. Return true if the operation resulted in an undoable command. If this handle
    // is invalid or already in the data then nothing happens and returns false.
    //virtual bool try_add(Signal_Source a_source, ID_Type const& a_id) = 0;

    // Undoable remove object. Return true if the operation resulted in an undoable command. If this handle
    // is invalid or already in the data then nothing happens and returns false. Handle data is not deleted
    // until the last handle for it is deleted.
    template <typename U>
    bool try_remove(Signal_Source a_source, ID<U> const& a_id)
    {
      static_assert(has_type<U>, "Bad type for Abstract_Project_Interface_Imp<...>::try_remove");
      return section<U>()->try_remove(a_source, a_id);
    }

    // Request that the editor for this file be opened or switched to.
    template <typename U>
    bool try_request_editor(Signal_Source a_source, ID<U> const& a_id)
    {
      static_assert(has_type<U>, "Bad type for Abstract_Project_Interface_Imp<...>::try_request_editor");
      return csection<U>()->try_request_editor(a_source, a_id);
    }

    // Request that the focus change to this object.
    template <typename U>
    bool try_request_outliner(Signal_Source a_source, ID<U> const& a_id)
    {
      static_assert(has_type<U>, "Bad type for Abstract_Project_Interface_Imp<...>::try_request_outliner");
      return csection<U>()->try_request_outliner(a_source, a_id);
    }

    // Member Interface
    //------------------------------------------------------------
    // Attempt to get the data value for the member at this index in the data associated with the
    // supplied id. If the id is valid, the returned pair consists of true and the data value. If
    // the id is null or invalid, the returned pair consists of false and a default constructed
    // value.
    template <std::size_t I, typename U>
    std::pair<bool,Member_Value_Type<U,I>> try_get(Index_Tag<I>&&, ID<U> const& a_id) const
    {
      static_assert(has_type<U>, "Bad type for Abstract_Project_Interface_Imp<...>::try_get");
      static_assert(has_member<U,I>, "Bad member index for Abstract_Project_Interface_Imp<...>::try_get");
      return cmember<U,I>()->try_get(Index_Tag<I>{}, a_id);
    }

    // Attempt an undoable change to the data value for the member at this index in the data
    // associated with the supplied id. If the id is valid and the supplied value results in a
    // change to the data (e.g. does not compare the same as the current), signals are emitted
    // telling everything to update this value, and true is returned. If the id is null or
    // invalid, nothing happens and false is returned.
    template <std::size_t I, typename U>
    bool try_set(Index_Tag<I>&&, ID<U> const& a_id, Member_Value_Type<U,I> const& a_value) const
    {
      static_assert(has_type<U>, "Bad type for Abstract_Project_Interface_Imp<...>::try_set");
      static_assert(has_member<U,I>, "Bad member index for Abstract_Project_Interface_Imp<...>::try_set");
      return member<U,I>()->try_set(Index_Tag<I>{}, a_id, a_value);
    }
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Abstract_Project_Interface
  //---------------------------------------------------------------------------
  // Factory function to make a type that implements this interface.

  //std::unique_ptr<Abstract_Project_Interface> make_project_interface(Project_Data&& a_data);

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  namespace v2
  {
    class Entity_ID;
    class Variant;

    class Abstract_Project_Signalbox;

    //---------------------------------------------------------------------------
    // Abstract_Project_Interface
    //---------------------------------------------------------------------------
    // Planning a redo with a different oobject layout.
    class Abstract_Project_Interface
    {
      // Special 6
      //============================================================
      //~Abstract_Project_Interface() override = 0;

      // Interface
      //============================================================

      // Virtuals
      //------------------------------------------------------------
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

      // Undo the last command issued. Return true if succeeded.
      virtual bool undo() = 0;

      // Redo the last undone command. Return true if succeeded.
      virtual bool redo() = 0;

      // Clear the undo/redo history.
      virtual void clear_history() = 0;

      // Add an object that will rely on the Project's signals. If
      // nulltpr or already present, nothing happens.
      virtual void add_signalbox(Abstract_Project_Signalbox* a_signalbox) = 0;

      // Remove an object that will rely on the Project's signals. If
      // nulltpr or not present, nothing happens.
      virtual void remove_signalbox(Abstract_Project_Signalbox* a_signalbox) = 0;

      // Clear all the signalboxes so that nothing relies on changes to this.
      virtual void clear_signalboxes() = 0;


      // Entity Collection Data
      //------------------------------------------------------------
      // Are there any entities in this Project?
      virtual bool is_empty() const = 0;

      // How many entities are in this Project?
      virtual std::size_t count() const = 0;

      // Does this id appear in the data?
      virtual bool has(Entity_ID const& a_id) const = 0;

      // Get the index of the data associated with the supplied id. This is the current position
      // in the project's collection of data for this type of data. If the id is null or invalid,
      // the returned index is equal to count().
      virtual std::size_t index(Entity_ID const& a_id) const = 0;

      // Get the id at this index. If the index is invalid a null id is returned.
      virtual Entity_ID get_at(std::size_t a_index) const = 0;

      // Get the id with this name. If the name is invalid a null id is returned.
      virtual Entity_ID get_named(QString const& a_name) const = 0;

      // Get all the ids in data order
      virtual std::vector<Entity_ID> get_all() const = 0;

      // Does this name appear in the data?
      virtual bool has_name(QString const&) const = 0;

      // Get all the objects names in data order
      virtual std::vector<QString> get_all_names() const = 0;

      // Alter the supplied name so that it is unique among the existing data names
      virtual void fix_name(QString&) const = 0;


      // Buildables
      //------------------------------------------------------------
      // Is this entity buildable?
      virtual bool is_buildable(Entity_ID const& a_id) const = 0;

      // Get all the buildable entities.
      virtual std::vector<Entity_ID> get_all_buildable() const = 0;


      // Entity Collection Editing
      //------------------------------------------------------------
      // Undoable make a new entity using the supplied typestring. If the typestring is invalid the returned
      // id is null, otherwise it is the id of the new entity.
      virtual Entity_ID try_make(Signal_Source a_source, QString const& a_type) = 0;

      // Undoable add a new object using the supplied handle. The name will be modified if it is currently in
      // use by another object. Return true if the operation resulted in an undoable command. If this handle
      // is invalid or already in the data then nothing happens and returns false.
      //virtual bool try_add(Signal_Source a_source, ID_Type const& a_id) = 0;

      // Undoable remove entity. Return true if the operation resulted in an undoable command.
      virtual bool try_remove(Signal_Source a_source, Entity_ID const& a_id) = 0;

      // Request that the editor for this entity be opened or switched to.
      virtual bool try_request_editor(Signal_Source a_source, Entity_ID const& a_id) = 0;

      // Request that the focus change to this entity.
      virtual bool try_request_outliner(Signal_Source a_source, Entity_ID const& a_id) = 0;


      // Entity Data
      //------------------------------------------------------------
      // Get the name of the data associated with the supplied id. If the id is null or invalid,
      // the returned name is empty, which names cannot be.
      virtual QString name(Entity_ID const& a_id) const = 0;

      // Attempt an undoable change to the name of the data associated with the supplied id. If
      // the id is valid and the supplied value results in a change to the data, signals are emitted
      // telling everything to update this name, and true is returned. If the id is null or
      // invalid, nothing happens and false is returned. Success does not indicate that the name
      // is set to what has been supplied, but that the name has changed.
      virtual bool try_set_name(Signal_Source a_source, Entity_ID const& a_id, QString const& a_name) = 0;


      // Member Interface
      //------------------------------------------------------------
      // Attempt to get the data value for the member at this index in the data associated with the
      // supplied id. If the id is valid and index is valid for that entity, the returned variant
      // contains the data value in the proper type. If id is null or invalid, or the index is invalid
      // for a valid id, the variant is invalid.
      virtual Variant try_get(Entity_ID const& a_id, std::size_t a_index) const = 0;

      // As try_get except the member is found by matching to the name and not its index. If the name
      // is empty or not present, the returned variant is invalid.
      virtual Variant try_get_named(Entity_ID const& a_id, QString const& a_name) const = 0;

      // Attempt an undoable change to the data value for the member at this index in the data
      // associated with the supplied id. If the id is valid, the index is valid for that entity, and
      // the variant is the right data type, then the change is made and true is returned. If the id
      // is null or invalid, or the variant is the wrong type, nothing happens and false is returned.
      virtual bool try_set(Signal_Source a_source, Entity_ID const& a_id, std::size_t a_index, Variant const& a_value) = 0;

      // As try_set except the member is found by matching to the name and not its index. If the name
      // is empty or not present, the operation fails and returns false.
      virtual bool try_set_named(Signal_Source a_source, Entity_ID const& a_id, QString const& a_name, Variant const& a_value) = 0;
    };
  }
  //------------------------------------------------------------------------------------------------------------------------------------------------------

} // namespace sak

//------------------------------------------------------------------------------------------------------------------------------------------------------

template <std::size_t LI, std::size_t MI, std::size_t LL, std::size_t ML, typename...Args>
sak::Abstract_Member_Interface_Imp<flamingo::typelist<Args...>,LI,MI,LL,ML>::~Abstract_Member_Interface_Imp() = default;

template <std::size_t LI, std::size_t LL, std::size_t ML, typename...Args>
sak::Abstract_Member_Interface_Imp<flamingo::typelist<Args...>,LI,ML,LL,ML>::~Abstract_Member_Interface_Imp() = default;

template <std::size_t LL, std::size_t ML, typename...Args>
sak::Abstract_Member_Interface_Imp<flamingo::typelist<Args...>,LL,ML,LL,ML>::~Abstract_Member_Interface_Imp() = default;

template <std::size_t LI, std::size_t LS, typename...Args>
sak::Abstract_Section_Interface_Imp<flamingo::typelist<Args...>,LI,LS>::~Abstract_Section_Interface_Imp() = default;

template <std::size_t LS, typename...Args>
sak::Abstract_Section_Interface_Imp<flamingo::typelist<Args...>,LS,LS>::~Abstract_Section_Interface_Imp() = default;

template <typename T, typename...Args>
sak::Abstract_Project_Interface_Imp<T,Args...>::~Abstract_Project_Interface_Imp() = default;


#endif // SAK_ABSTRACT_PROJECT_INTERFACE_HPP
