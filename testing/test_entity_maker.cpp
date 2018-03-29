#include "test_entity_maker.hpp"

#include "dummy_entity_maker.hpp"

#include <sak/entity_id.hpp>
#include <sak/entity.hpp>
#include <sak/entity_handle.hpp>

#include <iostream>
#include <cassert>

#include <QString>

void sak::testing::test_entity_maker()
{
  std::cout << "Testing sak::Abstract_Entity_Maker" << std::endl;
  std::cout << "==============================" << std::endl;

  using namespace sak;

  auto l_true_maker = Dummy_Entity_Maker::make_self();

  Abstract_Entity_Maker* l_maker{l_true_maker.get()};

  std::cout << "Abstract_Entity_Maker::type = " << l_maker->type().toStdString() << std::endl;

  auto l_id = make_entity_id(123u);
  std::cout << "id value = " << entity_id_value(l_id) << std::endl;

  auto l_handle = l_maker->make_entity(l_id);

  assert(not_null(l_handle));

  std::cout << "Entity_Handle is_null = " << is_null(l_handle) << std::endl;
  std::cout << "Entity_Handle::id = " << entity_id_value(l_handle.id()) << std::endl;

  assert(l_handle.id() == l_id);


  std::cout << "==============================" << std::endl;
}
