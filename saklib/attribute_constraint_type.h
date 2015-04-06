#ifndef ATTRIBUTE_CONSTRAINT_TYPE_H
#define ATTRIBUTE_CONSTRAINT_TYPE_H

#include "types.h"

namespace Saklib
{
    class Constraint;

    /*
    Constraint_Type
    ====================================================================================================
    Abstract class the contains flyweight information to create a given Attribute based on it.

    */
    template <typename T>
    class Constraint_Type
    {
    public:
        bool value_can_be(T const& value)   { return v_value_can_be(value); }

    protected:
        virtual ~Constraint_Type() = default;

        virtual bool v_value_can_be(T const& value) = 0;
    };

    template <typename T>
    class Unconstrained:
            public Constraint_Type<T>
    {
    public:
        ~Unconstrained() override = default;

    protected:
        bool v_value_can_be(T const& value) override
        {
            return true;
        }
    };


    //Shptr<Attribute_Definition> make_shared_Attribute_Definition(String const& name, Type_Enum type);

    //Shptr<Attribute_Definition> make_shared_Attribute_Definition(String const& name, Type_Enum type, Uptr<Constraint>&& constraint = Uptr<Constraint>());

} // namespace Saklib

#endif // ATTRIBUTE_CONSTRAINT_TYPE_H
