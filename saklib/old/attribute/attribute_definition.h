#ifndef SAKLIB_ATTRIBUTE_DEFINITION_H
#define SAKLIB_ATTRIBUTE_DEFINITION_H

#include <memory>
#include "iattribute_base.h"
#include "iattribute_definition.h"
#include "../object/object_name.h"
#include "attribute_typeid.h"
#include "attribute_constraint.h"
#include "attribute_maker.h"

#include "attribute.h"

#include "../types.h"
#include "../common_traits.h"

namespace saklib
{
    template <typename T>
    class Attribute_Definition :
            public IAttribute_Definition<T>,
            public local::Object_Name_RW,
            public local::Attribute_Typeid<T>,
            public local::Attribute_Constraint_RW<T>,
            public local::Attribute_Maker<T>
    {
    public:
        // Typedefs
        //============================================================
        COMMON_TRAITS_TYPEDEFS_T

        // Special 6
        //============================================================
        Attribute_Definition():
            IAttribute_Definition<T>(),
            local::Object_Name_RW("Attribute Default Name"),
            local::Attribute_Constraint_RW<T>(),
            local::Attribute_Maker<T>(*this, *this)
        {}

        explicit Attribute_Definition(String const& a_name):
            IAttribute_Definition<T>(),
            local::Object_Name_RW(a_name),
            local::Attribute_Constraint_RW<T>(),
            local::Attribute_Maker<T>(*this, *this)
        {}

        ~Attribute_Definition() override = default;
    };


} // namespace saklib

#endif // SAKLIB_ATTRIBUTE_DEFINITION_H

