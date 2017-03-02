#ifndef DCLIB_META_TYPELIST_HPP
#define DCLIB_META_TYPELIST_HPP

#include <type_traits>

namespace dclib
{
    namespace meta
    {
        //---------------------------------------------------------------------------
        // Class typelist<Ts...>
        //---------------------------------------------------------------------------
        // Type wrapper for a variadic template argument. It has no data members so
        // as to signify that we are using it only to manipulate the types.

        template <typename...Ts>
        struct typelist {};

        // Namespace for Metafunctions
        namespace mf
        {
            //---------------------------------------------------------------------------
            // Metafunction list_size<List>
            //---------------------------------------------------------------------------
            // Get the size of the typelist as a compiletime constant.
            // e.g. list_size<typelist<A,B,C>>::value = 3

            template <typename List>
            struct size;

            template <typename...Args>
            struct size<typelist<Args...>> : public std::integral_constant<std::size_t, sizeof...(Args)> {};

            static_assert(size<typelist<bool,int,float,void>>::value == 4, "typelist list_size failed.");

            //---------------------------------------------------------------------------
            // Metafunction concatenate<Front, Back>
            //---------------------------------------------------------------------------
            // Create a typelist that is made up of all the types in Front, followed by
            // all the types in Back.
            // e.g. push_back<typelist<A,B,C>, typelist<D,E,F>>::type = typelist<A,B,C,D,E,F>

            template <typename Front, typename Back>
            struct concatenate;

            template <typename...Fs, typename...Bs>
            struct concatenate<typelist<Fs...>, typelist<Bs...>>
            {
                using type = typelist<Fs...,Bs...>;
            };

            // Helper alias
            template <typename Front, typename Back>
            using concatenate_t = typename concatenate<Front,Back>::type;

            static_assert(std::is_same<typelist<bool,int,float,void>, concatenate_t<typelist<bool,int>,typelist<float,void>>>::value, "typelist concatenate failed.");

            //---------------------------------------------------------------------------
            // Metafunction push_back<List, Type>
            //---------------------------------------------------------------------------
            // Add Type to the end of List.
            // e.g. push_back<typelist<A,B,C>, D>::type = typelist<A,B,C,D>

            template <typename List, typename T>
            struct push_back;

            template <typename T, typename...Args>
            struct push_back<typelist<Args...>, T>
            {
                using type = typelist<Args...,T>;
            };

            // Helper alias
            template <typename List, typename T>
            using push_back_t = typename push_back<List,T>::type;

            static_assert(std::is_same<typelist<bool,int,float>, push_back_t<typelist<bool,int>,float>>::value, "typelist push_back failed.");

            //---------------------------------------------------------------------------
            // Metafunction push_front<List, Type>
            //---------------------------------------------------------------------------
            // Add Type to the front of List.
            // e.g. push_front<typelist<A,B,C>, D>::type = typelist<D,A,B,C>

            template <typename List, typename T>
            struct push_front;

            template <typename T, typename...Args>
            struct push_front<typelist<Args...>, T>
            {
                using type = typelist<T,Args...>;
            };

            // Helper alias
            template <typename List, typename T>
            using push_front_t = typename push_front<List,T>::type;

            static_assert(std::is_same<typelist<float,bool,int>, push_front_t<typelist<bool,int>,float>>::value, "typelist push_front failed.");

            //---------------------------------------------------------------------------
            // Metafunction reverse<List>
            //---------------------------------------------------------------------------
            // Reverse the order of List.
            // e.g. reverse<typelist<A,B,C>>::type = typelist<C,B,A>

            template <typename T>
            struct reverse;

            // Nothing changes with an empty typelist.
            template <>
            struct reverse<typelist<>>
            {
                using arg_type = typelist<>;
                using type = typelist<>;
            };

            // Nothing changes with a typelist with a single type.
            template <typename T>
            struct reverse<typelist<T>>
            {
                using arg_type = typelist<T>;
                using type = typelist<T>;
            };

