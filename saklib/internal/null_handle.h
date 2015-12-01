#ifndef SAKLIB_INTERNAL_NULL_HANDLE_H
#define SAKLIB_INTERNAL_NULL_HANDLE_H

#ifndef SAKLIB_INTERNAL_NULL_HANDLE__FWD_H
#include "null_handle__fwd.h"
#endif

#ifndef INCLUDE_STD_CSTDDEF
#define INCLUDE_STD_CSTDDEF
#include <cstddef>
#endif

namespace saklib
{
    namespace internal
    {
        //---------------------------------------------------------------------------
        // Handle_Value_Type
        //---------------------------------------------------------------------------

        using Handle_Value_Type = std::size_t;

        // Factory Functions
        //============================================================
        // constexpr
        Handle_Value_Type null_handle_value();

        //---------------------------------------------------------------------------
        // Null_Handle_Type
        //---------------------------------------------------------------------------

        class Null_Handle_Type
        {
        public:
            static Handle_Value_Type const value;
        };

        // Factory Functions
        //============================================================
        // constexpr
        Null_Handle_Type null_handle();


    } // namespace internal
} // namespace saklib

#ifndef SAKLIB_INTERNAL_NULL_HANDLE__INLINE_H
#include "null_handle__inline.h"
#endif

#endif // SAKLIB_INTERNAL_NULL_HANDLE_H
