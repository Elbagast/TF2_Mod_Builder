#include "all_attribute_definitions.h"

namespace
{
    // helper function to convert an arg to a templated type
    template <Saklib::Type_Enum TE>
    Saklib::Shptr<Saklib::Attribute_Definition> internal_make(Saklib::String const& name)
    {
        return Saklib::Shptr<Saklib::Attribute_Definition>(new Saklib::Attribute_Definition_Type<Saklib::TypeHolder_st<TE> >(name));
    }
}

Saklib::Shptr<Saklib::Attribute_Definition> Saklib::make_shared_Attribute_Definition(String const& name, Type_Enum type)
{
    if (name.empty())
    {
        assert(false);
        return Shptr<Attribute_Definition>(nullptr);
    }
    switch (type)
    {
    case Type_Enum::Bool:            return internal_make<Type_Enum::Bool>(name);
    case Type_Enum::Int:             return internal_make<Type_Enum::Int>(name);
    case Type_Enum::Double:          return internal_make<Type_Enum::Double>(name);
    case Type_Enum::String:          return internal_make<Type_Enum::String>(name);
    case Type_Enum::Path:            return internal_make<Type_Enum::Path>(name);
    case Type_Enum::ElementID:       return internal_make<Type_Enum::ElementID>(name);

    case Type_Enum::Vector_Bool:      return internal_make<Type_Enum::Vector_Bool>(name);
    case Type_Enum::Vector_Int:       return internal_make<Type_Enum::Vector_Int>(name);
    case Type_Enum::Vector_Double:    return internal_make<Type_Enum::Vector_Double>(name);
    case Type_Enum::Vector_String:    return internal_make<Type_Enum::Vector_String>(name);
    case Type_Enum::Vector_Path:      return internal_make<Type_Enum::Vector_Path>(name);
    case Type_Enum::Vector_ElementID: return internal_make<Type_Enum::Vector_ElementID>(name);

    default:                         assert(false); return Shptr<Attribute_Definition>(nullptr);
    }
}
