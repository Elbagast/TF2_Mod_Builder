#include "attribute_data_boolean_type__test.h"

#include "attribute_data_boolean_type.h"

#include <iostream>
#include <cassert>

namespace saklib
{
    namespace internal
    {
        namespace
        {
            template <typename T>
            void assert__Attribute_Data_Definition_Boolean_Type(Attribute_Data_Definition_Boolean_Type<T> const& ar_constraint, T a_initial)
            {
                assert(ar_constraint.get_initial_value() == a_initial);
                assert(ar_constraint.can_set_value_to(true));
                assert(ar_constraint.can_set_value_to(false));
            }
        }
    }
}

void saklib::internal::test_constraint_boolean_type()
{
    std::cout << "test_Attribute_Data_Definition_Bool" << std::endl;

    // should fail to compile with link error
    //Attribute_Data_Definition_Boolean_Type<int> int_constraint{};

    Attribute_Data_Definition_Bool bool_constraint{"stuff"};

    std::cout << bool_constraint << std::endl;

    assert__Attribute_Data_Definition_Boolean_Type(bool_constraint, false);

    bool_constraint.set_initial_value(true);
    std::cout << bool_constraint << std::endl;
    assert__Attribute_Data_Definition_Boolean_Type(bool_constraint, true);

    std::cout << "----------------------------" << std::endl;
}

void saklib::internal::test_constrained_boolean_type()
{
    std::cout << "test_Attribute_Data_Bool" << std::endl;

    // should fail to compile with link error
    //Attribute_Data_Definition_Boolean_Type<int> int_constraint{};
    {
        Attribute_Data_Definition_Bool bool_constraint{"stuff"};
        Attribute_Data_Bool bool_value{bool_constraint};

        std::cout << bool_constraint << std::endl;
        std::cout << bool_value << std::endl;

        assert(bool_value.cget_value() == false);
        assert(bool_value.can_set_value_to(true));
        assert(!bool_value.can_set_value_to(false));

        if (bool_value.try_set_value(true))
            std::cout << "value changed" << std::endl;
        else
            std::cout << "no change" << std::endl;
        std::cout << bool_value << std::endl;

        assert(bool_value.cget_value() == true);
        assert(bool_value.can_set_value_to(false));
        assert(!bool_value.can_set_value_to(true));

        if (bool_value.try_set_value(true))
            std::cout << "value changed" << std::endl;
        else
            std::cout << "no change" << std::endl;
        std::cout << bool_value << std::endl;

        if (bool_value.try_set_value(false))
            std::cout << "value changed" << std::endl;
        else
            std::cout << "no change" << std::endl;
        assert(bool_value.cget_value() == false);
        assert(bool_value.can_set_value_to(true));
        assert(!bool_value.can_set_value_to(false));

        std::cout << bool_value << std::endl;
    }

    {
        // again but with non-default constraint
        Attribute_Data_Definition_Bool bool_constraint{"stuff", true};
        Attribute_Data_Bool bool_value{bool_constraint};

        std::cout << bool_constraint << std::endl;
        std::cout << bool_value << std::endl;

        assert(bool_value.cget_value() == true);
        assert(bool_value.can_set_value_to(false));
        assert(!bool_value.can_set_value_to(true));

        if (bool_value.try_set_value(false))
            std::cout << "value changed" << std::endl;
        else
            std::cout << "no change" << std::endl;
        std::cout << bool_value << std::endl;

        assert(bool_value.cget_value() == false);
        assert(bool_value.can_set_value_to(true));
        assert(!bool_value.can_set_value_to(false));

        if (bool_value.try_set_value(false))
            std::cout << "value changed" << std::endl;
        else
            std::cout << "no change" << std::endl;
        std::cout << bool_value << std::endl;

        if (bool_value.try_set_value(true))
            std::cout << "value changed" << std::endl;
        else
            std::cout << "no change" << std::endl;
        assert(bool_value.cget_value() == true);
        assert(bool_value.can_set_value_to(false));
        assert(!bool_value.can_set_value_to(true));

        std::cout << bool_value << std::endl;
    }

    std::cout << "----------------------------" << std::endl;
}
