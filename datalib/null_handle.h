#ifndef NULL_HANDLE_H
#define NULL_HANDLE_H

#include <cstddef>
#include <type_traits>

namespace datalib
{
    class Null_Handle_Type
    {
    public:
        using underlying_type = std::size_t;

        static_assert(std::is_integral<underlying_type>::value
                      && std::is_unsigned<underlying_type>::value,
                      "Supplied underlying_type must be an unsigned integral type.");

        Null_Handle_Type() = default;

        static underlying_type const value{0};
    };

    // constexpr
    inline Null_Handle_Type null_handle()                           { return Null_Handle_Type(); }

    // constexpr
    inline Null_Handle_Type::underlying_type null_handle_value()    { return Null_Handle_Type::value; }

} // namespace datalib

#endif // NULL_HANDLE_H

