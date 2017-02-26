#ifndef SAK_SHARED_FWD_COMMAND_HPP
#define SAK_SHARED_FWD_COMMAND_HPP

#include <cstddef>

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
} // namespace sak

#endif // SAK_SHARED_FWD_COMMAND_HPP
