#include "xml_traits.hpp"

#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>
#include <qtlib/string_conversion.hpp>

#include "object.hpp"

namespace sak
{
  namespace shared
  {
    namespace
    {
      template <typename T>
      struct do_loop_to_stream
      {
        using object_type = T;
        using type_string_type = typename object_type::type_string_type;

        template <std::size_t Index, std::size_t End = object_type::size()>
        struct do_loop
        {
          using member_type = mf::object_member_t<object_type, Index>;
          using name_type = typename member_type::name_string_type;
          using value_type = typename member_type::value_type;

          void operator()(QXmlStreamWriter& a_stream, object_type const& a_object)
          {
            // This can potentially get farmed out to elsewhere, allowing multiline versions
            auto l_name = qtlib::To_QString<name_type>()(a_object.cmember_at<Index>().name());
            auto l_data = qtlib::To_QString<value_type>()(a_object.cmember_at<Index>().cget());
            a_stream.writeTextElement(l_name, l_data);
            do_loop<Index+1, End>()(a_stream, a_object);
          }
        };


        template <std::size_t End>
        struct do_loop<End, End>
        {
          void operator()(QXmlStreamWriter&, object_type const&)
          {
          }
        };


        void operator()(QXmlStreamWriter& a_stream, object_type const& a_object)
        {
          // start the element
          a_stream.writeStartElement(qtlib::To_QString<type_string_type>()(a_object.type()));

          do_loop<0>()(a_stream, a_object);

          // end the element
          a_stream.writeEndElement();
        }
      };



      template <typename T>
      struct do_loop_from_stream
      {
        using object_type = T;
        using type_string_type = typename object_type::type_string_type;

        template <std::size_t Index, std::size_t End = object_type::size()>
        struct do_loop
        {
          using member_type = mf::object_member_t<object_type, Index>;
          using name_type = typename member_type::name_string_type;
          using value_type = typename member_type::value_type;

          void operator()(QXmlStreamReader& a_stream, object_type& a_object)
          {
            if (a_stream.readNextStartElement()
                && a_stream.name().toString() == qtlib::To_QString<name_type>()(a_object.cmember_at<Index>().name()))
            {
              qDebug() << "tokenstring = " << a_stream.tokenString() << a_stream.name().toString();

              // read the data as a string
              auto l_data_qstring = a_stream.readElementText();
              // convert the data
              auto l_data = qtlib::From_QString<value_type>()(l_data_qstring);
              // write it
              a_object.member_at<Index>().get() = l_data;

              qDebug() << "tokenstring = " << a_stream.tokenString() << a_stream.name().toString();
              // apparently we jump to the end element when we use readElementText()
            }
            else
            {
              // bad member name...
              qDebug() << "Bad member name...";
              qDebug() << "Last element: " << a_stream.qualifiedName().toString();
            }
            do_loop<Index+1,End>()(a_stream, a_object);
          }
        };


        template <std::size_t End>
        struct do_loop<End, End>
        {
          void operator()(QXmlStreamReader&, object_type&)
          {
          }
        };


        void operator()(QXmlStreamReader& a_stream, object_type& a_object)
        {
          // open the element and verify it's correct
          if (a_stream.readNextStartElement()
              && a_stream.name().toString() == qtlib::To_QString<type_string_type>()(a_object.type()))
          {
            qDebug() << "tokenstring = " << a_stream.tokenString() << a_stream.name().toString();
            do_loop<0>()(a_stream, a_object);
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
            qDebug() << "Didn't find " << qtlib::To_QString<type_string_type>()(a_object.type());
            qDebug() << "Last element: " << a_stream.qualifiedName().toString();
          }
        }
      };
    }
  }
}


template <typename T>
void sak::shared::xml_traits<T>::to_stream(QXmlStreamWriter& a_stream, object_type const& a_object)
{
  do_loop_to_stream<T>()(a_stream, a_object);
}

template <typename T>
void sak::shared::xml_traits<T>::from_stream(QXmlStreamReader& a_stream, object_type& a_object)
{
  do_loop_from_stream<T>()(a_stream, a_object);
}



// Forced Instantiations
//============================================================
template sak::file::xml_traits;
template sak::texture::xml_traits;
