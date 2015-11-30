#ifndef SAKLIB_INTERNAL_TYPE_STRING__FWD_H
#define SAKLIB_INTERNAL_TYPE_STRING__FWD_H

namespace saklib
{
    namespace internal
    {
        template <typename T>
        struct Type_C_String;

        template <typename T>
        struct Type_String;

        using Type_String_Bool = Type_String<bool>;
        using Type_String_Int = Type_String<int>;

        using TS_Bool = Type_String_Bool;
        using TS_Int = Type_String_Int;

    } // namespace internal
} // namespace saklib

#endif // SAKLIB_INTERNAL_TYPE_STRING__FWD_H

