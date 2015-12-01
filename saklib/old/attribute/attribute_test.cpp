#include "attribute_test.h"
#include <string>
#include <iostream>


#include "attribute_definition.h"
#include "attribute.h"

void saklib::attribute_test()
{
    std::cout << "Split up Attribute test" << std::endl << std::endl;

    Attribute_Definition<int> att_int_def{"Some Name"};

    std::unique_ptr<IAttribute_Base> att_int_1 = att_int_def.make_attribute();

    IAttribute_Base& att_int_1_base = *(att_int_1.get());
    IAttribute<int>& att_int_1_full = static_cast<IAttribute<int>&>(att_int_1_base);

    std::cout << "name=\"" << att_int_1_base.name()
              << "\" type=\"" << att_int_1_base.type_string()
              << "\" value=\"" << att_int_1_full.value()

              << "\" inital=\"" << att_int_1_full.initial_value()
              << "\" lowest=\"" << att_int_1_full.lowest_value()
              << "\" highest=\"" << att_int_1_full.highest_value()

              << "\"" << std::endl;

    att_int_1_full.set_value(5);
    std::cout << "name=\"" << att_int_1_base.name()
              << "\" type=\"" << att_int_1_base.type_string()
              << "\" value=\"" << att_int_1_full.value()

              << "\" inital=\"" << att_int_1_full.initial_value()
              << "\" lowest=\"" << att_int_1_full.lowest_value()
              << "\" highest=\"" << att_int_1_full.highest_value()

              << "\"" << std::endl;

    att_int_def.set_name("moooo");
    att_int_def.set_lowest_value(15);
    att_int_def.set_initial_value(4);
    att_int_def.set_highest_value(101254);
    std::cout << "name=\"" << att_int_1_base.name()
              << "\" type=\"" << att_int_1_base.type_string()
              << "\" value=\"" << att_int_1_full.value()

              << "\" inital=\"" << att_int_1_full.initial_value()
              << "\" lowest=\"" << att_int_1_full.lowest_value()
              << "\" highest=\"" << att_int_1_full.highest_value()

              << "\"" << std::endl;

    Attribute_Definition<double> att_double_def{"Argleblargle"};

    std::unique_ptr<IAttribute_Base> att_double_1 = att_double_def.make_attribute();

    IAttribute_Base& att_double_1_base = *(att_double_1.get());
    IAttribute<double>& att_double_1_full = static_cast<IAttribute<double>&>(att_double_1_base);

    std::cout << "name=\"" << att_double_1_base.name()
              << "\" type=\"" << att_double_1_base.type_string()
              << "\" value=\"" << att_double_1_full.value()

              << "\" inital=\"" << att_double_1_full.initial_value()
              << "\" lowest=\"" << att_double_1_full.lowest_value()
              << "\" highest=\"" << att_double_1_full.highest_value()
              << "\" dp=\"" << att_double_1_full.decimal_places()

              << "\"" << std::endl;

    att_double_1_full.set_value(1354.546);
    std::cout << "name=\"" << att_double_1_base.name()
              << "\" type=\"" << att_double_1_base.type_string()
              << "\" value=\"" << att_double_1_full.value()

              << "\" inital=\"" << att_double_1_full.initial_value()
              << "\" lowest=\"" << att_double_1_full.lowest_value()
              << "\" highest=\"" << att_double_1_full.highest_value()
              << "\" dp=\"" << att_double_1_full.decimal_places()

              << "\"" << std::endl;


    std::cout << "----------------------------------------" << std::endl;
}
