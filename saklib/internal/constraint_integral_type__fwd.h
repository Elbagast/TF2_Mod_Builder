#ifndef SAKLIB_INTERNAL_CONSTRAINT_INTEGRAL_TYPE__FWD_H
#define SAKLIB_INTERNAL_CONSTRAINT_INTEGRAL_TYPE__FWD_H

namespace saklib
{
    namespace internal
    {
        template <typename T>
        class Constraint_Integral_Type;

        using Constraint_Short = Constraint_Integral_Type<short>;
        using Constraint_UShort = Constraint_Integral_Type<unsigned short>;

        using Constraint_Int = Constraint_Integral_Type<int>;
        using Constraint_UInt = Constraint_Integral_Type<unsigned int>;

        using Constraint_Long = Constraint_Integral_Type<long>;
        using Constraint_ULong = Constraint_Integral_Type<unsigned long>;

        using Constraint_LLong = Constraint_Integral_Type<long long>;
        using Constraint_ULLong = Constraint_Integral_Type<unsigned long long>;

        template <typename T>
        class Constrained_Integral_Type;

        using Constrained_Short = Constrained_Integral_Type<short>;
        using Constrained_UShort = Constrained_Integral_Type<unsigned short>;

        using Constrained_Int = Constrained_Integral_Type<int>;
        using Constrained_UInt = Constrained_Integral_Type<unsigned int>;

        using Constrained_Long = Constrained_Integral_Type<long>;
        using Constrained_ULong = Constrained_Integral_Type<unsigned long>;

        using Constrained_LLong = Constrained_Integral_Type<long long>;
        using Constrained_ULLong = Constrained_Integral_Type<unsigned long long>;

    } // namespace internal
} // namespace saklib

#endif // SAKLIB_INTERNAL_CONSTRAINT_INTEGRAL_TYPE__FWD_H

