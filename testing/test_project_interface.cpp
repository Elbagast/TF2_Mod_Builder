#include "test_project_interface.hpp"

#include <sak/project_interface.hpp>

#include <iostream>
#include <memory>
#include <cassert>

void sak::testing::test_project_interface()
{
  std::cout << "Testing sak::Project_Interface" << std::endl;
  std::cout << "==============================" << std::endl;

  using namespace sak;


  std::unique_ptr<Abstract_Project_Interface> l_api{ new Project_Interface{} };

  std::cout << "==============================" << std::endl;
}
