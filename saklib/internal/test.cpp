#include "test.h"

#include <string>
#include <iostream>

#include "null_handle.h"
#include "handle.h"
#include "handle_factory.h"
#include "reference_counted_storage.h"
#include "smart_handle.h"
#include "smart_handle_manager.h"

void saklib::internal::test_handle()
{
    std::cout << "test_handle()" << std::endl;

    auto h_null = null_handle();

    Handle<int> h_int_0{ null_handle() };
    Handle<int> h_int_1{ 1 };
    Handle<int> h_int_2{ 2 };
    Handle<int> h_int_3{ 3 };
    Handle<int> h_int_4{ 4 };
    Handle<int> h_int_5{ h_int_4 };
    assert(h_int_0.get_value() == 0);
    assert(h_int_0.get_value() == null_handle_value());
    assert(h_int_0 == null_handle());
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


    std::cout << "Null_Handle_Type::value = " << Null_Handle_Type::value << std::endl;
    std::cout << "Handle<int> h_int_0 = " << h_int_0.get_value() << std::endl;
    std::cout << "Handle<int> h_int_1 = " << h_int_1.get_value() << std::endl;
    std::cout << "Handle<int> h_int_2 = " << h_int_2.get_value() << std::endl;
    std::cout << "Handle<int> h_int_3 = " << h_int_3.get_value() << std::endl;
    std::cout << "Handle<int> h_int_4 = " << h_int_4.get_value() << std::endl;
    std::cout << "Handle<int> h_int_5 = " << h_int_5.get_value() << std::endl;

    {
        Handle<int> h_int_6{6};
        assert(h_int_6.get_value() == 6);
        h_int_5 = std::move(h_int_6);
        assert(h_int_5.get_value() == 6);
        assert(h_int_6.get_value() == null_handle_value());
        assert(h_int_6 == null_handle());

        std::cout << "Handle<int> h_int_5 = " << h_int_5.get_value() << std::endl;
        std::cout << "Handle<int> h_int_6 = " << h_int_6.get_value() << std::endl;
    }

}

void saklib::internal::test_handle_factory()
{
    std::cout << "test_handle_factory()" << std::endl;

    {
        std::cout << "Handle_Factory<int>" << std::endl;

        Handle_Factory<int> l_factory{};

        auto h_0 = l_factory.make_null_handle();
        auto h_1 = l_factory.make_new_handle();
        auto h_2 = l_factory.make_new_handle();
        auto h_3 = l_factory.make_new_handle();
        auto h_4 = l_factory.make_new_handle();
        auto h_5 = h_4;

        assert(h_0.get_value() == 0);
        assert(h_0.get_value() == null_handle_value());
        assert(h_0 == null_handle());
        assert(h_1.get_value() == 1);
        assert(h_2.get_value() == 2);
        assert(h_3.get_value() == 3);
        assert(h_4.get_value() == 4);
        assert(h_5.get_value() == 4);

        l_factory.revoke_handle(h_3);
        l_factory.revoke_handle(h_4);

        auto h_6 = l_factory.make_new_handle();
        auto h_7 = l_factory.make_new_handle();
        assert(h_6 == h_3);
        assert(h_7 == (h_4));
    }

    {
        std::cout << "Sequential_Handle_Factory<int>" << std::endl;

        Sequential_Handle_Factory<int> l_factory{};

        auto h_0 = l_factory.make_null_handle();
        auto h_1 = l_factory.make_new_handle();
        auto h_2 = l_factory.make_new_handle();
        auto h_3 = l_factory.make_new_handle();
        auto h_4 = l_factory.make_new_handle();
        auto h_5 = h_4;

        assert(h_0.get_value() == 0);
        assert(h_0.get_value() == null_handle_value());
        assert(h_0 == null_handle());
        assert(h_1.get_value() == 1);
        assert(h_2.get_value() == 2);
        assert(h_3.get_value() == 3);
        assert(h_4.get_value() == 4);
        assert(h_5.get_value() == 4);

        l_factory.revoke_handle(h_3);
        l_factory.revoke_handle(h_4);

        auto h_6 = l_factory.make_new_handle();
        auto h_7 = l_factory.make_new_handle();
        assert(h_6.get_value() == 5);
        assert(h_7.get_value() == 6);
    }
}

