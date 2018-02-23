#include "test_project_interface.hpp"

#include <sak/project_interface.hpp>
#include <sak/signal_source.hpp>

#include "dummy_project_signalbox.hpp"

#include <iostream>
#include <memory>
#include <cassert>

class A;

void sak::testing::test_project_interface()
{
  std::cout << "Testing sak::Project_Interface" << std::endl;
  std::cout << "==============================" << std::endl;

  using namespace sak;


  std::unique_ptr<Abstract_Project_Interface> l_api{ new Project_Interface{QString{"D:/blah/blah.sakpro"}} };

  std::cout << "name: \"" << l_api->name().toStdString() << "\"" << std::endl;
  std::cout << "location: \"" << l_api->location().toStdString() << "\"" << std::endl;
  std::cout << "filepath: \"" << l_api->filepath().toStdString() << "\"" << std::endl;

  auto l_dsb = make_dummy_project_signalbox<File_Definition,Texture_Definition,Material_Definition>();

  l_api->add_signalbox(l_dsb.get());

  auto l_result = l_api->try_set_name(Signal_Source::User, ID<File_Definition>{5}, QString{"somename"});
  assert(!l_result);

  auto l_id = l_api->add_default(Tag<File_Definition>(), Signal_Source::User);
  assert(l_api->undo_count() == 1);
  assert(l_api->can_undo());

  l_api->undo();
  assert(l_api->undo_count() == 0);
  assert(l_api->can_undo() == false);
  assert(l_api->redo_count() == 1);
  assert(l_api->can_redo() == true);

  l_api->redo();

  std::cout << l_api->get_name(l_id).toStdString() << std::endl;

  l_api->try_set_name(Signal_Source::User, l_id, QString{"somename"});

  std::cout << l_api->get_name(l_id).toStdString() << std::endl;

  l_api->undo();
  std::cout << l_api->get_name(l_id).toStdString() << std::endl;

  // Fails to compile with a message that tells us why, and leads
  // back to here :)
  //l_api->has(ID<A>{});


  std::cout << "==============================" << std::endl;
}