            template <typename T, typename...Args>
            struct reverse<typelist<T,Args...>>
            {
                using arg_type = typelist<T,Args...>;
                using type = typename push_back<typename reverse<typelist<Args...>>::type, T>::type;
            };

            // Due to recursive calls, having lots of types needs a hand.
            template
                    <
                    typename A,
                    typename B,
                    typename C,
                    typename D,
                    typename E,
                    typename F,
                    typename G,
                    typename H,
                    typename ... Args
                    >
            struct reverse<typelist<A,B,C,D,E,F,G,H,Args...>>
            {
                using type = concatenate_t<typename reverse<typelist<Args...>>::type, typelist<H,G,F,E,D,C,B,A>>;
            };

            // Helper alias
            template <typename List>
            using reverse_t = typename reverse<List>::type;

            static_assert(std::is_same<typelist<float,int,bool>, reverse_t<typelist<bool,int,float>>>::value, "typelist reverse failed.");

            //---------------------------------------------------------------------------
            // Metafunction pop_front<List, Count = 1>
            //---------------------------------------------------------------------------
            // Remove the front Count of types from a typelist. The default Count is 1
            // so 1 is removed by default. Using a count of 0 will do nothing. If there
            // is nothing to remove then nothing happens.
            // e.g. pop_front<typelist<A,B,C>>::type = typelist<B,C>
            // e.g. pop_front<typelist<A,B,C>,2>::type = typelist<C>

            template <typename List, std::size_t Count = 1>
            struct pop_front;

            template <std::size_t N, typename T, typename...Args>
            struct pop_front<typelist<T,Args...>, N>
            {
                using type = typename pop_front<typelist<Args...>, N-1>::type;
            };

            // If the tuple has at least 1 element and we only remove one, remove the front.
            template <typename T, typename...Args>
            struct pop_front<typelist<T,Args...>, 1>
            {
                using type = typelist<Args...>;
            };

            // If the tuple has at least 1 element and we remove none, type is the same as input.
            template < typename T, typename...Args>
            struct pop_front<typelist<T,Args...>,0>
            {
                using type = typelist<T,Args...>;
            };

            // If the tuple has no elements we don't care how many will be removed, as nothing happens
            template <std::size_t N>
            struct pop_front<typelist<>,N>
            {
                using type = typelist<>;
            };

            // Helper alias
            template <typename List, std::size_t Count = 1>
            using pop_front_t = typename pop_front<List,Count>::type;

            static_assert(std::is_same<typelist<int,float,void>, pop_front_t<typelist<bool,int,float,void>>>::value, "typelist pop_front failed.");
            static_assert(std::is_same<typelist<void>, pop_front_t<typelist<bool,int,float,void>,3>>::value, "typelist pop_front failed.");


            //---------------------------------------------------------------------------
            // Metafunction pop_back<List, Count = 1>
            //---------------------------------------------------------------------------
            // Remove the back Count of types from a typelist. The default Count is 1
            // so 1 is removed by default. Using a count of 0 will do nothing. If there
            // is nothing to remove then nothing happens.
            // e.g. pop_back<typelist<A,B,C>>::type = typelist<A,B>
            // e.g. pop_back<typelist<A,B,C>,2>::type = typelist<A>

            template <typename List, std::size_t Count = 1>
            struct pop_back;

            // If List contains at least one type, reverse List then remove Count from
            // the front of that, then reverse the result.
            template <std::size_t Count, typename T, typename...Args>
            struct pop_back<typelist<T,Args...>, Count>
            {
                using type = reverse_t<pop_front_t<reverse_t<typelist<T,Args...>>,Count>>;
            };

            // If Count is 0 then the output is the input.
            template <typename T,typename...Args>
            struct pop_back<typelist<T,Args...>,0>
            {
                using type = typelist<T,Args...>;
            };

            // If we are acting on an empty list then the output is empty regardless.
            template <std::size_t Count>
            struct pop_back<typelist<>,Count>
            {
                using type = typelist<>;
            };

            // Helper alias
            template <typename List, std::size_t Count = 1>
            using pop_back_t = typename pop_back<List,Count>::type;

