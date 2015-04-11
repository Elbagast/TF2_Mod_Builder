#ifndef CONSTRAINT_DOUBLE_H
#define CONSTRAINT_DOUBLE_H

#include "constraint.h"
#include "maybe.h"

namespace Saklib
{
    /*
    Constraint<Double>
    ====================================================================================================

    */
    template <>
    class Constraint<Double>
    {
    public:
        // Special 6
        //============================================================
        Constraint(Double minimum, Double maximum);
        ~Constraint() = default;

        Constraint(Constraint const& other) = default;
        Constraint& operator=(Constraint const& other) = default;

        //Constraint(Constraint && other) = default;
        //Constraint& operator=(Constraint && other) = default;

        // Interface
        //============================================================
        bool has_min_value() const;
        bool has_max_value() const;

        Double min_value() const;
        Double max_value() const;

        void set_min_value(Double value);
        void set_max_value(Double value);

        void unset_min_value();
        void unset_max_value();

    private:
        Maybe<Double> m_min;
        Maybe<Double> m_max;
    };
} // namespace Saklib


// Implementation
//----------------------------------------------------------------------------------------------------
// Special 6
//============================================================
inline
Saklib::Constraint<Saklib::Double>::Constraint(Double minimum, Double maximum):
    m_min(minimum),
    m_max(maximum)
{}

// Interface
//============================================================
inline
bool Saklib::Constraint<Saklib::Double>::has_min_value() const
{
    return m_min.used();
}

inline
bool Saklib::Constraint<Saklib::Double>::has_max_value() const
{
    return m_max.used();
}

inline
Saklib::Double Saklib::Constraint<Saklib::Double>::min_value() const
{
    return m_min.value();
}

inline
Saklib::Double Saklib::Constraint<Saklib::Double>::max_value() const
{
    return m_max.value();
}

inline
void Saklib::Constraint<Saklib::Double>::set_min_value(Double value)
{
    m_min.set_value(value);
}

inline
void Saklib::Constraint<Saklib::Double>::set_max_value(Double value)
{
    m_max.set_value(value);
}

inline
void Saklib::Constraint<Saklib::Double>::unset_min_value()
{
    m_min.unset_value();
}

inline
void Saklib::Constraint<Saklib::Double>::unset_max_value()
{
    m_max.unset_value();
}

#endif // CONSTRAINT_DOUBLE_H
