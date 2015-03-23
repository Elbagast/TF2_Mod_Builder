#ifndef ELEMENTID_H
#define ELEMENTID_H

#include "types.h"

namespace Saklib
{
    /*
    ElementID
    ====================================================================================================
    Dumb id data class for Elements.
    */

    class ElementID
    {
    public:
        // Special 6
        //============================================================
        explicit ElementID(id_type value = invalid_id()):
            m_value(value)
        {
        }
        ~ElementID() = default;

        ElementID(ElementID const& other) = default;
        ElementID& operator=(ElementID const& other) = default;

        // Implicit default move
        //ElementID(ElementID && other) = default;
        //ElementID& operator=(ElementID && other) = default;

        // Interface
        //============================================================
        // The underlying id number
        id_type value() const { return m_value; }
        // Is the stored id number valid? DOES NOT CHECK WHETHER THIS ID IS USED IN A GIVEN MANAGER
        bool is_valid() const { return m_value != invalid_id(); }

    private:
        // Data
        //============================================================
        id_type m_value;
    };

    inline ElementID invalid_elementid() { return ElementID(); }
            
    inline bool operator==(ElementID lhs, ElementID rhs) { return lhs.value() == rhs.value(); }
    inline bool operator!=(ElementID lhs, ElementID rhs) { return !operator==(lhs, rhs); }
    inline bool operator< (ElementID lhs, ElementID rhs) { return lhs.value() < rhs.value(); }
    inline bool operator> (ElementID lhs, ElementID rhs) { return operator<(rhs, lhs); }
    inline bool operator<=(ElementID lhs, ElementID rhs) { return !operator>(lhs, rhs); }
    inline bool operator>=(ElementID lhs, ElementID rhs) { return !operator<(lhs, rhs); }

} //namespace Saklib

#endif // ELEMENTID_H