            static_assert(std::is_same<typelist<bool,int,float>, pop_back_t<typelist<bool,int,float,void>>>::value, "typelist pop_back failed.");
            static_assert(std::is_same<typelist<bool>, pop_back_t<typelist<bool,int,float,void>,3>>::value, "typelist pop_back failed.");

            //---------------------------------------------------------------------------
            // Metafunction type_at<List,Index>
            //---------------------------------------------------------------------------
            // Get the type in a typelist that has a given index in the list. If Index is
            // out of bounds, the template will fail to instantiate.
            // e.g. type_at<typelist<A,B,C>,0>::type = A
            // e.g. type_at<typelist<A,B,C>,1>::type = B
            // e.g. type_at<typelist<A,B,C>,2>::type = C
            // e.g. type_at<typelist<A,B,C>,3>::type = FAIL

            template <typename List, std::size_t Index>
            struct type_at;

            template <std::size_t Index, typename T,typename...Args>
            struct type_at<typelist<T,Args...>,Index>
            {
                using type = typename type_at<typelist<Args...>,Index-1>::type;
            };

            template <typename T,typename...Args>
            struct type_at<typelist<T,Args...>,0>
            {
                using type = T;
            };

            // Helper alias
            template <typename List, std::size_t Index>
            using type_at_t = typename type_at<List,Index>::type;

            static_assert(std::is_same<bool, type_at_t<typelist<bool,int,float,void>,0>>::value, "typelist type_at failed.");
            static_assert(std::is_same<int, type_at_t<typelist<bool,int,float,void>,1>>::value, "typelist type_at failed.");
            static_assert(std::is_same<float, type_at_t<typelist<bool,int,float,void>,2>>::value, "typelist type_at failed.");
            static_assert(std::is_same<void, type_at_t<typelist<bool,int,float,void>,3>>::value, "typelist type_at failed.");

            // This line should fail to compile. The test would fail anyway, but it should break.
            //static_assert(std::is_same<void, type_at_t<typelist<bool,int,float,void>,5>>::value, "typelist type_at failed.");

            //---------------------------------------------------------------------------
            // Metafunction remove<List,Index,Count>
            //---------------------------------------------------------------------------
            // Remove types from List starting at Index, removing Count types in total.
            // If we run out of types to remove, we stop.

            template <typename List, std::size_t Index, std::size_t Count = 1>
            struct remove;

            // We have to have an out of bounds check on this one.
            template <std::size_t Index, std::size_t Count, typename... Args>
            struct remove<typelist<Args...>,Index,Count>
            {
                using type =
                typename std::conditional
                <
                    (Index < sizeof...(Args)),
                    concatenate_t<pop_back_t<typelist<Args...>,sizeof...(Args) - Index>, pop_front_t<typelist<Args...>,Index + Count>>,
                    typelist<Args...>
                >::type;
            };

            // If our Count is 0 we do nothing regardless of anything else.
            template <std::size_t Index, typename... Args>
            struct remove<typelist<Args...>,Index,0>
            {
                using type = typelist<Args...>;
            };

            // Helper alias
            template <typename List, std::size_t Index, std::size_t Count = 1>
            using remove_t = typename remove<List,Index,Count>::type;

            static_assert(std::is_same<typelist<bool,float,void>, remove_t<typelist<bool,int,float,void>,1>>::value, "typelist remove failed.");
            static_assert(std::is_same<typelist<bool,void>, remove_t<typelist<bool,int,float,void>,1,2>>::value, "typelist remove failed.");
            static_assert(std::is_same<typelist<bool,int>, remove_t<typelist<bool,int,float,void>,2,5>>::value, "typelist remove failed.");
            static_assert(std::is_same<typelist<bool,int,float,void>, remove_t<typelist<bool,int,float,void>,5>>::value, "typelist remove failed.");

            //---------------------------------------------------------------------------
            // Metafunction insert<List,Type,Index,Count>
            //---------------------------------------------------------------------------
            // Insert the Type inside List1, starting at Index, Count times.
            // e.g. insert<typelist<A,B,C,D,E>,T,2>::type = typelist<A,B,T,C,D,E>
            // e.g. insert<typelist<A,B,C,D,E>,T,1,3>::type = typelist<A,T,T,T,B,C,D,E>

