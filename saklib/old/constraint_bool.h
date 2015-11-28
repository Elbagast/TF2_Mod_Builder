#ifndef CONSTRAINT_BOOL_H
#define CONSTRAINT_BOOL_H

#include "constraint.h"

namespace saklib
{
    /*
    Constraint<Bool>
    ====================================================================================================

    */
    template <>
    class Constraint<Bool>
    {
    public:
        // Special 6
        //============================================================
        Constraint() = default;
        ~Constraint() = default;

        Constraint(Constraint const& other) = default;
        Constraint& operator=(Constraint const& other) = default;

        //Constraint(Constraint && other) = default;
        //Constraint& operator=(Constraint && other) = default;
    };
} // namespace saklib


#endif // CONSTRAINT_BOOL_H
