#ifndef ELEMENT_H
#define ELEMENT_H

#include "types.h"
#include "type_traits.h"
#include "fwd_attribute_type.h"
#include "element_definition.h"

namespace Saklib
{  
    class Attribute;
    /*
    Element
    ====================================================================================================
    Data storage class which forms the backbone of a dictionary of attributes of different types. All of
    the data it stores are dumb types.

    Element doesn't track its parent, as it may be referenced be more than one other Element, so you
    will have to track that elsewhere if you need to.
    */
    class Element
    {
    public:
        // Internal Manager Access - forwarded to static manager
        //============================================================
        // Is an Element_Definition with this type registered?
        static bool definition_exists(String const& type);
        // Is an Element_Definition with this exact configuration registered?
        static bool definition_exists(Element_Definition const& definition);
        // If an Element_Definition with the same configuration as arg does not exist, add it do the definitions 
        static bool try_add_definition(Element_Definition&& definition);
        // Add this Element_Definition, overriding any definitions that might match
        static void add_override_definition(Element_Definition&& definition);
        // Get a vector of the registered types
        static Vector_String get_registered_types();

        // Special 6
        //============================================================
        explicit Element(String const& type = String());
        ~Element();

        // NO COPYING
        Element(Element const& other) = delete;
        Element& operator=(Element const& other) = delete;

        // Explicit default move (thanks Microsoft...)
        Element(Element && other);
        Element& operator=(Element && other);

        // Basic Access
        //============================================================
        String const& type() const;
        bool can_be_root() const;

        String const& name() const;
        void set_name(String const& name);

        // Attributes Access
        //============================================================
        // How many Attributes does this Element have?
        size_type attribute_count() const;

        // How many Attributes of the given type does this Element have?
        template <typename T>
        size_type attribute_count_type() const
        {
            size_type count{0};
            for (auto const& attribute : m_attributes)
                if (attribute->type_enum() == Type_Traits<T>::type_enum_value)
                    ++count;
            return count;
        }
        template <Type_Enum TE>
        size_type attribute_count_enum() const
        {
            return attribute_count_type<TypeHolder_st<TE>>();
        }

        // Does this have an Attribute with this name?
        bool has_attribute(String const& name) const;

        // Get the Attribute with this name, nullptr if not found
        Attribute* attribute(String const& name) const;

        // Get the Attribute at this index, nullptr if not found
        Attribute* attribute(size_type index) const;

        // Get a Vector of all the Attribute names
        Vector_String attribute_names() const;

        // Access to all of the Attributes (do we want to allow write access?...)
        Vector<Uptr<Attribute>>& attributes();
        Vector<Uptr<Attribute>> const& attributes() const;
        
        // Get a pointer to a derived Attribute type for the Attribute specified by name
        template <typename Stored_Type>
        Attribute_Type<Stored_Type>* attribute_type_cast(String const& name) const
        {
            return dynamic_cast<Attribute_Type<Stored_Type>*>(attribute(name));
        }
        template <typename Stored_Type>
        Attribute_Type<Stored_Type>* attribute_type_cast(size_type index) const
        {
            return dynamic_cast<Attribute_Type<Stored_Type>*>(m_attributes.at(index).get());
        }
        template <Type_Enum TE>
        Attribute_Type<TypeHolder_st<TE> >* attribute_enum_cast(String const& name) const
        {
            return dynamic_cast<Attribute_Type<TypeHolder_st<TE> >*>(attribute(name));
        }
        template <Type_Enum TE>
        Attribute_Type<TypeHolder_st<TE> >* attribute_enum_cast(size_type index) const
        {
            return dynamic_cast<Attribute_Type<TypeHolder_st<TE> >*>(m_attributes.at(index).get());
        }
        

    private:
        // Data
        //============================================================
        String m_type;
        String m_name;
        bool m_can_be_root;
        Vector<Uptr<Attribute>> m_attributes;
        // maybe cache stats here?

        // Initialisation Helpers
        //============================================================
        static String initialise_type_from_definition_of(String const& type); // called so that a check that type is valid can be made here
        static String initialise_name_from_definition_of(String const& type);
        static bool initialise_can_be_root_from_definition_of(String const& type);
        static Vector<Uptr<Attribute>> initialise_attributes_from_definition_of(String const& type);

        // Internal Manager
        //============================================================
        class Element_Definition_Manager
        {
        public:
            Element_Definition_Manager();

            // Interface
            //============================================================
            // Is an Element_Definition with this type registered?
            bool definition_exists(String const& type) const;
            // Is an Element_Definition with this exact configuration registered?
            bool definition_exists(Element_Definition const& definition) const;
            // If an Element_Definition with the same configuration as arg does not exist, add it do the definitions 
            bool try_add_definition(Element_Definition&& definition);
            // Add this Element_Definition, overriding any definitions that might match
            void add_override_definition(Element_Definition&& definition);
            // Get a vector of the registered types
            Vector_String get_registered_types() const;

            String get_type_from_definition_of(String const& type) const; // called so that a check that type is valid can be made here
            String get_name_from_definition_of(String const& type) const;
            bool get_can_be_root_from_definition_of(String const& type) const;
            Vector<Uptr<Attribute>> get_attributes_from_definition_of(String const& type) const;

            static Uptr<Attribute> initialise_attribute_from_definition(Attribute_Definition const& definition);
        private:
            Vector<Element_Definition>::iterator find_definition(String const& type);
            Vector<Element_Definition>::const_iterator find_definition(String const& type) const; 
            Vector<Element_Definition>::iterator find_definition(Element_Definition const& definition);
            Vector<Element_Definition>::const_iterator find_definition(Element_Definition const& definition) const;

            void add_definition(Element_Definition&& definition);
            
            Vector<Element_Definition> m_element_definitions;
        };


        static Element_Definition_Manager s_element_definition_manager;
    };


} // namespace Saklib

#endif // ELEMENT_H
