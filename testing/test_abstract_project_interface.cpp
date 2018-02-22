#include "test_abstract_project_interface.hpp"

#include "dummy_project_interface.hpp"

#include <memory>
#include <cassert>

namespace sak
{
  using API = Abstract_Project_Interface_Imp<File_Definition,Texture_Definition,Material_Definition>;
  using PI = Dummy_Project_Interface_Imp<File_Definition,Texture_Definition,Material_Definition>;
  using ASB = API::Signalbox_Type;

  namespace
  {
    template <typename T>
    void do_test_section(API* a_api)
    {
      std::cout << "-------------------------" << std::endl;
      std::cout << "Typestring = \"" << T::Typestring_Type::data() << "\"" << std::endl;

      auto l_si = a_api->get_section<T>();
      l_si->is_empty(Tag<T>{});
      l_si->count(Tag<T>{});
      l_si->has(ID<T>{});
      l_si->has_name(Tag<T>{}, QString{});
      l_si->get_at(Tag<T>{}, std::size_t{});
      l_si->get_named(Tag<T>{}, QString{});
      l_si->get_ids(Tag<T>{});
      l_si->get_names(Tag<T>{});
      std::cout << "-------------------------" << std::endl;
    }
  }
}


void sak::testing::test_abstract_project_interface()
{
  std::cout << "Testing sak::Abstract_Project_Interface" << std::endl;
  std::cout << "==============================" << std::endl;

  using namespace sak;


  std::unique_ptr<API> l_api{ new PI{}};

  l_api->save();
  l_api->load();
  l_api->name();
  l_api->location();
  l_api->filepath();
  l_api->can_undo();
  l_api->can_redo();
  l_api->undo_count();
  l_api->redo_count();
  l_api->undo();
  l_api->redo();
  l_api->can_redo();
  l_api->clear_history();
  QString l_name{};
  l_api->has_name(l_name);
  l_api->get_all_names();
  l_api->fix_name(l_name);

  ASB* l_asb{nullptr};
  l_api->add_signalbox(l_asb);
  l_api->remove_signalbox(l_asb);
  l_api->clear_signalboxes();

  do_test_section<File_Definition>(l_api.get());
  do_test_section<Texture_Definition>(l_api.get());
  do_test_section<Material_Definition>(l_api.get());

  std::cout << "==============================" << std::endl;
}
