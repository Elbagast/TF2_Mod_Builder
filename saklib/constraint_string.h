#ifndef CONSTRAINT_STRING_H
#define CONSTRAINT_STRING_H

#include "constraint.h"

namespace Saklib
{
    /*
    Constraint<String>
    ====================================================================================================

    */
    template <>
    class Constraint<String>
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
} // namespace Saklib



#endif // CONSTRAINT_STRING_H
