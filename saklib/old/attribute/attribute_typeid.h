#ifndef SAKLIB_ATTRIBUTE_TYPEID_H
#define SAKLIB_ATTRIBUTE_TYPEID_H

#include "iattribute_typeid.h"
#include "../types.h"
#include "../common_traits.h"

namespace saklib
{
    namespace local
    {
        /*
        Attribute_Typeid<T>
        ====================================================================================================
        Implementation for a static typeid for T
        */
        template <typename T>
        class Attribute_Typeid :
                public virtual IAttribute_Typeid
        {
        public:
            ~Attribute_Typeid() override = default;

        protected:
            Type_Enum v_type() const override       { return saklib::Common_Traits<T>::type_enum(); }
            String v_type_string() const override   { return saklib::Common_Traits<T>::type_string(); }
            bool v_is_simple_type() const override  { return saklib::is_simple_type(saklib::Common_Traits<T>::type_enum()); }
            bool v_is_vector_type() const override  { return saklib::is_vector_type(saklib::Common_Traits<T>::type_enum()); }
            bool v_is_element_type() const override { return saklib::is_element_type(saklib::Common_Traits<T>::type_enum()); }
        };
    } // namespace local
} // namespace saklib

#endif // SAKLIB_ATTRIBUTE_TYPEID_H

