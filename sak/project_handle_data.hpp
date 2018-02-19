﻿#ifndef SAK_PROJECT_HANDLE_DATA_HPP
#define SAK_PROJECT_HANDLE_DATA_HPP

#ifndef SAK_PROJECT_HANDLE_DATA_FWD_HPP
#include "project_handle_data_fwd.hpp"
#endif

#ifndef SAK_TAG_FWD_HPP
#include "tag_fwd.hpp"
#endif

#ifndef SAK_HANDLE_HPP
#include "handle.hpp"
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
    // Project_Handle_Data_Part_Imp<List, Index, End>
    //---------------------------------------------------------------------------
    // Declaration and default arguments for the template class that builds the
    // template chain. This class's purpose is to hold all of the handles for all
    // of the supplied types and implement name actions that can be done on them.
    template
    <
      typename T_List,
      std::size_t Index = 0,
      std::size_t End = (flamingo::typelist_size_v<T_List> - 1)
    >
    class Project_Handle_Data_Part_Imp;

    //------------------------------------------------------------------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    // Project_Handle_Data_Part_Imp<List, Index, End>
    //---------------------------------------------------------------------------
    // For a type that isn't at the end of the list.
    template <std::size_t Index, std::size_t End, typename...Args>
    class Project_Handle_Data_Part_Imp<flamingo::typelist<Args...>,Index,End> :
        protected Project_Handle_Data_Part_Imp<flamingo::typelist<Args...>,Index+1,End>
    {
      // Typedefs
      //============================================================
      using Inh = Project_Handle_Data_Part_Imp<flamingo::typelist<Args...>,Index+1,End>;

      using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,Index>;
      using Handle_Type = Handle<Type>;
      using Tag_Type = Tag<Type>;

    public:
      // Special 6
      //============================================================
      Project_Handle_Data_Part_Imp();
      ~Project_Handle_Data_Part_Imp();

      Project_Handle_Data_Part_Imp(Project_Handle_Data_Part_Imp const&);
      Project_Handle_Data_Part_Imp& operator=(Project_Handle_Data_Part_Imp const&);

      Project_Handle_Data_Part_Imp(Project_Handle_Data_Part_Imp &&);
      Project_Handle_Data_Part_Imp& operator=(Project_Handle_Data_Part_Imp &&);

      // Interface
      //============================================================
      // Are there any objects in this Project?
      bool is_empty(Tag_Type&&) const;

      // How many objects are in this Project?
      std::size_t count(Tag_Type&&) const;

      // Does this handle appear in the data?
      bool has_handle(Handle_Type const& a_handle) const;

      // Does this name appear in the data?
      bool has_handle_named(Tag_Type&&, QString const& a_name) const;

      // Get the handle at this index. If the index is invalid a null handle is returned.
      Handle_Type get_handle_at(Tag_Type&&, std::size_t a_index) const;

      // Get the handle with this name. If the name is invalid a null handle is returned.
      Handle_Type get_handle_named(Tag_Type&&, QString const& a_name) const;

      // Get all the handles names in data order
      std::vector<QString> get_names(Tag_Type&&) const;

      // Access the handles for direct manipulation.
      std::vector<Handle_Type>& get_handles(Tag_Type&&);
      std::vector<Handle_Type> const& cget_handles(Tag_Type&&) const;

      using Inh::is_empty;
      using Inh::count;
      using Inh::has_handle;
      using Inh::has_handle_named;
      using Inh::get_handle_at;
      using Inh::get_names;
      using Inh::get_handles;
      using Inh::cget_handles;

    private:
      std::vector<Handle_Type> m_handles;
    };

    //------------------------------------------------------------------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    // Project_Handle_Data_Part_Imp<List, End, End>
    //---------------------------------------------------------------------------
    // For a type that isn't at the end of the list.
    template <std::size_t End, typename...Args>
    class Project_Handle_Data_Part_Imp<flamingo::typelist<Args...>,End,End>
    {
      // Typedefs
      //============================================================
      using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,End>;
      using Handle_Type = Handle<Type>;
      using Tag_Type = Tag<Type>;

    public:
      // Special 6
      //============================================================
      Project_Handle_Data_Part_Imp();
      ~Project_Handle_Data_Part_Imp();

      Project_Handle_Data_Part_Imp(Project_Handle_Data_Part_Imp const&);
      Project_Handle_Data_Part_Imp& operator=(Project_Handle_Data_Part_Imp const&);

      Project_Handle_Data_Part_Imp(Project_Handle_Data_Part_Imp &&);
      Project_Handle_Data_Part_Imp& operator=(Project_Handle_Data_Part_Imp &&);

      // Interface
      //============================================================
      // Are there any objects in this Project?
      bool is_empty(Tag_Type&&) const;

      // How many objects are in this Project?
      std::size_t count(Tag_Type&&) const;

      // Does this handle appear in the data?
      bool has_handle(Handle_Type const& a_handle) const;
      // Does this name appear in the data?

      bool has_handle_named(Tag_Type&&, QString const& a_name) const;

      // Get the handle at this index. If the index is invalid a null handle is returned.
      Handle_Type get_handle_at(Tag_Type&&, std::size_t a_index) const;

      // Get the handle with this name. If the name is invalid a null handle is returned.
      Handle_Type get_handle_named(Tag_Type&&, QString const& a_name) const;

      // Get all the handles names in data order
      std::vector<QString> get_names(Tag_Type&&) const;

      // Access the handles for direct manipulation.
      std::vector<Handle_Type>& get_handles(Tag_Type&&);
      std::vector<Handle_Type> const& cget_handles(Tag_Type&&) const;

    private:
      std::vector<Handle_Type> m_handles;
    };
    //------------------------------------------------------------------------------------------------------------------------------------------------------

  } // namespace internal

  //---------------------------------------------------------------------------
  // Project_Handle_Data_Imp<T,Args...>
  //---------------------------------------------------------------------------
  // The bit that holds all of the Project data allowing access for layers that
  // need all of it. This object does nothing whatsoever to enure that the data
  // follows any rules, it merely hold it. This is mostly because the final
  // layer imposes the rules on the data and is going to need all sorts of
  // things in order to carry out operations like adding, removing and renaming
  // handles and emitting the proper signals.

  template <typename T, typename...Args>
  class Project_Handle_Data_Imp :
      protected internal::Project_Handle_Data_Part_Imp<flamingo::typelist<T,Args...>>
  {
    // Typedefs
    //============================================================
    using Inh = internal::Project_Handle_Data_Part_Imp<flamingo::typelist<T,Args...>>;
  public:
    // Special 6
    //============================================================
    Project_Handle_Data_Imp();
    ~Project_Handle_Data_Imp();

    Project_Handle_Data_Imp(Project_Handle_Data_Imp const&);
    Project_Handle_Data_Imp& operator=(Project_Handle_Data_Imp const&);

    Project_Handle_Data_Imp(Project_Handle_Data_Imp &&);
    Project_Handle_Data_Imp& operator=(Project_Handle_Data_Imp &&);

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

    // Handles Interface
    //------------------------------------------------------------
    using Inh::is_empty;
    using Inh::count;
    using Inh::has_handle;
    using Inh::has_handle_named;
    using Inh::get_handle_at;
    using Inh::get_names;
    using Inh::get_handles;
    using Inh::cget_handles;

    // Functions are as follows, with overloads for each Type in the
    // the arguments <T,Args...>:
    //------------------------------------------------------------
    // Are there any objects in this Project?
    //bool is_empty(Tag_Type&&) const;

    // How many objects are in this Project?
    //std::size_t count(Tag_Type&&) const;

    // Does this handle appear in the data?
    //bool has_handle(Handle_Type const& a_handle) const;

    // Does this name appear in the data?
    //bool has_handle_named(Tag_Type&&, QString const& a_name) const;

    // Get the handle at this index. If the index is invalid a null handle is returned.
    //Handle_Type get_handle_at(Tag_Type&&, std::size_t a_index) const;

    // Get the handle with this name. If the name is invalid a null handle is returned.
    //Handle_Type get_handle_named(Tag_Type&&, QString const& a_name) const;

    // Get all the handles names in data order
    //std::vector<QString> get_names(Tag_Type&&) const;

    // Access the handles for direct manipulation.
    //std::vector<Handle_Type>& get_handles(Tag_Type&&);
    //std::vector<Handle_Type> const& cget_handles(Tag_Type&&) const;
  };
  //------------------------------------------------------------------------------------------------------------------------------------------------------

} // namespace sak

#endif // SAK_PROJECT_HANDLE_DATA_HPP