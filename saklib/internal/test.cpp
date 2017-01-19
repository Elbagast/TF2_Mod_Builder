#include "test.h"

#include "string.h"
#include <iostream>
#include <cassert>

#include "null_integer_id.h"
#include "uint_id.h"

void saklib::internal::test_handle()
{
    std::cout << "test_handle()" << std::endl;

    Uint_ID h_null{};

    Uint_ID h_int_0{ Uint_ID::get_null_value() };
    Uint_ID h_int_1{ 1 };
    Uint_ID h_int_2{ 2 };
    Uint_ID h_int_3{ 3 };
    Uint_ID h_int_4{ 4 };
    Uint_ID h_int_5{ h_int_4 };
    assert(h_int_0.get_value() == 0);
    //assert(h_int_0.get_value() == null_integer_id_value());
    //assert(h_int_0 == null_integer_id());
    assert(h_int_1.get_value() == 1);
    assert(h_int_2.get_value() == 2);
    assert(h_int_3.get_value() == 3);
    assert(h_int_4.get_value() == 4);
    assert(h_int_5.get_value() == 4);


    // comparison to null handle
    assert(h_int_0 == h_null);
    assert(h_int_1 != h_null);
    assert(h_int_2 != h_null);
    assert(h_int_3 != h_null);
    assert(h_int_4 != h_null);
    assert(h_int_5 != h_null);

    assert(h_null == h_int_0);
    assert(h_null != h_int_1);
    assert(h_null != h_int_2);
    assert(h_null != h_int_3);
    assert(h_null != h_int_4);
    assert(h_null != h_int_5);

    assert(h_int_4 == h_int_5);
    assert(h_int_1 != h_int_2);
    assert(h_int_1 < h_int_2);
    assert(h_int_2 > h_int_1);

    assert(h_int_3 <= h_int_4);
    assert(h_int_4 >= h_int_3);
    assert(h_int_4 <= h_int_5);
    assert(h_int_4 >= h_int_5);


    std::cout << "Null_Integer_ID_Type::value = " << Null_Integer_ID_Type::value << std::endl;
    std::cout << "Handle<int> h_int_0 = " << h_int_0.get_value() << std::endl;
    std::cout << "Handle<int> h_int_1 = " << h_int_1.get_value() << std::endl;
    std::cout << "Handle<int> h_int_2 = " << h_int_2.get_value() << std::endl;
    std::cout << "Handle<int> h_int_3 = " << h_int_3.get_value() << std::endl;
    std::cout << "Handle<int> h_int_4 = " << h_int_4.get_value() << std::endl;
    std::cout << "Handle<int> h_int_5 = " << h_int_5.get_value() << std::endl;

    {
        Uint_ID h_int_6{6};
        assert(h_int_6.get_value() == 6);
        h_int_5 = std::move(h_int_6);
        assert(h_int_5.get_value() == 6);
        //assert(h_int_6.get_value() == null_integer_id_value());
        //assert(h_int_6 == null_integer_id());

        std::cout << "Handle<int> h_int_5 = " << h_int_5.get_value() << std::endl;
        std::cout << "Handle<int> h_int_6 = " << h_int_6.get_value() << std::endl;
    }

}

void saklib::internal::test_handle_factory()
{
    std::cout << "test_handle_factory()" << std::endl;

    {
        std::cout << "Integer_ID_Factory<int>" << std::endl;

        Uint_ID_Factory l_factory{};

        auto h_0 = l_factory.make_null_id();
        auto h_1 = l_factory.issue_id();
        auto h_2 = l_factory.issue_id();
        auto h_3 = l_factory.issue_id();
        auto h_4 = l_factory.issue_id();
        auto h_5 = h_4;

        assert(h_0.get_value() == 0);
        //assert(h_0.get_value() == null_integer_id_value());
        //assert(h_0 == null_integer_id());
        assert(h_1.get_value() == 1);
        assert(h_2.get_value() == 2);
        assert(h_3.get_value() == 3);
        assert(h_4.get_value() == 4);
        assert(h_5.get_value() == 4);

        l_factory.revoke_id(h_3);
        l_factory.revoke_id(h_4);

        auto h_6 = l_factory.issue_id();
        auto h_7 = l_factory.issue_id();
        assert(h_6 == h_3);
        assert(h_7 == (h_4));
    }

}

