#include "property_test.h"
#include "property.h"

#include <string>
#include <iostream>

namespace
{
    ALL_TEMPLATES_PROPERTY(Poop)

}

void saklib::property_test()
{
    std::cout << "Templated Properties Test" << std::endl << std::endl;

    local::Property_RW<int> some_property{154};
    std::cout << some_property.data() << std::endl;
    some_property.set_data(123);
    std::cout << some_property.data() << std::endl;

    Local_Poop_RW<std::string> test_poop{};

    std::cout << test_poop.Poop_c_str() << std::endl;
    test_poop.set_Poop("weeeee");
    std::cout << test_poop.Poop() << std::endl;
    test_poop.set_Poop("this is poop");
    std::cout << test_poop.Poop() << std::endl;

    std::cout << "----------------------------------------" << std::endl;
}
