#ifndef ELEMENT_MANAGER_H
#define ELEMENT_MANAGER_H

#include "types.h"
#include "element.h"
#include "elementid.h"
#include "attributeid.h"
#include <map>

namespace Saklib
{
    /*
    Element_Manager
    ====================================================================================================
    Simple manager for Elements via ElementIDs and AttributeIDs. It's really just map with a simplified
    interface. You will need access to this class to make use of the ID types.


    */
    class Element_Manager
    {
    public:
        // Special 6
        //============================================================
        Element_Manager();
        ~Element_Manager() = default;

        Element_Manager(Element_Manager const& other) = delete;
        Element_Manager& operator=(Element_Manager const& other) = delete;

        // Interface
        //============================================================
        // Build a new Map_Entry containing a new Element from type and return the id number
        ElementID make_element(Element_Definition const& definition, String const& type = String());
        // Destory the Element associated with this id
        void destroy_element(ElementID elementid);

        // Is this ElementID valid for this?
        bool is_valid(ElementID elementid) const;

        // Access the parent of this ID
        bool has_parent(ElementID elementid) const;
        AttributeID parent(ElementID elementid) const;
        void set_parent(ElementID elementid, AttributeID new_parent);

        // Whether this Element has Attribute links in or out
        //bool is_linked(ElementID elementid) const;
        // This Element's Attribute(s?) are linked to other Elements' Attribute data
        //bool has_links_in(ElementID elementid) const;
        // Which Attributes are linked to others
        //Vector_AttributeID attributes_linked_in(ElementID elementid) const;
        // Other Elements' Attribute(s?) are linked to this Element's Attribute data
        //bool has_links_out(ElementID elementid) const;
        // Which Attributes are linked from
        //Vector_AttributeID attributes_linked_out(ElementID elementid) const;

        // Access the Element associated with this ID
        Element& element(ElementID elementid);
        Element const& element(ElementID elementid) const;



        // Ask questions about Elements ?..

        // Is this AttributeID valid for this?
        bool is_valid(AttributeID attributeid) const;

        // Make an AttributeID from the given data
        AttributeID attributeid(ElementID elementid, size_type attribute_index) const;
        AttributeID attributeid(ElementID elementid, String const& attribute_name) const;


        // Access the Attribute associated with this ID
        Attribute*const attribute(AttributeID attributeid);
        Attribute*const attribute(ElementID elementid, size_type attribute_index);
        Attribute*const attribute(ElementID elementid, String const& attribute_name);

        Attribute const*const attribute(AttributeID attributeid) const;
        Attribute const*const attribute(ElementID elementid, size_type attribute_index) const;
        Attribute const*const attribute(ElementID elementid, String const& attribute_name) const;

        // Typed Access to Attributes

        // Auxillary access
        Vector_ElementID all_elementids() const;
        // ElementIDs that have no parent
        Vector_ElementID root_elementids() const;

        // Destory everything
        void clear();

        // Command Interface
        //============================================================
        // Bits that only Command objects will end up using

        size_type command_ref_count(ElementID elementid) const;

        // Adjust ref counts
        void increment_command_ref_count(ElementID elementid);
        void decrement_command_ref_count(ElementID elementid);



    private:
        // Typedefs
        //============================================================
        class Element_Cache
        {
        public:
            // Special 6
            //============================================================
            Element_Cache(Element_Definition const& definition, String const& name):
                m_element(definition, name),
                m_parent(),
                m_linked(),
                m_command_ref_count{0}
            {}
            ~Element_Cache() = default;

            Element_Cache(Element_Cache const& other) = delete;
            Element_Cache& operator=(Element_Cache const& other) = delete;

            Element_Cache(Element_Cache && other):
                m_element(std::move(other.m_element)),
                m_parent(std::move(other.m_parent)),
                m_linked(std::move(other.m_linked)),
                m_command_ref_count(std::move(other.m_command_ref_count))
            {}
            Element_Cache& operator=(Element_Cache && other)
            {
                m_element = std::move(other.m_element);
                m_parent = std::move(other.m_parent);
                m_linked = std::move(other.m_linked);
                m_command_ref_count = std::move(other.m_command_ref_count);
                return *this;
            }

            // Member Data
            //============================================================
            Element m_element;
            AttributeID m_parent;           // the Attribute that owns this Element
            Vector_AttributeID m_linked;    // where this Element is referenced
            size_type m_command_ref_count;  // how many Commands reference this Element

            // Attribute stats that we compute once?
        };

        using map_type = std::map < ElementID, Element_Cache >;
        using iterator = map_type::iterator;
        using const_iterator = map_type::const_iterator;

        // Helpers
        //============================================================
        //void cache_find(ElementID elementid);

        // Member Data
        //============================================================
        map_type m_map;
        //iterator m_last_find;

        mutable id_type m_next_id;
    };

} //namespace Saklib

#endif // ELEMENT_MANAGER_H
