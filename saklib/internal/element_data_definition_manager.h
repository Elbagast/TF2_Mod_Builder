#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_DEFINITION_MANAGER_H
#define SAKLIB_INTERNAL_ELEMENT_DATA_DEFINITION_MANAGER_H

#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_DEFINITION_MANAGER__FWD_H
#include "element_data_definition_manager__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_H
#include "element_data.h"
#endif

#ifndef SAKLIB_INTERNAL_REFERENCE_COUNTED_STORAGE_H
#include "reference_counted_storage.h"
#endif

namespace saklib
{
    namespace internal
    {
        //---------------------------------------------------------------------------
        // Element_Definition_Data_Manager
        //---------------------------------------------------------------------------

        class Element_Data_Definition_Manager
        {
        public:
            // Typedefs
            //============================================================
            using storage_type = Reference_Counted_Storage<std::string, Element_Data_Definition>;
            using reference_counter_type = storage_type::reference_counter_type;

            // Interface
            //============================================================
            // Is there a definition with this type?
            bool has_definition(std::string const& a_type) const;

            Element_Data_Definition_Handle add_definition(Element_Data_Definition && a_definition);

            // Get a definition, throw an exception if there isn't one
            Element_Data_Definition const& cget_definition(std::string const& a_type) const;

            // Get reference counted handle to a definition
            Element_Data_Definition_Handle make_definition_handle(std::string const& a_type);

            // The number of Elements that have been made using this definition.
            std::size_t get_definition_usage_count(std::string const& a_type) const;

            // Can this definition corresponding to this type be removed? A definition can
            // only be removed if it exists and it has a usage count of 0. If these are
            // both true then true is returned. If there is no such definition or it has
            // a usage count above 0 then false is returned.
            bool can_remove_definition(std::string const& a_type) const;

            // Try and remove the definition corresponding to this type. This function
            // calls can_remove_definition() and only removes the definition if the result
            // of that is true. If the remove cannot happen or fails then this function
            // return false, otherwise the definition corresponding to this type is
            // removed.
            bool remove_definition(std::string const& a_type);

            std::vector<std::string> cget_definition_types() const;
            std::vector<Element_Data_Definition_Handle> make_definition_handles();

        private:
            storage_type m_storage;
        };

        //---------------------------------------------------------------------------
        // Element_Definition_Data_Handle
        //---------------------------------------------------------------------------

        class Element_Data_Definition_Handle
        {
        public:
            // Typedefs
            //============================================================
            using storage_type = Element_Data_Definition_Manager::storage_type;
            using reference_counter_type = Element_Data_Definition_Manager::reference_counter_type;

            // Special 6
            //============================================================
            Element_Data_Definition_Handle();
            explicit Element_Data_Definition_Handle(reference_counter_type const& a_ref_counter);
            explicit Element_Data_Definition_Handle(reference_counter_type&& a_ref_counter);
            ~Element_Data_Definition_Handle();

            Element_Data_Definition_Handle(Element_Data_Definition_Handle const& other);
            Element_Data_Definition_Handle& operator=(Element_Data_Definition_Handle const& other);

            Element_Data_Definition_Handle(Element_Data_Definition_Handle && other);
            Element_Data_Definition_Handle& operator=(Element_Data_Definition_Handle && other);

            // Interface
            //============================================================
            bool is_valid() const;
            bool is_null() const;

            std::size_t cget_reference_count() const;

            //data interface
            // what should it be?

            Element_Data_Definition const& cget_definition() const;


            // Comparison Operators
            //============================================================
            bool operator==(Element_Data_Definition_Handle const& rhs);
            bool operator!=(Element_Data_Definition_Handle const& rhs);
            bool operator<(Element_Data_Definition_Handle const& rhs);
            bool operator>(Element_Data_Definition_Handle const& rhs);
            bool operator<=(Element_Data_Definition_Handle const& rhs);
            bool operator>=(Element_Data_Definition_Handle const& rhs);


            // Comparison Operators for compare to the null handle
            //============================================================
            bool operator==(Null_Integer_ID_Type const& rhs);
            bool operator!=(Null_Integer_ID_Type const& rhs);

        private:
            reference_counter_type m_reference_counter;
        };

    } // namespace internal
} // namespace saklib

#endif // SAKLIB_INTERNAL_ELEMENT_DATA_DEFINITION_MANAGER_H
