#include "xml_traits.hpp"

//#include <gui/string_conversion.hpp>
#include "typestring_qstring.hpp"
#include "section_data_manager.hpp"
#include "section_data.hpp"
#include "project_data.hpp"
#include "handle.hpp"

#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>
#include <QString>
#include <QFile>

#include "exception.hpp"

//---------------------------------------------------------------------------
// Xml_Traits<Project_Data>
//---------------------------------------------------------------------------

QXmlStreamWriter& sak::Xml_Traits<sak::Project_Data>::to_stream(QXmlStreamWriter& a_stream, Project_Data const& a_data)
{
  a_stream.setAutoFormatting(true);
  a_stream.writeStartDocument();

  // start the element that contains all the data
  a_stream.writeStartElement("Project");

  Xml_Traits<File_Data_Manager>::to_stream(a_stream, *(a_data.cget_file_manager()));
  Xml_Traits<Texture_Data_Manager>::to_stream(a_stream, *(a_data.cget_texture_manager()));

  // end the element that contains all the data
  a_stream.writeEndElement();

  a_stream.writeEndDocument();

  return a_stream;
}

QXmlStreamReader& sak::Xml_Traits<sak::Project_Data>::from_stream(QXmlStreamReader& a_stream, Project_Data& a_data)
{
  // <Project>
  if (a_stream.readNextStartElement()
      && a_stream.name().toString() != "Project")
  {
    throw XML_Error(a_stream.lineNumber());
  }

  Xml_Traits<File_Data_Manager>::from_stream(a_stream, *(a_data.get_file_manager()));
  Xml_Traits<Texture_Data_Manager>::from_stream(a_stream, *(a_data.get_texture_manager()));

  //l_data->m_file_manager.from_xmlstream(l_stream);
  //l_data->m_texture_manager.from_xmlstream(l_stream);

  // </Project>
  qDebug() << "tokenstring = " << a_stream.tokenString() << a_stream.name().toString();
  if (a_stream.readNext() != QXmlStreamReader::Characters)
  {
    qDebug() << "Didn't find Project Characters";
    throw XML_Error(a_stream.lineNumber());
    // Bad file structure
  }
  qDebug() << "tokenstring = " << a_stream.tokenString() << a_stream.name().toString();
  if (a_stream.readNext() != QXmlStreamReader::EndElement)
  {
    qDebug() << "Didn't find Project EndElement";
    throw XML_Error(a_stream.lineNumber());
    // Bad file structure
  }
  qDebug() << "tokenstring = " << a_stream.tokenString() << a_stream.name().toString();

  return a_stream;
}



//---------------------------------------------------------------------------
// Xml_Traits<Section_Data_Manager<T>>
//---------------------------------------------------------------------------
namespace
{
  QString const c_count_title{ u8"Count" };
}

template <typename T>
//QXmlStreamWriter& sak::Xml_Traits<Section_Data_Manager<T>>::to_stream(QXmlStreamWriter& a_stream, Section_Data_Manager<T> const& a_data)
QXmlStreamWriter& sak::internal::Xml_Traits_Section_Data_Manager<T>::to_stream(QXmlStreamWriter& a_stream, Section_Data_Manager<T> const& a_data)
{
  using Data_Type = typename Section_Data_Manager<T>::Data_Type;

  // Write the start e.g. <Foos>
  // Use the plural of the typestring for the managed type.
  a_stream.writeStartElement(Typestring_QString<Data_Type::Typestring_Plural>::value());

  // Write a count of how many there should be
  a_stream.writeTextElement(c_count_title, QString::number(a_data.count()));

  // Get a copy of all the handles
  auto l_handles = a_data.get_all();

  // For each handle write it to the stream.
  for (auto const& l_handle : l_handles)
  {
    // Remember we have to dereference the handle to get to the data
    Xml_Traits<Data_Type>::to_stream(a_stream, *l_handle);
  }

  // Write the end e.g. </Foos>
  a_stream.writeEndElement();

  return a_stream;
}

