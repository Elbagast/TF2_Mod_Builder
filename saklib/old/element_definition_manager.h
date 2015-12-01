#ifndef ELEMENT_DEFINITION_MANAGER_H
#define ELEMENT_DEFINITION_MANAGER_H

#include "types.h"
#include "element_definition.h"

namespace saklib
{
    class Attribute;
    /*
    Element_Definition_Manager
    ====================================================================================================
    Class which stores Element_Definiton objects
    */
    class Element_Definition_Manager
    {
    public:
        // Special 6
        //============================================================
        Element_Definition_Manager();
        ~Element_Definition_Manager();

        // NO COPYING - contains polymorphic types
        Element_Definition_Manager(Element_Definition_Manager const& other) = delete;
        Element_Definition_Manager& operator=(Element_Definition_Manager const& other) = delete;

        // Implicit default move
        Element_Definition_Manager(Element_Definition_Manager && other);
        Element_Definition_Manager& operator=(Element_Definition_Manager && other);

        // Interface
        //============================================================
        // Is an Element_Definition with this type registered?
        bool definition_exists(String const& type) const;
        // Is an Element_Definition with this exact configuration registered?
        bool definition_exists(Element_Definition const& definition) const;
        // If an Element_Definition with the same configuration as arg does not exist, add it do the definitions
        bool try_add_definition(Element_Definition&& definition);
        // Add this Element_Definition, overriding any definitions that might match
        void add_override_definition(Element_Definition&& definition);
        // Get a vector of the registered types

        std::vector<Element_Definition> const& definitions() const { return m_definitions; }
        std::vector<String> definition_types() const;

        // Get the definition
        Element_Definition const& definition(String const& type) const;

    private:
        // Data Members
        //============================================================
        std::vector<Element_Definition>::iterator find_definition(String const& type);
        std::vector<Element_Definition>::const_iterator find_definition(String const& type) const;
        std::vector<Element_Definition>::iterator find_definition(Element_Definition const& definition);
        std::vector<Element_Definition>::const_iterator find_definition(Element_Definition const& definition) const;

        void add_definition(Element_Definition&& definition);

        std::vector<Element_Definition> m_definitions;
    };


} // namespace saklib

#endif // ELEMENT_DEFINITION_MANAGER_H
