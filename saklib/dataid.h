#ifndef DATAID_H
#define DATAID_H

#include "types.h"

namespace Saklib
{
    /*
    DataID
    ====================================================================================================
    Dumb id data class for Nodes.
    */

    class DataID
    {
    public:
        // Special 6
        //============================================================
        explicit DataID(id_type value = invalid_id());

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

    DataID invalid_DataID();

    bool operator==(DataID lhs, DataID rhs);
    bool operator!=(DataID lhs, DataID rhs);
    bool operator< (DataID lhs, DataID rhs);
    bool operator> (DataID lhs, DataID rhs);
    bool operator<=(DataID lhs, DataID rhs);
    bool operator>=(DataID lhs, DataID rhs);

} //namespace Saklib


// Implementation
//----------------------------------------------------------------------------------------------------

// Special 6
//============================================================
inline
Saklib::DataID::DataID(id_type value):
   m_value(value)
{
}

// Interface
//============================================================
// The underlying id number
inline
Saklib::id_type Saklib::DataID::value() const
{
    return m_value;
}
// Is the stored id number valid? DOES NOT CHECK WHETHER THIS ID IS USED IN A GIVEN MANAGER
inline
bool Saklib::DataID::is_valid() const
{
    return m_value != invalid_id();
}

inline
Saklib::DataID Saklib::invalid_DataID()
{
    return DataID();
}

inline
bool Saklib::operator==(DataID lhs, DataID rhs)
{
    return lhs.value() == rhs.value();
}

inline
bool Saklib::operator!=(DataID lhs, DataID rhs)
{
    return !operator==(lhs, rhs);
}

inline
bool Saklib::operator< (DataID lhs, DataID rhs)
{
    return lhs.value() < rhs.value();
}

inline
bool Saklib::operator> (DataID lhs, DataID rhs)
{
    return operator<(rhs, lhs);
}

inline
bool Saklib::operator<=(DataID lhs, DataID rhs)
{
    return !operator>(lhs, rhs);
}

inline
bool Saklib::operator>=(DataID lhs, DataID rhs)
{
    return !operator<(lhs, rhs);
}

#endif // DATAID_H

