#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "types.h"

namespace saklib
{
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
        Attribute();
        virtual ~Attribute();

        // NO COPYING
        Attribute(Attribute const& other) = delete;
        Attribute& operator=(Attribute const& other) = delete;

        // Implcit default move
        //Attribute(Attribute && other) = default;
        //Attribute& operator=(Attribute && other) = default;

        // General Interface
        //============================================================
        String const& name() const;
        Type_Enum type_enum() const;
        String type_string() const;
        
        bool is_simple_type() const;
        bool is_vector_type() const;
        bool is_constrained() const;

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

} // namespace saklib

// Implementation
//----------------------------------------------------------------------------------------------------
// Special 6
//============================================================
inline
saklib::Attribute::Attribute() = default;

inline
saklib::Attribute::~Attribute() = default;

// General Interface
//============================================================
inline
saklib::String const& saklib::Attribute::name() const
{
    return v_name();
}

inline
saklib::Type_Enum saklib::Attribute::type_enum() const
{
    return v_type_enum();
}

inline
saklib::String saklib::Attribute::type_string() const
{
    return v_type_string();
} // could probably make this into a non-virtual call...

inline
bool saklib::Attribute::is_simple_type() const
{
    return saklib::is_simple_type(type_enum());
}

inline
bool saklib::Attribute::is_vector_type() const
{
    return saklib::is_vector_type(type_enum());
}

inline
bool saklib::Attribute::is_constrained() const
{
    return v_is_constrained();
}

#endif // ATTRIBUTE_H
