#ifndef SAKLIB_INTERNAL_REFERENCE_COUNTED_STORAGE_H
#define SAKLIB_INTERNAL_REFERENCE_COUNTED_STORAGE_H

#ifndef SAKLIB_INTERNAL_REFERENCE_COUNTED_STORAGE__FWD_H
#include "reference_counted_storage__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_HANDLE_H
#include "handle.h"
#endif

#ifndef SAKLIB_INTERNAL_STORAGE_TRAITS_H
#include "storage_traits.h"
#endif

#ifndef INCLUDE_STD_MAP
#define INCLUDE_STD_MAP
#include <map>
#endif

#ifndef INCLUDE_STD_TUPLE
#define INCLUDE_STD_TUPLE
#include <tuple>
#endif

#ifndef INCLUDE_STD_VECTOR
#define INCLUDE_STD_VECTOR
#include <vector>
#endif

#ifndef INCLUDE_STD_QUEUE
#define INCLUDE_STD_QUEUE
#include <queue>
#endif

#ifndef INCLUDE_STD_FUNCTIONAL
#define INCLUDE_STD_FUNCTIONAL
#include <functional>
#endif

#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif
/*
#ifndef INCLUDE_BOOST_SIGNALS2
#define INCLUDE_BOOST_SIGNALS2
#include <boost/signals2.hpp>
#endif
*/
#ifndef SAKLIB_INTERNAL_REFERENCE_COUNTER_H
#include "reference_counter.h"
#endif

namespace saklib
{
    namespace internal
    {
        template <typename H>
        class Reference_Counted_Storage__Slot_Box
        {
        public:
            using handle_type = H;

            virtual ~Reference_Counted_Storage__Slot_Box() = default;

            virtual void slot_new_data(handle_type const& a_handle) = 0;
            virtual void slot_destruction_start(handle_type const& a_handle) = 0;
            virtual void slot_destruction_end(handle_type const& a_handle) = 0;
        };

        //---------------------------------------------------------------------------
        // Reference_Counted_Storage<H, Args...>
        //---------------------------------------------------------------------------
        // Arbitrarily extend to N data types, with at least one. This version gives up the pre_destructor
        // so right now there is no informing anything of changes.

        template <typename H, typename... Args>
        class Reference_Counted_Storage
        {
            static_assert(std::tuple_size<std::tuple<Args...>>::value > 0, "Cannot instantiate with no types, would mean it stores no data");

        public:
            // Typedefs
            //============================================================
            // this is the data that is stored in the map...
            using data_tuple_type = std::tuple<Args...>;
            using stored_tuple_type = std::tuple <typename Storage_Traits<Args>::stored_type...>;
            using handle_type = H;

            // The map stores the reference count and data seperately since this object is responsible for
            // the reference count.
            using map_type = std::map < handle_type, std::pair<std::size_t, stored_tuple_type> >;

            // Type for the erase queue
            using queue_type = std::priority_queue<handle_type, std::vector<handle_type>, std::greater<handle_type>>;

            // Need to figure out how I want to have this class inform others that data is being destroyed
            //using signal_destruction_start_type = boost::signals2::signal<void(handle_type const&)>;
            //using slot_destruction_start_type = typename signal_destruction_start_type::slot_type;

            //using signal_destruction_end_type = boost::signals2::signal<void(handle_type const&)>;
            //using signal_destruction_end_type = typename signal_destruction_start_type::slot_type;

            //---------------------------------------------------------------------------
            // Data<N>
            //---------------------------------------------------------------------------
            // Convenience access to the relevent types for a given part of the data tuple.
            template <std::size_t N>
            class Data
            {
                // Typedefs
                //============================================================
            public:
                using template_arg_type = typename std::tuple_element<N, data_tuple_type>::type;
                using storage_traits_type = Storage_Traits<template_arg_type>;
                using stored_type = typename storage_traits_type::stored_type;
                using return_type = typename storage_traits_type::return_type;
                using const_return_type = typename storage_traits_type::const_return_type;
            };

            // Special 6
            //============================================================
            Reference_Counted_Storage();

            // Interface
            //============================================================

            bool has_data(handle_type const& a_handle) const;

            // constexpr
            static std::size_t data_types_count(); // return N

            template <std::size_t N = 0>
            typename Data<N>::return_type get_data(handle_type const& a_handle);
            template <std::size_t N = 0>
            typename Data<N>::const_return_type cget_data(handle_type const& a_handle) const;

            std::size_t cget_reference_count(handle_type const& a_handle) const;

            void increment_reference_count(handle_type const& a_handle);

            void decrement_reference_count(handle_type const& a_handle);

            // constexpr
            static std::size_t reference_count_max();

            // constexpr
            static std::size_t reference_count_zero();

            // must declare this after the functions it will use
            using reference_counter_type = Member_Reference_Counter <
                                                                     Reference_Counted_Storage<H, Args...>,
                                                                     H,
                                                                     &Reference_Counted_Storage<H, Args...>::increment_reference_count,
                                                                     &Reference_Counted_Storage<H, Args...>::decrement_reference_count
                                                                     >;

            // Emplace the given data using the given handle, return true if succeeded. The handle
            // supplied must not already be in use (i.e. has_data(a_handle) == false) and it is not
            // this object's responsibility to ensure that.
            reference_counter_type emplace_data(handle_type const& a_handle, typename Storage_Traits<Args>::stored_type&&... a_data);
            reference_counter_type emplace_data_tuple(handle_type const& a_handle, stored_tuple_type&& a_tuple);

            reference_counter_type make_handle(handle_type const& a_handle);

            std::vector<handle_type> cget_all_handles() const;


            // currently unimplemented.
            void signal_new_data(handle_type const& a_handle);
            void signal_destruction_start(handle_type const& a_handle);
            void signal_destruction_end(handle_type const& a_handle);

        private:
            std::size_t& get_iterator_reference_count(typename map_type::iterator a_iterator);
            std::size_t cget_iterator_reference_count(typename map_type::const_iterator a_iterator) const;

            template <std::size_t N>
            typename Data<N>::return_type get_iterator_data(typename map_type::iterator a_iterator);
            template <std::size_t N>
            typename Data<N>::const_return_type cget_iterator_data(typename map_type::const_iterator a_iterator) const;

            // Data Members
            //============================================================
            map_type m_map;
            bool m_currently_erasing;
            queue_type m_erase_queue;
        };

    } // namespace internal
} // namespace saklib

#ifndef SAKLIB_INTERNAL_REFERENCE_COUNTED_STORAGE__INLINE_H
#include "reference_counted_storage__inline.h"
#endif

#endif // SAKLIB_INTERNAL_REFERENCE_COUNTED_STORAGE_H
