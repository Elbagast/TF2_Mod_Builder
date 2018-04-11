#ifndef SAK_NUMERIC_FWD_HPP
#define SAK_NUMERIC_FWD_HPP

// Standard Headers
//============================================================
#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <cstdint>
#endif

namespace sak
{
  using Bool = bool;

  using Int8 = std::int8_t;
  using Int16 = std::int16_t;
  using Int32 = std::int32_t;
  using Int64 = std::int64_t;

  using Uint8 = std::uint8_t;
  using Uint16 = std::uint16_t;
  using Uint32 = std::uint32_t;
  using Uint64 = std::uint64_t;

  using Float32 = float;
  using Float64 = double;
}

#endif // SAK_NUMERIC_FWD_HPP
