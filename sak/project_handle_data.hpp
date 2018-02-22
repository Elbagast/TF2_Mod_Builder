#ifndef SAK_PROJECT_HANDLE_DATA_HPP
#define SAK_PROJECT_HANDLE_DATA_HPP

#ifndef SAK_PROJECT_HANDLE_DATA_FWD_HPP
#include "project_handle_data_fwd.hpp"
#endif

#ifndef SAK_TAG_FWD_HPP
#include "tag_fwd.hpp"
#endif

#ifndef SAK_ID_HPP
#include "id.hpp"
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
  //---------------------------------------------------------------------------
  // Section_Handle_Data_Imp<List, Index, End>
  //---------------------------------------------------------------------------
  // Declaration and default arguments for the template class that builds the
  // template chain. This class's purpose is to hold all of the handles for all
  // of the supplied types and implement name actions that can be done on them.
  template
  <
    typename T_List,
    std::size_t Index = 0,
    std::size_t End = (flamingo::typelist_size_v<T_List>)
  >
  class Section_Handle_Data_Imp;

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Section_Handle_Data_Imp<List, Index, End>
  //---------------------------------------------------------------------------
  // For a type that isn't at the end of the list.
  template <std::size_t Index, std::size_t End, typename...Args>
  class Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index,End> :
      protected Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index+1,End>
  {
    // Typedefs
    //============================================================
    using Inh = Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index+1,End>;

    using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,Index>;
    using Handle_Type = Handle<Type>;
    using Tag_Type = Tag<Type>;
    using ID_Type = ID<Type>;

  public:
    // Special 6
    //============================================================
    Section_Handle_Data_Imp();
    ~Section_Handle_Data_Imp();

    Section_Handle_Data_Imp(Section_Handle_Data_Imp const&);
    Section_Handle_Data_Imp& operator=(Section_Handle_Data_Imp const&);

    Section_Handle_Data_Imp(Section_Handle_Data_Imp &&);
    Section_Handle_Data_Imp& operator=(Section_Handle_Data_Imp &&);

    // Interface
    //============================================================
    // User Interface
    //------------------------------------------------------------
    // This part will get used by the interface implementor.

    // Are there any objects in this Project?
    bool is_empty(Tag_Type&&) const;

    // How many objects are in this Project?
    std::size_t count(Tag_Type&&) const;

    // Does this id appear in the data?
    bool has(ID_Type const& a_id) const;

    // Get the index of the id in the data. If the id is not present or is null,
    // the returned value is equal to count().
    std::size_t index(ID_Type const& a_id) const;

    // Get the name data associted with this id. If the id is not present or is null,
    // the returned value is empty.
    QString name(ID_Type const& a_id) const;

    // Does this name appear in the data?
    bool has_name(Tag_Type&&, QString const&) const;

    // Get the id at this index. If the index is invalid a null id is returned.
    ID_Type get_at(Tag_Type&&, std::size_t a_index) const;

    // Get the id with this name. If the name is invalid a null id is returned.
    ID_Type get_named(Tag_Type&&, QString const&) const;

    // Get all the ids in data order
    std::vector<ID_Type> get_ids(Tag_Type&&) const;

    // Get all the handles names in data order
    std::vector<QString> get_names(Tag_Type&&) const;

    // Internal Interface
    //------------------------------------------------------------
    // This part will get used by the data implementor.

    // Does this handle appear in the data?
    bool has_handle(Handle_Type const& a_handle) const;

    // Get the handle for this id. If the id is invalid or null a null handle is returned.
    Handle_Type get_handle(ID_Type const& a_id) const;

    // Get the handle at this index. If the index is invalid a null handle is returned.
    Handle_Type get_handle_at(Tag_Type&&, std::size_t a_index) const;

    // Get the handle with this name. If the name is invalid a null handle is returned.
    Handle_Type get_handle_named(Tag_Type&&, QString const& a_name) const;

    // Determine what index a handle would be at if it were added to the current data
    // with this name. If the name is empty or already present, the result is count().
    std::size_t future_index(QString const& a_name) const;

    // Add a handle to the collection and return its index. If the handle is null or
    // already present, nothing happens and return count().
    std::size_t add(Handle_Type const& a_handle);

    // Remove the handle at this index from the collection and return true. If the handle
    // is null or not present, nothing happens and return false.
    bool remove(Tag_Type&&, std::size_t a_index);

    // Access the handles for direct manipulation.
    std::vector<Handle_Type>& get_handles(Tag_Type&&);

    // Also const access.
    std::vector<Handle_Type> const& cget_handles(Tag_Type&&) const;

  private:
    std::vector<Handle_Type> m_handles;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Section_Handle_Data_Imp<List, End, End>
  //---------------------------------------------------------------------------
  // For a type that isn't at the end of the list.
  template <std::size_t End, typename...Args>
  class Section_Handle_Data_Imp<flamingo::typelist<Args...>,End,End>
  {

  public:
    // Special 6
    //============================================================
    Section_Handle_Data_Imp();
    ~Section_Handle_Data_Imp();

    Section_Handle_Data_Imp(Section_Handle_Data_Imp const&);
    Section_Handle_Data_Imp& operator=(Section_Handle_Data_Imp const&);

    Section_Handle_Data_Imp(Section_Handle_Data_Imp &&);
    Section_Handle_Data_Imp& operator=(Section_Handle_Data_Imp &&);
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

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
      protected Section_Handle_Data_Imp<flamingo::typelist<T,Args...>>
  {
    // Typedefs
    //============================================================
    using Inh = Section_Handle_Data_Imp<flamingo::typelist<T,Args...>>;
    using Typelist_Type = flamingo::typelist<T,Args...>;
    static_assert(flamingo::typelist_all_unique_v<Typelist_Type>,
                  "Cannot have repeating types in the supplied template arguments.");

    template <typename U>
    using Section_Handle_Data_Type =
    Section_Handle_Data_Imp
    <
      Typelist_Type,
      flamingo::typelist_find_v<Typelist_Type, U>
    >;

    template <std::size_t I>
    using Section_Handle_Data_At =
    Section_Handle_Data_Imp
    <
      Typelist_Type,
      I
    >;

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

    // Section Interface Access
    //------------------------------------------------------------
    template <typename U>
    Section_Handle_Data_Type<U>* get_section()
    {
      static_assert(flamingo::typelist_find_v<Typelist_Type,U> != flamingo::typelist_size_v<Typelist_Type>,
                    "Cannot get data, type not present.");
      return this;
    }

    template <typename U>
    Section_Handle_Data_Type<U> const* cget_section() const
    {
      static_assert(flamingo::typelist_find_v<Typelist_Type,U> != flamingo::typelist_size_v<Typelist_Type>,
                    "Cannot get data, type not present.");
      return this;
    }

    template <std::size_t I>
    Section_Handle_Data_At<I>* get_section_at()
    {
      static_assert(I < flamingo::typelist_size_v<Typelist_Type>,
                    "Cannot get data, type index is out of range.");
      return this;
    }

    template <std::size_t I>
    Section_Handle_Data_At<I> const* cget_section_at() const
    {
      static_assert(I < flamingo::typelist_size_v<Typelist_Type>,
                    "Cannot get data, type index is out of range.");
      return this;
    }

  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

} // namespace sak

#endif // SAK_PROJECT_HANDLE_DATA_HPP
