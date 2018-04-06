#include "project_handle_factory.hpp"

#include "class_definitions.hpp"
#include "data.hpp"
#include "handle.hpp"

//---------------------------------------------------------------------------
// Section_Handle_Factory_Imp<List, Index, End>
//---------------------------------------------------------------------------
// For a type that isn't at the end of the list.

// Special 6
//============================================================
template <std::size_t Index, std::size_t End, typename...Args>
sak::Section_Handle_Factory_Imp<flamingo::typelist<Args...>,Index,End>::Section_Handle_Factory_Imp() = default;

template <std::size_t Index, std::size_t End, typename...Args>
sak::Section_Handle_Factory_Imp<flamingo::typelist<Args...>,Index,End>::~Section_Handle_Factory_Imp() = default;

template <std::size_t Index, std::size_t End, typename...Args>
sak::Section_Handle_Factory_Imp<flamingo::typelist<Args...>,Index,End>::Section_Handle_Factory_Imp(Section_Handle_Factory_Imp const&) = default;

template <std::size_t Index, std::size_t End, typename...Args>
sak::Section_Handle_Factory_Imp<flamingo::typelist<Args...>,Index,End>& sak::Section_Handle_Factory_Imp<flamingo::typelist<Args...>,Index,End>::operator=(Section_Handle_Factory_Imp const&) = default;

template <std::size_t Index, std::size_t End, typename...Args>
sak::Section_Handle_Factory_Imp<flamingo::typelist<Args...>,Index,End>::Section_Handle_Factory_Imp(Section_Handle_Factory_Imp &&) = default;

template <std::size_t Index, std::size_t End, typename...Args>
sak::Section_Handle_Factory_Imp<flamingo::typelist<Args...>,Index,End>& sak::Section_Handle_Factory_Imp<flamingo::typelist<Args...>,Index,End>::operator=(Section_Handle_Factory_Imp &&) = default;

namespace
{
  template <typename T>
  QString do_default_name()
  {
    return QString::fromUtf8(T::Default_Name_Type::data());
  }
}


// Interface
//============================================================
// The default name of handles made by this.
template <std::size_t Index, std::size_t End, typename...Args>
QString sak::Section_Handle_Factory_Imp<flamingo::typelist<Args...>,Index,End>::default_name(Tag_Type&&) const
{
  return do_default_name<Type>();
}

// Make a null handle.
template <std::size_t Index, std::size_t End, typename...Args>
typename sak::Section_Handle_Factory_Imp<flamingo::typelist<Args...>,Index,End>::Handle_Type sak::Section_Handle_Factory_Imp<flamingo::typelist<Args...>,Index,End>::make_null(Tag_Type&&) const
{
  return Handle_Type{};
}

// Make a handle with data that is default initialised and has
// the default new name.
template <std::size_t Index, std::size_t End, typename...Args>
typename sak::Section_Handle_Factory_Imp<flamingo::typelist<Args...>,Index,End>::Handle_Type sak::Section_Handle_Factory_Imp<flamingo::typelist<Args...>,Index,End>::make_default(Tag_Type&&) const
{
  return Handle_Type{std::make_shared<Data_Type>(Data_Type(do_default_name<Type>())),next_id()};
}

// Make a handle with the supplied data. If the name is empty
// it will be given the default new name.
template <std::size_t Index, std::size_t End, typename...Args>
typename sak::Section_Handle_Factory_Imp<flamingo::typelist<Args...>,Index,End>::Handle_Type sak::Section_Handle_Factory_Imp<flamingo::typelist<Args...>,Index,End>::make_emplace(Data_Type&& a_data) const
{
  auto l_handle = Handle_Type{std::make_shared<Data_Type>(std::move(a_data)),next_id()};
  if (l_handle->cname().isEmpty())
  {
    l_handle->name() = do_default_name<Type>();
  }
  return l_handle;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Section_Handle_Factory_Imp<List, End, End>
//---------------------------------------------------------------------------
// For the type that is at the end of the list.

// Special 6
//============================================================
template <std::size_t End, typename...Args>
sak::Section_Handle_Factory_Imp<flamingo::typelist<Args...>,End,End>::Section_Handle_Factory_Imp() :
  m_next_id{0}
{
}

template <std::size_t End, typename...Args>
sak::Section_Handle_Factory_Imp<flamingo::typelist<Args...>,End,End>::~Section_Handle_Factory_Imp() = default;

template <std::size_t End, typename...Args>
sak::Section_Handle_Factory_Imp<flamingo::typelist<Args...>,End,End>::Section_Handle_Factory_Imp(Section_Handle_Factory_Imp const&) = default;

template <std::size_t End, typename...Args>
sak::Section_Handle_Factory_Imp<flamingo::typelist<Args...>,End,End>& sak::Section_Handle_Factory_Imp<flamingo::typelist<Args...>,End,End>::operator=(Section_Handle_Factory_Imp const&) = default;

template <std::size_t End, typename...Args>
sak::Section_Handle_Factory_Imp<flamingo::typelist<Args...>,End,End>::Section_Handle_Factory_Imp(Section_Handle_Factory_Imp &&) = default;

template <std::size_t End, typename...Args>
sak::Section_Handle_Factory_Imp<flamingo::typelist<Args...>,End,End>& sak::Section_Handle_Factory_Imp<flamingo::typelist<Args...>,End,End>::operator=(Section_Handle_Factory_Imp &&) = default;

// Get the next id to use for a handle.
template <std::size_t End, typename...Args>
std::size_t sak::Section_Handle_Factory_Imp<flamingo::typelist<Args...>,End,End>::next_id() const
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


template class sak::Section_Handle_Factory_Imp<sak::Project_Typelist,0,3>;
template class sak::Section_Handle_Factory_Imp<sak::Project_Typelist,1,3>;
template class sak::Section_Handle_Factory_Imp<sak::Project_Typelist,2,3>;
template class sak::Section_Handle_Factory_Imp<sak::Project_Typelist,3,3>;

template class sak::Project_Handle_Factory;

