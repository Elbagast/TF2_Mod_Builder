#ifndef SAK_SECTION_XML_TRAITS_FWD_HPP
#define SAK_SECTION_XML_TRAITS_FWD_HPP

#ifndef SAK_SECTION_DATA_FWD_HPP
#include "section_data_fwd.hpp"
#endif

namespace sak
{
  template <typename T>
  class Section_Xml_Traits;

  using File_Xml_Traits = Section_Xml_Traits<File_Data>;
  using Texture_Xml_Traits = Section_Xml_Traits<Texture_Data>;

}

#endif // SAK_SECTION_XML_TRAITS_FWD_HPP
