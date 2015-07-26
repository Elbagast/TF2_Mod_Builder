#ifndef DATA_H
#define DATA_H

#include "idata.h"
#include "idata_type.h"
#include "limited_access_data.h"
//#include "all_type_traits.h"

namespace Saklib
{
    /*
    Data<T>
    ====================================================================================================
    Implemented local holder of a data value
    */
    template <typename T>
    class Data :
            public IData,
            public IData_Type<T>
    {
        static_assert(stored_type_traits::type_enum_value != Type_Enum::Undefined, "Cannot instantiate with an undefined type");

    public:
        // Special 6
        //============================================================
        explicit Data(stored_type const& value, bool value_is_editable = true):
            IData_Type<T>(),
            m_value(value, value_is_editable)
        {}
        ~Data() override = default;

        // No copy
        Data(Data const& other) = delete;
        Data& operator=(Data const& other) = delete;

        // Implicit default move
        //Data(Data && other) = default;
        //Data& operator=(Data && other) = default;

        // IData Virtual Interface
        //============================================================
        Type_Enum type_enum() const override            { return stored_type_traits::type_enum(); }
        String type_string() const override             { return stored_type_traits::type_string(); }

        bool user_can_set_data() const override         { return m_value.user_can_edit(); }
        void set_user_can_set_data(bool state) override { m_value.set_user_can_edit(state); }

        // IData_Type<T> Virtual Interface
        //============================================================
        stored_type const& data() const override        { return m_value.value(); }
        void set_data(stored_type const& value)         { m_value.set_value(value); }

        bool user_set_data(stored_type const& value)    { return m_value.user_set_value(value); }

    private:
        Limited_Access_Data<stored_type> m_value;
    };

    /*
    Data_Node<Vector<T>>
    ====================================================================================================
    Intermediate class to implement data-type specific operations.
    */
    template <typename T>
    class Data<Vector<T> > :
            public IData,
            public IData_Type<Vector<T> >
    {
        static_assert(stored_type_traits::type_enum_value != Type_Enum::Undefined, "Cannot instantiate with an undefined type");

    public:
        // Special 6
        //============================================================
        explicit Data(stored_type const& value, bool value_is_editable = true):
            IData_Type<T>(),
            m_vector(value, value_is_editable)
        {}
        ~Data() override = default;

        // No copy
        Data(Data const& other) = delete;
        Data& operator=(Data const& other) = delete;

        // Implicit default move
        //Data(Data && other) = default;
        //Data& operator=(Data && other) = default;

        // IData Virtual Interface
        //============================================================
        Type_Enum type_enum() const override                                    { return stored_type_traits::type_enum(); }
        String type_string() const override                                     { return stored_type_traits::type_string(); }

        bool user_can_set_data() const override                                 { return m_vector.user_can_edit(); }
        void set_user_can_set_data(bool state) override                         { m_vector.set_user_can_edit(state); }

        // IData_Type<Vector<T>> Virtual Interface
        //============================================================
        stored_type const& vector() const override                              { m_vector.vector(); }
        void set_vector(stored_type const& vector_value) override               { m_vector.set_vector(vector_value); }
        bool user_set_vector(stored_type const& vector_value) override          { return m_vector.user_set_vector(vector_value); }

        void swap_vector(stored_type& vector_value) override                    { m_vector.swap_vector(vector_value); }
        bool user_swap_vector(stored_type& vector_value) override               { return m_vector.user_swap_vector(vector_value); }

        bool empty() const override                                             { return m_vector.empty(); }
        size_type size() const override                                         { return m_vector.size(); }

        void clear() override                                                   { m_vector.clear(); }
        bool user_clear() override                                              { return m_vector.user_clear(); }

        value_type const& at(size_type index) const override                    { return m_vector.at(index); }
        void set_at(size_type index, value_type const& value) override          { m_vector.set_at(index, value); }
        bool user_set_at(size_type index, value_type const& value) override     { return m_vector.user_set_at(index, value); }

        value_type const& front() const override                                { return m_vector.front(); }
        void set_front(value_type const& value) override                        { m_vector.set_front(value); }
        bool user_set_front(value_type const& value) override                   { return m_vector.user_set_front(value); }

        value_type const& back() const override                                 { return m_vector.back(); }
        void set_back(value_type const& value) override                         { m_vector.set_back(value); }
        bool user_set_back(value_type const& value) override                    { return m_vector.user_set_back(value); }

        void swap_at(size_type index, size_type other_index) override           { m_vector.swap_at(index, other_index); }
        bool user_swap_at(size_type index, size_type other_index) override      { return m_vector.user_swap_at(index, other_index); }

        void push_back(value_type const& value) override                        { m_vector.push_back(value); }
        bool user_push_back(value_type const& value) override                   { return m_vector.user_push_back(value); }

        void pop_back() override                                                { m_vector.pop_back(); }
        bool user_pop_back() override                                           { return m_vector.user_pop_back(); }

        bool user_insert_at(size_type index, value_type const& value) override  { return m_vector.user_insert_at(index, value); }
        void insert_at(size_type index, value_type const& value) override       { m_vector.insert_at(index, value); }

        bool user_remove_at(size_type index) override                           { return m_vector.user_remove_at(index); }
        void remove_at(size_type index) override                                { m_vector.remove_at(index); }

    private:
        Limited_Access_Data<stored_type> m_vector;
    };

} // namespace Saklib

#endif // DATA_H