            template <typename List, typename Type, std::size_t Index, std::size_t Count = 1>
            struct insert;












            //---------------------------------------------------------------------------
            // Metafunction insert_list<List1,List2,Index>
            //---------------------------------------------------------------------------
            // Insert the contents of List2 inside List1, starting at Index.
            // e.g. insert_list<typelist<A,B,C>,typelist<D,E,F>,1>::type = typelist<A,D,E,F,B,C>

            template <typename List1, typename List2, std::size_t Index>
            struct insert_list;












            //---------------------------------------------------------------------------
            // Metafunction sublist<List,Index,Length>
            //---------------------------------------------------------------------------
            // Get the typelist that starts at Index in List, and is as long as Length. If
            // the length overruns the end of List then we stop.

            template <typename List, std::size_t Index, std::size_t Length>
            struct sublist;

            // We have to have an out of bounds check on this one.
            // We have to specialise for List to contain at least one type.
            template <typename T, std::size_t Index, std::size_t Length, typename... Args>
            struct sublist<typelist<T,Args...>,Index,Length>
            {
                using type =
                typename std::conditional
                <
                    (Index < size<typelist<T,Args...>>::value),
                    typename sublist<pop_front_t<typelist<T,Args...>,Index>,0,Length>::type,
                    typelist<>
                >::type;
            };

            // If we start at the begining then it's simple.
            // We have to specialise for List to contain at least one type.
            template <typename T, std::size_t Length, typename... Args>
            struct sublist<typelist<T,Args...>,0,Length>
            {
                using type =
                typename std::conditional
                <
                    (Length == size<typelist<T,Args...>>::value),
                    typelist<T,Args...>,
                    typename std::conditional
                    <
                        (Length > size<typelist<T,Args...>>::value),
                        typelist<T,Args...>,
                        pop_back_t<typelist<T,Args...>, (size<typelist<T,Args...>>::value - Length)>
                    >::type
                >::type;
            };

            // If the length is 0, the type is empty.
            // We have to specialise for List to contain at least one type.
            template <typename T, std::size_t Index, typename... Args>
            struct sublist<typelist<T,Args...>,Index,0>
            {
                using type = typelist<>;
            };

            // If the length is 0, and the length is 0, the type is empty.
            // We have to specialise for List to contain at least one type.
            template <typename T, typename... Args>
            struct sublist<typelist<T,Args...>,0,0>
            {
                using type = typelist<>;
            };

            // If List is empty the result is always empty.
            template <std::size_t Index, std::size_t Length>
            struct sublist<typelist<>,Index,Length>
            {
                using type = typelist<>;
            };

            // Helper alias
            template <typename List, std::size_t Index, std::size_t Length>
            using sublist_t = typename sublist<List,Index,Length>::type;

            static_assert(std::is_same<sublist_t<typelist<>,1,2>, typelist<>>::value, "typelist sublist failed.");
            static_assert(std::is_same<sublist_t<typelist<bool,int,float,void>,1,0>, typelist<>>::value, "typelist sublist failed.");
            static_assert(std::is_same<sublist_t<typelist<bool,int,float,void>,1,2>, typelist<int,float>>::value, "typelist sublist failed.");
            static_assert(std::is_same<sublist_t<typelist<bool,int,float,void>,0,5>, typelist<bool,int,float,void>>::value, "typelist sublist failed.");
            static_assert(std::is_same<sublist_t<typelist<bool,int,float,void>,5,5>, typelist<>>::value, "typelist sublist failed.");
            static_assert(std::is_same<sublist_t<typelist<bool,int,float,void>,3,5>, typelist<void>>::value, "typelist sublist failed.");

