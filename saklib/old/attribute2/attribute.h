#ifndef SAKLIB_ATTRIBUTE_H
#define SAKLIB_ATTRIBUTE_H

#ifndef SAKLIB_ATTRIBUTE__FWD_H
#include "attribute__fwd.h"
#endif

#ifndef SAKLIB_ATTRIBUTE_DEFINITION__FWD_H
#include "attribute_definition__fwd.h"
#endif

#include <memory>

namespace saklib
{
    class Fixed_String;
    class String;
    class Element;
    class Index;

    class Attribute
    {
    public:
        bool is_valid() const;
        void expire();
        bool is_expired() const;

        Element cget_parent_element() const;
        Index cget_index_in_parent_element() const;

        Attribute cget_next_attribute() const;
        Attribute cget_previous_attribute() const;

        Fixed_String cget_name_string() const;
        Fixed_String cget_type_string() const;
        Fixed_String cget_value_string() const;

        bool is_bool() const;
        bool is_int() const;
        bool is_float() const;
        bool is_colour() const;
        bool is_string() const;
        bool is_element() const;

        bool is_vector_bool() const;
        bool is_vector_int() const;
        bool is_vector_float() const;
        bool is_vector_colour() const;
        bool is_vector_string() const;
        bool is_vector_element() const;

        Attribute_Bool cget_attribute_bool() const;
        Attribute_Int cget_attribute_int() const;
        Attribute_Float cget_attribute_float() const;
        Attribute_Colour cget_attribute_colour() const;
        Attribute_String cget_attribute_string() const;
        Attribute_Element cget_attribute_element() const;

        Attribute_Vector_Bool cget_attribute_vector_bool() const;
        Attribute_Vector_Int cget_attribute_vector_int() const;
        Attribute_Vector_Float cget_attribute_vector_float() const;
        Attribute_Vector_Colour cget_attribute_vector_colour() const;
        Attribute_Vector_String cget_attribute_vector_string() const;
        Attribute_Vector_Element cget_attribute_vector_element() const;

    private:
        class Implementation;

        Implementation* get_implementation();
        Implementation const* cget_implementation() const;

        std::unique_ptr<Implementation> m_implementation;
    };

} // namespace saklib

#endif // SAKLIB_ATTRIBUTE_H

