#include "test_abstract_project_signalbox.hpp"

#include "dummy_project_signalbox.hpp"

#include <memory>
#include <cassert>

namespace sak
{
  using APSB = Abstract_Project_Signalbox_Imp<File_Definition,Texture_Definition,Material_Definition>;
  using PSB = Dummy_Project_Signalbox_Imp<File_Definition,Texture_Definition,Material_Definition>;

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

  auto l_apsb = make_dummy_project_signalbox<File_Definition, Texture_Definition, Material_Definition>();

  do_test_signalbox<File_Definition>(l_apsb.get());
  do_test_signalbox<Texture_Definition>(l_apsb.get());
  do_test_signalbox<Material_Definition>(l_apsb.get());

  std::cout << "==============================" << std::endl;
}
