#ifndef SAK_PROJECT_SIGNALBOX_HPP
#define SAK_PROJECT_SIGNALBOX_HPP

#include "fwd/signalbox.hpp"
#include <sak/shared/signalbox.hpp>

namespace sak
{
  namespace project
  {
    namespace abstract
    {
      class signalbox :
          public file::abstract::signalbox
      {
      public:
        ~signalbox() override = default;
      };
    }
  }
}

#endif // SAK_PROJECT_SIGNALBOX_HPP
