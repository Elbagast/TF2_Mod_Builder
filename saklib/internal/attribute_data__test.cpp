#include "attribute_data__test.h"

#include "attribute_data.h"

#include "type_string.h"

#include <iostream>
#include <cassert>


void saklib::internal::test_attribute()
{
    std::cout << "test_attribute()" << std::endl;

    Attribute_Data_Definition def_bool1{"First Bool", Type_Bool()};
    std::cout << def_bool1 << std::endl;

    Attribute_Data att_bool1{def_bool1};
    std::cout << att_bool1 << std::endl;

    Attribute_Data_Definition def_int1{"First Int", Type_Int()};
    std::cout << def_int1 << std::endl;

    Attribute_Data att_int1{def_int1};
    std::cout << att_int1 << std::endl;

    Attribute_Data_Definition def_int2{"Second Int", Type_Int(), 0,10,5};
    std::cout << def_int2 << std::endl;

    Attribute_Data att_int2{def_int2};
    std::cout << att_int2 << std::endl;

    std::cout << "----------------------------" << std::endl;
}
