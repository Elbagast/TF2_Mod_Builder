#include "attribute__test.h"

#include "attribute.h"

#include "type_string.h"

#include <iostream>
#include <cassert>


void saklib::internal::test_attribute()
{
    std::cout << "test_attribute()" << std::endl;

    Attribute_Definition def_bool1{"First Bool", TS_Bool()};
    std::cout << def_bool1 << std::endl;

    Attribute att_bool1{def_bool1};
    std::cout << att_bool1 << std::endl;

    Attribute_Definition def_int1{"First Int", TS_Int()};
    std::cout << def_int1 << std::endl;

    Attribute att_int1{def_int1};
    std::cout << att_int1 << std::endl;

    Attribute_Definition def_int2{"Second Int", TS_Int(), 0,10,5};
    std::cout << def_int2 << std::endl;

    Attribute att_int2{def_int2};
    std::cout << att_int2 << std::endl;

    std::cout << "----------------------------" << std::endl;
}
