#ifndef ICONSTRAINT_INT_H
#define ICONSTRAINT_INT_H

#include <limits>
#include <cassert>

namespace saklib
{
    /*
    ====================================================================================================

    */
    template <typename Integer_Type>
    class IConstraint_Int
    {
    public:
        using integer_type = Integer_Type;

        static_assert(std::numeric_limits<integer_type>::is_specialized
                      && std::numeric_limits<integer_type>::is_integer
                      , "IConstraint_Int can only use an integer type");

        virtual ~IConstraint_Int() = default;

        bool is_valid_value(integer_type value) const       { return value <= highest_value() && value >= lowest_value(); }

        integer_type highest_value() const                  { return v_highest_value(); }
        integer_type lowest_value() const                   { return v_lowest_value(); }
        integer_type initial_value() const                  { return v_initial_value(); }

        static integer_type default_highest_value() const   { return std::numeric_limits<integer_type>::max(); }
        static integer_type default_lowest_value() const    { return std::numeric_limits<integer_type>::lowest(); }
        static integer_type default_initial_value() const   { return integer_type{0}; }

    protected:
        //virtual bool v_is_valid_value(integer_type value) const = 0;
        virtual integer_type v_highest_value() const = 0;
        virtual integer_type v_lowest_value() const = 0;
        virtual integer_type v_initial_value() const = 0;
    };

    /*
    ====================================================================================================

    */
    template <typename Integer_Type>
    class Default_Constraint_Int :
            public IConstraint_Int<Integer_Type>
    {
    public:
        ~Default_Constraint_Int() override = default;

    protected:
        //bool v_is_valid_value(integer_type value) const override    { return value <= highest_value() && value >= lowest_value(); }
        integer_type v_highest_value() const override               { return default_highest_value(); }
        integer_type v_lowest_value() const override                { return default_lowest_value(); }
        integer_type v_default_value() const override               { return default_initial_value(); }
    };



    // hmmmmmmmmm

    /*
    ====================================================================================================

    */
    template <typename Integer_Type>
    class Int_Max :
            public IConstraint_Int<Integer_Type>
    {
    public:
        explicit Int_Max(integer_type max):
            m_max(max)
        {

        }
        ~Int_Max() override = default;

    protected:
        //bool v_is_valid_value(integer_type value) const override    { return value <= m_max && value >= lowest_value(); }
        integer_type v_highest_value() const override               { return m_max; }
        integer_type v_lowest_value() const override                { return default_lowest_value(); }
        integer_type v_default_value() const override               { return default_initial_value(); }
    private:
        integer_type m_max;
    };

    /*
    ====================================================================================================

    */
    template <typename Integer_Type>
    class Int_Min :
            public IConstraint_Int<Integer_Type>
    {
    public:
        explicit Int_Max(integer_type min):
            m_min(min)
        {

        }
        ~Int_Max() override = default;

    protected:
        //bool v_is_valid_value(integer_type value) const override    { return value <= m_max && value >= lowest_value(); }
        integer_type v_highest_value() const override               { return default_highest_value(); }
        integer_type v_lowest_value() const override                { return m_min; }
        integer_type v_default_value() const override               { return default_initial_value(); }
    private:
        integer_type m_min;
    };


} // namespace saklib

#endif // ICONSTRAINT_INT_H

