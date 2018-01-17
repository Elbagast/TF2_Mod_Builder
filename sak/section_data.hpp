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

namespace sak
{
  //---------------------------------------------------------------------------
  // Shared_Data_Class
  //---------------------------------------------------------------------------
  // Data that is present for all data types, always at the front.

  using Shared_Data_Class =
  flamingo::data_class
  <
  flamingo::data_member<QString, FLAMINGO_LITYPE_STRING(u8"Name")>
  ,flamingo::data_member<QString, FLAMINGO_LITYPE_STRING(u8"Description")>
  >;


  //---------------------------------------------------------------------------
  // typelist_to_variant
  //---------------------------------------------------------------------------
  // This is only used here.

  namespace internal
  {

    template <typename T_List>
    struct typelist_to_variant;

    template <typename... Args>
    struct typelist_to_variant<flamingo::typelist<Args...>>
    {
      using type = boost::variant<Args...>;
    };

    template <typename T_List>
    using typelist_to_variant_t = typename typelist_to_variant<T_List>::type;
  }

  //---------------------------------------------------------------------------
  // Section_Data
  //---------------------------------------------------------------------------
  // We wrap our flamingo::data_class with a simple typename and forward
  // everything to it. The data_class has to be available as a public typedef
  // so we can build forwarding utilities.
  template <typename T_Data_Traits>
  class Section_Data
  {
  public:
    using Typestring = typename T_Data_Traits::Typestring;
    using Typestring_Plural = typename T_Data_Traits::Typestring_Plural;
    // Always have the shared members first.
    using Data_Class = flamingo::data_class_concatenate_t<Shared_Data_Class, typename T_Data_Traits::Data_Class>;
    // Must do this after the shared members are added.
    using Member_Value_Variant = internal::typelist_to_variant_t<flamingo::data_class_member_typelist_t<Data_Class>>;

    static std::basic_string<typename Typestring::char_type> type()
    {
      return std::basic_string<typename Typestring::char_type>(Typestring::data());
    }
    static std::basic_string<typename Typestring::char_type> type_plural()
    {
      return std::basic_string<typename Typestring::char_type>(Typestring_Plural::data());
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
    Data_Class m_data;
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
  // Section_Data_Member_Variant<T>
  //---------------------------------------------------------------------------

  template <typename T>
  class Section_Data_Member_Variant
  {
  public:
    using Type = internal::typelist_to_variant_t<flamingo::typelist_unique_t<Section_Data_Member_Typelist_Type<T>>>;
  };

  template <typename T>
  using Section_Data_Member_Variant_Type = typename Section_Data_Member_Variant<T>::Type;


  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // Now we define the individual data sections. These could go in their own
  // files depending on how complicated they get.

  //---------------------------------------------------------------------------
  // File
  //---------------------------------------------------------------------------
  // Typestring classes and unique data members

  class File_Data_Traits
  {
  public:
    using Typestring = FLAMINGO_LITYPE_STRING(u8"File");
    using Typestring_Plural = FLAMINGO_LITYPE_STRING(u8"Files");

    using Data_Class =
    flamingo::data_class
    <
    flamingo::data_member<QString, FLAMINGO_LITYPE_STRING(u8"Buildpath")>
    ,flamingo::data_member<QString, FLAMINGO_LITYPE_STRING(u8"Sourcepath")>
    ,flamingo::data_member<bool, FLAMINGO_LITYPE_STRING(u8"Booltest")>
    ,flamingo::data_member<QString, FLAMINGO_LITYPE_STRING(u8"std_stringtest")>
    >;

  };

  class File_Data :
      public Section_Data<File_Data_Traits>
  {};

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Texture
  //---------------------------------------------------------------------------
  // Typestring classes and unique data members

  class Texture_Data_Traits
  {
  public:
    using Typestring = FLAMINGO_LITYPE_STRING(u8"Texture");
    using Typestring_Plural = FLAMINGO_LITYPE_STRING(u8"Textures");

    using Data_Class =
    flamingo::data_class
    <
    flamingo::data_member<QString, FLAMINGO_LITYPE_STRING(u8"Buildpath")>
    ,flamingo::data_member<QString, FLAMINGO_LITYPE_STRING(u8"Sourcepath")>
    >;

  };

  class Texture_Data :
      public Section_Data<Texture_Data_Traits>
  {};
}



#endif // SAK_SECTION_DATA_HPP
