#ifndef ATTRIBUTE_DEFINITION_H
#define ATTRIBUTE_DEFINITION_H

#include "types.h"

namespace Saklib
{
    class Constraint;

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
        Attribute_Definition() = default;
        virtual ~Attribute_Definition() = default;

        Attribute_Definition(Attribute_Definition const& other) = delete;
        Attribute_Definition& operator=(Attribute_Definition const& other) = delete;
        
        String const& name() const  { return v_name(); }
        Type_Enum type_enum() const { return v_type_enum(); }
        String type_string() const  { return v_type_string(); }
        
        bool is_simple_type() const     { return Saklib::is_simple_type(type_enum()); }
        bool is_vector_type() const     { return Saklib::is_vector_type(type_enum()); }
        bool is_constrained() const     { return v_is_constrained(); }

    protected:
        // Virtuals
        //============================================================
        virtual String const& v_name() const = 0;
        virtual Type_Enum v_type_enum() const = 0;
        virtual String v_type_string() const = 0;
        virtual bool v_is_constrained() const = 0;
    };

    Shptr<Attribute_Definition> make_shared_Attribute_Definition(String const& name, Type_Enum type);

    template <typename T>
    Shptr<Attribute_Definition> make_shared_Attribute_Definition_by_type(String const& name);

    template <typename T, typename... Args>
    Shptr<Attribute_Definition> make_shared_Attribute_Definition_by_type(String const& name, Args&&... args);
    //This function has to know about all of the constraint types so that it can forward the args...
    //which means it can't be implemented here

} // namespace Saklib

#endif // ATTRIBUTE_DEFINITION_H
