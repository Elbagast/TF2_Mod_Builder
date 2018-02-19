#include "test_project_data.hpp"

#include <sak/data_definitions.hpp>
#include <sak/class_definitions.hpp>
#include <sak/data.hpp>
#include <sak/handle.hpp>
#include <sak/tag.hpp>
//#include <sak/project_data.hpp>

#include <iostream>
#include <cassert>
/*
namespace
{
  template <typename T>
  void do_project_test(sak::Project_Data& a_project)
  {
    using namespace sak;

    //constexpr Tag<T> TAG {};

    std::cout << "Section<T>:" << std::endl;
    std::cout << "-------------------------" << std::endl;
    std::cout << "Typestring = \"" << T::Typestring_Type::data() << "\"" << std::endl;

    std::cout << "empty() = \"" << a_project.empty(Tag<T>()) << "\"" << std::endl;
    std::cout << "count() = \"" << a_project.count(Tag<T>()) << "\"" << std::endl;
    //std::cout << "empty() = \"" << a_project.empty(TAG) << "\"" << std::endl;
    //std::cout << "count() = \"" << a_project.count(TAG) << "\"" << std::endl;
    std::cout << "has_handle() = \"" << a_project.has_handle(Handle<T>()) << "\"" << std::endl;

    // no handles so this should be null
    auto l_h = a_project.get_handle_at(Tag<T>(), 0);
    assert(!l_h);

    // no handles so this should be empty
    auto l_hs = a_project.get_handles(Tag<T>());
    assert(l_hs.size() == 0);

    // no handles so this should be empty
    auto l_ns = a_project.get_names(Tag<T>());
    assert(l_ns.size() == 0);

    assert(a_project.empty(Tag<T>()));
    assert(a_project.count(Tag<T>()) == 0);


    // make a default handle
    auto lh1 = a_project.make_default(Tag<T>());
    assert(lh1);
    std::cout << "make_default()" << std::endl;
    std::cout << "id = " << lh1.id() << std::endl;
    std::cout << "name = " << lh1->cname().toStdString() << std::endl;

    // add it to the project
    bool l_res1 = a_project.add(lh1);
    assert(l_res1);
    assert(!a_project.empty(Tag<T>()));
    assert(a_project.count(Tag<T>()) == 1);
    assert(a_project.has_handle(lh1));
    assert(a_project.has_handle_named(Tag<T>(),lh1->cname()));

    // Try adding it again, should fail
    bool l_res1a = a_project.add(lh1);
    assert(!l_res1a);
    assert(!a_project.empty(Tag<T>()));
    assert(a_project.count(Tag<T>()) == 1);
    assert(a_project.has_handle(lh1));

    // make another default handle
    auto lh2 = a_project.make_default(Tag<T>());
    assert(lh1);
    std::cout << "make_default()" << std::endl;
    std::cout << "id = " << lh2.id() << std::endl;
    std::cout << "name = " << lh2->cname().toStdString() << std::endl;

    // add it to the project
    bool l_res2 = a_project.add(lh2);
    assert(l_res2);
    assert(!a_project.empty(Tag<T>()));
    assert(a_project.count(Tag<T>()) == 2);
    assert(a_project.has_handle(lh2));
    assert(a_project.has_handle_named(Tag<T>(),lh2->cname()));


    // Make a name
    QString l_name{"dataname"};
    // Make some data
    Data<T> l_d1{l_name};

    // make emplace handle
    auto lh3 = a_project.make_emplace(std::move(l_d1));
    assert(lh3);
    std::cout << "make_emplace()" << std::endl;
    std::cout << "id = " << lh3.id() << std::endl;
    std::cout << "name = " << lh3->cname().toStdString() << std::endl;

    // add it to the project
    bool l_res3 = a_project.add(lh3);
    assert(l_res3);
    assert(!a_project.empty(Tag<T>()));
    assert(a_project.count(Tag<T>()) == 3);
    assert(a_project.has_handle(lh3));
    assert(a_project.has_handle_named(Tag<T>(),lh3->cname()));

    // Make some more data with the same name
    Data<T> l_d2{l_name};

    // make emplace handle
    auto lh4 = a_project.make_emplace(std::move(l_d2));
    assert(lh4);
    std::cout << "make_emplace()" << std::endl;
    std::cout << "id = " << lh4.id() << std::endl;
    std::cout << "name = " << lh4->cname().toStdString() << std::endl;

    // add it to the project
    bool l_res4 = a_project.add(lh4);
    assert(l_res4);
    assert(!a_project.empty(Tag<T>()));
    assert(a_project.count(Tag<T>()) == 4);
    assert(a_project.has_handle(lh4));
    assert(a_project.has_handle_named(Tag<T>(),lh4->cname()));



    std::cout << "-------------------------" << std::endl;
  }

}
*/

void sak::testing::test_project_data()
{
  std::cout << "Testing sak::Project_Data" << std::endl;
  std::cout << "==============================" << std::endl;

  using namespace sak;
/*
  auto l_pd_size = sizeof(Project_Data);
  auto l_pd_members_size = sizeof(std::size_t)
                           + sizeof(std::vector<Handle<File_Definition>>)
                           + sizeof(std::vector<Handle<Texture_Definition>>)
                           + sizeof(std::vector<Handle<Material_Definition>>);
  std::cout << "sizeof(Project_Data) = " << l_pd_size <<  std::endl;
  std::cout << "sizeof(Project_Data::members) = " << l_pd_members_size <<  std::endl;
  std::cout << "Project_Data imp overhead = " << l_pd_size - l_pd_members_size <<  std::endl;

  using PD_F = Project_Data_Imp<File_Definition>;
  using PD_FT = Project_Data_Imp<File_Definition, Texture_Definition>;
  using PD_FTM = Project_Data_Imp<File_Definition, Texture_Definition, Material_Definition>;

  std::cout << "sizeof(PD_F) = " << sizeof(PD_F) <<  std::endl;
  std::cout << "sizeof(PD_FT) = " << sizeof(PD_FT) <<  std::endl;
  std::cout << "sizeof(PD_FTM) = " << sizeof(PD_FTM) <<  std::endl;

  QString l_filepath{"D:/Source Army Knife/Test Projects/Project/Project.sakpro"};

  Project_Data l_p{l_filepath};

  std::cout << "Name =     \"" << l_p.name().toStdString() << "\"" << std::endl;
  std::cout << "Location = \"" << l_p.location().toStdString() << "\"" << std::endl;
  std::cout << "Filepath = \"" << l_p.filepath().toStdString() << "\"" << std::endl;

  //constexpr File_Tag const file_tag{};
  //constexpr Texture_Tag const texture_tag{};

  // Test the id access is being shared properly
  auto l_fh1 = l_p.make_default(File_Tag());
  assert(l_fh1.id() == 1);

  auto l_fh2 = l_p.make_default(File_Tag());
  assert(l_fh2.id() == 2);

  auto l_th1 = l_p.make_default(Texture_Tag());
  assert(l_th1.id() == 3);

  auto l_th2 = l_p.make_default(Texture_Tag());
  assert(l_th2.id() == 4);

  do_project_test<File_Definition>(l_p);
  do_project_test<Texture_Definition>(l_p);
  do_project_test<Material_Definition>(l_p);
*/
  std::cout << "==============================" << std::endl;
}
