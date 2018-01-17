#ifndef SAK_SECTION_COMMAND_FWD_HPP
#define SAK_SECTION_COMMAND_FWD_HPP

#ifndef INCLUDE_STD_CSTDDEF
#define INCLUDE_STD_CSTDDEF
#include <cstddef>
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Abstract_Signalling_Command<T>
  //---------------------------------------------------------------------------
  // Base class to contain shared typedefs and data members for commands on
  // objects via handles.
  template <typename T>
  class Abstract_Signalling_Command;

  //---------------------------------------------------------------------------
  // Command_Assign<T,Index>
  //---------------------------------------------------------------------------
  // Class that derives from generic::command that wraps the assignement of a
  // member's data.

  template <std::size_t Index, typename T>
  class Command_Assign;

  //---------------------------------------------------------------------------
  // Command_Added<T>
  //---------------------------------------------------------------------------
  // Class that derives from generic::command that wraps the addition of an
  // object to the project.

  template <typename T>
  class Command_Added;

  //---------------------------------------------------------------------------
  // Command_Removed<T>
  //---------------------------------------------------------------------------
  // Class that derives from generic::command that wraps the addition of an
  // object to the project.

  template <typename T>
  class Command_Removed;

} // namespace sak


#endif // SAK_SECTION_COMMAND_FWD_HPP
