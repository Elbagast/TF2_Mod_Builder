#ifndef SAK_TAG_FWD_HPP
#define SAK_TAG_FWD_HPP

#ifndef SAK_CLASS_DEFINITIONS_FWD_HPP
#include "class_definitions_fwd.hpp"
#endif

#ifndef INCLUDE_STD_CSTDDEF
#define INCLUDE_STD_CSTDDEF
#include <cstddef>
#endif

namespace sak
{
  template <std::size_t Index>
  class Index_Tag;

  template <typename T_Class_Def>
  class Tag;

  using File_Tag = Tag<File_Definition>;
  using Texture_Tag = Tag<Texture_Definition>;
  using Material_Tag = Tag<Material_Definition>;
}

#endif // SAK_TAG_FWD_HPP
