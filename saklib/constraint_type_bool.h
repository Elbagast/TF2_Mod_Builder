#ifndef CONSTRAINT_TYPE_BOOL_H
#define CONSTRAINT_TYPE_BOOL_H

#include "constraint_type.h"

namespace Saklib
{
    /*
    Constraint_Type<Bool>
    ====================================================================================================

    */
    template <>
    class Constraint_Type<Bool>
    {
    public:
        // Special 6
        //============================================================
        Constraint_Type() = default;
        ~Constraint_Type() = default;

        Constraint_Type(Constraint_Type const& other) = default;
        Constraint_Type& operator=(Constraint_Type const& other) = default;

        //Constraint_Type(Constraint_Type && other) = default;
        //Constraint_Type& operator=(Constraint_Type && other) = default;
    };
} // namespace Saklib


#endif // CONSTRAINT_TYPE_BOOL_H
