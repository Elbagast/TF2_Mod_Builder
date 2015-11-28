#ifndef SAKLIB_ATTRIBUTE_CONSTRAINT_H
#define SAKLIB_ATTRIBUTE_CONSTRAINT_H

#include <memory>
#include "iattribute.h"
#include "../unique_traits.h"

namespace saklib
{
    namespace local
    {
        /*
        Attribute_No_Constraint<T>
        ====================================================================================================
        */
        template <typename T, Specialisation S = Specialisation_Selector<T>::value>
        class Attribute_No_Constraint_R :
                public virtual IAttribute_Constraint_R<T, S>
        {
        public:
            // Typedefs
            //============================================================
            COMMON_TRAITS_TYPEDEFS_T

            // Special 6
            //============================================================
            Attribute_No_Constraint_R():
                IAttribute_Constraint_R<T, S>()
            {}
            virtual ~Attribute_No_Constraint_R() = default;

        protected:
            // Virtuals
            //============================================================
            bool v_can_set_value_to(stored_type_const_arg) const override   { return true; }
            stored_type v_initial_value() const override                    { return Common_Traits<T>::make_default_value(); }
            //void v_set_initial_value(stored_type_const_arg ) override       { }
        };


        /*
        Attribute_Constraint<T>
        ====================================================================================================
        */
        template <typename T, Specialisation S = Specialisation_Selector<T>::value>
        class Attribute_Constraint_RW :
                public virtual IAttribute_Constraint_RW<T, S>
        {
        public:
            // Typedefs
            //============================================================
            COMMON_TRAITS_TYPEDEFS_T

            // Special 6
            //============================================================
            Attribute_Constraint_RW():
                IAttribute_Constraint_RW<T, S>(),
                m_initial_value(Common_Traits<T>::make_default_value())
            {}
            explicit Attribute_Constraint_RW(stored_type_const_arg a_value):
                IAttribute_Constraint_RW<T>(),
                m_initial_value(a_value)
            {}
            ~Attribute_Constraint_RW() override = default;

        protected:
            // Virtuals
            //============================================================
            bool v_can_set_value_to(stored_type_const_arg) const override   { return true; }
            stored_type v_initial_value() const override                    { return m_initial_value; }
            void v_set_initial_value(stored_type_const_arg value) override  { m_initial_value = value; }
        private:
            stored_type m_initial_value;
        };

        //--------------------------------------------------------------------------------------------------------------
        /*
        Attribute_Constraint<T>
        ====================================================================================================
        */
        template <typename T>
        class Attribute_Constraint_RW<T, Specialisation::integer_type> :
                public virtual IAttribute_Constraint_RW<T>
        {
        public:
            // Typedefs
            //============================================================
            COMMON_TRAITS_TYPEDEFS_T

            // Special 6
            //============================================================
            Attribute_Constraint_RW():
                IAttribute_Constraint_RW<T>(),
                m_initial_value(saklib::Common_Traits<T>::make_default_value()),
                m_lowest_value(saklib::Unique_Traits<T>::default_lowest_value()),
                m_highest_value(saklib::Unique_Traits<T>::default_highest_value())

            {}
            Attribute_Constraint_RW(stored_type_const_arg a_initial,
                                    stored_type_const_arg a_lowest,
                                    stored_type_const_arg a_highest):
                Attribute_Constraint_RW()
            {
                v_set_initial_value(a_initial);
                v_set_lowest_value(a_lowest);
                v_set_highest_value(a_highest);
            }
            ~Attribute_Constraint_RW() override = default;

        protected:
            // Virtuals
            //============================================================
            bool v_can_set_value_to(stored_type_const_arg value) const override
            {
                return value > m_lowest_value && value < m_highest_value;
            }

            stored_type v_initial_value() const override                            { return m_initial_value; }
            stored_type v_lowest_value() const override                             { return m_lowest_value; }
            stored_type v_highest_value() const override                            { return m_highest_value; }

            void v_set_initial_value(stored_type_const_arg value) override
            {
                if (value > m_highest_value)
                {
                    m_initial_value = m_highest_value;
                }
                else if (value < m_lowest_value)
                {
                    m_initial_value = m_lowest_value;
                }
                else
                {
                    m_initial_value = value;
                }
            }
            void v_set_lowest_value(stored_type_const_arg value) override
            {
                if (value > m_highest_value)
                {
                    m_lowest_value = m_highest_value;
                }
                else
                {
                    m_lowest_value = value;
                    if (m_initial_value < m_lowest_value)
                    {
                        m_initial_value = m_lowest_value;
                    }
                }
            }
            void v_set_highest_value(stored_type_const_arg value) override
            {
                if (value < m_lowest_value)
                {
                    m_highest_value = m_lowest_value;
                }
                else
                {
                    m_highest_value = value;
                    if (m_initial_value > m_highest_value)
                    {
                        m_initial_value = m_highest_value;
                    }
                }
            }
        private:
            stored_type m_initial_value;
            stored_type m_highest_value;
            stored_type m_lowest_value;
        };


