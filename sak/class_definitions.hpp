#ifndef SAK_CLASS_DEFINITIONS_HPP
#define SAK_CLASS_DEFINITIONS_HPP

#ifndef SAK_CLASS_DEFINITIONS_FWD_HPP
#include "class_definitions_fwd.hpp"
#endif

#ifndef SAK_ABSTRACT_MEMBER_EDIT_WIDGET_FWD_HPP
#include "abstract_member_edit_widget_fwd.hpp"
#endif

#ifndef SAK_ABSTRACT_PROJECT_INTERFACE_FWD_HPP
#include "abstract_project_interface_fwd.hpp"
#endif

#ifndef SAK_DATA_DEFINITIONS_HPP
#include "data_definitions.hpp"
#endif

#ifndef FLAMINGO_DATA_CLASS_HPP
#include <flamingo/data_class.hpp>
#endif

class QString;
class QWidget;

namespace sak
{
  //---------------------------------------------------------------------------
  // Member_Definition<Name,Data_Def>
  //---------------------------------------------------------------------------
  // Define a member by supplying the name and the data definition.
  template <typename T_Data_Def, typename T_Name>
  class Member_Definition :
      private T_Data_Def // so we don't have to write forwarding functions
  {
  public:
    using Data_Def_Type = T_Data_Def;

    using Name_Type = T_Name;

    using Typestring_Type = typename Data_Def_Type::Typestring_Type;
    using Value_Type = typename Data_Def_Type::Value_Type;

    using Data_Def_Type::make_widget;
    using Data_Def_Type::set_widget_value;
    using Data_Def_Type::get_widget_value;
    using Data_Def_Type::connect_to;
    using Data_Def_Type::tooltip;

    using Data_Member = flamingo::data_member<Value_Type,Name_Type>;
  };

  //---------------------------------------------------------------------------
  // Member_Definition<Name,Class_Def>
  //---------------------------------------------------------------------------
  // Specialisation for Members that hold classes
  template <typename T_Name, typename T_Type, typename T_Type_Plural, typename T_Iconpath, typename...T_Member_Defs>
  class Member_Definition<T_Name, Class_Definition<T_Type,T_Type_Plural,T_Iconpath,T_Member_Defs...>>
  {
    using Class_Def = Class_Definition<T_Type,T_Type_Plural,T_Member_Defs...>;
  public:
    using Name_Type = T_Name;

    using Typestring_Type = typename Class_Def::Typestring_Type;

    // This needs to be a Handle<Class_Def::Data_Class>
    using Value_Type = typename Class_Def::Data_Class;

    // This is where the buggery happens.
    static std::unique_ptr<QWidget> make_widget();
    static void set_widget_value(QWidget* a_widget, Value_Type const& a_value);
    static Value_Type get_widget_value(QWidget* a_widget);
    static void connect_to(QWidget* a_widget, Abstract_Member_Edit_Widget* a_editor);
    static QString tooltip();

    using Data_Member = flamingo::data_member<Value_Type,Name_Type>;
  };

  //---------------------------------------------------------------------------
  // Class_Definition<Typestring,Plural,Member_Def...>
  //---------------------------------------------------------------------------
  // Define a class by supplying typestrings and Member_Definitions

  //template <typename T_Type, typename T_Type_Plural, typename T_Iconpath, typename...T_Member_Defs>
  //class Class_Definition;

  template <typename T_Type, typename T_Type_Plural, typename T_Iconpath, typename...T_Data_Defs, typename...T_Names>
  class Class_Definition<T_Type,T_Type_Plural,T_Iconpath, Member_Definition<T_Data_Defs,T_Names>...>
  {
  public:
    using Member_Def_Typelist = flamingo::typelist<Member_Definition<T_Data_Defs,T_Names>...>;
    using Member_Name_Typelist = flamingo::typelist<T_Names...>;
    using Member_Value_Typelist = flamingo::typelist<typename T_Data_Defs::Value_Type...>;

    using Typestring_Type = T_Type;
    using Typestring_Plural_Type = T_Type_Plural;

    using Iconpath_Type = T_Iconpath;

