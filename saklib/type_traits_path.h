#ifndef TYPE_TRAITS_PATH_H
#define TYPE_TRAITS_PATH_H
/*
Type_Traits<std::string>
====================================================================================================
*/
#include "type_traits.h"

namespace Saklib
{
    template <>
    struct Type_Traits<Path>
    {
    public:
        using stored_type = Path;
        using value_type = stored_type;

        static Type_Enum const type_enum_value{ Type_Enum::Path };

        static Type_Enum type_enum()
        {
            return type_enum_value;
        }
        static String type_string()
        {
            return "Path";
        }
        static void set_to_default_value(stored_type& value)
        {
            value.clear();
        }
    };

    template <>
    struct TypeHolder<Type_Enum::Path>
    {
        using traits_type = Type_Traits <Path>;
        using stored_type = traits_type::stored_type;
        using value_type = traits_type::value_type;
        static Type_Enum const enum_value{ Type_Enum::Path };
    };

    template <>
    struct Type_Traits<Vector_Path>
    {
    public:
        using stored_type = Vector_Path;
        using value_type = Path;

        static Type_Enum const type_enum_value{ Type_Enum::Vector_Path };

        static Type_Enum type_enum()
        {
            return type_enum_value;
        }
        static String type_string()
        {
            return "Vector_Path";
        }
        static void set_to_default_value(stored_type& value)
        {
            value.clear();
        }
    };

    template <>
    struct TypeHolder<Type_Enum::Vector_Path>
    {
        using traits_type = Type_Traits < Vector_Path >;
        using stored_type = traits_type::stored_type;
        using value_type = traits_type::value_type;
        static Type_Enum const type_enum_value{ Type_Enum::Vector_Path };
    };

} // namespace Saklib
#endif // TYPE_TRAITS_PATH_H

