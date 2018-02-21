#ifndef SAK_PROJECT_SIGNALBOX_DATA_HPP
#define SAK_PROJECT_SIGNALBOX_DATA_HPP

#ifndef SAK_PROJECT_SIGNALBOX_DATA_FWD_HPP
#include "project_signalbox_data_fwd.hpp"
#endif

#ifndef SAK_ABSTRACT_PROJECT_SIGNALBOX_FWD_HPP
#include "abstract_project_signalbox_fwd.hpp"
#endif

#ifndef SAK_ID_FWD_HPP
#include "id_fwd.hpp"
#endif

#ifndef SAK_SIGNAL_SOURCE_FWD_HPP
#include "signal_source_fwd.hpp"
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


namespace sak
{
  //---------------------------------------------------------------------------
  // Section_Signalbox_Data_Imp<List, Index, End>
  //---------------------------------------------------------------------------
  // Declaration and default arguments for the template class that builds the
  // template chain.
  template
  <
    typename T_List,
    std::size_t Index = 0,
    std::size_t End = (flamingo::typelist_size_v<T_List>)
  >
  class Section_Signalbox_Data_Imp;

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Section_Signalbox_Data_Imp<List, Index, End>
  //---------------------------------------------------------------------------
  // For a type that isn't at the end of the list.
  template <std::size_t Index, std::size_t End, typename...Args>
  class Section_Signalbox_Data_Imp<flamingo::typelist<Args...>,Index,End> :
      protected Section_Signalbox_Data_Imp<flamingo::typelist<Args...>,Index+1,End>
  {
    using Inh = Section_Signalbox_Data_Imp<flamingo::typelist<Args...>,Index+1,End>;
    using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,Index>;
    using ID_Type = ID<Type>;

  public:
    // Typedefs
    //============================================================
    using Signalbox_Type = typename Inh::Signalbox_Type;

    // Special 6
    //============================================================
    Section_Signalbox_Data_Imp();
    ~Section_Signalbox_Data_Imp();

    Section_Signalbox_Data_Imp(Section_Signalbox_Data_Imp const&);
    Section_Signalbox_Data_Imp& operator=(Section_Signalbox_Data_Imp const&);

    Section_Signalbox_Data_Imp(Section_Signalbox_Data_Imp &&);
    Section_Signalbox_Data_Imp& operator=(Section_Signalbox_Data_Imp &&);

    // Interface
    //============================================================
    // calls each of these on all the stored signalboxes.

    // When data has been added at a given index.
    void added(Signal_Source a_source, ID_Type const& a_id, std::size_t a_index);

    // When data has been removed from a given index.
    void removed(Signal_Source a_source, ID_Type const& a_id, std::size_t a_index);

    // When data at a given index has been moved to another index.
    void moved(Signal_Source a_source, ID_Type const& a_id, std::size_t a_from, std::size_t a_to);

    // When data at a given index has its name changed.
    void changed_name(Signal_Source a_source, ID_Type const& a_id, std::size_t a_index);

    // When data at a given index has all of its data changed.
    void changed_data(Signal_Source a_source, ID_Type const& a_id, std::size_t a_index);

    // When data at a given index has its data changed in a specific place.
    void changed_data_at(Signal_Source a_source, ID_Type const& a_id, std::size_t a_index, std::size_t a_member);

    // When data at a given index requests its editor be opened/brought to the top.
    void requests_editor(Signal_Source a_source, ID_Type const& a_id, std::size_t a_index);

    // When data at a given index requests focus in the outliner.
    void requests_outliner(Signal_Source a_source, ID_Type const& a_id, std::size_t a_index);


    using Inh::add_signalbox;
    using Inh::remove_signalbox;
    using Inh::clear_signalboxes;

  protected:
    // Internal Interface
    //============================================================
    // Access the signalboxes so functions can be called in them.
    using Inh::get_signalboxes;
    using Inh::cget_signalboxes;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Section_Signalbox_Data_Imp<List, End, End>
  //---------------------------------------------------------------------------
  // The end is one past the last element in the list so implement the data
  // here.
  template <std::size_t End, typename...Args>
  class Section_Signalbox_Data_Imp<flamingo::typelist<Args...>,End,End>
  {
  public:
    // Typedefs
    //============================================================
    using Signalbox_Type = Abstract_Project_Signalbox_Imp<Args...>;

    // Special 6
    //============================================================
    Section_Signalbox_Data_Imp();
    ~Section_Signalbox_Data_Imp();

    Section_Signalbox_Data_Imp(Section_Signalbox_Data_Imp const&);
    Section_Signalbox_Data_Imp& operator=(Section_Signalbox_Data_Imp const&);

    Section_Signalbox_Data_Imp(Section_Signalbox_Data_Imp &&);
    Section_Signalbox_Data_Imp& operator=(Section_Signalbox_Data_Imp &&);

    // Interface
    //============================================================

    // Add an object that will rely on the Project's signals. If nulltpr, nothing happens.
    void add_signalbox(Signalbox_Type* a_signalbox);

    // Remove an object that will rely on the Project's signals. If nulltpr, nothing happens.
    void remove_signalbox(Signalbox_Type* a_signalbox);

    // Clear all the signalboxes so that nothing relies on changes to this.
    void clear_signalboxes();

  protected:
    // Internal Interface
    //============================================================
    // Access the signalboxes so functions can be called in them.
    std::vector<Signalbox_Type*>& get_signalboxes();
    std::vector<Signalbox_Type*> const& cget_signalboxes() const;

  private:
    // Data Members
    //============================================================
    std::vector<Signalbox_Type*> m_signalboxes;
  };
  //------------------------------------------------------------------------------------------------------------------------------------------------------


  //---------------------------------------------------------------------------
  // Project_Signalbox_Data_Imp<T,Args...>
  //---------------------------------------------------------------------------
  // The top class of the template chain, where we gather and cleanup
  // everything. Also the requirement of at least one type stops bad template
  // instantiations.
  template <typename T, typename...Args>
  class Project_Signalbox_Data_Imp :
      protected Section_Signalbox_Data_Imp<flamingo::typelist<T,Args...>>
  {
    using Inh = Section_Signalbox_Data_Imp<flamingo::typelist<T,Args...>>;

    // Typedefs
    //============================================================
    using Typelist_Type = flamingo::typelist<T,Args...>;
    static_assert(flamingo::typelist_all_unique_v<Typelist_Type>,
                  "Cannot have repeating types in the supplied template arguments.");

    template <typename U>
    using Section_Signalbox_Data_Type =
    Section_Signalbox_Data_Imp
    <
      Typelist_Type,
      flamingo::typelist_find_v<Typelist_Type, U>
    >;

    template <std::size_t I>
    using Section_Signalbox_Data_At =
    Section_Signalbox_Data_Imp
    <
      Typelist_Type,
      I
    >;

  public:
    using Signalbox_Type = typename Inh::Signalbox_Type;
    // Special 6
    //============================================================
    Project_Signalbox_Data_Imp();
    ~Project_Signalbox_Data_Imp();

    Project_Signalbox_Data_Imp(Project_Signalbox_Data_Imp const&);
    Project_Signalbox_Data_Imp& operator=(Project_Signalbox_Data_Imp const&);

    Project_Signalbox_Data_Imp(Project_Signalbox_Data_Imp &&);
    Project_Signalbox_Data_Imp& operator=(Project_Signalbox_Data_Imp &&);

    // Interface
    //============================================================

    // Data Interface
    //------------------------------------------------------------
    using Inh::add_signalbox;
    using Inh::remove_signalbox;
    using Inh::clear_signalboxes;

    // Section Interface Access
    //------------------------------------------------------------
    template <typename U>
    Section_Signalbox_Data_Type<U>* get_section()
    {
      static_assert(flamingo::typelist_find_v<Typelist_Type,U> != flamingo::typelist_size_v<Typelist_Type>,
                    "Cannot get data, type not present.");
      return this;
    }

    template <typename U>
    Section_Signalbox_Data_Type<U> const* cget_section() const
    {
      static_assert(flamingo::typelist_find_v<Typelist_Type,U> != flamingo::typelist_size_v<Typelist_Type>,
                    "Cannot get data, type not present.");
      return this;
    }

    template <std::size_t I>
    Section_Signalbox_Data_At<I>* get_section_at()
    {
      static_assert(I < flamingo::typelist_size_v<Typelist_Type>,
                    "Cannot get data, type index is out of range.");
      return this;
    }

    template <std::size_t I>
    Section_Signalbox_Data_At<I> const* cget_section_at() const
    {
      static_assert(I < flamingo::typelist_size_v<Typelist_Type>,
                    "Cannot get data, type index is out of range.");
      return this;
    }

  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

} // namespace sak

#endif // SAK_PROJECT_SIGNALBOX_DATA_HPP
