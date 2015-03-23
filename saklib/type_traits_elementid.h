#ifndef TYPE_TRAITS_ELEMENTID_H
#define TYPE_TRAITS_ELEMENTID_H
/*
Type_Traits<ElementID>
====================================================================================================
*/
#include "type_traits.h"
#include "elementid.h"

namespace Saklib
{
    template <>
    struct Type_Traits<ElementID>
    {
    public:
        using stored_type = ElementID;
        using value_type = stored_type;

        static Type_Enum const type_enum_value{ Type_Enum::ElementID };

        static Type_Enum type_enum()
        {
            return type_enum_value;
        }
        static String type_string()
        {
            return "ElementID";
        }
        static void set_to_default_value(stored_type& value)
        {
            value = ElementID();
        }
    };

    template <>
    struct TypeHolder<Type_Enum::ElementID>
    {
        using traits_type = Type_Traits < ElementID >;
        using stored_type = traits_type::stored_type;
        using value_type = traits_type::value_type;
        static Type_Enum const enum_value{ Type_Enum::ElementID };
    };

    template <>
	struct Type_Traits<Vector_ElementID>
    {
    public:
		using stored_type = Vector_ElementID;
        using value_type = ElementID;

        static Type_Enum const type_enum_value{ Type_Enum::Vector_ElementID };

        static Type_Enum type_enum()
        {
            return type_enum_value;
        }
        static String type_string()
        {
            return "Vector_ElementID";
        }
        static void set_to_default_value(stored_type& value)
        {
            value.clear();
        }
    };

    template <>
    struct TypeHolder<Type_Enum::Vector_ElementID>
    {
		using traits_type = Type_Traits < Vector_ElementID >;
        using stored_type = traits_type::stored_type;
        using value_type = traits_type::value_type;
        static Type_Enum const type_enum_value{ Type_Enum::Vector_ElementID };
    };

} // namespace Saklib

#endif // TYPE_TRAITS_ELEMENTID_H
