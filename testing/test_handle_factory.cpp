#include "test_handle_factory.hpp"

#include <sak/data_definitions.hpp>
#include <sak/class_definitions.hpp>
#include <sak/data.hpp>
#include <sak/handle.hpp>
#include <sak/handle_factory.hpp>

#include <iostream>
#include <cassert>

namespace
{
  template <typename T>
  void do_test_handle_factory(std::ostream& a_stream)
  {
    using namespace sak;
    using Data_Type = Data<T>;
    using Handle_Type = Handle<T>;
    using Factory_Type = Handle_Factory<T>;

    a_stream << "Handle_Factory<T>:" << std::endl;
    a_stream << "-------------------------" << std::endl;
    a_stream << "Typestring = \"" << T::Typestring_Type::data() << "\"" << std::endl;

    Factory_Type l_f{};

    auto l_h0 = l_f.make_null_handle();
    assert(!l_h0);
    assert(l_h0.id() == 0);
    assert(l_h0.use_count() == 0);
    assert(l_h0.get() == nullptr);

    // make a handle
    auto l_h1 = l_f.make_handle(std::make_shared<Data_Type>());
    assert(l_h1);
    assert(l_h1.id() == 1);
    assert(l_h1.use_count() == 1);
    assert(l_h1.get() != nullptr);

    // make another handle
    auto l_h2 = l_f.make_handle(std::make_shared<Data_Type>());
    assert(l_h2);
    assert(l_h2.id() == 2);
    assert(l_h2.use_count() == 1);
    assert(l_h2.get() != nullptr);

    // Distinct data
    assert(l_h1.get() != l_h2.get());

    /*
    a_stream << "Begin full factory test..." << std::endl;
    // this should trigger an exception in the factory

    try
    {
      std::size_t l_id{l_h2.id() + 1};
      std::size_t l_count{0};
      while(true)
      {
        auto l_h = l_f.make_handle(std::make_shared<Data_Type>());
        assert(l_h);
        assert(l_h.id() == l_id);
        assert(l_h.use_count() == 1);
        assert(l_h.get() != nullptr);


        // Distinct data
        assert(l_h.get() != l_h1.get());
        assert(l_h.get() != l_h2.get());

        if (l_count == 100000)
        {
          a_stream << l_count << " ";
          l_count = 0;
        }

        ++l_id;
        ++l_count;
      }
    }
    catch (std::range_error& l_exception)
    {
      a_stream << l_exception.what() << std::endl;
    }
    */
    a_stream << "-------------------------" << std::endl;
  }
}

void sak::testing::test_handle_factory()
{
  std::cout << "Testing sak::Handle_Factory<T>" << std::endl;
  std::cout << "==============================" << std::endl;

  using namespace sak;

  do_test_handle_factory<File_Definition>(std::cout);
  do_test_handle_factory<Texture_Definition>(std::cout);

  std::cout << "==============================" << std::endl;
}
