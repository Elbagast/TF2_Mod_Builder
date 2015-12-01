#ifndef IATTRIBUTE_H
#define IATTRIBUTE_H

#include "types.h"
#include "common_traits.h"
#include "ivalue_storage.h"

namespace saklib
{
    template <typename T>
    class IConstraint;

    /*
    IAttribute
    ====================================================================================================
    Interface class for attributes which defines the generic parts of the interface for Attributes.
    */
    class IAttribute
    {
    public:
        // Special 6
        //============================================================
        virtual ~IAttribute() = 0;

        // General Interface
        //============================================================
        String const& name() const                              { return v_name(); }
        Type_Enum type_enum() const                             { return v_type_enum(); }
        String type_string() const                              { return v_type_string(); }

        bool is_simple_type() const                             { return saklib::is_simple_type(type_enum()); }
        bool is_vector_type() const                             { return saklib::is_vector_type(type_enum()); }

        //bool is_constrained() const                             { return v_is_constrained(); }

    protected:
        // Virtuals
        //============================================================
        virtual String const& v_name() const = 0;
        virtual Type_Enum v_type_enum() const = 0;
        virtual String v_type_string() const = 0;

        //virtual bool v_is_constrained() const = 0;
    };


    /*
    IAttribute_Type<T>
    ====================================================================================================
    Templated subclass for storage of simple types
    */
    template <typename T>
    class IAttribute_Type :
            public IAttribute // what if we add the constraining interface here?...
            ,public IValue_Storage<T>
            ,public IConstraint<T> // if this is here then
    {
    public:
        // Special 6
        //============================================================
        ~IAttribute_Type() override = 0;

    protected:
        // Virtuals
        //============================================================
        String const& v_name() const override = 0;
        Type_Enum v_type_enum() const override = 0;
        String v_type_string() const override = 0;

    };




} // namespace saklib

// IAttribute Implementation
//----------------------------------------------------------------------------------------------------
// Special 6
//============================================================
inline
saklib::IAttribute::~IAttribute() = default;


// IAttribute_Type<T> Implementation
//----------------------------------------------------------------------------------------------------
// Special 6
//============================================================
template <typename T>
inline
saklib::IAttribute<T>::~IAttribute() = default;

#endif // IATTRIBUTE_H

