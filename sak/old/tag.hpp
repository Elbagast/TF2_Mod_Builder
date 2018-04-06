#ifndef SAK_TAG_HPP
#define SAK_TAG_HPP

#ifndef SAK_TAG_FWD_HPP
#include "tag_fwd.hpp"
#endif

namespace sak
{
  template <std::size_t I>
  class Index_Tag
  {
  public:
    Index_Tag() = default;
    ~Index_Tag() = default;

    Index_Tag(Index_Tag const&) = default;
    Index_Tag& operator=(Index_Tag const&) = default;

    Index_Tag(Index_Tag &&) = default;
    Index_Tag& operator=(Index_Tag &&) = default;
  };

  template <typename T_Class_Def>
  class Tag
  {
  public:
    Tag() = default;
    ~Tag() = default;

    Tag(Tag const&) = default;
    Tag& operator=(Tag const&) = default;

    Tag(Tag &&) = default;
    Tag& operator=(Tag &&) = default;
  };
}

#endif // SAK_TAG_HPP
