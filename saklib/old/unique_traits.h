#ifndef UNIQUE_TRAITS_TEMPLATE_H
#define UNIQUE_TRAITS_TEMPLATE_H

#include "types.h"
#include "elementid.h"
#include <limits>

namespace saklib
{
    /*
    Unique_Traits<T>
    ====================================================================================================
    Class which contains unique functions for each type that is specialised. By default there is nothing
    of interest.

    */
    template <typename T>
    struct Unique_Traits
    {
        static bool const is_specialised{ false };
        static bool const is_specialized{ false };
    };


    /*
    Unique_Traits<Bool>
    ====================================================================================================
    */
    template <>
    struct Unique_Traits<Bool>
    {
        static bool const is_specialised{ true };
        static bool const is_specialized{ true };

        static Bool default_initial_value()   { return Bool{false}; }
        // Nothing
    };


    /*
    Unique_Traits<Int>
    ====================================================================================================
    */
    template <>
    struct Unique_Traits<Int>
    {
        static bool const is_specialised{ true };
        static bool const is_specialized{ true };

        static Int default_initial_value()    { return Int{0}; }

        static Int default_lowest_value()     { return std::numeric_limits<Int>::lowest(); }
        static Int default_highest_value()    { return std::numeric_limits<Int>::max(); }
    };


    /*
    Unique_Traits<Double>
    ====================================================================================================
    */
    template <>
    struct Unique_Traits<Double>
    {
        static bool const is_specialised{ true };
        static bool const is_specialized{ true };

        static Double default_initial_value()       { return Double{0.0}; }

        static Double default_lowest_value()        { return std::numeric_limits<Double>::lowest(); }
        static Double default_highest_value()       { return std::numeric_limits<Double>::max(); }

        // Precision stuff...
        static size_type default_decimal_places()   { return 1000; }
        //static size_type default_lowest_exponent()  {}
        //static size_type default_highest_exponent() {}

    };


    /*
    Unique_Traits<String>
    ====================================================================================================
    */
    template <>
    struct Unique_Traits<String>
    {
        static bool const is_specialised{ true };
        static bool const is_specialized{ true };

        static String default_initial_value()    { return String{}; }

        // Nothing
    };


    /*
    Unique_Traits<Path>
    ====================================================================================================
    */
    template <>
    struct Unique_Traits<Path>
    {
        static bool const is_specialised{ true };
        static bool const is_specialized{ true };

        static Path default_initial_value()    { return Path{}; }

        // Nothing
    };


    /*
    Unique_Traits<ElementID>
    ====================================================================================================
    */
    template <>
    struct Unique_Traits<ElementID>
    {
        static bool const is_specialised{ true };
        static bool const is_specialized{ true };

        static ElementID default_initial_value()    { return invalid_elementid(); }

        // Nothing
    };

} // namespace saklib

#endif // UNIQUE_TRAITS_TEMPLATE_H

