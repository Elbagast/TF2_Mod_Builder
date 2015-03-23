#ifndef DATATRAITS_DOUBLE_H
#define DATATRAITS_DOUBLE_H
/*
Type_Traits<double>
====================================================================================================
*/
#include "type_traits.h"

namespace Saklib
{
    template <>
	struct Type_Traits<Double>
    {
    public:
		using stored_type = Double;
        using value_type = stored_type;

        static Type_Enum const type_enum_value{ Type_Enum::Double };

        static Type_Enum type_enum()
        {
            return type_enum_value;
        }
        static String type_string()
        {
            return "Double";
        }
        static void set_to_default_value(stored_type& value)
        {
            value = 0.0;
        }
    };

    template <>
    struct TypeHolder<Type_Enum::Double>
    {
		using traits_type = Type_Traits < Double >;
        using stored_type = traits_type::stored_type;
        using value_type = traits_type::value_type;
        static Type_Enum const enum_value{ Type_Enum::Double };
    };

    template <>
	struct Type_Traits<Vector_Double>
    {
    public:
		using stored_type = Vector_Double;
		using value_type = Double;

        static Type_Enum const type_enum_value{ Type_Enum::Vector_Double };

        static Type_Enum type_enum()
        {
            return type_enum_value;
        }
        static String type_string()
        {
            return "Vector_Double";
        }
        static void set_to_default_value(stored_type& value)
        {
            value.clear();
        }
    };

    template <>
    struct TypeHolder<Type_Enum::Vector_Double>
    {
		using traits_type = Type_Traits < Vector_Double >;
        using stored_type = traits_type::stored_type;
        using value_type = traits_type::value_type;
        static Type_Enum const type_enum_value{ Type_Enum::Vector_Double };
    };

} // namespace Saklib

#endif // DATATRAITS_DOUBLE_H
