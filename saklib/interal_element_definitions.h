#ifndef INTERAL_ELEMENT_DEFINITIONS_H
#define INTERAL_ELEMENT_DEFINITIONS_H

#include "element_definition.h"

namespace Saklib
{
    // Static Helpers
    //============================================================
    // Define Element configurations for use

    Element_Definition internal_definition_of_Project();
    Element_Definition internal_definition_of_File();

    Element_Definition internal_definition_of_SingleInt();

    void register_all_internal_definitions();
} // namespace Saklib

#endif // INTERAL_ELEMENT_DEFINITIONS_H
