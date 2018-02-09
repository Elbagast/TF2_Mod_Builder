#include "project_handle_factory.hpp"

#include "class_definitions.hpp"
#include "data.hpp"
#include "handle.hpp"

//---------------------------------------------------------------------------
// Do_Project_Handle_Factory_Part_Imp<T>
//---------------------------------------------------------------------------
namespace sak
{
  namespace internal
  {
    template <typename T>
    class Do_Project_Handle_Factory_Part_Imp
    {
      // Typedefs
      //============================================================
      using Type = T;
      using Handle_Type = Handle<Type>;
      using Data_Type = Data<Type>;
      using Tag_Type = Tag<Type>;
    public:

      // Interface
      //============================================================
      static QString default_name()
      {
        return QString::fromUtf8(Type::Default_Name_Type::data());
      }

      // Make a null handle.
      static Handle_Type make_null()
      {
        return Handle_Type{};
      }

      // Make a handle with data that is default initialised and has
      // the default new name.
      static Handle_Type make_default(std::size_t a_id)
      {
        return Handle_Type{std::make_shared<Data_Type>(Data_Type(default_name())),a_id};
      }

      // Make a handle with the supplied data. If the name is empty
      // it will be given the default new name.
      static Handle_Type make_emplace(Data_Type&& a_data, std::size_t a_id)
      {
        auto l_handle = Handle_Type{std::make_shared<Data_Type>(std::move(a_data)),a_id};
        if (l_handle->cname().isEmpty())
        {
          l_handle->name() = default_name();
        }
        return l_handle;
      }
    };
  }
}



//---------------------------------------------------------------------------
// Project_Handle_Factory_Part_Imp<List, Index, End>
//---------------------------------------------------------------------------
// For a type that isn't at the end of the list.

// Special 6
//============================================================
template <std::size_t Index, std::size_t End, typename...Args>
sak::internal::Project_Handle_Factory_Part_Imp<flamingo::typelist<Args...>,Index,End>::Project_Handle_Factory_Part_Imp() = default;

template <std::size_t Index, std::size_t End, typename...Args>
sak::internal::Project_Handle_Factory_Part_Imp<flamingo::typelist<Args...>,Index,End>::~Project_Handle_Factory_Part_Imp() = default;

template <std::size_t Index, std::size_t End, typename...Args>
sak::internal::Project_Handle_Factory_Part_Imp<flamingo::typelist<Args...>,Index,End>::Project_Handle_Factory_Part_Imp(Project_Handle_Factory_Part_Imp const&) = default;

template <std::size_t Index, std::size_t End, typename...Args>
sak::internal::Project_Handle_Factory_Part_Imp<flamingo::typelist<Args...>,Index,End>& sak::internal::Project_Handle_Factory_Part_Imp<flamingo::typelist<Args...>,Index,End>::operator=(Project_Handle_Factory_Part_Imp const&) = default;

template <std::size_t Index, std::size_t End, typename...Args>
sak::internal::Project_Handle_Factory_Part_Imp<flamingo::typelist<Args...>,Index,End>::Project_Handle_Factory_Part_Imp(Project_Handle_Factory_Part_Imp &&) = default;

template <std::size_t Index, std::size_t End, typename...Args>
sak::internal::Project_Handle_Factory_Part_Imp<flamingo::typelist<Args...>,Index,End>& sak::internal::Project_Handle_Factory_Part_Imp<flamingo::typelist<Args...>,Index,End>::operator=(Project_Handle_Factory_Part_Imp &&) = default;

// Interface
//============================================================
// The default name of handles made by this.
template <std::size_t Index, std::size_t End, typename...Args>
QString sak::internal::Project_Handle_Factory_Part_Imp<flamingo::typelist<Args...>,Index,End>::default_name(Tag_Type&&) const
{
  return Do_Project_Handle_Factory_Part_Imp<Type>::default_name();
}

// Make a null handle.
template <std::size_t Index, std::size_t End, typename...Args>
typename sak::internal::Project_Handle_Factory_Part_Imp<flamingo::typelist<Args...>,Index,End>::Handle_Type sak::internal::Project_Handle_Factory_Part_Imp<flamingo::typelist<Args...>,Index,End>::make_null(Tag_Type&&) const
{
  return Do_Project_Handle_Factory_Part_Imp<Type>::make_null();
}

// Make a handle with data that is default initialised and has
// the default new name.
template <std::size_t Index, std::size_t End, typename...Args>
typename sak::internal::Project_Handle_Factory_Part_Imp<flamingo::typelist<Args...>,Index,End>::Handle_Type sak::internal::Project_Handle_Factory_Part_Imp<flamingo::typelist<Args...>,Index,End>::make_default(Tag_Type&&) const
{
  return Do_Project_Handle_Factory_Part_Imp<Type>::make_default(next_id());
}

// Make a handle with the supplied data. If the name is empty
// it will be given the default new name.
template <std::size_t Index, std::size_t End, typename...Args>
typename sak::internal::Project_Handle_Factory_Part_Imp<flamingo::typelist<Args...>,Index,End>::Handle_Type sak::internal::Project_Handle_Factory_Part_Imp<flamingo::typelist<Args...>,Index,End>::make_emplace(Data_Type&& a_data) const
{
  return Do_Project_Handle_Factory_Part_Imp<Type>::make_emplace(std::move(a_data),next_id());
}


