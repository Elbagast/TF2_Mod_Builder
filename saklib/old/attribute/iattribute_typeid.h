#ifndef SAKLIB_IATTRIBUTE_TYPEID_H
#define SAKLIB_IATTRIBUTE_TYPEID_H

#include "../types.h"
#include "../common_traits.h"

namespace saklib
{
    using saklib::Type_Enum;
    using saklib::String;
    /*
    IFixed_Typeid
    ====================================================================================================
    Interface for a typeid that is only set on construction.
    */
    class IAttribute_Typeid
    {
    public:
        virtual ~IAttribute_Typeid() = default;

        Type_Enum type() const          { return v_type(); }
        String type_string() const      { return v_type_string(); }
        bool is_simple_type() const     { return v_is_simple_type(); }
        bool is_vector_type() const     { return v_is_vector_type(); }
        bool is_element_type() const    { return v_is_element_type(); }
    protected:
        virtual Type_Enum v_type() const = 0;
        virtual String v_type_string() const = 0;
        virtual bool v_is_simple_type() const = 0;
        virtual bool v_is_vector_type() const = 0;
        virtual bool v_is_element_type() const = 0;
    };

} // namespace saklib

#endif // SAKLIB_IATTRIBUTE_TYPEID_H

