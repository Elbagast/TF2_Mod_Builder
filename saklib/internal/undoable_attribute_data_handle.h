#ifndef SAKLIB_INTERNAL_UNDOABLE_ATTRIBUTE_DATA_HANDLE_H
#define SAKLIB_INTERNAL_UNDOABLE_ATTRIBUTE_DATA_HANDLE_H

#ifndef SAKLIB_INTERNAL_UNDOABLE_ATTRIBUTE_DATA_HANDLE__FWD_H
#include "undoable_attribute_data_handle__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_UNDOABLE_ELEMENT_DATA_HANDLE__FWD_H
#include "undoable_element_data_handle__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_UNDOABLE_ATTRIBUTE_DATA_HANDLE_BOOL__FWD_H
#include "undoable_attribute_data_handle_bool__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_UNDOABLE_ATTRIBUTE_DATA_HANDLE_INT__FWD_H
#include "undoable_attribute_data_handle_int__fwd.h"
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
        //---------------------------------------------------------------------------
        // Undoable_Attribute_Data_Handle
        //---------------------------------------------------------------------------

        class Undoable_Attribute_Data_Handle
        {
            template <typename T>
            friend class Undoable_Attribute_Data_Handle_Boolean_Type;
            template <typename T>
            friend class Undoable_Attribute_Data_Handle_Integral_Type;

        public:
            // Typedefs
            //============================================================
            using handle_type = Attribute_Data_Handle::handle_type;

            // Special 6
            //============================================================
            Undoable_Attribute_Data_Handle();
            Undoable_Attribute_Data_Handle(Attribute_Data_Handle const& a_attribute_handle, Command_History& ar_command_history);
            Undoable_Attribute_Data_Handle(Attribute_Data_Handle && a_attribute_handle, Command_History& ar_command_history);
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

            Undoable_Attribute_Data_Handle_Boolean_Type<bool> cget_bool() const;

            template <typename T>
            bool is_bool_type() const;

            template <typename T>
            Undoable_Attribute_Data_Handle_Boolean_Type<T> cget_bool_type() const;

            bool is_int() const;

            Undoable_Attribute_Data_Handle_Integral_Type<int> cget_int() const;

            template <typename T>
            bool is_int_type() const;

            template <typename T>
            Undoable_Attribute_Data_Handle_Integral_Type<T> cget_int_type() const;

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
            Attribute_Data_Handle m_attribute_handle;
            mutable Command_History* mp_command_history;
        };
    } // namespace internal
} // namespace saklib

#endif // SAKLIB_INTERNAL_UNDOABLE_ATTRIBUTE_DATA_HANDLE_H
