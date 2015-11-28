#ifndef SAKLIB_INTERNAL_ATTRIBUTE_H
#define SAKLIB_INTERNAL_ATTRIBUTE_H

#ifndef SAKLIB_INTERNAL_ATTRIBUTE__FWD_H
#include "attribute__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_ALL_CONSTRAINT__FWD_H
#include "all_constraint__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_TYPE_STRING__FWD_H
#include "type_string__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_STRING_H
#include "string.h"
#endif

#include <iosfwd>
#include <exception>
#include <boost/any.hpp>

namespace saklib
{
    namespace internal
    {


        class Attribute_Definition
        {
        public:
            // Constructor will throw if the supplied any does not contain one of the required
            // constraint objects.
            Attribute_Definition(String const& a_name, String const& a_type);
            Attribute_Definition(String const& a_name, TS_Bool&& a_type);
            Attribute_Definition(String const& a_name, TS_Bool&& a_type, bool a_initial);
            Attribute_Definition(String const& a_name, TS_Int&& a_type);
            Attribute_Definition(String const& a_name, TS_Int&& a_type, int a_bound1, int a_bound2, int a_intiial = 0);

            String get_name() const;
            void set_name(String const& a_name);

            String get_type() const;
            void set_type(String const& a_type);

            bool is_bool() const;
            bool is_int() const;

            void set_to_bool();
            void set_to_int();

            Constraint_Bool& get_constraint_bool();
            Constraint_Int& get_constraint_int();

            Constraint_Bool const& cget_constraint_bool() const;
            Constraint_Int const& cget_constraint_int() const;

            boost::any const& cget_any_constraint() const;
        private:
            String m_name;
            boost::any m_any_constraint;
        };

        Attribute_Definition make_attribute_definition_bool__default(String const& a_name);
        Attribute_Definition make_attribute_definition_bool(String const& a_name, bool a_initial);
        Attribute_Definition make_attribute_definition_int__default(String const& a_name);
        Attribute_Definition make_attribute_definition_int(String const& a_name, int a_bound1, int a_bound2, int a_intiial = 0);



        class Attribute
        {
        public:
            explicit Attribute(Attribute_Definition const& a_definition);

            String get_name() const;

            String get_type() const;

            bool is_bool() const;
            bool is_int() const;

            Constrained_Bool& get_value_bool();
            Constrained_Int& get_value_int();

            Constrained_Bool const& cget_value_bool() const;
            Constrained_Int const& cget_value_int() const;

        private:
            Attribute_Definition const& mr_definition;
            boost::any m_any_constrained;
        };

        std::ostream& operator << (std::ostream& a_ostream, Attribute_Definition const& a_definitition);
        std::ostream& operator << (std::ostream& a_ostream, Attribute const& a_attribute);

    } // namespace internal
} // namespace saklib

#endif // SAKLIB_INTERNAL_ATTRIBUTE_H

