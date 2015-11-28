#ifndef IVALUE_STORAGE_H
#define IVALUE_STORAGE_H

/*
Defining the interface for stored values / vectors
 */
#include <vector>
#include "common_traits.h"

namespace saklib
{
    /*
    IValue_Storage<T>
    ====================================================================================================
    Templated subclass for storage of simple types
    */
    template <typename T>
    class IValue_Storage
    {
    public:
        using stored_type = typename Common_Traits<T>::stored_type;
        using value_type = typename Common_Traits<T>::value_type;

        using stored_type_const_arg = typename Common_Traits<T>::stored_type_const_arg;
        using stored_type_const_return = typename Common_Traits<T>::stored_type_const_return;

        using value_type_const_arg = typename Common_Traits<T>::value_type_const_arg;
        using value_type_const_return = typename Common_Traits<T>::value_type_const_return;

        // Special 6
        //============================================================
        ~IValue_Storage() override = default;

        // General Interface
        //============================================================
        stored_type_const_return value() const      { return v_value(); }
        void set_value(stored_type_const_arg value) { v_set_value(value); }

    protected:
        // Virtuals
        //============================================================
        virtual stored_type_const_return v_value() const = 0;
        virtual void v_set_value(stored_type_const_arg value) = 0;
    };

    /*
    IValue_Storage<T>
    ====================================================================================================
    Templated subclass for storage of simple types
    */
    template <typename T>
    class IValue_Storage<std::vector<T>>
    {
    public:
        using stored_type = typename Common_Traits<std::vector<T>>::stored_type;
        using value_type = typename Common_Traits<std::vector<T>>::value_type;

        using stored_type_const_arg = typename Common_Traits<std::vector<T>>::stored_type_const_arg;
        using stored_type_const_return = typename Common_Traits<std::vector<T>>::stored_type_const_return;

        using value_type_const_arg = typename Common_Traits<std::vector<T>>::value_type_const_arg;
        using value_type_const_return = typename Common_Traits<std::vector<T>>::value_type_const_return;

        // Special 6
        //============================================================
        ~IValue_Storage() override = 0;

        // Vector Interface
        //============================================================
        stored_type_const_return vector() const                     { return v_vector(); }
        void set_vector(stored_type_const_arg vector_value)         { v_set_vector(vector_value); }
        void swap_vector(stored_type& vector_value)                 { v_swap_vector(vector_value); }

        bool empty() const                                          { return v_empty(); }
        size_type size() const                                      { return v_size(); }
        void clear()                                                { v_clear(); }

        value_type_const_return at(size_type index) const           { return v_at(index); }
        //value_type_const_return front() const                       { return v_front(); }
        //value_type_const_return back() const                        { return v_back(); }

        void set_at(size_type index, value_type_const_arg value)    { v_set_at(index, value); }
        //void set_front(value_type_const_arg value)                     { v_set_front(value); }
        //void set_back(value_type_const_arg value)                      { v_set_back(value); }

        void swap_at(size_type index, size_type other_index)        { v_swap_at(index, other_index); }

        //void push_back(value_type_const_arg value)                     { v_push_back(value); }
        //void pop_back()                                             { v_pop_back(); }

        // add value before index, such that index will point to the value added afterwards
        void insert_at(size_type index, value_type_const_arg value) { v_insert_at(index, value); }
        // remove value at index, such that index will point to where the value was
        void remove_at(size_type index)                             { v_remove_at(index); }

    protected:
        // Virtuals
        //============================================================

        virtual stored_type_const_return v_vector() const = 0;
        virtual void v_set_vector(stored_type_const_arg vector_value) = 0;
        virtual void v_swap_vector(stored_type& vector_value) = 0;

        virtual bool v_empty() const = 0;
        virtual size_type v_size() const = 0;
        virtual void v_clear() = 0;

        virtual value_type_const_return v_at(size_type index) const = 0;
        //virtual value_type_const_return v_front() const = 0;
        //virtual value_type_const_return v_back() const = 0;

        virtual void v_set_at(size_type index, value_type_const_arg value) = 0;
        //virtual void v_set_front(value_type_const_arg value) = 0;
        //virtual void v_set_back(value_type_const_arg value) = 0;

        virtual void v_swap_at(size_type index, size_type other_index) = 0;

        //virtual void v_push_back(value_type_const_arg value) = 0;
        //virtual void v_pop_back() = 0;

        virtual void v_insert_at(size_type index, value_type_const_arg value) = 0;
        virtual void v_remove_at(size_type index) = 0;
    };




    /*
    Local_Value_Storage<T>
    ====================================================================================================
    */
    template <typename T>
    class Local_Value_Storage :
            public IValue_Storage
    {
    public:
        // Special 6
        //============================================================
        Local_Value_Storage() :
            IValue_Storage(),
            m_value(Common_Traits<T>::make_default_value())
        {}
        explicit Local_Value_Storage(stored_type_const_arg value) :
            IValue_Storage(),
            m_value(value)
        {}
        ~Local_Value_Storage() override = default;

    protected:
        // Virtuals
        //============================================================
        stored_type_const_return v_value() const override       { return m_value; }
        void v_set_value(stored_type_const_arg value) override  { m_value = value; }

    private:
        stored_type m_value;
    };


    /*
    Local_Value_Storage<std::vector<T>>
    ====================================================================================================
    */
    template <typename T>
    class Local_Value_Storage<std::vector<T>> :
            public IValue_Storage<std::vector<T>>
    {
    public:
        // Special 6
        //============================================================
        Local_Value_Storage() :
            IValue_Storage(),
            m_vector(Common_Traits<std::vector<T>>::make_default_value())
        {}
        explicit Local_Value_Storage(stored_type_const_arg vector) :
            IValue_Storage(),
            m_vector(vector)
        {}
        ~Local_Value_Storage() override = default;

    protected:
        // Virtuals
        //============================================================

        stored_type_const_return v_vector() const override              { return m_vector; }
        void v_set_vector(stored_type_const_arg vector_value) override  { m_vector = vector_value; }
        void v_swap_vector(stored_type& vector_value) override          { std::swap(m_vector, vector_value); }

        bool v_empty() const override                                   { return m_vector.empty(); }
        size_type v_size() const override                               { return m_vector.size(); }
        void v_clear() override                                         { return m_vector.clear(); }

        value_type_const_return v_at(size_type index) const override    { return m_vector.at(index); }
        //value_type_const_return v_front() const override                { return m_vector.front(); }
        //value_type_const_return v_back() const override                 { return m_vector.back(); }

        void v_set_at(size_type index, value_type_const_arg value) override { m_vector.at(index) = value;}
        //void v_set_front(value_type_const_arg value) override               { m_vector.front() = value; }
        //void v_set_back(value_type_const_arg value) override                { m_vector.back() = value; }

        void v_swap_at(size_type index, size_type other_index) override     { std::swap(m_vector.at(index), m_vector.at(other_index)); }

        //void v_push_back(value_type_const_arg value) override               { m_vector.push_back(value); }
        //void v_pop_back() override                                          { m_vector.pop_back(); }

        void v_insert_at(size_type index, value_type_const_arg value) override
        {
            auto index_iterator = m_vector.begin();
            std::advance(index_iterator, index);
            m_vector.insert(index_iterator, value);
        }
        void v_remove_at(size_type index) override
        {
            auto index_iterator = m_vector.begin();
            std::advance(index_iterator, index);
            m_vector.erase(index_iterator);
        }

    private:
        stored_type m_vector;
    };


} // namespace saklib

#endif // IVALUE_STORAGE_H

