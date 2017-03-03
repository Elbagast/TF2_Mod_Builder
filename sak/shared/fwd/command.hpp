#ifndef SAK_SHARED_FWD_COMMAND_HPP
#define SAK_SHARED_FWD_COMMAND_HPP

#include <cstddef>
#include "object.hpp"
#include <generic/fwd/command.hpp>

namespace sak
{
  namespace shared
  {
    namespace abstract
    {
      using command = generic::abstract::Command;
      //---------------------------------------------------------------------------
      // abstract::command_assign<T>
      //---------------------------------------------------------------------------
      // Base class for commands for the assignment of member values. This class
      // captures the common details and allows us to hide the signaling methods.

      template <typename T>
      class signalling_command;
    }

    //---------------------------------------------------------------------------
    // command_assign<T,Index>
    //---------------------------------------------------------------------------
    // Class that derives from generic::command that wraps the assignement of a
    // member's data.

    template <typename T, std::size_t Index>
    class command_assign;

    //---------------------------------------------------------------------------
    // command_added<T>
    //---------------------------------------------------------------------------
    // Class that derives from generic::command that wraps the addition of an
    // object to the project.

    template <typename T>
    class command_added;

    //---------------------------------------------------------------------------
    // command_removed<T>
    //---------------------------------------------------------------------------
    // Class that derives from generic::command that wraps the addition of an
    // object to the project.

    template <typename T>
    class command_removed;


  } // namespace shared

  namespace file
  {
    template <std::size_t Index>
    using command_assign = shared::command_assign<object,Index>;

    using command_added = shared::command_added<object>;

    using command_removed = shared::command_removed<object>;

  } // namespace file

  namespace texture
  {
    template <std::size_t Index>
    using command_assign = shared::command_assign<object,Index>;

    using command_added = shared::command_added<object>;

    using command_removed = shared::command_removed<object>;

  } // namespace texture
} // namespace sak

#endif // SAK_SHARED_FWD_COMMAND_HPP
