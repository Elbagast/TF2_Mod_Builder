#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE_INT_H
#define SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE_INT_H

#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE_INT__FWD_H
#include "attribute_data_handle_int__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE_H
#include "attribute_data_handle.h"
#endif

namespace saklib
{
    namespace internal
    {
        //---------------------------------------------------------------------------
        // Attribute_Data_Handle_Int
        //---------------------------------------------------------------------------
        class Attribute_Data_Handle_Int
        {
        public:
            // Typedefs
            //============================================================
            using reference_counter_type = Element_Data_Handle::reference_counter_type;
            using handle_type = reference_counter_type::handle_type;
            using storage_type = reference_counter_type::storage_type;

            // Special 6
            //============================================================
            Attribute_Data_Handle_Int();
            Attribute_Data_Handle_Int(reference_counter_type const& a_reference_counter, std::size_t a_index);
            Attribute_Data_Handle_Int(reference_counter_type&& a_reference_counter, std::size_t a_index);
            ~Attribute_Data_Handle_Int();

            Attribute_Data_Handle_Int(Attribute_Data_Handle_Int const& other);
            Attribute_Data_Handle_Int& operator=(Attribute_Data_Handle_Int const& other);

            Attribute_Data_Handle_Int(Attribute_Data_Handle_Int && other);
            Attribute_Data_Handle_Int& operator=(Attribute_Data_Handle_Int && other);

            // Interface
            //============================================================
            bool is_valid() const;
            bool is_null() const;

            handle_type cget_element_handle() const;
            std::size_t cget_element_reference_count() const;

            std::size_t cget_attribute_index() const;

            // Attribute_Data Wrapper Interface
            //============================================================
            std::string const& cget_name() const;

            std::string const& cget_type() const;

            std::string cget_value_string() const;

            int cget_value() const;

            bool can_set_value_to(int a_value) const;

            bool try_set_value(int a_value);

            void set_value(int a_value);

            int cget_lowest_value() const;

            int cget_highest_value() const;

            // Comparison Operators
            //============================================================
            bool operator==(Attribute_Data_Handle_Int const& rhs);
            bool operator!=(Attribute_Data_Handle_Int const& rhs);
            bool operator<(Attribute_Data_Handle_Int const& rhs);
            bool operator>(Attribute_Data_Handle_Int const& rhs);
            bool operator<=(Attribute_Data_Handle_Int const& rhs);
            bool operator>=(Attribute_Data_Handle_Int const& rhs);

            // Comparison Operators to Untyped Handle
            //============================================================
            //bool operator==(Attribute_Data_Handle const& rhs);
            //bool operator!=(Attribute_Data_Handle const& rhs);

            // Comparison Operators for compare to the null handle
            //============================================================
            bool operator==(Null_Handle_Type const& rhs);
            bool operator!=(Null_Handle_Type const& rhs);

        protected:
            // Protected Helpers
            //============================================================
            storage_type& get_storage();
            storage_type const& cget_storage() const;

            Element_Data& get_element();
            Element_Data const& cget_element() const;

            Attribute_Data_Int& get_attribute();
            Attribute_Data_Int const& cget_attribute() const;

        private:
            // Data Members
            //============================================================
            reference_counter_type m_reference_counter;
            std::size_t m_attribute_index;
        };
    } // namespace internal
} // namespace saklib


#endif // SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE_INT_H
