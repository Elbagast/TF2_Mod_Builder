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
            handle_factory_type m_handle_factory; // right now this does not know when a handle is revoked
        };

    } // namespace internal
} // namespace saklib

#endif // ELEMENT_DATA_MANAGER_H
