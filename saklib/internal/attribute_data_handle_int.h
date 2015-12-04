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
        template <typename T = int>
        class Attribute_Data_Handle_Integral_Type
        {
        public:
            // Typedefs
            //============================================================
            using reference_counter_type = Element_Data_Handle::reference_counter_type;
            using handle_type = reference_counter_type::handle_type;
            using storage_type = reference_counter_type::storage_type;

            using int_type = T;
            using attribute_data_type = Attribute_Data_Integral_Type<int_type>;

            // Special 6
            //============================================================
            Attribute_Data_Handle_Integral_Type();
            Attribute_Data_Handle_Integral_Type(reference_counter_type const& a_reference_counter, std::size_t a_index);
            Attribute_Data_Handle_Integral_Type(reference_counter_type&& a_reference_counter, std::size_t a_index);
            ~Attribute_Data_Handle_Integral_Type();

            Attribute_Data_Handle_Integral_Type(Attribute_Data_Handle_Integral_Type const& other);
            Attribute_Data_Handle_Integral_Type& operator=(Attribute_Data_Handle_Integral_Type const& other);

            Attribute_Data_Handle_Integral_Type(Attribute_Data_Handle_Integral_Type && other);
            Attribute_Data_Handle_Integral_Type& operator=(Attribute_Data_Handle_Integral_Type && other);

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

            int_type cget_value() const;

            bool can_set_value_to(int_type a_value) const;

            bool try_set_value(int_type a_value);

            void set_value(int_type a_value);

            int_type cget_lowest_value() const;

            int_type cget_highest_value() const;

            // Comparison Operators
            //============================================================
            bool operator==(Attribute_Data_Handle_Integral_Type const& rhs);
            bool operator!=(Attribute_Data_Handle_Integral_Type const& rhs);
            bool operator<(Attribute_Data_Handle_Integral_Type const& rhs);
            bool operator>(Attribute_Data_Handle_Integral_Type const& rhs);
            bool operator<=(Attribute_Data_Handle_Integral_Type const& rhs);
            bool operator>=(Attribute_Data_Handle_Integral_Type const& rhs);

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

            attribute_data_type& get_attribute();
            attribute_data_type const& cget_attribute() const;

        private:
            // Data Members
            //============================================================
            reference_counter_type m_reference_counter;
            std::size_t m_attribute_index;
        };
    } // namespace internal
} // namespace saklib


#endif // SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE_INT_H
