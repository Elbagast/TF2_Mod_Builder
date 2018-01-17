#ifndef SAK_SECTION_INTERFACE_FWD_HPP
#define SAK_SECTION_INTERFACE_FWD_HPP

#ifndef SAK_SECTION_DATA_FWD_HPP
#include "section_data_fwd.hpp"
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Section_Interface<T>
  //---------------------------------------------------------------------------
  template <typename T>
  class Section_Interface;


  using File_Interface = Section_Interface<File_Data>;

  using Texture_Interface = Section_Interface<Texture_Data>;

}

#endif // SAK_SECTION_INTERFACE_FWD_HPP
