#ifndef CONSTRAINT_DOUBLE_H
#define CONSTRAINT_DOUBLE_H

#include "constraint.h"
#include "maybe.h"

namespace saklib
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
        Constraint(Double minimum, Double maximum, Double step_size, size_type decimal_places);
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
        bool has_decimal_places() const;

        Double min_value() const;
        Double max_value() const;
        Double step_size() const;
        size_type decimal_places() const;

        void set_min_value(Double value);
        void set_max_value(Double value);
        void set_step_size(Double value);
        void set_decimal_places(size_type value);

        void unset_min_value();
        void unset_max_value();
        void unset_step_size();
        void unset_decimal_places();

    private:
        Maybe<Double> m_min;
        Maybe<Double> m_max;
        Maybe<Double> m_step_size;
        Maybe<size_type> m_decimal_places;
    };
} // namespace saklib


// Implementation
//----------------------------------------------------------------------------------------------------
// Special 6
//============================================================
inline
saklib::Constraint<saklib::Double>::Constraint(Double minimum, Double maximum, Double step_size, size_type decimal_places):
    m_min(minimum),
    m_max(maximum),
    m_step_size(step_size),
    m_decimal_places(decimal_places)
{}

// Interface
//============================================================
inline
bool saklib::Constraint<saklib::Double>::has_min_value() const
{
    return m_min.used();
}

inline
bool saklib::Constraint<saklib::Double>::has_max_value() const
{
    return m_max.used();
}

inline
bool saklib::Constraint<saklib::Double>::has_step_size() const
{
    return m_step_size.used();
}

inline
bool saklib::Constraint<saklib::Double>::has_decimal_places() const
{
    return m_decimal_places.used();
}

inline
saklib::Double saklib::Constraint<saklib::Double>::min_value() const
{
    return m_min.value();
}

inline
saklib::Double saklib::Constraint<saklib::Double>::max_value() const
{
    return m_max.value();
}

inline
saklib::Double saklib::Constraint<saklib::Double>::step_size() const
{
    return m_step_size.value();
}

inline
saklib::size_type saklib::Constraint<saklib::Double>::decimal_places() const
{
    return m_decimal_places.value();
}

inline
void saklib::Constraint<saklib::Double>::set_min_value(Double value)
{
    m_min.set_value(value);
}

inline
void saklib::Constraint<saklib::Double>::set_max_value(Double value)
{
    m_max.set_value(value);
}

inline
void saklib::Constraint<saklib::Double>::set_step_size(Double value)
{
    m_step_size.set_value(value);
}

inline
void saklib::Constraint<saklib::Double>::set_decimal_places(size_type value)
{
    m_decimal_places.set_value(value);
}

inline
void saklib::Constraint<saklib::Double>::unset_min_value()
{
    m_min.unset_value();
}

inline
void saklib::Constraint<saklib::Double>::unset_max_value()
{
    m_max.unset_value();
}


inline
void saklib::Constraint<saklib::Double>::unset_step_size()
{
    m_step_size.unset_value();
}

inline
void saklib::Constraint<saklib::Double>::unset_decimal_places()
{
    m_decimal_places.unset_value();
}

#endif // CONSTRAINT_DOUBLE_H
