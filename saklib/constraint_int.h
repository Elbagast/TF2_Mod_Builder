#ifndef CONSTRAINT_INT_H
#define CONSTRAINT_INT_H

#include "constraint.h"
#include "maybe.h"

namespace Saklib
{
    /*
    Constraint<Int>
    ====================================================================================================

    */
    template <>
    class Constraint<Int>
    {
    public:
        // Special 6
        //============================================================
        Constraint(Int minimum, Int maximum);
        ~Constraint() = default;

        Constraint(Constraint const& other) = default;
        Constraint& operator=(Constraint const& other) = default;

        //Constraint(Constraint && other) = default;
        //Constraint& operator=(Constraint && other) = default;

        // Interface
        //============================================================
        bool has_min_value() const;
        bool has_max_value() const;

        Int min_value() const;
        Int max_value() const;

        void set_min_value(Int value);
        void set_max_value(Int value);

        void unset_min_value();
        void unset_max_value();

    private:
        Maybe<Int> m_min;
        Maybe<Int> m_max;
    };
} // namespace Saklib


// Implementation
//----------------------------------------------------------------------------------------------------
// Special 6
//============================================================
inline
Saklib::Constraint<Saklib::Int>::Constraint(Int minimum, Int maximum):
    m_min(minimum),
    m_max(maximum)
{}

// Interface
//============================================================
inline
bool Saklib::Constraint<Saklib::Int>::has_min_value() const
{
    return m_min.used();
}

inline
bool Saklib::Constraint<Saklib::Int>::has_max_value() const
{
    return m_max.used();
}

inline
Saklib::Int Saklib::Constraint<Saklib::Int>::min_value() const
{
    return m_min.value();
}

inline
Saklib::Int Saklib::Constraint<Saklib::Int>::max_value() const
{
    return m_max.value();
}

inline
void Saklib::Constraint<Saklib::Int>::set_min_value(Int value)
{
    m_min.set_value(value);
}

inline
void Saklib::Constraint<Saklib::Int>::set_max_value(Int value)
{
    m_max.set_value(value);
}

inline
void Saklib::Constraint<Saklib::Int>::unset_min_value()
{
    m_min.unset_value();
}

inline
void Saklib::Constraint<Saklib::Int>::unset_max_value()
{
    m_max.unset_value();
}

#endif // CONSTRAINT_INT_H
