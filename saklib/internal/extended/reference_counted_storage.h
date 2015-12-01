#ifndef SAKLIB_INTERNAL_REFERENCE_COUNTED_STORAGE_H
#define SAKLIB_INTERNAL_REFERENCE_COUNTED_STORAGE_H

#ifndef SAKLIB_INTERNAL_REFERENCE_COUNTED_STORAGE__FWD_H
#include "reference_counted_storage__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_HANDLE_H
#include "handle.h"
#endif

#ifndef SAKLIB_INTERNAL_HANDLE_FACTORY_H
#include "handle_factory.h"
#endif

#include <map>
#include <tuple>
#include <queue>
#include <functional>
#include <memory>

namespace saklib
{
    namespace internal
    {
        template <typename T, typename... Args>
        class Reference_Counted_Storage
        {
        private:
            template <typename T_Again>
            struct Internal
            {
                // Typedefs
                //============================================================
                using data_type = T_Again;
                using handle_type = Handle<data_type>;
                using handle_factory_type = Handle_Factory<data_type>;

                using data_stored_type = data_type;
                using data_return_type = data_type&;
                using data_const_return_type = data_type const&;
                using reference_count_type = std::size_t;

                static data_return_type get_data_fail();
                static data_const_return_type cget_data_fail();

                static data_return_type get_data_return_from_stored(data_stored_type& a_stored);
                static data_const_return_type cget_data_return_from_stored(data_stored_type const& a_stored);
            };

            template <typename T_Again>
            struct Internal<T_Again*>
            {
                // Typedefs
                //============================================================
                using data_type = T_Again;
                using handle_type = Handle<data_type>;
                using handle_factory_type = Handle_Factory<data_type>;

                using data_stored_type = std::unique_ptr<data_type>;
                using data_return_type = data_type*;
                using data_const_return_type = data_type const*;
                using reference_count_type = std::size_t;

                static data_return_type get_data_fail();
                static data_const_return_type cget_data_fail();

                static data_return_type get_data_return_from_stored(data_stored_type& a_stored);
                static data_const_return_type cget_data_return_from_stored(data_stored_type const& a_stored);
            };

            using internal_type = Internal<T>;

        public:
            // Probably want to static assert the functor

            // Typedefs
            //============================================================
            using data_type = typename internal_type::data_type;
            using handle_type = typename internal_type::handle_type;
            using handle_factory_type = typename internal_type::handle_factory_type;

            using data_stored_type = typename internal_type::data_stored_type;
            using data_return_type = typename internal_type::data_return_type;
            using data_const_return_type = typename internal_type::data_const_return_type;
            using reference_count_type = typename internal_type::reference_count_type;

            using tuple_type = std::tuple < data_stored_type, reference_count_type, Args...>;
            using map_type = std::map < handle_type, tuple_type >;
            using queue_type = std::priority_queue<handle_type, std::vector<handle_type>, std::greater<handle_type>>;

            // Special 6
            //============================================================
            Reference_Counted_Storage();

            // Interface
            //============================================================
            handle_type make_null_handle() const;

            handle_type emplace_data(data_stored_type&& a_data);

            bool is_null(handle_type const& a_handle) const;

            bool is_valid(handle_type const& a_handle) const;

            bool has_data(handle_type const& a_handle) const;

            data_return_type get_data(handle_type const& a_handle);

            data_const_return_type cget_data(handle_type const& a_handle) const;

            reference_count_type get_reference_count(handle_type const& a_handle) const;

            void increment_reference_count(handle_type const& a_handle);

            void decrement_reference_count(handle_type const& a_handle);

            static reference_count_type reference_count_max();

            static reference_count_type reference_count_zero();

            template <std::size_t I>
            typename std::tuple_element<I, tuple_type >::type& get_extra_property(handle_type const& a_handle);

            template <std::size_t I>
            typename std::tuple_element<I, tuple_type >::type const& cget_extra_property(handle_type const& a_handle) const;

            template <std::size_t I>
            void set_extra_property(handle_type const& a_handle, typename std::tuple_element<I, tuple_type >::type const& a_value);

        private:
            // By using a tuple the manager can potentially be extended
            //using tuple_type = std::tuple < data_stored_type, reference_count_type, Args...>;
           // using map_type = std::map < handle_type, tuple_type >;
            //using queue_type = std::priority_queue<handle_type, std::vector<handle_type>, std::greater<handle_type>>;

            data_return_type get_iterator_data(typename map_type::iterator a_iterator);

            data_const_return_type cget_iterator_data(typename map_type::const_iterator a_iterator) const;

            reference_count_type& get_iterator_reference_count(typename map_type::iterator a_iterator);

            reference_count_type const& cget_iterator_reference_count(typename map_type::const_iterator a_iterator) const;

            map_type m_map;
            handle_factory_type m_handle_factory;
            bool m_currently_erasing;
            queue_type m_erase_queue;
        };


    } // namespace internal
} // namespace saklib

#ifndef SAKLIB_INTERNAL_REFERENCE_COUNTED_STORAGE__INLINE_H
#include "reference_counted_storage__inline.h"
#endif

#endif // SAKLIB_INTERNAL_REFERENCE_COUNTED_STORAGE_H

