#ifndef SAKLIB_INTERNAL_HANDLE_FACTORY_H
#define SAKLIB_INTERNAL_HANDLE_FACTORY_H

#ifndef SAKLIB_INTERNAL_HANDLE_FACTORY__FWD_H
#include "handle_factory__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_HANDLE_H
#include "handle.h"
#endif

#ifndef INCLUDE_STD_QUEUE
#define INCLUDE_STD_QUEUE
#include <queue>
#endif

#ifndef INCLUDE_STD_FUNCTIONAL
#define INCLUDE_STD_FUNCTIONAL
#include <functional>
#endif

namespace saklib
{
    namespace internal
    {
        //---------------------------------------------------------------------------
        // Handle_Factory<T>
        //---------------------------------------------------------------------------

        template <typename T>
        class Handle_Factory
        {
        public:
            // Typedefs
            //============================================================
            using handle_type = Handle<T>;
            using data_type = typename handle_type::data_type;

            // Special 6
            //============================================================
            Handle_Factory();

            // Interface
            //============================================================
            static handle_type make_null_handle();

            handle_type make_new_handle();

            void revoke_handle(handle_type const& handle);

        private:
            // Data Members
            //============================================================
            // The queue will store the handle with the lowest value at the top
            using queue_type = std::priority_queue<handle_type, std::vector<handle_type>, std::greater<handle_type>>;

            queue_type m_revoked_handles;
            Handle_Value_Type m_next_value;
        };

        //---------------------------------------------------------------------------
        // Sequential_Handle_Factory<T>
        //---------------------------------------------------------------------------

        template <typename T>
        class Sequential_Handle_Factory
        {
        public:
            // Typedefs
            //============================================================
            using handle_type = Handle<T>;
            using data_type = typename handle_type::data_type;

            // Special 6
            //============================================================
            Sequential_Handle_Factory();

            // Interface
            //============================================================
            static handle_type make_null_handle();

            handle_type make_new_handle();

            // constexpr ?
            static void revoke_handle(handle_type const& /*handle*/);

        private:
            // Data Members
            //============================================================
            Handle_Value_Type m_next_value;
        };
    } // namespace internal
} // namespace saklib

#ifndef SAKLIB_INTERNAL_HANDLE_FACTORY__INLINE_H
#include "handle_factory__inline.h"
#endif

#endif // SAKLIB_INTERNAL_HANDLE_FACTORY_H

