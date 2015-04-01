#include "interal_element_definitions.h"
#include "element.h"

// Static Helpers
//============================================================
// Define the Element type needed by this Class
Saklib::Element_Definition Saklib::internal_definition_of_Project()
{
    return Element_Definition("Project", true,
    {
        make_shared_Attribute_Definition("Filepath", Type_Enum::Path),
        make_shared_Attribute_Definition("TestBool", Type_Enum::Bool),
        make_shared_Attribute_Definition("TestInt", Type_Enum::Int),
        make_shared_Attribute_Definition("TestDouble", Type_Enum::Double),
        make_shared_Attribute_Definition("TestString", Type_Enum::String),
        make_shared_Attribute_Definition("TestElement", Type_Enum::ElementID),
        make_shared_Attribute_Definition("TestElement2", Type_Enum::ElementID),

        make_shared_Attribute_Definition("TestVectorBool", Type_Enum::Vector_Bool),
        make_shared_Attribute_Definition("TestVectorInt", Type_Enum::Vector_Int),
        make_shared_Attribute_Definition("TestVectorDouble", Type_Enum::Vector_Double),
        make_shared_Attribute_Definition("TestVectorString", Type_Enum::Vector_String),
        make_shared_Attribute_Definition("TestVectorPath", Type_Enum::Vector_Path),
        make_shared_Attribute_Definition("TestVectorElementID", Type_Enum::Vector_ElementID),
    });
}

Saklib::Element_Definition Saklib::internal_definition_of_File()
{
    return Element_Definition("File", false,
    {
        make_shared_Attribute_Definition("Source", Type_Enum::Path),
        make_shared_Attribute_Definition("Target", Type_Enum::Path),
    });
}

Saklib::Element_Definition Saklib::internal_definition_of_SingleInt()
{
    return Element_Definition("SingleInt", false,
    {
        make_shared_Attribute_Definition("Data", Type_Enum::Int),
    });
}

void Saklib::register_all_internal_definitions()
{
    Element::try_add_definition(internal_definition_of_Project());
    Element::try_add_definition(internal_definition_of_File());
    Element::try_add_definition(internal_definition_of_SingleInt());
}
