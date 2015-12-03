#ifndef SAKLIB_INTERNAL_UNDOABLE_ATTRIBUTE_DATA_HANDLE_BOOL_H
#define SAKLIB_INTERNAL_UNDOABLE_ATTRIBUTE_DATA_HANDLE_BOOL_H

#ifndef SAKLIB_INTERNAL_UNDOABLE_ATTRIBUTE_DATA_HANDLE_BOOL__FWD_H
#include "undoable_attribute_data_handle_bool__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_UNDOABLE_ATTRIBUTE_DATA_HANDLE__FWD_H
#include "undoable_attribute_data_handle__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE_BOOL_H
#include "attribute_data_handle_bool.h"
#endif

#ifndef SAKLIB_INTERNAL_COMMAND_HISTORY__FWD_H
#include "command_history__fwd.h"
#endif

namespace saklib
{
    namespace internal
    {
        //---------------------------------------------------------------------------
        // Undoable_Attribute_Data_Handle_Bool
        //---------------------------------------------------------------------------
        class Undoable_Attribute_Data_Handle_Bool
        {
        public:
            // Typedefs
            //============================================================
            using handle_type = Attribute_Data_Handle_Bool::handle_type;

            // Special 6
            //============================================================
            Undoable_Attribute_Data_Handle_Bool();
            explicit Undoable_Attribute_Data_Handle_Bool(Attribute_Data_Handle_Bool const& a_attribute_handle, Command_History* ap_command_history);
            explicit Undoable_Attribute_Data_Handle_Bool(Attribute_Data_Handle_Bool && a_attribute_handle, Command_History* ap_command_history);
            ~Undoable_Attribute_Data_Handle_Bool();

            Undoable_Attribute_Data_Handle_Bool(Undoable_Attribute_Data_Handle_Bool const& other);
            Undoable_Attribute_Data_Handle_Bool& operator=(Undoable_Attribute_Data_Handle_Bool const& other);

            Undoable_Attribute_Data_Handle_Bool(Undoable_Attribute_Data_Handle_Bool && other);
            Undoable_Attribute_Data_Handle_Bool& operator=(Undoable_Attribute_Data_Handle_Bool && other);

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

            bool cget_value() const;

            bool can_set_value_to(bool a_value) const;

            //bool try_set_value(bool a_value);

            bool set_value(bool a_value);

            // Comparison Operators
            //============================================================
            bool operator==(Undoable_Attribute_Data_Handle_Bool const& rhs);
            bool operator!=(Undoable_Attribute_Data_Handle_Bool const& rhs);
            bool operator<(Undoable_Attribute_Data_Handle_Bool const& rhs);
            bool operator>(Undoable_Attribute_Data_Handle_Bool const& rhs);
            bool operator<=(Undoable_Attribute_Data_Handle_Bool const& rhs);
            bool operator>=(Undoable_Attribute_Data_Handle_Bool const& rhs);

            // Comparison Operators to Untyped Handle
            //============================================================
            //bool operator==(Undoable_Attribute_Data_Handle const& rhs);
            //bool operator!=(Undoable_Attribute_Data_Handle const& rhs);

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
            Attribute_Data_Handle_Bool m_attribute_handle;
            Command_History* mp_command_history;
        };
    } // namespace internal
} // namespace saklib

#endif // SAKLIB_INTERNAL_UNDOABLE_ATTRIBUTE_DATA_HANDLE_BOOL_H
