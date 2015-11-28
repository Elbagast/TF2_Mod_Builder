#ifndef CONSTRAINT_PATH_H
#define CONSTRAINT_PATH_H

#include "constraint.h"

namespace saklib
{
    /*
    Constraint<Path>
    ====================================================================================================

    */
    template <>
    class Constraint<Path>
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


#endif // CONSTRAINT_PATH_H
