#ifndef SAKLIB_ATTRIBUTE_H
#define SAKLIB_ATTRIBUTE_H

#include "iattribute.h"
#include "../object/object_name.h"
#include "attribute_typeid.h"
#include "attribute_value.h"
#include "attribute_constraint.h"

namespace saklib
{
    /*
    Attribute<T>
    ====================================================================================================
    The full interface for an Attribute object of type T. Use this to access it without caring about
    how the data is implemented.
    */
    template <typename T>
    class Attribute :
            public IAttribute<T>,
            public remote::Object_Name_R,
            public local::Attribute_Typeid<T>,
            public remote::Attribute_Constraint_R<T>,
            public local::Attribute_Value<T>
    {
    public:
        // Typedefs
        //============================================================
        COMMON_TRAITS_TYPEDEFS_T

        // Special 6
        //============================================================
        Attribute(IObject_Name_R const& ar_name, IAttribute_Constraint_R<T> const& ar_constraint):
            IAttribute<T>(),
            remote::Object_Name_R(ar_name),
            local::Attribute_Typeid<T>(),
            remote::Attribute_Constraint_R<T>(ar_constraint),
            local::Attribute_Value<T>(this->initial_value())
        {}

        ~Attribute() override = default;
    };
} // namespace saklib

#endif // SAKLIB_ATTRIBUTE_H

