#include "attribute_data_int__test.h"

#include "attribute_data_int.h"

#include <iostream>
#include <cassert>

namespace saklib
{
    namespace internal
    {
        namespace
        {
            template <typename T>
            void assert__Attribute_Data_Definition_Integral_Type(Attribute_Data_Definition_Integral_Type<T> const& ar_constraint, T a_lowest, T a_highest, T a_initial, T a_good_value, T a_bad_value)
            {
                assert(ar_constraint.get_lowest_value() == a_lowest);
                assert(ar_constraint.get_highest_value() == a_highest);
                assert(ar_constraint.get_initial_value() == a_initial);
                assert(ar_constraint.can_set_value_to(a_good_value));
                assert(!ar_constraint.can_set_value_to(a_bad_value));
            }

            template <typename T>
            void internal_test()
            {
                Attribute_Data_Definition_Integral_Type<T> int_definition{"Test"};

                std::cout << int_definition << std::endl;

                int_definition.set_range(-100,100);
                assert__Attribute_Data_Definition_Integral_Type<T>(int_definition, -100, 100, 0, 14, 111);

                int_definition.set_range(-200,200,50);
                assert__Attribute_Data_Definition_Integral_Type<T>(int_definition, -200, 200, 50, -150, -250);

                int_definition.set_range(500,400,50);
                assert__Attribute_Data_Definition_Integral_Type<T>(int_definition, 400, 500, 400, 487, 333);

                int_definition.set_lowest_value(300);
                assert__Attribute_Data_Definition_Integral_Type<T>(int_definition, 300, 500, 400, 487, 1);


                int_definition.set_range(-100,100);

                // test initial set above, at and below lowest
                int_definition.set_initial_value(-99);
                assert__Attribute_Data_Definition_Integral_Type<T>(int_definition, -100, 100, -99, 55, -400);
                int_definition.set_initial_value(-100);
                assert__Attribute_Data_Definition_Integral_Type<T>(int_definition, -100, 100, -100, 3, -5000);
                int_definition.set_initial_value(-101);
                assert__Attribute_Data_Definition_Integral_Type<T>(int_definition, -100, 100, -100, -80, 50456);

                int_definition.set_range(100,-100);

                // test initial set below, at and above highest
                int_definition.set_initial_value(99);
                assert__Attribute_Data_Definition_Integral_Type<T>(int_definition, -100, 100, 99, 55, -400);
                int_definition.set_initial_value(100);
                assert__Attribute_Data_Definition_Integral_Type<T>(int_definition, -100, 100, 100, 3, -5000);
                int_definition.set_initial_value(101);
                assert__Attribute_Data_Definition_Integral_Type<T>(int_definition, -100, 100, 100, -80, 50456);

                int_definition.set_range(100,-100);

                // test lowest set above, at and below initial
                int_definition.set_lowest_value(1);
                assert__Attribute_Data_Definition_Integral_Type<T>(int_definition, 0, 100, 0, 55, -400);
                int_definition.set_lowest_value(0);
                assert__Attribute_Data_Definition_Integral_Type<T>(int_definition, 0, 100, 0, 3, -5000);
                int_definition.set_lowest_value(-1);
                assert__Attribute_Data_Definition_Integral_Type<T>(int_definition, -1, 100, 0, -1, 50456);


                int_definition.set_range(100,-100);

                // test highest set above, at and below initial
                int_definition.set_highest_value(1);
                assert__Attribute_Data_Definition_Integral_Type<T>(int_definition, -100, 1, 0, -5, -400);
                int_definition.set_highest_value(0);
                assert__Attribute_Data_Definition_Integral_Type<T>(int_definition, -100, 0, 0, -10, -5000);
                int_definition.set_highest_value(-1);
                assert__Attribute_Data_Definition_Integral_Type<T>(int_definition, -100, 0, 0, -1, 50456);

                // test set to only one value
                int_definition.set_to_only_value(123456);
                assert__Attribute_Data_Definition_Integral_Type<T>(int_definition, 123456, 123456, 123456, 123456, 234);


                // test set to default
                int_definition.set_to_default();
                assert(int_definition.get_lowest_value() == int_definition.default_lowest_value());
                assert(int_definition.get_highest_value() == int_definition.default_highest_value());
                assert(int_definition.get_initial_value() == int_definition.default_initial_value());
                assert(int_definition.can_set_value_to(136453));
            }
        }
    }
}

void saklib::internal::test_constraint_integral_type()
{
    std::cout << "test_Attribute_Data_Definition_Integral_Type()" << std::endl;

    // should fail to compile with link error
    //Attribute_Data_Definition_Integral_Type<double> double_constraint{};

    internal_test<int>();
    internal_test<long>();
    internal_test<long long>();


    std::cout << "----------------------------" << std::endl;
}
