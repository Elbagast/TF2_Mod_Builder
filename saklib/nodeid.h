#ifndef NODEID_H
#define NODEID_H

#include "types.h"

namespace Saklib
{
    /*
    NodeID
    ====================================================================================================
    Dumb id data class for Nodes.
    */

    class NodeID
    {
    public:
        // Special 6
        //============================================================
        explicit NodeID(id_type value = invalid_id());

        // Implicit default destructor, copy, move

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

    NodeID invalid_NodeID();

    bool operator==(NodeID lhs, NodeID rhs);
    bool operator!=(NodeID lhs, NodeID rhs);
    bool operator< (NodeID lhs, NodeID rhs);
    bool operator> (NodeID lhs, NodeID rhs);
    bool operator<=(NodeID lhs, NodeID rhs);
    bool operator>=(NodeID lhs, NodeID rhs);

} //namespace Saklib


// Implementation
//----------------------------------------------------------------------------------------------------

// Special 6
//============================================================
inline
Saklib::NodeID::NodeID(id_type value):
   m_value(value)
{
}

// Interface
//============================================================
// The underlying id number
inline
Saklib::id_type Saklib::NodeID::value() const
{
    return m_value;
}
// Is the stored id number valid? DOES NOT CHECK WHETHER THIS ID IS USED IN A GIVEN MANAGER
inline
bool Saklib::NodeID::is_valid() const
{
    return m_value != invalid_id();
}

inline
Saklib::NodeID Saklib::invalid_NodeID()
{
    return NodeID();
}

inline
bool Saklib::operator==(NodeID lhs, NodeID rhs)
{
    return lhs.value() == rhs.value();
}

inline
bool Saklib::operator!=(NodeID lhs, NodeID rhs)
{
    return !operator==(lhs, rhs);
}

inline
bool Saklib::operator< (NodeID lhs, NodeID rhs)
{
    return lhs.value() < rhs.value();
}

inline
bool Saklib::operator> (NodeID lhs, NodeID rhs)
{
    return operator<(rhs, lhs);
}

inline
bool Saklib::operator<=(NodeID lhs, NodeID rhs)
{
    return !operator>(lhs, rhs);
}

inline
bool Saklib::operator>=(NodeID lhs, NodeID rhs)
{
    return !operator<(lhs, rhs);
}


#endif // NODEID_H
