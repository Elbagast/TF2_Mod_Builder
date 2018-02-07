#ifndef SAK_PROJECT_SIGNALBOX_DATA_FWD_HPP
#define SAK_PROJECT_SIGNALBOX_DATA_FWD_HPP

#ifndef SAK_CLASS_DEFINITIONS_FWD_HPP
#include "class_definitions_fwd.hpp"
#endif

namespace sak
{
  template <typename T, typename...Args>
  class Project_Signalbox_Data_Shared_Imp;

  template <typename T_List, typename...Args>
  class Project_Signalbox_Data_Section_Imp;

  template <typename T, typename...Args>
  class Project_Signalbox_Data_Imp;

  using Project_Signalbox_Data = Project_Signalbox_Data_Imp<File_Definition,Texture_Definition,Material_Definition>;
} // namespace sak

#endif // SAK_PROJECT_SIGNALBOX_DATA_FWD_HPP
