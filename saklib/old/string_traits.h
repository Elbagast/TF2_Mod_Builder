#ifndef STRING_TRAITS_H
#define STRING_TRAITS_H

#include "types.h"
#include <string>

namespace saklib
{
    /*
    String_Traits<T>
    ====================================================================================================
    Class which contains unique functions for each type that is specialised. By default there is nothing
    of interest.

    */
    template <typename T>
    struct String_Traits
    {
        static bool const is_specialised{ false };
        static bool const is_specialized{ false };

        static std::string to_string(T const& value)    { assert(is_specialised); return std::string(); }
        static T from_string(std::string const& value)  { assert(is_specialised); return T(); }
    };

    /*
    Should probably specialise for all built in integer and float types, without typedefs

    bool

    char?

    short
    int
    long
    long long

    unsigned short
    unsigned int
    unsigned long
    unsinged long long

    float
    double
    long double

    */

    /*
    String_Traits<bool>
    ====================================================================================================
    */
    template <>
    struct String_Traits<bool>
    {
        static bool const is_specialised{ true };
        static bool const is_specialized{ true };

        static std::string to_string(bool value)                        { return std::to_string(int(value)); }
        static bool from_string(std::string const& value)               { return std::stoi(value) > 0 ? true : false; }
    };


    /*
    String_Traits<int>
    ====================================================================================================
    */
    template <>
    struct String_Traits<int>
    {
        static bool const is_specialised{ true };
        static bool const is_specialized{ true };

        static std::string to_string(int value)                         { return std::to_string(value); }
        static int from_string(std::string const& value)                { return std::stoi(value); }
    };

    /*
    String_Traits<long>
    ====================================================================================================
    */
    template <>
    struct String_Traits<long>
    {
        static bool const is_specialised{ true };
        static bool const is_specialized{ true };

        static std::string to_string(long value)                        { return std::to_string(value); }
        static long from_string(std::string const& value)               { return std::stol(value); }
    };


    /*
    String_Traits<long long>
    ====================================================================================================
    */
    template <>
    struct String_Traits<long long>
    {
        static bool const is_specialised{ true };
        static bool const is_specialized{ true };

        static std::string to_string(long long value)                   { return std::to_string(value); }
        static long long from_string(std::string const& value)          { return std::stoll(value); }
    };


    /*
    String_Traits<unsigned int>
    ====================================================================================================
    */
    template <>
    struct String_Traits<unsigned int>
    {
        static bool const is_specialised{ true };
        static bool const is_specialized{ true };

        static std::string to_string(unsigned int value)                 { return std::to_string(value); }
        static unsigned int from_string(std::string const& value)        { return static_cast<unsigned int>(std::stoul(value)); }
    };

    /*
    String_Traits<unsigned long>
    ====================================================================================================
    */
    template <>
    struct String_Traits<unsigned long>
    {
        static bool const is_specialised{ true };
        static bool const is_specialized{ true };

        static std::string to_string(unsigned long value)                { return std::to_string(value); }
        static unsigned long from_string(std::string const& value)       { return std::stoul(value); }
    };


    /*
    String_Traits<unsigned long long>
    ====================================================================================================
    */
    template <>
    struct String_Traits<unsigned long long>
    {
        static bool const is_specialised{ true };
        static bool const is_specialized{ true };

        static std::string to_string(unsigned long long value)          { return std::to_string(value); }
        static unsigned long long from_string(std::string const& value) { return std::stoull(value); }
    };


    /*
    String_Traits<float>
    ====================================================================================================
    */
    template <>
    struct String_Traits<float>
    {
        static bool const is_specialised{ true };
        static bool const is_specialized{ true };

        static std::string to_string(float value)                       { return std::to_string(value); }
        static float from_string(std::string const& value)              { return std::stof(value); }
    };

    /*
    String_Traits<double>
    ====================================================================================================
    */
    template <>
    struct String_Traits<double>
    {
        static bool const is_specialised{ true };
        static bool const is_specialized{ true };

        static std::string to_string(double value)                      { return std::to_string(value); }
        static double from_string(std::string const& value)             { return std::stod(value); }
    };

    /*
    String_Traits<long double>
    ====================================================================================================
    */
    template <>
    struct String_Traits<long double>
    {
        static bool const is_specialised{ true };
        static bool const is_specialized{ true };

        static std::string to_string(long double value)                 { return std::to_string(value); }
        static long double from_string(std::string const& value)        { return std::stold(value); }
    };


    /*
    String_Traits<std::string>
    ====================================================================================================
    */
    template <>
    struct String_Traits<std::string>
    {
        static bool const is_specialised{ true };
        static bool const is_specialized{ true };

        static std::string to_string(std::string const& value)          { return value; }
        static std::string from_string(std::string const& value)        { return value; }
    };


    /*
    String_Traits<Path>
    ====================================================================================================
    */
    template <>
    struct String_Traits<Path>
    {
        static bool const is_specialised{ true };
        static bool const is_specialized{ true };

        static std::string to_string(Path const& value)   { return value.string(); }
        static Path from_string(std::string const& value) { return Path(value); }
    };


    /*
    String_Traits<ElementID>
    ====================================================================================================
    */
    template <>
    struct String_Traits<ElementID>
    {
        static bool const is_specialised{ true };
        static bool const is_specialized{ true };

        static std::string to_string(ElementID const& value)   { return std::to_string(value.value());; }
        static ElementID from_string(std::string const& value) { return ElementID(std::stoi(value)); }
    };


    /*
    String_Traits<std::vector<T>>
    ====================================================================================================
    */
    template <typename T>
    struct String_Traits<std::vector<T>>
    {
        static bool const is_specialised{ true };
        static bool const is_specialized{ true };

        static std::string to_string(std::vector<T> const& vector)
        {
            std::string result{"[ "};
            if (!vector.empty())
            {
                for (std::size_t index = 0, end = vector.size(); index < end; ++index)
                {
                    result.push_back('"');
                    result += String_Traits<T>::to_string(vector.at(index));
                    result.push_back('"');
                    if (index != end - 1)
                    {
                        result += ", ";
                    }
                }
            }

            result += " ]";
            return result;
        }
        static std::vector<T> from_string(std::string const& value)
        {
            std::vector<T> result{};

            assert(false);

            return result;
        }
    };


    /*
    Convenience functions
    ====================================================================================================
    */
    template <typename T>
    std::string to_string(T const& value)
    {
        assert(String_Traits<T>::is_specialised);
        return String_Traits<T>::to_string(value);
    }

    template <typename T>
    T from_string(std::string const& value)
    {
        assert(String_Traits<T>::is_specialised);
        return String_Traits<T>::from_string(value);
    }

} // namespace saklib
#endif // STRING_TRAITS_H

