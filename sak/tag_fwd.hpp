#ifndef SAK_TAG_FWD_HPP
#define SAK_TAG_FWD_HPP

#ifndef SAK_SECTION_DATA_FWD_HPP
#include "section_data_fwd.hpp"
#endif

namespace sak
{
  template <std::size_t Index>
  class Index_Tag;

  template <typename T>
  class Tag;

  using File_Tag = Tag<File_Data>;
  using Texture_Tag = Tag<Texture_Data>;
}

#endif // SAK_TAG_FWD_HPP
