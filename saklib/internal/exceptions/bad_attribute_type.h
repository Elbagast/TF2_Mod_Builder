#ifndef SAKLIB_INTERNAL_BAD_ATTRIBUTE_TYPE_H
#define SAKLIB_INTERNAL_BAD_ATTRIBUTE_TYPE_H

#ifndef SAKLIB_INTERNAL_STRING_H
#include "../string.h"
#endif

#include <stdexcept>

namespace saklib
{
    namespace internal
    {
        class Bad_Attribute_Type :
                public std::bad_cast
        {
        public:
            Bad_Attribute_Type(String const& a_attempted_type, String const& a_actual_type);
            ~Bad_Attribute_Type() override;

            char const* what() const override;

            String const& get_attempted_type() const;
            String const& get_actual_type() const;
        private:
            String m_attempted_type;
            String m_actual_type;
            String m_what;
        };

    } // namespace internal
} // namespace saklib


#endif // BAD_ATTRIBUTE_TYPE_H
