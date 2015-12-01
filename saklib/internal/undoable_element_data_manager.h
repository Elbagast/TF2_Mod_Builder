#ifndef SAKLIB_INTERNAL_UNDOABLE_ELEMENT_DATA_MANAGER_H
#define SAKLIB_INTERNAL_UNDOABLE_ELEMENT_DATA_MANAGER_H

#ifndef SAKLIB_INTERNAL_UNDOABLE_ELEMENT_DATA_MANAGER__FWD_H
#include "undoable_element_data_manager__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_MANAGER_H
#include "element_data_manager.h"
#endif

namespace saklib
{
    namespace internal
    {
        class Command_Manager;
        /*
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
            // definition stuff

            // command stuff

            // handle making stuff

            Undoable_Element_Data_Handle make_null_handle() const;
            Undoable_Element_Data_Handle make_element(std::string const& a_type);
            Undoable_Element_Data_Handle make_element_handle(handle_type const& a_handle);

            std::vector<handle_type> cget_all_handles() const;
            std::vector<Undoable_Element_Data_Handle> make_all_element_handles();
        private:
            Element_Data_Manager m_data_manager;
            //Command_Manager m_command_manager;
        };

        class Undoable_Attribute_Data_Handle;

        //---------------------------------------------------------------------------
        // Undoable_Element_Data_Handle
        //---------------------------------------------------------------------------
        // Intercept all calls to the Element and wrap them in Command objects.
        // Instead of access to Attributes, supply access to Attribute_Data_Handles.

        class Undoable_Element_Data_Handle
        {
            friend class Undoable_Element_Data_Manager;
        public:
            // Typedefs
            //============================================================
            using smart_handle_type = Element_Data_Handle::smart_handle_type;
            using handle_type = Element_Data_Handle::handle_type;
            using reference_count_type = Element_Data_Handle::reference_count_type;

            // Special 6
            //============================================================
        private:
            Undoable_Element_Data_Handle(Undoable_Element_Data_Manager& ar_manager, Element_Data_Handle&& a_data_handle);
        public:
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

            handle_type get_handle() const;

            Handle_Value_Type get_handle_value() const;

            reference_count_type get_reference_count() const;

            // Element_Data Wrapper Interface
            //============================================================
            std::string const& cget_type() const;

            std::string const& cget_name() const;
            void set_name(std::string const& a_name);

            std::size_t get_attribute_count() const;

            Undoable_Attribute_Data_Handle get_attribute_at(std::size_t a_index);

            std::vector<Undoable_Attribute_Data_Handle> get_attributes();

        private:
            // Data Members
            //============================================================
            //Command_Manager* mp_command_manager;
            Element_Data_Handle m_data_handle;
        };
        */
    } // namespace internal
} // namespace saklib

#endif // SAKLIB_INTERNAL_UNDOABLE_ELEMENT_DATA_MANAGER_H
