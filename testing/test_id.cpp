#include "test_id.hpp"

#include <sak/id.hpp>

#include <sak/data_definitions.hpp>
#include <sak/class_definitions.hpp>

#include <iostream>
#include <cassert>

namespace
{
  template <typename T>
  void do_test_id(std::ostream& a_stream)
  {
    using namespace sak;
    using ID_Type = ID<T>;

    a_stream << "ID<T>:" << std::endl;
    a_stream << "-------------------------" << std::endl;
    std::cout << "sizeof(ID<T>) = " << sizeof(ID_Type) <<  std::endl;
    a_stream << "Typestring = \"" << T::Typestring_Type::data() << "\"" << std::endl;

    // Test a null id
    ID_Type l_id1{};
    assert(!l_id1);
    assert(l_id1.value() == 0);

    // Test a non-null id
    std::size_t l_value{1};
    ID_Type l_id2{l_value};
    assert(l_id2);
    assert(l_id2.value() == l_value);

    assert(l_id2.value() != 0);
    assert(l_id2.value() != l_id1.value());
    assert(l_id2 != l_id1);
    assert(l_id1 < l_id2);
    assert(l_id2 > l_id1);


    // Copy an id
    ID_Type l_id3{l_id2};
    assert(l_id2);
    assert(l_id3);
    assert(l_id2.value() == 1);
    assert(l_id2.value() == l_value);
    assert(l_id3.value() == l_value);
    assert(l_id2.value() == l_id3.value());
    assert(l_id2 == l_id3);

    // Get another
    ++l_value;
    ID_Type l_id4{l_value};
    assert(l_id4);
    assert(l_id4.value() == 2);
    assert(l_id4.value() == l_value);

    // Test Swap
    assert(l_id3 < l_id4);
    assert(l_id3.value() == 1);
    assert(l_id4.value() == 2);
    swap(l_id3,l_id4);
    assert(l_id3 > l_id4);
    assert(l_id3.value() == 2);
    assert(l_id4.value() == 1);

    // Test Reset
    assert(l_id3);
    l_id3.reset();
    assert(!l_id3);
    assert(l_id3.value() == 0);
    assert(l_id3.value() == l_id1.value());
    assert(l_id3 == l_id1);
    a_stream << "-------------------------" << std::endl;
  }
}


void sak::testing::test_id()
{
  std::cout << "Testing sak::ID<T>" << std::endl;
  std::cout << "==============================" << std::endl;

  using namespace sak;

  do_test_id<File_Definition>(std::cout);
  do_test_id<Texture_Definition>(std::cout);
  do_test_id<Material_Definition>(std::cout);

  std::cout << "==============================" << std::endl;
}
