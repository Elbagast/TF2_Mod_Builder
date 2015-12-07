#ifndef SAKLIB_INTERNAL_UNDOABLE_ATTRIBUTE_DATA_HANDLE_INT_H
#define SAKLIB_INTERNAL_UNDOABLE_ATTRIBUTE_DATA_HANDLE_INT_H

#ifndef SAKLIB_INTERNAL_UNDOABLE_ATTRIBUTE_DATA_HANDLE_INT__FWD_H
#include "undoable_attribute_data_handle_int__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_UNDOABLE_ATTRIBUTE_DATA_HANDLE__FWD_H
#include "undoable_attribute_data_handle__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE_INT_H
#include "attribute_data_handle_int.h"
#endif

#ifndef SAKLIB_INTERNAL_COMMAND_HISTORY__FWD_H
#include "command_history__fwd.h"
#endif

namespace saklib
{
    namespace internal
    {
        //---------------------------------------------------------------------------
        // Undoable_Attribute_Data_Handle_Integral_Type<T>
        //---------------------------------------------------------------------------
        template <typename T>
        class Undoable_Attribute_Data_Handle_Integral_Type
        {
        public:
            // Typedefs
            //============================================================
            using handle_type = typename Attribute_Data_Handle_Integral_Type<T>::handle_type;

            using int_type = T;

            // Special 6
            //============================================================
            Undoable_Attribute_Data_Handle_Integral_Type();
            Undoable_Attribute_Data_Handle_Integral_Type(Attribute_Data_Handle_Integral_Type<T> const& a_attribute_handle, Command_History& ar_command_history);
            Undoable_Attribute_Data_Handle_Integral_Type(Attribute_Data_Handle_Integral_Type<T> && a_attribute_handle, Command_History& ar_command_history);
            ~Undoable_Attribute_Data_Handle_Integral_Type();

            Undoable_Attribute_Data_Handle_Integral_Type(Undoable_Attribute_Data_Handle_Integral_Type const& other);
            Undoable_Attribute_Data_Handle_Integral_Type& operator=(Undoable_Attribute_Data_Handle_Integral_Type const& other);

            Undoable_Attribute_Data_Handle_Integral_Type(Undoable_Attribute_Data_Handle_Integral_Type && other);
            Undoable_Attribute_Data_Handle_Integral_Type& operator=(Undoable_Attribute_Data_Handle_Integral_Type && other);

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

            int_type cget_value() const;

            bool can_set_value_to(int_type a_value) const;

            bool try_set_value(int_type a_value);

            void set_value(int_type a_value);

            int_type cget_lowest_value() const;

            int_type cget_highest_value() const;

            // Comparison Operators
            //============================================================
            bool operator==(Undoable_Attribute_Data_Handle_Integral_Type const& rhs);
            bool operator!=(Undoable_Attribute_Data_Handle_Integral_Type const& rhs);
            bool operator<(Undoable_Attribute_Data_Handle_Integral_Type const& rhs);
            bool operator>(Undoable_Attribute_Data_Handle_Integral_Type const& rhs);
            bool operator<=(Undoable_Attribute_Data_Handle_Integral_Type const& rhs);
            bool operator>=(Undoable_Attribute_Data_Handle_Integral_Type const& rhs);

            // Comparison Operators to Untyped Handle
            //============================================================
            bool operator==(Undoable_Attribute_Data_Handle const& rhs);
            bool operator!=(Undoable_Attribute_Data_Handle const& rhs);

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
            Attribute_Data_Handle_Integral_Type<T> m_attribute_handle;
            Command_History* mp_command_history;
        };
    } // namespace internal
} // namespace saklib

#endif // SAKLIB_INTERNAL_UNDOABLE_ATTRIBUTE_DATA_HANDLE_INT_H
