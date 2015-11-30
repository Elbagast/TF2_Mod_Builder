#include "element_data_manager__test.h"

#include "element_data_manager.h"
#include "element_data.h"
#include "attribute_data.h"
#include "type_string.h"

#include <iostream>
#include <cassert>


void saklib::internal::test_element_manager()
{
    std::cout << "test_element_manager()" << std::endl;

    using ED = Element_Data_Definition;
    using AD = Attribute_Data_Definition;

    Element_Data_Manager edm{};

    {
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

        edm.add_definition(ed1);
    }
    assert(edm.has_definition("Moooo"));
    assert(edm.get_definition_usage_count("Moooo") == 0);

    {
        ED ed1
        {
            "Poop",
            {
                AD("First", TS_Int(), -100, 100, 0),
                AD("Second", TS_Int(), -20, 20, 0)
            }
        };

        edm.add_definition(ed1);
    }
    assert(edm.has_definition("Poop"));
    assert(edm.get_definition_usage_count("Poop") == 0);

    Element_Data_Handle eh0 = edm.make_null_handle();
    assert(eh0.is_null());
    assert(!eh0.is_valid());

    Element_Data_Handle eh1 = edm.make_element_handle("Moooo");
    assert(!eh1.is_null());
    assert(eh1.is_valid());
    assert(edm.get_definition_usage_count("Moooo") == 1);

    Element_Data_Handle eh2{eh1};
    assert(eh1.get_reference_count() == 2);
    assert(eh2.get_reference_count() == 2);
    assert(edm.get_definition_usage_count("Moooo") == 1);

    Element_Data_Handle eh3 = edm.make_element_handle("Moooo");
    assert(eh1.get_reference_count() == 2);
    assert(eh2.get_reference_count() == 2);
    assert(eh3.get_reference_count() == 1);
    assert(edm.get_definition_usage_count("Moooo") == 2);

    std::cout << eh1.cget_element() << std::endl;

    std::cout << "----------------------------" << std::endl;
}
