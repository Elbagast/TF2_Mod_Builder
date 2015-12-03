#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_BASE_H
#define SAKLIB_INTERNAL_ATTRIBUTE_DATA_BASE_H

#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_BASE__FWD_H
#include "attribute_data_base__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_ALL_ATTRIBUTE_DATA__FWD_H
#include "all_attribute_data__fwd.h"
#endif

#ifndef INCLUDE_STD_STRING
#define INCLUDE_STD_STRING
#include <string>
#endif

#ifndef INCLUDE_STD_TYPEINDEX
#define INCLUDE_STD_TYPEINDEX
#include <typeindex>
#endif

namespace saklib
{
    namespace internal
    {
        //---------------------------------------------------------------------------
        // Attribute_Data_Definition_Base
        //---------------------------------------------------------------------------

        class Attribute_Data_Definition_Base
        {
        public:
            // Special 6
            //============================================================
            virtual ~Attribute_Data_Definition_Base() = 0;

            virtual Attribute_Data_Definition_Base* clone() const = 0;

            // Interface
            //============================================================
            virtual std::string const& cget_name() const = 0;
            virtual void set_name(std::string const& a_name) = 0;

            virtual std::string const& cget_type() const = 0;

            // default implementations supplied - all return false
            virtual bool is_bool() const;
            virtual bool is_int() const;
        };

        // Non-Member Operators
        //============================================================
        //std::ostream& operator << (std::ostream& a_ostream, Attribute_Data_Definition const& a_definitition);


        //---------------------------------------------------------------------------
        // Attribute_Data_Base
        //---------------------------------------------------------------------------

        class Attribute_Data_Base
        {
        public:
            // Special 6
            //============================================================
            virtual ~Attribute_Data_Base() = 0;

            virtual Attribute_Data_Base* clone() const = 0;

            // Interface
            //============================================================
            virtual std::string const& cget_name() const = 0;

            virtual std::string const& cget_type() const = 0;

            // default implementations suuplied - all return false
            virtual bool is_bool() const;
            virtual bool is_int() const;
        };

        // Non-Member Operators
        //============================================================
        //std::ostream& operator << (std::ostream& a_ostream, Attribute_Data const& a_attribute);

    } // namespace internal
} // namespace saklib

#endif // SAKLIB_INTERNAL_ATTRIBUTE_DATA_BASE_H
