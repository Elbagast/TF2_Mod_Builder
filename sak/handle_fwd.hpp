#ifndef SAK_HANDLE_FWD_HPP
#define SAK_HANDLE_FWD_HPP

#ifndef SAK_SECTION_DATA_FWD_HPP
#include "section_data_fwd.hpp"
#endif

namespace sak
{
  template <typename T>
  class Handle;

  using File_Handle = Handle<File_Data>;
  using Texture_Handle = Handle<Texture_Data>;
}

#endif // SAK_HANDLE_FWD_HPP
