#ifndef SAK_ABSTRACT_PROJECT_SIGNALBOX_HPP
#define SAK_ABSTRACT_PROJECT_SIGNALBOX_HPP

#ifndef SAK_ABSTRACT_PROJECT_SIGNALBOX_FWD_HPP
#include "abstract_project_signalbox_fwd.hpp"
#endif

#ifndef SAK_HANDLE_FWD_HPP
#include "handle_fwd.hpp"
#endif

#ifndef SAK_SIGNAL_SOURCE_FWD_HPP
#include "signal_source_fwd.hpp"
#endif

#ifndef FLAMINGO_TYPELIST_HPP
#include <flamingo/typelist.hpp>
#endif

namespace sak
{
  namespace internal
  {
    //---------------------------------------------------------------------------
    // Abstract_Project_Signalbox_Part_Imp<List, Index, End>
    //---------------------------------------------------------------------------
    // Declaration and default arguments for the template class that builds the
    // template chain.
    template
    <
      typename T_List,
      std::size_t Index = 0,
      std::size_t End = (flamingo::typelist_size_v<T_List> - 1)
    >
    class Abstract_Project_Signalbox_Part_Imp;

    //------------------------------------------------------------------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    // Abstract_Project_Signalbox_Part_Imp<List, Index, End>
    //---------------------------------------------------------------------------
    // For a type that isn't at the end of the list.
    template <std::size_t Index, std::size_t End, typename...Args>
    class Abstract_Project_Signalbox_Part_Imp<flamingo::typelist<Args...>,Index,End> :
        public Abstract_Project_Signalbox_Part_Imp<flamingo::typelist<Args...>,Index+1,End>
    {
      using Inh = Abstract_Project_Signalbox_Part_Imp<flamingo::typelist<Args...>,Index+1,End>;

      using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,Index>;

    public:
      // Special 6
      //============================================================
      ~Abstract_Project_Signalbox_Part_Imp() override = 0;

      // Interface
      //============================================================
      // When a handle has been added at a given index.
      virtual void added(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index) = 0;
      // When a handle has been removed from a given index.
      virtual void removed(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index) = 0;
      // When a handle at a given index has been moved to another index.
      virtual void moved(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_from, std::size_t a_to) = 0;
      // When a handle at a given index has its name changed.
      virtual void changed_name(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index) = 0;
      // When a handle at a given index has all of its data changed.
      virtual void changed_data(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index) = 0;
      // When a handle at a given index has its data changed in a specific place.
      virtual void changed_data_at(Signal_Source a_source, Handle<Type> const& a_handler, std::size_t a_index, std::size_t a_member) = 0;
      // When a handle at a given index requests its editor be opened/brought to the top.
      virtual void requests_editor(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index) = 0;
      // When a handle at a given index requests focus in the outliner.
      virtual void requests_outliner(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index) = 0;

      using Inh::added;
      using Inh::removed;
      using Inh::moved;
      using Inh::changed_name;
      using Inh::changed_data;
      using Inh::changed_data_at;
      using Inh::requests_editor;
      using Inh::requests_outliner;
    };

    //------------------------------------------------------------------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    // Abstract_Project_Signalbox_Part_Imp<List, End, End>
    //---------------------------------------------------------------------------
    // For the last type in the list
    template <std::size_t End, typename...Args>
    class Abstract_Project_Signalbox_Part_Imp<flamingo::typelist<Args...>,End,End>
    {
      using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,End>;
    public:

      // Special 6
      //============================================================
      virtual ~Abstract_Project_Signalbox_Part_Imp() = 0;

      // Interface
      //============================================================
      // When a handle has been added at a given index.
      virtual void added(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index) = 0;
      // When a handle has been removed from a given index.
      virtual void removed(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index) = 0;
      // When a handle at a given index has been moved to another index.
      virtual void moved(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_from, std::size_t a_to) = 0;
      // When a handle at a given index has its name changed.
      virtual void changed_name(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index) = 0;
      // When a handle at a given index has all of its data changed.
      virtual void changed_data(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index) = 0;
      // When a handle at a given index has its data changed in a specific place.
      virtual void changed_data_at(Signal_Source a_source, Handle<Type> const& a_handler, std::size_t a_index, std::size_t a_member) = 0;
      // When a handle at a given index requests its editor be opened/brought to the top.
      virtual void requests_editor(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index) = 0;
      // When a handle at a given index requests focus in the outliner.
      virtual void requests_outliner(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index) = 0;
    };

  } // namespace internal

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Project_Signalbox_Data_Imp<T,Args...>
  //---------------------------------------------------------------------------
  // The top class of the template chain, where we gather and cleanup
  // everything. Also the requirement of at least one type stops bad template
  // instantiations.
  template <typename T, typename...Args>
  class Abstract_Project_Signalbox_Imp :
      protected internal::Abstract_Project_Signalbox_Part_Imp<flamingo::typelist<T,Args...>>
  {
    using Inh = internal::Abstract_Project_Signalbox_Part_Imp<flamingo::typelist<T,Args...>>;
  public:
    // Special 6
    //============================================================
    ~Abstract_Project_Signalbox_Imp() override = 0;

    // Interface
    //============================================================
    using Inh::added;
    using Inh::removed;
    using Inh::moved;
    using Inh::changed_name;
    using Inh::changed_data;
    using Inh::changed_data_at;
    using Inh::requests_editor;
    using Inh::requests_outliner;

    // Signals are as follows, with overloads for each Type in the
    // the arguments <T,Args...>:
    //------------------------------------------------------------

    // When a handle has been added at a given index.
    //virtual void added(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index) = 0;

    // When a handle has been removed from a given index.
    //virtual void removed(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index) = 0;

    // When a handle at a given index has been moved to another index.
    //virtual void moved(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_from, std::size_t a_to) = 0;

    // When a handle at a given index has its name changed.
    //virtual void changed_name(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index) = 0;

    // When a handle at a given index has all of its data changed.
    //virtual void changed_data(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index) = 0;

    // When a handle at a given index has its data changed in a specific place.
    //virtual void changed_data_at(Signal_Source a_source, Handle<Type> const& a_handler, std::size_t a_index, std::size_t a_member) = 0;

    // When a handle at a given index requests its editor be opened/brought to the top.
    //virtual void requests_editor(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index) = 0;

    // When a handle at a given index requests focus in the outliner.
    //virtual void requests_outliner(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index) = 0;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

} // namespace sak

template <std::size_t Index, std::size_t End, typename...Args>
sak::internal::Abstract_Project_Signalbox_Part_Imp<flamingo::typelist<Args...>,Index,End>::~Abstract_Project_Signalbox_Part_Imp() = default;

template <std::size_t End, typename...Args>
sak::internal::Abstract_Project_Signalbox_Part_Imp<flamingo::typelist<Args...>,End,End>::~Abstract_Project_Signalbox_Part_Imp() = default;

template <typename T, typename...Args>
sak::Abstract_Project_Signalbox_Imp<T,Args...>::~Abstract_Project_Signalbox_Imp() = default;

#endif // SAK_ABSTRACT_PROJECT_SIGNALBOX_HPP
