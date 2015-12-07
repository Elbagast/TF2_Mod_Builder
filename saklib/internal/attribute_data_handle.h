#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE_H
#define SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE_H

#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE__FWD_H
#include "attribute_data_handle__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_ALL_ATTRIBUTE_DATA_HANDLE__FWD_H
#include "all_attribute_data_handle__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_NULL_HANDLE__FWD_H
#include "null_handle__fwd.h"
#endif

#ifndef INCLUDE_STD_CSTDDEF
#define INCLUDE_STD_CSTDDEF
#include <cstddef>
#endif

#ifndef INCLUDE_STD_STRING
#define INCLUDE_STD_STRING
#include <string>
#endif

namespace saklib
{
    namespace internal
    {
        //---------------------------------------------------------------------------
        // Attribute_Data_Handle<Manager>
        //---------------------------------------------------------------------------

        template <typename M>
        class Attribute_Data_Handle
        {
        public:
            // Typedefs
            //============================================================
            using manager_type = M;
            using reference_counter_type = typename manager_type::reference_counter_type;
            using handle_type = typename reference_counter_type::handle_type;
            using storage_type = typename reference_counter_type::storage_type;

            // Special 6
            //============================================================
            Attribute_Data_Handle();
            Attribute_Data_Handle(manager_type* ap_manager, reference_counter_type const& a_reference_counter, std::size_t a_index);
            Attribute_Data_Handle(manager_type* ap_manager, reference_counter_type&& a_reference_counter, std::size_t a_index);
            ~Attribute_Data_Handle();

            Attribute_Data_Handle(Attribute_Data_Handle const& other);
            Attribute_Data_Handle& operator=(Attribute_Data_Handle const& other);

            Attribute_Data_Handle(Attribute_Data_Handle && other);
            Attribute_Data_Handle& operator=(Attribute_Data_Handle && other);

            // Interface
            //============================================================
            bool is_valid() const;
            bool is_null() const;

            handle_type cget_element_handle() const;
            std::size_t cget_element_reference_count() const;

            std::size_t cget_attribute_index() const;

            manager_type& get_manager();
            manager_type const& cget_manager() const;

            // Attribute_Data Wrapper Interface
            //============================================================
            std::string const& cget_name() const;

            std::string const& cget_type() const;

            std::string cget_value_string() const;

            bool is_bool() const;
            bool is_int() const;

            Attribute_Data_Handle_Boolean_Type<bool, M> cget_bool() const;
            Attribute_Data_Handle_Integral_Type<int, M> cget_int() const;

            template <typename T>
            bool is_bool_type() const;
            template <typename T>
            bool is_int_type() const;

            template <typename T>
            Attribute_Data_Handle_Boolean_Type<T, M> const& cget_bool_type() const;
            template <typename T>
            Attribute_Data_Handle_Integral_Type<T, M> const& cget_int_type() const;

            // Comparison Operators
            //============================================================
            bool operator==(Attribute_Data_Handle const& rhs);
            bool operator!=(Attribute_Data_Handle const& rhs);
            bool operator<(Attribute_Data_Handle const& rhs);
            bool operator>(Attribute_Data_Handle const& rhs);
            bool operator<=(Attribute_Data_Handle const& rhs);
            bool operator>=(Attribute_Data_Handle const& rhs);

            // Comparison Operators for compare to the null handle
            //============================================================
            bool operator==(Null_Handle_Type const& rhs);
            bool operator!=(Null_Handle_Type const& rhs);

        private:
            // Data Members
            //============================================================
            manager_type* mp_manager;
            reference_counter_type m_reference_counter;
            std::size_t m_attribute_index;
        };
    } // namespace internal
} // namespace saklib


#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE__INLINE_H
#include "attribute_data_handle__inline.h"
#endif

#endif // SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE_H
