#ifndef ATTRIBUTE_TYPE_H
#define ATTRIBUTE_TYPE_H

#include "types.h"
#include "all_type_traits.h"
#include "fwd_attribute_type.h"
#include "attribute.h"
#include "attribute_definition_type.h"
#include <cassert>

namespace Saklib
{
    /*
    Attribute_Type<T>
    ====================================================================================================
    Templated subclass for storage of simple types
    */ 
    template <typename T>
    class Attribute_Type :
        public Attribute
    {
    public:
        using stored_type = T;
        using stored_type_traits = Type_Traits < stored_type >;

        using definition_type = Attribute_Definition_Type < stored_type >;

        // Special 6
        //============================================================
        explicit Attribute_Type(Shptr<Attribute_Definition> const& definition) :
            Attribute(),
            m_definition(definition), // if this is nullptr the constructor will fail...
            mp_definition(dynamic_cast<definition_type*>(m_definition.get())),
            mr_name(m_definition->name()),
            m_value()
        {
            assert(definition);                                 // there was actually a definition
            assert(mp_definition);                              // it was the right type
            assert(v_type_enum() != Type_Enum::Undefined);      // this isn't an Undefined Attribute
            stored_type_traits::set_to_default_value(m_value);
        }
        ~Attribute_Type() override = default;

        // NO COPYING
        Attribute_Type(Attribute_Type const& other) = delete;
        Attribute_Type& operator=(Attribute_Type const& other) = delete;

        // Value Interface
        //============================================================
        stored_type& value()
        {
            return m_value;
        }
        stored_type const& value() const
        {
            return m_value;
        }
        void set_value(stored_type const& value)
        {
            m_value = value;
        }

    protected:
        // Virtuals
        //============================================================
        String const& v_name() const override final     { return mr_name; }
        Type_Enum v_type_enum() const override final    { return stored_type_traits::type_enum(); }
        String v_type_string() const override final     { return stored_type_traits::type_string(); }

    private:
        // shared_ptr ensures the definition's lifetime will be at least as long as this
        Shptr<Attribute_Definition> m_definition;

        // locally cached and pre-cast references
        definition_type const*const mp_definition;  // lifetime is that of m_definition
        String const& mr_name;                 // lifetime is that of m_definition
        //constraint_type const*const mp_constraint;  // lifetime is that of m_definition

        // stored data
        stored_type m_value;
    };



    /*
    Attribute_Type<Vector<T>>
    ====================================================================================================
    Specialisation for storage of vectors of simple types
    */
    template <typename T>
    class Attribute_Type<Vector<T>> :
        public Attribute
    {
    public:
        using stored_type = Vector<T>;
        using stored_type_traits = Type_Traits < stored_type >;

        using value_type = T;
        using value_type_traits = Type_Traits<value_type>;
        
        using definition_type = Attribute_Definition_Type < stored_type >;

        // Special 6
        //============================================================
        explicit Attribute_Type(Shptr<Attribute_Definition> const& definition) :
            Attribute(),
            m_definition(definition), // if this is nullptr the constructor will fail...
            mp_definition(dynamic_cast<definition_type*>(m_definition.get())),
            mr_name(m_definition->name()),
            m_vector()
        {
            assert(definition);                                 // there was actually a definition
            assert(mp_definition);                              // it was the right type
            assert(v_type_enum() != Type_Enum::Undefined);      // this isn't an Undefined Attribute
        }
        ~Attribute_Type() override = default;

        // NO COPYING
        Attribute_Type(Attribute_Type const& other) = delete;
        Attribute_Type& operator=(Attribute_Type const& other) = delete;

        // Vector Interface
        //============================================================
        // TESTING TEMP
        //stored_type& vector()                                   { return m_vector; }
        stored_type const& vector() const                       { return m_vector; }
        void set_vector(stored_type const& vector_value)        { m_vector = vector_value; }
        void swap_vector(stored_type& vector_value)             { std::swap(m_vector, vector_value); }

        bool empty() const                                      { return m_vector.empty(); }
        size_type size() const                                  { return m_vector.size(); }
        void clear()                                            { m_vector.clear(); }

        value_type const& at(size_type index) const             { return m_vector.at(index); }
        value_type const& front() const                         { return m_vector.front(); }
        value_type const& back() const                          { return m_vector.back(); }

        void set_at(size_type index, value_type const& value)   { m_vector.at(index) = value; }
        void set_front(value_type const& value)                 { m_vector.front() = value; }
        void set_back(value_type const& value)                  { m_vector.back() = value; }

        void swap_at(size_type index, size_type other_index)    { std::swap(m_vector.at(index), m_vector.at(other_index)); }

        void push_back(value_type const& value)                 { m_vector.push_back(value); }
        void pop_back()                                         { m_vector.pop_back(); }

        // add value before index, such that index will point to the value added afterwards
        void insert_at(size_type index, value_type const& value)
        {
            auto index_iterator = m_vector.begin();
            std::advance(index_iterator, index);
            m_vector.insert(index_iterator, value);
        }
        // remove value at index, such that index will point to where the value was
        void remove_at(size_type index)
        {
            auto index_iterator = m_vector.begin();
            std::advance(index_iterator, index);
            m_vector.erase(index_iterator);
        }

    protected:
        // Virtuals
        //============================================================
        String const& v_name() const override final     { return mr_name; }
        Type_Enum v_type_enum() const override final    { return stored_type_traits::type_enum(); }
        String v_type_string() const override final     { return stored_type_traits::type_string(); }

        //bool v_is_constrained() const override final      { return mp_constraint != nullptr; }

    private:
        // shared_ptr ensures the definition's lifetime will be at least as long as this
        Shptr<Attribute_Definition> m_definition;

        // locally cached and pre-cast references
        definition_type const*const mp_definition;  // lifetime is that of m_definition
        String const& mr_name;                 // lifetime is that of m_definition

        // stored data
        stored_type m_vector;
    };