        //--------------------------------------------------------------------------------------------------------------
        /*
        Attribute_Constraint<T>
        ====================================================================================================
        */
        template <typename T>
        class Attribute_Constraint_RW<T, Specialisation::floating_point_type> :
                public virtual IAttribute_Constraint_RW<T>
        {
        public:
            // Typedefs
            //============================================================
            COMMON_TRAITS_TYPEDEFS_T

            // Special 6
            //============================================================
            Attribute_Constraint_RW():
                IAttribute_Constraint_RW<T>(),
                m_initial_value(saklib::Common_Traits<T>::make_default_value()),
                m_lowest_value(saklib::Unique_Traits<T>::default_lowest_value()),
                m_highest_value(saklib::Unique_Traits<T>::default_highest_value()),
                m_decimal_places(saklib::Unique_Traits<T>::default_decimal_places())
            {}
            Attribute_Constraint_RW(stored_type_const_arg a_initial,
                                    stored_type_const_arg a_lowest,
                                    stored_type_const_arg a_highest,
                                    size_type a_decimal_places):
                Attribute_Constraint_RW()
            {
                v_set_initial_value(a_initial);
                v_set_lowest_value(a_lowest);
                v_set_highest_value(a_highest);
                v_set_decimal_places(a_decimal_places);
            }
            ~Attribute_Constraint_RW() override = default;

        protected:
            // Virtuals
            //============================================================
            bool v_can_set_value_to(stored_type_const_arg value) const override
            {
                return value > m_lowest_value && value < m_highest_value;
            }

            stored_type v_initial_value() const override                            { return m_initial_value; }
            stored_type v_lowest_value() const override                             { return m_lowest_value; }
            stored_type v_highest_value() const override                            { return m_highest_value; }
            size_type v_decimal_places() const override                             { return m_decimal_places; }

            void v_set_initial_value(stored_type_const_arg value) override
            {
                if (value > m_highest_value)
                {
                    m_initial_value = m_highest_value;
                }
                else if (value < m_lowest_value)
                {
                    m_initial_value = m_lowest_value;
                }
                else
                {
                    m_initial_value = value;
                }
            }
            void v_set_lowest_value(stored_type_const_arg value) override
            {
                if (value > m_highest_value)
                {
                    m_lowest_value = m_highest_value;
                }
                else
                {
                    m_lowest_value = value;
                    if (m_initial_value < m_lowest_value)
                    {
                        m_initial_value = m_lowest_value;
                    }
                }
            }
            void v_set_highest_value(stored_type_const_arg value) override
            {
                if (value < m_lowest_value)
                {
                    m_highest_value = m_lowest_value;
                }
                else
                {
                    m_highest_value = value;
                    if (m_initial_value > m_highest_value)
                    {
                        m_initial_value = m_highest_value;
                    }
                }
            }
            void v_set_decimal_places(size_type value) override { m_decimal_places = value; }
        private:
            stored_type m_initial_value;
            stored_type m_highest_value;
            stored_type m_lowest_value;
            size_type m_decimal_places;
        };
    } // namespace local

