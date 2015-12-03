#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_BOOLEAN_TYPE__FWD_H
#define SAKLIB_INTERNAL_ATTRIBUTE_DATA_BOOLEAN_TYPE__FWD_H

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

    } // namespace internal
} // namespace saklib

#endif // SAKLIB_INTERNAL_ATTRIBUTE_DATA_BOOLEAN_TYPE__FWD_H