void saklib::internal::test_reference_counted_storage()
{
    std::cout << "test_reference_counted_storage()" << std::endl;
    {
        std::cout << "Reference_Counted_Storage<int>" << std::endl;

        Reference_Counted_Storage<int> l_rc_storage{};

        auto h_0 = l_rc_storage.make_null_handle();
        auto h_1 = l_rc_storage.emplace_data(111);
        auto h_2 = l_rc_storage.emplace_data(222);
        auto h_3 = l_rc_storage.emplace_data(333);

        assert(!l_rc_storage.is_valid(h_0));
        assert(l_rc_storage.is_valid(h_1));
        assert(l_rc_storage.is_valid(h_2));
        assert(l_rc_storage.is_valid(h_3));

        assert(!l_rc_storage.has_data(h_0));
        assert(l_rc_storage.has_data(h_1));
        assert(l_rc_storage.has_data(h_2));
        assert(l_rc_storage.has_data(h_3));

        try
        {
            assert(l_rc_storage.cget_data(h_0) == 0);
        }
        catch(std::range_error& e)
        {
            assert(true);
        }

        assert(l_rc_storage.cget_data(h_1) == 111);
        assert(l_rc_storage.cget_data(h_2) == 222);
        assert(l_rc_storage.cget_data(h_3) == 333);

    }

    {
        std::cout << "Reference_Counted_Storage<int*>" << std::endl;

        Reference_Counted_Storage<int*> l_rc_storage{};

        auto h_0 = l_rc_storage.make_null_handle();
        auto h_1 = l_rc_storage.emplace_data(std::make_unique<int>(111));
        auto h_2 = l_rc_storage.emplace_data(std::make_unique<int>(222));
        auto h_3 = l_rc_storage.emplace_data(std::make_unique<int>(333));

        assert(!l_rc_storage.is_valid(h_0));
        assert(l_rc_storage.is_valid(h_1));
        assert(l_rc_storage.is_valid(h_2));
        assert(l_rc_storage.is_valid(h_3));

        assert(!l_rc_storage.has_data(h_0));
        assert(l_rc_storage.has_data(h_1));
        assert(l_rc_storage.has_data(h_2));
        assert(l_rc_storage.has_data(h_3));

        assert(l_rc_storage.cget_data(h_0) == nullptr);

        assert(*(l_rc_storage.cget_data(h_1)) == 111);
        assert(*(l_rc_storage.cget_data(h_2)) == 222);
        assert(*(l_rc_storage.cget_data(h_3)) == 333);
    }

}

