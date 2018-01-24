#ifndef SAK_SECTION_DATA_HPP
#define SAK_SECTION_DATA_HPP

#ifndef SAK_SECTION_DATA_FWD_HPP
#include "section_data_fwd.hpp"
#endif

#ifndef FLAMINGO_DATA_CLASS_HPP
#include <flamingo/data_class.hpp>
#endif

#ifndef FLAMINGO_LITYPE_STRING_HPP
#include <flamingo/litype/string.hpp>
#endif

#ifndef INCLUDE_STD_STRING
#define INCLUDE_STD_STRING
#include <string>
#endif

#ifndef INCLUDE_QT_QSTRING
#define INCLUDE_QT_QSTRING
#include <QString>
#endif

#ifndef INCLUDE_BOOST_VARIANT
#define INCLUDE_BOOST_VARIANT
#include <boost/variant.hpp>
#endif

#include "shared_attributes.hpp"

namespace sak
{

  namespace internal
  {
    //---------------------------------------------------------------------------
    // Shared_Data_Class
    //---------------------------------------------------------------------------
    // Data that is present for all data types, always at the front.

    using Shared_Data_Class =
    flamingo::data_class
    <
    flamingo::data_member<Text_Line, FLAMINGO_LITYPE_STRING(u8"Name")>
    ,flamingo::data_member<Text_Line, FLAMINGO_LITYPE_STRING(u8"Description")>
    >;

    //---------------------------------------------------------------------------
    // typelist_to_variant
    //---------------------------------------------------------------------------
    // This is only used here.
    template <typename T_List>
    struct typelist_to_variant;

    template <typename... Args>
    struct typelist_to_variant<flamingo::typelist<Args...>>
    {
      using type = boost::variant<Args...>;
    };

    template <typename T_List>
    using typelist_to_variant_t = typename typelist_to_variant<T_List>::type;


    //---------------------------------------------------------------------------
    // Value_Data_Class
    //---------------------------------------------------------------------------
    // Data class that will hold the actual data values
    template <typename T>
    class Value_Data_Class;


    template <typename...T, typename...N>
    class Value_Data_Class<flamingo::data_class<flamingo::data_member<T,N>...>>
    {
    public:
      using Type = flamingo::data_class<flamingo::data_member<typename T::Value_Type,N>...>;
    };

    template <typename T>
    using Value_Data_Class_Type = typename Value_Data_Class<T>::Type;
  }

  //---------------------------------------------------------------------------
  // Section_Data
  //---------------------------------------------------------------------------
  // We wrap our flamingo::data_class with a simple typename and forward
  // everything to it. The data_class has to be available as a public typedef
  // so we can build forwarding utilities.

  /*
  - We are supplied with a class that contains data traits.
  - There is a list of members that are traits classes with names.
  - Supply access to the traits classes to find out what to do with the values.
  - Supply access to the value type so it can be stored.
  */


  template <typename T_Data_Traits>
  class Section_Data
  {
  public:
    using Typestring = typename T_Data_Traits::Typestring;
    using Typestring_Plural = typename T_Data_Traits::Typestring_Plural;

    using Iconpath_String = typename T_Data_Traits::Iconpath;

    // Always have the shared members first.
    using Data_Class = flamingo::data_class_concatenate_t<internal::Shared_Data_Class, typename T_Data_Traits::Data_Class>;

    using Value_Data_Class = internal::Value_Data_Class_Type<Data_Class>;


    // Must do this after the shared members are added.
    using Member_Value_Variant = internal::typelist_to_variant_t<flamingo::data_class_member_typelist_t<Data_Class>>;

    static decltype(auto) type()
    {
      return std::basic_string<typename Typestring::char_type>(Typestring::data());
    }
    static decltype(auto) type_plural()
    {
      return std::basic_string<typename Typestring::char_type>(Typestring_Plural::data());
    }
    static decltype(auto) iconpath()
    {
      return std::basic_string<typename Iconpath_String::char_type>(Iconpath_String::data());
    }



    Section_Data() :
      m_data{}
    {}
    ~Section_Data() = default;

    Section_Data(Section_Data const&) = default;
    Section_Data& operator=(Section_Data const&) = default;

    Section_Data(Section_Data &&) = default;
    Section_Data& operator=(Section_Data &&) = default;

    // Modifiers
    //============================================================
    // Swap the data tuple with that of another data_class.
    void swap(Section_Data& a_other) noexcept(noexcept(m_data.swap(a_other.m_data)))
    {
      m_data.swap(a_other.m_data);
    }

    // Data Access
    //============================================================
    template <std::size_t I>
    decltype(auto) member_at()
    {
      return m_data.member_at<I>();
    }

    template <std::size_t I>
    decltype(auto) cmember_at() const
    {
      return m_data.cmember_at<I>();
    }

    template <typename S>
    decltype(auto) member()
    {
      return m_data.member<S>();
    }

    template <typename S>
    decltype(auto) cmember() const
    {
      return m_data.cmember<S>();
    }

  private:
    Value_Data_Class m_data;
  };


  //---------------------------------------------------------------------------
  // Section_Data_Size<T>
  //---------------------------------------------------------------------------
  // Member count of a Section_Data<> class

  template <typename T>
  class Section_Data_Size
  {
  public:
    static constexpr std::size_t const value = flamingo::data_class_size<typename T::Data_Class>::value;
  };

  template <typename T>
  constexpr std::size_t const Section_Data_Size_v = Section_Data_Size<T>::value;


