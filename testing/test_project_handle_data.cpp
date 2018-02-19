#include "test_project_handle_data.hpp"

#include <sak/data_definitions.hpp>
#include <sak/class_definitions.hpp>
#include <sak/data.hpp>
#include <sak/handle.hpp>
#include <sak/tag.hpp>
#include <sak/project_handle_factory.hpp>
#include <sak/project_handle_data.hpp>

#include <iostream>
#include <cassert>

#include <QString>

namespace
{
  template <typename T>
  void out_handle(sak::Handle<T> const& a_handle)
  {
    std::cout << "Handle type=\"" << T::Typestring_Type::data()
              << "\" ptr=\"" << a_handle.get()
              << "\" id=\"" << a_handle.id() << "\"";
    if (a_handle)
    {
      std::cout << "name=\"" << a_handle->cname().toStdString() << "\"";
    }
    std::cout << std::endl;
  }


  template <typename T>
  void do_test_phf(sak::Project_Handle_Factory const& a_phf, sak::Project_Handle_Data& a_phd)
  {
    using namespace sak;
    using Tag_Type = Tag<T>;
    using Data_Type = Data<T>;
    using Handle_Type = Handle<T>;

    assert(a_phd.cget_handles(Tag_Type()).empty());

    // First handle
    //--------------------------
    // Make a default handle
    auto l_h1 = a_phf.make_default(Tag_Type());

    // Shouldn't have this name until it's in the data
    assert(!a_phd.has_name(l_h1->cname()));

    // Add it to the data
    a_phd.get_handles(Tag_Type()).push_back(l_h1);
    assert(a_phd.cget_handles(Tag_Type()).size() == 1);

    // Should have this name now
    assert(a_phd.has_name(l_h1->cname()));

    std::cout << "name count = " << a_phd.get_all_names().size() << std::endl;

    // Second handle
    //--------------------------
    // Make another default handle
    auto l_h2 = a_phf.make_default(Tag_Type());
    assert(l_h1->cname() == l_h2->cname());

    // Fix the name of the handle
    a_phd.fix_name(l_h2->name());

    // Should be different
    assert(l_h1->cname() != l_h2->cname());

    // Should not have the fixed name
    assert(!a_phd.has_name(l_h2->cname()));

    // Add it to the data
    a_phd.get_handles(Tag_Type()).push_back(l_h2);
    assert(a_phd.cget_handles(Tag_Type()).size() == 2);

    // Should have this name now
    assert(a_phd.has_name(l_h2->cname()));

    // Third handle
    //--------------------------
    // Make another default handle
    auto l_h3 = a_phf.make_default(Tag_Type());
    assert(l_h1->cname() == l_h3->cname());

    // Fix the name of the handle
    a_phd.fix_name(l_h3->name());
    // Should be different to both the other handles
    assert(l_h1->cname() != l_h3->cname());
    assert(l_h2->cname() != l_h3->cname());

    // Should not have the fixed name
    assert(!a_phd.has_name(l_h3->cname()));

    // Add it to the data
    a_phd.get_handles(Tag_Type()).push_back(l_h3);
    assert(a_phd.cget_handles(Tag_Type()).size() == 3);

    // Should have this name now
    assert(a_phd.has_name(l_h3->cname()));

    // Fourth handle
    //--------------------------
    QString l_name{"testname"};

    // Make a handle with a non-default name
    auto l_h4 = a_phf.make_emplace(Data_Type{l_name});

    // Should not have this name THE FIRST TIME
    //assert(!a_phd.has_name(l_h4->cname()));

    // Fix the name of the handle
    a_phd.fix_name(l_h4->name());

    // Should be unchanged THE FIRST TIME
    //assert(l_h4->cname() == l_name);

    // Add it to the data
    a_phd.get_handles(Tag_Type()).push_back(l_h4);
    assert(a_phd.cget_handles(Tag_Type()).size() == 4);

    // Should have this name now
    assert(a_phd.has_name(l_h4->cname()));

    // Fifth handle
    //--------------------------
    // Make another handle with a non-default name
    auto l_h5 = a_phf.make_emplace(Data_Type{l_name});

    // Fix the name of the handle
    a_phd.fix_name(l_h5->name());

    // Should be changed
    assert(l_h5->cname() != l_name);

    // Should not have the fixed name
    assert(!a_phd.has_name(l_h5->cname()));

    // Add it to the data
    a_phd.get_handles(Tag_Type()).push_back(l_h5);
    assert(a_phd.cget_handles(Tag_Type()).size() == 5);

    // Should have this name now
    assert(a_phd.has_name(l_h5->cname()));


    for (auto const& l_handle : a_phd.cget_handles(Tag_Type{}))
    {
      out_handle(l_handle);
    }


    std::cout << "-------------------------" << std::endl;
  }
}


void sak::testing::test_project_handle_data()
{
  std::cout << "Testing sak::Project_Handle_Data" << std::endl;
  std::cout << "==============================" << std::endl;

  using namespace sak;

  // Assuming this works properly
  Project_Handle_Factory l_phf{};

  Project_Handle_Data l_phd{};

  assert(l_phd.get_all_names().empty());

  do_test_phf<File_Definition>(l_phf,l_phd);
  do_test_phf<Texture_Definition>(l_phf,l_phd);
  do_test_phf<Material_Definition>(l_phf,l_phd);


  std::cout << "All names:" << std::endl;
  std::cout << "-------------------------" << std::endl;
  for (auto const& l_name : l_phd.get_all_names())
  {
    std::cout << l_name.toStdString() << std::endl;
  }


  std::cout << "==============================" << std::endl;
}
