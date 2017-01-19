#ifndef SAKLIB_INTERNAL_UNDOABLE_ELEMENT_DATA_HANDLE_H
#define SAKLIB_INTERNAL_UNDOABLE_ELEMENT_DATA_HANDLE_H

#ifndef SAKLIB_INTERNAL_UNDOABLE_ELEMENT_DATA_HANDLE__FWD_H
#include "undoable_element_data_handle__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_COMMAND_HISTORY__FWD_H
#include "command_history__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_UNDOABLE_ATTRIBUTE_DATA_HANDLE__FWD_H
#include "undoable_attribute_data_handle__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_HANDLE_H
#include "element_data_handle.h"
#endif

namespace saklib
{
    namespace internal
    {
        //---------------------------------------------------------------------------
        // Undoable_Element_Data_Handle
        //---------------------------------------------------------------------------
        // Intercept all calls to the Element and wrap them in Command objects.
        // Instead of access to Attributes, supply access to Attribute_Data_Handles.

        class Undoable_Element_Data_Handle
        {
            //friend class Undoable_Attribute_Data_Handle;
        public:
            // Typedefs
            //============================================================
            using handle_type = Element_Data_Handle::handle_type;

            // Special 6
            //============================================================
            Undoable_Element_Data_Handle();
            Undoable_Element_Data_Handle(Element_Data_Handle const& a_data_handle, Command_History& ar_command_history);
            Undoable_Element_Data_Handle(Element_Data_Handle && a_data_handle, Command_History& ar_command_history);
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
            std::string const& cget_type() const;

            std::string const& cget_name() const;
            void set_name(std::string const& a_name);

            std::size_t cget_attribute_count() const;

            Undoable_Attribute_Data_Handle cget_attribute_at(std::size_t a_index) const;

            std::vector<Undoable_Attribute_Data_Handle> cget_attributes() const;

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
            bool operator==(Null_Integer_ID_Type const& rhs);
            bool operator!=(Null_Integer_ID_Type const& rhs);

        protected:
            // Protected Helpers
            //============================================================
            Command_History& get_command_history();
            Command_History const& cget_command_history() const;

        private:
            // Data Members
            //============================================================
            Element_Data_Handle m_element_handle;
            Command_History* mp_command_history;
        };
    } // namespace internal
} // namespace saklib

#endif // SAKLIB_INTERNAL_UNDOABLE_ELEMENT_DATA_HANDLE_H
