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
        Constraint(Int minimum, Int maximum, Int step_size = 1);
        ~Constraint() = default;

        Constraint(Constraint const& other) = default;
        Constraint& operator=(Constraint const& other) = default;

        //Constraint(Constraint && other) = default;
        //Constraint& operator=(Constraint && other) = default;

        // Interface
        //============================================================
        bool has_min_value() const;
        bool has_max_value() const;
        bool has_step_size() const;

        Int min_value() const;
        Int max_value() const;
        Int step_size() const;

        void set_min_value(Int value);
        void set_max_value(Int value);
        void set_step_size(Int value);

        void unset_min_value();
        void unset_max_value();
        void unset_step_size();

    private:
        Maybe<Int> m_min;
        Maybe<Int> m_max;
        Maybe<Int> m_step_size;
    };
} // namespace Saklib


// Implementation
//----------------------------------------------------------------------------------------------------
// Special 6
//============================================================
inline
Saklib::Constraint<Saklib::Int>::Constraint(Int minimum, Int maximum, Int step_size):
    m_min(minimum),
    m_max(maximum),
    m_step_size(step_size)
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
bool Saklib::Constraint<Saklib::Int>::has_step_size() const
{
    return m_step_size.used();
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
Saklib::Int Saklib::Constraint<Saklib::Int>::step_size() const
{
    return m_step_size.value();
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
void Saklib::Constraint<Saklib::Int>::set_step_size(Int value)
{
    m_step_size.set_value(value);
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

inline
void Saklib::Constraint<Saklib::Int>::unset_step_size()
{
    m_step_size.unset_value();
}

#endif // CONSTRAINT_INT_H
