#include "test_project.hpp"

#include <sak/entity_id.hpp>
//#include <sak/project.hpp>
#include <sak/entity_manager.hpp>

#include <tf2mb/project.hpp>

#include <sak_test/dummy_observer.hpp>

#include <iostream>
#include <cassert>

#include <QString>

void sak::testing::test_project()
{
  std::cout << "Testing sak::Project" << std::endl;
  std::cout << "==============================" << std::endl;

  using namespace sak;
/*
  Project l_project{QString{"D:\\Source Army Knife\\Test Projects\\untitled\\untitled.sakpro"}};

  std::cout << "Enttiy Types:" << std::endl;
  for (auto const& l_type : l_project.centity_manager()->get_all_types())
  {
    std::cout << l_type << std::endl;
  }
*/
  //Dummy_Observer l_do{};

  //l_project.entity_manager().add_observer(std::addressof(l_do));

  std::cout << "==============================" << std::endl;
}
