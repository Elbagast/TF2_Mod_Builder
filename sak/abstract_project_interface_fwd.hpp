#ifndef SAK_ABSTRACT_PROJECT_INTERFACE_FWD_HPP
#define SAK_ABSTRACT_PROJECT_INTERFACE_FWD_HPP

#ifndef SAK_SECTION_DATA_FWD_HPP
#include "section_data_fwd.hpp"
#endif

namespace sak
{
  namespace v2
  {
    template <std::size_t Index, typename T>
    class Abstract_Section_Member_Interface;

    template <typename T>
    class Abstract_Section_Interface;

    class Abstract_Project_Save_Interface;

    class Abstract_Project_Path_Interface;

    class Abstract_Project_History_Interface;

    template <typename T, typename...Args>
    class Abstract_Project_Signalbox_Interface;

    template <typename T, typename...Args>
    class Abstract_Project_Chained_Interface;

    using Abstract_Project_Interface = Abstract_Project_Chained_Interface<File_Data,Texture_Data>;
  }
}

#endif // SAK_ABSTRACT_PROJECT_INTERFACE_FWD_HPP
