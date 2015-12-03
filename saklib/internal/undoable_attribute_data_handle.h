#ifndef SAKLIB_INTERNAL_UNDOABLE_ATTRIBUTE_DATA_HANDLE_H
#define SAKLIB_INTERNAL_UNDOABLE_ATTRIBUTE_DATA_HANDLE_H

#ifndef SAKLIB_INTERNAL_UNDOABLE_ATTRIBUTE_DATA_HANDLE__FWD_H
#include "undoable_attribute_data_handle__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE_H
#include "attribute_data_handle.h"
#endif

#ifndef SAKLIB_INTERNAL_COMMAND_HISTORY__FWD_H
#include "command_history__fwd.h"
#endif

namespace saklib
{
    namespace internal
    {
        class Undoable_Attribute_Data_Handle_Bool;
        class Undoable_Attribute_Data_Handle_Int;

        class Undoable_Attribute_Data_Handle
        {
            friend class Undoable_Attribute_Data_Handle_Bool;
            friend class Undoable_Attribute_Data_Handle_Int;
            //etc.
        public:
            // Typedefs
            //============================================================
            using handle_type = Attribute_Data_Handle::handle_type;

            // Special 6
            //============================================================
            Undoable_Attribute_Data_Handle();
            Undoable_Attribute_Data_Handle(Attribute_Data_Handle const& a_attribute_handle, Command_History* ap_command_history);
            Undoable_Attribute_Data_Handle(Attribute_Data_Handle&& a_attribute_handle, Command_History* ap_command_history);
            ~Undoable_Attribute_Data_Handle();

            Undoable_Attribute_Data_Handle(Undoable_Attribute_Data_Handle const& other);
            Undoable_Attribute_Data_Handle& operator=(Undoable_Attribute_Data_Handle const& other);

            Undoable_Attribute_Data_Handle(Undoable_Attribute_Data_Handle && other);
            Undoable_Attribute_Data_Handle& operator=(Undoable_Attribute_Data_Handle && other);

            // Interface
            //============================================================
            bool is_valid() const;
            bool is_null() const;

            handle_type cget_element_handle() const;
            std::size_t cget_element_reference_count() const;

            std::size_t cget_attribute_index() const;

            // Attribute_Data Wrapper Interface
            //============================================================
            std::string const& cget_name() const;

            std::string const& cget_type() const;

            std::string cget_value_string() const;

            bool is_bool() const;
            bool is_int() const;

            Undoable_Attribute_Data_Handle_Bool cget_bool() const;
            Undoable_Attribute_Data_Handle_Int cget_int() const;

            // Comparison Operators
            //============================================================
            bool operator==(Undoable_Attribute_Data_Handle const& rhs);
            bool operator!=(Undoable_Attribute_Data_Handle const& rhs);
            bool operator<(Undoable_Attribute_Data_Handle const& rhs);
            bool operator>(Undoable_Attribute_Data_Handle const& rhs);
            bool operator<=(Undoable_Attribute_Data_Handle const& rhs);
            bool operator>=(Undoable_Attribute_Data_Handle const& rhs);

            // Comparison Operators for compare to the null handle
            //============================================================
            bool operator==(Null_Handle_Type const& rhs);
            bool operator!=(Null_Handle_Type const& rhs);

        protected:
            // Protected Helpers
            //============================================================
            Command_History& get_command_history();
            Command_History const& cget_command_history() const;

        private:
            // Data Members
            //============================================================
            Attribute_Data_Handle m_attribute_handle;
            Command_History* mp_command_history;
        };
    } // namespace internal
} // namespace saklib

#endif // SAKLIB_INTERNAL_UNDOABLE_ATTRIBUTE_DATA_HANDLE_H
