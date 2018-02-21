#ifndef SAK_PROJECT_INTERFACE_FWD_HPP
#define SAK_PROJECT_INTERFACE_FWD_HPP

#ifndef SAK_CLASS_DEFINITIONS_FWD_HPP
#include "class_definitions_fwd.hpp"
#endif

namespace sak
{
  template <typename T, typename...Args>
  class Project_Interface_Imp;

  using Project_Interface = Project_Interface_Imp<File_Definition,Texture_Definition, Material_Definition>;
}

#endif // SAK_PROJECT_INTERFACE_FWD_HPP
