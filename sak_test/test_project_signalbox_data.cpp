#include "test_project_signalbox_data.hpp"

#include "dummy_project_signalbox.hpp"
#include <sak/project_signalbox_data.hpp>

#include <iostream>
#include <cassert>
#include <type_traits>


namespace sak
{
  namespace
  {
    template <typename T>
    void do_project_signalbox_test(Project_Signalbox_Data& a_psd)
    {
      std::cout << "-------------------------" << std::endl;
      std::cout << "Typestring = \"" << T::Typestring_Type::data() << "\"" << std::endl;

      auto a_ss = Signal_Source::System;
      auto a_id = ID<T>{};

      a_psd.added(a_ss,a_id,0);
      a_psd.removed(a_ss,a_id,0);
      a_psd.moved(a_ss,a_id,0,1);
      a_psd.changed_name(a_ss,a_id,0);
      a_psd.changed_data(a_ss,a_id,0);
      a_psd.changed_data_at(a_ss,a_id,0,0);
      a_psd.requests_editor(a_ss,a_id,0);
      a_psd.requests_outliner(a_ss,a_id,0);
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

  using Dummy_Project_Signalbox = Dummy_Project_Signalbox_Imp<File_Definition,Texture_Definition,Material_Definition>;

  Dummy_Project_Signalbox l_ps1{};
  Dummy_Project_Signalbox l_ps2{};
  Dummy_Project_Signalbox l_ps3{};

  l_psd.add_signalbox(nullptr);
  l_psd.add_signalbox(&l_ps1);
  l_psd.add_signalbox(&l_ps2);
  l_psd.add_signalbox(&l_ps3);

  do_project_signalbox_test<File_Definition>(l_psd);
  do_project_signalbox_test<Texture_Definition>(l_psd);
  do_project_signalbox_test<Material_Definition>(l_psd);

  std::cout << "remove some signalboxes:" << std::endl;
  std::cout << "address = " << dynamic_cast<Dummy_Project_Signalbox*>(&l_ps2) << std::endl;
  std::cout << "address = " << dynamic_cast<Dummy_Project_Signalbox*>(&l_ps3) << std::endl;

  l_psd.remove_signalbox(nullptr);
  l_psd.remove_signalbox(&l_ps2);
  l_psd.remove_signalbox(&l_ps3);

  do_project_signalbox_test<File_Definition>(l_psd);
  do_project_signalbox_test<Texture_Definition>(l_psd);
  do_project_signalbox_test<Material_Definition>(l_psd);

  std::cout << "==============================" << std::endl;
}
