#ifndef SAK_SECTION_OUTLINER_ITEMS_FWD_HPP
#define SAK_SECTION_OUTLINER_ITEMS_FWD_HPP

#ifndef SAK_SECTION_DATA_FWD_HPP
#include "section_data_fwd.hpp"
#endif

namespace sak
{
  template <typename T>
  class Section_Outliner_Header_Item;

  template <typename T>
  class Section_Outliner_Item;

  using File_Outliner_Header_Item = Section_Outliner_Header_Item<File_Data>;
  using File_Outliner_Item = Section_Outliner_Item<File_Data>;

  using Texture_Outliner_Header_Item = Section_Outliner_Header_Item<Texture_Data>;
  using Texture_Outliner_Item = Section_Outliner_Item<Texture_Data>;

}

#endif // SAK_SECTION_OUTLINER_ITEMS_FWD_HPP
