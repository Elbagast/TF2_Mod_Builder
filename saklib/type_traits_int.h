#ifndef TYPE_TRAITS_INT_H
#define TYPE_TRAITS_INT_H
/*
Type_Traits<int>
====================================================================================================
*/
#include "type_traits.h"

namespace Saklib
{
    template <>
	struct Type_Traits<Int>
    {
    public:
		using stored_type = Int;
        using value_type = stored_type;

        static Type_Enum const type_enum_value{ Type_Enum::Int };

        static Type_Enum type_enum()
        {
            return type_enum_value;
        }
        static String type_string()
        {
            return "Int";
        }
        static void set_to_default_value(stored_type& value)
        {
            value = 0;
        }
    };

    template <>
    struct TypeHolder<Type_Enum::Int>
    {
		using traits_type = Type_Traits < Int >;
        using stored_type = traits_type::stored_type;
        using value_type = traits_type::value_type;
        static Type_Enum const type_enum_value{ Type_Enum::Int };
    };

    template <>
	struct Type_Traits<Vector_Int>
    {
    public:
		using stored_type = Vector_Int;
		using value_type = Int;

        static Type_Enum const type_enum_value{ Type_Enum::Vector_Int };

        static Type_Enum type_enum()
        {
            return type_enum_value;
        }
        static String type_string()
        {
            return "Vector_Int";
        }
        static void set_to_default_value(stored_type& value)
        {
            value.clear();
        }
    };

    template <>
    struct TypeHolder<Type_Enum::Vector_Int>
    {
		using traits_type = Type_Traits < Vector_Int >;
        using stored_type = traits_type::stored_type;
        using value_type = traits_type::value_type;
        static Type_Enum const type_enum_value{ Type_Enum::Vector_Int };
    };

} // namespace Saklib

#endif // TYPE_TRAITS_INT_H
