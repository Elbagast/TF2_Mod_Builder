#ifndef SAK_TESTING_DUMMY_PROJECT_SIGNALBOX_HPP
#define SAK_TESTING_DUMMY_PROJECT_SIGNALBOX_HPP

#include <sak/abstract_project_signalbox.hpp>
#include <sak/id.hpp>
#include <sak/signal_source.hpp>

#include <sak/data_definitions.hpp>
#include <sak/class_definitions.hpp>

#include <memory>
#include <iostream>
#include <cassert>

namespace sak
{
  std::ostream& operator<<(std::ostream& a_ostream, Signal_Source a_source);

  //---------------------------------------------------------------------------
  // Dummy_Section_Signalbox_Imp<List, Index, End>
  //---------------------------------------------------------------------------
  // Declaration and default arguments for the template class that builds the
  // template chain.
  template
  <
    typename T_List,
    std::size_t Index = 0,
    std::size_t End = (flamingo::typelist_size_v<T_List>)
  >
  class Dummy_Section_Signalbox_Imp;

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Project_Signalbox_Section_Imp<List, Index, End>
  //---------------------------------------------------------------------------
  // For a type that isn't at the end of the list.
  template <std::size_t Index, std::size_t End, typename...Args>
  class Dummy_Section_Signalbox_Imp<flamingo::typelist<Args...>,Index,End> :
      public Dummy_Section_Signalbox_Imp<flamingo::typelist<Args...>,Index+1,End>
  {
    using Inh = Dummy_Section_Signalbox_Imp<flamingo::typelist<Args...>,Index+1,End>;

    using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,Index>;
    using ID_Type = ID<Type>;

  public:
    // Special 6
    //============================================================
    ~Dummy_Section_Signalbox_Imp() override = default;

    // Interface
    //============================================================
    // When data has been added at a given index.
    void added(Signal_Source a_source, ID_Type const& a_id, std::size_t a_index) override
    {
      std::cout << this << " : "
                << "sak::Section_Signalbox_Imp<List," << Index << ","<< End <<">::added( "
                << a_source
                << ", ID<"<< Type::Typestring_Type::data() << ">=" << a_id.value()
                << ", " << a_index << ")" << std::endl;
    }

    // When data has been removed from a given index.
    void removed(Signal_Source a_source, ID_Type const& a_id, std::size_t a_index) override
    {
      std::cout << this << " : "
                << "sak::Section_Signalbox_Imp<List," << Index << ","<< End <<">::removed( "
                << a_source
                << ", ID<"<< Type::Typestring_Type::data() << ">=" << a_id.value()
                << ", " << a_index << ")" << std::endl;
    }

    // When data at a given index has been moved to another index.
    void moved(Signal_Source a_source, ID_Type const& a_id, std::size_t a_from, std::size_t a_to) override
    {
      std::cout << this << " : "
                << "sak::Section_Signalbox_Imp<List," << Index << ","<< End <<">::moved( "
                << a_source
                << ", ID<"<< Type::Typestring_Type::data() << ">=" << a_id.value()
                << ", " << a_from
                << ", " << a_to << ")" << std::endl;
    }

    // When data at a given index has its name changed.
    void changed_name(Signal_Source a_source, ID_Type const& a_id, std::size_t a_index) override
    {
      std::cout << this << " : "
                << "sak::Section_Signalbox_Imp<List," << Index << ","<< End <<">::changed_name( "
                << a_source
                << ", ID<"<< Type::Typestring_Type::data() << ">=" << a_id.value()
                << ", " << a_index << ")" << std::endl;
    }

    // When data at a given index has all of its data changed.
    void changed_data(Signal_Source a_source, ID_Type const& a_id, std::size_t a_index) override
    {
      std::cout << this << " : "
                << "sak::Section_Signalbox_Imp<List," << Index << ","<< End <<">::changed_data( "
                << a_source
                << ", ID<"<< Type::Typestring_Type::data() << ">=" << a_id.value()
                << ", " << a_index << ")" << std::endl;
    }

    // When data at a given index has its data changed in a specific place.
    void changed_data_at(Signal_Source a_source, ID_Type const& a_id, std::size_t a_index, std::size_t a_member) override
    {
      std::cout << this << " : "
                << "sak::Section_Signalbox_Imp<List," << Index << ","<< End <<">::changed_data_at( "
                << a_source
                << ", ID<"<< Type::Typestring_Type::data() << ">=" << a_id.value()
                << ", " << a_index
                << ", " << a_member << ")" << std::endl;
    }

    // When data at a given index requests its editor be opened/brought to the top.
    void requests_editor(Signal_Source a_source, ID_Type const& a_id, std::size_t a_index) override
    {
      std::cout << this << " : "
                << "sak::Section_Signalbox_Imp<List," << Index << ","<< End <<">::requests_editor( "
                << a_source
                << ", ID<"<< Type::Typestring_Type::data() << ">=" << a_id.value()
                << ", " << a_index << ")" << std::endl;
    }

    // When data at a given index requests focus in the outliner.
    void requests_outliner(Signal_Source a_source, ID_Type const& a_id, std::size_t a_index) override
    {
      std::cout << this << " : "
                << "sak::Section_Signalbox_Imp<List," << Index << ","<< End <<">::requests_outliner( "
                << a_source
                << ", ID<"<< Type::Typestring_Type::data() << ">=" << a_id.value()
                << ", " << a_index << ")" << std::endl;
    }
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Dummy_Section_Signalbox_Imp<List, End, End>
  //---------------------------------------------------------------------------
  // For the last type in the list
  template <std::size_t End, typename...Args>
  class Dummy_Section_Signalbox_Imp<flamingo::typelist<Args...>,End,End> :
      public Abstract_Project_Signalbox_Imp<Args...>
  {
  public:
    // Special 6
    //============================================================
    ~Dummy_Section_Signalbox_Imp() override = default;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Dummy_Project_Signalbox_Imp<T,Args...>
  //---------------------------------------------------------------------------
  // The top class of the template chain, where we gather and cleanup
  // everything. Also the requirement of at least one type stops bad template
  // instantiations.
  template <typename T, typename...Args>
  class Dummy_Project_Signalbox_Imp :
      public Dummy_Section_Signalbox_Imp<flamingo::typelist<T,Args...>>
  {
    using Inh = Dummy_Section_Signalbox_Imp<flamingo::typelist<T,Args...>>;
    using Typelist_Type = flamingo::typelist<T,Args...>;

    static_assert(flamingo::typelist_all_unique_v<Typelist_Type>,
                  "Cannot have repeating types in the supplied template arguments.");
  public:
    // Special 6
    //============================================================
    ~Dummy_Project_Signalbox_Imp() override = default;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  template <typename...Args>
  std::unique_ptr<Abstract_Project_Signalbox_Imp<Args...>> make_dummy_project_signalbox()
  {
    return std::unique_ptr<Abstract_Project_Signalbox_Imp<Args...>>{ std::make_unique<Dummy_Project_Signalbox_Imp<Args...>>().release() };
  }
}


#endif // SAK_TESTING_DUMMY_PROJECT_SIGNALBOX_HPP