template <typename T>
//QXmlStreamReader& sak::Xml_Traits<Section_Data_Manager<T>>::from_stream(QXmlStreamReader& a_stream, Section_Data_Manager<T>& a_data)
QXmlStreamReader& sak::internal::Xml_Traits_Section_Data_Manager<T>::from_stream(QXmlStreamReader& a_stream, Section_Data_Manager<T>& a_data)
{
  using Data_Type = typename Section_Data_Manager<T>::Data_Type;

  // Read the start e.g. <Foos>
  if (a_stream.readNextStartElement() && a_stream.name() != Typestring_QString<Data_Type::Typestring_Plural>::value())
  {
    // Bad file structure
    qDebug() << "Didn't find " << Typestring_QString<Data_Type::Typestring_Plural>::value() << "...";
    qDebug() << "Last element: " << a_stream.qualifiedName().toString();
    throw XML_Error(a_stream.lineNumber());
  }
  //qDebug() << "tokenstring = " << a_stream.tokenString() << a_stream.name().toString();
  //qDebug() << "Files:";
  //int l_count {0};

  // <Count>
  if (a_stream.readNextStartElement() && a_stream.name().toString() != c_count_title)
  {
    qDebug() << "Didn't find " << Typestring_QString<Data_Type::Typestring_Plural>::value() << " " << c_count_title;
    qDebug() << "Last element: " << a_stream.qualifiedName().toString();
    // file format error
    throw XML_Error(a_stream.lineNumber());
  }

  int l_count = a_stream.readElementText().toInt();

  // Data to build into
  Section_Data_Manager<T> l_data{};

  //m_handles.reserve(l_count); // only call outside members...and it could be made public
  // read the files
  for (int l_index = 0; l_index != l_count; ++l_index)
  {
    Data_Type l_object{};
    Xml_Traits<Data_Type>::from_stream(a_stream, l_object);

    // make a handle for this
    auto l_handle = l_data.make_emplace(std::move(l_object));
    assert(l_handle.id() != 0);
    assert(l_handle.get() != nullptr);
    assert(not_null(l_handle));
    // add it to the data
    l_data.added(l_handle);
  }
  // </Files>

  qDebug() << "tokenstring = " << a_stream.tokenString() << a_stream.name().toString();
  if (a_stream.readNext() != QXmlStreamReader::Characters)
  {
    // Bad file structure
    qDebug() << "Didn't find Characters";

    throw XML_Error(a_stream.lineNumber());
  }
  qDebug() << "tokenstring = " << a_stream.tokenString() << a_stream.name().toString();
  if (a_stream.readNext() != QXmlStreamReader::EndElement)
  {
    // Bad file structure
    throw XML_Error(a_stream.lineNumber());
  }
  qDebug() << "tokenstring = " << a_stream.tokenString() << a_stream.name().toString();

  // swap the data
  swap(a_data,l_data);
  assert(a_data.count() == static_cast<std::size_t>(l_count));

  return a_stream;
}




//---------------------------------------------------------------------------
// Xml_Traits<Section_Data<T>>
//---------------------------------------------------------------------------

namespace sak
{
  namespace
  {
    template <typename T>
    struct do_loop_to_stream
    {
      using Data_Type = T;
      using Typestring = typename Data_Type::Typestring;
     // using Typestring_Type = std::basic_string<typename Typestring::char_type>;

      template <std::size_t Index, std::size_t End = Section_Data_Size_v<Data_Type>>
      struct do_loop
      {
        using Member_Value_Type = Section_Data_Member_Value_Type<Index, Data_Type>;
        using Member_Name_Type = Section_Data_Member_Name_Type<Index, Data_Type>;

        static_assert(flamingo::litype::is_string<Member_Name_Type>::value, "not a flamingo::litype::string<>");

        void operator()(QXmlStreamWriter& a_stream, Data_Type const& a_data)
        {
          // Write the start e.g. <Foo>
          a_stream.writeStartElement(Typestring_QString<Member_Name_Type>::value());

          // Write the data. Each type needs an overload of this class.
          Xml_Traits<Member_Value_Type>::to_stream(a_stream, a_data.cmember_at<Index>());

          // Write the end e.g. </Foo>
          a_stream.writeEndElement();

          // Continue the loop
          do_loop<Index+1, End>()(a_stream, a_data);
        }
      };


      template <std::size_t End>
      struct do_loop<End, End>
      {
        void operator()(QXmlStreamWriter&, Data_Type const&)
        {
        }
      };


      void operator()(QXmlStreamWriter& a_stream, Data_Type const& a_data)
      {
        // start the element
        a_stream.writeStartElement(Typestring_QString<Typestring>::value());

        // Loop through the members.
        do_loop<0>()(a_stream, a_data);

        // end the element
        a_stream.writeEndElement();
      }
    };



    template <typename T>
    struct do_loop_from_stream
    {
      using Data_Type = T;
      using Typestring = typename Data_Type::Typestring;
      //using Typestring_Type = std::basic_string<typename Typestring::char_type>;

      template <std::size_t Index, std::size_t End = Section_Data_Size_v<Data_Type>>
      struct do_loop
      {
        using Member_Value_Type = Section_Data_Member_Value_Type<Index, Data_Type>;
        using Member_Name_Type = Section_Data_Member_Name_Type<Index, Data_Type>;