  //---------------------------------------------------------------------------
  // Section_Data_Member<Index, T>
  //---------------------------------------------------------------------------
  // Member type of a Section_Data<> class

  // Access to member types for types that inherit shared::data_class
  template <std::size_t Index, typename T>
  class Section_Data_Member
  {
  public:
    using Type = flamingo::data_class_member_t<Index,typename T::Data_Class>;

  };

  template <std::size_t I, typename T>
  using Section_Data_Member_Type = typename Section_Data_Member<I,T>::Type;

  //---------------------------------------------------------------------------
  // Section_Data_Member_Value<Index, T>
  //---------------------------------------------------------------------------
  // Member name type of a Section_Data<> class

  // Access to member types for types that inherit shared::data_class
  template <std::size_t Index, typename T>
  class Section_Data_Member_Value
  {
  public:
    using Type = flamingo::data_class_member_t<Index,typename T::Value_Data_Class>;

  };

  template <std::size_t I, typename T>
  using Section_Data_Member_Value_Type = typename Section_Data_Member_Value<I,T>::Type;


  //---------------------------------------------------------------------------
  // Section_Data_Member_Name<Index, T>
  //---------------------------------------------------------------------------
  // Member name type of a Section_Data<> class

  // Access to member types for types that inherit shared::data_class
  template <std::size_t Index, typename T>
  class Section_Data_Member_Name
  {
  public:
    using Type = flamingo::data_class_member_name_t<Index,typename T::Data_Class>;
  };

  template <std::size_t I, typename T>
  using Section_Data_Member_Name_Type = typename Section_Data_Member_Name<I,T>::Type;



  //---------------------------------------------------------------------------
  // Section_Data_Member_Typelist<T>
  //---------------------------------------------------------------------------

  template <typename T>
  class Section_Data_Member_Typelist
  {
  public:
    using Type = flamingo::data_class_member_typelist_t<typename T::Data_Class>;
  };

  template <typename T>
  using Section_Data_Member_Typelist_Type = typename Section_Data_Member_Typelist<T>::Type;

  //---------------------------------------------------------------------------
  // Section_Data_Member_Value_Typelist<T>
  //---------------------------------------------------------------------------

  template <typename T>
  class Section_Data_Member_Value_Typelist
  {
  public:
    using Type = flamingo::data_class_member_typelist_t<typename T::Value_Data_Class>;
  };

  template <typename T>
  using Section_Data_Member_Value_Typelist_Type = typename Section_Data_Member_Value_Typelist<T>::Type;



  //---------------------------------------------------------------------------
  // Section_Data_Member_Name_Typelist<T>
  //---------------------------------------------------------------------------

  template <typename T>
  class Section_Data_Member_Name_Typelist
  {
  public:
    using Type = flamingo::data_class_member_name_typelist_t<typename T::Data_Class>;
  };

  template <typename T>
  using Section_Data_Member_Name_Typelist_t = typename Section_Data_Member_Name_Typelist<T>::Type;

  //---------------------------------------------------------------------------
  // Section_Data_Member_Value_Variant<T>
  //---------------------------------------------------------------------------

  template <typename T>
  class Section_Data_Member_Value_Variant
  {
  public:
    using Type = internal::typelist_to_variant_t<flamingo::typelist_unique_t<Section_Data_Member_Value_Typelist_Type<T>>>;
  };

  template <typename T>
  using Section_Data_Member_Value_Variant_Type = typename Section_Data_Member_Value_Variant<T>::Type;


  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // Now we define the individual data sections. These could go in their own
  // files depending on how complicated they get.


  namespace internal
  {
    using Literal_String_S =   FLAMINGO_LITYPE_STRING(u8"s");
  }



  //---------------------------------------------------------------------------
  // File
  //---------------------------------------------------------------------------
  // Typestring classes and unique data members

  class File_Data_Traits
  {
  public:
    using Typestring = FLAMINGO_LITYPE_STRING(u8"File");
    using Typestring_Plural = flamingo::litype::string_concatenate_t<Typestring, internal::Literal_String_S>;

    using Iconpath = FLAMINGO_LITYPE_STRING(u8"D:\\Source Army Knife\\Icons\\file_icon.png");

    using Data_Class =
    flamingo::data_class
    <
    //flamingo::data_member<QString, FLAMINGO_LITYPE_STRING(u8"Buildpath")>
    //,flamingo::data_member<QString, FLAMINGO_LITYPE_STRING(u8"Sourcepath")>
    //,flamingo::data_member<bool, FLAMINGO_LITYPE_STRING(u8"Booltest")>
    //,flamingo::data_member<QString, FLAMINGO_LITYPE_STRING(u8"std_stringtest")>
    >;

  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Texture
  //---------------------------------------------------------------------------
  // Typestring classes and unique data members


  class Texture_Data_Traits
  {
  public:
    using Typestring = FLAMINGO_LITYPE_STRING(u8"Texture");
    using Typestring_Plural = flamingo::litype::string_concatenate_t<Typestring, internal::Literal_String_S>;

    using Iconpath = FLAMINGO_LITYPE_STRING(u8"D:\\Source Army Knife\\Icons\\texture_icon.png");

    using Data_Class =
    flamingo::data_class
    <
    //flamingo::data_member<QString, FLAMINGO_LITYPE_STRING(u8"Buildpath")>
    //,flamingo::data_member<QString, FLAMINGO_LITYPE_STRING(u8"Sourcepath")>
    >;

  };

}



#endif // SAK_SECTION_DATA_HPP
