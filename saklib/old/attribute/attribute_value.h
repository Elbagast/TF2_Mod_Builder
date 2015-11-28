#ifndef SAKLIB_ATTRIBUTE_VALUE_H
#define SAKLIB_ATTRIBUTE_VALUE_H

#include "iattribute_value.h"

namespace saklib
{
    namespace local
    {
        /*
        Attribute_Value<T>
        ====================================================================================================
        Interface for access to a value of type T.
        */
        template <typename T>
        class Attribute_Value :
                public virtual IAttribute_Value_RW<T>
        {
        public:
            // Typedefs
            //============================================================
            COMMON_TRAITS_TYPEDEFS_T

            // Special 6
            //============================================================
            Attribute_Value():
                IAttribute_Value_RW<T>(),
                m_value(Common_Traits<stored_type>::make_default_value())
            {}
            explicit Attribute_Value(stored_type_const_arg value) :
                IAttribute_Value_RW<T>(),
                m_value(value)
            {}
            ~Attribute_Value() override = default;

        protected:
            // Virtuals
            //============================================================
            stored_type_const_return v_value() const override       { return m_value; }
            void v_set_value(stored_type_const_arg value) override  { m_value = value; }
        private:
            stored_type m_value;
        };

        /*
        Attribute_Value<std::vector<T>>
        ====================================================================================================
        Interface for access to a value of type std::vector<T>.
        */
        template <typename T>
        class Attribute_Value<std::vector<T>> :
                public virtual IAttribute_Value_RW<std::vector<T>>
        {
        public:
            // Typedefs
            //============================================================
            COMMON_TRAITS_TYPEDEFS_T

            // Special 6
            //============================================================
            Attribute_Value() :
                IAttribute_Value_RW<std::vector<T>>(),
                m_vector(Common_Traits<std::vector<T>>::make_default_value())
            {}
            explicit Attribute_Value(stored_type_const_arg vector) :
                IAttribute_Value_RW<std::vector<T>>(),
                m_vector(vector)
            {}
            ~Attribute_Value() override = default;

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

    } // namespace local

} // namespace saklib

#endif // SAKLIB_ATTRIBUTE_VALUE_H

