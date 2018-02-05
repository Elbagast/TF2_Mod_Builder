#include "test_abstract_project_interface.hpp"

#include <sak/data_definitions.hpp>
#include <sak/class_definitions.hpp>
#include <sak/data.hpp>
#include <sak/handle.hpp>
#include <sak/tag.hpp>
#include <sak/abstract_project_interface.hpp>
#include <sak/project_data.hpp>

#include <iostream>
#include <cassert>

#include <QString>

void sak::testing::test_abstract_project_interface()
{
  std::cout << "Testing sak::Abstract_Project_Interface" << std::endl;
  std::cout << "==============================" << std::endl;

  using namespace sak;

  QString l_filepath{"D:/Source Army Knife/Test Projects/Project/Project.sakpro"};


  auto l_pi = make_project_interface(Project_Data {l_filepath});

  std::cout << "Name =     \"" << l_pi->name().toStdString() << "\"" << std::endl;
  std::cout << "Location = \"" << l_pi->location().toStdString() << "\"" << std::endl;
  std::cout << "Filepath = \"" << l_pi->filepath().toStdString() << "\"" << std::endl;


  std::cout << "==============================" << std::endl;
}
