#ifndef SAKLIB_INTERNAL_BAD_ATTRIBUTE_DATA_TYPE_H
#define SAKLIB_INTERNAL_BAD_ATTRIBUTE_DATA_TYPE_H

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
        // Bad_Attribute_Data_Type
        //---------------------------------------------------------------------------

        class Bad_Attribute_Data_Type :
                public std::bad_cast
        {
        public:
            // Special 6
            //============================================================
            explicit Bad_Attribute_Data_Type(std::string const& a_attempted_type);
            Bad_Attribute_Data_Type(std::string const& a_attempted_type, std::string const& a_actual_type);
            ~Bad_Attribute_Data_Type() override;

            // Interface
            //============================================================
            char const* what() const override;

            std::string const& get_attempted_type() const;
            std::string const& get_actual_type() const;
        private:
            // Data Members
            //============================================================
            std::string m_attempted_type;
            std::string m_actual_type;
            std::string m_what;
        };

    } // namespace internal
} // namespace saklib


#endif // BAD_ATTRIBUTE_DATA_TYPE_H
