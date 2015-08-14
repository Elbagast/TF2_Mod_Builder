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
    using Thing_Index = datalib::Smart_Handle<Thing_Manager>;

    using Thing_Manager_Alt = datalib::Smart_Handle_Manager < Thing , datalib::Handle_Factory, datalib::Reference_Counted_Value_Storage >;


    using Thing_Index_Alt = datalib::Smart_Handle<Thing_Manager_Alt>;


    std::ostream& operator<<(std::ostream& os, Thing const& thing)
    {
        os << "Something{ value=\"" << thing.get_value() << "\"}";
        return os;
    }

    std::ostream& operator<<(std::ostream& os, Thing_H const& handle)
    {
        os << handle.underlying_value();
        return os;
    }

    std::ostream& operator<<(std::ostream& os, Thing_Index const& index)
    {
        os  << "Index{ is_null=" << std::boolalpha << index.is_null() << std::noboolalpha
            << " H=" << index.handle()
            << " RC=" << index.reference_count()
            << " Data=" << (index.cdata() ? index.cdata()->get_value() : "") << "}";
        return os;
    }

    std::ostream& operator<<(std::ostream& os, Thing_Index_Alt const& index)
    {
        os  << "Index{ is_null=" << std::boolalpha << index.is_null() << std::noboolalpha
            << " H=" << index.handle()
            << " RC=" << index.reference_count()
            << " Data=" << (index.is_valid() ? index.cdata().get_value() : "") << "}";
        return os;
    }
}

void datalib::test()
{
    std::cout << "Handles Test" << std::endl << std::endl;



    Thing_Manager manager{};

    Thing_Index index0{ manager.make_null_handle() };

    Thing_Index index1{ manager.emplace_data(std::make_unique<Thing>("first")) };  // ID = 1
    Thing_Index index2{ manager.emplace_data(std::make_unique<Thing>("second")) }; // ID = 2
    Thing_Index index3{ index1 }; // ID = 1
    Thing_Index index4{ index1 }; // ID = 1

    std::cout << "index0: " << index0 << std::endl;
    std::cout << "index1: " << index1 << std::endl;
    std::cout << "index2: " << index2 << std::endl;
    std::cout << "index3: " << index3 << std::endl;
    std::cout << "index4: " << index4 << std::endl;
    std::cout << std::endl;
    {
        Thing_Index index5{ manager.emplace_data(std::make_unique<Thing>("third")) }; // ID = 3
        Thing_Index index6{ index1 }; // ID = 1
        Thing_Index index7{ index1 }; // ID = 1
        Thing_Index index8{ std::move(index2) }; // ID = 2

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

    Thing_Index index9{ manager.emplace_data(std::make_unique<Thing>("forth")) }; // this should get id = 2 when ids are tracked

    std::cout << "index9: " << index9 << std::endl; // ID = 2

    std::cout << "----------------------------------------" << std::endl;
}

void datalib::test2()
{
    std::cout << "Handles Test 2" << std::endl << std::endl;



    Thing_Manager_Alt manager{};

    Thing_Index_Alt index0{ manager.make_null_handle() };

    Thing_Index_Alt index1{ manager.emplace_data(Thing("first")) };  // ID = 1
    Thing_Index_Alt index2{ manager.emplace_data(Thing("second")) }; // ID = 2
    Thing_Index_Alt index3{ index1 }; // ID = 1
    Thing_Index_Alt index4{ index1 }; // ID = 1

    std::cout << "index0: " << index0 << std::endl;
    std::cout << "index1: " << index1 << std::endl;
    std::cout << "index2: " << index2 << std::endl;
    std::cout << "index3: " << index3 << std::endl;
    std::cout << "index4: " << index4 << std::endl;
    std::cout << std::endl;
    {
        Thing_Index_Alt index5{ manager.emplace_data(Thing("third")) }; // ID = 3
        Thing_Index_Alt index6{ index1 }; // ID = 1
        Thing_Index_Alt index7{ index1 }; // ID = 1
        Thing_Index_Alt index8{ std::move(index2) }; // ID = 2

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

    Thing_Index_Alt index9{ manager.emplace_data(Thing("forth")) }; // this should get id = 2 when ids are tracked

    std::cout << "index9: " << index9 << std::endl; // ID = 2

    std::cout << "----------------------------------------" << std::endl;
}
