#include "project_handle_data.hpp"

#include "data_definitions.hpp"
#include "class_definitions.hpp"
#include "data.hpp"
#include "handle.hpp"
#include "tag.hpp"
#include "name_utilities.hpp"

#include <algorithm>
#include <limits>
#include <iterator>
#include <cassert>
#include <type_traits>

#include <QString>

namespace sak
{
  namespace
  {
    template <typename T>
    decltype(auto) do_find_handle(std::vector<Handle<T>> const& a_handles, Handle<T> const& a_handle)
    {
      return std::find(a_handles.cbegin(), a_handles.cend(), a_handle);
    }

    template <typename T>
    bool do_has_handle(std::vector<Handle<T>> const& a_handles, Handle<T> const& a_handle)
    {
      return do_find_handle(a_handles, a_handle) != a_handles.cend();
    }

    template <typename T>
    std::size_t do_index_of_handle(std::vector<Handle<T>> const& a_handles, Handle<T> const& a_handle)
    {
      auto l_found = do_find_handle(a_handles,a_handle);
      if (l_found != a_handles.cend())
      {
        return static_cast<std::size_t>(std::distance(a_handles.cbegin(),l_found));
      }
      else
      {
        return a_handles.size();
      }
    }

    template <typename T>
    decltype(auto) do_find_handle_named(std::vector<Handle<T>> const& a_handles, QString const& a_name)
    {
      return std::find_if(a_handles.cbegin(), a_handles.cend(), [&a_name](Handle<T> const& a_handle) -> bool { return a_handle->cname() == a_name; });
    }

    template <typename T>
    bool do_has_handle_named(std::vector<Handle<T>> const& a_handles, QString const& a_name)
    {
      return do_find_handle_named(a_handles, a_name) != a_handles.cend();
    }

    template <typename T>
    decltype(auto) do_find_handle_id(std::vector<Handle<T>> const& a_handles, ID<T> const& a_id)
    {
      return std::find_if(a_handles.cbegin(), a_handles.cend(), [&a_id](Handle<T> const& a_handle) -> bool { return a_handle.id() == a_id; });
    }

    template <typename T>
    bool do_has_handle_id(std::vector<Handle<T>> const& a_handles, ID<T> const& a_id)
    {
      return do_find_handle_id(a_handles, a_id) != a_handles.cend();
    }

    template <typename T>
    std::size_t do_index_of_id(std::vector<Handle<T>> const& a_handles, ID<T> const& a_id)
    {
      auto l_found = do_find_handle_id(a_handles,a_id);
      if (l_found != a_handles.cend())
      {
        return static_cast<std::size_t>(std::distance(a_handles.cbegin(),l_found));
      }
      else
      {
        return a_handles.size();
      }
    }

    template <typename T>
    QString do_name_of_id(std::vector<Handle<T>> const& a_handles, ID<T> const& a_id)
    {
      auto l_found = do_find_handle_id(a_handles,a_id);
      if (l_found != a_handles.cend())
      {
        return (*l_found)->cname();
      }
      else
      {
        return QString{};
      }
    }

    // get an iterator where handle is to be inserted in order to maintain alphabetic sorting by name.
    template <typename T>
    decltype(auto) do_find_name_position(std::vector<Handle<T>> const& a_handles, QString const& a_name)
    {
      if (!a_name.isEmpty() && !do_has_handle_named(a_handles,a_name))
      {
        // find the first handle with a name greater than this one
        return std::find_if(a_handles.cbegin(), a_handles.cend(), [&a_name](Handle<T> const& a_handle) -> bool { return a_handle->cname() > a_name; });
      }
      else
      {
        return a_handles.cend();
      }
    }
  }
}


//---------------------------------------------------------------------------
// Section_Handle_Data_Imp<List, Index, End>
//---------------------------------------------------------------------------
// For a type that isn't at the end of the list.

// Special 6
//============================================================
template <std::size_t Index, std::size_t End, typename...Args>
sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index,End>::Section_Handle_Data_Imp() :
  Inh(),
  m_handles{}
{}

template <std::size_t Index, std::size_t End, typename...Args>
sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index,End>::~Section_Handle_Data_Imp() = default;

template <std::size_t Index, std::size_t End, typename...Args>
sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index,End>::Section_Handle_Data_Imp(Section_Handle_Data_Imp const&) = default;

template <std::size_t Index, std::size_t End, typename...Args>
sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index,End>& sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index,End>::operator=(Section_Handle_Data_Imp const&) = default;

template <std::size_t Index, std::size_t End, typename...Args>
sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index,End>::Section_Handle_Data_Imp(Section_Handle_Data_Imp &&) = default;

template <std::size_t Index, std::size_t End, typename...Args>
sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index,End>& sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index,End>::operator=(Section_Handle_Data_Imp &&) = default;

