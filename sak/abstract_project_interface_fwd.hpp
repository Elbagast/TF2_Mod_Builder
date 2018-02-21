#ifndef SAK_ABSTRACT_PROJECT_INTERFACE_FWD_HPP
#define SAK_ABSTRACT_PROJECT_INTERFACE_FWD_HPP

#ifndef SAK_CLASS_DEFINITIONS_FWD_HPP
#include "class_definitions_fwd.hpp"
#endif

//#ifndef INCLUDE_STD_CSTDDEF
//#define INCLUDE_STD_CSTDDEF
//#include <cstddef>
//#endif

namespace sak
{
  template <typename T, typename...Args>
  class Abstract_Project_Interface_Imp;

  using Abstract_Project_Interface = Abstract_Project_Interface_Imp<File_Definition,Texture_Definition, Material_Definition>;
}

#endif // SAK_ABSTRACT_PROJECT_INTERFACE_FWD_HPP
