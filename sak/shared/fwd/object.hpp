#ifndef SAK_SHARED_FWD_OBJECT_HPP
#define SAK_SHARED_FWD_OBJECT_HPP

//#include <flamingo/fwd/data_class.hpp>
//#include <dclib/ct/fwd/member.hpp>
//#include <dclib/litype/string.hpp>
class QString;

namespace sak
{
  namespace shared
  {
    template <typename S_Type, typename...T_Members>
    class typenamed_data_class;
  }

  namespace file
  {
    class object;
  }

  namespace texture
  {
    class object;
  }
}

#endif // SAK_SHARED_FWD_OBJECT_HPP
