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

    using UEDM = Undoable_Element_Data_Manager;
    using UEDH = Undoable_Element_Data_Handle;
    using UADH = Undoable_Attribute_Data_Handle;

    using UADH_Bool = Undoable_Attribute_Data_Handle_Bool;
    using UADH_Int = Undoable_Attribute_Data_Handle_Int;

    UEDM uedm{};

    UEDH uedh1 = uedm.make_element(eddm.make_definition_handle("Moooo"));

    assert(uedh1.is_valid());
    assert(uedh1.cget_handle().get_value() == 1);
    assert(uedh1.cget_reference_count() == 1);
    assert(uedh1.cget_type() == "Moooo");
    assert(uedh1.cget_attribute_count() == 4);

    assert(uedm.can_undo() == false);
    assert(uedm.can_redo() == false);
    assert(uedm.cget_command_count() == 0);

    UADH uadh = uedh1.cget_attribute_at(2);
    assert(uadh.is_valid());
    assert(uadh.is_int());

    UADH_Int uedh_int1 = uadh.cget_int();
    assert(uedh_int1.is_valid());
    uedh_int1.set_value(123);
    assert(uedm.can_undo() == true);
    assert(uedm.can_redo() == false);
    assert(uedm.cget_command_count() == 1);
    assert(uedm.cget_undo_count() == 1);
    assert(uedm.cget_redo_count() == 0);
    assert(uedh_int1.cget_value() == 123);

    uedm.undo();
    assert(uedm.can_undo() == false);
    assert(uedm.can_redo() == true);
    assert(uedm.cget_command_count() == 1);
    assert(uedm.cget_undo_count() == 0);
    assert(uedm.cget_redo_count() == 1);
    assert(uedh_int1.cget_value() == 0);

    uedm.redo();
    assert(uedm.can_undo() == true);
    assert(uedm.can_redo() == false);
    assert(uedm.cget_command_count() == 1);
    assert(uedm.cget_undo_count() == 1);
    assert(uedm.cget_redo_count() == 0);
    assert(uedh_int1.cget_value() == 123);

    uedh_int1.set_value(123);
    assert(uedm.can_undo() == true);
    assert(uedm.can_redo() == false);
    assert(uedm.cget_command_count() == 1);
    assert(uedm.cget_undo_count() == 1);
    assert(uedm.cget_redo_count() == 0);
    assert(uedh_int1.cget_value() == 123);

    uedh_int1.set_value(456);
    assert(uedm.can_undo() == true);
    assert(uedm.can_redo() == false);
    assert(uedm.cget_command_count() == 2);
    assert(uedm.cget_undo_count() == 2);
    assert(uedm.cget_redo_count() == 0);
    assert(uedh_int1.cget_value() == 456);

    uedm.undo();
    assert(uedm.can_undo() == true);
    assert(uedm.can_redo() == true);
    assert(uedm.cget_command_count() == 2);
    assert(uedm.cget_undo_count() == 1);
    assert(uedm.cget_redo_count() == 1);
    assert(uedh_int1.cget_value() == 123);

    uedm.undo();
    assert(uedm.can_undo() == false);
    assert(uedm.can_redo() == true);
    assert(uedm.cget_command_count() == 2);
    assert(uedm.cget_undo_count() == 0);
    assert(uedm.cget_redo_count() == 2);
    assert(uedh_int1.cget_value() == 0);

    uedm.redo();
    assert(uedm.can_undo() == true);
    assert(uedm.can_redo() == true);
    assert(uedm.cget_command_count() == 2);
    assert(uedm.cget_undo_count() == 1);
    assert(uedm.cget_redo_count() == 1);
    assert(uedh_int1.cget_value() == 123);

    uedm.redo();
    assert(uedm.can_undo() == true);
    assert(uedm.can_redo() == false);
    assert(uedm.cget_command_count() == 2);
    assert(uedm.cget_undo_count() == 2);
    assert(uedm.cget_redo_count() == 0);
    assert(uedh_int1.cget_value() == 456);

    uedm.clear();
    assert(uedm.can_undo() == false);
    assert(uedm.can_redo() == false);
    assert(uedm.cget_command_count() == 0);
    assert(uedm.cget_undo_count() == 0);
    assert(uedm.cget_redo_count() == 0);
    assert(uedh_int1.cget_value() == 456);



    std::cout << "----------------------------" << std::endl;
}
