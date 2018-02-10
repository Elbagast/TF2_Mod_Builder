#include "project_handle_data.hpp"

#include "data_definitions.hpp"
#include "class_definitions.hpp"
#include "data.hpp"
#include "handle.hpp"
#include "tag.hpp"
#include "name_utilities.hpp"

#include <cassert>
#include <algorithm>
#include <iterator>
#include <type_traits>

#include <QString>

//---------------------------------------------------------------------------
// Project_Handle_Data_Part_Imp<List, Index, End>
//---------------------------------------------------------------------------
// For a type that isn't at the end of the list.

// Special 6
//============================================================
template <std::size_t Index, std::size_t End, typename...Args>
sak::internal::Project_Handle_Data_Part_Imp<flamingo::typelist<Args...>,Index,End>::Project_Handle_Data_Part_Imp() :
  Inh(),
  m_handles{}
{}

template <std::size_t Index, std::size_t End, typename...Args>
sak::internal::Project_Handle_Data_Part_Imp<flamingo::typelist<Args...>,Index,End>::~Project_Handle_Data_Part_Imp() = default;

template <std::size_t Index, std::size_t End, typename...Args>
sak::internal::Project_Handle_Data_Part_Imp<flamingo::typelist<Args...>,Index,End>::Project_Handle_Data_Part_Imp(Project_Handle_Data_Part_Imp const&) = default;

template <std::size_t Index, std::size_t End, typename...Args>
sak::internal::Project_Handle_Data_Part_Imp<flamingo::typelist<Args...>,Index,End>& sak::internal::Project_Handle_Data_Part_Imp<flamingo::typelist<Args...>,Index,End>::operator=(Project_Handle_Data_Part_Imp const&) = default;

template <std::size_t Index, std::size_t End, typename...Args>
sak::internal::Project_Handle_Data_Part_Imp<flamingo::typelist<Args...>,Index,End>::Project_Handle_Data_Part_Imp(Project_Handle_Data_Part_Imp &&) = default;

template <std::size_t Index, std::size_t End, typename...Args>
sak::internal::Project_Handle_Data_Part_Imp<flamingo::typelist<Args...>,Index,End>& sak::internal::Project_Handle_Data_Part_Imp<flamingo::typelist<Args...>,Index,End>::operator=(Project_Handle_Data_Part_Imp &&) = default;

// Interface
//============================================================
// Access the handles for direct manipulation.
template <std::size_t Index, std::size_t End, typename...Args>
std::vector<typename sak::internal::Project_Handle_Data_Part_Imp<flamingo::typelist<Args...>,Index,End>::Handle_Type>& sak::internal::Project_Handle_Data_Part_Imp<flamingo::typelist<Args...>,Index,End>::get_raw_handles(Tag_Type&&)
{
  return m_handles;
}

