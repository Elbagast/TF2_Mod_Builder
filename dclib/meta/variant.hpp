#ifndef DCLIB_META_VARIANT_HPP
#define DCLIB_META_VARIANT_HPP

#include "typelist.hpp"
#include <boost/variant.hpp>

namespace dclib
{
  namespace meta
  {
    namespace mf
    {
      template <typename List>
      struct to_variant;

      template <typename... Args>
      struct to_variant<meta::typelist<Args...>>
      {
        using type = boost::variant<Args...>;
      };

      template <typename List>
      using to_variant_t = typename to_variant<List>::type;
    } // namespace mf
  } // namespace meta
} // namespace dclib

#endif // DCLIB_META_VARIANT_HPP
