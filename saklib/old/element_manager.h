#ifndef ELEMENT_MANAGER_H
#define ELEMENT_MANAGER_H

#include "types.h"
#include "element.h"
#include "elementid.h"
#include "attributeid.h"
#include <map>
//#include <tuple>

namespace saklib
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
        ElementID make_element(Element_Definition const& definition, String const& name = String());
        // Destory the Element associated with this id
        void destroy_element(ElementID const& elementid);

        // Is this ElementID valid for this?
        bool has_elementid(ElementID const& elementid) const;

        // Access the parent of this ID
        bool has_parent(ElementID const& elementid) const;
        AttributeID element_parent(ElementID const& elementid) const;
        void set_element_parent(ElementID const& elementid, AttributeID new_parent);

        // The name of a given Element
        String const& element_name(ElementID const& elementid) const;
        // Set an Element name, return true if the given name was unique
        bool set_element_name(ElementID const& elementid, String const& name);

        // Whether this Element has Attribute links in or out
        //bool is_linked(ElementID const& elementid) const;
        // This Element's Attribute(s?) are linked to other Elements' Attribute data
        //bool has_links_in(ElementID const& elementid) const;
        // Which Attributes are linked to others
        //Vector_AttributeID attributes_linked_in(ElementID const& elementid) const;
        // Other Elements' Attribute(s?) are linked to this Element's Attribute data
        //bool has_links_out(ElementID const& elementid) const;
        // Which Attributes are linked from
        //Vector_AttributeID attributes_linked_out(ElementID const& elementid) const;

        // Access the Element associated with this ID
        Element* element(ElementID const& elementid);
        Element const* celement(ElementID const& elementid) const;



        // Ask questions about Elements ?..

        // Is this AttributeID valid for this?
        bool has_attributeid(AttributeID const& attributeid) const;

        // Make an AttributeID from the given data
        AttributeID attributeid(ElementID const& elementid, size_type attribute_index) const;
        AttributeID attributeid(ElementID const& elementid, String const& attribute_name) const;


        // Access the Attribute associated with this ID
        Attribute* attribute(AttributeID const& attributeid);
        Attribute* attribute(ElementID const& elementid, size_type attribute_index);
        Attribute* attribute(ElementID const& elementid, String const& attribute_name);

        Attribute const* cattribute(AttributeID const& attributeid) const;
        Attribute const* cattribute(ElementID const& elementid, size_type attribute_index) const;
        Attribute const* cattribute(ElementID const& elementid, String const& attribute_name) const;

        // Typed Access to Attributes

        // Auxillary access
        std::vector<ElementID> all_elementids() const;
        // ElementIDs that have no parent
        std::vector<ElementID> root_elementids() const;
        // Names of all Elements
        std::vector<String> all_element_names() const;

        // Destory everything
        void clear();

        // Command Interface
        //============================================================
        // Bits that only Command objects will end up using

        size_type command_ref_count(ElementID const& elementid) const;

        // Adjust ref counts
        void increment_command_ref_count(ElementID const& elementid);
        void decrement_command_ref_count(ElementID const& elementid);



    private:
        String make_name_unique(String const& name);

        // Typedefs
        //============================================================
        class Element_Cache
        {
        public:
            // Special 6
            //============================================================
            Element_Cache(Element_Definition const& definition, String const& name = String()):
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
            std::vector<AttributeID> m_linked;    // where this Element is referenced
            size_type m_command_ref_count;  // how many Commands reference this Element

            // Attribute stats that we compute once?
        };


        //using tuple_type = std::tuple<Element, AttributeID, Vector_AttributeID, size_type>;
        using map_type = std::map < ElementID, Element_Cache >;


        using iterator = map_type::iterator;
        using const_iterator = map_type::const_iterator;

        /*
        iterator find(ElementID const& elementid);
        const_iterator cfind(ElementID const& elementid) const;

        enum Data_Index : size_type
        {
            Element = 0,
            Parent = 1,
            Linked = 2,
            Command_Ref_Count = 3
        };

        template <std::size_t I>
        static
        typename std::tuple_element<I, tuple_type>::type& get_iterator(iterator it)
        {
            return std::get<I>(it->second);
        }
*/

        // Helpers
        //============================================================
        //void cache_find(ElementID const& elementid);

        // Member Data
        //============================================================
        map_type m_map;
        //iterator m_last_find;

        mutable id_type m_next_id;
    };

} //namespace saklib

#endif // ELEMENT_MANAGER_H
