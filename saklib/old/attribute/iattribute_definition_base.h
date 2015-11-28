#ifndef SAKLIB_IATTRIBUTE_DEFINITION_BASE_H
#define SAKLIB_IATTRIBUTE_DEFINITION_BASE_H

#include "../object/iobject_name.h"
#include "iattribute_typeid.h"
#include "iattribute_maker.h"

namespace saklib
{
    /*
    IAttribute_Base
    ====================================================================================================
    The base interface for Attribute objects that will be stored as IAttribute pointers.
    */
    class IAttribute_Definition_Base :
            public virtual IObject_Name_RW,
            public virtual IAttribute_Typeid,
            public virtual IAttribute_Maker
    {
    public:
        ~IAttribute_Definition_Base() override = default;
    };
} // namespace saklib

#endif // SAKLIB_IATTRIBUTE_DEFINITION_BASE_H

