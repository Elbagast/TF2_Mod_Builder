#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_HANDLE_H
#define SAKLIB_INTERNAL_ELEMENT_DATA_HANDLE_H

#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_HANDLE__FWD_H
#include "element_data_handle__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_MANAGER__FWD_H
#include "element_data_manager.h"
#endif

#ifndef SAKLIB_INTERNAL_ELEMENT_DATA__FWD_H
#include "element_data__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE__FWD_H
#include "attribute_data_handle__fwd.h"
#endif

namespace saklib
{
    namespace internal
    {
        //---------------------------------------------------------------------------
        // Element_Data_Handle
        //---------------------------------------------------------------------------
        class Element_Data_Handle
        {
            //friend class Attribute_Data_Handle;
        public:
            // Typedefs
            //============================================================
            using reference_counter_type = Element_Data_Manager::reference_counter_type;
            using handle_type = reference_counter_type::handle_type;
            using storage_type = reference_counter_type::storage_type;

            // Special 6
            //============================================================
            Element_Data_Handle();
            explicit Element_Data_Handle(reference_counter_type const& a_reference_counter);
            explicit Element_Data_Handle(reference_counter_type&& a_reference_counter);
            ~Element_Data_Handle();

            Element_Data_Handle(Element_Data_Handle const& other);
            Element_Data_Handle& operator=(Element_Data_Handle const& other);

            Element_Data_Handle(Element_Data_Handle && other);
            Element_Data_Handle& operator=(Element_Data_Handle && other);

            // Interface
            //============================================================
            bool is_valid() const;
            bool is_null() const;

            handle_type cget_handle() const;

            std::size_t cget_reference_count() const;

            // Element_Data Wrapper Interface
            //============================================================
            std::string const& cget_type() const;

            std::string const& cget_name() const;
            void set_name(std::string const& a_name);

            std::size_t cget_attribute_count() const;

            Attribute_Data_Handle cget_attribute_at(std::size_t a_index) const;

            std::vector<Attribute_Data_Handle> cget_attributes() const;

            // Comparison Operators
            //============================================================
            bool operator==(Element_Data_Handle const& rhs);
            bool operator!=(Element_Data_Handle const& rhs);
            bool operator<(Element_Data_Handle const& rhs);
            bool operator>(Element_Data_Handle const& rhs);
            bool operator<=(Element_Data_Handle const& rhs);
            bool operator>=(Element_Data_Handle const& rhs);

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
        private:
            // Data Members
            //============================================================
            reference_counter_type m_reference_counter;
        };

    } // namespace internal
} // namespace saklib


#endif // SAKLIB_INTERNAL_ELEMENT_DATA_HANDLE_H
