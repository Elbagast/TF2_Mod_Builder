#ifndef CONSTRAINT_TYPE_H
#define CONSTRAINT_TYPE_H

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
    class Constraint_Type<Vector<T>>
    {
    public:
        bool vector_can_be(Vector<T> const& value)  { return v_vector_can_be(value); }
        bool component_can_be(T const& value)       { return v_component_can_be(value); }

    protected:
        virtual ~Constraint_Type() = default;

        virtual bool v_vector_can_be(Vector<T> const& value) = 0;
        virtual bool v_component_can_be(T const& value) = 0;
    };


    template <typename T>
    class Unconstrained:
            public Constraint_Type<T>
    {
    public:
        ~Unconstrained() override = default;

    protected:
        bool v_value_can_be(T const& /*value*/) override    { return true; }
    };

    template <typename T>
    class Unconstrained<Vector<T>>:
            public Constraint_Type<Vector<T>>
    {
    public:
        ~Unconstrained() override = default;

    protected:
        bool v_vector_can_be(Vector<T> const& /*value*/) override   { return true; }
        bool v_component_can_be(T const& /*value*/) override        { return true; }
    };

    template <typename T>
    class Numeric_Range:
            public Constraint_Type<T>
    {
        // make sure T is a numeric type
        //static_assert()
    public:
        Numeric_Range(T lower_bound, T upper_bound, bool include_lower, bool include_upper):
            m_lower_bound(lower_bound),
            m_upper_bound(upper_bound),
            m_include_lower(include_lower),
            m_include_upper(include_upper)
        {}
        ~Numeric_Range() override = default;

        T lower_bound() const       { return m_lower_bound; }
        T upper_bound() const       { return m_lower_bound; }
        bool include_lower() const  { return m_include_lower; }
        bool include_upper() const  { return m_include_upper; }

    protected:
        bool v_value_can_be(T const& value) override
        {
            return more_than_lower(value) && less_than_upper(value);
        }
    private:
        bool more_than_lower(T const& value)
        {
            if (m_include_lower)
                return value >= m_lower_bound;
            else
                return value > m_lower_bound;
        }

        bool less_than_upper(T const& value)
        {
            if (m_include_upper)
                return value <= m_upper_bound;
            else
                return value < m_upper_bound;
        }

        T m_lower_bound;
        T m_upper_bound;
        bool m_include_lower;
        bool m_include_upper;
    };

    //Shptr<Attribute_Definition> make_shared_Attribute_Definition(String const& name, Type_Enum type);

    //Shptr<Attribute_Definition> make_shared_Attribute_Definition(String const& name, Type_Enum type, Uptr<Constraint>&& constraint = Uptr<Constraint>());

} // namespace Saklib

#endif // CONSTRAINT_TYPE_H
