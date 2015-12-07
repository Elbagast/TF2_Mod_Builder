#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_HANDLE_H
#define SAKLIB_INTERNAL_ELEMENT_DATA_HANDLE_H

#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_HANDLE__FWD_H
#include "element_data_handle__fwd.h"
#endif

/*
#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_MANAGER__FWD_H
#include "element_data_manager.h"
#endif

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
        template <typename M>
        class Element_Data_Handle
        {
        public:
            // Typedefs
            //============================================================
            using manager_type = M;
            using reference_counter_type = typename manager_type::reference_counter_type;
            using handle_type = typename reference_counter_type::handle_type;
            using storage_type = typename reference_counter_type::storage_type;

            using attribute_handle_type = Attribute_Data_Handle<M>;

            // Special 6
            //============================================================
            Element_Data_Handle();
            Element_Data_Handle(manager_type* ap_manager, reference_counter_type const& a_reference_counter);
            Element_Data_Handle(manager_type* ap_manager, reference_counter_type&& a_reference_counter);
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

            manager_type& get_manager();
            manager_type const& cget_manager() const;

            // Element_Data Wrapper Interface
            //============================================================
            std::string const& cget_type() const;

            std::string const& cget_name() const;
            void set_name(std::string const& a_name);

            std::size_t cget_attribute_count() const;

            attribute_handle_type cget_attribute_at(std::size_t a_index) const;

            std::vector<attribute_handle_type> cget_attributes() const;

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

        private:
            // Data Members
            //============================================================
            manager_type* mp_manager;
            reference_counter_type m_reference_counter;
        };

    } // namespace internal
} // namespace saklib

#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_HANDLE__INLINE_H
#include "element_data_handle__inline.h"
#endif

#endif // SAKLIB_INTERNAL_ELEMENT_DATA_HANDLE_H
