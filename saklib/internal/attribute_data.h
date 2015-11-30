#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_H
#define SAKLIB_INTERNAL_ATTRIBUTE_DATA_H

#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA__FWD_H
#include "attribute_data__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_ALL_CONSTRAINT__FWD_H
#include "all_constraint__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_TYPE_STRING__FWD_H
#include "type_string__fwd.h"
#endif

#ifndef INCLUDE_STD_STRING
#define INCLUDE_STD_STRING
#include <string>
#endif

#ifndef INCLUDE_STD_IOSFWD
#define INCLUDE_STD_IOSFWD
#include <iosfwd>
#endif

#ifndef INCLUDE_BOOST_ANY
#define INCLUDE_BOOST_ANY
#include <boost/any.hpp>
#endif

namespace saklib
{
    namespace internal
    {
        //---------------------------------------------------------------------------
        // Attribute_Data_Definition
        //---------------------------------------------------------------------------

        class Attribute_Data_Definition
        {
        public:
            // Special 6
            //============================================================
            // Construct based on the given type string. If the type string is invalid then the type
            // will be bool.
            Attribute_Data_Definition(std::string const& a_name, std::string const& a_type);
            Attribute_Data_Definition(std::string const& a_name, TS_Bool&& a_type);
            Attribute_Data_Definition(std::string const& a_name, TS_Bool&& a_type, bool a_initial);
            Attribute_Data_Definition(std::string const& a_name, TS_Int&& a_type);
            Attribute_Data_Definition(std::string const& a_name, TS_Int&& a_type, int a_bound1, int a_bound2, int a_intiial = 0);

            // Interface
            //============================================================
            std::string const& cget_name() const;
            void set_name(std::string const& a_name);

            std::string const& cget_type() const;
            void set_type(std::string const& a_type);

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
            // Data Members
            //============================================================
            std::string m_name;
            boost::any m_any_constraint;
        };

        // Factory Functions
        //============================================================
        Attribute_Data_Definition make_attribute_definition_bool__default(std::string const& a_name);
        Attribute_Data_Definition make_attribute_definition_bool(std::string const& a_name, bool a_initial);
        Attribute_Data_Definition make_attribute_definition_int__default(std::string const& a_name);
        Attribute_Data_Definition make_attribute_definition_int(std::string const& a_name, int a_bound1, int a_bound2, int a_intiial = 0);

        // Non-Member Operators
        //============================================================
        std::ostream& operator << (std::ostream& a_ostream, Attribute_Data_Definition const& a_definitition);


        //---------------------------------------------------------------------------
        // Attribute_Data
        //---------------------------------------------------------------------------

        class Attribute_Data
        {
        public:
            // Special 6
            //============================================================
            explicit Attribute_Data(Attribute_Data_Definition const& a_definition);

            // Interface
            //============================================================
            std::string const& cget_name() const;

            std::string const& cget_type() const;

            bool is_bool() const;
            bool is_int() const;

            Constrained_Bool& get_value_bool();
            Constrained_Int& get_value_int();

            Constrained_Bool const& cget_value_bool() const;
            Constrained_Int const& cget_value_int() const;

        private:
            // Data Members
            //============================================================
            Attribute_Data_Definition const& mr_definition;
            boost::any m_any_constrained;
        };

        // Non-Member Operators
        //============================================================
        std::ostream& operator << (std::ostream& a_ostream, Attribute_Data const& a_attribute);

    } // namespace internal
} // namespace saklib

#endif // SAKLIB_INTERNAL_ATTRIBUTE_DATA_H

