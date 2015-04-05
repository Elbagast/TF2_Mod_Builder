#ifndef ELEMENT_H
#define ELEMENT_H

#include "types.h"
#include "type_traits.h"
#include "fwd_attribute_type.h"


namespace Saklib
{  
    class Element_Definition;
    class Attribute;
    /*
    Element
    ====================================================================================================
    Data storage class which forms the backbone of a dictionary of attributes of different types. All of
    the data it stores are dumb types.

    Element doesn't track its parent, as it may be referenced be more than one other Element, so you
    will have to track that elsewhere if you need to.
    */
    class Element
    {
    public:
        // Special 6
        //============================================================
        Element(Element_Definition const& definition, String const& name = String());
        ~Element();

        // NO COPYING
        Element(Element const& other) = delete;
        Element& operator=(Element const& other) = delete;

        // Explicit default move (thanks Microsoft...)
        Element(Element && other);
        Element& operator=(Element && other);

        // Basic Access
        //============================================================
        String const& type() const;
        bool can_be_root() const;

        String const& name() const;
        void set_name(String const& name);

        // Attributes Access
        //============================================================
        // How many Attributes does this Element have?
        size_type attribute_count() const;

        // How many Attributes of the given type does this Element have?
        template <typename T>
        size_type attribute_count_type() const
        {
            size_type count{0};
            for (auto const& attribute : m_attributes)
                if (attribute->type_enum() == Type_Traits<T>::type_enum_value)
                    ++count;
            return count;
        }
        template <Type_Enum TE>
        size_type attribute_count_enum() const
        {
            return attribute_count_type<TypeHolder_st<TE>>();
        }

        // Does this have an Attribute with this name?
        bool has_attribute(String const& name) const;

        // Get the Attribute with this name, nullptr if not found
        Attribute* attribute(String const& name) const;

        // Get the Attribute at this index, nullptr if not found
        Attribute* attribute(size_type index) const;

        // Get a Vector of all the Attribute names
        Vector_String attribute_names() const;

        // Access to all of the Attributes - since std::unique_ptr::get() is const we can edit Attributes via this function
        Vector<Uptr<Attribute>> const& attributes() const;
        
        // Get a pointer to a derived Attribute type for the Attribute specified by name
        template <typename Stored_Type>
        Attribute_Type<Stored_Type>* attribute_type_cast(String const& name) const
        {
            return dynamic_cast<Attribute_Type<Stored_Type>*>(attribute(name));
        }
        template <typename Stored_Type>
        Attribute_Type<Stored_Type>* attribute_type_cast(size_type index) const
        {
            return dynamic_cast<Attribute_Type<Stored_Type>*>(m_attributes.at(index).get());
        }
        template <Type_Enum TE>
        Attribute_Type<TypeHolder_st<TE> >* attribute_enum_cast(String const& name) const
        {
            return dynamic_cast<Attribute_Type<TypeHolder_st<TE> >*>(attribute(name));
        }
        template <Type_Enum TE>
        Attribute_Type<TypeHolder_st<TE> >* attribute_enum_cast(size_type index) const
        {
            return dynamic_cast<Attribute_Type<TypeHolder_st<TE> >*>(m_attributes.at(index).get());
        }
        

    private:
        // Data
        //============================================================
        String m_type;
        String m_name;
        bool m_can_be_root;
        Vector<Uptr<Attribute>> m_attributes;
        // maybe cache stats here?

    };


} // namespace Saklib

#endif // ELEMENT_H
