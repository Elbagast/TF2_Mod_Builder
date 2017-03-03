#ifndef SAK_SHARED_FWD_DATA_MANAGER_HPP
#define SAK_SHARED_FWD_DATA_MANAGER_HPP

#include "object.hpp"

namespace sak
{
  namespace shared
  {
    //---------------------------------------------------------------------------
    // sak::shared::data_manager<T>
    //---------------------------------------------------------------------------
    // Splitting out the repeated backend management system for project...

    template <typename T>
    class data_manager;
  }

  namespace file
  {
    using data_manager = shared::data_manager<file::object>;
  }

  namespace texture
  {
    using data_manager = shared::data_manager<texture::object>;
  }
}

#endif // SAK_SHARED_FWD_DATA_MANAGER_HPP
