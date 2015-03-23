#ifndef ATTRIBUTEID_TYPE_H
#define ATTRIBUTEID_TYPE_H

#include "types.h"
#include "attributeid.h"

namespace Saklib
{
    /*
    AttributeID_Type<T>
    ====================================================================================================
    Templated type to provide direct typed access to the data in a given Attribute<T>

    This class may not make any sense anymore
    */
    template <typename T>
    class AttributeID_Type
    {
    public:
        using stored_type = T;
        using attribute_type = Attribute_Type < stored_type >;

        // Special 6
        //============================================================
        // Create an invalid id
        AttributeID_Type() :
            m_attributeid(),
            mp_attribute(nullptr)
        {}
        // Create a new id that references an Element of this type
        explicit AttributeID_Type(AttributeID const& attributeid) :
            m_attributeid(attributeid),
            mp_attribute(m_attributeid.attribute_type_cast<stored_type>())
        {}
        explicit AttributeID_Type(AttributeID && attributeid) :
			m_attributeid(std::move(attributeid)),
			mp_attribute(m_attributeid.attribute_type_cast<stored_type>())
		{}
        // Create a new id that references an Element of this type
        AttributeID_Type(ElementID const& elementid, String const& attribute_name) :
            m_attributeid(elementid, attribute_name),
            mp_attribute(m_attributeid.attribute_type_cast<stored_type>())
        {}
        // Create a new id that references an Element of this type
        AttributeID_Type(ElementID const& elementid, Attribute* attribute) :
            m_attributeid(elementid, attribute),
            mp_attribute(attribute_type_cast<stored_type>(attribute))
        {}
        // Create a new id that references an Element of this type
        AttributeID_Type(ElementID const& elementid, attribute_type* attribute) :
            m_attributeid(elementid, attribute),
            mp_attribute(attribute)
        {}

        // Implicit default destructor

        // Implicit default copy

        // Implicit default move

        // Interface
        //============================================================
        // Is this ElementID flagged as being Attribute data?
        bool is_valid() const                       { return mp_attribute != nullptr; }
        ElementID const& elementid() const          { return mp_attribute.elementid(); }
        AttributeID const& attributeid() const      { return mp_attribute; }
        String const& attribute_name() const        { return mp_attribute->name(); }

        attribute_type* attribute() const           { return mp_attribute; }

        // forwarding interface?
        // dereference operator?
        // how are we going to use this class?

    private:
        // Data
        //============================================================
        AttributeID m_attributeid;
        attribute_type* mp_attribute;
    };

    template <typename T>
    inline bool operator==(AttributeID_Type<T> const& lhs, AttributeID_Type<T> const& rhs)  { return lhs.attribute() == rhs.attribute(); }
    template <typename T>
    inline bool operator!=(AttributeID_Type<T> const& lhs, AttributeID_Type<T> const& rhs)  { return !operator==(lhs, rhs); }

    // Are these comparisons meaningful?
    template <typename T>
    inline bool operator< (AttributeID_Type<T> const& lhs, AttributeID_Type<T> const& rhs)  { return (lhs.elementid() < rhs.elementid()) && (lhs.attribute_name() < rhs.attribute_name()); }
    template <typename T>
    inline bool operator> (AttributeID_Type<T> const& lhs, AttributeID_Type<T> const& rhs)  { return operator<(rhs, lhs); }
    template <typename T>
    inline bool operator<=(AttributeID_Type<T> const& lhs, AttributeID_Type<T> const& rhs)  { return !operator>(lhs, rhs); }
    template <typename T>
    inline bool operator>=(AttributeID_Type<T> const& lhs, AttributeID_Type<T> const& rhs)  { return !operator<(lhs, rhs); }


} //namespace Saklib

#endif // ATTRIBUTEID_TYPE_H
