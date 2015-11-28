#ifndef SAKLIB_INTERNAL_TYPE_STRING_H
#define SAKLIB_INTERNAL_TYPE_STRING_H

#ifndef SAKLIB_INTERNAL_TYPE_STRING__FWD_H
#include "type_string__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_STRING_H
#include "string.h"
#endif

namespace saklib
{
    namespace internal
    {
        template <typename T>
        struct Type_String
        {
            static char const* c_string()       { return "Undefined"; }
            static wchar_t const* wc_string()   { return L"Undefined"; }

            String operator()() const   { return String(c_string()); }
        };


        template <>
        struct Type_String<bool>
        {
            static char const* c_string()       { return "Bool"; }
            static wchar_t const* wc_string()   { return L"Bool"; }

            String operator()() const   { return String(c_string()); }
        };

        template <>
        struct Type_String<int>
        {
            static char const* c_string()       { return "Int"; }
            static wchar_t const* wc_string()   { return L"Int"; }

            String operator()() const   { return String(c_string()); }
        };

    } // namespace internal
} // namespace saklib



#endif // SAKLIB_INTERNAL_TYPE_STRING_H
