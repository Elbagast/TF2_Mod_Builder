#ifndef PROXYID_H
#define PROXYID_H

#include "types.h"
#include "elementid.h"
#include "attributeid.h"
//#include <numeric>
//#include <QtDebug>

namespace Saklib
{
    /*
    ProxyID
    ====================================================================================================
    Pack an ElementID or AttributeID into a stucture that is sizeof(void*).
    */

    class ProxyID
    {
    public:
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

        bool is_attribute_flag_set() const;

        static
        size_type max_elementid_value();

        static
        size_type max_attribute_index();

        // Packing and Unpacking into size_type
        //============================================================
        static
        size_type pack(ProxyID proxyid);

        static
        size_type pack(ElementID elementid);

        static
        size_type pack(AttributeID attributeid);

        static
        ProxyID unpack(size_type raw_value);

        // Operators
        //============================================================
        bool operator==(ProxyID const& other) const;
        bool operator!=(ProxyID const& other) const;

    private:
        // Internal Data Packing
        //============================================================
        void pack_elementid_value(size_type value);

        void pack_attribute_index(size_type index);

        static
        size_type const s_data_size{sizeof(void*)};

        static
        size_type const s_data_half_size{s_data_size / 2};

        static
        size_type const s_count_to_last_byte{s_data_size - 1};
        /*
        unsigned char* data_start()
        {
            return m_data;
        }

        unsigned char* data_half_start()
        {
            return m_data + s_data_half_size;
        }
        unsigned char* data_last()
        {
            return m_data + s_count_to_last_byte;
        }
        */
        void clear_data();

        // Data
        //============================================================
        unsigned char m_data[s_data_size];
    };

    static_assert(sizeof(ProxyID) == sizeof(void*), "ProxyID size mismatch with void*.");
    static_assert(sizeof(ProxyID) == sizeof(size_type), "ProxyID size mismatch with size_type.");

    ProxyID invalid_proxyid();

} //namespace Saklib


// Implementation
//----------------------------------------------------------------------------------------------------

// Special 6
//============================================================
inline
Saklib::ProxyID::ProxyID()
{
    clear_data();
}

inline
Saklib::ProxyID::ProxyID(ElementID elementid)
{
    clear_data();
    pack_elementid_value(elementid.value());
    assert(elementid.value() == elementid_value());
}

//#pragma GCC diagnostic ignored "-Wnarrowing"
inline
Saklib::ProxyID::ProxyID(AttributeID attributeid) :
    ProxyID(attributeid.elementid())
{
    pack_attribute_index(attributeid.index());

    //qDebug() << "AttributeID.index in: " << attributeid.index() << "out:" << attribute_index();
    assert(attributeid.index() == attribute_index());
}
//#pragma GCC diagnostic pop

// Interface
//============================================================
inline
Saklib::size_type Saklib::ProxyID::elementid_value() const
{
    size_type value{0};
    memcpy(static_cast<void*>(&value), static_cast<void const*>(m_data), s_data_half_size);
    return value;
}

inline
Saklib::ElementID Saklib::ProxyID::elementid() const
{
    return ElementID(elementid_value());
}

inline
Saklib::size_type Saklib::ProxyID::attribute_index() const
{
    unsigned int index_out{ 0 };

    memcpy(static_cast<void*>(&index_out), static_cast<void const*>(m_data + s_data_half_size), s_data_half_size);

    index_out &= ~(1 << (s_data_half_size * 8 - 1));

    return index_out;
}

inline
Saklib::AttributeID Saklib::ProxyID::attributeid() const
{
    if (is_attribute())
        return AttributeID(elementid(), attribute_index());
    else
        return invalid_attributeid();
}

// Does this contain a valid ElementID?
inline
bool Saklib::ProxyID::is_valid() const
{
    return elementid_value() != 0;
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
    return (m_data[s_count_to_last_byte] >>(7) & 1);
}

inline
Saklib::size_type Saklib::ProxyID::max_elementid_value()
{
    size_type max_value{0};
    // set bits 0 to sizeof(size_type) / 2 * 8 to 1
    for (size_type bit = 0, end = sizeof(size_type) / 2 * 8; bit != end; ++bit)
    {
        max_value |= (1 << bit);
    }
    return max_value;
}

inline
Saklib::size_type Saklib::ProxyID::max_attribute_index()
{
    size_type max_value{0};
    // set bits 0 to sizeof(size_type) / 2 * 8 - 1 to 1
    for (size_type bit = 0, end = sizeof(size_type) / 2 * 8 - 1; bit != end; ++bit)
    {
        max_value |= (1 << bit);
    }
    return max_value;
}

// Packing and Unpacking into size_type
//============================================================
inline
Saklib::size_type Saklib::ProxyID::pack(ProxyID proxyid)
{
    size_type result{0};
    memcpy(static_cast<void*>(&result), static_cast<void const*>(&proxyid), sizeof(proxyid));
    return result;
}

inline
Saklib::size_type Saklib::ProxyID::pack(ElementID elementid)
{
    ProxyID proxyid{elementid};
    size_type result{0};
    memcpy(static_cast<void*>(&result), static_cast<void const*>(&proxyid), sizeof(proxyid));
    return result;
}

inline
Saklib::size_type Saklib::ProxyID::pack(AttributeID attributeid)
{
    ProxyID proxyid{attributeid};
    size_type result{0};
    memcpy(static_cast<void*>(&result), static_cast<void const*>(&proxyid), sizeof(proxyid));
    return result;
}

inline
Saklib::ProxyID Saklib::ProxyID::unpack(size_type raw_value)
{
    ProxyID result{};
    memcpy(static_cast<void*>(&result), static_cast<void const*>(&raw_value), sizeof(raw_value));
    return result;
}

// Operators
//============================================================
inline
bool Saklib::ProxyID::operator==(ProxyID const& other) const
{
    for (size_type index = 0; index != s_data_size; ++index)
    {
        if (m_data[index] != other.m_data[index])
        {
            return false;
        }
    }
    return true;
}
inline
bool Saklib::ProxyID::operator!=(ProxyID const& other) const
{
    return !operator==(other);
}

// Internal Data Packing
//============================================================
inline
void Saklib::ProxyID::pack_elementid_value(size_type value)
{
    assert(value <= max_elementid_value());
    // copy the first half of value into the front of m_data
    memcpy(static_cast<void*>(m_data), static_cast<void const*>(&value), s_data_half_size);
}

inline
void Saklib::ProxyID::pack_attribute_index(size_type index)
{
    assert(index <= max_attribute_index());
    // copy the first half of value into the front of m_data
    memcpy(static_cast<void*>(m_data + s_data_half_size), static_cast<void const*>(&index), s_data_half_size);
    // now set the last bit
    m_data[s_count_to_last_byte] |= 1 << (7);
}

inline
void Saklib::ProxyID::clear_data()
{
    std::fill_n(m_data, s_data_size, 0);
}

inline
Saklib::ProxyID Saklib::invalid_proxyid()
{
    return ProxyID();
}


#endif // PROXYID_H
