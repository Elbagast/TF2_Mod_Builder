#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_BOOLEAN_TYPE_H
#define SAKLIB_INTERNAL_ATTRIBUTE_DATA_BOOLEAN_TYPE_H

#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_BOOLEAN_TYPE__FWD_H
#include "attribute_data_boolean_type__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA__FWD_H
#include "attribute_data__fwd.h"
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
#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif

namespace saklib
{
    namespace internal
    {
        //---------------------------------------------------------------------------
        // Attribute_Data_Definition_Boolean_Type<T>
        //---------------------------------------------------------------------------

        template <typename T>
        class Attribute_Data_Definition_Boolean_Type
        {
            static_assert(std::is_same<T, bool>::value, "Can only use bool type.");
        public:
            // Typedefs
            //============================================================
            using boolean_type = T;

            // Special 6
            //============================================================
            explicit Attribute_Data_Definition_Boolean_Type(std::string const& a_name, boolean_type a_initial = default_initial_value());

            // Interface
            //============================================================
            std::string const& cget_name() const;
            void set_name(std::string const& a_name);

            std::string const& cget_type() const;

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
            // Data Members
            //============================================================
            std::string m_name;
            boolean_type m_initial_value;
        };

        // Non-Member Operators
        //============================================================
        template <typename T>
        std::ostream& operator << (std::ostream& a_ostream, Attribute_Data_Definition_Boolean_Type<T> const& a_constraint);

        //---------------------------------------------------------------------------
        // Attribute_Data_Boolean_Type<T>
        //---------------------------------------------------------------------------

        template <typename T>
        class Attribute_Data_Boolean_Type
        {
            static_assert(std::is_same<T, bool>::value, "Can only use bool type.");
        public:
            // Typedefs
            //============================================================
            using definition_type = Attribute_Data_Definition_Boolean_Type<T>;
            using boolean_type = typename definition_type::boolean_type;

            // Special 6
            //============================================================
            explicit Attribute_Data_Boolean_Type(definition_type const& ar_constraint);

            // Interface
            //============================================================
            std::string const& cget_name() const;

            std::string const& cget_type() const;

            std::string cget_value_string() const;

            // Get the stored value
            boolean_type cget_value() const;

            // Can the value be set to this? Returns true if it can, but returns false if the
            // value is already set to this since there would be no change.
            bool can_set_value_to(boolean_type a_value) const;

            // If can_set_value_to() then set the value to this and return true, else false.
            bool try_set_value(boolean_type a_value);

            void set_value(boolean_type a_value);

        private:
            // Data Members
            //============================================================
            definition_type const& mr_definition;
            boolean_type m_value;
        };

        // Non-Member Operators
        //============================================================
        template <typename T>
        std::ostream& operator << (std::ostream& a_ostream, Attribute_Data_Boolean_Type<T> const& a_constrained);

    } // namespace internal
} // namespace saklib

#endif // SAKLIB_INTERNAL_ATTRIBUTE_DATA_BOOLEAN_TYPE_H

