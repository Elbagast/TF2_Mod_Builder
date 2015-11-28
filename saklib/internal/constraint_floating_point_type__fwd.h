#ifndef SAKLIB_INTERNAL_CONSTRAINT_FLOATING_POINT_TYPE__FWD_H
#define SAKLIB_INTERNAL_CONSTRAINT_FLOATING_POINT_TYPE__FWD_H

namespace saklib
{
    namespace internal
    {
        template <typename T>
        class Constraint_Floating_Point_Type;

        using Constraint_Float = Constraint_Floating_Point_Type<float>;
        using Constraint_Double = Constraint_Floating_Point_Type<double>;
        using Constraint_LDouble = Constraint_Floating_Point_Type<long double>;

        template <typename T>
        class Constrained_Floating_Point_Type;

        using Constrained_Float = Constrained_Floating_Point_Type<float>;
        using Constrained_Double = Constraint_Floating_Point_Type<double>;
        using Constrained_LDouble = Constrained_Floating_Point_Type<long double>;
    } // namespace internal
} // namespace saklib

#endif // SAKLIB_INTERNAL_CONSTRAINT_FLOATING_POINT_TYPE__FWD_H

