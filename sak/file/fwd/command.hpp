#ifndef SAK_FILE_FWD_COMMAND_HPP
#define SAK_FILE_FWD_COMMAND_HPP

#include <sak/shared/fwd/command.hpp>
#include "object.hpp"

namespace sak
{
  namespace file
  {
    //---------------------------------------------------------------------------
    // command_assign<T,Index>
    //---------------------------------------------------------------------------
    // Class that derives from generic::command that wraps the assignement of a
    // member's data.

    template <std::size_t Index>
    using command_assign = shared::command_assign<object,Index>;

  } // namespace rt
} // namespace dclib

#endif // SAK_FILE_FWD_COMMAND_HPP
