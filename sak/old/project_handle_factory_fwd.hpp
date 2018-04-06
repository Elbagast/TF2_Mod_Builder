#ifndef SAK_PROJECT_HANDLE_FACTORY_FWD_HPP
#define SAK_PROJECT_HANDLE_FACTORY_FWD_HPP

#ifndef SAK_CLASS_DEFINITIONS_FWD_HPP
#include "class_definitions_fwd.hpp"
#endif

namespace sak
{
  template <typename T, typename...Args>
  class Project_Handle_Factory_Imp;

  using Project_Handle_Factory = Project_Handle_Factory_Imp<File_Definition,Texture_Definition,Material_Definition>;
} // namespace sak

#endif // SAK_PROJECT_HANDLE_FACTORY_FWD_HPP
