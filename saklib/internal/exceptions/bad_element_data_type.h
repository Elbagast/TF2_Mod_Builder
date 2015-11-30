#ifndef SAKLIB_INTERNAL_BAD_ELEMENT_DATA_TYPE_H
#define SAKLIB_INTERNAL_BAD_ELEMENT_DATA_TYPE_H

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
        // Bad_Element_Data_Type
        //---------------------------------------------------------------------------

        class Bad_Element_Data_Type :
                public std::out_of_range
        {
        public:
            // Special 6
            //============================================================
            explicit Bad_Element_Data_Type(std::string const& a_type);
            ~Bad_Element_Data_Type() override;

            // Interface
            //============================================================
            char const* what() const override;

            std::string const& get_type() const;
        private:
            // Data Members
            //============================================================
            std::string m_type;
            std::string m_what;
        };

    } // namespace internal
} // namespace saklib

#endif // BAD_ELEMENT_DATA_TYPE_H
