#ifndef DCLIB_META_POWER_HPP
#define DCLIB_META_POWER_HPP

#include <type_traits>

namespace dclib
{
  namespace meta
  {
    namespace mf
    {
      // Value of an int of N to power P
      template <typename I, std::size_t N, std::size_t P>
      struct power : public std::integral_constant<I, N * power<I,N,P-1>::value> {};

      template <typename I, std::size_t N>
      struct power<I,N,0> : public std::integral_constant<I, 1> {};

      template <std::size_t P>
      using power_2 = power<std::size_t, 2u, P>;

    } // namespace mf
  } // namespace meta
} // namespace dclib

#endif // DCLIB_META_POWER_HPP
