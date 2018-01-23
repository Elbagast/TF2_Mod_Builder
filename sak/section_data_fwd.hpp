#ifndef SAK_SECTION_DATA_FWD_HPP
#define SAK_SECTION_DATA_FWD_HPP

#ifndef INCLUDE_STD_CSTDDEF
#define INCLUDE_STD_CSTDDEF
#include <cstddef>
#endif

namespace sak
{
  template <typename T>
  class Section_Data;

  template <typename T>
  class Section_Data_Size;

  template <std::size_t Index, typename T>
  class Section_Data_Member;

  template <std::size_t Index, typename T>
  class Section_Data_Member_Value;

  template <std::size_t Index, typename T>
  class Section_Data_Member_Name;

  template <typename T>
  class Section_Data_Member_Typelist;

  template <typename T>
  class Section_Data_Member_Value_Typelist;

  template <typename T>
  class Section_Data_Member_Name_Typelist;

  template <typename T>
  class Section_Data_Member_Value_Variant;

  class File_Data_Traits;
  using File_Data = Section_Data<File_Data_Traits>;

  class Texture_Data_Traits;
  using Texture_Data = Section_Data<Texture_Data_Traits>;

}

#endif // SAK_SECTION_DATA_FWD_HPP
