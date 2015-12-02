#ifndef SAKLIB_INTERNAL_UNDOABLE_ELEMENT_DATA_MANAGER_H
#define SAKLIB_INTERNAL_UNDOABLE_ELEMENT_DATA_MANAGER_H

#ifndef SAKLIB_INTERNAL_UNDOABLE_ELEMENT_DATA_MANAGER__FWD_H
#include "undoable_element_data_manager__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_MANAGER_H
#include "element_data_manager.h"
#endif

#ifndef SAKLIB_INTERNAL_COMMAND_HISTORY_H
#include "command_history.h"
#endif

namespace saklib
{
    namespace internal
    {
        //---------------------------------------------------------------------------
        // Undoable_Element_Data_Manager
        //---------------------------------------------------------------------------

        class Undoable_Element_Data_Manager
        {
        public:
            // Typedefs
            //============================================================
            using handle_type = Element_Data_Manager::handle_type;

            // Interface
            //============================================================
            bool has_element(handle_type const& a_handle) const;
            Undoable_Element_Data_Handle make_element_handle(handle_type const& a_handle);
            Undoable_Element_Data_Handle make_element(Element_Data_Definition_Handle&& a_definition_handle);

            std::vector<handle_type> cget_all_handles() const;
            std::vector<Undoable_Element_Data_Handle> make_all_element_handles();

            // We must wrap all calls to Element_Data and Attribute_Data functions that change data so that
            // those changes can be undone. Do we put them ALL in here? Or spread them across the different
            // Undoable_X_Handle types?

        private:
            Element_Data_Manager m_data_manager;
            Command_History m_command_history;
        };

        class Undoable_Attribute_Data_Handle;

        //---------------------------------------------------------------------------
        // Undoable_Element_Data_Handle
        //---------------------------------------------------------------------------
        // Intercept all calls to the Element and wrap them in Command objects.
        // Instead of access to Attributes, supply access to Attribute_Data_Handles.

        class Undoable_Element_Data_Handle
        {
        public:
            // Typedefs
            //============================================================
            using handle_type = Element_Data_Handle::handle_type;

            // Special 6
            //============================================================
        private:
            Undoable_Element_Data_Handle(Undoable_Element_Data_Manager& ar_manager, Element_Data_Handle&& a_data_handle);
            Undoable_Element_Data_Handle();
            ~Undoable_Element_Data_Handle();

            Undoable_Element_Data_Handle(Undoable_Element_Data_Handle const& other);
            Undoable_Element_Data_Handle& operator=(Undoable_Element_Data_Handle const& other);

            Undoable_Element_Data_Handle(Undoable_Element_Data_Handle && other);
            Undoable_Element_Data_Handle& operator=(Undoable_Element_Data_Handle && other);

            // Interface
            //============================================================
            bool is_valid() const;
            bool is_null() const;

            handle_type cget_handle() const;

            std::size_t cget_reference_count() const;

            // Element_Data Wrapper Interface
            //============================================================
            /*
            std::string const& cget_type() const;

            std::string const& cget_name() const;
            void set_name(std::string const& a_name);

            std::size_t get_attribute_count() const;

            Undoable_Attribute_Data_Handle get_attribute_at(std::size_t a_index);

            std::vector<Undoable_Attribute_Data_Handle> get_attributes();
            */

            // Comparison Operators
            //============================================================
            bool operator==(Undoable_Element_Data_Handle const& rhs);
            bool operator!=(Undoable_Element_Data_Handle const& rhs);
            bool operator<(Undoable_Element_Data_Handle const& rhs);
            bool operator>(Undoable_Element_Data_Handle const& rhs);
            bool operator<=(Undoable_Element_Data_Handle const& rhs);
            bool operator>=(Undoable_Element_Data_Handle const& rhs);

            // Comparison Operators for compare to the null handle
            //============================================================
            bool operator==(Null_Handle_Type const& rhs);
            bool operator!=(Null_Handle_Type const& rhs);

        private:
            // Data Members
            //============================================================
            Element_Data_Handle m_data_handle;

            // This or one to the Command_History? Depends where Commands will be issued
            Undoable_Element_Data_Manager* mp_manager;
        };

    } // namespace internal
} // namespace saklib

#endif // SAKLIB_INTERNAL_UNDOABLE_ELEMENT_DATA_MANAGER_H