            //---------------------------------------------------------------------------
            // Metafunction find_first<List,T>
            //---------------------------------------------------------------------------
            // Determine the index of the first instance of the T in List. If it is not
            // found, then the value is the size of List.
            // e.g find_first<typelist<A,B,C,D,E,F,G>,C>::value = 2
            // e.g find_first<typelist<A,B,C,D,E,F,G>,H>::value = 7
            // e.g find_first<typelist<A,B,C,C,C,D,E>,C>::value = 2

            template <typename List, typename T>
            struct find_first;

            template <typename T, typename A, typename... Args>
            struct find_first<typelist<A,Args...>, T> : public std::integral_constant<std::size_t, 1 + find_first<typelist<Args...>,T>::value > {};

            template <typename T, typename... Args>
            struct find_first<typelist<T,Args...>,T> : public std::integral_constant<std::size_t, 0 > {};

            template <typename T>
            struct find_first<typelist<>,T> : public std::integral_constant<std::size_t, 0 > {};

            static_assert(find_first<typelist<bool,int,float,void>,int>::value == 1, "typelist find_first failed.");
            static_assert(find_first<typelist<bool,int,float,void>,float>::value == 2, "typelist find_first failed.");
            static_assert(find_first<typelist<bool,int,float,void>,double>::value == 4, "typelist find_first failed.");

            //---------------------------------------------------------------------------
            // Metafunction count<List,T>
            //---------------------------------------------------------------------------
            // Determine how many times T is in List.

            template <typename List, typename T>
            struct count;

            namespace internal
            {
                template <typename List, typename T, std::size_t Count = 0>
                struct do_count;

                template <typename T, std::size_t Count, typename...Args>
                struct do_count<typelist<T,Args...>,T,Count> : std::integral_constant<std::size_t, do_count<typelist<Args...>,T,Count+1>::value> {};

                template <typename T, typename R, std::size_t Count, typename...Args>
                struct do_count<typelist<R,Args...>,T,Count> : std::integral_constant<std::size_t, do_count<typelist<Args...>,T,Count>::value> {};

                template <typename T, std::size_t Count>
                struct do_count<typelist<>,T,Count> : std::integral_constant<std::size_t, Count> {};
            }

            template <typename T, typename...Args>
            struct count<typelist<Args...>,T> : internal::do_count<typelist<Args...>,T> {};

            static_assert(count<typelist<bool,int,float,void>,int>::value == 1, "typelist count failed.");
            static_assert(count<typelist<bool,int,int,void>,int>::value == 2, "typelist count failed.");
            static_assert(count<typelist<int,int,int,int>,int>::value == 4, "typelist count failed.");
            static_assert(count<typelist<int,int,bool,int>,int>::value == 3, "typelist count failed.");
            static_assert(count<typelist<>,int>::value == 0, "typelist count failed.");

            //---------------------------------------------------------------------------
            // Metafunction count_front<List>
            //---------------------------------------------------------------------------
            // Determine how many times the first type in List occurs at the front of the
            // List.
            // e.g count_front<typelist<A,B,C,D,E,F,G>>::value = 1
            // e.g count_front<typelist<A,A,B,C,D,E,F>>::value = 2
            // e.g count_front<typelist<A,A,A,A,A,A,B>>::value = 6
            // e.g count_front<typelist<A,A,A>>::value = 3
            // e.g count_front<typelist<>>::value = 0

            template <typename List>
            struct count_front;

            template <typename T, typename... Args>
            struct count_front<typelist<T,T,Args...>> : public std::integral_constant<std::size_t, 1 + count_front<typelist<T,Args...>>::value> {};

            template <typename T, typename R, typename... Args>
            struct count_front<typelist<T,R,Args...>> : public std::integral_constant<std::size_t, 1> {};

            template <typename T>
            struct count_front<typelist<T>> : public std::integral_constant<std::size_t, 1> {};

            template <>
            struct count_front<typelist<>> : public std::integral_constant<std::size_t, 0> {};

            static_assert(count_front<typelist<bool,int,float,void>>::value == 1, "typelist count_front failed.");
            static_assert(count_front<typelist<bool,bool,float,void>>::value == 2, "typelist count_front failed.");
            static_assert(count_front<typelist<int,int,int,int>>::value == 4, "typelist count_front failed.");
            static_assert(count_front<typelist<>>::value == 0, "typelist count_front failed.");