void saklib::internal::test_smart_handle_manager()
{
    std::cout << "test_smart_handle_manager()" << std::endl;

    Smart_Handle_Manager<int> l_manager{};

    auto sm0 = l_manager.make_null_handle();
    assert(sm0.is_null());
    assert(!sm0.is_valid());
    assert(sm0.get_handle_value() == 0);

    auto sm1 = l_manager.emplace_data(111);
    std::cout << "sm1 is_valid=" << sm1.is_valid()
              << " get_handle_value()=" << sm1.get_handle_value()
              << " cget_data()=" << sm1.cget_data()
              << " cget_cmanager()=" << sm1.cget_storage()
              << std::endl;
    assert(sm1.is_valid());
    assert(sm1.get_handle_value() == 1);
    assert(sm1.cget_data() == 111);
    //assert(sm1.cget_cmanager() == &l_manager);

    auto sm2 = l_manager.emplace_data(222);
    std::cout << "sm2 is_valid=" << sm2.is_valid()
              << " get_handle_value()=" << sm2.get_handle_value()
              << " cget_data()=" << sm2.cget_data()
              << " cget_cmanager()=" << sm2.cget_storage()
              << std::endl;
    assert(sm2.is_valid());
    assert(sm2.get_handle_value() == 2);
    assert(sm2.get_reference_count() == 1);
    assert(sm2.cget_data() == 222);
    //assert(sm2.cget_cmanager() == &l_manager);

    auto sm3 = l_manager.emplace_data(333);
    std::cout << "sm3 is_valid=" << sm3.is_valid()
              << " get_handle_value()=" << sm3.get_handle_value()
              << " cget_data()=" << sm3.cget_data()
              << " cget_cmanager()=" << sm3.cget_storage()
              << std::endl;
    assert(sm3.is_valid());
    assert(sm3.get_handle_value() == 3);
    assert(sm3.get_reference_count() == 1);
    assert(sm3.cget_data() == 333);
    //assert(sm3.cget_cmanager() == &l_manager);

    auto sm4 = sm3;
    std::cout << "sm4 is_valid=" << sm4.is_valid()
              << " get_handle_value()=" << sm4.get_handle_value()
              << " cget_data()=" << sm4.cget_data()
              << " cget_cmanager()=" << sm4.cget_storage()
              << std::endl;
    assert(sm4.is_valid());
    assert(sm4 == sm3);
    assert(sm4.get_handle() == sm3.get_handle());
    assert(sm4.get_handle_value() == 3);
    assert(sm3.get_reference_count() == 2);
    assert(sm4.get_reference_count() == 2);
    assert(sm4.cget_data() == 333);
    assert(sm4.cget_data() == sm3.cget_data());
    //assert(sm4.cget_cmanager() == &l_manager);
    assert(sm4.cget_storage() == sm3.cget_storage());

    {
        auto sm5 = std::move(sm4);

        assert(sm4.is_null());
        assert(sm5.get_handle_value() == 3);

        assert(sm5.is_valid());
        assert(sm5.get_handle_value() == 3);
        assert(sm5.get_reference_count() == 2);
        assert(sm5.cget_data() == 333);

        sm5 = l_manager.emplace_data(444);

        assert(sm3.get_reference_count() == 1);
        assert(sm5.get_reference_count() == 1);
        assert(sm5.cget_data() == 444);
        assert(sm5.get_handle_value() == 4);

        sm4 = l_manager.emplace_data(555);
        assert(sm4.get_handle_value() == 5);
        assert(sm4.get_reference_count() == 1);
        assert(sm4.cget_data() == 555);

        auto sm6 = sm4;
        auto sm7 = sm4;
        auto sm8 = sm4;

        auto sm9 = l_manager.emplace_data(1111);
        assert(sm9.get_handle_value() == 6);
        auto sm10 = l_manager.emplace_data(1111);
        assert(sm10.get_handle_value() == 7);
        auto sm11 = l_manager.emplace_data(1111);
        assert(sm11.get_handle_value() == 8);

        assert(sm4.get_reference_count() == 4);
    }
    assert(sm4.get_handle_value() == 5);

    assert(sm4.get_reference_count() == 1);
    assert(sm4.cget_data() == 555);
    assert(sm3.get_reference_count() == 1);

    auto sm6 = l_manager.emplace_data(666);
    std::cout << "sm6 is_valid=" << sm6.is_valid()
              << " get_handle_value()=" << sm6.get_handle_value()
              << " cget_data()=" << sm6.cget_data()
              << " cget_cmanager()=" << sm6.cget_storage()
              << std::endl;
    assert(sm6.get_reference_count() == 1);
    assert(sm6.get_handle_value() == 4); // this handle value should have been revoked and reissued
    assert(sm6.cget_data() == 666);

}

namespace saklib
{
    namespace internal
    {
        namespace
        {
            class Link;

