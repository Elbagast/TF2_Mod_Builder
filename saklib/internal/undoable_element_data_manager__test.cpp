#include "undoable_element_data_manager__test.h"


#include <iostream>
#include <cassert>

#include "type_string.h"

#include "undoable_element_data_manager.h"
#include "undoable_element_data_handle.h"
#include "all_undoable_attribute_data_handle.h"

void saklib::internal::test_undoable_element_data_manager()
{
    std::cout << "test_undoable_element_data_manager()" << std::endl;

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

    Undoable_Element_Data_Manager edm{};

    Element_Data_Definition_Handle eddh1 = eddm.make_definition_handle("Moooo");
    assert(eddh1.is_valid());
    assert(eddh1.cget_reference_count() == 2); // should be this and the one extra increment
    assert(eddm.get_definition_usage_count("Moooo") == 1);

    using UEDH = Undoable_Element_Data_Handle;

    {
        UEDH edh1 = edm.make_element(eddm.make_definition_handle("Moooo"));

        assert(edh1.is_valid());
        assert(edh1.cget_handle().get_value() == 1);
        assert(edh1.cget_reference_count() == 1);
        assert(eddm.get_definition_usage_count("Moooo") == 2);

        //std::cout << edh1 << std::endl;

        UEDH edh2 = edm.make_element(eddm.make_definition_handle("Moooo"));
        assert(edh2.is_valid());
        assert(edh2.cget_handle().get_value() == 2);
        assert(edh2.cget_reference_count() == 1);
        assert(eddm.get_definition_usage_count("Moooo") == 3);
        {
            UEDH edh3 = edm.make_element(eddm.make_definition_handle("Moooo"));
            assert(edh3.is_valid());
            assert(edh3.cget_handle().get_value() == 3);
            assert(edh3.cget_reference_count() == 1);
            assert(eddm.get_definition_usage_count("Moooo") == 4);

            UEDH edh4 = edm.make_element(eddm.make_definition_handle("Moooo"));
            assert(edh4.is_valid());
            assert(edh4.cget_handle().get_value() == 4);
            assert(edh4.cget_reference_count() == 1);
            assert(eddm.get_definition_usage_count("Moooo") == 5);


            UEDH edh2_copy{edh2};
            assert(edh2_copy.is_valid());
            assert(edh2 == edh2_copy);
            assert(edh2_copy.cget_handle().get_value() == 2);
            assert(edh2.cget_reference_count() == 2);
            assert(edh2_copy.cget_reference_count() == 2);
        }
        assert(eddm.get_definition_usage_count("Moooo") == 3);

        UEDH edh5 = edm.make_element(eddm.make_definition_handle("Moooo"));
        assert(edh5.is_valid());
        assert(edh5.cget_handle().get_value() == 5); // right now the handle is the next in the sequence rather than an old, revoked one
        assert(edh5.cget_reference_count() == 1);
        assert(eddm.get_definition_usage_count("Moooo") == 4);


        // destroy a usage of this type by assigning this handle to null
        eddh1 = Element_Data_Definition_Handle();
        assert(eddm.get_definition_usage_count("Moooo") == 3);

        edh5 = UEDH();
        assert(eddm.get_definition_usage_count("Moooo") == 2);

        edh2 = UEDH();
        assert(eddm.get_definition_usage_count("Moooo") == 1);

        edh1 = UEDH();
        assert(eddm.get_definition_usage_count("Moooo") == 0);
    }
    // Now for Attribute stuff

    {
        UEDH edh1 = edm.make_element(eddm.make_definition_handle("Moooo"));
        assert(edh1.cget_reference_count() == 1);

        auto adh0 = edh1.cget_attribute_at(0);
        assert(edh1.cget_reference_count() == 2);
        assert(adh0.is_valid());
        assert(adh0.cget_name() == "Default Bool");
        assert(adh0.cget_type() == TS_Bool()());
        assert(adh0.is_bool());

        {
            auto adh_bool0 = adh0.cget_bool();
            assert(edh1.cget_reference_count() == 3);
            assert(adh_bool0.is_valid());
            assert(adh_bool0.cget_name() == "Default Bool");
            assert(adh_bool0.cget_type() == TS_Bool()());
            assert(adh_bool0.cget_value() == false);
            assert(adh_bool0.can_set_value_to(true) == true);
            assert(adh_bool0.try_set_value(true) == true);

            assert(edm.cget_undo_count() == 1);
            assert(edh1.cget_reference_count() == 4);

            assert(adh_bool0.cget_value() == true);
            assert(adh_bool0.can_set_value_to(false) == true);
            assert(adh_bool0.try_set_value(false) == true);
            assert(adh_bool0.cget_value() == false);

            assert(edm.cget_undo_count() == 2);
            assert(edh1.cget_reference_count() == 5); // should be a ref in a command

            adh_bool0.set_value(true);
            assert(adh_bool0.cget_value() == true);

            assert(edm.cget_undo_count() == 3);
            assert(edh1.cget_reference_count() == 6); // should be a ref in a command
        }


        auto adh3 = edh1.cget_attribute_at(3);
        //assert(edh1.cget_reference_count() == 3);
        assert(adh3.is_valid());
        assert(adh3.cget_name() == "Constrained Int");
        assert(adh3.cget_type() == TS_Int()());
        assert(adh3.is_int());

        {
            auto adh3_int = adh3.cget_int();
            //assert(edh1.cget_reference_count() == 4);
            assert(adh3_int.is_valid());
            assert(adh3_int.cget_name() == "Constrained Int");
            assert(adh3_int.cget_type() == TS_Int()());

            assert(adh3_int.cget_value() == 5);
            assert(adh3_int.cget_lowest_value() == 0);
            assert(adh3_int.cget_highest_value() == 10);

            assert(adh3_int.can_set_value_to(1) == true);
            assert(adh3_int.try_set_value(1) == true);
            assert(adh3_int.cget_value() == 1);
            assert(adh3_int.can_set_value_to(-6) == false);
            assert(adh3_int.try_set_value(-6) == false);
            assert(adh3_int.cget_value() == 1);

            // hmmmmmmm
            adh3_int.set_value(-6);
            assert(adh3_int.cget_value() == -6);

            assert(adh3_int.try_set_value(2) == true);
            assert(adh3_int.cget_value() == 2);
        }
        //assert(edh1.cget_reference_count() == 3);
    }

    std::cout << "----------------------------" << std::endl;
}
