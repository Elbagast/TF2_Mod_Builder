#ifndef SAK_TAG_HPP
#define SAK_TAG_HPP

#ifndef SAK_TAG_FWD_HPP
#include "tag_fwd.hpp"
#endif

namespace sak
{
  template <std::size_t I>
  class Index_Tag {};

  template <typename T_Class_Def>
  class Tag {};

}

#endif // SAK_TAG_HPP
