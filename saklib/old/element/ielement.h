#ifndef SAKLIB_IELEMENT_H
#define SAKLIB_IELEMENT_H

#include "../object/iobject_type.h"
#include "../object/iobject_name.h"
#include "../object/iobject_pointer_storage.h"

namespace saklib
{
    class IAttribute_Base;
    /*
    IElement
    ====================================================================================================
    Interface class for access to Elements regardless of how or where they're implemented.
    */
    class IElement :
            public virtual IObject_Type_R,
            public virtual IObject_Name_RW,
            public virtual IObject_Pointer_Storage_R<IAttribute_Base>
    {
    public:
        // Special 6
        //============================================================
        ~IElement() override = default;

    };
} // namespace saklib


#endif // SAKLIB_IELEMENT_H


