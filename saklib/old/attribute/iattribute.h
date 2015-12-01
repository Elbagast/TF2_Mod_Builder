#ifndef SAKLIB_IATTRIBUTE_H
#define SAKLIB_IATTRIBUTE_H

#include "iattribute_base.h"
#include "iattribute_value.h"
#include "iattribute_constraint.h"
#include "../types.h"
#include "../common_traits.h"

namespace saklib
{
    template <typename T>
    class IAttribute :
            public IAttribute_Base,
            public virtual IAttribute_Constraint_R<T>,
            public virtual IAttribute_Value_RW<T>
    {
    public:
        // Typedefs
        //============================================================
        COMMON_TRAITS_TYPEDEFS_T

        // Special 6
        //============================================================
        ~IAttribute() override = default;
    };
} // namespace saklib

#endif // SAKLIB_IATTRIBUTE_H

