#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_FLOATING_POINT_TYPE__FWD_H
#define SAKLIB_INTERNAL_ATTRIBUTE_DATA_FLOATING_POINT_TYPE__FWD_H

namespace saklib
{
    namespace internal
    {
        template <typename T>
        class Attribute_Data_Definition_Floating_Point_Type;

        using Attribute_Data_Definition_Float = Attribute_Data_Definition_Floating_Point_Type<float>;
        using Attribute_Data_Definition_Double = Attribute_Data_Definition_Floating_Point_Type<double>;
        using Attribute_Data_Definition_LDouble = Attribute_Data_Definition_Floating_Point_Type<long double>;

        template <typename T>
        class Attribute_Data_Floating_Point_Type;

        using Attribute_Data_Float = Attribute_Data_Floating_Point_Type<float>;
        using Attribute_Data_Double = Attribute_Data_Definition_Floating_Point_Type<double>;
        using Attribute_Data_LDouble = Attribute_Data_Floating_Point_Type<long double>;
    } // namespace internal
} // namespace saklib

#endif // SAKLIB_INTERNAL_ATTRIBUTE_DATA_FLOATING_POINT_TYPE__FWD_H