    using Data_Class = flamingo::data_class< typename Member_Definition<T_Data_Defs,T_Names>::Data_Member...>;
  };

  namespace internal
  {
    using Literal_String_S = FLAMINGO_LITYPE_STRING(u8"s");
  }

  template <typename T_Type, typename T_Iconpath, typename...T_Member_Defs>
  using Default_Class_Definition =
  Class_Definition
  <
    T_Type,
    flamingo::litype::string_concatenate_t<T_Type,internal::Literal_String_S>,
    T_Iconpath,
    T_Member_Defs...
  >;


  //---------------------------------------------------------------------------
  // Class_Def_Size<Class_Def>
  //---------------------------------------------------------------------------
  // The number of member definitions a class definition has

  template <typename T_Class_Def>
  class Class_Def_Size
  {
  public:
    static constexpr std::size_t const value = flamingo::typelist_size_v<typename T_Class_Def::Member_Def_Typelist>;
  };

  template <typename T_Class_Def>
  static constexpr std::size_t const Class_Def_Size_v = Class_Def_Size<T_Class_Def>::value;

  //---------------------------------------------------------------------------
  // Class_Member_Def_At<Index,Class_Def>
  //---------------------------------------------------------------------------
  // Access the definition for a given member in a class definition.

  template <std::size_t T_Index, typename T_Class_Def>
  class Class_Member_Def_At
  {
  public:
    using Type = flamingo::typelist_at_t<typename T_Class_Def::Member_Def_Typelist, T_Index>;
  };

  template <std::size_t T_Index, typename T_Class_Def>
  using Class_Member_Def_At_Type = typename Class_Member_Def_At<T_Index, T_Class_Def>::Type;





  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // Now we define the individual data sections. These could go in their own
  // files depending on how complicated they get. We need to do it via
  // inheritance/composition in order to hide the long typename of the template
  // classes used.


  namespace internal
  {
    using Icondir_Type = FLAMINGO_LITYPE_STRING(u8"D:/Source Army Knife/Icons/");

    template <typename T_Filename>
    class Iconpath
    {
    public:
      using Type = flamingo::litype::string_concatenate_t<Icondir_Type,T_Filename>;
    };

    template <typename T_Filename>
    using Iconpath_Type = typename Iconpath<T_Filename>::Type;
  }

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // File
  //---------------------------------------------------------------------------

  class File_Definition :
      public Default_Class_Definition
      <
      FLAMINGO_LITYPE_STRING(u8"File"),
      internal::Iconpath_Type<FLAMINGO_LITYPE_STRING(u8"file_icon.png")>,
      Member_Definition<Text_Line_Definition, FLAMINGO_LITYPE_STRING(u8"First")>,
      Member_Definition<Text_Line_Definition, FLAMINGO_LITYPE_STRING(u8"Second")>
      >
  {
    static_assert(Class_Def_Size_v<File_Definition> == 2,  "bad size");
    static_assert(flamingo::typelist_size_v<Member_Def_Typelist> == 2,  "bad size");
    static_assert(flamingo::typelist_size_v<Member_Name_Typelist> == 2,  "bad size");
    static_assert(flamingo::typelist_size_v<Member_Value_Typelist> == 2,  "bad size");
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Texture
  //---------------------------------------------------------------------------

  class Texture_Definition :
      public Default_Class_Definition
      <
      FLAMINGO_LITYPE_STRING(u8"Texture"),
      internal::Iconpath_Type<FLAMINGO_LITYPE_STRING(u8"texture_icon.png")>,
      Member_Definition<Text_Line_Definition, FLAMINGO_LITYPE_STRING(u8"Another")>
      >
  {
    static_assert(Class_Def_Size_v<Texture_Definition> == 1,  "bad size");
    static_assert(flamingo::typelist_size_v<Member_Def_Typelist> == 1,  "bad size");
    static_assert(flamingo::typelist_size_v<Member_Name_Typelist> == 1,  "bad size");
    static_assert(flamingo::typelist_size_v<Member_Value_Typelist> == 1,  "bad size");
  };
} // namespace sak

#endif // SAK_CLASS_DEFINITIONS_HPP
