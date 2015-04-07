#ifndef PROXYID_H
#define PROXYID_H

#include "types.h"
#include "elementid.h"
#include "attributeid.h"
#include <numeric>

namespace Saklib
{
    /*
    ProxyID
    ====================================================================================================
    Pack an ElementID or AttributeID into a stucture that is 4 bytes long.
    */

    class ProxyID
    {
    public:
        friend bool operator==(ProxyID lhs, ProxyID rhs);
        friend bool operator< (ProxyID lhs, ProxyID rhs);

        // Special 6
        //============================================================
        ProxyID();
        explicit ProxyID(ElementID elementid);
        explicit ProxyID(AttributeID attributeid);

        ProxyID(ProxyID const& other) = default;
        ProxyID& operator=(ProxyID const& other) = default;
        // Interface
        //============================================================
        size_type elementid_value() const;

        ElementID elementid() const;

        size_type attribute_index() const;

        AttributeID attributeid() const;

        // Does this contain a valid ElementID?
        bool is_valid() const;

        // Does this contain an ElementID?
        bool is_element() const;

        // Does this contain an AttributeID?
        bool is_attribute() const;

        inline bool is_attribute_flag_set() const;

        static
        size_type max_elementid_value();

        static
        size_type max_attribute_index();

        // Packing and Unpacking into size_type (unsigned int)
        //============================================================
        static
        size_type pack(ProxyID proxyid);

        static
        size_type pack(ElementID elementid);

        static
        size_type pack(AttributeID attributeid);

        static
        ProxyID unpack(size_type raw_value);

    private:
        // Internal Data Packing
        //============================================================
        static
        unsigned short pack_elementid_value(size_type value);

        static
        short pack_attribute_index(size_type index);

        // Data
        //============================================================
        unsigned short m_elementid_value;
        unsigned short m_attribute_index;
    };

    ProxyID invalid_proxyid();

    bool operator==(ProxyID lhs, ProxyID rhs);
    bool operator!=(ProxyID lhs, ProxyID rhs);
    bool operator< (ProxyID lhs, ProxyID rhs);
    bool operator> (ProxyID lhs, ProxyID rhs);
    bool operator<=(ProxyID lhs, ProxyID rhs);
    bool operator>=(ProxyID lhs, ProxyID rhs);

} //namespace Saklib


// Implementation
//----------------------------------------------------------------------------------------------------

// Special 6
//============================================================
inline
Saklib::ProxyID::ProxyID() :
    m_elementid_value{ 0 },
    m_attribute_index{ 0 }
{}

inline
Saklib::ProxyID::ProxyID(ElementID elementid) :
    m_elementid_value{ pack_elementid_value(elementid.value()) },
    m_attribute_index{ 0 }
{}

#pragma GCC diagnostic ignored "-Wnarrowing"
inline
Saklib::ProxyID::ProxyID(AttributeID attributeid) :
    m_elementid_value{ pack_elementid_value(attributeid.elementid().value()) },
    m_attribute_index{ pack_attribute_index(attributeid.index()) }
{}
#pragma GCC diagnostic pop

// Interface
//============================================================
inline
Saklib::size_type Saklib::ProxyID::elementid_value() const
{
    return static_cast<unsigned int>(m_elementid_value);
}

inline
Saklib::ElementID Saklib::ProxyID::elementid() const
{
    return ElementID(elementid_value());
}

inline
Saklib::size_type Saklib::ProxyID::attribute_index() const
{
    unsigned short attribute_index{ m_attribute_index };
    // unset the last bit before converting
    attribute_index &= ~(1 << (sizeof(unsigned short) * 8 - 1));
    return static_cast<unsigned int>(attribute_index);
}

inline
Saklib::AttributeID Saklib::ProxyID::attributeid() const
{
    if (is_attribute())
        return AttributeID(elementid(), attribute_index());
    else
        return AttributeID();
}

// Does this contain a valid ElementID?
inline
bool Saklib::ProxyID::is_valid() const
{
    return m_elementid_value != 0;
}

