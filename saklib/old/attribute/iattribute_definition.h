#ifndef SAKLIB_IATTRIBUTE_DEFINITION_H
#define SAKLIB_IATTRIBUTE_DEFINITION_H

#include "iattribute_definition_base.h"
#include "iattribute_constraint.h"
#include "../types.h"
#include "../common_traits.h"

namespace saklib
{
    template <typename T>
    class IAttribute_Definition :
            public IAttribute_Definition_Base,
            public virtual IAttribute_Constraint_RW<T>
    {
    public:
        // Typedefs
        //============================================================
        COMMON_TRAITS_TYPEDEFS_T

        // Special 6
        //============================================================
        ~IAttribute_Definition() override = default;
    };
} // namespace saklib

#endif // SAKLIB_IATTRIBUTE_DEFINITION_H

