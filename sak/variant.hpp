#ifndef SAK_VARIANT_HPP
#define SAK_VARIANT_HPP

#ifndef SAK_VARIANT_FWD_HPP
#include "variant_fwd.hpp"
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Variant
  //---------------------------------------------------------------------------
  // Class that can contain one of any of the values for Entity data members or
  // parts of those members, or may contain no value. A Variant that contains
  // no value is invalid.

  class Variant
  {
  public:
    Variant() = default;
  };
}

#endif // SAK_VARIANT_HPP
