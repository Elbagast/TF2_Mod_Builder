#ifndef SAK_SECTION_DATA_MANAGER_FWD_HPP
#define SAK_SECTION_DATA_MANAGER_FWD_HPP

#ifndef SAK_SECTION_DATA_FWD_HPP
#include "section_data_fwd.hpp"
#endif

namespace sak
{
  template <typename T>
  class Section_Data_Manager;


  using File_Data_Manager = Section_Data_Manager<File_Data>;

  using Texture_Data_Manager = Section_Data_Manager<Texture_Data>;

} // namespace sak

#endif // SAK_SECTION_DATA_MANAGER_FWD_HPP
