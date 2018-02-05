#include "test_class_definitions.hpp"

#include <sak/data_definitions.hpp>
#include <sak/class_definitions.hpp>

#include <iostream>


namespace
{
  template <typename T>
  void data_def_to_stream (std::ostream& a_stream)
  {
    using namespace sak;

    using Data_Def = T;

    a_stream << "Data_Def:" << std::endl;
    a_stream << "-------------------------" << std::endl;
    a_stream << "Typestring =   \"" << Data_Def::Typestring_Type::data() << "\"" << std::endl;
  }


  template <typename T>
  void member_def_to_stream (std::ostream& a_stream)
  {
    using namespace sak;

    using Member_Def = T;

    a_stream << "Member_Def:" << std::endl;
    a_stream << "-------------" << std::endl;
    a_stream << "Name =       \"" << Member_Def::Name_Type::data() << "\"" << std::endl;
    a_stream << "Typestring = \"" << Member_Def::Typestring_Type::data() << "\"" << std::endl;
    a_stream << "--------------" << std::endl;
  }

  template <typename T>
  class do_members_to_stream
  {
  public:
    template <std::size_t I, std::size_t End = sak::Class_Def_Size_v<T>>
    struct do_member
    {
      void operator()(std::ostream& a_stream)
      {
        member_def_to_stream<sak::Class_Member_Def_At_Type<I,T>>(a_stream);
        do_member<I+1,End>()(a_stream);
      }
    };

    template <std::size_t End>
    struct do_member<End,End>
    {
      void operator()(std::ostream&)
      {
      }
    };

    void operator()(std::ostream& a_stream)
    {
      do_member<0>()(a_stream);
    }
  };


  template <typename T>
  void class_def_to_stream (std::ostream& a_stream)
  {
    using namespace sak;

    using Class_Def = T;

    a_stream << "Class_Def:" << std::endl;
    a_stream << "-------------------------" << std::endl;
    a_stream << "Typestring = \"" << Class_Def::Typestring_Type::data() << "\"" << std::endl;
    a_stream << "Plural =     \"" << Class_Def::Typestring_Plural_Type::data() << "\"" << std::endl;
    a_stream << "Iconpath =   \"" << Class_Def::Iconpath_Type::data() << "\"" << std::endl;
    a_stream << "Size =       \"" << Class_Def_Size_v<T> << "\"" << std::endl;

    do_members_to_stream<T>()(a_stream);

    a_stream << "-------------------------" << std::endl;
  }
}

void sak::testing::test_class_definitions()
{
  std::cout << "Testing Class Definitions" << std::endl;
  std::cout << "==============================" << std::endl;

  class_def_to_stream<sak::File_Definition>(std::cout);
  class_def_to_stream<sak::Texture_Definition>(std::cout);


  std::cout << "==============================" << std::endl;
}