    /*
    Attribute_Type<Vector<Bool>>
    ====================================================================================================
    This entire specialisation exists because of the std::vector<bool> specialisation. The actual vector
    type is different so that references can be returned from it.
    */
    template <>
    class Attribute_Type<Vector<Bool>> :
        public Attribute
    {
    public:
        using stored_type = Vector<Bool>;
        using stored_type_traits = Type_Traits < stored_type >;

        using value_type = Bool;
        using value_type_traits = Type_Traits<value_type>;

        using definition_type = Attribute_Definition_Type < stored_type >;

        // Special 6
        //============================================================
        explicit Attribute_Type(Shptr<Attribute_Definition> const& definition) :
            Attribute(),
            m_definition(definition), // if this is nullptr the constructor will fail...
            mp_definition(dynamic_cast<definition_type*>(m_definition.get())),
            mr_name(m_definition->name()),
            m_vector()
        {
            assert(definition);                                 // there was actually a definition
            assert(mp_definition);                              // it was the right type
            assert(v_type_enum() != Type_Enum::Undefined);      // this isn't an Undefined Attribute
        }
        ~Attribute_Type() override = default;

        // NO COPYING
        Attribute_Type(Attribute_Type const& other) = delete;
        Attribute_Type& operator=(Attribute_Type const& other) = delete;

        // Vector Interface
        //============================================================
        // TESTING TEMP
        //stored_type& vector()                                   { return m_vector; }
        stored_type const& vector() const
        {
            static stored_type fake_vector;
            fake_vector.clear();
            for (auto value : m_vector)
            {
                fake_vector.push_back(value);
            }
            return fake_vector;
        }
        void set_vector(stored_type const& vector_value)
        {
            m_vector.clear();
            for (auto value : vector_value)
            {
                m_vector.push_back(value);
            }
        }
        void swap_vector(stored_type& vector_value)
        {
            stored_type swap_target{vector()};
            std::swap(vector_value,swap_target);
            set_vector(swap_target);
        }

        bool empty() const                                      { return m_vector.empty(); }
        size_type size() const                                  { return m_vector.size(); }
        void clear()                                            { m_vector.clear(); }

        value_type const& at(size_type index) const             { return m_vector.at(index).ref(); }
        value_type const& front() const                         { return m_vector.front().ref(); }
        value_type const& back() const                          { return m_vector.back().ref(); }

        void set_at(size_type index, value_type const& value)   { m_vector.at(index).set(value); }
        void set_front(value_type const& value)                 { m_vector.front().set(value); }
        void set_back(value_type const& value)                  { m_vector.back().set(value); }

        void swap_at(size_type index, size_type other_index)    { std::swap(m_vector.at(index), m_vector.at(other_index)); }

        void push_back(value_type const& value)                 { m_vector.push_back(value); }
        void pop_back()                                         { m_vector.pop_back(); }

        // add value before index, such that index will point to the value added afterwards
        void insert_at(size_type index, value_type const& value)
        {
            auto index_iterator = m_vector.begin();
            std::advance(index_iterator, index);
            m_vector.insert(index_iterator, value);
        }
        // remove value at index, such that index will point to where the value was
        void remove_at(size_type index)
        {
            auto index_iterator = m_vector.begin();
            std::advance(index_iterator, index);
            m_vector.erase(index_iterator);
        }

    protected:
        // Virtuals
        //============================================================
        String const& v_name() const override final     { return mr_name; }
        Type_Enum v_type_enum() const override final    { return stored_type_traits::type_enum(); }
        String v_type_string() const override final     { return stored_type_traits::type_string(); }

        //bool v_is_constrained() const override final      { return mp_constraint != nullptr; }

    private:
        class Bool_Holder
        {
        public:
            Bool_Holder(bool input = false): m_value(input) {}

            bool& ref()             { return m_value; }
            bool const& ref() const { return m_value; }
            bool value() const      { return m_value; }

            operator bool()         { return m_value; }

            void set(bool value)    { m_value = value; }
        private:
            bool m_value;
        };

        // shared_ptr ensures the definition's lifetime will be at least as long as this
        Shptr<Attribute_Definition> m_definition;

        // locally cached and pre-cast references
        definition_type const*const mp_definition;  // lifetime is that of m_definition
        String const& mr_name;                 // lifetime is that of m_definition

        // stored data
        Vector<Bool_Holder> m_vector;
    };


    /*
    Casting Functions
    ====================================================================================================
    If you want to use the enum instead, do it here
    */
    template <typename T>
    Attribute_Type<T>* attribute_type_cast(Attribute* attribute)
    {
        return dynamic_cast<Attribute_Type<T>*>(attribute);
    }
    template <typename T>
    Attribute_Type<T>const* attribute_type_cast(Attribute const* attribute)
    {
        return dynamic_cast<Attribute_Type<T>const*>(attribute);
    }

    template <Type_Enum TE>
    Attribute_Type<TypeHolder_st<TE> >* attribute_enum_cast(Attribute* attribute)
    {
        return dynamic_cast<Attribute_Type<TypeHolder_st<TE> >*>(attribute);
    }
    template <Type_Enum TE>
    Attribute_Type<TypeHolder_st<TE> > const* attribute_enum_cast(Attribute const* attribute)
    {
        return dynamic_cast<Attribute_Type<TypeHolder_st<TE> > const*>(attribute);
    }

} // namespace Saklib

#endif // ATTRIBUTE_TYPE_H
