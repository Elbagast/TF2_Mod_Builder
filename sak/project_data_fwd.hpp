#ifndef SAK_PROJECT_DATA_FWD_HPP
#define SAK_PROJECT_DATA_FWD_HPP

#ifndef SAK_CLASS_DEFINITIONS_FWD_HPP
#include "class_definitions_fwd.hpp"
#endif

namespace sak
{
  template <typename T, typename...Args>
  class Project_Chained_Data;

  using Project_Data = Project_Chained_Data<File_Definition,Texture_Definition>;
} // namespace sak

#endif // SAK_PROJECT_DATA_FWD_HPP
