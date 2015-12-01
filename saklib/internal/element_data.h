#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_H
#define SAKLIB_INTERNAL_ELEMENT_DATA_H

#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_H
#include "attribute_data.h"
#endif

#ifndef INCLUDE_STD_CSTDDEF
#define INCLUDE_STD_CSTDDEF
#include <cstddef>
#endif

#ifndef INCLUDE_STD_STRING
#define INCLUDE_STD_STRING
#include <string>
#endif

#ifndef INCLUDE_STD_VECTOR
#define INCLUDE_STD_VECTOR
#include <vector>
#endif

#ifndef INCLUDE_STD_TYPE_TRAITS
#define INCLUDE_STD_TYPE_TRAITS
#include <type_traits>
#endif

#ifndef INCLUDE_STD_IOSFWD
#define INCLUDE_STD_IOSFWD
#include <iosfwd>
#endif

namespace saklib
{
    namespace internal
    {
        //---------------------------------------------------------------------------
        // Element_Data_Definition
        //---------------------------------------------------------------------------

        class Element_Data_Definition
        {
        public:
            // Typedefs
            //============================================================
            using storage_type = std::vector<Attribute_Data_Definition>;

            // Special 6
            //============================================================
            explicit Element_Data_Definition(std::string const& a_type);
            Element_Data_Definition(std::string const& a_type, storage_type const& a_attribute_definitions);
            Element_Data_Definition(std::string const& a_type, storage_type && a_attribute_definitions);

            // Interface
            //============================================================
            std::string const& cget_type() const;
            void set_type(std::string const& a_type);

            std::size_t get_attribute_count() const;

            Attribute_Data_Definition& get_attribute_at(std::size_t a_index);
            Attribute_Data_Definition const& cget_attribute_at(std::size_t a_index) const;

            storage_type const& cget_attributes() const;

            void push_back_attribute_definition(Attribute_Data_Definition const& a_attribute_definition);
            void push_back_attribute_definition(Attribute_Data_Definition && a_attribute_definition);

            void insert_attribute_definition(std::size_t a_index, Attribute_Data_Definition const&);
            void insert_attribute_definition(std::size_t a_index, Attribute_Data_Definition &&);

            void remove_attribute_definition(std::size_t a_index);

            void set_attribute_definitions(storage_type const& a_attribute_definitions);

        private:
            // Data Members
            //============================================================
            std::string m_type;
            storage_type m_attribute_definitions;
        };

        // Non-Member Operators
        //============================================================
        std::ostream& operator << (std::ostream& a_ostream, Element_Data_Definition const& a_element_definition);

        //---------------------------------------------------------------------------
        // Element_Data
        //---------------------------------------------------------------------------

        class Element_Data
        {
        public:
            // Typedefs
            //============================================================
            using storage_type = std::vector<Attribute_Data>;

            // Special 6
            //============================================================
            explicit Element_Data(Element_Data_Definition const& ar_definition);
            Element_Data(Element_Data_Definition const& a_definition, std::string const& a_name);

            // Interface
            //============================================================
            std::string const& cget_type() const;

            std::string const& cget_name() const;
            void set_name(std::string const& a_name);

            std::size_t get_attribute_count() const;

            Attribute_Data& get_attribute_at(std::size_t a_index);
            Attribute_Data const& cget_attribute_at(std::size_t a_index) const;

            storage_type const& cget_attributes() const;

        private:
            // Data Members
            //============================================================
            Element_Data_Definition const& mr_definition;
            std::string m_name;
            storage_type m_attributes;
        };

        // Non-Member Operators
        //============================================================
        std::ostream& operator << (std::ostream& a_ostream, Element_Data const& a_element);

    } // namespace internal
} // namespace saklib

#endif // SAKLIB_INTERNAL_ELEMENT_DATA_H
