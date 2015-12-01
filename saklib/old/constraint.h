#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include "types.h"
#include "common_traits.h"

namespace saklib
{
    /*
    Constraint<T>
    ====================================================================================================
    In order to create a constraint for a given type, specialise this template. The interface of a
    constraint could be anything.

    Using this template means that only one type of constraint can exist per data type (for now) and
    ensures constraints don't exist for types until implemented.

    */
    template <typename T>
    class Constraint
    {
    public:
        // Special 6
        //============================================================
        Constraint() = delete;
        ~Constraint() = delete;

        Constraint(Constraint const& other) = delete;
        Constraint& operator=(Constraint const& other) = delete;

        Constraint(Constraint && other) = delete;
        Constraint& operator=(Constraint && other) = delete;
    };

    // Determine of a type can be constrained by checking if the Constraint<T> destructor is implemented.
    //template <typename T>
    //constexpr
    //bool is_constrainable();

} // namespace saklib

#endif // CONSTRAINT_H