// Interface
//============================================================
// User Interface
//------------------------------------------------------------
// This part will get used by the interface implementor.

// Are there any objects in this Project?
template <std::size_t Index, std::size_t End, typename...Args>
bool sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index,End>::is_empty(Tag_Type&&) const
{
  return m_handles.empty();
}

// How many objects are in this Project?
template <std::size_t Index, std::size_t End, typename...Args>
std::size_t sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index,End>::count(Tag_Type&&) const
{
  return m_handles.size();
}

// Does this handle appear in the data?
template <std::size_t Index, std::size_t End, typename...Args>
bool sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index,End>::has(ID_Type const& a_id) const
{
  return do_has_handle_id(m_handles,a_id);
}

// Get the index of the id in the data. If the id is not present or is null,
// the returned value is equal to count().
template <std::size_t Index, std::size_t End, typename...Args>
std::size_t sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index,End>::index(ID_Type const& a_id) const
{
  return do_index_of_id(m_handles,a_id);
}

// Get the name data associted with this id. If the id is not present or is null,
// the returned value is empty.
template <std::size_t Index, std::size_t End, typename...Args>
QString sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index,End>::name(ID_Type const& a_id) const
{
  return do_name_of_id(m_handles,a_id);
}

// Does this name appear in the data?
template <std::size_t Index, std::size_t End, typename...Args>
bool sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index,End>::has_name(Tag_Type&&, QString const& a_name) const
{
  return do_has_handle_named(m_handles,a_name);
}

// Get the handle at this index. If the index is invalid a null handle is returned.
template <std::size_t Index, std::size_t End, typename...Args>
typename sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index,End>::ID_Type sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index,End>::get_at(Tag_Type&&, std::size_t a_index) const
{
  if (a_index < m_handles.size())
  {
    return m_handles.at(a_index).id();
  }
  else
  {
    return ID_Type{};
  }
}

// Get the handle with this name. If the name is invalid a null handle is returned.
template <std::size_t Index, std::size_t End, typename...Args>
typename sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index,End>::ID_Type sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index,End>::get_named(Tag_Type&&, QString const& a_name) const
{
  auto l_found = do_find_handle_named(m_handles,a_name);
  if (l_found != m_handles.cend())
  {
    return l_found->id();
  }
  else
  {
    return ID_Type{};
  }
}

// Get the handles names in data order
template <std::size_t Index, std::size_t End, typename...Args>
std::vector<typename sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index,End>::ID_Type> sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index,End>::get_ids(Tag_Type&&) const
{
  std::vector<ID_Type> l_result{};
  l_result.reserve(m_handles.size());
  for (auto const& l_handle : m_handles)
  {
    l_result.push_back(l_handle.id());
  }
  return l_result;
}

// Get the handles names in data order
template <std::size_t Index, std::size_t End, typename...Args>
std::vector<QString> sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index,End>::get_names(Tag_Type&&) const
{
  std::vector<QString> l_result{};
  l_result.reserve(m_handles.size());
  for (auto const& l_handle : m_handles)
  {
    l_result.push_back(l_handle->cname());
  }
  return l_result;
}

// Internal Interface
//------------------------------------------------------------
// This part will get used by the data implementor.

// Does this handle appear in the data?
template <std::size_t Index, std::size_t End, typename...Args>
bool sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index,End>::has_handle(Handle_Type const& a_handle) const
{
  return do_has_handle(m_handles,a_handle);
}

// Get the handle for this id. If the id is invalid or null a null handle is returned.
template <std::size_t Index, std::size_t End, typename...Args>
typename sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index,End>::Handle_Type sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index,End>::get_handle(ID_Type const& a_id) const
{
  auto l_found = do_find_handle_id(m_handles,a_id);
  if (l_found != m_handles.cend())
  {
    return *l_found;
  }
  else
  {
    return Handle_Type{};
  }
}

// Get the handle at this index. If the index is invalid a null handle is returned.
template <std::size_t Index, std::size_t End, typename...Args>
typename sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index,End>::Handle_Type sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index,End>::get_handle_at(Tag_Type&&, std::size_t a_index) const
{
  if (a_index < m_handles.size())
  {
    return m_handles.at(a_index);
  }
  else
  {
    return Handle_Type{};
  }
}

// Get the handle with this name. If the name is invalid a null handle is returned.
template <std::size_t Index, std::size_t End, typename...Args>
typename sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index,End>::Handle_Type sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index,End>::get_handle_named(Tag_Type&&, QString const& a_name) const
{
  auto l_found = do_find_handle_named(m_handles,a_name);
  if (l_found != m_handles.cend())
  {
    return *l_found;
  }
  else
  {
    return Handle_Type{};
  }
}

