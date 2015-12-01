#ifndef ALL_ATTRIBUTE_DEFINITIONS_H
#define ALL_ATTRIBUTE_DEFINITIONS_H

#include "attribute_definition.h"
#include "attribute_definition_type.h"

namespace saklib
{
    std::shared_ptr<Attribute_Definition> make_shared_Attribute_Definition(String const& name, Type_Enum type);

    template <typename T>
    std::shared_ptr<Attribute_Definition> make_shared_Attribute_Definition_by_type(String const& name);

    template <typename T, typename... Args>
    std::shared_ptr<Attribute_Definition> make_shared_Attribute_Definition_by_type(String const& name, Args&&... args);

} // namespace saklib


// Implementation
//----------------------------------------------------------------------------------------------------

template <typename T>
std::shared_ptr<saklib::Attribute_Definition> saklib::make_shared_Attribute_Definition_by_type(String const& name)
{
    if (name.empty())
    {
        assert(false);
        return std::shared_ptr<Attribute_Definition>(nullptr);
    }
    return std::shared_ptr<Attribute_Definition>(new Attribute_Definition_Type<T>(name));
}

template <typename T, typename... Args>
std::shared_ptr<saklib::Attribute_Definition> saklib::make_shared_Attribute_Definition_by_type(String const& name, Args&&... args)
{
    if (name.empty())
    {
        assert(false);
        return std::shared_ptr<Attribute_Definition>(nullptr);
    }
    return std::shared_ptr<Attribute_Definition>(new Attribute_Definition_Type<T>(name, std::forward<Args>(args)...));
}

#endif // ALL_ATTRIBUTE_DEFINITIONS_H

