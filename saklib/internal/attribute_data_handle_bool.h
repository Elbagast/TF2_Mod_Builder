#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE_BOOL_H
#define SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE_BOOL_H

#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE_BOOL__FWD_H
#include "attribute_data_handle_bool__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE_H
#include "attribute_data_handle.h"
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
        // Attribute_Data_Handle_Boolean_Type<bool>
        //---------------------------------------------------------------------------
        template <typename T>
        class Attribute_Data_Handle_Boolean_Type
        {
        public:
            // Typedefs
            //============================================================
            using handle_type = Attribute_Data_Handle::handle_type;

            using bool_type = T;

            // Special 6
            //============================================================
            Attribute_Data_Handle_Boolean_Type();
            explicit Attribute_Data_Handle_Boolean_Type(Attribute_Data_Handle const& a_attribute_handle);
            explicit Attribute_Data_Handle_Boolean_Type(Attribute_Data_Handle&& a_attribute_handle);
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

            Element_Data_Manager& get_manager();
            Element_Data_Manager const& cget_manager() const;

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
            bool operator==(Attribute_Data_Handle const& rhs);
            bool operator!=(Attribute_Data_Handle const& rhs);

            // Comparison Operators for compare to the null handle
            //============================================================
            bool operator==(Null_Handle_Type const& rhs);
            bool operator!=(Null_Handle_Type const& rhs);

        protected:
            // Protected Helpers
            //============================================================
            Attribute_Data_Boolean_Type<T>& get_attribute_bool();
            Attribute_Data_Boolean_Type<T> const& cget_attribute_bool() const;

        private:
            // Data Members
            //============================================================
            Attribute_Data_Handle m_attribute_handle;
        };
    } // namespace internal
} // namespace saklib

#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE_BOOL__INLINE_H
#include "attribute_data_handle_bool__inline.h"
#endif

#endif // SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE_BOOL_H
