#ifndef TYPE_TRAITS_NODEID_H
#define TYPE_TRAITS_NODEID_H
/*
Type_Traits<ElementID>
====================================================================================================
*/
#include "type_traits.h"
#include "nodeid.h"

namespace Saklib
{
    template <>
    struct Type_Traits<NodeID>
    {
    public:
        using stored_type = NodeID;
        using value_type = stored_type;

        static Type_Enum const type_enum_value{ Type_Enum::NodeID };

        static Type_Enum type_enum()
        {
            return type_enum_value;
        }
        static String type_string()
        {
            return "NodeID";
        }
        static void set_to_default_value(stored_type& value)
        {
            value = NodeID();
        }
    };

    template <>
    struct TypeHolder<Type_Enum::NodeID>
    {
        using traits_type = Type_Traits < NodeID >;
        using stored_type = traits_type::stored_type;
        using value_type = traits_type::value_type;
        static Type_Enum const enum_value{ Type_Enum::NodeID };
    };

    template <>
    struct Type_Traits<Vector_NodeID>
    {
    public:
        using stored_type = Vector_NodeID;
        using value_type = NodeID;

        static Type_Enum const type_enum_value{ Type_Enum::Vector_NodeID };

        static Type_Enum type_enum()
        {
            return type_enum_value;
        }
        static String type_string()
        {
            return "Vector_NodeID";
        }
        static void set_to_default_value(stored_type& value)
        {
            value.clear();
        }
    };

    template <>
    struct TypeHolder<Type_Enum::Vector_NodeID>
    {
        using traits_type = Type_Traits < Vector_NodeID >;
        using stored_type = traits_type::stored_type;
        using value_type = traits_type::value_type;
        static Type_Enum const type_enum_value{ Type_Enum::Vector_NodeID };
    };

} // namespace Saklib

#endif // TYPE_TRAITS_NODEID_H

