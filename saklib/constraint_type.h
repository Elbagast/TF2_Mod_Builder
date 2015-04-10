#ifndef CONSTRAINT_TYPE_H
#define CONSTRAINT_TYPE_H

#include "types.h"
#include "all_type_traits.h"

namespace Saklib
{
    /*
    Constraint_Type<T>
    ====================================================================================================
    In order to create a constraint for a given type, specialise this template. The interface of a
    constraint could be anything.

    Using this template means that only one type of constraint can exist per data type (for now) and
    ensures constraints don't exist for types until implemented.

    */
    template <typename T>
    class Constraint_Type
    {
    public:
        // Special 6
        //============================================================
        Constraint_Type() = delete;
        ~Constraint_Type() = delete;

        Constraint_Type(Constraint_Type const& other) = delete;
        Constraint_Type& operator=(Constraint_Type const& other) = delete;

        Constraint_Type(Constraint_Type && other) = delete;
        Constraint_Type& operator=(Constraint_Type && other) = delete;
    };

    // Determine of a type can be constrained by checking if the Constraint_Type<T> destructor is implemented.
    //template <typename T>
    //constexpr
    //bool is_constrainable();

} // namespace Saklib

#endif // CONSTRAINT_TYPE_H
