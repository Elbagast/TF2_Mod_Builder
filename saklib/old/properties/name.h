#ifndef SAKLIB_INTERNAL_PROPERTIES_NAME_H
#define SAKLIB_INTERNAL_PROPERTIES_NAME_H

#ifndef SAKLIB_INTERNAL_PROPERTIES_NAME__FWD_H
#include "name__fwd.h"
#endif

namespace saklib
{
    namespace internal
    {
        namespace properties
        {
            namespace local
            {
                namespace read
                {
                    template <typename T>
                    class Name
                    {
                    public:
                        using property_type = T;
                    };
                } // namespace read

                namespace write
                {
                    template <typename T>
                    class Name;
                } // namespace read
            } // namespace local

            namespace remote
            {
                namespace read
                {
                    template <typename T>
                    class Name;
                } // namespace read

                namespace write
                {
                    template <typename T>
                    class Name;
                } // namespace read
            } // namespace remote
        } // namespace properties

    } // namespace internal
} // namespace saklib


#ifndef SAKLIB_INTERNAL_PROPERTIES_NAME__INLINE_H
#include "name__inline.h"
#endif

#endif // SAKLIB_INTERNAL_PROPERTIES_NAME_H

