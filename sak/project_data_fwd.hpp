#ifndef SAK_PROJECT_DATA_FWD_HPP
#define SAK_PROJECT_DATA_FWD_HPP

#ifndef SAK_SECTION_DATA_FWD_HPP
#include "section_data_fwd.hpp"
#endif

namespace sak
{
  class Project_Data;

  namespace v2
  {
    template <typename T, typename...Args>
    class Project_Chained_Data;

    using Project_Data = Project_Chained_Data<File_Data,Texture_Data>;
  }
} // namespace sak

#endif // SAK_PROJECT_DATA_FWD_HPP
