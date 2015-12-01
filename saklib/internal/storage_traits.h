#ifndef SAKLIB_INTERNAL_STORAGE_TRAITS_H
#define SAKLIB_INTERNAL_STORAGE_TRAITS_H

#ifndef SAKLIB_INTERNAL_STORAGE_TRAITS__FWD_H
#include "storage_traits__fwd.h"
#endif

#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif

namespace saklib
{
    namespace internal
    {
        template <typename T>
        class Storage_Traits
        {
        public:
            // Typedefs
            //============================================================
            using stored_type = T;
            using return_type = T&;
            using const_return_type = T const&;

            // Interface
            //============================================================
            static return_type get_data_from_stored(stored_type& a_stored);
            static const_return_type cget_data_from_stored(stored_type const& a_stored);

            static return_type get_data_fail();
            static const_return_type cget_data_fail();
        };

        //---------------------------------------------------------------------------
        // Internal<T*>
        //---------------------------------------------------------------------------

        template <typename T>
        class Storage_Traits<T*>
        {
        public:
            // Typedefs
            //============================================================
            using stored_type = std::unique_ptr<T>;
            using return_type = T*;
            using const_return_type = T const*;

            // Interface
            //============================================================
            static return_type get_data_from_stored(stored_type& a_stored);
            static const_return_type cget_data_from_stored(stored_type const& a_stored);

            static return_type get_data_fail();
            static const_return_type cget_data_fail();
        };

    } // namespace internal
} // namespace saklib

#ifndef SAKLIB_INTERNAL_STORAGE_TRAITS__INLINE_H
#include "storage_traits__inline.h"
#endif

#endif // SAKLIB_INTERNAL_STORAGE_TRAITS_H

