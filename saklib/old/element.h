#ifndef ELEMENT_H
#define ELEMENT_H

#include "types.h"

namespace saklib
{  
    class Element_Definition;
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
        // Special 6
        //============================================================
        Element(Element_Definition const& definition, String const& name = String());
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
        size_type attribute_count_type(Type_Enum type) const;

        // Does this have an Attribute with this name?
        bool has_attribute(String const& name) const;

        // Does this have an Attribute with this index?
        bool has_attribute(size_type index) const;

        // Get the Attribute with this name, nullptr if not found
        Attribute* attribute(String const& name);
        Attribute const* cattribute(String const& name) const;

        // Get the Attribute at this index, nullptr if not found
        Attribute* attribute(size_type index);
        Attribute const* cattribute(size_type index) const;

        // Get a Vector of all the Attribute names
        std::vector<String> attribute_names() const;

    private:
        using attribute_vector = std::vector<std::unique_ptr<Attribute>>;
        using iterator = attribute_vector::iterator;
        using const_iterator = attribute_vector::const_iterator;

        iterator find_attribute(String const& name);
        const_iterator cfind_attribute(String const& name) const;

        // Data
        //============================================================
        // So we actually have some special attributes...
        String m_type;
        String m_name;
        bool m_can_be_root;
        attribute_vector m_attributes;
        // maybe cache stats here?

    };


} // namespace saklib

#endif // ELEMENT_H
