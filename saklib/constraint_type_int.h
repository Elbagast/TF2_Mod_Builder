#ifndef CONSTRAINT_TYPE_INT_H
#define CONSTRAINT_TYPE_INT_H

#include "constraint_type.h"
#include "maybe.h"

namespace Saklib
{
    /*
    Constraint_Type<Int>
    ====================================================================================================

    */
    template <>
    class Constraint_Type<Int>
    {
    public:
        // Special 6
        //============================================================
        Constraint_Type() = default;
        ~Constraint_Type() = default;

        Constraint_Type(Constraint_Type const& other) = default;
        Constraint_Type& operator=(Constraint_Type const& other) = default;

        //Constraint_Type(Constraint_Type && other) = default;
        //Constraint_Type& operator=(Constraint_Type && other) = default;

        // Interface
        //============================================================
        bool has_min_value() const
        {
            return m_min.used();
        }
        bool has_max_value() const
        {
            return m_max.used();
        }
        //bool has_default_value() const
        //{
        //    return m_default.used();
        //}

        Int min_value() const
        {
            return m_min.value();
        }
        Int max_value() const
        {
            return m_max.value();
        }
        //Int default_value() const
        //{
         //   return m_default.value();
        //}

        void set_min_value(Int value)
        {
            m_min.set_value(value);
        }
        void set_max_value(Int value)
        {
            m_max.set_value(value);
        }
        //void set_default_value(Int value)
        //{
       //     m_default.set_value(value);
        //}

        void unset_min_value()
        {
            m_min.unset_value();
        }
        void unset_max_value()
        {
            m_max.unset_value();
        }
        //void unset_default_value()
        //{
         //   m_default.unset_value();
        //}

    private:
        Maybe<Int> m_min;
        Maybe<Int> m_max;
        //Maybe<stored_type> m_default;
    };
} // namespace Saklib



#endif // CONSTRAINT_TYPE_INT_H
