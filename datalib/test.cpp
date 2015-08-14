#include "test.h"

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

    //using Thing_Manager = datalib::Smart_Handle_Pointer_Manager < Thing >;
    //using Thing_Manager = datalib::Smart_Handle_Manager < Thing , datalib::Handle_Pointer_Storage<Thing>, datalib::Handle_Factory<Thing> >;
    using Thing_Manager = datalib::Smart_Handle_Manager < Thing , datalib::Handle_Factory, datalib::Reference_Counted_Pointer_Storage >;
    using Thing_SH = datalib::Smart_Handle<Thing_Manager>;

    using Thing_Manager_Alt = datalib::Smart_Handle_Manager < Thing , datalib::Handle_Factory, datalib::Reference_Counted_Value_Storage >;


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

    using Link_H = datalib::Handle < Link >;
    using Link_Manager = datalib::Smart_Handle_Manager < Link , datalib::Handle_Factory, datalib::Reference_Counted_Pointer_Storage >;
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
    //Link_SH link1{ manager.emplace_data(std::make_unique<Link>()) };
    //Link_SH link2{ manager.emplace_data(std::make_unique<Link>()) };

    std::cout << "link0: " << link0 << std::endl; // H = 1, child = 0
    //std::cout << "link1: " << link1 << std::endl; // H = 2, child = 0
    //std::cout << "link2: " << link2 << std::endl; // H = 3, child = 0

    std::cout << std::endl;

    link0.data()->set_child(manager.emplace_data(std::make_unique<Link>()));
    //link0.data()->set_child(link1);
    //link1.data()->set_child(link2);

    std::cout << "link0: " << link0 << std::endl; // H = 1, child = 2
    //std::cout << "link1: " << link1 << std::endl; // H = 2, child = 0
    std::cout << "link1: " << link0.cdata()->cget_child() << std::endl; // H = 2, child = 0
    //std::cout << "link2: " << link2 << std::endl; // H = 3, child = 0

    // currently the storage does not like recursive removal calls...
    link0.data()->set_child(manager.make_null_handle());

    std::cout << std::endl;
/*
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
    */

    std::cout << "----------------------------------------" << std::endl;
}
