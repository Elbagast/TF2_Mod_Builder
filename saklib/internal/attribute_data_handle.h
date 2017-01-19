#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE_H
#define SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE_H

#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE__FWD_H
#include "attribute_data_handle__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_ALL_ATTRIBUTE_DATA_HANDLE__FWD_H
#include "all_attribute_data_handle__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_MANAGER__FWD_H
#include "element_data_manager__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_HANDLE_H
#include "element_data_handle.h"
#endif

#ifndef SAKLIB_INTERNAL_NULL_INTEGER_ID__FWD_H
#include "null_integer_id__fwd.h"
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
        // Attribute_Data_Handle
        //---------------------------------------------------------------------------

        class Attribute_Data_Handle
        {
            template <typename T>
            friend class Attribute_Data_Handle_Boolean_Type;
            template <typename T>
            friend class Attribute_Data_Handle_Integral_Type;
        public:
            // Typedefs
            //============================================================
            using reference_counter_type = Element_Data_Handle::reference_counter_type;
            using handle_type = Element_Data_Handle::handle_type;
            using storage_type = Element_Data_Handle::storage_type;

            // Special 6
            //============================================================
            Attribute_Data_Handle();
            Attribute_Data_Handle(Element_Data_Handle const& a_element_handle, std::size_t a_index);
            Attribute_Data_Handle(Element_Data_Handle&& a_element_handle, std::size_t a_index);
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

            Element_Data_Manager& get_manager();
            Element_Data_Manager const& cget_manager() const;

            // Attribute_Data Wrapper Interface
            //============================================================
            std::string const& cget_name() const;

            std::string const& cget_type() const;

            std::string cget_value_string() const;

            bool is_bool() const;

            Attribute_Data_Handle_Boolean_Type<bool> cget_bool() const;

            template <typename T>
            bool is_bool_type() const;

            template <typename T>
            Attribute_Data_Handle_Boolean_Type<T> cget_bool_type() const;

            bool is_int() const;
            Attribute_Data_Handle_Integral_Type<int> cget_int() const;

            template <typename T>
            bool is_int_type() const;

            template <typename T>
            Attribute_Data_Handle_Integral_Type<T> cget_int_type() const;

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
            bool operator==(Null_Integer_ID_Type const& rhs);
            bool operator!=(Null_Integer_ID_Type const& rhs);

        protected:
            // Protected Helpers
            //============================================================
            Attribute_Data& get_attribute();
            Attribute_Data const& cget_attribute() const;

        private:
            // Data Members
            //============================================================
            Element_Data_Handle m_element_handle;
            std::size_t m_attribute_index;
        };
    } // namespace internal
} // namespace saklib


#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE__INLINE_H
#include "attribute_data_handle__inline.h"
#endif

#endif // SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE_H
