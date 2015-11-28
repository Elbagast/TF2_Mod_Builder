#ifndef SAKLIB_ELEMENT_H
#define SAKLIB_ELEMENT_H

#include "ielement.h"
#include "../object/object_name.h"
#include "../object/object_type.h"
#include "../object/object_pointer_storage.h"

namespace saklib
{
    /*
    Element
    ====================================================================================================
    */
    class Element :
            public IElement,
            public remote::Object_Type_R,
            public local::Object_Name_RW,
            public local::Object_Pointer_Storage_R<IAttribute_Base>
    {
        // Typedefs
        //============================================================
        using stored_type = IObject_Pointer_Storage_R<IAttribute_Base>::stored_type;
        using storage_type = IObject_Pointer_Storage_R<IAttribute_Base>::storage_type;
    public:
        // Special 6
        //============================================================
        Element(IObject_Type_R const& ar_type, String const& a_name, storage_type& a_attributes):
            IElement(),
            remote::Object_Type_R(ar_type),
            local::Object_Name_RW(a_name),
            local::Object_Pointer_Storage_R<IAttribute_Base>(a_attributes)
        {}
        Element(IObject_Type_R const& ar_type, String const& a_name, storage_type&& a_attributes):
            IElement(),
            remote::Object_Type_R(ar_type),
            local::Object_Name_RW(a_name),
            local::Object_Pointer_Storage_R<IAttribute_Base>(std::forward<storage_type>(a_attributes))
        {}
        ~Element() override = default;
    };


} // namespace saklib

#endif // SAKLIB_ELEMENT_H
