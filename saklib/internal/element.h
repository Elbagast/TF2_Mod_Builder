#ifndef SAKLIB_INTERNAL_ELEMENT_H
#define SAKLIB_INTERNAL_ELEMENT_H

#ifndef SAKLIB_INTERNAL_ATTRIBUTE_H
#include "attribute.h"
#endif

#ifndef SAKLIB_INTERNAL_SIZE_TYPE_H
#include "size_type.h"
#endif

#ifndef SAKLIB_INTERNAL_STRING_H
#include "string.h"
#endif

#include <vector>
#include <iosfwd>

namespace saklib
{
    namespace internal
    {
        class Element_Definition
        {
        public:
            using storage_type = std::vector<Attribute_Definition>;

            explicit Element_Definition(String const& a_type);
            Element_Definition(String const& a_type, storage_type const& a_attribute_definitions);
            Element_Definition(String const& a_type, storage_type && a_attribute_definitions);

            String get_type() const;
            void set_type(String const& a_type);

            Size_Type get_attribute_count() const;

            Attribute_Definition& get_attribute_at(Size_Type a_index);
            Attribute_Definition const& cget_attribute_at(Size_Type a_index) const;

            void push_back_attribute_definition(Attribute_Definition const& a_attribute_definition);
            void push_back_attribute_definition(Attribute_Definition && a_attribute_definition);

            void insert_attribute_definition(Size_Type a_index, Attribute_Definition const&);
            void insert_attribute_definition(Size_Type a_index, Attribute_Definition &&);

            void remove_attribute_definition(Size_Type a_index);

            void set_attribute_definitions(storage_type const& a_attribute_definitions);

        private:
            String m_type;
            storage_type m_attribute_definitions;
        };

        class Element
        {
        public:
            using storage_type = std::vector<Attribute>;

            explicit Element(Element_Definition const& ar_definition);
            Element(Element_Definition const& a_definition, String const& a_name);

            String get_type() const;

            String get_name() const;
            void set_name(String const& a_name);

            Size_Type get_attribute_count() const;
            Attribute& get_attribute_at(Size_Type a_index);
            Attribute const& cget_attribute_at(Size_Type a_index) const;

        private:
            Element_Definition const& mr_definition;
            String m_name;
            storage_type m_attributes;
        };

        std::ostream& operator << (std::ostream& a_ostream, Element_Definition const& a_element_definition);
        std::ostream& operator << (std::ostream& a_ostream, Element const& a_element);

    } // namespace internal
} // namespace saklib

#endif // SAKLIB_INTERNAL_ELEMENT_H
