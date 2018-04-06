#ifndef SAK_DATA_FWD_HPP
#define SAK_DATA_FWD_HPP

#ifndef INCLUDE_STD_CSTDDEF
#define INCLUDE_STD_CSTDDEF
#include <cstddef>
#endif

namespace sak
{
  template <typename T_Class_Def>
  class Data;

  template <typename T>
  class Data_Size;

  template <std::size_t Index, typename T>
  class Data_Member_Def;

  template <std::size_t Index, typename T>
  class Data_Member_Name;

  template <std::size_t Index, typename T>
  class Data_Member_Value;
}

#endif // SAK_DATA_FWD_HPP
