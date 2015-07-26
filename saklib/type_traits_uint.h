#ifndef TYPE_TRAITS_UINT_H
#define TYPE_TRAITS_UINT_H
/*
Type_Traits<int>
====================================================================================================
*/
#include "type_traits.h"

namespace Saklib
{
    template <>
    struct Type_Traits<Uint>
    {
    public:
        using stored_type = Uint;
        using value_type = stored_type;

        static Type_Enum const type_enum_value{ Type_Enum::Uint };

        static Type_Enum type_enum()
        {
            return type_enum_value;
        }
        static String type_string()
        {
            return "Uint";
        }
        static void set_to_default_value(stored_type& value)
        {
            value = 0;
        }
    };

    template <>
    struct TypeHolder<Type_Enum::UInt>
    {
        using traits_type = Type_Traits < Uint >;
        using stored_type = traits_type::stored_type;
        using value_type = traits_type::value_type;
        static Type_Enum const type_enum_value{ Type_Enum::UInt };
    };

    template <>
    struct Type_Traits<Vector_Uint>
    {
    public:
        using stored_type = Vector_Uint;
        using value_type = Uint;

        static Type_Enum const type_enum_value{ Type_Enum::Vector_Uint };

        static Type_Enum type_enum()
        {
            return type_enum_value;
        }
        static String type_string()
        {
            return "Vector_Uint";
        }
        static void set_to_default_value(stored_type& value)
        {
            value.clear();
        }
    };

    template <>
    struct TypeHolder<Type_Enum::Vector_Uint>
    {
        using traits_type = Type_Traits < Vector_Uint >;
        using stored_type = traits_type::stored_type;
        using value_type = traits_type::value_type;
        static Type_Enum const type_enum_value{ Type_Enum::Vector_Uint };
    };

} // namespace Saklib

#endif // TYPE_TRAITS_UINT_H

