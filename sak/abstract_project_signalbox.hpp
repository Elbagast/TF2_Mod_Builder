#ifndef SAK_ABSTRACT_PROJECT_SIGNALBOX_HPP
#define SAK_ABSTRACT_PROJECT_SIGNALBOX_HPP

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

namespace sak
{
  //---------------------------------------------------------------------------
  // Abstract_Section_Signalbox_Imp<List, Index, End>
  //---------------------------------------------------------------------------
  // Declaration and default arguments for the template class that builds the
  // template chain.
  template
  <
    typename T_List,
    std::size_t Index = 0,
    std::size_t End = (flamingo::typelist_size_v<T_List>)
  >
  class Abstract_Section_Signalbox_Imp;

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Abstract_Section_Signalbox_Imp<List, Index, End>
  //---------------------------------------------------------------------------
  // For a type that isn't at the end of the list.
  template <std::size_t Index, std::size_t End, typename...Args>
  class Abstract_Section_Signalbox_Imp<flamingo::typelist<Args...>,Index,End> :
      protected Abstract_Section_Signalbox_Imp<flamingo::typelist<Args...>,Index+1,End>
  {
    using Inh = Abstract_Section_Signalbox_Imp<flamingo::typelist<Args...>,Index+1,End>;

    using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,Index>;
    using ID_Type = ID<Type>;

  public:
    // Special 6
    //============================================================
    ~Abstract_Section_Signalbox_Imp() override = 0;

    // Interface
    //============================================================
    // When data has been added at a given index.
    virtual void added(Signal_Source a_source, ID_Type const& a_id, std::size_t a_index) = 0;

    // When data has been removed from a given index.
    virtual void removed(Signal_Source a_source, ID_Type const& a_id, std::size_t a_index) = 0;

    // When data at a given index has been moved to another index.
    virtual void moved(Signal_Source a_source, ID_Type const& a_id, std::size_t a_from, std::size_t a_to) = 0;

    // When data at a given index has its name changed.
    virtual void changed_name(Signal_Source a_source, ID_Type const& a_id, std::size_t a_index) = 0;

    // When data at a given index has all of its data changed.
    virtual void changed_data(Signal_Source a_source, ID_Type const& a_id, std::size_t a_index) = 0;

    // When data at a given index has its data changed in a specific place.
    virtual void changed_data_at(Signal_Source a_source, ID_Type const& a_id, std::size_t a_index, std::size_t a_member) = 0;

    // When data at a given index requests its editor be opened/brought to the top.
    virtual void requests_editor(Signal_Source a_source, ID_Type const& a_id, std::size_t a_index) = 0;

    // When data at a given index requests focus in the outliner.
    virtual void requests_outliner(Signal_Source a_source, ID_Type const& a_id, std::size_t a_index) = 0;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Abstract_Project_Signalbox_Section_Imp<List, End, End>
  //---------------------------------------------------------------------------
  // For the last type in the list
  template <std::size_t End, typename...Args>
  class Abstract_Section_Signalbox_Imp<flamingo::typelist<Args...>,End,End>
  {
  public:
    // Special 6
    //============================================================
    virtual ~Abstract_Section_Signalbox_Imp() = 0;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Project_Signalbox_Data_Imp<T,Args...>
  //---------------------------------------------------------------------------
  // The top class of the template chain, where we gather and cleanup
  // everything. Also the requirement of at least one type stops bad template
  // instantiations.
  template <typename T, typename...Args>
  class Abstract_Project_Signalbox_Imp :
      protected Abstract_Section_Signalbox_Imp<flamingo::typelist<T,Args...>>
  {
    using Inh = Abstract_Section_Signalbox_Imp<flamingo::typelist<T,Args...>>;
    using Typelist_Type = flamingo::typelist<T,Args...>;

    static_assert(flamingo::typelist_all_unique_v<Typelist_Type>,
                  "Cannot have repeating types in the supplied template arguments.");

    template <typename U>
    using Abstract_Section_Signalbox_Type =
    Abstract_Section_Signalbox_Imp
    <
      Typelist_Type,
      flamingo::typelist_find_v<Typelist_Type, U>
    >;
    template <std::size_t I>

    using Abstract_Section_Signalbox_At =
    Abstract_Section_Signalbox_Imp
    <
      Typelist_Type,
      I
    >;

  public:
    // Special 6
    //============================================================
    ~Abstract_Project_Signalbox_Imp() override = 0;

    // Intreface
    //============================================================

    // Section Interface Access
    //------------------------------------------------------------

    template <typename U>
    Abstract_Section_Signalbox_Type<U>* get_signalbox()
    {
      static_assert(flamingo::typelist_find_v<Typelist_Type,U> != flamingo::typelist_size_v<Typelist_Type>,
                    "Cannot make interface, type not present.");
      return this;
    }

    template <typename U>
    Abstract_Section_Signalbox_Type<U> const* cget_signalbox() const
    {
      static_assert(flamingo::typelist_find_v<Typelist_Type,U> != flamingo::typelist_size_v<Typelist_Type>,
                    "Cannot make interface, type not present.");
      return this;
    }

    template <std::size_t I>
    Abstract_Section_Signalbox_At<I>* get_signalbox_at()
    {
      static_assert(I < flamingo::typelist_size_v<Typelist_Type>,
                    "Cannot make interface, type index is out of range.");
      return this;
    }

    template <std::size_t I>
    Abstract_Section_Signalbox_At<I> const* cget_signalbox_at() const
    {
      static_assert(I < flamingo::typelist_size_v<Typelist_Type>,
                    "Cannot make interface, type index is out of range.");
      return this;
    }
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

} // namespace sak

template <std::size_t Index, std::size_t End, typename...Args>
sak::Abstract_Section_Signalbox_Imp<flamingo::typelist<Args...>,Index,End>::~Abstract_Section_Signalbox_Imp() = default;

template <std::size_t End, typename...Args>
sak::Abstract_Section_Signalbox_Imp<flamingo::typelist<Args...>,End,End>::~Abstract_Section_Signalbox_Imp() = default;

template <typename T, typename...Args>
sak::Abstract_Project_Signalbox_Imp<T,Args...>::~Abstract_Project_Signalbox_Imp() = default;

#endif // SAK_ABSTRACT_PROJECT_SIGNALBOX_HPP
