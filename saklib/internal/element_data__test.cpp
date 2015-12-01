#include "element_data__test.h"

#include "element_data.h"
#include "type_string.h"

#include <iostream>

void saklib::internal::test_element()
{
    std::cout << "test_element()" << std::endl;

    using ED = Element_Data_Definition;
    using AD = Attribute_Data_Definition;

    ED ed1
    {
        "Moooo",
        {
            AD("Default Bool", TS_Bool()),
            AD("Constrained Bool",TS_Bool(), true),
            AD("Default Int", TS_Int()),
            AD("Constrained Int", TS_Int(), 0, 10, 5)
        }
    };

    std::cout << ed1 << std::endl;

    Element_Data e1{ed1, "Test Element"};

    std::cout << e1 << std::endl;

    Element_Data e2{e1};
    std::cout << e2 << std::endl;

    std::cout << "----------------------------" << std::endl;
}
