#ifndef SAKLIB_ATTRIBUTE_DEFINITION_H
#define SAKLIB_ATTRIBUTE_DEFINITION_H

#ifndef SAKLIB_ATTRIBUTE_DEFINITION__FWD_H
#include "attribute_definition__fwd.h"
#endif

#include <memory>

namespace saklib
{
    class Fixed_String;
    class String;
    class Element_Definition;
    class Index;

    class Attribute_Definition
    {
    public:
        bool is_valid() const;
        void expire();
        bool is_expired() const;

        Element_Definition cget_parent_element_definition() const;
        Index cget_index_in_parent_element_definition() const;

        Attribute_Definition cget_next_attribute_definition() const;
        Attribute_Definition cget_previous_attribute_definition() const;

        Fixed_String cget_name_string() const;
        void set_name_string(String const& a_value);

        Fixed_String cget_type_string() const;
        void set_type_by_string(String const& a_value);

        void set_type_to_bool();
        void set_type_to_int();
        void set_type_to_float();
        void set_type_to_colour();
        void set_type_to_string();
        void set_type_to_element();

        void set_type_to_vector_bool();
        void set_type_to_vector_int();
        void set_type_to_vector_float();
        void set_type_to_vector_colour();
        void set_type_to_vector_string();
        void set_type_to_vector_element();

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

        Attribute_Definition_Bool cget_attribute_bool() const;
        Attribute_Definition_Int cget_attribute_int() const;
        Attribute_Definition_Float cget_attribute_float() const;
        Attribute_Definition_Colour cget_attribute_colour() const;
        Attribute_Definition_String cget_attribute_string() const;
        Attribute_Definition_Element cget_attribute_element() const;

        Attribute_Definition_Vector_Bool cget_attribute_vector_bool() const;
        Attribute_Definition_Vector_Int cget_attribute_vector_int() const;
        Attribute_Definition_Vector_Float cget_attribute_vector_float() const;
        Attribute_Definition_Vector_Colour cget_attribute_vector_colour() const;
        Attribute_Definition_Vector_String cget_attribute_vector_string() const;
        Attribute_Definition_Vector_Element cget_attribute_vector_element() const;

    private:
        class Implementation;

        Implementation* get_implementation();
        Implementation const* cget_implementation() const;

        std::unique_ptr<Implementation> m_implementation;
    };

} // namespace saklib

#endif // SAKLIB_ATTRIBUTE_DEFINITION_H

