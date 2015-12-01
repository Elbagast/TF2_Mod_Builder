#include "all_attribute_definitions.h"

namespace
{
    // helper function to convert an arg to a templated type
    template <saklib::Type_Enum TE>
    std::shared_ptr<saklib::Attribute_Definition> internal_make(saklib::String const& name)
    {
        return std::shared_ptr<saklib::Attribute_Definition>(new saklib::Attribute_Definition_Type<saklib::Type_Holder_st<TE> >(name));
    }
}

std::shared_ptr<saklib::Attribute_Definition> saklib::make_shared_Attribute_Definition(String const& name, Type_Enum type)
{
    if (name.empty())
    {
        assert(false);
        return std::shared_ptr<Attribute_Definition>(nullptr);
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

    default:                         assert(false); return std::shared_ptr<Attribute_Definition>(nullptr);
    }
}
