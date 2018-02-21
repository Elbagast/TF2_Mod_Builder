#ifndef SAK_PROJECT_HANDLE_FACTORY_HPP
#define SAK_PROJECT_HANDLE_FACTORY_HPP

#ifndef SAK_PROJECT_HANDLE_FACTORY_FWD_HPP
#include "project_handle_factory_fwd.hpp"
#endif

#ifndef SAK_TAG_FWD_HPP
#include "tag_fwd.hpp"
#endif

#ifndef SAK_HANDLE_FWD_HPP
#include "handle_fwd.hpp"
#endif

#ifndef SAK_DATA_FWD_HPP
#include "data_fwd.hpp"
#endif

#ifndef FLAMINGO_TYPELIST_HPP
#include <flamingo/typelist.hpp>
#endif

class QString;

namespace sak
{
  //---------------------------------------------------------------------------
  // Section_Handle_Factory_Imp<List, Index, End>
  //---------------------------------------------------------------------------
  // Declaration and default arguments for the template class that builds the
  // template chain.
  template
  <
    typename T_List,
    std::size_t Index = 0,
    std::size_t End = (flamingo::typelist_size_v<T_List>)
  >
  class Section_Handle_Factory_Imp;

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Section_Handle_Factory_Imp<List, Index, End>
  //---------------------------------------------------------------------------
  // For a type that isn't at the end of the list.

  template <std::size_t Index, std::size_t End, typename...Args>
  class Section_Handle_Factory_Imp<flamingo::typelist<Args...>,Index,End> :
      protected Section_Handle_Factory_Imp<flamingo::typelist<Args...>,Index+1,End>
  {
    // Typedefs
    //============================================================
    using Inh = Section_Handle_Factory_Imp<flamingo::typelist<Args...>,Index+1,End>;

    using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,Index>;
    using Handle_Type = Handle<Type>;
    using Data_Type = Data<Type>;
    using Tag_Type = Tag<Type>;

  public:
    // Special 6
    //============================================================
    Section_Handle_Factory_Imp();
    ~Section_Handle_Factory_Imp();

    Section_Handle_Factory_Imp(Section_Handle_Factory_Imp const&);
    Section_Handle_Factory_Imp& operator=(Section_Handle_Factory_Imp const&);

    Section_Handle_Factory_Imp(Section_Handle_Factory_Imp &&);
    Section_Handle_Factory_Imp& operator=(Section_Handle_Factory_Imp &&);

    // Interface
    //============================================================
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
    using Inh::next_id;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Section_Handle_Factory_Imp<List, End, End>
  //---------------------------------------------------------------------------
  // For the type that is at the end of the list.

  template <std::size_t End, typename...Args>
  class Section_Handle_Factory_Imp<flamingo::typelist<Args...>,End,End>
  {
  public:
    // Special 6
    //============================================================
    Section_Handle_Factory_Imp();
    ~Section_Handle_Factory_Imp();

    Section_Handle_Factory_Imp(Section_Handle_Factory_Imp const&);
    Section_Handle_Factory_Imp& operator=(Section_Handle_Factory_Imp const&);

    Section_Handle_Factory_Imp(Section_Handle_Factory_Imp &&);
    Section_Handle_Factory_Imp& operator=(Section_Handle_Factory_Imp &&);

  protected:
    // Get the next id to use for a handle.
    std::size_t next_id() const;
  private:
    mutable std::size_t m_next_id;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Project_Handle_Factory_Imp<T,Args...>
  //---------------------------------------------------------------------------

  template <typename T, typename...Args>
  class Project_Handle_Factory_Imp :
      protected Section_Handle_Factory_Imp<flamingo::typelist<T,Args...>>
  {
    // Typedefs
    //============================================================
    using Inh = Section_Handle_Factory_Imp<flamingo::typelist<T,Args...>>;
    using Typelist_Type = flamingo::typelist<T,Args...>;

    template <typename U>
    using Section_Handle_Factory_Type =
    Section_Handle_Factory_Imp
    <
      Typelist_Type,
      flamingo::typelist_find_v<Typelist_Type, U>
    >;

    template <std::size_t I>
    using Section_Handle_Factory_At =
    Section_Handle_Factory_Imp
    <
      Typelist_Type,
      I
    >;
  public:
    // Special 6
    //============================================================
    Project_Handle_Factory_Imp();
    ~Project_Handle_Factory_Imp();

    Project_Handle_Factory_Imp(Project_Handle_Factory_Imp const&);
    Project_Handle_Factory_Imp& operator=(Project_Handle_Factory_Imp const&);

    Project_Handle_Factory_Imp(Project_Handle_Factory_Imp &&);
    Project_Handle_Factory_Imp& operator=(Project_Handle_Factory_Imp &&);

    // Interface
    //============================================================
    // Access the section interfaces.

    template <typename U>
    Section_Handle_Factory_Type<U>* get_section()
    {
      static_assert(flamingo::typelist_find_v<Typelist_Type,U> != flamingo::typelist_size_v<Typelist_Type>,
                    "Cannot get data, type not present.");
      return this;
    }

    template <typename U>
    Section_Handle_Factory_Type<U> const* cget_section() const
    {
      static_assert(flamingo::typelist_find_v<Typelist_Type,U> != flamingo::typelist_size_v<Typelist_Type>,
                    "Cannot get data, type not present.");
      return this;
    }

    template <std::size_t I>
    Section_Handle_Factory_At<I>* get_section_at()
    {
      static_assert(I < flamingo::typelist_size_v<Typelist_Type>,
                    "Cannot get data, type index is out of range.");
      return this;
    }

    template <std::size_t I>
    Section_Handle_Factory_At<I> const* cget_section_at() const
    {
      static_assert(I < flamingo::typelist_size_v<Typelist_Type>,
                    "Cannot get data, type index is out of range.");
      return this;
    }
  };

} // namespace sak

#endif // SAK_PROJECT_HANDLE_FACTORY_HPP
