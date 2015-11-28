#include "element_test.h"
#include <string>
#include <iostream>

#include "element.h"
#include "element_definition.h"
#include "../attribute/attribute.h"
#include "../attribute/attribute_definition.h"

template <typename T>
using up = std::unique_ptr<T>;

void saklib::element_test()
{
    std::cout << "Split up Element test" << std::endl << std::endl;

    up<IElement_Definition> edef0{ new Element_Definition()};

    IElement_Definition& r_edef0 = *(edef0.get());

    r_edef0.set_type("Poop");

    {
        // scope to expire destruct pointers
        up<IAttribute_Definition_Base> adef0{ new Attribute_Definition<Int>("First Attribute Int") };
        up<IAttribute_Definition_Base> adef1{ new Attribute_Definition<String>("Second Attribute String") };
        r_edef0.push_back(adef0);
        r_edef0.push_back(adef1);
    }

    std::cout << "Element Definition:" << std::endl;
    std::cout << "-------------------" << std::endl;
    std::cout << "Type = \"" << r_edef0.type() << "\"" << std::endl;
    std::cout << "Size = \"" << r_edef0.size() << "\"" << std::endl;

    for (size_type index = 0, end = r_edef0.size(); index != end; ++index)
    {
        std::cout << "Attribute Definition " << index
                  << " name=\"" << r_edef0.at(index)->name()
                  << "\" type=\"" << r_edef0.at(index)->type_string()
                  << std::endl;
    }
    std::cout << std::endl;

    up<IElement> element0{ r_edef0.make_element("Some Element") };
    IElement& r_element0 = *(element0.get());

    std::cout << "Element:" << std::endl;
    std::cout << "-------------------" << std::endl;
    std::cout << "Type = \"" << r_element0.type() << "\"" << std::endl;
    std::cout << "Size = \"" << r_element0.size() << "\"" << std::endl;
    std::cout << "Name = \"" << r_element0.name() << "\"" << std::endl;

    for (size_type index = 0, end = r_element0.size(); index != end; ++index)
    {
        std::cout << "Attribute " << index
                  << " name=\"" << r_element0.at(index)->name()
                  << "\" type=\"" << r_element0.at(index)->type_string();
        if (r_element0.at(index)->type() == Type_Enum::Int)
        {
            auto true_ptr = static_cast<IAttribute<Int>*>(r_element0.at(index));
            std::cout << "\" value=\"" << true_ptr->value();
        }
        else if (r_element0.at(index)->type() == Type_Enum::String)
        {
            auto true_ptr = static_cast<IAttribute<String>*>(r_element0.at(index));
            std::cout << "\" value=\"" << true_ptr->value();
        }

        std::cout << "\"" << std::endl;
    }
    std::cout << std::endl;



    std::cout << "----------------------------------------" << std::endl;
}
