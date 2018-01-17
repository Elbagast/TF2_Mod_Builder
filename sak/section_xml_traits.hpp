#ifndef SAK_SECTION_XML_TRAITS_HPP
#define SAK_SECTION_XML_TRAITS_HPP

#ifndef SAK_SECTION_XML_TRAITS_FWD_HPP
#include "section_xml_traits_fwd.hpp"
#endif

class QXmlStreamWriter;
class QXmlStreamReader;

namespace sak
{
  template <typename T>
  class Section_Xml_Traits
  {
  public:
    using Data_Type = T;

    static void to_stream(QXmlStreamWriter& a_stream, Data_Type const& a_data);
    static void from_stream(QXmlStreamReader& a_stream, Data_Type& a_data);
  };
} // namespace sak

#endif // SAK_SECTION_XML_TRAITS_HPP
