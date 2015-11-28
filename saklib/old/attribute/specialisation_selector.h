#ifndef SAKLIB_SPECIALISATION_SELECTOR_H
#define SAKLIB_SPECIALISATION_SELECTOR_H

#include "../types.h"

namespace saklib
{
    using saklib::size_type;

    enum class Specialisation
    {
        none,
        integer_type,
        floating_point_type,
        colour_type,
        string_type,
        path_type,
        element_type
    };

    template <typename T>
    struct Specialisation_Selector
    {
        static Specialisation const value{Specialisation::none};
    };

#define SPECIALISATION_SELECTOR_SPECIALISATION(t_type, enum_value) \
    template<> struct Specialisation_Selector<t_type> { static Specialisation const value{Specialisation::enum_value}; };


    SPECIALISATION_SELECTOR_SPECIALISATION(int, integer_type)

    SPECIALISATION_SELECTOR_SPECIALISATION(double, floating_point_type)


} // namespace saklib

#endif // SAKLIB_SPECIALISATION_SELECTOR_H

