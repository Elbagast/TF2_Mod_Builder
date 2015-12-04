#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_INT_H
#define SAKLIB_INTERNAL_ATTRIBUTE_DATA_INT_H

#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_INT__FWD_H
#include "attribute_data_int__fwd.h"
#endif

#ifndef INCLUDE_STD_TYPE_TRAITS
#define INCLUDE_STD_TYPE_TRAITS
#include <type_traits>
#endif

#ifndef INCLUDE_STD_STRING
#define INCLUDE_STD_STRING
#include <string>
#endif

#ifndef INCLUDE_STD_IOSFWD
#define INCLUDE_STD_IOSFWD
#include <iosfwd>
#endif
namespace saklib
{
    namespace internal
    {
        //---------------------------------------------------------------------------
        // Attribute_Data_Definition_Integral_Type<T>
        //---------------------------------------------------------------------------

        template <typename T>
        class Attribute_Data_Definition_Integral_Type
        {
            static_assert(std::is_integral<T>::value, "Can only use integral types.");
        public:
            // Typedefs
            //============================================================
            using int_type = typename Type_Integral_Type<T>::int_type;

            // Special 6
            //============================================================
            // Initialise with the default lowest, highest and initial values.
            explicit Attribute_Data_Definition_Integral_Type(std::string const& a_name);
            // Initialise as if calling set_range(a_bound1, a_bound2, a_initial)
            Attribute_Data_Definition_Integral_Type(std::string const& a_name, int_type a_bound1, int_type a_bound2, int_type a_initial = default_initial_value());
            // Initialise as if calling set_to_only_value(a_bound1, a_bound2, a_initial)
            Attribute_Data_Definition_Integral_Type(std::string const& a_name, int_type a_value);

            // Interface
            //============================================================
            std::string const& cget_name() const;
            void set_name(std::string const& a_name);

            std::string const& cget_type() const;

            // Ask if a given value is within the range [lowest, highest], return true if
            // it is, otherwise return false.
            bool can_set_value_to(int_type a_value) const;

            int_type get_initial_value() const;
            int_type get_lowest_value() const;
            int_type get_highest_value() const;

            // Set the initial value. If the supplied value is outside [lowest, highest] it
            // will instead be set to the boundary it is closest to.
            // e.g. if lowest = 0, highest = 10, initial = 5
            // set_initial_value(1) -> lowest = 0, highest = 10, initial = 1
            // set_initial_value(-1) -> lowest = 0, highest = 10, initial = 0
            // set_initial_value(11) -> lowest = 0, highest = 10, initial = 10
            void set_initial_value(int_type a_value);

            // Set the lowest value. If the supplied value is greater than initial value it
            // will instead be set to be the same as the initial value.
            // e.g. if lowest = 0, highest = 10, initial = 5
            // set_lowest_value(1) -> lowest = 1, highest = 10, initial = 5
            // set_lowest_value(6) -> lowest = 5, highest = 10, initial = 5
            // set_lowest_value(11) -> lowest = 5, highest = 10, initial = 5
            void set_lowest_value(int_type a_value);

            // Set the highest value. If the supplied value is less than initial value it
            // will instead be set to be the same as the initial value.
            // e.g. if lowest = 0, highest = 10, initial = 5
            // set_highest_value(-1) -> lowest = 1, highest = 5, initial = 5
            // set_highest_value(4) -> lowest = 1, highest = 5, initial = 5
            // set_highest_value(11) -> lowest = 1, highest = 11, initial = 5
            void set_highest_value(int_type a_value);

            // Set the all the constraint values. You must supply at least the range bounds
            // either way around. The lower of them will become the lowest and the higher
            // the highest. If you supply an initial value, it will be set after the lowest
            // and highest have been set, using the same rules as set_initial_value(). By
            // default the initial value is 0, so it will be set to that or the closest
            // boundary to 0.
            // e.g.
            // set_range(-5,10) -> lowest = -5, highest = 10, initial = 0
            // set_range(-5,10,1) -> lowest = -5, highest = 10, initial = 1
            // set_range(-5,10,-6) -> lowest = -5, highest = 10, initial = -5
            // set_range(-5,10,123) -> lowest = -5, highest = 10, initial = 10
            // set_range(120,0) -> lowest = 0, highest = 120, initial = 0
            // set_range(120,0,20) -> lowest = 0, highest = 120, initial = 20
            // set_range(120,0,-20) -> lowest = 0, highest = 120, initial = 0
            // set_range(120,0,140) -> lowest = 0, highest = 120, initial = 120
            void set_range(int_type a_bound1, int_type a_bound2, int_type a_initial = default_initial_value());

            // Set the lowest, highest, and inital values all to the given value. This
            // means the constraint is set to a single value.
            // e.g.
            // set_to_only_value(0) -> lowest = 0, highest = 0, initial = 0
            // set_to_only_value(1234) -> lowest = 1234, highest = 1234, initial = 1234
            // set_to_only_value(-5678) -> lowest = -5678, highest = -5678, initial = -5678
            void set_to_only_value(int_type a_value);

            // Set the constraints to the defaults
            void set_to_default();

            // all should be constexpr
            static int_type default_initial_value();
            static int_type default_lowest_value();
            static int_type default_highest_value();
        private:
            // Data Members
            //============================================================
            std::string m_name;
            int_type m_initial_value;
            int_type m_lowest_value;
            int_type m_highest_value;
        };

        // Non-Member Operators
        //============================================================
        template <typename T>
        std::ostream& operator << (std::ostream& a_ostream, Attribute_Data_Definition_Integral_Type<T> const& ar_definition);


        //---------------------------------------------------------------------------
        // Attribute_Data_Integral_Type<T>
        //---------------------------------------------------------------------------

        template <typename T>
        class Attribute_Data_Integral_Type
        {
            static_assert(std::is_integral<T>::value, "Can only use integral types.");
        public:
            // Typedefs
            //============================================================
            using definition_type = Attribute_Data_Definition_Integral_Type<T>;
            using int_type = typename definition_type::int_type;

            // Special 6
            //============================================================
            explicit Attribute_Data_Integral_Type(definition_type const& ar_definition);

            // Interface
            //============================================================
            std::string const& cget_name() const;

            std::string const& cget_type() const;

            std::string cget_value_string() const;

            // Get the stored value
            int_type cget_value() const;

            // Can the value be set to this? Returns true if it can, but returns false if the
            // value is already set to this since there would be no change.
            bool can_set_value_to(int_type a_value) const;

            // If can_set_value_to() then set the value to this and return true, else false.
            bool try_set_value(int_type a_value);

            void set_value(int_type a_value);

            int_type cget_lowest_value() const;
            int_type cget_highest_value() const;

        private:
            // Data Members
            //============================================================
            definition_type const& mr_definition;
            int_type m_value;
        };

        // Non-Member Operators
        //============================================================
        template <typename T>
        std::ostream& operator << (std::ostream& a_ostream, Attribute_Data_Integral_Type<T> const& ar_attribute);


    } // namespace internal
} // namespace saklib

#endif // SAKLIB_INTERNAL_ATTRIBUTE_DATA_INT_H

