#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "types.h"

namespace Saklib
{
    class Attribute_Definition;

    /*
    Attribute
    ====================================================================================================
    Abstract base class for attributes which defines the generic parts of the interface for Attributes.
    */
    class Attribute
    {
    public:
        // Special 6
        //============================================================
        Attribute() = default;
        virtual ~Attribute() = default;

        // NO COPYING
        Attribute(Attribute const& other) = delete;
        Attribute& operator=(Attribute const& other) = delete;

        // General Interface
        //============================================================
        String const& name() const      { return v_name(); }
        Type_Enum type_enum() const     { return v_type_enum(); }
        String type_string() const      { return v_type_string(); } // could probably make this into a non-virtual call...
        
        bool is_simple_type() const     { return Saklib::is_simple_type(type_enum()); }
        bool is_vector_type() const     { return Saklib::is_vector_type(type_enum()); }
        bool is_constrained() const     { return v_is_constrained(); }

        // hmmmmmm
        //bool is_linked() const          { return v_is_linked(); }
        
    protected:
        // Virtuals
        //============================================================
        virtual String const& v_name() const = 0;
        virtual Type_Enum v_type_enum() const = 0;
        virtual String v_type_string() const = 0;

        virtual bool v_is_constrained() const = 0;
    };

    Uptr<Attribute> make_Attribute(Shptr<Attribute_Definition> const& definition);

} // namespace Saklib

#endif // ATTRIBUTE_H