    namespace remote
    {
        /*
        Attribute_Constraint_R<T>
        ====================================================================================================
        Interface for editing constraints on a value of type T.
        */
        template <typename T, Specialisation S = Specialisation_Selector<T>::value>
        class Attribute_Constraint_R :
                public virtual IAttribute_Constraint_R<T>
        {
        public:
            // Typedefs
            //============================================================
            COMMON_TRAITS_TYPEDEFS_T

            // Special 6
            //============================================================
            explicit Attribute_Constraint_R(IAttribute_Constraint_R<T> const& ar_constraint):
                IAttribute_Constraint_R<T>(),
                mr_constraint(ar_constraint)
            {}
            ~Attribute_Constraint_R() override = default;

        protected:
            // Virtuals
            //============================================================
            bool v_can_set_value_to(stored_type_const_arg value) const override { return mr_constraint.can_set_value_to(value); }
            stored_type v_initial_value() const override                        { return mr_constraint.initial_value(); }

        private:
            IAttribute_Constraint_R<T> const& mr_constraint;
        };

        /*
        Attribute_Constraint_RW<T>
        ====================================================================================================
        Interface for editing constraints on a value of type T.
        */
        template <typename T, Specialisation S = Specialisation_Selector<T>::value>
        class Attribute_Constraint_RW :
                public virtual IAttribute_Constraint_RW<T>
        {
        public:
            // Typedefs
            //============================================================
            COMMON_TRAITS_TYPEDEFS_T

            // Special 6
            //============================================================
            explicit Attribute_Constraint_RW(IAttribute_Constraint_RW<T>& ar_constraint):
                IAttribute_Constraint_RW<T>(),
                mr_constraint(ar_constraint)
            {}
            ~Attribute_Constraint_RW() override = default;

        protected:
            // Virtuals
            //============================================================
            bool v_can_set_value_to(stored_type_const_arg value) const override { return mr_constraint.can_set_value_to(value); }
            stored_type v_initial_value() const override                        { return mr_constraint.initial_value(); }
            void v_set_initial_value(stored_type_const_arg value) override      { mr_constraint.v_set_initial_value(value); }

        private:
            IAttribute_Constraint_RW<T>& mr_constraint;
        };

        //--------------------------------------------------------------------------------------------------------------
        //--------------------------------------------------------------------------------------------------------------
        /*
        Attribute_Constraint_R<T, Specialisation::integer_type>
        ====================================================================================================
        */
        template <typename T>
        class Attribute_Constraint_R<T, Specialisation::integer_type> :
                public virtual IAttribute_Constraint_R<T>
        {
        public:
            // Typedefs
            //============================================================
            COMMON_TRAITS_TYPEDEFS_T

            // Special 6
            //============================================================
            explicit Attribute_Constraint_R(IAttribute_Constraint_R<T, Specialisation::integer_type> const& ar_constraint):
                IAttribute_Constraint_R<T>(),
                mr_constraint(ar_constraint)
            {}
            ~Attribute_Constraint_R() override = default;

        protected:
            // Virtuals
            //============================================================
            bool v_can_set_value_to(stored_type_const_arg value) const override { return mr_constraint.can_set_value_to(value); }

            stored_type v_initial_value() const override                        { return mr_constraint.initial_value(); }
            stored_type v_lowest_value() const override                         { return mr_constraint.lowest_value(); }
            stored_type v_highest_value() const override                        { return mr_constraint.highest_value(); }
        private:
            IAttribute_Constraint_R<T> const& mr_constraint;
        };

