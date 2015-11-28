#ifndef ICONSTRAINT_H
#define ICONSTRAINT_H

#include "common_traits.h"

namespace saklib
{
    /*
    IConstraint_Minimum<T>
    ====================================================================================================

    hmm the inheritance is complicating things


    */
    template <typename T>
    class IConstraint_Minimum
    {
    public:
        using stored_type = typename Common_Traits<T>::stored_type;
        using value_type = typename Common_Traits<T>::value_type;

        using stored_type_const_arg = typename Common_Traits<T>::stored_type_const_arg;
        using stored_type_const_return = typename Common_Traits<T>::stored_type_const_return;

        using value_type_const_arg = typename Common_Traits<T>::value_type_const_arg;
        using value_type_const_return = typename Common_Traits<T>::value_type_const_return;

        // Special 6
        //============================================================
        virtual ~IConstraint_Minimum() = default;


        // Interface
        //============================================================
        static stored_type default_initial_value()                  { return Common_Traits<T>::make_default_value(); }
        stored_type initial_value() const                           { return v_initial_value(); }
        bool can_set_value_to(stored_type_const_arg value) const    { return v_can_set_value_to(value); }

    protected:
        virtual stored_type v_initial_value() const = 0;
        virtual bool v_can_set_value_to(stored_type_const_arg value) const = 0;
    };

    /*
    IConstraint_Specialised<T>
    ====================================================================================================

    */
    template <typename T>
    class IConstraint_Specialised
    {
    public:
        // Special 6
        //============================================================
        ~IConstraint() override = default;

    };


    /*
    IConstraint<T>
    ====================================================================================================

    */
    template <typename T>
    class IConstraint :
            public IConstraint_Minimum<T>
            ,public IConstraint_Specialised<T>
    {
    public:
        // Special 6
        //============================================================
        ~IConstraint() override = default;

    };

    /*
    No_Constraint<T>
    ====================================================================================================

    */
    template <typename T>
    class No_Constraint :
            public IConstraint<T>
    {
    public:
        // Special 6
        //============================================================
        ~No_Constraint() override = default;

    protected:
        stored_type v_initial_value() const                             { return default_initial_value(); }
        bool v_can_set_value_to(stored_type_const_arg /*value*/) const  { return true; }
    };

    /*
    Initial_Value_Constraint<T>
    ====================================================================================================

    */
    template <typename T>
    class Initial_Value_Constraint :
            public IConstraint<T>
    {
    public:
        // Special 6
        //============================================================
        Initial_Value_Constraint(stored_type_const_arg value):
            IConstraint<T>(),
            m_initial_value(value)
        {}
        ~Initial_Value_Constraint() override = default;

    protected:
        stored_type v_initial_value() const                             { return m_initial_value; }
        bool v_can_set_value_to(stored_type_const_arg /*value*/) const  { return true; }
    private:
        stored_type m_initial_value;
    };


} // namespace saklib

#endif // ICONSTRAINT_H

