#ifndef SAK_SHARED_FWD_COMMAND_HPP
#define SAK_SHARED_FWD_COMMAND_HPP

#include <cstddef>
#include "object.hpp"

namespace sak
{
  namespace shared
  {
    //---------------------------------------------------------------------------
    // command_assign<T,Index>
    //---------------------------------------------------------------------------
    // Class that derives from generic::command that wraps the assignement of a
    // member's data.

    template <typename T, std::size_t Index>
    class command_assign;

  } // namespace shared

  namespace file
  {
    //---------------------------------------------------------------------------
    // command_assign<T,Index>
    //---------------------------------------------------------------------------
    // Class that derives from generic::command that wraps the assignement of a
    // member's data.

    template <std::size_t Index>
    using command_assign = shared::command_assign<object,Index>;

  } // namespace file
} // namespace sak

#endif // SAK_SHARED_FWD_COMMAND_HPP
