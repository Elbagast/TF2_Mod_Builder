#ifndef CONSTRAINT_TYPE_VECTOR_H
#define CONSTRAINT_TYPE_VECTOR_H

#include "constraint_type.h"
#include "maybe.h"

namespace Saklib
{
    /*
    Constraint_Type<Vector<T>>
    ====================================================================================================

    */
    template <typename T>
    class Constraint_Type<Vector<T>>
    {
    public:
        using value_constraint_type = Constraint_Type<T>;

        // Special 6
        //============================================================
        template <typename... Args>
        Constraint_Type(Args&&... args):
            m_value_constraint(value_constraint_type(std::forward<Args>(args)...))
        {}

        ~Constraint_Type() = default;

        Constraint_Type(Constraint_Type const& other) = default;
        Constraint_Type& operator=(Constraint_Type const& other) = default;

        //Constraint_Type(Constraint_Type && other) = default;
        //Constraint_Type& operator=(Constraint_Type && other) = default;

        // Interface
        //============================================================
        bool has_value_constraint() const
        {
            return m_value_constraint.used();
        }
        value_constraint_type const& value_constraint() const
        {
            return m_value_constraint.value();
        }

        void set_value_constraint(value_constraint_type const& constraint)
        {
            return m_value_constraint.set_value(constraint);
        }
        template <typename... Args>
        void set_value_constraint(Args&&... args)
        {
            return m_value_constraint.set_value(value_constraint_type(std::forward<Args>(args)...));
        }
        void unset_value_constraint()
        {
            return m_value_constraint.unset_value();
        }

    private:
        //Maybe<size_type> m_max_length;
        Maybe<value_constraint_type>  m_value_constraint;
    };
} // namespace Saklib



#endif // CONSTRAINT_TYPE_VECTOR_H
