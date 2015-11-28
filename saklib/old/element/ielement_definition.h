#ifndef SAKLIB_IELEMENT_DEFINITION_H
#define SAKLIB_IELEMENT_DEFINITION_H

#include "../object/iobject_type.h"
#include "../object/iobject_name.h"
#include "../object/iobject_pointer_storage.h"
#include "ielement_maker.h"

namespace saklib
{
    class IAttribute_Definition_Base;
    /*
    IElement_Definition
    ====================================================================================================
    */
    class IElement_Definition :
            public virtual IObject_Type_RW,
            public virtual IObject_Pointer_Storage_RW<IAttribute_Definition_Base>,
            public virtual IElement_Maker
    {
    public:
        // Special 6
        //============================================================
        ~IElement_Definition() override = default;
    };
} // namespace saklib

#endif // SAKLIB_IELEMENT_DEFINITION_H

