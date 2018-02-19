#ifndef SAK_PROJECT_SIGNALBOX_DATA_HPP
#define SAK_PROJECT_SIGNALBOX_DATA_HPP

#ifndef SAK_PROJECT_SIGNALBOX_DATA_FWD_HPP
#include "project_signalbox_data_fwd.hpp"
#endif

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
  namespace internal
  {
    //---------------------------------------------------------------------------
    // Project_Signalbox_Data_Part_Imp<List, Index, End>
    //---------------------------------------------------------------------------
    // Declaration and default arguments for the template class that builds the
    // template chain.
    template
    <
      typename T_List,
      std::size_t Index = 0,
      std::size_t End = (flamingo::typelist_size_v<T_List> - 1)
    >
    class Project_Signalbox_Data_Part_Imp;

    //------------------------------------------------------------------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    // Project_Signalbox_Data_Part_Imp<List, Index, End>
    //---------------------------------------------------------------------------
    // For a type that isn't at the end of the list.
    template <std::size_t Index, std::size_t End, typename...Args>
    class Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,Index,End> :
        public Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,Index+1,End>
    {
      using Inh = Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,Index+1,End>;

      using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,Index>;

    public:
      // Typedefs
      //============================================================
      using Signalbox_Type = typename Inh::Signalbox_Type;

      // Special 6
      //============================================================
      Project_Signalbox_Data_Part_Imp();
      ~Project_Signalbox_Data_Part_Imp();

      Project_Signalbox_Data_Part_Imp(Project_Signalbox_Data_Part_Imp const&);
      Project_Signalbox_Data_Part_Imp& operator=(Project_Signalbox_Data_Part_Imp const&);

      Project_Signalbox_Data_Part_Imp(Project_Signalbox_Data_Part_Imp &&);
      Project_Signalbox_Data_Part_Imp& operator=(Project_Signalbox_Data_Part_Imp &&);

      // Interface
      //============================================================
      // calls each of these on all the stored signalboxes.

      // When a handle has been added at a given index.
      void added(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index);
      // When a handle has been removed from a given index.
      void removed(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index);
      // When a handle at a given index has been moved to another index.
      void moved(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_from, std::size_t a_to);
      // When a handle at a given index has its name changed.
      void changed_name(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index);
      // When a handle at a given index has all of its data changed.
      void changed_data(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index);
      // When a handle at a given index has its data changed in a specific place.
      void changed_data_at(Signal_Source a_source, Handle<Type> const& a_handler, std::size_t a_index, std::size_t a_member);
      // When a handle at a given index requests its editor be opened/brought to the top.
      void requests_editor(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index);
      // When a handle at a given index requests focus in the outliner.
      void requests_outliner(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index);

      using Inh::added;
      using Inh::removed;
      using Inh::moved;
      using Inh::changed_name;
      using Inh::changed_data;
      using Inh::changed_data_at;
      using Inh::requests_editor;
      using Inh::requests_outliner;

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
    // Project_Signalbox_Data_Part_Imp<List, End, End>
    //---------------------------------------------------------------------------
    // For the last type in the list
    template <std::size_t End, typename...Args>
    class Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,End,End>
    {
      using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,End>;
    public:
      // Typedefs
      //============================================================
      using Signalbox_Type = Abstract_Project_Signalbox_Imp<Args...>;

      // Special 6
      //============================================================
      Project_Signalbox_Data_Part_Imp();
      ~Project_Signalbox_Data_Part_Imp();

      Project_Signalbox_Data_Part_Imp(Project_Signalbox_Data_Part_Imp const&);
      Project_Signalbox_Data_Part_Imp& operator=(Project_Signalbox_Data_Part_Imp const&);

      Project_Signalbox_Data_Part_Imp(Project_Signalbox_Data_Part_Imp &&);
      Project_Signalbox_Data_Part_Imp& operator=(Project_Signalbox_Data_Part_Imp &&);

      // Interface
      //============================================================
      // calls each of these on all the stored signalboxes.

      // When a handle has been added at a given index.
      void added(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index);
      // When a handle has been removed from a given index.
      void removed(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index);
      // When a handle at a given index has been moved to another index.
      void moved(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_from, std::size_t a_to);
      // When a handle at a given index has its name changed.
      void changed_name(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index);
      // When a handle at a given index has all of its data changed.
      void changed_data(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index);
      // When a handle at a given index has its data changed in a specific place.
      void changed_data_at(Signal_Source a_source, Handle<Type> const& a_handler, std::size_t a_index, std::size_t a_member);
      // When a handle at a given index requests its editor be opened/brought to the top.
      void requests_editor(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index);
      // When a handle at a given index requests focus in the outliner.
      void requests_outliner(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index);

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
  } // namespace internal
  //------------------------------------------------------------------------------------------------------------------------------------------------------


  //---------------------------------------------------------------------------
  // Project_Signalbox_Data_Imp<T,Args...>
  //---------------------------------------------------------------------------
  // The top class of the template chain, where we gather and cleanup
  // everything. Also the requirement of at least one type stops bad template
  // instantiations.
  template <typename T, typename...Args>
  class Project_Signalbox_Data_Imp :
      protected internal::Project_Signalbox_Data_Part_Imp<flamingo::typelist<T,Args...>>
  {
    using Inh = internal::Project_Signalbox_Data_Part_Imp<flamingo::typelist<T,Args...>>;
  public:
    // Typedefs
    //============================================================
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
    using Inh::added;
    using Inh::removed;
    using Inh::moved;
    using Inh::changed_name;
    using Inh::changed_data;
    using Inh::changed_data_at;
    using Inh::requests_editor;
    using Inh::requests_outliner;

    using Inh::add_signalbox;
    using Inh::remove_signalbox;
    using Inh::clear_signalboxes;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

} // namespace sak

#endif // SAK_PROJECT_SIGNALBOX_DATA_HPP
