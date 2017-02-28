#ifndef SAK_SHARED_OBJECT_HPP
#define SAK_SHARED_OBJECT_HPP

#include "fwd/object.hpp"
#include <dclib/ct/object.hpp>
#include <dclib/ct/member.hpp>

#include <QString>

namespace sak
{
  namespace shared
  {
    namespace mf
    {

      //---------------------------------------------------------------------------
      // Metafunction object_member<T,I>
      //---------------------------------------------------------------------------
      // For a given object type retrieve the member type at the supplied index.
      template <typename T, std::size_t I>
      using object_member_t = typename object_member<T,I>::type;
    } // namespace mf
  }
}

#endif // SAK_SHARED_OBJECT_HPP
