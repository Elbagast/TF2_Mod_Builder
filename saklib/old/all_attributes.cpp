#include "all_attributes.h"

namespace
{
    // helper function
    template <saklib::Type_Enum TE>
    std::unique_ptr<saklib::Attribute> internal_make(std::shared_ptr<saklib::Attribute_Definition> const& definition)
    {
        return std::unique_ptr<saklib::Attribute>(new saklib::Attribute_Type<saklib::Type_Holder_st<TE> >(definition));
    }
}

std::unique_ptr<saklib::Attribute> saklib::make_Attribute(std::shared_ptr<Attribute_Definition> const& definition)
{
    if (!definition)
    {
        assert(false);
        return std::unique_ptr<Attribute>(nullptr);
    }

    switch (definition->type_enum())
    {
    case Type_Enum::Bool:            return internal_make<Type_Enum::Bool>(definition);
    case Type_Enum::Int:             return internal_make<Type_Enum::Int>(definition);
    case Type_Enum::Double:          return internal_make<Type_Enum::Double>(definition);
    case Type_Enum::String:          return internal_make<Type_Enum::String>(definition);
    case Type_Enum::Path:            return internal_make<Type_Enum::Path>(definition);
    case Type_Enum::ElementID:       return internal_make<Type_Enum::ElementID>(definition);

    case Type_Enum::Vector_Bool:      return internal_make<Type_Enum::Vector_Bool>(definition);
    case Type_Enum::Vector_Int:       return internal_make<Type_Enum::Vector_Int>(definition);
    case Type_Enum::Vector_Double:    return internal_make<Type_Enum::Vector_Double>(definition);
    case Type_Enum::Vector_String:    return internal_make<Type_Enum::Vector_String>(definition);
    case Type_Enum::Vector_Path:      return internal_make<Type_Enum::Vector_Path>(definition);
    case Type_Enum::Vector_ElementID: return internal_make<Type_Enum::Vector_ElementID>(definition);

    default:                         assert(false); return std::unique_ptr<Attribute>(nullptr);
    }
}

saklib::Type_Enum saklib::attribute_TypeString_to_Type_Enum(String const& typeString)
{
    if (typeString == Type_Holder_traits<Type_Enum::Bool>::type_string())
        return Type_Enum::Bool;
    else if (typeString == Type_Holder_traits<Type_Enum::Int>::type_string())
        return Type_Enum::Int;
    else if (typeString == Type_Holder_traits<Type_Enum::Double>::type_string())
        return Type_Enum::Double;
    else if (typeString == Type_Holder_traits<Type_Enum::String>::type_string())
        return Type_Enum::String;
    else if (typeString == Type_Holder_traits<Type_Enum::ElementID>::type_string())
        return Type_Enum::ElementID;

    else if (typeString == Type_Holder_traits<Type_Enum::Vector_Bool>::type_string())
        return Type_Enum::Vector_Bool;
    else if (typeString == Type_Holder_traits<Type_Enum::Vector_Int>::type_string())
        return Type_Enum::Vector_Int;
    else if (typeString == Type_Holder_traits<Type_Enum::Vector_Double>::type_string())
        return Type_Enum::Vector_Double;
    else if (typeString == Type_Holder_traits<Type_Enum::Vector_String>::type_string())
        return Type_Enum::Vector_String;
    else if (typeString == Type_Holder_traits<Type_Enum::Vector_ElementID>::type_string())
        return Type_Enum::Vector_ElementID;

    else
        return Type_Enum::Undefined;
}

saklib::String saklib::attribute_Type_Enum_to_TypeString(Type_Enum type)
{
    switch (type)
    {
    case Type_Enum::Bool:        return Type_Holder_traits<Type_Enum::Bool>::type_string();
    case Type_Enum::Int:         return Type_Holder_traits<Type_Enum::Int>::type_string();
    case Type_Enum::Double:      return Type_Holder_traits<Type_Enum::Double>::type_string();
    case Type_Enum::String:      return Type_Holder_traits<Type_Enum::String>::type_string();
    case Type_Enum::ElementID:   return Type_Holder_traits<Type_Enum::ElementID>::type_string();

    case Type_Enum::Vector_Bool:        return Type_Holder_traits<Type_Enum::Vector_Bool>::type_string();
    case Type_Enum::Vector_Int:         return Type_Holder_traits<Type_Enum::Vector_Int>::type_string();
    case Type_Enum::Vector_Double:      return Type_Holder_traits<Type_Enum::Vector_Double>::type_string();
    case Type_Enum::Vector_String:      return Type_Holder_traits<Type_Enum::Vector_String>::type_string();
    case Type_Enum::Vector_ElementID:   return Type_Holder_traits<Type_Enum::Vector_ElementID>::type_string();

    default:                    return Type_Holder_traits<Type_Enum::Undefined>::type_string();
    }
}