template <std::size_t Index, std::size_t End, typename...Args>
std::vector<typename sak::internal::Project_Handle_Data_Part_Imp<flamingo::typelist<Args...>,Index,End>::Handle_Type> const& sak::internal::Project_Handle_Data_Part_Imp<flamingo::typelist<Args...>,Index,End>::cget_raw_handles(Tag_Type&&) const
{
  return m_handles;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Project_Raw_Handle_Data_Part_Imp<List, End, End>
//---------------------------------------------------------------------------
// For a type that isn't at the end of the list.

// Special 6
//============================================================
template <std::size_t End, typename...Args>
sak::internal::Project_Handle_Data_Part_Imp<flamingo::typelist<Args...>,End,End>::Project_Handle_Data_Part_Imp() :
  m_handles{}
{}

template <std::size_t End, typename...Args>
sak::internal::Project_Handle_Data_Part_Imp<flamingo::typelist<Args...>,End,End>::~Project_Handle_Data_Part_Imp() = default;

template <std::size_t End, typename...Args>
sak::internal::Project_Handle_Data_Part_Imp<flamingo::typelist<Args...>,End,End>::Project_Handle_Data_Part_Imp(Project_Handle_Data_Part_Imp const&) = default;

template <std::size_t End, typename...Args>
sak::internal::Project_Handle_Data_Part_Imp<flamingo::typelist<Args...>,End,End>& sak::internal::Project_Handle_Data_Part_Imp<flamingo::typelist<Args...>,End,End>::operator=(Project_Handle_Data_Part_Imp const&) = default;

template <std::size_t End, typename...Args>
sak::internal::Project_Handle_Data_Part_Imp<flamingo::typelist<Args...>,End,End>::Project_Handle_Data_Part_Imp(Project_Handle_Data_Part_Imp &&) = default;

template <std::size_t End, typename...Args>
sak::internal::Project_Handle_Data_Part_Imp<flamingo::typelist<Args...>,End,End>& sak::internal::Project_Handle_Data_Part_Imp<flamingo::typelist<Args...>,End,End>::operator=(Project_Handle_Data_Part_Imp &&) = default;

// Interface
//============================================================
// Access the handles for direct manipulation.
template <std::size_t End, typename...Args>
std::vector<typename sak::internal::Project_Handle_Data_Part_Imp<flamingo::typelist<Args...>,End,End>::Handle_Type>& sak::internal::Project_Handle_Data_Part_Imp<flamingo::typelist<Args...>,End,End>::get_raw_handles(Tag_Type&&)
{
  return m_handles;
}

template <std::size_t End, typename...Args>
std::vector<typename sak::internal::Project_Handle_Data_Part_Imp<flamingo::typelist<Args...>,End,End>::Handle_Type> const& sak::internal::Project_Handle_Data_Part_Imp<flamingo::typelist<Args...>,End,End>::cget_raw_handles(Tag_Type&&) const
{
  return m_handles;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Project_Raw_Handle_Data_Imp<T,Args...>
//---------------------------------------------------------------------------
// The bit that holds all of the Project data allowing access for layers that
// need all of it. This object does nothing whatsoever to enure that the data
// follows any rules, it merely hold it. This is mostly because the final
// layer imposes the rules on the data and is going to need all sorts of
// things in order to carry out operations like adding, removing and renaming
// handles and emitting the proper signals.

// Special 6
//============================================================
template <typename T, typename...Args>
sak::Project_Handle_Data_Imp<T,Args...>::Project_Handle_Data_Imp() = default;

template <typename T, typename...Args>
sak::Project_Handle_Data_Imp<T,Args...>::~Project_Handle_Data_Imp() = default;

template <typename T, typename...Args>
sak::Project_Handle_Data_Imp<T,Args...>::Project_Handle_Data_Imp(Project_Handle_Data_Imp const&) = default;

template <typename T, typename...Args>
sak::Project_Handle_Data_Imp<T,Args...>& sak::Project_Handle_Data_Imp<T,Args...>::operator=(Project_Handle_Data_Imp const&) = default;

template <typename T, typename...Args>
sak::Project_Handle_Data_Imp<T,Args...>::Project_Handle_Data_Imp(Project_Handle_Data_Imp &&) = default;

template <typename T, typename...Args>
sak::Project_Handle_Data_Imp<T,Args...>& sak::Project_Handle_Data_Imp<T,Args...>::operator=(Project_Handle_Data_Imp &&) = default;


namespace
{
  template <typename T>
  decltype(auto) do_find_handle_named(std::vector<sak::Handle<T>> const& a_handles, QString const& a_name)
  {
    return std::find_if(a_handles.cbegin(), a_handles.cend(), [&a_name](sak::Handle<T> const& a_handle) -> bool { return a_handle->cname() == a_name; });
  }

  template <typename T>
  bool do_has_handle_named(std::vector<sak::Handle<T>> const& a_handles, QString const& a_name)
  {
    return do_find_handle_named(a_handles, a_name) != a_handles.cend();
  }

  //---------------------------------------------------------------------------
  // Do_All_Handle_Count<T,Args...>
  //---------------------------------------------------------------------------
  // count how many of all things are managed by the project.
  template <typename T, typename...Args>
  class Do_All_Handle_Count
  {
  private:
    using Project_Typelist = flamingo::typelist<T,Args...>;
    using Project_Data_Type = sak::Project_Handle_Data_Imp<T,Args...>;

    template <std::size_t Index, std::size_t End = flamingo::typelist_size_v<Project_Typelist>>
    class Do_Loop
    {
      using Tag_Type = sak::Tag<flamingo::typelist_at_t<Project_Typelist,Index>>;
    public:
      void operator()(Project_Data_Type const* a_data, std::size_t& a_count)
      {
        a_count += a_data->cget_raw_handles(Tag_Type()).size();
        Do_Loop<Index+1,End>()(a_data,a_count);
      }
    };
    template <std::size_t End>
    class Do_Loop<End,End>
    {
    public:
      void operator()(Project_Data_Type const*, std::size_t&)
      {
      }
    };

  public:
    std::size_t operator()(Project_Data_Type const* a_data) const
    {
      std::size_t l_result{0};
      Do_Loop<0>()(a_data, l_result);
      return l_result;
    }
  };

  //---------------------------------------------------------------------------
  // Do_Has_Name<T,Args...>
  //---------------------------------------------------------------------------
  template <typename T, typename...Args>
  class Do_Has_Name
  {
  private:
    using Project_Typelist = flamingo::typelist<T,Args...>;
    using Project_Data_Type = sak::Project_Handle_Data_Imp<T,Args...>;

    template <std::size_t Index, std::size_t End = flamingo::typelist_size_v<Project_Typelist>>
    class Do_Loop
    {
      using Tag_Type = sak::Tag<flamingo::typelist_at_t<Project_Typelist,Index>>;
    public:
      bool operator()(Project_Data_Type const* a_data, QString const& a_name) const
      {
        if (do_has_handle_named(a_data->cget_raw_handles(Tag_Type()),a_name))
        {
          return true;
        }
        return Do_Loop<Index+1,End>()(a_data, a_name);
      }
    };

    // Recusion stops at the end.
    template <std::size_t End>
    class Do_Loop<End,End>
    {
    public:
      bool operator()(Project_Data_Type const*, QString const&) const
      {
        return false;
      }
    };

  public:
    bool operator()(Project_Data_Type const* a_data, QString const& a_name) const
    {
      // Check all the data sections. If name is found then it returns true.
      // If it reaches the end then it returns false.
      return Do_Loop<0>()(a_data, a_name);
    }
  };

  //---------------------------------------------------------------------------
  // Do_Get_All_Names<T,Args...>
  //---------------------------------------------------------------------------
  template <typename T, typename...Args>
  class Do_Get_All_Names
  {
  private:
    using Project_Typelist = flamingo::typelist<T,Args...>;
    using Project_Data_Type = sak::Project_Handle_Data_Imp<T,Args...>;

    template <std::size_t Index, std::size_t End = flamingo::typelist_size_v<Project_Typelist>>
    class Do_Loop
    {
      using Tag_Type = sak::Tag<flamingo::typelist_at_t<Project_Typelist,Index>>;
    public:
      void operator()(Project_Data_Type const* a_data, std::vector<QString>& a_result) const
      {
        // Go through all the handles for this section
        for (auto const& l_handle : a_data->cget_raw_handles(Tag_Type()))
        {
          // and add the name to the result.
          a_result.push_back(l_handle->cname());
        }
        // Then recurse
        Do_Loop<Index+1,End>()(a_data, a_result);
      }
    };

    // Recusion stops at the end.
    template <std::size_t End>
    class Do_Loop<End,End>
    {
    public:
      void operator()(Project_Data_Type const*, std::vector<QString>&) const
      {
      }
    };

  public:
    std::vector<QString> operator()(Project_Data_Type const* a_data) const
    {
      // Where we shall put the results.
      std::vector<QString> l_result{};
      // Reserve a number equal to the count to prevent multiple allocations.
      l_result.reserve(Do_All_Handle_Count<T,Args...>()(a_data));
      // Get names for each type and add them to the result
      Do_Loop<0>()(a_data, l_result);

      return l_result;
    }
  };
}

// Interface
//============================================================
// Does this name appear in the data?
template <typename T, typename...Args>
bool sak::Project_Handle_Data_Imp<T,Args...>::has_name(QString const& a_name) const
{
  return Do_Has_Name<T,Args...>()(this,a_name);
}

// Get all the objects names in alphabetical order. The true
// types that are associated with the names are ignored.
template <typename T, typename...Args>
std::vector<QString> sak::Project_Handle_Data_Imp<T,Args...>::get_all_names() const
{
 return Do_Get_All_Names<T,Args...>()(this);
}

// Alter the supplied name so that it is unique among the
// existing data names.
template <typename T, typename...Args>
void sak::Project_Handle_Data_Imp<T,Args...>::fix_name(QString& a_name) const
{
  auto l_names = Do_Get_All_Names<T,Args...>()(this);
  std::sort(l_names.begin(), l_names.end());
  uniqueify_name(a_name, l_names);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
template class sak::internal::Project_Handle_Data_Part_Imp<sak::Project_Typelist,0,2>;
template class sak::internal::Project_Handle_Data_Part_Imp<sak::Project_Typelist,1,2>;
template class sak::internal::Project_Handle_Data_Part_Imp<sak::Project_Typelist,2,2>;

template class sak::Project_Handle_Data;
