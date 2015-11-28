#ifndef SAKLIB_IATTRIBUTE_BASE_H
#define SAKLIB_IATTRIBUTE_BASE_H

#include "../object/iobject_name.h"
#include "iattribute_typeid.h"

namespace saklib
{
    /*
    IAttribute_Base
    ====================================================================================================
    The base interface for Attribute objects that will be stored as IAttribute pointers.
    */
    class IAttribute_Base :
            public virtual IObject_Name_R,
            public virtual IAttribute_Typeid
    {
    public:
        ~IAttribute_Base() override = default;
    };
} // namespace saklib

#endif //SAKLIB_ IATTRIBUTE_BASE_H

