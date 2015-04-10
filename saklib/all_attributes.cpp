#include "all_attributes.h"

namespace
{
    // helper function
    template <Saklib::Type_Enum TE>
    Saklib::Uptr<Saklib::Attribute> internal_make(Saklib::Shptr<Saklib::Attribute_Definition> const& definition)
    {
        return Saklib::Uptr<Saklib::Attribute>(new Saklib::Attribute_Type<Saklib::TypeHolder_st<TE> >(definition));
    }
}

Saklib::Uptr<Saklib::Attribute> Saklib::make_Attribute(Shptr<Attribute_Definition> const& definition)
{
    if (!definition)
    {
        assert(false);
        return Uptr<Attribute>(nullptr);
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

    default:                         assert(false); return Uptr<Attribute>(nullptr);
    }
}


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
