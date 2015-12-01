#ifndef ELEMENTID_H
#define ELEMENTID_H

#include "types.h"

namespace saklib
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
        explicit ElementID(id_type value = invalid_id());
        ~ElementID() = default;

        ElementID(ElementID const& other) = default;
        ElementID& operator=(ElementID const& other) = default;

        // Implicit default move
        //ElementID(ElementID && other) = default;
        //ElementID& operator=(ElementID && other) = default;

        // Interface
        //============================================================
        // The underlying id number
        id_type value() const;
        // Is the stored id number valid? DOES NOT CHECK WHETHER THIS ID IS USED IN A GIVEN MANAGER
        bool is_valid() const;

    private:
        // Data
        //============================================================
        id_type m_value;
    };

    ElementID invalid_elementid();
            
    bool operator==(ElementID lhs, ElementID rhs);
    bool operator!=(ElementID lhs, ElementID rhs);
    bool operator< (ElementID lhs, ElementID rhs);
    bool operator> (ElementID lhs, ElementID rhs);
    bool operator<=(ElementID lhs, ElementID rhs);
    bool operator>=(ElementID lhs, ElementID rhs);

} //namespace saklib


// Implementation
//----------------------------------------------------------------------------------------------------

// Special 6
//============================================================
inline
saklib::ElementID::ElementID(id_type value):
   m_value(value)
{
}

// Interface
//============================================================
// The underlying id number
inline
saklib::id_type saklib::ElementID::value() const
{
    return m_value;
}
// Is the stored id number valid? DOES NOT CHECK WHETHER THIS ID IS USED IN A GIVEN MANAGER
inline
bool saklib::ElementID::is_valid() const
{
    return m_value != invalid_id();
}

inline
saklib::ElementID saklib::invalid_elementid()
{
    return ElementID();
}

inline
bool saklib::operator==(ElementID lhs, ElementID rhs)
{
    return lhs.value() == rhs.value();
}

inline
bool saklib::operator!=(ElementID lhs, ElementID rhs)
{
    return !operator==(lhs, rhs);
}

inline
bool saklib::operator< (ElementID lhs, ElementID rhs)
{
    return lhs.value() < rhs.value();
}

inline
bool saklib::operator> (ElementID lhs, ElementID rhs)
{
    return operator<(rhs, lhs);
}

inline
bool saklib::operator<=(ElementID lhs, ElementID rhs)
{
    return !operator>(lhs, rhs);
}

inline
bool saklib::operator>=(ElementID lhs, ElementID rhs)
{
    return !operator<(lhs, rhs);
}


#endif // ELEMENTID_H
