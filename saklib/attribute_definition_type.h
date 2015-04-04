#ifndef ATTRIBUTE_DEFINITION_TYPE_H
#define ATTRIBUTE_DEFINITION_TYPE_H

#include "types.h"
#include "all_type_traits.h"
#include "attribute_definition.h"
//#include "constraint_type.h"

namespace Saklib
{
    /*
    Attribute_Definition
    ====================================================================================================
    Class the contains flyweight information to create a given Attribute based on it.

    Without any specific type data this is a useless class - so it makes no sense if it containts no 
    constraint info.
    */
    template <typename T>
    class Attribute_Definition_Type:
        public Attribute_Definition
    {
    public:
        using stored_type = T;
        using stored_type_traits = Type_Traits<stored_type>;

        //using constraint_type = Constraint_Type < stored_type >;

        // Special 6
        //============================================================
        explicit Attribute_Definition_Type(String const& name) ://, Uptr<Constraint>& constraint = Uptr<Constraint>()) :
            Attribute_Definition(),
            m_name(name)//,
            //m_constraint(assess_constraint_arg(constraint))
        {}
        /*
        Attribute_Definition_Type(String const& name) ://, Uptr<constraint_type>& constraint = Uptr<constraint_type>()) :
            Attribute_Definition(),
            m_name(name)//,
            //m_constraint(constraint.release())
        {}
        Attribute_Definition_Type(String const& name) ://, Uptr<constraint_type>&& constraint = Uptr<constraint_type>()) :
            Attribute_Definition(),
            m_name(name)//,
            //m_constraint(std::forward<Uptr<constraint_type>>(constraint))
        {}
        */
        ~Attribute_Definition_Type() = default;

        Attribute_Definition_Type(Attribute_Definition_Type const& other) = delete;
        Attribute_Definition_Type& operator=(Attribute_Definition_Type const& other) = delete;

        // hides Attribute_Definition::constraint when using this exact class
        //constraint_type const*const constraint() const  { return m_constraint.get(); }

    protected:
        // Virtuals
        //============================================================
        String const& v_name() const override  { return m_name; }
        Type_Enum v_type_enum() const override      { return stored_type_traits::type_enum(); }
        String v_type_string() const override  { return stored_type_traits::type_string(); }
        //constraint_type const*const v_constraint() const override   { return m_constraint.get(); }

        //bool v_is_constrained() const override      { return m_constraint != nullptr; }

    private:
        /*
        Uptr < constraint_type > assess_constraint_arg(Uptr<Constraint>& constraint)
        {
            if (constraint != nullptr && constraint->type_enum() == stored_type_traits::type_enum())
                return Uptr < constraint_type >(dynamic_cast<constraint_type*>(constraint.release()));
            else
                return Uptr < constraint_type >();
        }
        */
        String const m_name;
        //Uptr < constraint_type > const m_constraint;
    };
    
} // namespace Saklib

#endif // ATTRIBUTE_DEFINITION_TYPE_H
