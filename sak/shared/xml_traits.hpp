#ifndef SAK_SHARED_XML_TRAITS_HPP
#define SAK_SHARED_XML_TRAITS_HPP

class QXmlStreamWriter;
class QXmlStreamReader;
#include "fwd/object.hpp"

namespace sak
{
  namespace shared
  {
    template <typename T>
    struct xml_traits
    {
      using object_type = T;
      static void to_stream(QXmlStreamWriter& a_stream, object_type const& a_object);
      static void from_stream(QXmlStreamReader& a_stream, object_type& a_object);
    };
  }

  namespace file
  {
    using xml_traits = shared::xml_traits<object>;
  }

  namespace texture
  {
    using xml_traits = shared::xml_traits<object>;
  }
}

#endif // SAK_SHARED_XML_TRAITS_HPP
