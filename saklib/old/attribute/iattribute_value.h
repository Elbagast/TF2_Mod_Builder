#ifndef SAKLIB_IATTRIBUTE_VALUE_H
#define SAKLIB_IATTRIBUTE_VALUE_H

#include "../types.h"
#include "../common_traits.h"

namespace saklib
{
    using saklib::size_type;
    /*
    IAttribute_Value_R<T>
    ====================================================================================================
    Interface for access to a value of type T.
    */
    template <typename T>
    class IAttribute_Value_R
    {
    public:
        // Typedefs
        //============================================================
        COMMON_TRAITS_TYPEDEFS_T

        // Special 6
        //============================================================
        virtual ~IAttribute_Value_R() = default;

        // General Interface
        //============================================================
        stored_type_const_return value() const          { return v_value(); }

    protected:
        // Virtuals
        //============================================================
        virtual stored_type_const_return v_value() const = 0;
    };

    /*
    IAttribute_Value<T>
    ====================================================================================================
    Interface for access to a value of type T.
    */
    template <typename T>
    class IAttribute_Value_RW :
            public virtual IAttribute_Value_R<T>
    {
    public:
        // Typedefs
        //============================================================
        COMMON_TRAITS_TYPEDEFS_T

        // Special 6
        //============================================================
        ~IAttribute_Value_RW() override = default;

        // General Interface
        //============================================================
        void set_value(stored_type_const_return value)  { v_set_value(value); }

    protected:
        // Virtuals
        //============================================================
        virtual void v_set_value(stored_type_const_return value) = 0;
    };




    /*
    IAttribute_Value<std::vector<T>>
    ====================================================================================================
    Interface for access to a value of type std::vector<T>.
    */
    template <typename T>
    class IAttribute_Value_R<std::vector<T>>
    {
    public:
        // Typedefs
        //============================================================
        COMMON_TRAITS_TYPEDEFS_T

        // Special 6
        //============================================================
        virtual ~IAttribute_Value_R() = default;

        // Vector Interface
        //============================================================
        stored_type_const_return vector() const                     { return v_vector(); }

        bool empty() const                                          { return v_empty(); }
        size_type size() const                                      { return v_size(); }

        value_type_const_return at(size_type index) const           { return v_at(index); }
        //value_type_const_return front() const                       { return v_front(); }
        //value_type_const_return back() const                        { return v_back(); }

    protected:
        // Virtuals
        //============================================================

        virtual stored_type_const_return v_vector() const = 0;

        virtual bool v_empty() const = 0;
        virtual size_type v_size() const = 0;

        virtual value_type_const_return v_at(size_type index) const = 0;
        //virtual value_type_const_return v_front() const = 0;
        //virtual value_type_const_return v_back() const = 0;
    };


    /*
    IAttribute_Value<std::vector<T>>
    ====================================================================================================
    Interface for access to a value of type std::vector<T>.
    */
    template <typename T>
    class IAttribute_Value_RW<std::vector<T>> :
            public IAttribute_Value_R<std::vector<T>>
    {
    public:
        // Typedefs
        //============================================================
        COMMON_TRAITS_TYPEDEFS_T

        // Special 6
        //============================================================
        ~IAttribute_Value_RW() override = default;

        // Vector Interface
        //============================================================
        void set_vector(stored_type_const_arg vector_value)         { v_set_vector(vector_value); }
        void swap_vector(stored_type& vector_value)                 { v_swap_vector(vector_value); }

        void clear()                                                { v_clear(); }

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
        virtual void v_clear() = 0;

        virtual void v_set_at(size_type index, value_type_const_arg value) = 0;
        //virtual void v_set_front(value_type_const_arg value) = 0;
        //virtual void v_set_back(value_type_const_arg value) = 0;

        virtual void v_swap_at(size_type index, size_type other_index) = 0;

        //virtual void v_push_back(value_type_const_arg value) = 0;
        //virtual void v_pop_back() = 0;

        virtual void v_insert_at(size_type index, value_type_const_arg value) = 0;
        virtual void v_remove_at(size_type index) = 0;
    };
} // namespace saklib

#endif // SAKLIB_IATTRIBUTE_VALUE_H

