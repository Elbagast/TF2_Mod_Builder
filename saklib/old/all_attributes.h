#ifndef ALL_ATTRIBUTES_H
#define ALL_ATTRIBUTES_H
/*
Header to inlcude when using attributes
====================================================================================================
This file includes all of the attribute templates and the Common_Traits, and defines the switch functions
for simple Attribute creation.
*/
#include "types.h"
#include "attribute.h"
#include "attribute_type.h"
#include "common_traits.h"

namespace saklib
{
    std::unique_ptr<Attribute> make_Attribute(std::shared_ptr<Attribute_Definition> const& definition);

    Type_Enum attribute_TypeString_to_Type_Enum(String const& typeString);

    String attribute_Type_Enum_to_TypeString(Type_Enum type);

} // namespace saklib

#endif // ALL_ATTRIBUTES_H
