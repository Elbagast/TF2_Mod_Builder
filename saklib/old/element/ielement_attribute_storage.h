#ifndef SAKLIB_IELEMENT_ATTRIBUTE_STORAGE_H
#define SAKLIB_IELEMENT_ATTRIBUTE_STORAGE_H

#include "../types.h"

namespace saklib
{
    class IAttribute_Base;
    /*
    IElement_Attribute_Storage
    ====================================================================================================
    */
    class IElement_Attribute_Storage
    {
    public:
        // Special 6
        //============================================================
        virtual ~IElement_Attribute_Storage() = default;

        // Interface
        //============================================================
        // How many Attributes does this Element have?
        size_type attribute_count() const                               { return v_attribute_count(); }

        // How many Attributes of the given type does this Element have?
        size_type attribute_count_of_type(Type_Enum type) const         { return v_attribute_count_of_type(type); }

        // Does this have an Attribute with this name or index?
        bool has_attribute(String const& name) const                    { return v_has_attribute(name); }
        bool has_attribute(size_type index) const                       { return v_has_attribute(index); }

        // Get the Attribute with this name or index, return nullptr if not found
        IAttribute_Base* attribute(String const& name)                  { return v_attribute(name); }
        IAttribute_Base* attribute(size_type index)                     { return v_attribute(index); }

        IAttribute_Base const* cattribute(String const& name) const     { return v_cattribute(name); }
        IAttribute_Base const* cattribute(size_type index) const        { return v_cattribute(index); }

        // Get a Vector of all the Attribute names
        std::vector<String> attribute_names() const                     { return v_attribute_names(); }


    protected:
        // Virtuals
        //============================================================
        virtual size_type v_attribute_count() const = 0;
        virtual size_type v_attribute_count_of_type(Type_Enum type) const = 0;

        virtual bool v_has_attribute(String const& name) const = 0;
        virtual bool v_has_attribute(size_type index) const = 0;

        virtual IAttribute_Base* v_attribute(String const& name) = 0;
        virtual IAttribute_Base* v_attribute(size_type index) = 0;

        virtual IAttribute_Base const* v_cattribute(String const& name) const = 0;
        virtual IAttribute_Base const* v_cattribute(size_type index) const = 0;

        virtual std::vector<String> v_attribute_names() const = 0;
    };


} // namespace saklib

#endif // SAKLIB_IELEMENT_ATTRIBUTE_STORAGE_H

