#ifndef ATTRIBUTEID_H
#define ATTRIBUTEID_H

#include "types.h"
#include "elementid.h"

namespace Saklib
{

    /*
    AttributeID
    ====================================================================================================
    Dumb data id to access an Attribute as an index of a given Element, via an ElementID. You will need
    a manager to use this class

    DOES NOT GUARANTEE THE VALIDITY OF THE STORED INDEX
    */
    class AttributeID
    {
    public:
        // Special 6
        //============================================================
        // Create a new id that references an Element of this type
        explicit AttributeID(ElementID elementid = ElementID(), size_type attribute_index = 0) :
            m_elementid(elementid),
            m_attribute_index(attribute_index)
        {}
        ~AttributeID() = default;

        AttributeID(AttributeID const& other) = default;
        AttributeID& operator=(AttributeID const& other) = default;

        // Implicit default move
        //AttributeID(AttributeID && other) = default;
        //AttributeID& operator=(AttributeID && other) = default;

        // Interface
        //============================================================
        ElementID elementid() const { return m_elementid; }
        size_type index() const     { return m_attribute_index; }
        bool is_valid() const       { return m_elementid.is_valid(); }

    private:
        // Data
        //============================================================
        ElementID m_elementid;
        size_type m_attribute_index;
    };

    inline AttributeID invalid_attributeid() { return AttributeID(); }

    inline bool operator==(AttributeID lhs, AttributeID rhs)  { return (lhs.elementid() == rhs.elementid()) && (lhs.index() == rhs.index()); }
    inline bool operator!=(AttributeID lhs, AttributeID rhs)  { return !operator==(lhs, rhs); }
    inline bool operator< (AttributeID lhs, AttributeID rhs)
    {
        return (lhs.elementid() < rhs.elementid())|| ((lhs.elementid() == rhs.elementid()) && (lhs.index() < rhs.index()));
    }
    inline bool operator> (AttributeID lhs, AttributeID rhs)  { return operator<(rhs, lhs); }
    inline bool operator<=(AttributeID lhs, AttributeID rhs)  { return !operator>(lhs, rhs); }
    inline bool operator>=(AttributeID lhs, AttributeID rhs)  { return !operator<(lhs, rhs); }


} //namespace Saklib

#endif // ATTRIBUTEID_H
