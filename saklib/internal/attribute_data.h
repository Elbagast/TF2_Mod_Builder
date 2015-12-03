#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_H
#define SAKLIB_INTERNAL_ATTRIBUTE_DATA_H

#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA__FWD_H
#include "attribute_data__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_ALL_ATTRIBUTE_DATA__FWD_H
#include "all_attribute_data__fwd.h"
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

#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif

#ifndef INCLUDE_STD_FUNCTIONAL
#define INCLUDE_STD_FUNCTIONAL
#include <functional>
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
            friend class Attribute_Data;
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

            Attribute_Data_Definition_Bool& get_bool();
            Attribute_Data_Definition_Int& get_int();

            Attribute_Data_Definition_Bool const& cget_bool() const;
            Attribute_Data_Definition_Int const& cget_int() const;

        private:
            // Data Members
            //============================================================
            boost::any m_any_definition;

            using name_getter_type = std::function<std::string const&(boost::any const&)>;
            using name_setter_type = std::function<void (boost::any&, std::string const&)>;
            using type_getter_type = std::function<std::string const& (boost::any const&)>;
            using value_string_getter_type = std::function<std::string (boost::any const&)>;

            name_getter_type mf_name_getter;
            name_setter_type mf_name_setter;
            type_getter_type mf_type_getter;

            // not used here, given to Attribute_Data built with this
            value_string_getter_type mf_value_getter;
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

            std::string cget_value_string() const;

            bool is_bool() const;
            bool is_int() const;

            Attribute_Data_Bool& get_bool();
            Attribute_Data_Int& get_int();

            Attribute_Data_Bool const& cget_bool() const;
            Attribute_Data_Int const& cget_int() const;

        private:
            using value_string_getter_type = std::function<std::string (boost::any const&)>;

            // Data Members
            //============================================================
            Attribute_Data_Definition const& mr_definition;
            boost::any m_any_attribute;
            value_string_getter_type mf_value_string_getter;
        };

        // Non-Member Operators
        //============================================================
        std::ostream& operator << (std::ostream& a_ostream, Attribute_Data const& a_attribute);

    } // namespace internal
} // namespace saklib

#endif // SAKLIB_INTERNAL_ATTRIBUTE_DATA_H