            class Link_Pre_Destructor;

            using Link_H = Handle < Link >;
            using Link_Manager = Smart_Handle_Manager < Link >;
            using Link_SH = Link_Manager::smart_handle_type;

            class Link_Pre_Destructor
            {
            public:
                using data_type = Link;
                using arg_type = Link&;

                void operator()(arg_type a_value) const;
            };


            class Link
            {
            public:
                Link() : m_child( Link_SH() ) {}
                explicit Link(Link_SH const& child) : m_child( child ) {}
                ~Link() = default;

                Link_SH & get_child()                   { return m_child; }
                Link_SH const& cget_child() const       { return m_child; }
                void set_child(Link_SH const& value)    { m_child = value; }
            private:
                Link_SH m_child;
            };


            std::ostream& operator<<(std::ostream& os, Link_H const& handle)
            {
                os << handle.get_value();
                return os;
            }


            std::ostream& operator<<(std::ostream& os, Link const& thing)
            {
                os << "Link{ child=\"" << thing.cget_child().get_handle_value() << "\"}";
                return os;
            }

            std::ostream& operator<<(std::ostream& os, Link_SH const& a_smart_handle)
            {
                os  << "Link_SH{ is_null=" << std::boolalpha << a_smart_handle.is_null() << std::noboolalpha
                    << " H=" << a_smart_handle.get_handle()
                    << " RC=" << a_smart_handle.get_reference_count()
                    << " Data=" << a_smart_handle.cget_data()
                    << " }";
                return os;
            }
        }
    }
}

void saklib::internal::Link_Pre_Destructor::operator ()(arg_type a_value) const
{
    a_value.set_child(Link_SH());
}



void saklib::internal::test_smart_handle_manager__handle_owning_data()
{
    std::cout << "test_smart_handle_manager__handle_owning_data()" << std::endl << std::endl;

    Link_Manager manager{};

    auto link0 = manager.emplace_data(Link());
    auto link1 = manager.emplace_data(Link());
    auto link2 = manager.emplace_data(Link());
    //Link_SH link0{ manager.emplace_data(std::make_unique<Link>()) };
    //Link_SH link1{ manager.emplace_data(std::make_unique<Link>()) };
    //Link_SH link2{ manager.emplace_data(std::make_unique<Link>()) };

    std::cout << "link0: " << link0 << std::endl; // H = 1, child = 0
    std::cout << "link1: " << link1 << std::endl; // H = 2, child = 0
    std::cout << "link2: " << link2 << std::endl; // H = 3, child = 0

    std::cout << std::endl;

    //link0.data()->set_child(manager.emplace_data(std::make_unique<Link>()));
    link0.get_data().set_child(link1);
    link1.get_data().set_child(link2);

    std::cout << "link0: " << link0 << std::endl; // H = 1, child = 2
    std::cout << "link1: " << link1 << std::endl; // H = 2, child = 0
    std::cout << "link2: " << link2 << std::endl; // H = 3, child = 0

    std::cout << std::endl;

    {
        Link_SH link3{ manager.emplace_data(Link()) };
        link2.get_data().set_child(link3);
        std::cout << "link0: " << link0 << std::endl; // H = 1, child = 2
        std::cout << "link1: " << link1 << std::endl; // H = 2, child = 3
        std::cout << "link2: " << link2 << std::endl; // H = 3, child = 4
        std::cout << "link3: " << link3 << std::endl; // H = 4, child = 0
    }

    std::cout << std::endl;

    std::cout << "link0: " << link0 << std::endl; // H = 1, child = 2
    std::cout << "link1: " << link1 << std::endl; // H = 2, child = 3
    std::cout << "link2: " << link2 << std::endl; // H = 3, child = 4

    std::cout << "link3: " << link2.cget_data().cget_child() << std::endl; // H = 4, child = 0

    std::cout << std::endl;

    // we can make a circular reference that will break things on destruction....

    //link1.data()->set_child(link0);

    //std::cout << "link0: " << link0 << std::endl; // H = 1, child = 2
    //std::cout << "link1: " << link1 << std::endl; // H = 2, child = 1
    //std::cout << "link2: " << link2 << std::endl; // H = 3, child = 4
    //std::cout << "link3: " << link2.cdata()->cget_child() << std::endl; // H = 4, child = 0


    std::cout << "----------------------------------------" << std::endl;
}

