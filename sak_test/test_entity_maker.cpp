#include "test_entity_maker.hpp"

#include "dummy_entity_maker.hpp"

#include <sak/entity_id.hpp>
#include <sak/internal/entity.hpp>

#include <iostream>
#include <cassert>
#include <string>

void sak::testing::test_entity_maker()
{
  std::cout << "Testing sak::Abstract_Entity_Maker" << std::endl;
  std::cout << "==============================" << std::endl;

  using namespace sak;

  auto l_true_maker = std::make_unique<Dummy_Entity_Maker>();

  Abstract_Entity_Maker* l_maker{l_true_maker.get()};

  std::cout << "Abstract_Entity_Maker::type = " << l_maker->type() << std::endl;

  auto l_id = make_entity_id(123u);
  std::cout << "id value = " << entity_id_value(l_id) << std::endl;

  Entity l_entity{l_maker->make_entity(l_id)};

  std::cout << "Entity::id = " << entity_id_value(l_entity.id()) << std::endl;

  assert(l_entity.id() == l_id);


  std::cout << "==============================" << std::endl;
}
