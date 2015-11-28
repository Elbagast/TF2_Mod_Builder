#ifndef SAKLIB_INTERNAL_CONSTRAINT_BOOLEAN_TYPE__FWD_H
#define SAKLIB_INTERNAL_CONSTRAINT_BOOLEAN_TYPE__FWD_H

namespace saklib
{
    namespace internal
    {
        template <typename T>
        class Constraint_Boolean_Type;

        using Constraint_Bool = Constraint_Boolean_Type<bool>;

        template <typename T>
        class Constrained_Boolean_Type;

        using Constrained_Bool = Constrained_Boolean_Type<bool>;

    } // namespace internal
} // namespace saklib

#endif // SAKLIB_INTERNAL_CONSTRAINT_BOOLEAN_TYPE__FWD_H

