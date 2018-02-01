#ifndef SAK_XML_TRAITS_HPP
#define SAK_XML_TRAITS_HPP

#ifndef SAK_XML_TRAITS_FWD_HPP
#include "xml_traits_fwd.hpp"
#endif

#ifndef SAK_PROJECT_DATA_FWD_HPP
#include "project_data_fwd.hpp"
#endif

#ifndef SAK_SECTION_DATA_MANAGER_FWD_HPP
#include "section_data_manager_fwd.hpp"
#endif

#ifndef SAK_SECTION_DATA_FWD_HPP
#include "section_data_fwd.hpp"
#endif

class QString;
class QXmlStreamWriter;
class QXmlStreamReader;

namespace sak
{
  //---------------------------------------------------------------------------
  // Xml_Traits<T>
  //---------------------------------------------------------------------------
  // For each class that you want to save or load in an xml file, supply a
  // specialised version of the class with to_stream and from_stream functions.
  /*
  template <typename T>
  class Xml_Traits
  {
  public:
    using Data_Type = T;

    static QXmlStreamWriter& to_stream(QXmlStreamWriter& a_stream, Data_Type const& a_data);
    static QXmlStreamReader& from_stream(QXmlStreamReader& a_stream, Data_Type& a_data);
  };
  */

  //---------------------------------------------------------------------------
  // Xml_Traits<Project_Data>
  //---------------------------------------------------------------------------

  template <>
  class Xml_Traits<Project_Data>
  {
  public:
    static QXmlStreamWriter& to_stream(QXmlStreamWriter& a_stream, Project_Data const& a_data);
    static QXmlStreamReader& from_stream(QXmlStreamReader& a_stream, Project_Data& a_data);
  };


  //---------------------------------------------------------------------------
  // Xml_Traits<Section_Data_Manager<T>>
  //---------------------------------------------------------------------------

  // Have to redirect if we want to hide a partial template specialisation...
  namespace internal
  {
    template <typename T>
    class Xml_Traits_Section_Data_Manager
    {
    public:
      static QXmlStreamWriter& to_stream(QXmlStreamWriter& a_stream, Section_Data_Manager<T> const& a_data);
      static QXmlStreamReader& from_stream(QXmlStreamReader& a_stream, Section_Data_Manager<T>& a_data);
    };
  }

  template <typename T>
  class Xml_Traits<Section_Data_Manager<T>>
  {
  public:
    static QXmlStreamWriter& to_stream(QXmlStreamWriter& a_stream, Section_Data_Manager<T> const& a_data)
    {
      return internal::Xml_Traits_Section_Data_Manager<T>::to_stream(a_stream, a_data);
    }
    static QXmlStreamReader& from_stream(QXmlStreamReader& a_stream, Section_Data_Manager<T>& a_data)
    {
      return internal::Xml_Traits_Section_Data_Manager<T>::from_stream(a_stream, a_data);
    }
  };

  //---------------------------------------------------------------------------
  // Xml_Traits<Section_Data<T>>
  //---------------------------------------------------------------------------

  // Have to redirect if we want to hide a partial template specialisation...
  namespace internal
  {
    template <typename T>
    class Xml_Traits_Section_Data
    {
    public:
      static QXmlStreamWriter& to_stream(QXmlStreamWriter& a_stream, Section_Data<T> const& a_data);
      static QXmlStreamReader& from_stream(QXmlStreamReader& a_stream, Section_Data<T>& a_data);
    };

  }

  template <typename T>
  class Xml_Traits<Section_Data<T>>
  {
  public:
    static QXmlStreamWriter& to_stream(QXmlStreamWriter& a_stream, Section_Data<T> const& a_data)
    {
      return internal::Xml_Traits_Section_Data<T>::to_stream(a_stream, a_data);
    }
    static QXmlStreamReader& from_stream(QXmlStreamReader& a_stream, Section_Data<T>& a_data)
    {
      return internal::Xml_Traits_Section_Data<T>::from_stream(a_stream, a_data);
    }
  };


  //---------------------------------------------------------------------------
  // Xml_Traits<QString>
  //---------------------------------------------------------------------------

  template <>
  class Xml_Traits<QString>
  {
  public:
    static QXmlStreamWriter& to_stream(QXmlStreamWriter& a_stream, QString const& a_data);
    static QXmlStreamReader& from_stream(QXmlStreamReader& a_stream, QString& a_data);
  };

}

#endif // SAK_XML_TRAITS_HPP