/*
#include "handle.h"
#include "handle_factory.h"
#include "smart_handle.h"
#include "smart_handle_manager.h"
#include "reference_counted_value_storage.h"
#include "reference_counted_pointer_storage.h"
#include "smart_handle_pointer_manager.h"

#include <string>
#include <iostream>
#include <tuple>



namespace
{
    class Thing
    {
    public:
        explicit Thing(std::string const& value) : m_value( value ) {}
        ~Thing() = default;

        std::string const& get_value() const        { return m_value; }
        void set_value(std::string const& value)    { m_value = value; }
        void do_stuff() const                       { std::cout << "Thing::do_stuff()" << std::endl; }
    private:
        std::string m_value;
    };



    using Thing_H = datalib::Handle < Thing >;
    using Thing_H_Factory = datalib::Handle_Factory < Thing >;

    using Thing_Manager = datalib::Smart_Handle_Manager < Thing , datalib::Handle_Factory, datalib::Reference_Counted_Pointer_Storage, datalib::No_Pre_Destruction<Thing> >;
    using Thing_SH = datalib::Smart_Handle<Thing_Manager>;

    using Thing_Manager_Alt = datalib::Smart_Handle_Manager < Thing , datalib::Handle_Factory, datalib::Reference_Counted_Value_Storage, datalib::No_Pre_Destruction<Thing> >;


    using Thing_SH_Alt = datalib::Smart_Handle<Thing_Manager_Alt>;


    std::ostream& operator<<(std::ostream& os, Thing const& thing)
    {
        os << "Thing{ value=\"" << thing.get_value() << "\"}";
        return os;
    }

    std::ostream& operator<<(std::ostream& os, Thing_H const& handle)
    {
        os << handle.underlying_value();
        return os;
    }

    std::ostream& operator<<(std::ostream& os, Thing_SH const& index)
    {
        os  << "Thing_SH{ is_null=" << std::boolalpha << index.is_null() << std::noboolalpha
            << " H=" << index.handle()
            << " RC=" << index.reference_count()
            << " Data=\"" << (index.cmanager() && index.cdata() ? index.cdata()->get_value() : "") << "\"}";
        return os;
    }

    std::ostream& operator<<(std::ostream& os, Thing_SH_Alt const& index)
    {
        os  << "Thing_SH_Alt{ is_null=" << std::boolalpha << index.is_null() << std::noboolalpha
            << " H=" << index.handle()
            << " RC=" << index.reference_count()
            << " Data=\"" << (index.cmanager() && index.is_valid() ? index.cdata().get_value() : "") << "\"}";
        return os;
    }
}

void datalib::test()
{
    std::cout << "Handles Test" << std::endl << std::endl;



    Thing_Manager manager{};

    Thing_SH index0{ manager.make_null_handle() };

    Thing_SH index1{ manager.emplace_data(std::make_unique<Thing>("first")) };  // ID = 1
    Thing_SH index2{ manager.emplace_data(std::make_unique<Thing>("second")) }; // ID = 2
    Thing_SH index3{ index1 }; // ID = 1
    Thing_SH index4{ index1 }; // ID = 1

    std::cout << "index0: " << index0 << std::endl;
    std::cout << "index1: " << index1 << std::endl;
    std::cout << "index2: " << index2 << std::endl;
    std::cout << "index3: " << index3 << std::endl;
    std::cout << "index4: " << index4 << std::endl;
    std::cout << std::endl;
    {
        Thing_SH index5{ manager.emplace_data(std::make_unique<Thing>("third")) }; // ID = 3
        Thing_SH index6{ index1 }; // ID = 1
        Thing_SH index7{ index1 }; // ID = 1
        Thing_SH index8{ std::move(index2) }; // ID = 2

        std::cout << "index2: " << index2 << std::endl; // now ID = 0
        std::cout << "index5: " << index5 << std::endl;
        std::cout << "index6: " << index6 << std::endl;
        std::cout << "index7: " << index7 << std::endl;
        std::cout << "index8: " << index8 << std::endl;

        index4 = index5;
        std::cout << "index4: " << index4 << std::endl; // now ID = 3, rc = 2

        std::cout << std::endl;
    }
    std::cout << "index0: " << index0 << std::endl; // ID = 0
    std::cout << "index1: " << index1 << std::endl; // ID = 1
    std::cout << "index2: " << index2 << std::endl; // ID = 0
    std::cout << "index3: " << index3 << std::endl; // ID = 1
    std::cout << "index4: " << index4 << std::endl; // ID = 3, rc = 1

    Thing_SH index9{ manager.emplace_data(std::make_unique<Thing>("forth")) }; // this should get id = 2 when ids are tracked

    std::cout << "index9: " << index9 << std::endl; // ID = 2

    std::cout << "----------------------------------------" << std::endl;
}

void datalib::test2()
{
    std::cout << "Handles Test 2" << std::endl << std::endl;



    Thing_Manager_Alt manager{};

    Thing_SH_Alt index0{ manager.make_null_handle() };

    Thing_SH_Alt index1{ manager.emplace_data(Thing("first")) };  // ID = 1
    Thing_SH_Alt index2{ manager.emplace_data(Thing("second")) }; // ID = 2
    Thing_SH_Alt index3{ index1 }; // ID = 1
    Thing_SH_Alt index4{ index1 }; // ID = 1

    std::cout << "index0: " << index0 << std::endl;
    std::cout << "index1: " << index1 << std::endl;
    std::cout << "index2: " << index2 << std::endl;
    std::cout << "index3: " << index3 << std::endl;
    std::cout << "index4: " << index4 << std::endl;
    std::cout << std::endl;
    {
        Thing_SH_Alt index5{ manager.emplace_data(Thing("third")) }; // ID = 3
        Thing_SH_Alt index6{ index1 }; // ID = 1
        Thing_SH_Alt index7{ index1 }; // ID = 1
        Thing_SH_Alt index8{ std::move(index2) }; // ID = 2

        std::cout << "index2: " << index2 << std::endl; // now ID = 0
        std::cout << "index5: " << index5 << std::endl;
        std::cout << "index6: " << index6 << std::endl;
        std::cout << "index7: " << index7 << std::endl;
        std::cout << "index8: " << index8 << std::endl;

        index4 = index5;
        std::cout << "index4: " << index4 << std::endl; // now ID = 3, rc = 2

        std::cout << std::endl;
    }
    std::cout << "index0: " << index0 << std::endl; // ID = 0
    std::cout << "index1: " << index1 << std::endl; // ID = 1
    std::cout << "index2: " << index2 << std::endl; // ID = 0
    std::cout << "index3: " << index3 << std::endl; // ID = 1
    std::cout << "index4: " << index4 << std::endl; // ID = 3, rc = 1

    Thing_SH_Alt index9{ manager.emplace_data(Thing("forth")) }; // this should get id = 2 when ids are tracked

    std::cout << "index9: " << index9 << std::endl; // ID = 2

    std::cout << "----------------------------------------" << std::endl;
}



namespace
{
    class Link;

    struct Link_Pre_Destructor;


    using Link_H = datalib::Handle < Link >;
    using Link_Manager = datalib::Smart_Handle_Manager < Link , datalib::Handle_Factory, datalib::Reference_Counted_Pointer_Storage, Link_Pre_Destructor >;
    using Link_SH = datalib::Smart_Handle < Link_Manager >;

    class Link
    {
    public:
        explicit Link(Link_SH const& child = Link_SH()) : m_child( child ) {}
        ~Link() = default;

        Link_SH & get_child()                   { return m_child; }
        Link_SH const& cget_child() const       { return m_child; }
        void set_child(Link_SH const& value)    { m_child = value; }
    private:
        Link_SH m_child;
    };

    struct Link_Pre_Destructor
    {
        using data_type = Link;

        static void prepare_to_destroy(Link& value) { value.set_child(Link_SH()); }
    };




    std::ostream& operator<<(std::ostream& os, Link_H const& handle)
    {
        os << handle.underlying_value();
        return os;
    }


    std::ostream& operator<<(std::ostream& os, Link const& thing)
    {
        os << "Link{ child=\"" << thing.cget_child().handle() << "\"}";
        return os;
    }

    std::ostream& operator<<(std::ostream& os, Link_SH const& index)
    {
        os  << "Link_SH{ is_null=" << std::boolalpha << index.is_null() << std::noboolalpha
            << " H=" << index.handle()
            << " RC=" << index.reference_count()
            << " Data=";
        if (index.cdata())
            os << *(index.cdata());
        os  << " }";
        return os;
    }
}

void datalib::test3()
{
    std::cout << "Handles Test 3" << std::endl << std::endl;


    Link_Manager manager{};

    Link_SH link0{ manager.emplace_data(std::make_unique<Link>()) };
    Link_SH link1{ manager.emplace_data(std::make_unique<Link>()) };
    Link_SH link2{ manager.emplace_data(std::make_unique<Link>()) };

    std::cout << "link0: " << link0 << std::endl; // H = 1, child = 0
    std::cout << "link1: " << link1 << std::endl; // H = 2, child = 0
    std::cout << "link2: " << link2 << std::endl; // H = 3, child = 0

    std::cout << std::endl;

    //link0.data()->set_child(manager.emplace_data(std::make_unique<Link>()));
    link0.data()->set_child(link1);
    link1.data()->set_child(link2);

    std::cout << "link0: " << link0 << std::endl; // H = 1, child = 2
    std::cout << "link1: " << link1 << std::endl; // H = 2, child = 0
    std::cout << "link2: " << link2 << std::endl; // H = 3, child = 0

    // currently the storage does not like recursive removal calls...
    //link0.data()->set_child(manager.make_null_handle());

    std::cout << std::endl;

    {
        Link_SH link3{ manager.emplace_data(std::make_unique<Link>()) };
        link2.data()->set_child(link3);
        std::cout << "link0: " << link0 << std::endl; // H = 1, child = 2
        std::cout << "link1: " << link1 << std::endl; // H = 2, child = 3
        std::cout << "link2: " << link2 << std::endl; // H = 3, child = 4
        std::cout << "link3: " << link3 << std::endl; // H = 4, child = 0
    }

    std::cout << std::endl;

    std::cout << "link0: " << link0 << std::endl; // H = 1, child = 2
    std::cout << "link1: " << link1 << std::endl; // H = 2, child = 3
    std::cout << "link2: " << link2 << std::endl; // H = 3, child = 4

    std::cout << "link3: " << link2.cdata()->cget_child() << std::endl; // H = 4, child = 0

    std::cout << std::endl;

    // we can make a circular reference that will break things on destruction....

    //link1.data()->set_child(link0);

    //std::cout << "link0: " << link0 << std::endl; // H = 1, child = 2
    //std::cout << "link1: " << link1 << std::endl; // H = 2, child = 1
    //std::cout << "link2: " << link2 << std::endl; // H = 3, child = 4
    //std::cout << "link3: " << link2.cdata()->cget_child() << std::endl; // H = 4, child = 0


    std::cout << "----------------------------------------" << std::endl;
}
*/