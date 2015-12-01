#ifndef ATTRIBUTE_DEFINITION_TYPE_H
#define ATTRIBUTE_DEFINITION_TYPE_H

#include "types.h"
#include "common_traits.h"
#include "attribute_definition.h"
#include "all_constraints.h"

namespace saklib
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
        using stored_type_traits = Common_Traits<stored_type>;

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
        void set_constraint(std::unique_ptr < constraint_type >&& new_constraint);

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
        std::unique_ptr < constraint_type > m_constraint;
    };
    
    // Related Non-Member Functions
    //============================================================

    template <typename T>
    std::unique_ptr<Attribute_Definition_Type<T>> make_Attribute_Definition_Type(String const& name)
    {
        return std::make_unique<Attribute_Definition_Type<T>>(name);
    }

    template <typename T, typename... Args>
    std::unique_ptr<Attribute_Definition_Type<T>> make_Attribute_Definition_Type(String const& name, Args&&... args)
    {
        return std::make_unique<Attribute_Definition_Type<T>>(name, std::forward<Args>(args)...);
    }


} // namespace saklib

// Implementation
//----------------------------------------------------------------------------------------------------

// Special 6
//============================================================
template <typename T>
saklib::Attribute_Definition_Type<T>::Attribute_Definition_Type(String const& name) :
    Attribute_Definition(),
    m_name(name),
    m_constraint(nullptr)
{}

template <typename T>
template <typename... Args>
saklib::Attribute_Definition_Type<T>::Attribute_Definition_Type(String const& name, Args&&... args) :
    Attribute_Definition(),
    m_name(name),
    m_constraint(std::make_unique<constraint_type>(std::forward<Args>(args)...))
{}

// Interface
//============================================================
template <typename T>
saklib::String const& saklib::Attribute_Definition_Type<T>::name() const
{
    return m_name;
}

template <typename T>
void saklib::Attribute_Definition_Type<T>::set_name(String const& value)
{
    m_name = value;
}

template <typename T>
typename saklib::Attribute_Definition_Type<T>::constraint_type const* saklib::Attribute_Definition_Type<T>::constraint() const
{
    return m_constraint.get();
}

template <typename T>
void saklib::Attribute_Definition_Type<T>::set_constraint(std::unique_ptr < constraint_type >&& new_constraint)
{
    m_constraint = std::move(new_constraint);
}

// Virtuals
//============================================================
template <typename T>
saklib::String const& saklib::Attribute_Definition_Type<T>::v_name() const
{
    return m_name;
}

template <typename T>
saklib::Type_Enum saklib::Attribute_Definition_Type<T>::v_type_enum() const
{
    return stored_type_traits::type_enum();
}

template <typename T>
saklib::String saklib::Attribute_Definition_Type<T>::v_type_string() const
{
    return stored_type_traits::type_string();
}

template <typename T>
bool saklib::Attribute_Definition_Type<T>::v_is_constrained() const
{
    return m_constraint != nullptr;
}

#endif // ATTRIBUTE_DEFINITION_TYPE_H
