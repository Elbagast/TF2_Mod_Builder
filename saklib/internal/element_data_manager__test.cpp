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

    Element_Data_Definition_Manager eddm{};

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

        eddm.add_definition(std::move(ed1));
    }
    assert(eddm.has_definition("Moooo"));
    assert(eddm.get_definition_usage_count("Moooo") == 0);

    Element_Data_Manager edm{};

    Element_Data_Definition_Handle eddh1 = eddm.make_definition_handle("Moooo");
    assert(eddh1.is_valid());
    assert(eddh1.cget_reference_count() == 2); // should be this and the one extra increment
    assert(eddm.get_definition_usage_count("Moooo") == 1);

    Element_Data_Handle edh1 = edm.make_element(eddm.make_definition_handle("Moooo"));

    assert(edh1.is_valid());
    assert(edh1.cget_reference_count() == 1);
    assert(eddm.get_definition_usage_count("Moooo") == 2);

    std::cout << edh1.cget_element() << std::endl;

    Element_Data_Handle edh2 = edm.make_element(eddm.make_definition_handle("Moooo"));
    assert(edh2.cget_reference_count() == 1);
    assert(eddm.get_definition_usage_count("Moooo") == 3);
    {
        Element_Data_Handle edh3 = edm.make_element(eddm.make_definition_handle("Moooo"));
        assert(edh3.cget_reference_count() == 1);
        assert(eddm.get_definition_usage_count("Moooo") == 4);

        Element_Data_Handle edh2_copy{edh2};
        assert(edh2 == edh2_copy);
        assert(edh2.cget_reference_count() == 2);
        assert(edh2_copy.cget_reference_count() == 2);
    }
    assert(eddm.get_definition_usage_count("Moooo") == 3);

    // destroy a usage of this type by assigning this handle to null
    eddh1 = Element_Data_Definition_Handle();
    assert(eddm.get_definition_usage_count("Moooo") == 2);

    edh2 = Element_Data_Handle();
    assert(eddm.get_definition_usage_count("Moooo") == 1);

    edh1 = Element_Data_Handle();
    assert(eddm.get_definition_usage_count("Moooo") == 0);



    std::cout << "----------------------------" << std::endl;
}
