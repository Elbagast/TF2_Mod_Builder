#ifndef DATATRAITS_STRING_H
#define DATATRAITS_STRING_H
/*
Type_Traits<std::string>
====================================================================================================
*/
#include "type_traits.h"

namespace Saklib
{
    template <>
    struct Type_Traits<String>
    {
    public:
        using stored_type = String;
        using value_type = stored_type;

        static Type_Enum const type_enum_value{ Type_Enum::String };

        static Type_Enum type_enum()
        {
            return type_enum_value;
        }
        static String type_string()
        {
            return "String";
        }
        static void set_to_default_value(stored_type& value)
        {
            value.clear();
        }
    };

    template <>
    struct TypeHolder<Type_Enum::String>
    {
        using traits_type = Type_Traits <String>;
        using stored_type = traits_type::stored_type;
        using value_type = traits_type::value_type;
        static Type_Enum const enum_value{ Type_Enum::String };
    };

    template <>
    struct Type_Traits<Vector_String>
    {
    public:
        using stored_type = Vector_String;
        using value_type = String;

        static Type_Enum const type_enum_value{ Type_Enum::Vector_String };

        static Type_Enum type_enum()
        {
            return type_enum_value;
        }
        static String type_string()
        {
            return "Vector_String";
        }
        static void set_to_default_value(stored_type& value)
        {
            value.clear();
        }
    };

    template <>
    struct TypeHolder<Type_Enum::Vector_String>
    {
        using traits_type = Type_Traits < Vector_String >;
        using stored_type = traits_type::stored_type;
        using value_type = traits_type::value_type;
        static Type_Enum const type_enum_value{ Type_Enum::Vector_String };
    };

} // namespace Saklib

#endif // DATATRAITS_STRING_H
