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
        private:
            using this_type = Element_Data_Manager;

            friend class Element_Data_Handle<this_type>;
            friend class Attribute_Data_Handle<this_type>;

            friend class Attribute_Data_Handle_Boolean_Type<bool, this_type>;

            friend class Attribute_Data_Handle_Integral_Type<int, this_type>;

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
            Element_Data_Handle<this_type> make_element_handle(handle_type const& a_handle);

            Element_Data_Handle<this_type> make_element(Element_Data_Definition_Handle&& a_definition_handle);

            std::size_t cget_reference_count(handle_type const& a_handle) const;

            std::vector<handle_type> cget_all_handles() const;
            std::vector<Element_Data_Handle<this_type>> make_all_element_handles();

        protected:
            // Element_Data Wrapper Interface
            //============================================================
            std::string const& element_cget_type(handle_type const& a_handle) const;

            std::string const& element_cget_name(handle_type const& a_handle) const;
            void element_set_name(handle_type const& a_handle, std::string const& a_name);

            std::size_t element_cget_attribute_count(handle_type const& a_handle) const;

            bool element_has_attribute(handle_type const& a_handle, std::size_t a_index) const;

            Attribute_Data_Handle<this_type> element_cget_attribute_at(handle_type const& a_handle, std::size_t a_index) const;

            std::vector<Attribute_Data_Handle<this_type>> element_cget_attributes(handle_type const& a_handle) const;

            // Attribute_Data Wrapper Interface
            //============================================================
            std::string const& attribute_cget_name(handle_type const& a_handle, std::size_t a_index) const;

            std::string const& attribute_cget_type(handle_type const& a_handle, std::size_t a_index) const;

            std::string attribute_cget_value_string(handle_type const& a_handle, std::size_t a_index) const;

            bool attribute_is_bool(handle_type const& a_handle, std::size_t a_index) const;
            bool attribute_is_int(handle_type const& a_handle, std::size_t a_index) const;

            Attribute_Data_Handle_Boolean_Type<bool, this_type> attribute_cget_bool(handle_type const& a_handle, std::size_t a_index) const;
            Attribute_Data_Handle_Integral_Type<int, this_type> attribute_cget_int(handle_type const& a_handle, std::size_t a_index) const;

            template <typename T>
            bool attribute_is_bool_type(handle_type const& a_handle, std::size_t a_index) const;
            template <typename T>
            bool attribute_is_int_type(handle_type const& a_handle, std::size_t a_index) const;

            template <typename T>
            Attribute_Data_Handle_Boolean_Type<T, this_type> attribute_cget_bool_type(handle_type const& a_handle, std::size_t a_index) const;
            template <typename T>
            Attribute_Data_Handle_Integral_Type<T, this_type> attribute_cget_int_type(handle_type const& a_handle, std::size_t a_index) const;

            // Attribute_Data_Boolean_Type<T> Wrapper Interface
            //============================================================
            template <typename T>
            T attribute_bool_type_cget_value(handle_type const& a_handle, std::size_t a_index) const;

            template <typename T>
            bool attribute_bool_type_can_set_value_to(handle_type const& a_handle, std::size_t a_index, T a_value) const;

            template <typename T>
            bool attribute_bool_type_try_set_value(handle_type const& a_handle, std::size_t a_index, T a_value);

            template <typename T>
            void attribute_bool_type_set_value(handle_type const& a_handle, std::size_t a_index, T a_value);

            // Attribute_Data_Integral_Type<T> Wrapper Interface
            //============================================================
            template <typename T>
            T attribute_int_type_cget_value(handle_type const& a_handle, std::size_t a_index) const;

            template <typename T>
            bool attribute_int_type_can_set_value_to(handle_type const& a_handle, std::size_t a_index, T a_value) const;

            template <typename T>
            bool attribute_int_type_try_set_value(handle_type const& a_handle, std::size_t a_index, T a_value);

            template <typename T>
            void attribute_int_type_set_value(handle_type const& a_handle, std::size_t a_index, T a_value);

            template <typename T>
            T attribute_int_type_cget_lowest_value(handle_type const& a_handle, std::size_t a_index) const;

            template <typename T>
            T attribute_int_type_cget_highest_value(handle_type const& a_handle, std::size_t a_index) const;


        private:
            // Private Helpers
            //============================================================
            reference_counter_type make_reference_counter(handle_type const& a_handle) const;

            Element_Data& get_element(handle_type const& a_handle);
            Element_Data const& cget_element(handle_type const& a_handle) const;

            Attribute_Data& get_attribute(handle_type const& a_handle, std::size_t a_index);
            Attribute_Data const& cget_attribute(handle_type const& a_handle, std::size_t a_index) const;

            template <typename T>
            Attribute_Data_Boolean_Type<T>& get_attribute_bool_type(handle_type const& a_handle, std::size_t a_index);
            template <typename T>
            Attribute_Data_Boolean_Type<T> const& cget_attribute_bool_type(handle_type const& a_handle, std::size_t a_index) const;

            template <typename T>
            Attribute_Data_Integral_Type<T>& get_attribute_int_type(handle_type const& a_handle, std::size_t a_index);
            template <typename T>
            Attribute_Data_Integral_Type<T> const& cget_attribute_int_type(handle_type const& a_handle, std::size_t a_index) const;

            // Data Members
            //============================================================
            mutable storage_type m_storage;
            handle_factory_type m_handle_factory; // right now this does not know when a handle is revoked
        };

    } // namespace internal
} // namespace saklib

#endif // ELEMENT_DATA_MANAGER_H
