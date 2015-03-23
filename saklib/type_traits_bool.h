#ifndef TYPE_TRAITS_BOOL_H
#define TYPE_TRAITS_BOOL_H
/*
DataTraits<bool> and DataTraits<Vector<bool>>
====================================================================================================
*/
#include "type_traits.h"

namespace Saklib
{

    template <>
    struct Type_Traits<Bool>
    {
    public:
		using stored_type = Bool;
        using value_type = stored_type;
        
        static Type_Enum const type_enum_value{ Type_Enum::Bool };

        static Type_Enum type_enum()
        {
            return type_enum_value;
        }
        static String type_string()
        {
            return "Bool";
        }
        static void set_to_default_value(stored_type& value)
        {
            value = false;
        }
    };
    
    template <>
    struct TypeHolder<Type_Enum::Bool>
    {
		using traits_type = Type_Traits < Bool >;
        using stored_type = traits_type::stored_type;
        using value_type = traits_type::value_type;
        static Type_Enum const typeid_value{ Type_Enum::Int };
    };

    template <>
	struct Type_Traits<Vector_Bool>
    {
    public:
		using stored_type = Vector_Bool;
		using value_type = Bool;

        static Type_Enum const type_enum_value{ Type_Enum::Vector_Bool };

        static Type_Enum type_enum()
        {
            return type_enum_value;
        }
        static String type_string()
        {
            return "Vector_Bool";
        }
        static void set_to_default_value(stored_type& value)
        {
            value.clear();
        }
    };

    template <>
    struct TypeHolder<Type_Enum::Vector_Bool>
    {
		using traits_type = Type_Traits < Vector_Bool >;
        using stored_type = traits_type::stored_type;
        using value_type = traits_type::value_type;
        static Type_Enum const type_enum_value{ Type_Enum::Vector_Bool };
    };

} // namespace Saklib


#endif // TYPE_TRAITS_BOOL_H
