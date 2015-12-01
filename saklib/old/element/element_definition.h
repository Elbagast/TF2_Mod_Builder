#ifndef SAKLIB_ELEMENT_DEFINITION_H
#define SAKLIB_ELEMENT_DEFINITION_H

#include "ielement_definition.h"
#include "../object/object_name.h"
#include "../object/object_type.h"
#include "../object/object_pointer_storage.h"
#include "element_maker.h"

namespace saklib
{
    /*
    Element_Definition
    ====================================================================================================
    */
    class Element_Definition :
            public IElement_Definition,
            public local::Object_Type_RW,
            public local::Object_Name_RW,
            public local::Object_Pointer_Storage_RW<IAttribute_Definition_Base>,
            public local::Element_Maker
    {
        // Typedefs
        //============================================================
        using stored_type = IObject_Pointer_Storage_R<IAttribute_Definition_Base>::stored_type;
        using storage_type = IObject_Pointer_Storage_R<IAttribute_Definition_Base>::storage_type;
    public:
        // Special 6
        //============================================================
        Element_Definition():
            IElement_Definition(),
            local::Object_Type_RW(),
            local::Object_Name_RW(),
            local::Object_Pointer_Storage_RW<IAttribute_Definition_Base>(),
            local::Element_Maker(*this, *this)
        {}

        Element_Definition(String const& a_type, String const& a_name):
            IElement_Definition(),
            local::Object_Type_RW(a_type),
            local::Object_Name_RW(a_name),
            local::Object_Pointer_Storage_RW<IAttribute_Definition_Base>(),
            local::Element_Maker(*this, *this)
        {}
        ~Element_Definition() override = default;
    };


} // namespace saklib
#endif // SAKLIB_ELEMENT_DEFINITION_H

