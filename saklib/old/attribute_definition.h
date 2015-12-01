#ifndef ATTRIBUTE_DEFINITION_H
#define ATTRIBUTE_DEFINITION_H

#include "types.h"

namespace saklib
{
    /*
    Attribute_Definition
    ====================================================================================================
    Abstract class the contains flyweight information to create a given Attribute based on it.

    */
    class Attribute_Definition
    {
    public:
        // Special 6
        //============================================================
        Attribute_Definition();
        virtual ~Attribute_Definition();

        Attribute_Definition(Attribute_Definition const& other) = delete;
        Attribute_Definition& operator=(Attribute_Definition const& other) = delete;

        //Attribute_Definition(Attribute_Definition && other) = default;
        //Attribute_Definition& operator=(Attribute_Definition && other) = default;
        
        // Interface
        //============================================================

        String const& name() const;
        Type_Enum type_enum() const;
        String type_string() const;
        
        bool is_simple_type() const;
        bool is_vector_type() const;
        bool is_constrained() const;

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
saklib::Attribute_Definition::Attribute_Definition() = default;

inline
saklib::Attribute_Definition::~Attribute_Definition() = default;


// Interface
//============================================================
inline
saklib::String const& saklib::Attribute_Definition::name() const
{
    return v_name();
}

inline
saklib::Type_Enum saklib::Attribute_Definition::type_enum() const
{
    return v_type_enum();
}

inline
saklib::String saklib::Attribute_Definition::type_string() const
{
    return v_type_string();
}

inline
bool saklib::Attribute_Definition::is_simple_type() const
{
    return saklib::is_simple_type(type_enum());
}

inline
bool saklib::Attribute_Definition::is_vector_type() const
{
    return saklib::is_vector_type(type_enum());
}

inline
bool saklib::Attribute_Definition::is_constrained() const
{
    return v_is_constrained();
}



#endif // ATTRIBUTE_DEFINITION_H
