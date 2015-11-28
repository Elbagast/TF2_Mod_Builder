#ifndef INTERNAL_ELEMENT_DEFINITIONS_H
#define INTERNAL_ELEMENT_DEFINITIONS_H

#include "element_definition.h"

namespace saklib
{
    // Static Helpers
    //============================================================
    // Define Element configurations for use

    Element_Definition internal_definition_of_Project();
    Element_Definition internal_definition_of_File();

    Element_Definition internal_definition_of_SingleInt();
    Element_Definition internal_definition_of_Build();
} // namespace saklib

#endif // INTERNAL_ELEMENT_DEFINITIONS_H
