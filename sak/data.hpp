#ifndef SAK_DATA_HPP
#define SAK_DATA_HPP

#ifndef SAK_DATA_FWD_HPP
#include "data_fwd.hpp"
#endif

#ifndef FLAMINGO_DATA_CLASS_HPP
#include <flamingo/data_class.hpp>
#endif

#ifndef FLAMINGO_LITYPE_STRING_HPP
#include <flamingo/litype/string.hpp>
#endif

#ifndef INCLUDE_QT_QSTRING
#define INCLUDE_QT_QSTRING
#include <QString>
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Data<Class_Def>
  //---------------------------------------------------------------------------
  // Supplied with a class definition type, we determine the data type to be
  // used and store it alongside the common data like the name. If we want to
  // do other things like linking to other objects and data locking it will
  // go in here.

  template <typename T_Class_Def>
  class Data
  {
  public:
    // Reveal the definition type
    using Class_Def_Type = T_Class_Def;

    // Reveal things that will be needed to be used with this class.
    using Member_Def_Typelist = typename Class_Def_Type::Member_Def_Typelist;
    using Member_Name_Typelist = typename Class_Def_Type::Member_Name_Typelist;
    using Member_Value_Typelist = typename Class_Def_Type::Member_Value_Typelist;

    //using Typestring_Type = typename Class_Def_Type::Typestring_Type;
    //using Typestring_Plural_Type = typename Class_Def_Type::Typestring_Plural_Type;

    //using Iconpath_String = typename Class_Def_Type::Iconpath;
    using Data_Class = typename Class_Def_Type::Data_Class;

    Data() :
      m_name{},
      m_data{}
    {}
    explicit Data(QString const& a_name) :
      m_name{a_name},
      m_data{}
    {}
    ~Data() = default;

    Data(Data const&) = default;
    Data& operator=(Data const&) = default;

    Data(Data &&) = default;
    Data& operator=(Data &&) = default;

    // Modifiers
    //============================================================
    // Swap the data tuple with that of another data_class.
    void swap(Data& a_other)
    {
      m_name.swap(a_other.m_name);
      m_data.swap(a_other.m_data);
    }

    // Data Access
    //============================================================
    // Name is special.
    QString& name()
    {
      return m_name;
    }

    QString const& cname() const
    {
      return m_name;
    }

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
    QString m_name;
    Data_Class m_data;
  };

  //---------------------------------------------------------------------------
  // Data_Size<T>
  //---------------------------------------------------------------------------
  // Member count of a Section_Data<> class

  template <typename T>
  class Data_Size
  {
  public:
    static constexpr std::size_t const value = flamingo::data_class_size<typename T::Data_Class>::value;
  };

  template <typename T>
  constexpr std::size_t const Data_Size_v = Data_Size<T>::value;

  //---------------------------------------------------------------------------
  // Data_Member_Def<Index, T>
  //---------------------------------------------------------------------------
  // Member type of a Section_Data<> class

  // Access to member types for types that inherit shared::data_class
  template <std::size_t Index, typename T>
  class Data_Member_Def
  {
  public:
    using Type = flamingo::typelist_at_t<typename T::Member_Def_Typelist,Index>;
  };

  template <std::size_t I, typename T>
  using Data_Member_Def_Type = typename Data_Member_Def<I,T>::Type;

  //---------------------------------------------------------------------------
  // Data_Member_Name<Index, T>
  //---------------------------------------------------------------------------
  // Member name type of a Section_Data<> class

  // Access to member types for types that inherit shared::data_class
  template <std::size_t Index, typename T>
  class Data_Member_Name
  {
  public:
    using Type = flamingo::typelist_at_t<typename T::Member_Name_Typelist,Index>;
    //using Type = flamingo::data_class_member_name_t<Index,typename T::Data_Class>;
  };

  template <std::size_t I, typename T>
  using Data_Member_Name_Type = typename Data_Member_Name<I,T>::Type;

  //---------------------------------------------------------------------------
  // Data_Member_Value<Index, T>
  //---------------------------------------------------------------------------
  // Member name type of a Section_Data<> class

  // Access to member types for types that inherit shared::data_class
  template <std::size_t Index, typename T>
  class Data_Member_Value
  {
  public:
    using Type = flamingo::typelist_at_t<typename T::Member_Value_Typelist,Index>;
    //using Type = flamingo::data_class_member_t<Index,typename T::Value_Data_Class>;
  };

  template <std::size_t I, typename T>
  using Data_Member_Value_Type = typename Data_Member_Value<I,T>::Type;

} // namespace sak

#endif // DATA_HPP
