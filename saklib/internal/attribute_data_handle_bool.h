#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE_BOOL_H
#define SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE_BOOL_H

#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE_BOOL__FWD_H
#include "attribute_data_handle_bool__fwd.h"
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
        // Attribute_Data_Handle_Boolean_Type<bool, Manager>
        //---------------------------------------------------------------------------
        template <typename T, typename M>
        class Attribute_Data_Handle_Boolean_Type
        {
        public:
            // Typedefs
            //============================================================
            using manager_type = M;
            using reference_counter_type = typename manager_type::reference_counter_type;
            using handle_type = typename reference_counter_type::handle_type;
            using storage_type = typename reference_counter_type::storage_type;

            using bool_type = T;

            // Special 6
            //============================================================
            Attribute_Data_Handle_Boolean_Type();
            Attribute_Data_Handle_Boolean_Type(manager_type* ap_manager, reference_counter_type const& a_reference_counter, std::size_t a_index);
            Attribute_Data_Handle_Boolean_Type(manager_type* ap_manager, reference_counter_type&& a_reference_counter, std::size_t a_index);
            ~Attribute_Data_Handle_Boolean_Type();

            Attribute_Data_Handle_Boolean_Type(Attribute_Data_Handle_Boolean_Type const& other);
            Attribute_Data_Handle_Boolean_Type& operator=(Attribute_Data_Handle_Boolean_Type const& other);

            Attribute_Data_Handle_Boolean_Type(Attribute_Data_Handle_Boolean_Type && other);
            Attribute_Data_Handle_Boolean_Type& operator=(Attribute_Data_Handle_Boolean_Type && other);

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

            bool_type cget_value() const;

            bool can_set_value_to(bool_type a_value) const;

            bool try_set_value(bool_type a_value);

            void set_value(bool_type a_value);

            // Comparison Operators
            //============================================================
            bool operator==(Attribute_Data_Handle_Boolean_Type const& rhs);
            bool operator!=(Attribute_Data_Handle_Boolean_Type const& rhs);
            bool operator<(Attribute_Data_Handle_Boolean_Type const& rhs);
            bool operator>(Attribute_Data_Handle_Boolean_Type const& rhs);
            bool operator<=(Attribute_Data_Handle_Boolean_Type const& rhs);
            bool operator>=(Attribute_Data_Handle_Boolean_Type const& rhs);

            // Comparison Operators to Untyped Handle
            //============================================================
            //bool operator==(Attribute_Data_Handle const& rhs);
            //bool operator!=(Attribute_Data_Handle const& rhs);

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

#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE_BOOL__INLINE_H
#include "attribute_data_handle_bool__inline.h"
#endif

#endif // SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE_BOOL_H
