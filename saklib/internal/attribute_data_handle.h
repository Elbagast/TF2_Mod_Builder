#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE_H
#define SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE_H

#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE__FWD_H
#include "attribute_data_handle__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_ALL_ATTRIBUTE_DATA_HANDLE__FWD_H
#include "all_attribute_data_handle__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_HANDLE_H
#include "element_data_handle.h"
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
            //friend class Attribute_Data_Handle_Bool;
            //friend class Attribute_Data_Handle_Int;
            // etc.
        public:
            // Typedefs
            //============================================================
            using reference_counter_type = Element_Data_Handle::reference_counter_type;
            using handle_type = reference_counter_type::handle_type;
            using storage_type = reference_counter_type::storage_type;

            // Special 6
            //============================================================
            Attribute_Data_Handle();
            Attribute_Data_Handle(reference_counter_type const& a_reference_counter, std::size_t a_index);
            Attribute_Data_Handle(reference_counter_type&& a_reference_counter, std::size_t a_index);
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

            // Attribute_Data Wrapper Interface
            //============================================================
            std::string const& cget_name() const;

            std::string const& cget_type() const;

            std::string cget_value_string() const;

            bool is_bool() const;
            bool is_int() const;

            Attribute_Data_Handle_Bool cget_bool() const;
            Attribute_Data_Handle_Int cget_int() const;

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

        //protected:
            // Protected Helpers
            //============================================================
            storage_type& get_storage();
            storage_type const& cget_storage() const;

            Element_Data& get_element();
            Element_Data const& cget_element() const;

            Attribute_Data& get_attribute();
            Attribute_Data const& cget_attribute() const;
        private:
            // Data Members
            //============================================================
            reference_counter_type m_reference_counter;
            std::size_t m_attribute_index;
        };
    } // namespace internal
} // namespace saklib

#endif // SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE_H
