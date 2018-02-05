#include "test_project_data.hpp"

#include <sak/data_definitions.hpp>
#include <sak/class_definitions.hpp>
#include <sak/data.hpp>
#include <sak/handle.hpp>
#include <sak/tag.hpp>
#include <sak/project_data.hpp>

#include <iostream>
#include <cassert>

namespace
{
  template <typename T>
  void do_project_test(sak::Project_Data& a_project)
  {
    using namespace sak;

    std::cout << "Section<T>:" << std::endl;
    std::cout << "-------------------------" << std::endl;
    std::cout << "Typestring = \"" << T::Typestring_Type::data() << "\"" << std::endl;

    std::cout << "empty() = \"" << a_project.empty(Tag<T>()) << "\"" << std::endl;
    std::cout << "count() = \"" << a_project.count(Tag<T>()) << "\"" << std::endl;
    std::cout << "has_handle() = \"" << a_project.has_handle(Handle<T>()) << "\"" << std::endl;

    // no handles so this should be null
    auto l_h = a_project.get_handle_at(Tag<T>(), 0);
    assert(!l_h);

    // no handles so this should be empty
    auto l_hs = a_project.get_all_handles(Tag<T>());
    assert(l_hs.size() == 0);

    // no handles so this should be empty
    auto l_ns = a_project.get_all_names(Tag<T>());
    assert(l_ns.size() == 0);

    std::cout << "-------------------------" << std::endl;
  }

}


void sak::testing::test_project_data()
{
  std::cout << "Testing sak::Project_Data" << std::endl;
  std::cout << "==============================" << std::endl;

  using namespace sak;

  QString l_filepath{"D:/Source Army Knife/Test Projects/Project/Project.sakpro"};

  Project_Data l_p{l_filepath};

  std::cout << "Name =     \"" << l_p.name().toStdString() << "\"" << std::endl;
  std::cout << "Location = \"" << l_p.location().toStdString() << "\"" << std::endl;
  std::cout << "Filepath = \"" << l_p.filepath().toStdString() << "\"" << std::endl;

  do_project_test<File_Definition>(l_p);
  do_project_test<Texture_Definition>(l_p);


  std::cout << "==============================" << std::endl;
}
