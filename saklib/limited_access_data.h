#ifndef LIMITED_ACCESS_DATA_H
#define LIMITED_ACCESS_DATA_H

#include "types.h"

namespace Saklib
{
    /*
    Limited_Access_Data<T>
    ====================================================================================================
    Simple pairing of a value with a bool that marks whether or not that value should be editable by the
    end user. Use forwarding functions to this class to limit access to the different levels as
    appropriate.
    */

    template <typename T>
    class Limited_Access_Data
    {
    public:
        using stored_type = T;

        // Special 6
        //============================================================
        explicit Limited_Access_Data(bool user_accessible = true):
            m_value(),
            m_user_can_edit(user_accessible)
        {}
        explicit Limited_Access_Data(stored_type const& value, bool user_accessible = true):
            m_value(value),
            m_user_can_edit(user_accessible)
        {}

        // Implicit default destructor, move, copy

        // Public Interface
        //============================================================

        // The current data value
        stored_type const& value() const
        {
            return m_value;
        }

        // Ask if user_set_value will succeed
        bool user_can_edit() const
        {
            return m_user_can_edit;
        }

        // if the value can be set by the user, set it, returning true if succeeding
        bool user_set_value(stored_type const& new_value)
        {
            if (m_user_can_edit)
            {
                set_value(new_value);
                return true;
            }
            else
            {
                return false;
            }
        }

        // Set the value without checking against the access flag
        void set_value(stored_type const& new_value)
        {
            m_value = new_value;
        }

        // Set the state of user access
        void set_user_can_edit(bool state)
        {
            m_user_can_edit = state;
        }

    private:
        // Member Variables
        //============================================================
        stored_type m_value;
        bool m_user_can_edit;
    };

    /*
    Limited_Access_Data<Vector<T>>
    ====================================================================================================
    Partial specialisation for vectors.
    */

    template <typename T>
    class Limited_Access_Data<Vector<T>>
    {
    public:
        using stored_type = Vector<T>;
        using value_type = T;

        // Special 6
        //============================================================
        explicit Limited_Access_Data(bool user_accessible = true):
            m_vector(),
            m_user_can_edit(user_accessible)
        {}
        explicit Limited_Access_Data(stored_type const& value, bool user_accessible = true):
            m_vector(value),
            m_user_can_edit(user_accessible)
        {}

        // Implicit default destructor, move, copy

        // Vector Interface
        //============================================================
        stored_type const& vector() const                               { return m_vector; }
        void set_vector(stored_type const& vector_value)                { m_vector = vector_value; }
        bool user_set_vector(stored_type const& vector_value)           { return user_conditional_function(&Limited_Access_Data::set_vector, vector_value); }
        void swap_vector(stored_type& vector_value)                     { std::swap(m_vector, vector_value); }
        bool user_swap_vector(stored_type& vector_value)                { return user_conditional_function(&Limited_Access_Data::user_swap_vector, vector_value); }

        bool empty() const                                              { return m_vector.empty(); }
        size_type size() const                                          { return m_vector.size(); }
        void clear()                                                    { m_vector.clear(); }
        bool user_clear()                                               { return user_conditional_function(&Limited_Access_Data::clear); }

        value_type const& at(size_type index) const                     { return m_vector.at(index); }
        value_type const& front() const                                 { return m_vector.front(); }
        value_type const& back() const                                  { return m_vector.back(); }

        void set_at(size_type index, value_type const& value)           { m_vector.at(index) = value; }
        bool user_set_at(size_type index, value_type const& value)      { return user_conditional_function(&Limited_Access_Data::set_at, index, value); }
        void set_front(value_type const& value)                         { m_vector.front() = value; }
        bool user_set_front(value_type const& value)                    { return user_conditional_function(&Limited_Access_Data::set_front, value); }
        void set_back(value_type const& value)                          { m_vector.back() = value; }
        bool user_set_back(value_type const& value)                     { return user_conditional_function(&Limited_Access_Data::user_set_back, value); }

        void swap_at(size_type index, size_type other_index)            { std::swap(m_vector.at(index), m_vector.at(other_index)); }
        bool user_swap_at(size_type index, size_type other_index)       { return user_conditional_function(&Limited_Access_Data::swap_at, index, other_index); }

        void push_back(value_type const& value)                         { m_vector.push_back(value); }
        bool user_push_back(value_type const& value)                    { return user_conditional_function(&Limited_Access_Data::push_back, value); }
        void pop_back()                                                 { m_vector.pop_back(); }
        bool user_pop_back()                                            { return user_conditional_function(&Limited_Access_Data::pop_back); }

        // add value before index, such that index will point to the value added afterwards
        void insert_at(size_type index, value_type const& value)
        {
            auto index_iterator = m_vector.begin();
            std::advance(index_iterator, index);
            m_vector.insert(index_iterator, value);
        }
        bool user_insert_at(size_type index, value_type const& value)   { return user_conditional_function(&Limited_Access_Data::insert_at, index, value); }

        // remove value at index, such that index will point to where the value was
        void remove_at(size_type index)
        {
            auto index_iterator = m_vector.begin();
            std::advance(index_iterator, index);
            m_vector.erase(index_iterator);
        }
        bool user_remove_at(size_type index)                            { return user_conditional_function(&Limited_Access_Data::remove_at, index); }

