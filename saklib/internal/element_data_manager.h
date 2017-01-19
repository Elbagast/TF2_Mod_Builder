#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_MANAGER_H
#define SAKLIB_INTERNAL_ELEMENT_DATA_MANAGER_H

#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_MANAGER__FWD_H
#include "element_data_manager__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_DEFINITION_MANAGER_H
#include "element_data_definition_manager.h"
#endif

#ifndef SAKLIB_INTERNAL_ELEMENT_ID_H
#include "element_id.h"
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
            using storage_type = Reference_Counted_Storage<Element_ID, Element_Data, Element_Data_Definition_Handle>;
            using reference_counter_type = storage_type::reference_counter_type;


            // Special 6
            //============================================================
            //Element_Data_Manager();

            // Interface
            //============================================================
            bool has_element(Element_ID a_id) const;
            Element_Data_Handle make_element_handle(Element_ID a_id);
            Attribute_Data_Handle make_attribute_handle(Element_ID a_id, std::size_t a_index);

            Element_Data_Handle make_element(Element_Data_Definition_Handle&& a_definition_handle);

            std::size_t cget_reference_count(Element_ID a_id) const;

            std::vector<Element_ID> cget_all_element_ids() const;
            std::vector<Element_Data_Handle> make_all_element_handles();

        private:
            // Data Members
            //============================================================
            storage_type m_storage;
            Element_ID_Factory m_id_factory; // right now this does not know when a handle is revoked
        };

    } // namespace internal
} // namespace saklib

#endif // ELEMENT_DATA_MANAGER_H
