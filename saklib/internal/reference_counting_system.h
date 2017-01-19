#ifndef REFERENCE_COUNTING_SYSTEM_H
#define REFERENCE_COUNTING_SYSTEM_H

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

namespace saklib
{
    namespace internal
    {

        //---------------------------------------------------------------------------
        // Reference_Counter
        //---------------------------------------------------------------------------
        template
                <
                typename Key,
                typename Key_const_arg,
                typename Manager,
                typename F_increment_reference_count,
                typename F_decrement_reference_count
                >
        class Reference_Counter
        {
            // static_assert( F_increment_reference_count is void operator()(Manager*, Key_const_arg));
            // static_assert( F_decrement_reference_count is void operator()(Manager*, Key_const_arg));
        };


        //---------------------------------------------------------------------------
        // Member_Reference_Counter
        //---------------------------------------------------------------------------
        template
                <
                typename Key,
                typename Key_const_arg,
                typename Manager,
                void (Manager::*F_increment_reference_count)(Key_const_arg),
                void (Manager::*F_decrement_reference_count)(Key_const_arg)
                >
        class Member_Reference_Counter;

        //---------------------------------------------------------------------------
        // Reference_Counted_Storage
        //---------------------------------------------------------------------------
        // Arbitrarily extend to N data types, with at least one. This version gives up the pre_destructor
        // so right now there is no informing anything of changes.
        template
                <
                typename Key,
                typename Key_const_arg,
                typename... Data_Types
                >
        class Reference_Counting_Storage;



        //---------------------------------------------------------------------------
        // Reference_Counting_Manager
        //---------------------------------------------------------------------------
        template
                <
                typename Key,
                typename Key_const_arg,
                typename Key_Factory,
                void (Key_Factory::*F_revoke_key)(Key_const_arg),
                typename... Data_Types
                >
        class Reference_Counting_Manager
        {
            static_assert(sizeof...(Data_Types) > 0, "Cannot instantiate with no stored data types.");
        public:
            // Typedefs
            //============================================================
            using key_type = Key;
            using key_const_arg_type = Key_const_arg;
            using key_factory_type = Key_Factory;

            using data_tuple_type = std::tuple<Data_Types...>;
            using stored_tuple_type = std::tuple <typename Storage_Traits<Data_Types>::stored_type...>;

            // The map stores the reference count and data seperately since this object is responsible for
            // the reference count.
            using map_type = std::map < key_type, std::pair<std::size_t, stored_tuple_type> >;

            // Type for the erase queue
            using queue_type = std::priority_queue<key_type, std::vector<key_type>, std::greater<key_type>>;

            //---------------------------------------------------------------------------
            // Data<N>
            //---------------------------------------------------------------------------
            // Convenience access to the relevent types for a given part of the data tuple.
            template <std::size_t N>
            struct Data
            {
                // Typedefs
                //============================================================
                using template_arg_type = typename std::tuple_element<N, data_tuple_type>::type;
                using storage_traits_type = Storage_Traits<template_arg_type>;
                using stored_type = typename storage_traits_type::stored_type;
                using return_type = typename storage_traits_type::return_type;
                using const_return_type = typename storage_traits_type::const_return_type;
            };

            // Special 6
            //============================================================
            Reference_Counting_Manager();

            // Interface
            //============================================================

            bool has_data(key_const_arg_type a_key) const;

            // constexpr
            static std::size_t data_types_count(); // return N

            template <std::size_t N = 0>
            typename Data<N>::return_type get_data(key_const_arg_type a_key);
            template <std::size_t N = 0>
            typename Data<N>::const_return_type cget_data(key_const_arg_type a_key) const;

            std::size_t cget_reference_count(key_const_arg_type a_key) const;

            void increment_reference_count(key_const_arg_type a_key);

            void decrement_reference_count(key_const_arg_type a_key);

            // constexpr
            static std::size_t reference_count_max();

            // constexpr
            static std::size_t reference_count_zero();

            using reference_counter_type =

            Member_Reference_Counter
            <
            key_type,
            key_const_arg_type,
            Reference_Counting_Manager,
            &Reference_Counting_Manager::increment_reference_count,
            &Reference_Counting_Manager::decrement_reference_count
            >;

            reference_counter_type emplace_data(typename Storage_Traits<Data_Types>::stored_type&&... a_data);
            reference_counter_type emplace_data_tuple(stored_tuple_type&& a_tuple);

            reference_counter_type make_reference_counter(key_const_arg_type a_key);
            std::vector<reference_counter_type> make_all_reference_counters();

            std::vector<key_type> cget_all_keys() const;


        private:
            std::size_t& get_iterator_reference_count(typename map_type::iterator a_iterator);
            std::size_t cget_iterator_reference_count(typename map_type::const_iterator a_iterator) const;

            template <std::size_t N>
            typename Data<N>::return_type get_iterator_data(typename map_type::iterator a_iterator);
            template <std::size_t N>
            typename Data<N>::const_return_type cget_iterator_data(typename map_type::const_iterator a_iterator) const;

            // Data Members
            //============================================================
            key_factory_type m_key_factory;
            map_type m_map;
            bool m_currently_erasing;
            queue_type m_erase_queue;
        };


    } // namespace internal
} // namespace saklib
#endif // REFERENCE_COUNTING_SYSTEM_H