        /*
        Attribute_Constraint_RW<T, Specialisation::integer_type>
        ====================================================================================================
        */
        template <typename T>
        class Attribute_Constraint_RW<T, Specialisation::integer_type> :
                public virtual IAttribute_Constraint_RW<T>
        {
        public:
            // Typedefs
            //============================================================
            COMMON_TRAITS_TYPEDEFS_T

            // Special 6
            //============================================================
            explicit Attribute_Constraint_RW(IAttribute_Constraint_RW<T, Specialisation::integer_type>& ar_constraint):
                IAttribute_Constraint_RW<T>(),
                mr_constraint(ar_constraint)
            {}
            ~Attribute_Constraint_RW() override = default;

        protected:
            // Virtuals
            //============================================================
            bool v_can_set_value_to(stored_type_const_arg value) const override { return mr_constraint.can_set_value_to(value); }

            stored_type v_initial_value() const override                        { return mr_constraint.initial_value(); }
            stored_type v_lowest_value() const override                         { return mr_constraint.lowest_value(); }
            stored_type v_highest_value() const override                        { return mr_constraint.highest_value(); }

            void v_set_initial_value(stored_type_const_arg value) override      { mr_constraint.set_initial_value(value); }
            void v_set_lowest_value(stored_type_const_arg value) override       { mr_constraint.set_lowest_value(value); }
            void v_set_highest_value(stored_type_const_arg value) override      { mr_constraint.set_highest_value(value); }
        private:
            IAttribute_Constraint_RW<T>& mr_constraint;
        };

        //--------------------------------------------------------------------------------------------------------------
        //--------------------------------------------------------------------------------------------------------------
        /*
        Attribute_Constraint_R<T, Specialisation::floating_point_type>
        ====================================================================================================
        */
        template <typename T>
        class Attribute_Constraint_R<T, Specialisation::floating_point_type> :
                public virtual IAttribute_Constraint_R<T>
        {
        public:
            // Typedefs
            //============================================================
            COMMON_TRAITS_TYPEDEFS_T

            // Special 6
            //============================================================
            explicit Attribute_Constraint_R(IAttribute_Constraint_R<T> const& ar_constraint):
                IAttribute_Constraint_R<T>(),
                mr_constraint(ar_constraint)
            {}
            ~Attribute_Constraint_R() override = default;

        protected:
            // Virtuals
            //============================================================
            bool v_can_set_value_to(stored_type_const_arg value) const override { return mr_constraint.can_set_value_to(value); }

            stored_type v_initial_value() const override                        { return mr_constraint.initial_value(); }
            stored_type v_lowest_value() const override                         { return mr_constraint.lowest_value(); }
            stored_type v_highest_value() const override                        { return mr_constraint.highest_value(); }
            size_type v_decimal_places() const override                         { return mr_constraint.decimal_places(); }
        private:
            IAttribute_Constraint_R<T> const& mr_constraint;
        };

        /*
        Attribute_Constraint_RW<T, Specialisation::floating_point_type>
        ====================================================================================================
        */
        template <typename T>
        class Attribute_Constraint_RW<T, Specialisation::floating_point_type> :
                public virtual IAttribute_Constraint_RW<T>
        {
        public:
            // Typedefs
            //============================================================
            COMMON_TRAITS_TYPEDEFS_T

            // Special 6
            //============================================================
            explicit Attribute_Constraint_RW(IAttribute_Constraint_RW<T>& ar_constraint):
                IAttribute_Constraint_RW<T>(),
                mr_constraint(ar_constraint)
            {}
            ~Attribute_Constraint_RW() override = default;

        protected:
            // Virtuals
            //============================================================
            bool v_can_set_value_to(stored_type_const_arg value) const override { return mr_constraint.can_set_value_to(value); }

            stored_type v_initial_value() const override                        { return mr_constraint.initial_value(); }
            stored_type v_lowest_value() const override                         { return mr_constraint.lowest_value(); }
            stored_type v_highest_value() const override                        { return mr_constraint.highest_value(); }
            size_type v_decimal_places() const override                         { return mr_constraint.decimal_places(); }

            void v_set_initial_value(stored_type_const_arg value) override      { mr_constraint.set_initial_value(value); }
            void v_set_lowest_value(stored_type_const_arg value) override       { mr_constraint.set_lowest_value(value); }
            void v_set_highest_value(stored_type_const_arg value) override      { mr_constraint.set_highest_value(value); }
            void v_set_decimal_places(size_type value) const override           { mr_constraint.decimal_places(value); }
        private:
            IAttribute_Constraint_RW<T>& mr_constraint;
        };
    } // namespace remote

} // namespace saklib

#endif // SAKLIB_ATTRIBUTE_CONSTRAINT_H

