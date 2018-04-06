#ifndef SAK_SECTION_WIDGET_FWD_HPP
#define SAK_SECTION_WIDGET_FWD_HPP

#ifndef SAK_SECTION_DATA_FWD_HPP
#include "section_data_fwd.hpp"
#endif

#ifndef INCLUDE_STD_CSTDDEF
#define INCLUDE_STD_CSTDDEF
#include <cstddef>
#endif

namespace sak
{
  template <typename T>
  class Section_Widget;

  using File_Widget = Section_Widget<File_Data>;
  using Texture_Widget = Section_Widget<Texture_Data>;

}



#endif // SAK_SECTION_WIDGET_FWD_HPP
