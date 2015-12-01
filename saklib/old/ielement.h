#ifndef IELEMENT_H
#define IELEMENT_H

#include "types.h"

namespace saklib
{
    class IAttribute;

    /*
    IElement
    ====================================================================================================
    Interface class for access to Elements regardless of how or where they're implemented.
    */
    class IElement
    {
    public:
        // Special 6
        //============================================================
        virtual ~IElement() = 0;

        // Basic Access...These are essentially hidden Attributes...
        //============================================================
        String const& type() const                              { return v_type(); }
        bool can_be_root() const                                { return v_can_be_root(); }

        String const& name() const                              { return v_name(); }
        void set_name(String const& name)                       { v_set_name(name); }

        // Attributes Access
        //============================================================
        // How many Attributes does this Element have?
        size_type attribute_count() const                       { return v_attribute_count(); }

        // How many Attributes of the given type does this Element have?
        size_type attribute_count_of_type(Type_Enum type) const { return v_attribute_count_of_type(type); }

        // Does this have an Attribute with this name or index?
        bool has_attribute(String const& name) const            { return v_has_attribute(name); }
        bool has_attribute(size_type index) const               { return v_has_attribute(index); }

        // Get the Attribute with this name or index, return nullptr if not found
        IAttribute* attribute(String const& name)               { return v_attribute(name); }
        IAttribute* attribute(size_type index)                  { return v_attribute(index); }

        IAttribute const* cattribute(String const& name) const  { return v_cattribute(name); }
        IAttribute const* cattribute(size_type index) const     { return v_cattribute(index); }

        // Get a Vector of all the Attribute names
        std::vector<String> attribute_names() const                   { return v_attribute_names(); }


    protected:
        virtual String const& v_type() const = 0;
        virtual bool v_can_be_root() const = 0;

        virtual String const& v_name() const = 0;
        virtual void v_set_name(String const& name) = 0;

        virtual size_type v_attribute_count() const = 0;
        virtual size_type v_attribute_count_of_type(Type_Enum type) const = 0;

        virtual bool v_has_attribute(String const& name) const = 0;
        virtual bool v_has_attribute(size_type index) const = 0;

        virtual IAttribute* v_attribute(String const& name) = 0;
        virtual IAttribute* v_attribute(size_type index) = 0;

        virtual IAttribute const* v_cattribute(String const& name) const = 0;
        virtual IAttribute const* v_cattribute(size_type index) const = 0;

        virtual std::vector<String> v_attribute_names() const = 0;
    };


} // namespace saklib

// Implementation
//----------------------------------------------------------------------------------------------------
// Special 6
//============================================================
inline
saklib::IElement::~IElement() = default;

#endif // IELEMENT_H