            //---------------------------------------------------------------------------
            // Metafunction all_same<List>
            //---------------------------------------------------------------------------
            template <typename T>
            struct all_same;

            template <typename T, typename... Args>
            struct all_same<typelist<T,T,Args...>> : public all_same<typelist<T,Args...>> {};

            template <typename T, typename U, typename... Args>
            struct all_same<typelist<T,U,Args...>> : public std::false_type {};

            template <typename T>
            struct all_same<typelist<T>> : public std::true_type {};

            template <>
            struct all_same<typelist<>> : public std::false_type {};


            //---------------------------------------------------------------------------
            // Metafunction first_is_unique<List>
            //---------------------------------------------------------------------------
            template <typename T>
            struct first_is_unique;

            template <typename T, typename... Args>
            struct first_is_unique<typelist<T,T,Args...>> : public std::false_type {};

            template <typename T, typename U, typename... Args>
            struct first_is_unique<typelist<T,U,Args...>> : public first_is_unique<typelist<T,Args...>> {};

            template <typename T>
            struct first_is_unique<typelist<T>> : public std::true_type {};

            template <>
            struct first_is_unique<typelist<>> : public std::false_type {};


            //---------------------------------------------------------------------------
            // Metafunction all_unique<List>
            //---------------------------------------------------------------------------
            template <typename T>
            struct all_unique;

            template <typename T, typename... Args>
            struct all_unique<typelist<T,Args...>> : public std::conditional<first_is_unique<typelist<T,Args...>>::value, all_unique<typelist<Args...>>, std::false_type>::type {};

            template <typename T>
            struct all_unique<typelist<T>> : public std::true_type {};

            template <>
            struct all_unique<typelist<>> : public std::false_type {};


            //---------------------------------------------------------------------------
            // Metafunction remove_type<List>
            //---------------------------------------------------------------------------
            template <typename List, typename T>
            struct remove_type;

            template <typename T, typename... Args>
            struct remove_type<typelist<T,Args...>,T>
            {
              using type = typename remove_type<typelist<Args...>,T>::type;
            };

            template <typename T, typename U, typename... Args>
            struct remove_type<typelist<U,Args...>,T>
            {
              using type = concatenate_t<typelist<U>, typename remove_type<typelist<Args...>,T>::type>;
            };


            template <typename T>
            struct remove_type<typelist<>,T>
            {
              using type = typelist<>;
            };

            template <typename List, typename T>
            using remove_type_t = typename remove_type<List,T>::type;

            //---------------------------------------------------------------------------
            // Metafunction remove_duplicates<List>
            //---------------------------------------------------------------------------
            // Make a typelist that only has each type that appears in the input only once.

            template <typename T>
            struct remove_duplicates;

            template <typename T, typename... Args>
            struct remove_duplicates<typelist<T,Args...>>
            {
              using type = concatenate_t
              <
                typelist<T>,
                typename remove_duplicates<remove_type_t<typelist<Args...>,T>>::type
              >;
            };

            template <typename T>
            struct remove_duplicates<typelist<T>>
            {
              using type = typelist<T>;
            };

            template <>
            struct remove_duplicates<typelist<>>
            {
              using type = typelist<>;
            };

            // Helper alias
            template <typename List>
            using remove_duplicates_t = typename remove_duplicates<List>::type;


            static_assert(std::is_same<typelist<bool,int,float>, remove_duplicates_t<typelist<bool,bool,int,float>>>::value,"bad remove_duplicates");
            static_assert(std::is_same<typelist<bool,int,float>, remove_duplicates_t<typelist<bool,int,bool,float>>>::value,"bad remove_duplicates");
            static_assert(std::is_same<typelist<bool,int,float>, remove_duplicates_t<typelist<bool,bool,int,bool,int,float,int,float,bool>>>::value,"bad remove_duplicates");



        } // namespace mf
    } // namespace meta
} // namespace dclib

#endif // DCLIB_META_TYPELIST_HPP
