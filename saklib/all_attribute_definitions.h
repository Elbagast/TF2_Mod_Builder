#ifndef ALL_ATTRIBUTE_DEFINITIONS_H
#define ALL_ATTRIBUTE_DEFINITIONS_H

#include "attribute_definition.h"
#include "attribute_definition_type.h"

template <typename T>
Saklib::Shptr<Saklib::Attribute_Definition> Saklib::make_shared_Attribute_Definition_by_type(String const& name)
{
    if (name.empty())
    {
        assert(false);
        return Shptr<Attribute_Definition>(nullptr);
    }
    return Shptr<Attribute_Definition>(new Attribute_Definition_Type<T>(name));
}

template <typename T, typename... Args>
Saklib::Shptr<Saklib::Attribute_Definition> Saklib::make_shared_Attribute_Definition_by_type(String const& name, Args&&... args)
{
    if (name.empty())
    {
        assert(false);
        return Shptr<Attribute_Definition>(nullptr);
    }
    return Shptr<Attribute_Definition>(new Attribute_Definition_Type<T>(name, std::forward<Args>(args)...));
}

#endif // ALL_ATTRIBUTE_DEFINITIONS_H

