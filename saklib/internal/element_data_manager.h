#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_MANAGER_H
#define SAKLIB_INTERNAL_ELEMENT_DATA_MANAGER_H

#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_MANAGER__FWD_H
#include "element_data_manager__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_DEFINITION_MANAGER_H
#include "element_data_definition_manager.h"
#endif

#ifndef SAKLIB_INTERNAL_HANDLE_FACTORY_H
#include "handle_factory.h"
#endif

#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_HANDLE__FWD_H
#include "element_data_handle__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_ALL_ATTRIBUTE_DATA_HANDLE__FWD_H
#include "all_attribute_data_handle__fwd.h"
#endif


namespace saklib
{
    namespace internal
    {
        //---------------------------------------------------------------------------
        // Element_Data_Manager
        //---------------------------------------------------------------------------
        class Element_Data_Manager
        {
        public:
            // Typedefs
            //============================================================
            using handle_type = Handle<Element_Data>;
            using handle_factory_type = Handle_Factory<Element_Data>;

            using storage_type = Reference_Counted_Storage<handle_type, Element_Data, Element_Data_Definition_Handle>;
            using reference_counter_type = storage_type::reference_counter_type;

            // Special 6
            //============================================================
            //Element_Data_Manager();

            // Interface
            //============================================================
            bool has_element(handle_type const& a_handle) const;
            Element_Data_Handle make_element_handle(handle_type const& a_handle);

            Element_Data_Handle make_element(Element_Data_Definition_Handle&& a_definition_handle);

            std::vector<handle_type> cget_all_handles() const;
            std::vector<Element_Data_Handle> make_all_element_handles();

            // Element_Data Wrapper Interface
            //============================================================
            std::string const& cget_type(handle_type const& a_handle) const;

            std::string const& cget_name(handle_type const& a_handle) const;
            void set_name(handle_type const& a_handle, std::string const& a_name);

            std::size_t cget_attribute_count(handle_type const& a_handle) const;

            Attribute_Data_Handle cget_attribute_at(handle_type const& a_handle, std::size_t a_index) const;

            std::vector<Attribute_Data_Handle> cget_attributes(handle_type const& a_handle) const;

            // Attribute_Data Wrapper Interface
            //============================================================
            std::string const& cget_name(handle_type const& a_handle, std::size_t a_index) const;

            std::string const& cget_type(handle_type const& a_handle, std::size_t a_index) const;

            std::string cget_value_string(handle_type const& a_handle, std::size_t a_index) const;

            bool is_bool(handle_type const& a_handle, std::size_t a_index) const;
            bool is_int(handle_type const& a_handle, std::size_t a_index) const;

            Attribute_Data_Handle_Bool& get_bool(handle_type const& a_handle, std::size_t a_index);
            Attribute_Data_Handle_Int& get_int(handle_type const& a_handle, std::size_t a_index);

            Attribute_Data_Handle_Bool const& cget_bool(handle_type const& a_handle, std::size_t a_index) const;
            Attribute_Data_Handle_Int const& cget_int(handle_type const& a_handle, std::size_t a_index) const;
            /*
            template <typename T>
            bool is_bool_type(handle_type const& a_handle, std::size_t a_index) const;
            template <typename T>
            bool is_int_type(handle_type const& a_handle, std::size_t a_index) const;

            template <typename T>
            Attribute_Data_Boolean_Type<T>& get_bool_type(handle_type const& a_handle, std::size_t a_index);
            template <typename T>
            Attribute_Data_Integral_Type<T>& get_int_type(handle_type const& a_handle, std::size_t a_index);

            template <typename T>
            Attribute_Data_Boolean_Type<T> const& cget_bool_type(handle_type const& a_handle, std::size_t a_index) const;
            template <typename T>
            Attribute_Data_Integral_Type<T> const& cget_int_type(handle_type const& a_handle, std::size_t a_index) const;
            */

        private:
            // Data Members
            //============================================================
            storage_type m_storage;
            handle_factory_type m_handle_factory; // right now this does not know when a handle is revoked
        };

    } // namespace internal
} // namespace saklib

#endif // ELEMENT_DATA_MANAGER_H
