#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_BOOL__FWD_H
#define SAKLIB_INTERNAL_ATTRIBUTE_DATA_BOOL__FWD_H

namespace saklib
{
    namespace internal
    {
        template <typename T>
        class Attribute_Data_Definition_Boolean_Type;

        using Attribute_Data_Definition_Bool = Attribute_Data_Definition_Boolean_Type<bool>;

        template <typename T>
        class Attribute_Data_Boolean_Type;

        using Attribute_Data_Bool = Attribute_Data_Boolean_Type<bool>;

        //---------------------------------------------------------------------------
        // Type_Boolean_Type<T>
        //---------------------------------------------------------------------------
        template <typename T>
        struct Type_Boolean_Type
        {
            using bool_type = T;
        };

        using Type_Bool = Type_Boolean_Type<bool>;

    } // namespace internal
} // namespace saklib

#endif // SAKLIB_INTERNAL_ATTRIBUTE_DATA_BOOL__FWD_H

