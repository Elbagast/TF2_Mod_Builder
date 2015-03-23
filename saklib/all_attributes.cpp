#include "all_attributes.h"


Saklib::Type_Enum Saklib::attribute_TypeString_to_Type_Enum(String const& typeString)
{
    if (typeString == TypeHolder_traits<Type_Enum::Bool>::type_string())
        return Type_Enum::Bool;
    else if (typeString == TypeHolder_traits<Type_Enum::Int>::type_string())
        return Type_Enum::Int;
    else if (typeString == TypeHolder_traits<Type_Enum::Double>::type_string())
        return Type_Enum::Double;
    else if (typeString == TypeHolder_traits<Type_Enum::String>::type_string())
        return Type_Enum::String;
    else if (typeString == TypeHolder_traits<Type_Enum::ElementID>::type_string())
        return Type_Enum::ElementID;

    else if (typeString == TypeHolder_traits<Type_Enum::Vector_Bool>::type_string())
        return Type_Enum::Vector_Bool;
    else if (typeString == TypeHolder_traits<Type_Enum::Vector_Int>::type_string())
        return Type_Enum::Vector_Int;
    else if (typeString == TypeHolder_traits<Type_Enum::Vector_Double>::type_string())
        return Type_Enum::Vector_Double;
    else if (typeString == TypeHolder_traits<Type_Enum::Vector_String>::type_string())
        return Type_Enum::Vector_String;
    else if (typeString == TypeHolder_traits<Type_Enum::Vector_ElementID>::type_string())
        return Type_Enum::Vector_ElementID;

    else
        return Type_Enum::Undefined;
}

Saklib::String Saklib::attribute_Type_Enum_to_TypeString(Type_Enum type)
{
    switch (type)
    {
    case Type_Enum::Bool:        return TypeHolder_traits<Type_Enum::Bool>::type_string();
    case Type_Enum::Int:         return TypeHolder_traits<Type_Enum::Int>::type_string();
    case Type_Enum::Double:      return TypeHolder_traits<Type_Enum::Double>::type_string();
    case Type_Enum::String:      return TypeHolder_traits<Type_Enum::String>::type_string();
    case Type_Enum::ElementID:   return TypeHolder_traits<Type_Enum::ElementID>::type_string();

    case Type_Enum::Vector_Bool:        return TypeHolder_traits<Type_Enum::Vector_Bool>::type_string();
    case Type_Enum::Vector_Int:         return TypeHolder_traits<Type_Enum::Vector_Int>::type_string();
    case Type_Enum::Vector_Double:      return TypeHolder_traits<Type_Enum::Vector_Double>::type_string();
    case Type_Enum::Vector_String:      return TypeHolder_traits<Type_Enum::Vector_String>::type_string();
    case Type_Enum::Vector_ElementID:   return TypeHolder_traits<Type_Enum::Vector_ElementID>::type_string();

    default:                    return TypeHolder_traits<Type_Enum::Undefined>::type_string();
    }
}