// Does this contain an ElementID?
inline
bool Saklib::ProxyID::is_element() const
{
    return is_valid() && !is_attribute_flag_set();
}

// Does this contain an AttributeID?
inline
bool Saklib::ProxyID::is_attribute() const
{
    return is_valid() && is_attribute_flag_set();
}

inline
bool Saklib::ProxyID::is_attribute_flag_set() const
{
    return (m_attribute_index >>(sizeof(short) * 8 - 1) & 1);
}

inline
Saklib::size_type Saklib::ProxyID::max_elementid_value()
{
    return static_cast<size_type>(std::numeric_limits<unsigned short>::max());
}

inline
Saklib::size_type Saklib::ProxyID::max_attribute_index()
{
    return static_cast<size_type>(std::numeric_limits<short>::max());
}

// Packing and Unpacking into size_type (unsigned int)
//============================================================
inline
Saklib::size_type Saklib::ProxyID::pack(ProxyID proxyid)
{
    size_type result{0};
    assert(sizeof(result) == sizeof(proxyid));
    memcpy(static_cast<void*>(&result), static_cast<void const*>(&proxyid), sizeof(proxyid));
    return result;
}

inline
Saklib::size_type Saklib::ProxyID::pack(ElementID elementid)
{
    ProxyID proxyid{elementid};
    size_type result{0};
    assert(sizeof(result) == sizeof(proxyid));
    memcpy(static_cast<void*>(&result), static_cast<void const*>(&proxyid), sizeof(proxyid));
    return result;
}

inline
Saklib::size_type Saklib::ProxyID::pack(AttributeID attributeid)
{
    ProxyID proxyid{attributeid};
    size_type result{0};
    assert(sizeof(result) == sizeof(proxyid));
    memcpy(static_cast<void*>(&result), static_cast<void const*>(&proxyid), sizeof(proxyid));
    return result;
}

inline
Saklib::ProxyID Saklib::ProxyID::unpack(size_type raw_value)
{
    ProxyID result{};
    assert(sizeof(result) == sizeof(raw_value));
    memcpy(static_cast<void*>(&result), static_cast<void const*>(&raw_value), sizeof(raw_value));
    return result;
}

// Internal Data Packing
//============================================================
inline
unsigned short Saklib::ProxyID::pack_elementid_value(size_type value)
{
    assert(value <= max_elementid_value());
    return static_cast<unsigned short>(value);
}

inline
short Saklib::ProxyID::pack_attribute_index(size_type index)
{
    assert(index <= max_attribute_index());
    unsigned short packed = static_cast<unsigned short>(index);
    // now set the last bit
    packed |= 1 << (sizeof(short) * 8 - 1);
    return packed;
}

inline Saklib::ProxyID Saklib::invalid_proxyid()
{
    return ProxyID();
}

inline
bool Saklib::operator==(ProxyID lhs, ProxyID rhs)
{
    return (lhs.m_elementid_value == rhs.m_elementid_value) && (lhs.m_attribute_index == rhs.m_attribute_index);

}
inline
bool Saklib::operator!=(ProxyID lhs, ProxyID rhs)
{
    return !operator==(lhs, rhs);
}

inline
bool Saklib::operator< (ProxyID lhs, ProxyID rhs)
{
    return (lhs.m_elementid_value < rhs.m_elementid_value)
            || ((lhs.m_elementid_value == rhs.m_elementid_value) && (lhs.m_attribute_index < rhs.m_attribute_index));
}

inline
bool Saklib::operator> (ProxyID lhs, ProxyID rhs)
{
    return operator<(rhs, lhs);
}

inline
bool Saklib::operator<=(ProxyID lhs, ProxyID rhs)
{
    return !operator>(lhs, rhs);
}

inline
bool Saklib::operator>=(ProxyID lhs, ProxyID rhs)
{
    return !operator<(lhs, rhs);
}

#endif // PROXYID_H
