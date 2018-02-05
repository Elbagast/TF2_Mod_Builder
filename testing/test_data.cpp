#include "test_data.hpp"

#include <sak/data_definitions.hpp>
#include <sak/class_definitions.hpp>
#include <sak/data.hpp>

#include <iostream>

namespace
{
  template <std::size_t I, typename T>
  void member_to_stream (std::ostream& a_stream, sak::Data<T> const& a_data)
  {
    using namespace sak;

    using Member_Def = Data_Member_Def_Type<I,Data<T>>;

    a_stream << "Member:" << std::endl;
    a_stream << "-------------" << std::endl;
    a_stream << "Typestring = \"" << Member_Def::Typestring_Type::data() << "\"" << std::endl;
    a_stream << "Name =       \"" << Member_Def::Name_Type::data() << "\"" << std::endl;
    a_stream << "Value =      \"" << a_data.cmember_at<I>() << "\"" << std::endl;
    a_stream << "--------------" << std::endl;
  }

  template <typename T>
  class do_members_to_stream
  {
  public:
    template <std::size_t I, std::size_t End = sak::Class_Def_Size_v<T>>
    struct do_member
    {
      void operator()(std::ostream& a_stream, sak::Data<T> const& a_data)
      {
        member_to_stream<I>(a_stream, a_data);
        do_member<I+1,End>()(a_stream, a_data);
      }
    };

    template <std::size_t End>
    struct do_member<End,End>
    {
      void operator()(std::ostream&, sak::Data<T> const&)
      {
      }
    };

    void operator()(std::ostream& a_stream, sak::Data<T> const& a_data)
    {
      do_member<0>()(a_stream, a_data);
    }
  };

  // temporary operator
  std::ostream& operator << (std::ostream& a_stream, QString const& a_string)
  {
    a_stream << a_string.toStdString();
    return a_stream;
  }


  template <typename T>
  void data_to_stream(std::ostream& a_stream, sak::Data<T> const& a_data)
  {
    using namespace sak;

    using Class_Def = T;

    a_stream << "Data<T>:" << std::endl;
    a_stream << "-------------------------" << std::endl;
    a_stream << "Typestring = \"" << Class_Def::Typestring_Type::data() << "\"" << std::endl;
    a_stream << "Name =       \"" << a_data.cname() << "\"" << std::endl;
    a_stream << "Size =       \"" << Data_Size_v<Data<T>> << "\"" << std::endl;

    do_members_to_stream<T>()(a_stream, a_data);

    a_stream << "-------------------------" << std::endl;
  }




  template <typename T>
  void do_test_data()
  {
    using namespace sak;
    using Data_Type = Data<T>;

    // Default construction
    Data_Type l_d1{};
    //std::cout << "Default name = \"" << l_d1.cname().toStdString() << "\"" << std::endl;

    // alter name
    l_d1.name() = QString("new name");
    //std::cout << "new name = \"" << l_d1.cname().toStdString() << "\"" << std::endl;

    data_to_stream(std::cout, l_d1);

  }
}



void sak::testing::test_data()
{
  std::cout << "Testing sak::Data<T>" << std::endl;
  std::cout << "==============================" << std::endl;

  using namespace sak;

  using File_Data = Data<File_Definition>;
  using Texture_Data = Data<Texture_Definition>;

  do_test_data<File_Definition>();
  do_test_data<Texture_Definition>();

  std::cout << "==============================" << std::endl;
}
