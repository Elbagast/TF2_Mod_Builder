#ifndef ELEMENT_DEFINITION_H
#define ELEMENT_DEFINITION_H

#include "types.h"
#include "all_attribute_definitions.h"

namespace Saklib
{
    /*
    Element_Definition
    ====================================================================================================
    Class that contains all the data needed to construct an Element of the configuration defined.
    */
    class Element_Definition
    {
    public:
        // Special 6
        //============================================================
        Element_Definition() :
            m_element_type("UndefinedElement"),
            m_can_be_root(false),
            m_attribute_definitions()
        {}
        explicit Element_Definition(String const& type, bool can_be_root = false) :
            m_element_type(type),
            m_can_be_root(can_be_root),
            m_attribute_definitions()
        {}
        Element_Definition(String const& type, bool can_be_root, Vector<Shptr<Attribute_Definition>> const& attribute_definitions) :
            m_element_type(type),
            m_can_be_root(can_be_root),
            m_attribute_definitions(attribute_definitions)
        {
        }
        ~Element_Definition() = default;

        // NO COPYING
        Element_Definition(Element_Definition const& other) = delete;
        Element_Definition& operator=(Element_Definition const& other) = delete;

        // VS2013 is being a git here. Not only can I not '= default' these, it insists on trying to copy
        // this class if they aren't defined. Even though copy is deleted. WTF
        Element_Definition(Element_Definition && other) :
            m_element_type(std::move(other.m_element_type)),
            m_can_be_root(std::move(other.m_can_be_root)),
            m_attribute_definitions(std::move(other.m_attribute_definitions))
        {}
        Element_Definition& operator=(Element_Definition && other)
        {
            m_element_type = std::move(other.m_element_type);
            m_can_be_root = std::move(other.m_can_be_root);
            m_attribute_definitions = std::move(other.m_attribute_definitions);
            return *this;
        }
        // Interface
        //============================================================
        String const& type() const
        {
            return m_element_type;
        }
        void set_type(String const& value);

        bool can_be_root() const
        {
            return m_can_be_root;
        }
        void set_can_be_root(bool state);

        Vector<Shptr<Attribute_Definition>> const& attribute_definitions() const
        {
            return m_attribute_definitions;
        }

        template <typename T>
        void add_attribute_definition(Uptr<Attribute_Definition_Type<T>>& definition)
        {
            m_attribute_definitions.emplace_back(definition.release());
        }

    private:
        // Data Members - these can't be constant, move-assignment is needed for use of this class in a std::map
        //============================================================
        String m_element_type;
        bool m_can_be_root;
        Vector<Shptr<Attribute_Definition>> m_attribute_definitions;

        // if you wanted to cache stats about this Element type, data would go here
    };

    
    inline bool operator==(Element_Definition const& lhs, Element_Definition const& rhs)
    { 
        return lhs.type() == rhs.type();
            //&& lhs.attribute_definitions() == rhs.attribute_definitions();
    }
    inline bool operator!=(Element_Definition const& lhs, Element_Definition const& rhs) { return !operator==(lhs, rhs); }
     
} // namespace Saklib

#endif // ELEMENT_DEFINITION_H
