#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_INT__FWD_H
#define SAKLIB_INTERNAL_ATTRIBUTE_DATA_INT__FWD_H



namespace saklib
{
    namespace internal
    {
        template <typename T>
        class Attribute_Data_Definition_Integral_Type;

        using Attribute_Data_Definition_Short = Attribute_Data_Definition_Integral_Type<short>;
        using Attribute_Data_Definition_UShort = Attribute_Data_Definition_Integral_Type<unsigned short>;

        using Attribute_Data_Definition_Int = Attribute_Data_Definition_Integral_Type<int>;
        using Attribute_Data_Definition_UInt = Attribute_Data_Definition_Integral_Type<unsigned int>;

        using Attribute_Data_Definition_Long = Attribute_Data_Definition_Integral_Type<long>;
        using Attribute_Data_Definition_ULong = Attribute_Data_Definition_Integral_Type<unsigned long>;

        using Attribute_Data_Definition_LLong = Attribute_Data_Definition_Integral_Type<long long>;
        using Attribute_Data_Definition_ULLong = Attribute_Data_Definition_Integral_Type<unsigned long long>;

        template <typename T>
        class Attribute_Data_Integral_Type;

        using Attribute_Data_Short = Attribute_Data_Integral_Type<short>;
        using Attribute_Data_UShort = Attribute_Data_Integral_Type<unsigned short>;

        using Attribute_Data_Int = Attribute_Data_Integral_Type<int>;
        using Attribute_Data_UInt = Attribute_Data_Integral_Type<unsigned int>;

        using Attribute_Data_Long = Attribute_Data_Integral_Type<long>;
        using Attribute_Data_ULong = Attribute_Data_Integral_Type<unsigned long>;

        using Attribute_Data_LLong = Attribute_Data_Integral_Type<long long>;
        using Attribute_Data_ULLong = Attribute_Data_Integral_Type<unsigned long long>;

        //---------------------------------------------------------------------------
        // Type_Integral_Type<T>
        //---------------------------------------------------------------------------
        template <typename T>
        struct Type_Integral_Type
        {
            using int_type = T;
        };

        using Type_Short = Type_Integral_Type<short>;
        using Type_UShort = Type_Integral_Type<unsigned short>;

        using Type_Int = Type_Integral_Type<int>;
        using Type_UInt = Type_Integral_Type<unsigned int>;

        using Type_Long = Type_Integral_Type<long>;
        using Type_ULong = Type_Integral_Type<unsigned long>;

        using Type_LLong = Type_Integral_Type<long long>;
        using Type_ULLong = Type_Integral_Type<unsigned long long>;

    } // namespace internal
} // namespace saklib

#endif // SAKLIB_INTERNAL_ATTRIBUTE_DATA_INT__FWD_H

