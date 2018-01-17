#include "section_xml_traits.hpp"

#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>
#include <qtlib/string_conversion.hpp>

#include "section_data.hpp"

namespace sak
{
  namespace
  {
    template <typename T>
    struct do_loop_to_stream
    {
      using Data_Type = T;
      using Typestring = typename Data_Type::Typestring;
      using Typestring_Type = std::basic_string<typename Typestring::char_type>;

      template <std::size_t Index, std::size_t End = Section_Data_Size_v<Data_Type>>
      struct do_loop
      {
        using member_type = Section_Data_Member_Type<Index, Data_Type>;
        using member_name_type = Section_Data_Member_Name_Type<Index, Data_Type>;

        using name_string_type = std::basic_string<typename member_name_type::char_type>;

        static_assert(flamingo::litype::is_string<member_name_type>::value, "not a flamingo::litype::string<>");

        void operator()(QXmlStreamWriter& a_stream, Data_Type const& a_data)
        {
          // This can potentially get farmed out to elsewhere, allowing multiline versions
          auto l_name = qtlib::To_QString<name_string_type>()(member_name_type::data());
          auto l_data = qtlib::To_QString<member_type>()(a_data.cmember_at<Index>());
          a_stream.writeTextElement(l_name, l_data);
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
        a_stream.writeStartElement(qtlib::To_QString<Typestring_Type>()(Typestring::data()));

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
      using Typestring_Type = std::basic_string<typename Typestring::char_type>;

      template <std::size_t Index, std::size_t End = Section_Data_Size_v<Data_Type>>
      struct do_loop
      {
        using member_type = Section_Data_Member_Type<Index, Data_Type>;
        using member_name_type = Section_Data_Member_Name_Type<Index, Data_Type>;

        using name_string_type = std::basic_string<typename member_name_type::char_type>;

        void operator()(QXmlStreamReader& a_stream, Data_Type& a_data)
        {
          if (a_stream.readNextStartElement()
              && a_stream.name().toString() == qtlib::To_QString<name_string_type>()(member_name_type::data()))
          {
            qDebug() << "tokenstring = " << a_stream.tokenString() << a_stream.name().toString();

            // read the data as a string
            auto l_data_qstring = a_stream.readElementText();
            // convert the data
            auto l_data = qtlib::From_QString<member_type>()(l_data_qstring);
            // write it
            a_data.member_at<Index>() = l_data;

            qDebug() << "tokenstring = " << a_stream.tokenString() << a_stream.name().toString();
            // apparently we jump to the end element when we use readElementText()
          }
          else
          {
            // bad member name...
            qDebug() << "Bad member name...";
            qDebug() << "Last element: " << a_stream.qualifiedName().toString();
          }
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
            && a_stream.name().toString() == qtlib::To_QString<Typestring_Type>()(Typestring::data()))
        {
          qDebug() << "tokenstring = " << a_stream.tokenString() << a_stream.name().toString();
          do_loop<0>()(a_stream, a_data);
          // close the element
          //a_stream.readNext();

          qDebug() << "tokenstring = " << a_stream.tokenString() << a_stream.name().toString();
          if (a_stream.readNext() != QXmlStreamReader::Characters)
          {
            // Bad file structure
            qDebug() << "Didn't find Characters";
          }
          qDebug() << "tokenstring = " << a_stream.tokenString() << a_stream.name().toString();
          if (a_stream.readNext() != QXmlStreamReader::EndElement)
          {
            // Bad file structure
            qDebug() << "Didn't find EndElement";
          }
          qDebug() << "tokenstring = " << a_stream.tokenString() << a_stream.name().toString();
        }
        else
        {
          // bad type...
          qDebug() << "Didn't find " << qtlib::To_QString<Typestring_Type>()(Typestring::data());
          qDebug() << "Last element: " << a_stream.qualifiedName().toString();
        }
      }
    };
  }
}


template <typename T>
void sak::Section_Xml_Traits<T>::to_stream(QXmlStreamWriter& a_stream, Data_Type const& a_data)
{
  do_loop_to_stream<T>()(a_stream, a_data);
}

template <typename T>
void sak::Section_Xml_Traits<T>::from_stream(QXmlStreamReader& a_stream, Data_Type& a_data)
{
  do_loop_from_stream<T>()(a_stream, a_data);
}



// Forced Instantiations
//============================================================
template sak::File_Xml_Traits;
template sak::Texture_Xml_Traits;
