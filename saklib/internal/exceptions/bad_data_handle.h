#ifndef SAKLIB_INTERNAL_BAD_DATA_HANDLE_H
#define SAKLIB_INTERNAL_BAD_DATA_HANDLE_H

#ifndef SAKLIB_INTERNAL_NULL_HANDLE_H
#include "../null_integer_id.h"
#endif

#ifndef INCLUDE_STD_STRING
#define INCLUDE_STD_STRING
#include <string>
#endif

#ifndef INCLUDE_STD_STDEXCEPT
#define INCLUDE_STD_STDEXCEPT
#include <stdexcept>
#endif

namespace saklib
{
    namespace internal
    {
        //---------------------------------------------------------------------------
        // Bad_Data_Handle
        //---------------------------------------------------------------------------
        class Bad_Data_Handle :
                public std::out_of_range
        {
        public:
            // Special 6
            //============================================================
            Bad_Data_Handle();
            Bad_Data_Handle(std::string const& a_type, Integer_ID_Value_Type a_value);
            ~Bad_Data_Handle() override;

            // Interface
            //============================================================
            char const* what() const override;

            std::string const& get_type() const;
            Integer_ID_Value_Type cget_handle_value() const;
        private:
            // Data Members
            //============================================================
            std::string m_type;
            std::string m_what;
            Integer_ID_Value_Type m_value;
        };


    } // namespace internal
} // namespace saklib



#endif // SAKLIB_INTERNAL_BAD_DATA_HANDLE_H
