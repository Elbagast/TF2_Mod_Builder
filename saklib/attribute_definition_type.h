#ifndef ATTRIBUTE_DEFINITION_TYPE_H
#define ATTRIBUTE_DEFINITION_TYPE_H

#include "types.h"
#include "all_type_traits.h"
#include "attribute_definition.h"
#include "all_constraints.h"

namespace Saklib
{
    /*
    Attribute_Definition_Type<T>
    ====================================================================================================
    Class that contains flyweight information to create a given Attribute based on it.

    Without any specific type data this is a useless class - so it makes no sense if it contains no
    constraint info.
    */
    template <typename T>
    class Attribute_Definition_Type:
        public Attribute_Definition
    {
    public:
        using stored_type = T;
        using stored_type_traits = Type_Traits<stored_type>;

        using constraint_type = Constraint < stored_type >;

        // Special 6
        //============================================================
        explicit Attribute_Definition_Type(String const& name);

        template <typename... Args>
        Attribute_Definition_Type(String const& name, Args&&... args);

        ~Attribute_Definition_Type() = default;

        Attribute_Definition_Type(Attribute_Definition_Type const& other) = delete;
        Attribute_Definition_Type& operator=(Attribute_Definition_Type const& other) = delete;

        //Attribute_Definition_Type(Attribute_Definition_Type && other) = default;
        //Attribute_Definition_Type& operator=(Attribute_Definition_Type && other) = default;

        // Interface
        //============================================================
        String const& name() const;
        void set_name(String const& value);

        constraint_type const* constraint() const;
        void set_constraint(Uptr < constraint_type >&& new_constraint);

        template <typename... Args>
        void emplace_constraint(Args&&... args)
        {
            m_constraint = std::move(std::make_unique<constraint_type>(std::forward<Args>(args)...));
        }

    protected:
        // Virtuals
        //============================================================
        String const& v_name() const override;
        Type_Enum v_type_enum() const override;
        String v_type_string() const override;
        bool v_is_constrained() const override;

    private:
        // Data Members
        //============================================================
        String m_name;
        Uptr < constraint_type > m_constraint;
    };
    
    // Related Non-Member Functions
    //============================================================

    template <typename T>
    Uptr<Attribute_Definition_Type<T>> make_Attribute_Definition_Type(String const& name)
    {
        return std::make_unique<Attribute_Definition_Type<T>>(name);
    }

    template <typename T, typename... Args>
    Uptr<Attribute_Definition_Type<T>> make_Attribute_Definition_Type(String const& name, Args&&... args)
    {
        return std::make_unique<Attribute_Definition_Type<T>>(name, std::forward<Args>(args)...);
    }


} // namespace Saklib

// Implementation
//----------------------------------------------------------------------------------------------------

// Special 6
//============================================================
template <typename T>
Saklib::Attribute_Definition_Type<T>::Attribute_Definition_Type(String const& name) :
    Attribute_Definition(),
    m_name(name),
    m_constraint(nullptr)
{}

template <typename T>
template <typename... Args>
Saklib::Attribute_Definition_Type<T>::Attribute_Definition_Type(String const& name, Args&&... args) :
    Attribute_Definition(),
    m_name(name),
    m_constraint(std::make_unique<constraint_type>(std::forward<Args>(args)...))
{}

// Interface
//============================================================
template <typename T>
Saklib::String const& Saklib::Attribute_Definition_Type<T>::name() const
{
    return m_name;
}

template <typename T>
void Saklib::Attribute_Definition_Type<T>::set_name(String const& value)
{
    m_name = value;
}

template <typename T>
typename Saklib::Attribute_Definition_Type<T>::constraint_type const* Saklib::Attribute_Definition_Type<T>::constraint() const
{
    return m_constraint.get();
}

template <typename T>
void Saklib::Attribute_Definition_Type<T>::set_constraint(Uptr < constraint_type >&& new_constraint)
{
    m_constraint = std::move(new_constraint);
}

// Virtuals
//============================================================
template <typename T>
Saklib::String const& Saklib::Attribute_Definition_Type<T>::v_name() const
{
    return m_name;
}

template <typename T>
Saklib::Type_Enum Saklib::Attribute_Definition_Type<T>::v_type_enum() const
{
    return stored_type_traits::type_enum();
}

template <typename T>
Saklib::String Saklib::Attribute_Definition_Type<T>::v_type_string() const
{
    return stored_type_traits::type_string();
}

template <typename T>
bool Saklib::Attribute_Definition_Type<T>::v_is_constrained() const
{
    return m_constraint != nullptr;
}

#endif // ATTRIBUTE_DEFINITION_TYPE_H
