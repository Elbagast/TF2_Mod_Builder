#ifndef SAKLIB_INTERNAL_TYPE_STRING_H
#define SAKLIB_INTERNAL_TYPE_STRING_H

#ifndef SAKLIB_INTERNAL_TYPE_STRING__FWD_H
#include "type_string__fwd.h"
#endif

#ifndef INCLUDE_STD_STRING
#define INCLUDE_STD_STRING
#include <string>
#endif

namespace saklib
{
    namespace internal
    {
        template <typename T>
        struct Type_C_String
        {
            char const* operator()() const { return "Undefined"; }
        };

        template <typename T>
        struct Type_String
        {
            std::string const& operator()() const
            {
                static std::string const s_value{Type_C_String<T>()()};
                return s_value;
            }
        };


        template <>
        struct Type_C_String<bool>
        {
            char const* operator()() const { return "Bool"; }
        };

        template <>
        struct Type_C_String<int>
        {
            char const* operator()() const { return "Int"; }
        };

    } // namespace internal
} // namespace saklib



#endif // SAKLIB_INTERNAL_TYPE_STRING_H
