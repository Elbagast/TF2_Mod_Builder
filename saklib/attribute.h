#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "types.h"

namespace Saklib
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

} // namespace Saklib

// Implementation
//----------------------------------------------------------------------------------------------------
// Special 6
//============================================================
inline
Saklib::Attribute::Attribute() = default;

inline
Saklib::Attribute::~Attribute() = default;

// General Interface
//============================================================
inline
Saklib::String const& Saklib::Attribute::name() const
{
    return v_name();
}

inline
Saklib::Type_Enum Saklib::Attribute::type_enum() const
{
    return v_type_enum();
}

inline
Saklib::String Saklib::Attribute::type_string() const
{
    return v_type_string();
} // could probably make this into a non-virtual call...

inline
bool Saklib::Attribute::is_simple_type() const
{
    return Saklib::is_simple_type(type_enum());
}

inline
bool Saklib::Attribute::is_vector_type() const
{
    return Saklib::is_vector_type(type_enum());
}

inline
bool Saklib::Attribute::is_constrained() const
{
    return v_is_constrained();
}

#endif // ATTRIBUTE_H
