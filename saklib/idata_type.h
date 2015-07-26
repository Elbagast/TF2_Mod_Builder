#ifndef IDATA_TYPE_H
#define IDATA_TYPE_H

#include "types.h"
#include "nodeid.h"
#include "all_type_traits.h"

namespace Saklib
{
    /*
    IData_Type<T>
    ====================================================================================================
    Class which describes the interface for access to a data value independent of where it's stored.
    */
    template <typename T>
    class IData_Type
    {
    public:
        // Typedefs
        //============================================================
        using stored_type = T;
        using stored_type_traits = Type_Traits < stored_type >;

        // Special 6
        //============================================================
        ~IData_Type() override = 0;

        // Virtual Interface
        //============================================================
        virtual stored_type const& data() const = 0;
        virtual void set_data(stored_type const& value) = 0;
        virtual bool user_set_data(stored_type const& value) = 0;
    };

    /*
    IData_Type<Vector<T>>
    ====================================================================================================
    Partial template specialisation for vectors.
    */
    template <typename T>
    class IData_Type<Vector<T> >
    {
    public:
        // Typedefs
        //============================================================
        using stored_type = Vector<T>;
        using stored_type_traits = Type_Traits < stored_type >;

        using value_type = T;
        using value_type_traits = Type_Traits < value_type >;

        // Special 6
        //============================================================
        ~IData_Type() override = 0;

        // Virtual Interface
        //============================================================
        virtual stored_type const& vector() const = 0;
        virtual void set_vector(stored_type const& vector_value) = 0;
        virtual bool user_set_vector(stored_type const& vector_value) = 0;

        virtual void swap_vector(stored_type& vector_value) = 0;
        virtual bool user_swap_vector(stored_type& vector_value) = 0;

        virtual bool empty() const = 0;
        virtual size_type size() const = 0;

        virtual void clear() = 0;
        virtual bool user_clear() = 0;

        virtual value_type const& at(size_type index) const = 0;
        virtual void set_at(size_type index, value_type const& value) = 0;
        virtual bool user_set_at(size_type index, value_type const& value) = 0;

        virtual value_type const& front() const = 0;
        virtual void set_front(value_type const& value) = 0;
        virtual bool user_set_front(value_type const& value) = 0;

        virtual value_type const& back() const = 0;
        virtual void set_back(value_type const& value) = 0;
        virtual bool user_set_back(value_type const& value) = 0;

        virtual void swap_at(size_type index, size_type other_index) = 0;
        virtual bool user_swap_at(size_type index, size_type other_index) = 0;

        virtual void push_back(value_type const& value) = 0;
        virtual bool user_push_back(value_type const& value) = 0;

        virtual void pop_back() = 0;
        virtual bool user_pop_back() = 0;

        virtual void insert_at(size_type index, value_type const& value) = 0;
        virtual bool user_insert_at(size_type index, value_type const& value) = 0;

        virtual void remove_at(size_type index) = 0;
        virtual bool user_remove_at(size_type index) = 0;
    };

} // namespace Saklib

template <typename T>
Saklib::IData_Type::~IData_Type() = default;

#endif // IDATA_TYPE_H