        void operator()(QXmlStreamReader& a_stream, Data_Type& a_data)
        {
          if (a_stream.readNextStartElement()
              && a_stream.name().toString() != Typestring_QString<Member_Name_Type>::value())
          {

            // bad member name...
            qDebug() << "Bad member name...";
            qDebug() << "Last element: " << a_stream.qualifiedName().toString();
            throw XML_Error(a_stream.lineNumber());
          }
          //qDebug() << "tokenstring = " << a_stream.tokenString() << a_stream.name().toString();


          Member_Value_Type l_data{};

          // This bit will go to hell for reference counted data....
          Xml_Traits<Member_Value_Type>::from_stream(a_stream, l_data);


          // read the data as a string
          //auto l_data_qstring = a_stream.readElementText();
          // convert the data
          //auto l_data = sak::gui::From_QString<Member_Value_Type>()(l_data_qstring);
          // write it
          a_data.member_at<Index>() = l_data;

          //qDebug() << "tokenstring = " << a_stream.tokenString() << a_stream.name().toString();
          // apparently we jump to the end element when we use readElementText()

          do_loop<Index+1,End>()(a_stream, a_data);
        }
      };


      template <std::size_t End>
      struct do_loop<End, End>
      {
        void operator()(QXmlStreamReader&, Data_Type&)
        {
        }
      };


      void operator()(QXmlStreamReader& a_stream, Data_Type& a_data)
      {
        // open the element and verify it's correct
        if (a_stream.readNextStartElement()
            && a_stream.name().toString() != Typestring_QString<Typestring>::value())
        {
          // bad type...
          qDebug() << "Didn't find " << Typestring_QString<Typestring>::value();
          qDebug() << "Last element: " << a_stream.qualifiedName().toString();
          throw XML_Error(a_stream.lineNumber());
        }
        //qDebug() << "tokenstring = " << a_stream.tokenString() << a_stream.name().toString();
        do_loop<0>()(a_stream, a_data);
        // close the element
        //a_stream.readNext();

        //qDebug() << "tokenstring = " << a_stream.tokenString() << a_stream.name().toString();
        if (a_stream.readNext() != QXmlStreamReader::Characters)
        {
          // Bad file structure
          qDebug() << "Didn't find Characters";
          throw XML_Error(a_stream.lineNumber());
        }
        //qDebug() << "tokenstring = " << a_stream.tokenString() << a_stream.name().toString();
        if (a_stream.readNext() != QXmlStreamReader::EndElement)
        {
          // Bad file structure
          qDebug() << "Didn't find EndElement";
          throw XML_Error(a_stream.lineNumber());
        }
        //qDebug() << "tokenstring = " << a_stream.tokenString() << a_stream.name().toString();
      }
    };
  }
}


template <typename T>
//QXmlStreamWriter& sak::Xml_Traits<Section_Data<T>>::to_stream(QXmlStreamWriter& a_stream, Section_Data<T> const& a_data)
QXmlStreamWriter& sak::internal::Xml_Traits_Section_Data<T>::to_stream(QXmlStreamWriter& a_stream, Section_Data<T> const& a_data)
{
  do_loop_to_stream<Section_Data<T>>()(a_stream, a_data);
  return a_stream;
}

template <typename T>
//QXmlStreamReader& sak::Xml_Traits<Section_Data<T>>::from_stream(QXmlStreamReader& a_stream, Section_Data<T>& a_data)
QXmlStreamReader& sak::internal::Xml_Traits_Section_Data<T>::from_stream(QXmlStreamReader& a_stream, Section_Data<T>& a_data)
{
  do_loop_from_stream<Section_Data<T>>()(a_stream, a_data);
  return a_stream;
}

//---------------------------------------------------------------------------
// Xml_Traits<QString>
//---------------------------------------------------------------------------

//template <>
QXmlStreamWriter& sak::Xml_Traits<QString>::to_stream(QXmlStreamWriter& a_stream, QString const& a_data)
{
  // QXmlStreamWriter automatically escapes forbidden characters and sequences.
  a_stream.writeCharacters(a_data);
  return a_stream;
}

//template <>
QXmlStreamReader& sak::Xml_Traits<QString>::from_stream(QXmlStreamReader& a_stream, QString& a_data)
{
  a_data = a_stream.readElementText();
  return a_stream;
}


// Forced Instantiations
//============================================================
//template sak::Xml_Traits<File_Data_Manager>;
//template sak::Xml_Traits<Texture_Data_Manager>;

template sak::internal::Xml_Traits_Section_Data_Manager<sak::File_Data>;
template sak::internal::Xml_Traits_Section_Data_Manager<sak::Texture_Data>;

// Forced Instantiations
//============================================================
//template sak::Xml_Traits<File_Data>;
//template sak::Xml_Traits<Texture_Data>;

template sak::internal::Xml_Traits_Section_Data<sak::File_Data_Traits>;
template sak::internal::Xml_Traits_Section_Data<sak::Texture_Data_Traits>;
