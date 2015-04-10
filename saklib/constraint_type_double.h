#ifndef CONSTRAINT_TYPE_DOUBLE_H
#define CONSTRAINT_TYPE_DOUBLE_H

#include "constraint_type.h"

namespace Saklib
{
    /*
    Constraint_Type<Double>
    ====================================================================================================

    */
    template <>
    class Constraint_Type<Double>
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

#endif // CONSTRAINT_TYPE_DOUBLE_H
