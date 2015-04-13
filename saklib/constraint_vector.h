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
            m_value_constraint(std::make_unique<value_constraint_type>(std::forward<Args>(args)...))
        {}

        ~Constraint() = default;

        Constraint(Constraint const& other) = delete;
        Constraint& operator=(Constraint const& other) = delete;

        //Constraint(Constraint && other) = default;
        //Constraint& operator=(Constraint && other) = default;

        // Interface
        //============================================================
        bool has_value_constraint() const
        {
            return m_value_constraint != nullptr;
        }
        value_constraint_type const* value_constraint() const
        {
            return m_value_constraint.get();
        }

        void set_value_constraint(value_constraint_type && constraint)
        {
            if (m_value_constraint != nullptr)
                *m_value_constraint = constraint;
            else
                m_value_constraint = std::make_unique<value_constraint_type>(constraint);
        }
        template <typename... Args>
        void set_value_constraint(Args&&... args)
        {
            return m_value_constraint.set_value(value_constraint_type(std::forward<Args>(args)...));
        }
        void unset_value_constraint()
        {
            return m_value_constraint.reset();
        }

    private:
        //Maybe<size_type> m_max_length;
        Uptr<value_constraint_type>  m_value_constraint;
    };
} // namespace Saklib



#endif // CONSTRAINT_VECTOR_H
