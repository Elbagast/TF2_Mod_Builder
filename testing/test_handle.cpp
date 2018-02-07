#include "test_handle.hpp"

#include <sak/data_definitions.hpp>
#include <sak/class_definitions.hpp>
#include <sak/data.hpp>
#include <sak/handle.hpp>

#include <iostream>
#include <cassert>

namespace
{
  template <typename T>
  void do_test_handle(std::ostream& a_stream)
  {
    using namespace sak;
    using Data_Type = Data<T>;
    using Handle_Type = Handle<T>;

    std::cout << "sizeof(Handle<T>) = " << sizeof(Handle<T>) <<  std::endl;

    a_stream << "Handle<T>:" << std::endl;
    a_stream << "-------------------------" << std::endl;
    a_stream << "Typestring = \"" << T::Typestring_Type::data() << "\"" << std::endl;

    // Test a null handle
    Handle_Type l_h1{};
    assert(!l_h1);
    assert(l_h1.id() == 0);
    assert(l_h1.use_count() == 0);
    assert(l_h1.get() == nullptr);

    // Test a non-null handle
    std::size_t l_id{1};
    Handle_Type l_h2{std::make_shared<Data_Type>(),l_id};
    assert(l_h2);
    assert(l_h2.id() == l_id);
    assert(l_h2.use_count() == 1);
    assert(l_h2.get() != nullptr);

    QString l_testname1{ u8"test name"};
    l_h2->name() = l_testname1;
    assert(l_h2->cname() == l_testname1);
    // Test data access by copying
    Data_Type l_d{*l_h2};
    assert(l_d.cname() == l_testname1);
    assert(l_d.cname() == l_h2->cname());

    // Copy a handle
    Handle_Type l_h3{l_h2};
    assert(l_h2);
    assert(l_h2.id() == l_id);
    assert(l_h2.use_count() == 2);
    assert(l_h2.get() != nullptr);

    assert(l_h3);
    assert(l_h3.id() == l_id);
    assert(l_h3.id() == l_h2.id());
    assert(l_h3.use_count() == 2);
    assert(l_h3.get() != nullptr);

    // comparing

    assert(l_h1 != l_h2);
    assert(l_h1 != l_h3);

    assert(l_h2 == l_h3);

    assert(l_h1 < l_h2);
    assert(l_h1 < l_h3);

    QString l_testname2{ u8"test name"};
    ++l_id;
    Handle_Type l_h4{std::make_shared<Data_Type>(l_testname2),l_id};

    // None of these should equal the new handle
    assert(l_h1 != l_h4);
    assert(l_h2 != l_h4);
    assert(l_h3 != l_h4);

    // Due to its higher id, these should all be less than the new one
    assert(l_h1 < l_h4);
    assert(l_h2 < l_h4);
    assert(l_h3 < l_h4);

    // Which means it should be greater than them too
    assert(l_h4 > l_h1);
    assert(l_h4 > l_h2);
    assert(l_h4 > l_h3);

    // reseting
    l_h3.reset();
    assert(!l_h3);
    assert(l_h3.id() == 0);
    assert(l_h3.use_count() == 0);
    assert(l_h3.get() == nullptr);

    assert(l_h2.use_count() == 1);

    assert(l_h1 == l_h3);
    assert(l_h2 != l_h3);

    assert(l_h3 < l_h2);
    assert(l_h3 < l_h4);



    a_stream << "-------------------------" << std::endl;
  }
}


void sak::testing::test_handle()
{
  std::cout << "Testing sak::Handle<T>" << std::endl;
  std::cout << "==============================" << std::endl;

  using namespace sak;

  using File_Data = Data<File_Definition>;
  using Texture_Data = Data<Texture_Definition>;

  using File_Handle = Handle<File_Definition>;
  using Texture_Handle = Handle<Texture_Definition>;

  do_test_handle<File_Definition>(std::cout);
  do_test_handle<Texture_Definition>(std::cout);

  std::cout << "==============================" << std::endl;
}
