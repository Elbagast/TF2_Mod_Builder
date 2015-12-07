#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_HANDLE_H
#define SAKLIB_INTERNAL_ELEMENT_DATA_HANDLE_H

#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_HANDLE__FWD_H
#include "element_data_handle__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_MANAGER_H
#include "element_data_manager.h"
#endif

/*
#ifndef SAKLIB_INTERNAL_ELEMENT_DATA__FWD_H
#include "element_data__fwd.h"
#endif
*/

#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE__FWD_H
#include "attribute_data_handle__fwd.h"
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

#ifndef INCLUDE_STD_VECTOR
#define INCLUDE_STD_VECTOR
#include <vector>
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
            friend class Attribute_Data_Handle;
        public:
            // Typedefs
            //============================================================
            using reference_counter_type = Element_Data_Manager::reference_counter_type;
            using handle_type = reference_counter_type::handle_type;
            using storage_type = reference_counter_type::storage_type;

            // Special 6
            //============================================================
            Element_Data_Handle();
            Element_Data_Handle(Element_Data_Manager* ap_manager, reference_counter_type const& a_reference_counter);
            Element_Data_Handle(Element_Data_Manager* ap_manager, reference_counter_type&& a_reference_counter);
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
            bool has_attribute(std::size_t a_index) const;

            Element_Data_Manager& get_manager();
            Element_Data_Manager const& cget_manager() const;

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
            Element_Data& get_element();
            Element_Data const& cget_element() const;

        private:
            // Data Members
            //============================================================
            Element_Data_Manager* mp_manager;
            reference_counter_type m_reference_counter;
        };

    } // namespace internal
} // namespace saklib

#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_HANDLE__INLINE_H
#include "element_data_handle__inline.h"
#endif

#endif // SAKLIB_INTERNAL_ELEMENT_DATA_HANDLE_H
