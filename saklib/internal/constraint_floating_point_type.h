#ifndef SAKLIB_INTERNAL_CONSTRAINT_FLOATING_POINT_TYPE_H
#define SAKLIB_INTERNAL_CONSTRAINT_FLOATING_POINT_TYPE_H

#ifndef SAKLIB_INTERNAL_CONSTRAINT_FLOATING_POINT_TYPE__FWD_H
#include "constraint_floating_point_type__fwd.h"
#endif

#ifndef INCLUDE_STD_TYPE_TRAITS
#define INCLUDE_STD_TYPE_TRAITS
#include <type_traits>
#endif

#ifndef INCLUDE_STD_IOSFWD
#define INCLUDE_STD_IOSFWD
#include <iosfwd>
#endif

namespace saklib
{
    namespace internal
    {
        template <typename T>
        class Constraint_Floating_Point_Type
        {
            static_assert(std::is_floating_point<T>::value, "Can only use floating point types.");
        public:
            using float_type = T;

            Constraint_Floating_Point_Type();

            bool can_set_value_to(float_type a_value) const;

        };
    } // namespace internal
} // namespace saklib

#endif // SAKLIB_INTERNAL_CONSTRAINT_FLOATING_POINT_TYPE_H