//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Project_Handle_Factory_Part_Imp<List, End, End>
//---------------------------------------------------------------------------
// For the type that is at the end of the list.

// Special 6
//============================================================
template <std::size_t End, typename...Args>
sak::internal::Project_Handle_Factory_Part_Imp<flamingo::typelist<Args...>,End,End>::Project_Handle_Factory_Part_Imp() :
  m_next_id{0}
{
}

template <std::size_t End, typename...Args>
sak::internal::Project_Handle_Factory_Part_Imp<flamingo::typelist<Args...>,End,End>::~Project_Handle_Factory_Part_Imp() = default;

template <std::size_t End, typename...Args>
sak::internal::Project_Handle_Factory_Part_Imp<flamingo::typelist<Args...>,End,End>::Project_Handle_Factory_Part_Imp(Project_Handle_Factory_Part_Imp const&) = default;

template <std::size_t End, typename...Args>
sak::internal::Project_Handle_Factory_Part_Imp<flamingo::typelist<Args...>,End,End>& sak::internal::Project_Handle_Factory_Part_Imp<flamingo::typelist<Args...>,End,End>::operator=(Project_Handle_Factory_Part_Imp const&) = default;

template <std::size_t End, typename...Args>
sak::internal::Project_Handle_Factory_Part_Imp<flamingo::typelist<Args...>,End,End>::Project_Handle_Factory_Part_Imp(Project_Handle_Factory_Part_Imp &&) = default;

template <std::size_t End, typename...Args>
sak::internal::Project_Handle_Factory_Part_Imp<flamingo::typelist<Args...>,End,End>& sak::internal::Project_Handle_Factory_Part_Imp<flamingo::typelist<Args...>,End,End>::operator=(Project_Handle_Factory_Part_Imp &&) = default;

// Interface
//============================================================
// The default name of handles made by this.
template <std::size_t End, typename...Args>
QString sak::internal::Project_Handle_Factory_Part_Imp<flamingo::typelist<Args...>,End,End>::default_name(Tag_Type&&) const
{
  return Do_Project_Handle_Factory_Part_Imp<Type>::default_name();
}

// Make a null handle.
template <std::size_t End, typename...Args>
typename sak::internal::Project_Handle_Factory_Part_Imp<flamingo::typelist<Args...>,End,End>::Handle_Type sak::internal::Project_Handle_Factory_Part_Imp<flamingo::typelist<Args...>,End,End>::make_null(Tag_Type&&) const
{
  return Do_Project_Handle_Factory_Part_Imp<Type>::make_null();
}

// Make a handle with data that is default initialised and has
// the default new name.
template <std::size_t End, typename...Args>
typename sak::internal::Project_Handle_Factory_Part_Imp<flamingo::typelist<Args...>,End,End>::Handle_Type sak::internal::Project_Handle_Factory_Part_Imp<flamingo::typelist<Args...>,End,End>::make_default(Tag_Type&&) const
{
  return Do_Project_Handle_Factory_Part_Imp<Type>::make_default(next_id());
}

// Make a handle with the supplied data. If the name is empty
// it will be given the default new name.
template <std::size_t End, typename...Args>
typename sak::internal::Project_Handle_Factory_Part_Imp<flamingo::typelist<Args...>,End,End>::Handle_Type sak::internal::Project_Handle_Factory_Part_Imp<flamingo::typelist<Args...>,End,End>::make_emplace(Data_Type&& a_data) const
{
  return Do_Project_Handle_Factory_Part_Imp<Type>::make_emplace(std::move(a_data),next_id());
}

// Get the next id to use for a handle.
template <std::size_t End, typename...Args>
std::size_t sak::internal::Project_Handle_Factory_Part_Imp<flamingo::typelist<Args...>,End,End>::next_id() const
{
  return ++m_next_id;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Project_Handle_Factory_Imp<T,Args...>
//---------------------------------------------------------------------------

template <typename T, typename...Args>
sak::Project_Handle_Factory_Imp<T,Args...>::Project_Handle_Factory_Imp() = default;

template <typename T, typename...Args>
sak::Project_Handle_Factory_Imp<T,Args...>::~Project_Handle_Factory_Imp() = default;

template <typename T, typename...Args>
sak::Project_Handle_Factory_Imp<T,Args...>::Project_Handle_Factory_Imp(Project_Handle_Factory_Imp const&) = default;

template <typename T, typename...Args>
sak::Project_Handle_Factory_Imp<T,Args...>& sak::Project_Handle_Factory_Imp<T,Args...>::operator=(Project_Handle_Factory_Imp const&) = default;

template <typename T, typename...Args>
sak::Project_Handle_Factory_Imp<T,Args...>::Project_Handle_Factory_Imp(Project_Handle_Factory_Imp &&) = default;

template <typename T, typename...Args>
sak::Project_Handle_Factory_Imp<T,Args...>& sak::Project_Handle_Factory_Imp<T,Args...>::operator=(Project_Handle_Factory_Imp &&) = default;

//------------------------------------------------------------------------------------------------------------------------------------------------------


template class sak::internal::Project_Handle_Factory_Part_Imp<sak::Project_Typelist,0,2>;
template class sak::internal::Project_Handle_Factory_Part_Imp<sak::Project_Typelist,1,2>;
template class sak::internal::Project_Handle_Factory_Part_Imp<sak::Project_Typelist,2,2>;

template class sak::Project_Handle_Factory;

