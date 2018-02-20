﻿#include "test_project_signalbox_data.hpp"

#include <sak/data_definitions.hpp>
#include <sak/class_definitions.hpp>
#include <sak/tag.hpp>
#include <sak/id.hpp>
#include <sak/abstract_project_signalbox.hpp>
#include <sak/project_signalbox_data.hpp>
#include <sak/signal_source.hpp>

#include <iostream>
#include <cassert>
#include <type_traits>

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
      std::cout << "sak::Section_Signalbox_Imp<List," << Index << ","<< End <<">::added "
                << dynamic_cast<Abstract_Project_Signalbox_Imp<Args...>*>(this) << std::endl;
    }

    // When data has been removed from a given index.
    void removed(Signal_Source a_source, ID_Type const& a_id, std::size_t a_index) override
    {
      std::cout << "sak::Section_Signalbox_Imp<List," << Index << ","<< End <<">::removed "
                << dynamic_cast<Abstract_Project_Signalbox_Imp<Args...>*>(this) << std::endl;
    }

    // When data at a given index has been moved to another index.
    void moved(Signal_Source a_source, ID_Type const& a_id, std::size_t a_from, std::size_t a_to) override
    {
      std::cout << "sak::Section_Signalbox_Imp<List," << Index << ","<< End <<">::moved "
                << dynamic_cast<Abstract_Project_Signalbox_Imp<Args...>*>(this) << std::endl;
    }

    // When data at a given index has its name changed.
    void changed_name(Signal_Source a_source, ID_Type const& a_id, std::size_t a_index) override
    {
      std::cout << "sak::Section_Signalbox_Imp<List," << Index << ","<< End <<">::changed_name "
                << dynamic_cast<Abstract_Project_Signalbox_Imp<Args...>*>(this) << std::endl;
    }

    // When data at a given index has all of its data changed.
    void changed_data(Signal_Source a_source, ID_Type const& a_id, std::size_t a_index) override
    {
      std::cout << "sak::Section_Signalbox_Imp<List," << Index << ","<< End <<">::changed_data "
                << dynamic_cast<Abstract_Project_Signalbox_Imp<Args...>*>(this) << std::endl;
    }

    // When data at a given index has its data changed in a specific place.
    void changed_data_at(Signal_Source a_source, ID_Type const& a_idr, std::size_t a_index, std::size_t a_member) override
    {
      std::cout << "sak::Section_Signalbox_Imp<List," << Index << ","<< End <<">::changed_data_at "
                << dynamic_cast<Abstract_Project_Signalbox_Imp<Args...>*>(this) << std::endl;
    }

    // When data at a given index requests its editor be opened/brought to the top.
    void requests_editor(Signal_Source a_source, ID_Type const& a_id, std::size_t a_index) override
    {
      std::cout << "sak::Section_Signalbox_Imp<List," << Index << ","<< End <<">::requests_editor "
                << dynamic_cast<Abstract_Project_Signalbox_Imp<Args...>*>(this) << std::endl;
    }

    // When data at a given index requests focus in the outliner.
    void requests_outliner(Signal_Source a_source, ID_Type const& a_id, std::size_t a_index) override
    {
      std::cout << "sak::Section_Signalbox_Imp<List," << Index << ","<< End <<">::requests_outliner "
                << dynamic_cast<Abstract_Project_Signalbox_Imp<Args...>*>(this) << std::endl;
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

  using Project_Signalbox = Project_Signalbox_Imp<File_Definition,Texture_Definition,Material_Definition>;
}

namespace sak
{
  namespace
  {
    template <typename T>
    void do_project_signalbox_test(Project_Signalbox_Data& a_psd)
    {
      std::cout << "-------------------------" << std::endl;
      std::cout << "Typestring = \"" << T::Typestring_Type::data() << "\"" << std::endl;
      auto l_ssd = a_psd.get_section<T>();

      auto a_ss = Signal_Source::System;
      auto a_id = ID<T>{};

      l_ssd->added(a_ss,a_id,0);
      l_ssd->removed(a_ss,a_id,0);
      l_ssd->moved(a_ss,a_id,0,1);
      l_ssd->changed_name(a_ss,a_id,0);
      l_ssd->changed_data(a_ss,a_id,0);
      l_ssd->changed_data_at(a_ss,a_id,0,0);
      l_ssd->requests_editor(a_ss,a_id,0);
      l_ssd->requests_editor(a_ss,a_id,0);
      std::cout << "-------------------------" << std::endl;
    }
  }
}


void sak::testing::test_project_signalbox_data()
{
  std::cout << "Testing sak::Project_Signalbox_Data" << std::endl;
  std::cout << "==============================" << std::endl;

  using namespace sak;

  Project_Signalbox_Data l_psd{};

  Project_Signalbox l_ps1{};
  Project_Signalbox l_ps2{};
  Project_Signalbox l_ps3{};

  l_psd.add_signalbox(nullptr);
  l_psd.add_signalbox(&l_ps1);
  l_psd.add_signalbox(&l_ps2);
  l_psd.add_signalbox(&l_ps3);

  do_project_signalbox_test<File_Definition>(l_psd);
  do_project_signalbox_test<Texture_Definition>(l_psd);
  do_project_signalbox_test<Material_Definition>(l_psd);

  std::cout << "remove some signalboxes:" << std::endl;
  std::cout << "address = " << dynamic_cast<Project_Signalbox*>(&l_ps2) << std::endl;
  std::cout << "address = " << dynamic_cast<Project_Signalbox*>(&l_ps3) << std::endl;

  l_psd.remove_signalbox(nullptr);
  l_psd.remove_signalbox(&l_ps2);
  l_psd.remove_signalbox(&l_ps3);

  do_project_signalbox_test<File_Definition>(l_psd);
  do_project_signalbox_test<Texture_Definition>(l_psd);
  do_project_signalbox_test<Material_Definition>(l_psd);

  std::cout << "==============================" << std::endl;
}
