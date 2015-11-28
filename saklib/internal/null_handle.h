#ifndef SAKLIB_INTERNAL_NULL_HANDLE_H
#define SAKLIB_INTERNAL_NULL_HANDLE_H

#ifndef SAKLIB_INTERNAL_NULL_HANDLE__FWD_H
#include "null_handle__fwd.h"
#endif

#include <cstddef>
#include <type_traits>

namespace saklib
{
    namespace internal
    {
        using Handle_Value_Type = std::size_t;
        static_assert(std::is_integral<Handle_Value_Type>::value
                      && std::is_unsigned<Handle_Value_Type>::value,
                      "Supplied underlying_type must be an unsigned integral type.");

        class Null_Handle_Type
        {
        public:
            static Handle_Value_Type const value;
        };

        // constexpr
        Null_Handle_Type null_handle();

        // constexpr
        Handle_Value_Type null_handle_value();
    } // namespace internal
} // namespace saklib

#ifndef SAKLIB_INTERNAL_NULL_HANDLE__INLINE_H
#include "null_handle__inline.h"
#endif

#endif // SAKLIB_INTERNAL_NULL_HANDLE_H
