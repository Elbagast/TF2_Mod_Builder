#ifndef SAK_ABSTRACT_SECTION_SIGNALBOX_FWD_HPP
#define SAK_ABSTRACT_SECTION_SIGNALBOX_FWD_HPP

#ifndef SAK_SECTION_DATA_FWD_HPP
#include "section_data_fwd.hpp"
#endif

namespace sak
{
  template <typename T>
  class Abstract_Section_Signalbox;

  using Abstract_File_Signalbox = Abstract_Section_Signalbox<File_Data>;
  using Abstract_Texture_Signalbox = Abstract_Section_Signalbox<Texture_Data>;
}

#endif // SAK_ABSTRACT_SECTION_SIGNALBOX_FWD_HPP
