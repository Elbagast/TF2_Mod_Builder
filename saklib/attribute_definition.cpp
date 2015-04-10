#include "attribute_definition.h"
#include "attribute_definition_type.h"

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

/*
namespace
{
    // helper function to convert an arg to a templated type
    template <Saklib::Type_Enum TE>
    Saklib::Shptr<Saklib::Attribute_Definition> internal_make(Saklib::String const& name, Saklib::Uptr<Saklib::Constraint>&& constraint)
    {
        return Saklib::Shptr<Saklib::Attribute_Definition>(new Saklib::Attribute_Definition_Type<Saklib::TypeHolder_st<TE> >(name, std::forward<Saklib::Uptr<Saklib::Constraint>>(constraint)));
    }
}

Saklib::Shptr<Saklib::Attribute_Definition> Saklib::make_shared_Attribute_Definition(String const& name, Type_Enum type, Uptr<Constraint>&& constraint)
{
    if (name.empty())
        return Shptr<Attribute_Definition>(nullptr);
    switch (type)
    {
    case Type_Enum::Bool:            return internal_make<Type_Enum::Bool>(name, std::forward<Uptr<Constraint>>(constraint));
    case Type_Enum::Int:             return internal_make<Type_Enum::Int>(name, std::forward<Uptr<Constraint>>(constraint));
    case Type_Enum::Double:          return internal_make<Type_Enum::Double>(name, std::forward<Uptr<Constraint>>(constraint));
    case Type_Enum::String:          return internal_make<Type_Enum::String>(name, std::forward<Uptr<Constraint>>(constraint));
    case Type_Enum::ElementID:       return internal_make<Type_Enum::ElementID>(name, std::forward<Uptr<Constraint>>(constraint));

    case Type_Enum::Vector_Bool:      return internal_make<Type_Enum::Vector_Bool>(name, std::forward<Uptr<Constraint>>(constraint));
    case Type_Enum::Vector_Int:       return internal_make<Type_Enum::Vector_Int>(name, std::forward<Uptr<Constraint>>(constraint));
    case Type_Enum::Vector_Double:    return internal_make<Type_Enum::Vector_Double>(name, std::forward<Uptr<Constraint>>(constraint));
    case Type_Enum::Vector_String:    return internal_make<Type_Enum::Vector_String>(name, std::forward<Uptr<Constraint>>(constraint));
    case Type_Enum::Vector_ElementID: return internal_make<Type_Enum::Vector_ElementID>(name, std::forward<Uptr<Constraint>>(constraint));

    default:                         return Shptr<Attribute_Definition>(nullptr);// return std::unique_ptr<Attribute>(new Attribute_Simple<TypeHolder_st<Type_Enum::Undefined> >(name));
    }
}
*/