// Determine what index this handle would be at if it were added to the current data.
// If the handle is null or already present, the result is count(). This is the same
// as the value returned by add, but nothing is added.
template <std::size_t Index, std::size_t End, typename...Args>
std::size_t sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index,End>::future_index(QString const& a_name) const
{
  // Advance an iterator from the start of handles to the position that the first handle
  // with a name greater than the supplied one is found.
  return static_cast<std::size_t>(std::distance(m_handles.cbegin(), do_find_name_position(m_handles, a_name)));
}

// Add a handle to the collection and return its index. If the handle is null or
// already present, nothing happens and return count().
template <std::size_t Index, std::size_t End, typename...Args>
std::size_t sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index,End>::add(Handle_Type const& a_handle)
{
  // If the handle is not null, not present in the data, and has a non-empty name
  if (a_handle && !has_handle(a_handle) && !a_handle->cname().isEmpty())
  {
    auto l_iter = m_handles.insert(do_find_name_position(m_handles, a_handle->cname()),a_handle);
    return static_cast<std::size_t>(std::distance(m_handles.begin(), l_iter));
  }
  else
  {
    return m_handles.size();
  }
}

// Remove the handle at this index from the collection and return true. If the handle
// is null or not present, nothing happens and return false.
template <std::size_t Index, std::size_t End, typename...Args>
bool sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index,End>::remove(Tag_Type&&, std::size_t a_index)
{
  if (a_index < m_handles.size())
  {
    auto l_iter = m_handles.begin();
    std::advance(l_iter, a_index);
    m_handles.erase(l_iter);
    return true;
  }
  else
  {
    return false;
  }
}

// Access the handles for direct manipulation.
template <std::size_t Index, std::size_t End, typename...Args>
std::vector<typename sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index,End>::Handle_Type>& sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index,End>::get_handles(Tag_Type&&)
{
  return m_handles;
}

template <std::size_t Index, std::size_t End, typename...Args>
std::vector<typename sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index,End>::Handle_Type> const& sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,Index,End>::cget_handles(Tag_Type&&) const
{
  return m_handles;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Section_Handle_Data_Imp<List, End, End>
//---------------------------------------------------------------------------
// For a type that isn't at the end of the list.

// Special 6
//============================================================
template <std::size_t End, typename...Args>
sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,End,End>::Section_Handle_Data_Imp() = default;

template <std::size_t End, typename...Args>
sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,End,End>::~Section_Handle_Data_Imp() = default;

template <std::size_t End, typename...Args>
sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,End,End>::Section_Handle_Data_Imp(Section_Handle_Data_Imp const&) = default;

template <std::size_t End, typename...Args>
sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,End,End>& sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,End,End>::operator=(Section_Handle_Data_Imp const&) = default;

template <std::size_t End, typename...Args>
sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,End,End>::Section_Handle_Data_Imp(Section_Handle_Data_Imp &&) = default;

template <std::size_t End, typename...Args>
sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,End,End>& sak::Section_Handle_Data_Imp<flamingo::typelist<Args...>,End,End>::operator=(Section_Handle_Data_Imp &&) = default;

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Project_Handle_Data_Imp<T,Args...>
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
        a_count += a_data->cget_handles(Tag_Type()).size();
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
        if (do_has_handle_named(a_data->cget_handles(Tag_Type()),a_name))
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
        for (auto const& l_handle : a_data->cget_handles(Tag_Type()))
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

namespace
{
  // Take the supplied name and alter it as necessary to be unique among the names that
  // are already in the supplied vector.
  void uniqueify_name(QString& a_name, std::vector<QString> const& a_names)
  {
    auto l_name_found = std::find(a_names.cbegin(), a_names.cend(), a_name);

    // if it wasn't found we can use it
    if (l_name_found != a_names.cend())
    {
      // append a number to the name and test it and keep doing this until we get to one we haven't found.
      for (int l_postfix = 1, l_end = std::numeric_limits<int>::max(); l_postfix != l_end; ++l_postfix)
      {
        QString l_fixed_name{a_name};
        l_fixed_name.append(QString::number(l_postfix));
        if (std::find(a_names.cbegin(), a_names.cend(), l_fixed_name) == a_names.end())
        {
          a_name = l_fixed_name;
          break;
        }
      }
    }
  }
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
template class sak::Section_Handle_Data_Imp<sak::Project_Typelist,0,3>;
template class sak::Section_Handle_Data_Imp<sak::Project_Typelist,1,3>;
template class sak::Section_Handle_Data_Imp<sak::Project_Typelist,2,3>;
template class sak::Section_Handle_Data_Imp<sak::Project_Typelist,3,3>;

template class sak::Project_Handle_Data;
