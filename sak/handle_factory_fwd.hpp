#ifndef SAK_HANDLE_FACTORY_FWD_HPP
#define SAK_HANDLE_FACTORY_FWD_HPP

#ifndef SAK_SECTION_DATA_FWD_HPP
#include "section_data_fwd.hpp"
#endif

namespace sak
{
  template <typename T>
  class Handle_Factory;

  using File_Handle_Factory = Handle_Factory<File_Data>;
  using Texture_Handle_Factory = Handle_Factory<Texture_Data>;

}

#endif // SAK_HANDLE_FACTORY_FWD_HPP
