#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_MANAGER_H
#define SAKLIB_INTERNAL_ELEMENT_DATA_MANAGER_H

#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_MANAGER__FWD_H
#include "element_data_manager__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_DEFINITION_MANAGER_H
#include "element_data_definition_manager.h"
#endif

#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_H
#include "element_data.h"
#endif

#ifndef SAKLIB_INTERNAL_HANDLE_FACTORY_H
#include "handle_factory.h"
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

        private:
            // Data Members
            //============================================================
            storage_type m_storage;
            handle_factory_type m_handle_factory;
        };


        //---------------------------------------------------------------------------
        // Element_Data_Handle
        //---------------------------------------------------------------------------


        // undo support has to go in here or in an object that holds this...
        class Element_Data_Handle
        {
        public:
            // Typedefs
            //============================================================
            using handle_type = Element_Data_Manager::handle_type;
            using storage_type = Element_Data_Manager::storage_type;
            using reference_counter_type = Element_Data_Manager::reference_counter_type;

            // Special 6
            //============================================================
            Element_Data_Handle();
            Element_Data_Handle(reference_counter_type&& a_reference_counter);
            ~Element_Data_Handle();

            Element_Data_Handle(Element_Data_Handle const& other);
            Element_Data_Handle& operator=(Element_Data_Handle const& other);

            Element_Data_Handle(Element_Data_Handle && other);
            Element_Data_Handle& operator=(Element_Data_Handle && other);

            // Interface
            //============================================================
            bool is_valid() const;
            bool is_null() const;

            std::size_t cget_reference_count() const;

            // probably don't want to expose the Element here...
            // need to supply wrapper handles for Attributes....
            Element_Data& get_element();
            Element_Data const& cget_element() const;

            /*
            // probably don't want to expose this either?..
            Element_Data_Manager* get_manager();
            Element_Data_Manager const* cget_manager() const;


            // Element_Data Wrapper Interface
            //============================================================
            std::string const& cget_type() const;

            std::string const& cget_name() const;
            void set_name(std::string const& a_name);

            std::size_t get_attribute_count() const;

            Attribute_Data_Handle get_attribute_at(std::size_t a_index);

            std::vector<Attribute_Data_Handle> get_attributes();

            */

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
            reference_counter_type m_reference_counter;
        };

    } // namespace internal
} // namespace saklib


#endif // ELEMENT_DATA_MANAGER_H
