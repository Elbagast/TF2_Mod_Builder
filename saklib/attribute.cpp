#include "attribute.h"
#include "attribute_type.h"

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
