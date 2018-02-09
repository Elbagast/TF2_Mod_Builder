#include "test_project_handle_factory.hpp"

#include <sak/data_definitions.hpp>
#include <sak/class_definitions.hpp>
#include <sak/data.hpp>
#include <sak/handle.hpp>
#include <sak/tag.hpp>
#include <sak/project_handle_factory.hpp>

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
  void do_test_phf(sak::Project_Handle_Factory const& a_phf)
  {
    using namespace sak;
    using Tag_Type = Tag<T>;
    using Data_Type = Data<T>;
    using Handle_Type = Handle<T>;


    std::cout << "default_name: \""
              << a_phf.default_name(Tag_Type()).toStdString()
              << "\"" << std::endl;

    // Make a null
    auto l_h0 = a_phf.make_null(Tag_Type());
    std::cout << "make_null: ";
    out_handle(l_h0);

    // Make with the default
    auto l_h1 = a_phf.make_default(Tag_Type());
    std::cout << "make_default: ";
    out_handle(l_h1);

    // Make a handle with some data
    Data_Type l_d{QString("testname")};
    auto l_h2 = a_phf.make_emplace(std::move(l_d));
    std::cout << "make_emplace([some data]): ";
    out_handle(l_h2);

    // Make a handle with some data with no name set
    auto l_h3 = a_phf.make_emplace(Data_Type{});
    std::cout << "make_emplace([data with no name]): ";
    out_handle(l_h3);

    std::cout << "-------------------------" << std::endl;
  }
}


void sak::testing::test_project_handle_factory()
{
  std::cout << "Testing sak::Project_Handle_Factory" << std::endl;
  std::cout << "==============================" << std::endl;

  using namespace sak;

  Project_Handle_Factory l_phf{};

  do_test_phf<File_Definition>(l_phf);
  do_test_phf<Texture_Definition>(l_phf);
  do_test_phf<Material_Definition>(l_phf);


  std::cout << "==============================" << std::endl;
}
