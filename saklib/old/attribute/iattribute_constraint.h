#ifndef SAKLIB_IATTRIBUTE_CONSTRAINT_H
#define SAKLIB_IATTRIBUTE_CONSTRAINT_H

#include "../types.h"
#include "../common_traits.h"
#include "specialisation_selector.h"

namespace saklib
{
    using saklib::size_type;

    /*
    IAttribute_Constraint_R<T>
    ====================================================================================================
    Interface for editing constraints on a value of type T.
    */
    template <typename T, Specialisation S = Specialisation_Selector<T>::value>
    class IAttribute_Constraint_R
    {
    public:
        // Typedefs
        //============================================================
       COMMON_TRAITS_TYPEDEFS_T

        // Special 6
        //============================================================
        virtual ~IAttribute_Constraint_R() = default;

        // Interface
        //============================================================
        bool can_set_value_to(stored_type_const_arg value) const    { return v_can_set_value_to(value); }
        stored_type initial_value() const                           { return v_initial_value(); }

    protected:
        // Virtuals
        //============================================================
        virtual stored_type v_initial_value() const = 0;
        virtual bool v_can_set_value_to(stored_type_const_arg value) const = 0;
    };

    /*
    IAttribute_Constraint_RW<T>
    ====================================================================================================
    Interface for editing constraints on a value of type T.
    */
    template <typename T, Specialisation S = Specialisation_Selector<T>::value>
    class IAttribute_Constraint_RW :
            public virtual IAttribute_Constraint_R<T>
    {
    public:
        // Typedefs
        //============================================================
        COMMON_TRAITS_TYPEDEFS_T

        // Special 6
        //============================================================
        ~IAttribute_Constraint_RW() override = default;

        // Interface
        //============================================================
        void set_initial_value(stored_type_const_arg value)     { return v_set_initial_value(value); }

    protected:
        // Virtuals
        //============================================================
        virtual void v_set_initial_value(stored_type_const_arg value) = 0;
    };


    //--------------------------------------------------------------------------------------------------------------
    /*
    IAttribute_Constraint_R<int>
    ====================================================================================================
    Interface for editing constraints on a value of type T.
    */
    template <typename T>
    class IAttribute_Constraint_R<T, Specialisation::integer_type>
    {
    public:
        // Typedefs
        //============================================================
        COMMON_TRAITS_TYPEDEFS_T

        // Special 6
        //============================================================
        virtual ~IAttribute_Constraint_R() = default;

        // Interface
        //============================================================
        bool can_set_value_to(stored_type_const_arg value) const    { return v_can_set_value_to(value); }
        stored_type initial_value() const                           { return v_initial_value(); }
        stored_type lowest_value() const                            { return v_lowest_value(); }
        stored_type highest_value() const                           { return v_highest_value(); }

    protected:
        // Virtuals
        //============================================================
        virtual bool v_can_set_value_to(stored_type_const_arg value) const = 0;
        virtual stored_type v_initial_value() const = 0;
        virtual stored_type v_lowest_value() const = 0;
        virtual stored_type v_highest_value() const = 0;
    };

    /*
    IAttribute_Constraint_RW<int>
    ====================================================================================================
    Interface for editing constraints on a value of type T.
    */
    template <typename T>
    class IAttribute_Constraint_RW<T, Specialisation::integer_type> :
            public virtual IAttribute_Constraint_R<T, Specialisation::integer_type>
    {
    public:
        // Typedefs
        //============================================================
        COMMON_TRAITS_TYPEDEFS_T

        // Special 6
        //============================================================
        ~IAttribute_Constraint_RW() override = default;

        // Interface
        //============================================================
        void set_initial_value(stored_type_const_arg value)     { return v_set_initial_value(value); }
        void set_highest_value(stored_type_const_arg value)     { return v_set_highest_value(value); }
        void set_lowest_value(stored_type_const_arg value)      { return v_set_lowest_value(value); }

    protected:
        // Virtuals
        //============================================================
        virtual void v_set_initial_value(stored_type_const_arg value) = 0;
        virtual void v_set_highest_value(stored_type_const_arg value) = 0;
        virtual void v_set_lowest_value(stored_type_const_arg value) = 0;
    };

    //--------------------------------------------------------------------------------------------------------------
    /*
    IAttribute_Constraint_R<int>
    ====================================================================================================
    Interface for editing constraints on a value of type T.
    */
    template <typename T>
    class IAttribute_Constraint_R<T, Specialisation::floating_point_type>
    {
    public:
        // Typedefs
        //============================================================
        COMMON_TRAITS_TYPEDEFS_T

        // Special 6
        //============================================================
        virtual ~IAttribute_Constraint_R() = default;

        // Interface
        //============================================================
        bool can_set_value_to(stored_type_const_arg value) const    { return v_can_set_value_to(value); }
        stored_type initial_value() const                           { return v_initial_value(); }
        stored_type lowest_value() const                            { return v_lowest_value(); }
        stored_type highest_value() const                           { return v_highest_value(); }
        size_type decimal_places() const                            { return v_decimal_places(); }

    protected:
        // Virtuals
        //============================================================
        virtual bool v_can_set_value_to(stored_type_const_arg value) const = 0;
        virtual stored_type v_initial_value() const = 0;
        virtual stored_type v_lowest_value() const = 0;
        virtual stored_type v_highest_value() const = 0;
        virtual size_type v_decimal_places() const = 0;
    };

    /*
    IAttribute_Constraint_RW<double>
    ====================================================================================================
    Interface for editing constraints on a value of type T.
    */
    template <typename T>
    class IAttribute_Constraint_RW<T, Specialisation::floating_point_type> :
            public virtual IAttribute_Constraint_R<T, Specialisation::floating_point_type>
    {
    public:
        // Typedefs
        //============================================================
        COMMON_TRAITS_TYPEDEFS_T

        // Special 6
        //============================================================
        ~IAttribute_Constraint_RW() override = default;

        // Interface
        //============================================================
        void set_initial_value(stored_type_const_arg value)     { return v_set_initial_value(value); }
        void set_highest_value(stored_type_const_arg value)     { return v_set_highest_value(value); }
        void set_lowest_value(stored_type_const_arg value)      { return v_set_lowest_value(value); }
        void set_decimal_places(size_type value)                { return v_set_decimal_places(value); }


    protected:
        // Virtuals
        //============================================================
        virtual void v_set_initial_value(stored_type_const_arg value) = 0;
        virtual void v_set_highest_value(stored_type_const_arg value) = 0;
        virtual void v_set_lowest_value(stored_type_const_arg value) = 0;
        virtual void v_set_decimal_places(size_type value) = 0;
    };


} // namespace saklib

#endif // SAKLIB_IATTRIBUTE_CONSTRAINT_H

