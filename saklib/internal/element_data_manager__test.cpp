#include "element_data_manager__test.h"

#include "element_data.h"
#include "element_data_manager.h"
#include "element_data_handle.h"

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
        AD thing{"Default Bool", Type_Bool()};
        thing.set_to_int();
        assert(thing.is_int());

        ED ed1
        {
            "Moooo",
            {
                AD("Default Bool", Type_Bool()),
                AD("Constrained Bool",Type_Bool(), true),
                AD("Default Int", Type_Int()),
                AD("Constrained Int", Type_Int(), 0, 10, 5)
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

    using EDH = Element_Data_Handle<Element_Data_Manager>;

    EDH edh1 = edm.make_element(eddm.make_definition_handle("Moooo"));

    assert(edh1.is_valid());
    assert(edh1.cget_handle().get_value() == 1);
    assert(edh1.cget_reference_count() == 1);
    assert(eddm.get_definition_usage_count("Moooo") == 2);

    //std::cout << edh1 << std::endl;

    EDH edh2 = edm.make_element(eddm.make_definition_handle("Moooo"));
    assert(edh2.is_valid());
    assert(edh2.cget_handle().get_value() == 2);
    assert(edh2.cget_reference_count() == 1);
    assert(eddm.get_definition_usage_count("Moooo") == 3);
    {
        EDH edh3 = edm.make_element(eddm.make_definition_handle("Moooo"));
        assert(edh3.is_valid());
        assert(edh3.cget_handle().get_value() == 3);
        assert(edh3.cget_reference_count() == 1);
        assert(eddm.get_definition_usage_count("Moooo") == 4);

        EDH edh4 = edm.make_element(eddm.make_definition_handle("Moooo"));
        assert(edh4.is_valid());
        assert(edh4.cget_handle().get_value() == 4);
        assert(edh4.cget_reference_count() == 1);
        assert(eddm.get_definition_usage_count("Moooo") == 5);


        EDH edh2_copy{edh2};
        assert(edh2_copy.is_valid());
        assert(edh2 == edh2_copy);
        assert(edh2_copy.cget_handle().get_value() == 2);
        assert(edh2.cget_reference_count() == 2);
        assert(edh2_copy.cget_reference_count() == 2);
    }
    assert(eddm.get_definition_usage_count("Moooo") == 3);

    EDH edh5 = edm.make_element(eddm.make_definition_handle("Moooo"));
    assert(edh5.is_valid());
    assert(edh5.cget_handle().get_value() == 5); // right now the handle is the next in the sequence rather than an old, revoked one
    assert(edh5.cget_reference_count() == 1);
    assert(eddm.get_definition_usage_count("Moooo") == 4);


    // destroy a usage of this type by assigning this handle to null
    eddh1 = Element_Data_Definition_Handle();
    assert(eddm.get_definition_usage_count("Moooo") == 3);

    edh5 = EDH();
    assert(eddm.get_definition_usage_count("Moooo") == 2);

    edh2 = EDH();
    assert(eddm.get_definition_usage_count("Moooo") == 1);

    edh1 = EDH();
    assert(eddm.get_definition_usage_count("Moooo") == 0);



    std::cout << "----------------------------" << std::endl;
}
