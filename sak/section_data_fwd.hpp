#ifndef SAK_SECTION_DATA_FWD_HPP
#define SAK_SECTION_DATA_FWD_HPP

#ifndef INCLUDE_STD_CSTDDEF
#define INCLUDE_STD_CSTDDEF
#include <cstddef>
#endif

namespace sak
{
  template <typename...T_Members>
  class Section_Data_Class;

  template <typename T>
  class Section_Data_Size;

  template <std::size_t Index, typename T>
  class Section_Data_Member;

  template <std::size_t Index, typename T>
  class Section_Data_Member_Name;

  template <typename T>
  class Section_Data_Member_Typelist;

  template <typename T>
  class Section_Data_Member_Name_Typelist;

  template <typename T>
  class Section_Data_Member_Variant;

  class File_Data_Traits;
  class File_Data;

  class Texture_Data_Traits;
  class Texture_Data;
}

#endif // SAK_SECTION_DATA_FWD_HPP
