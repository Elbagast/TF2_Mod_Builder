#ifndef SAKLIB_INTERNAL_PROPERTY__FWD_H
#define SAKLIB_INTERNAL_PROPERTY__FWD_H

namespace saklib
{
    namespace internal
    {
        enum class Location;

        enum class Access;


        template <typename T>
        class Property_Name;

        template <typename F_Name, Location L, Access A, typename T, typename T_Arg, typename T_Return>
        class Property;

        namespace property_names
        {
            class Name;
            class Type;
        } // namespace property_names
    } // namespace internal
} // namespace saklib

#endif // SAKLIB_INTERNAL_PROPERTY__FWD_H

