#ifndef CONSTRAINT_VECTOR_H
#define CONSTRAINT_VECTOR_H

#include "constraint.h"
#include "maybe.h"

namespace Saklib
{
    /*
    Constraint<Vector<T>>
    ====================================================================================================

    */
    template <typename T>
    class Constraint<Vector<T>>
    {
    public:
        using value_constraint_type = Constraint<T>;

        // Special 6
        //============================================================
        template <typename... Args>
        Constraint(Args&&... args):
            m_value_constraint(value_constraint_type(std::forward<Args>(args)...))
        {}

        ~Constraint() = default;

        Constraint(Constraint const& other) = default;
        Constraint& operator=(Constraint const& other) = default;

        //Constraint(Constraint && other) = default;
        //Constraint& operator=(Constraint && other) = default;

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



#endif // CONSTRAINT_VECTOR_H
