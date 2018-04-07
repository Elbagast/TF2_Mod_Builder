#include "test_entity_manager.hpp"

#include <sak/entity_id.hpp>
#include <sak/entity_definition.hpp>
#include <sak/entity_manager.hpp>
#include <sak/signal_source.hpp>

#include "test_io.hpp"
#include "dummy_observer.hpp"

#include <iostream>
#include <cassert>

void sak::testing::test_entity_manager()
{  
  std::cout << "Testing sak::Entity_Manager" << std::endl;
  std::cout << "==============================" << std::endl;

  Dummy_Observer l_do{};

  std::vector<Entity_Definition> l_defs{};
  l_defs.push_back(Entity_Definition{u8"Foo",u8"This is a Foo Entity.",u8""});
  l_defs.push_back(Entity_Definition{u8"Bar",u8"This is a Bar Entity.",u8""});

  Entity_Manager l_em{ l_defs };
  std::cout << "Starting condtions:" << std::endl;
  std::cout << "--------------------------" << std::endl;

  std::cout << l_em << std::endl;

  std::cout << "Adding an observer:" << std::endl;
  std::cout << "--------------------------" << std::endl;
  l_em.add_observer(std::addressof(l_do));

  std::cout << l_em << std::endl;

  std::cout << "Adding some Entities:" << std::endl;
  std::cout << "--------------------------" << std::endl;
  auto l_id1 = l_em.try_add(Signal_Source::User, u8"Foo");
  auto l_id2 = l_em.try_add(Signal_Source::User, u8"Foo");
  auto l_id3 = l_em.try_add(Signal_Source::User, u8"Foo");
  auto l_id4 = l_em.try_add(Signal_Source::User, u8"Bar");
  auto l_id5 = l_em.try_add(Signal_Source::User, u8"Bar");
  std::cout << l_em << std::endl;

  std::cout << "Undoing all the adds:" << std::endl;
  std::cout << "--------------------------" << std::endl;
  l_em.undo();
  l_em.undo();
  l_em.undo();
  l_em.undo();
  l_em.undo();
  std::cout << l_em << std::endl;

  std::cout << "Redoing all the adds:" << std::endl;
  std::cout << "--------------------------" << std::endl;
  l_em.redo();
  l_em.redo();
  l_em.redo();
  l_em.redo();
  l_em.redo();
  std::cout << l_em << std::endl;

  std::cout << "Editing some names:" << std::endl;
  std::cout << "--------------------------" << std::endl;
  l_em.try_set_name(Signal_Source::User, l_id1, u8"nametest"); // should work
  l_em.try_set_name(Signal_Source::User, l_id2, u8"nametest"); // should result in name of 'nametest1'
  l_em.try_set_name(Signal_Source::User, l_id1, u8"nametest"); // should do nothing
  l_em.try_set_name(Signal_Source::User, l_id2, u8"nametest"); // should result in name of 'nametest2'
  std::cout << l_em << std::endl;

  std::cout << "Undoing all the name changes:" << std::endl;
  std::cout << "--------------------------" << std::endl;
  l_em.undo();
  l_em.undo();
  l_em.undo();
  std::cout << l_em << std::endl;

  std::cout << "Redoing all the name changes:" << std::endl;
  std::cout << "--------------------------" << std::endl;
  l_em.redo();
  l_em.redo();
  l_em.redo();
  std::cout << l_em << std::endl;

  std::cout << "Remove some Entities:" << std::endl;
  std::cout << "--------------------------" << std::endl;
  l_em.try_remove(Signal_Source::User, l_id2);
  l_em.try_remove(Signal_Source::User, l_id3);
  std::cout << l_em << std::endl;

  std::cout << "Set a name to that of one of the removed:" << std::endl;
  std::cout << "--------------------------" << std::endl;
  l_em.try_set_name(Signal_Source::User, l_id1, u8"nametest2");
  std::cout << l_em << std::endl;

  std::cout << "==============================" << std::endl;
}
