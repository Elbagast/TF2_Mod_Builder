#include "test_abstract_project_signalbox.hpp"

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
  //---------------------------------------------------------------------------
  // Section_Signalbox_Imp<List, Index, End>
  //---------------------------------------------------------------------------
  // Declaration and default arguments for the template class that builds the
  // template chain.
  template
  <
    typename T_List,
    std::size_t Index = 0,
    std::size_t End = (flamingo::typelist_size_v<T_List>)
  >
  class Section_Signalbox_Imp;

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Project_Signalbox_Section_Imp<List, Index, End>
  //---------------------------------------------------------------------------
  // For a type that isn't at the end of the list.
  template <std::size_t Index, std::size_t End, typename...Args>
  class Section_Signalbox_Imp<flamingo::typelist<Args...>,Index,End> :
      public Section_Signalbox_Imp<flamingo::typelist<Args...>,Index+1,End>
  {
    using Inh = Section_Signalbox_Imp<flamingo::typelist<Args...>,Index+1,End>;

    using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,Index>;
    using ID_Type = ID<Type>;

  public:
    // Special 6
    //============================================================
    ~Section_Signalbox_Imp() override = default;

    // Interface
    //============================================================
    // When data has been added at a given index.
    void added(Signal_Source a_source, ID_Type const& a_id, std::size_t a_index) override
    {
      std::cout << "sak::Section_Signalbox_Imp<List," << Index << ","<< End <<">::added" << std::endl;
    }

    // When data has been removed from a given index.
    void removed(Signal_Source a_source, ID_Type const& a_id, std::size_t a_index) override
    {
      std::cout << "sak::Section_Signalbox_Imp<List," << Index << ","<< End <<">::removed" << std::endl;
    }

    // When data at a given index has been moved to another index.
    void moved(Signal_Source a_source, ID_Type const& a_id, std::size_t a_from, std::size_t a_to) override
    {
      std::cout << "sak::Section_Signalbox_Imp<List," << Index << ","<< End <<">::moved" << std::endl;
    }

    // When data at a given index has its name changed.
    void changed_name(Signal_Source a_source, ID_Type const& a_id, std::size_t a_index) override
    {
      std::cout << "sak::Section_Signalbox_Imp<List," << Index << ","<< End <<">::changed_name" << std::endl;
    }

    // When data at a given index has all of its data changed.
    void changed_data(Signal_Source a_source, ID_Type const& a_id, std::size_t a_index) override
    {
      std::cout << "sak::Section_Signalbox_Imp<List," << Index << ","<< End <<">::changed_data" << std::endl;
    }

    // When data at a given index has its data changed in a specific place.
    void changed_data_at(Signal_Source a_source, ID_Type const& a_idr, std::size_t a_index, std::size_t a_member) override
    {
      std::cout << "sak::Section_Signalbox_Imp<List," << Index << ","<< End <<">::changed_data_at" << std::endl;
    }

    // When data at a given index requests its editor be opened/brought to the top.
    void requests_editor(Signal_Source a_source, ID_Type const& a_id, std::size_t a_index) override
    {
      std::cout << "sak::Section_Signalbox_Imp<List," << Index << ","<< End <<">::requests_editor" << std::endl;
    }

    // When data at a given index requests focus in the outliner.
    void requests_outliner(Signal_Source a_source, ID_Type const& a_id, std::size_t a_index) override
    {
      std::cout << "sak::Section_Signalbox_Imp<List," << Index << ","<< End <<">::requests_outliner" << std::endl;
    }
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Section_Signalbox_Imp<List, End, End>
  //---------------------------------------------------------------------------
  // For the last type in the list
  template <std::size_t End, typename...Args>
  class Section_Signalbox_Imp<flamingo::typelist<Args...>,End,End> :
      public Abstract_Project_Signalbox_Imp<Args...>
  {
  public:
    // Special 6
    //============================================================
    ~Section_Signalbox_Imp() override = default;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Project_Signalbox_Imp<T,Args...>
  //---------------------------------------------------------------------------
  // The top class of the template chain, where we gather and cleanup
  // everything. Also the requirement of at least one type stops bad template
  // instantiations.
  template <typename T, typename...Args>
  class Project_Signalbox_Imp :
      public Section_Signalbox_Imp<flamingo::typelist<T,Args...>>
  {
    using Inh = Section_Signalbox_Imp<flamingo::typelist<T,Args...>>;
    using Typelist_Type = flamingo::typelist<T,Args...>;

    static_assert(flamingo::typelist_all_unique_v<Typelist_Type>,
                  "Cannot have repeating types in the supplied template arguments.");
  public:
    // Special 6
    //============================================================
    ~Project_Signalbox_Imp() override = default;

  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------
}

namespace sak
{
  using APSB = Abstract_Project_Signalbox_Imp<File_Definition,Texture_Definition,Material_Definition>;
  using PSB = Project_Signalbox_Imp<File_Definition,Texture_Definition,Material_Definition>;

  namespace
  {
    template <typename T>
    void do_test_signalbox(APSB* a_apsb)
    {
      std::cout << "-------------------------" << std::endl;
      std::cout << "Typestring = \"" << T::Typestring_Type::data() << "\"" << std::endl;

      auto l_assb = a_apsb->get_signalbox<T>();

      auto a_ss = Signal_Source::System;
      auto a_id = ID<T>{};

      l_assb->added(a_ss,a_id,0);
      l_assb->removed(a_ss,a_id,0);
      l_assb->moved(a_ss,a_id,0,1);
      l_assb->changed_name(a_ss,a_id,0);
      l_assb->changed_data(a_ss,a_id,0);
      l_assb->changed_data_at(a_ss,a_id,0,0);
      l_assb->requests_editor(a_ss,a_id,0);
      l_assb->requests_editor(a_ss,a_id,0);

      std::cout << "-------------------------" << std::endl;
    }
  }
}

void sak::testing::test_abstract_project_signalbox()
{
  std::cout << "Testing sak::Abstract_Project_Signalbox_Imp<T,Args...>" << std::endl;
  std::cout << "==============================" << std::endl;

  using namespace sak;

  std::unique_ptr<APSB> l_apsb{ new PSB{}};

  do_test_signalbox<File_Definition>(l_apsb.get());
  do_test_signalbox<Texture_Definition>(l_apsb.get());
  do_test_signalbox<Material_Definition>(l_apsb.get());

  std::cout << "==============================" << std::endl;
}
