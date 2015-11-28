#ifndef SAKLIB_INTERNAL_CONSTRAINT_BOOLEAN_TYPE_H
#define SAKLIB_INTERNAL_CONSTRAINT_BOOLEAN_TYPE_H

#ifndef SAKLIB_INTERNAL_CONSTRAINT_BOOLEAN_TYPE__FWD_H
#include "constraint_boolean_type__fwd.h"
#endif

#include <type_traits>
#include <iosfwd>

namespace saklib
{
    namespace internal
    {
        template <typename T>
        class Constraint_Boolean_Type
        {
            static_assert(std::is_same<T, bool>::value, "Can only use bool type.");
        public:
            using boolean_type = T;

            explicit Constraint_Boolean_Type(boolean_type a_initial = default_initial_value());

            // Ask if a given value is within the range [lowest, highest], return true if
            // it is, otherwise return false.
            bool can_set_value_to(boolean_type a_value) const;

            // Get the initial value
            boolean_type get_initial_value() const;

            // Set the initial value.
            void set_initial_value(boolean_type a_value);

            // Set the constraints to the defaults
            void set_to_default();

            // all should be constexpr
            static boolean_type default_initial_value();
        private:
            boolean_type m_initial_value;
        };



        template <typename T>
        class Constrained_Boolean_Type
        {
            static_assert(std::is_same<T, bool>::value, "Can only use bool type.");
        public:
            using constraint_type = Constraint_Boolean_Type<T>;
            using boolean_type = typename constraint_type::boolean_type;

            explicit Constrained_Boolean_Type(constraint_type const& ar_constraint);

            // Get the stored value
            boolean_type get_value() const;

            // Can the value be set to this? Returns true if it can, but returns false if the
            // value is already set to this since there would be no change.
            bool can_set_value_to(boolean_type a_value) const;

            // If can_set_value_to() then set the value to this and return true, else false.
            bool try_set_value(boolean_type a_value);

        private:
            constraint_type const& mr_constraint;
            boolean_type m_value;
        };

        template <typename T>
        std::ostream& operator << (std::ostream& a_ostream, Constraint_Boolean_Type<T> const& a_constraint);
        template <typename T>
        std::ostream& operator << (std::ostream& a_ostream, Constrained_Boolean_Type<T> const& a_constrained);

    } // namespace internal
} // namespace saklib

#endif // SAKLIB_INTERNAL_CONSTRAINT_BOOLEAN_TYPE_H

