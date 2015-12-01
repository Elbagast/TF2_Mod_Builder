#ifndef ATTRIBUTEID_H
#define ATTRIBUTEID_H

#include "types.h"
#include "elementid.h"

namespace saklib
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
        explicit AttributeID(ElementID elementid = ElementID(), size_type attribute_index = 0);
        ~AttributeID() = default;

        AttributeID(AttributeID const& other) = default;
        AttributeID& operator=(AttributeID const& other) = default;

        // Implicit default move
        //AttributeID(AttributeID && other) = default;
        //AttributeID& operator=(AttributeID && other) = default;

        // Interface
        //============================================================
        ElementID elementid() const;
        size_type index() const;
        bool is_valid() const;

    private:
        // Data
        //============================================================
        ElementID m_elementid;
        size_type m_attribute_index;
    };

    AttributeID invalid_attributeid();

    bool operator==(AttributeID lhs, AttributeID rhs);
    bool operator!=(AttributeID lhs, AttributeID rhs);
    bool operator< (AttributeID lhs, AttributeID rhs);
    bool operator> (AttributeID lhs, AttributeID rhs);
    bool operator<=(AttributeID lhs, AttributeID rhs);
    bool operator>=(AttributeID lhs, AttributeID rhs);

} //namespace saklib

// Implementation
//----------------------------------------------------------------------------------------------------

// Special 6
//============================================================
inline
saklib::AttributeID::AttributeID(ElementID elementid, size_type attribute_index) :
    m_elementid(elementid),
    m_attribute_index(attribute_index)
{}

// Interface
//============================================================
inline
saklib::ElementID saklib::AttributeID::elementid() const
{
    return m_elementid;
}

inline
saklib::size_type saklib::AttributeID::index() const
{
    return m_attribute_index;
}

inline
bool saklib::AttributeID::is_valid() const
{
    return m_elementid.is_valid();
}

inline
saklib::AttributeID saklib::invalid_attributeid()
{
    return AttributeID();
}

inline
bool saklib::operator==(AttributeID lhs, AttributeID rhs)
{
    return (lhs.elementid() == rhs.elementid()) && (lhs.index() == rhs.index());
}

inline
bool saklib::operator!=(AttributeID lhs, AttributeID rhs)
{
    return !operator==(lhs, rhs);
}

inline
bool saklib::operator< (AttributeID lhs, AttributeID rhs)
{
    return (lhs.elementid() < rhs.elementid())|| ((lhs.elementid() == rhs.elementid()) && (lhs.index() < rhs.index()));
}

inline
bool saklib::operator> (AttributeID lhs, AttributeID rhs)
{
    return operator<(rhs, lhs);
}

inline
bool saklib::operator<=(AttributeID lhs, AttributeID rhs)
{
    return !operator>(lhs, rhs);
}

inline
bool saklib::operator>=(AttributeID lhs, AttributeID rhs)
{
    return !operator<(lhs, rhs);
}


#endif // ATTRIBUTEID_H
