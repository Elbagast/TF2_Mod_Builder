#ifndef COMMAND_ATTRIBUTE_DATA_BOOL_H
#define COMMAND_ATTRIBUTE_DATA_BOOL_H

#include "command.h"
#include "attribute_data_handle_bool.h"

namespace saklib
{
    namespace internal
    {
        // if the handle types also become templated...
        /*
        template <typename T>
        using Command_Attribute_Data_Handle_Boolean_Type__Set_Value =

        Command_Simple_Stored_Get_Set
        <
        Attribute_Data_Handle_Boolean_Type<T>,
        typename Attribute_Data_Handle_Boolean_Type<T>::bool_type,
        typename Attribute_Data_Handle_Boolean_Type<T>::bool_type,
        &Attribute_Data_Handle_Boolean_Type<T>::cget_value,
        void,
        typename Attribute_Data_Handle_Boolean_Type<T>::bool_type,
        &Attribute_Data_Handle_Boolean_Type<T>::set_value
        >;
        */


    } // namespace internal
} // namespace saklib

#endif // COMMAND_ATTRIBUTE_DATA_BOOL_H
