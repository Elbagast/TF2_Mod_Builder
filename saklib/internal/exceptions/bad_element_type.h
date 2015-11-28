#ifndef SAKLIB_INTERNAL_BAD_ELEMENT_TYPE_H
#define SAKLIB_INTERNAL_BAD_ELEMENT_TYPE_H

#ifndef SAKLIB_INTERNAL_STRING_H
#include "../string.h"
#endif

#include <stdexcept>

namespace saklib
{
    namespace internal
    {
        class Bad_Element_Type :
                public std::out_of_range
        {
        public:
            explicit Bad_Element_Type(String const& a_type);
            ~Bad_Element_Type() override;

            char const* what() const override;

            String const& get_type() const;
        private:
            String m_type;
            String m_what;
        };

    } // namespace internal
} // namespace saklib

#endif // BAD_ELEMENT_TYPE_H