        // Ask if user_set_value will succeed
        bool user_can_edit() const
        {
            return m_user_can_edit;
        }

        // Set the state of user access
        void set_user_can_edit(bool state)
        {
            m_user_can_edit = state;
        }

    private:
        // Helpers
        //============================================================
        template <typename MemFunc>
        bool user_conditional_function(MemFunc func)
        {
            if (m_user_can_edit)
            {
                (this->*func)();
                return true;
            }
            else
            {
                return false;
            }
        }

        template <typename MemFunc, typename... Args>
        bool user_conditional_function(MemFunc func, Args&&... args)
        {
            if (m_user_can_edit)
            {
                (this->*func)(std::forward<Args>(args)...);
                return true;
            }
            else
            {
                return false;
            }
        }

        // Member Variables
        //============================================================
        stored_type m_vector;
        bool m_user_can_edit;
    };





    /*
    Limited_Access_Data<Vector<Bool>>
    ====================================================================================================
    This entire specialisation exists because of the std::vector<bool> specialisation. The actual vector
    type is different so that references can be returned from it.
    */

    template <>
    class Limited_Access_Data<Vector<Bool>>
    {
    public:
        using stored_type = Vector<Bool>;
        using value_type = Bool;

        // Special 6
        //============================================================
        explicit Limited_Access_Data(bool user_accessible = true):
            m_vector(),
            m_user_can_edit(user_accessible)
        {}
        explicit Limited_Access_Data(stored_type const& value, bool user_accessible = true):
            m_vector(),
            m_user_can_edit(user_accessible)
        {
            set_vector(value);
        }

        // Implicit default destructor, move, copy

        // Vector Interface
        //============================================================
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
        bool user_set_vector(stored_type const& vector_value)           { return user_conditional_function(&Limited_Access_Data::set_vector, vector_value); }
        void swap_vector(stored_type& vector_value)
        {
            stored_type swap_target{vector()};
            std::swap(vector_value,swap_target);
            set_vector(swap_target);
        }
        bool user_swap_vector(stored_type& vector_value)                { return user_conditional_function(&Limited_Access_Data::user_swap_vector, vector_value); }

        bool empty() const                                              { return m_vector.empty(); }
        size_type size() const                                          { return m_vector.size(); }
        void clear()                                                    { m_vector.clear(); }
        bool user_clear()                                               { return user_conditional_function(&Limited_Access_Data::clear); }

        value_type const& at(size_type index) const                     { return m_vector.at(index).ref(); }
        value_type const& front() const                                 { return m_vector.front().ref(); }
        value_type const& back() const                                  { return m_vector.back().ref(); }

        void set_at(size_type index, value_type const& value)           { m_vector.at(index).set(value); }
        bool user_set_at(size_type index, value_type const& value)      { return user_conditional_function(&Limited_Access_Data::set_at, index, value); }
        void set_front(value_type const& value)                         { m_vector.front().set(value); }
        bool user_set_front(value_type const& value)                    { return user_conditional_function(&Limited_Access_Data::set_front, value); }
        void set_back(value_type const& value)                          { m_vector.back().set(value); }
        bool user_set_back(value_type const& value)                     { return user_conditional_function(&Limited_Access_Data::user_set_back, value); }

        void swap_at(size_type index, size_type other_index)            { std::swap(m_vector.at(index), m_vector.at(other_index)); }
        bool user_swap_at(size_type index, size_type other_index)       { return user_conditional_function(&Limited_Access_Data::swap_at, index, other_index); }

        void push_back(value_type const& value)                         { m_vector.push_back(value); }
        bool user_push_back(value_type const& value)                    { return user_conditional_function(&Limited_Access_Data::push_back, value); }
        void pop_back()                                                 { m_vector.pop_back(); }
        bool user_pop_back()                                            { return user_conditional_function(&Limited_Access_Data::pop_back); }

        // add value before index, such that index will point to the value added afterwards
        void insert_at(size_type index, value_type const& value)
        {
            auto index_iterator = m_vector.begin();
            std::advance(index_iterator, index);
            m_vector.insert(index_iterator, value);
        }
        bool user_insert_at(size_type index, value_type const& value)   { return user_conditional_function(&Limited_Access_Data::insert_at, index, value); }

        // remove value at index, such that index will point to where the value was
        void remove_at(size_type index)
        {
            auto index_iterator = m_vector.begin();
            std::advance(index_iterator, index);
            m_vector.erase(index_iterator);
        }
        bool user_remove_at(size_type index)                            { return user_conditional_function(&Limited_Access_Data::remove_at, index); }

        // Set the state of user access
        void set_user_can_edit(bool state)
        {
            m_user_can_edit = state;
        }

    private:
        // Helpers
        //============================================================
        template <typename MemFunc>
        bool user_conditional_function(MemFunc func)
        {
            if (m_user_can_edit)
            {
                (this->*func)();
                return true;
            }
            else
            {
                return false;
            }
        }

        template <typename MemFunc, typename... Args>
        bool user_conditional_function(MemFunc func, Args&&... args)
        {
            if (m_user_can_edit)
            {
                (this->*func)(std::forward<Args>(args)...);
                return true;
            }
            else
            {
                return false;
            }
        }

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

        // Member Variables
        //============================================================
        Vector<Bool_Holder> m_vector;
        bool m_user_can_edit;
    };


} // namespace Saklib


#endif // LIMITED_ACCESS_DATA_H

