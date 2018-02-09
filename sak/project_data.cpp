#include "project_data.hpp"

#include "data_definitions.hpp"
#include "class_definitions.hpp"
#include "data.hpp"
#include "handle.hpp"
#include "handle_factory.hpp"
#include "tag.hpp"
#include "abstract_project_signalbox.hpp"
#include "name_utilities.hpp"

#include <cassert>
#include <algorithm>
#include <iterator>
#include <type_traits>

#include <QString>
#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>

namespace
{
  template <typename T>
  decltype(auto) do_find_handle(std::vector<sak::Handle<T>> const& a_handles, sak::Handle<T> const& a_handle)
  {
    return std::find(a_handles.cbegin(), a_handles.cend(), a_handle);
  }

  template <typename T>
  bool do_has_handle(std::vector<sak::Handle<T>> const& a_handles, sak::Handle<T> const& a_handle)
  {
    return do_find_handle(a_handles, a_handle) != a_handles.cend();
  }


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
}

//---------------------------------------------------------------------------
// Project_Data_Section_Data_Imp<T,Args...>
//---------------------------------------------------------------------------
// Implement the data members for all the sections so that the part that
// implements the interface can access all of the different handle types.

// Special 6
//============================================================
template <typename T>
sak::Project_Data_Section_Data_Imp<T>::Project_Data_Section_Data_Imp():
  m_handles{}
{}

template <typename T>
sak::Project_Data_Section_Data_Imp<T>::~Project_Data_Section_Data_Imp() = default;

template <typename T>
sak::Project_Data_Section_Data_Imp<T>::Project_Data_Section_Data_Imp(Project_Data_Section_Data_Imp &&) = default;

template <typename T>
sak::Project_Data_Section_Data_Imp<T>& sak::Project_Data_Section_Data_Imp<T>::operator=(Project_Data_Section_Data_Imp &&) = default;

template <typename T>
std::vector<sak::Handle<T>>& sak::Project_Data_Section_Data_Imp<T>::imp_handles(Tag<T>&&)
{
  return m_handles;
}

template <typename T>
std::vector<sak::Handle<T>> const& sak::Project_Data_Section_Data_Imp<T>::cimp_handles(Tag<T>&&) const
{
  return m_handles;
}



//---------------------------------------------------------------------------
// Project_Data_Shared_Imp<T,Args...>
//---------------------------------------------------------------------------
// Implement the parts that the data sections will depend on via virtual
// inheritance.

// Special 6
//============================================================
template <typename T, typename...Args>
sak::Project_Data_Shared_Imp<T,Args...>::Project_Data_Shared_Imp():
  m_next_id{0}
{}

template <typename T, typename...Args>
sak::Project_Data_Shared_Imp<T,Args...>::~Project_Data_Shared_Imp() = default;

template <typename T, typename...Args>
sak::Project_Data_Shared_Imp<T,Args...>::Project_Data_Shared_Imp(Project_Data_Shared_Imp &&) = default;

template <typename T, typename...Args>
sak::Project_Data_Shared_Imp<T,Args...>& sak::Project_Data_Shared_Imp<T,Args...>::operator=(Project_Data_Shared_Imp &&) = default;

// Interface
//============================================================

namespace
{
  //---------------------------------------------------------------------------
  // Do_All_Handle_Count<T,Args...>
  //---------------------------------------------------------------------------
  // count how many of all things are managed by the project.
  template <typename T, typename...Args>
  class Do_All_Handle_Count
  {
  private:
    using Project_Typelist = flamingo::typelist<T,Args...>;
    using Project_Data_Type = sak::Project_Data_Shared_Imp<T,Args...>;

    template <std::size_t Index, std::size_t End = flamingo::typelist_size_v<Project_Typelist>>
    class Do_Loop
    {
      using Tag_Type = sak::Tag<flamingo::typelist_at_t<Project_Typelist,Index>>;
    public:
      void operator()(Project_Data_Type const* a_data, std::size_t& a_count)
      {
        a_count += a_data->cimp_handles(Tag_Type()).size();
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
    using Project_Data_Type = sak::Project_Data_Shared_Imp<T,Args...>;

    template <std::size_t Index, std::size_t End = flamingo::typelist_size_v<Project_Typelist>>
    class Do_Loop
    {
      using Tag_Type = sak::Tag<flamingo::typelist_at_t<Project_Typelist,Index>>;
    public:
      bool operator()(Project_Data_Type const* a_data, QString const& a_name) const
      {
        if (do_has_handle_named(a_data->cimp_handles(Tag_Type()),a_name))
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
    using Project_Data_Type = sak::Project_Data_Shared_Imp<T,Args...>;

    template <std::size_t Index, std::size_t End = flamingo::typelist_size_v<Project_Typelist>>
    class Do_Loop
    {
      using Tag_Type = sak::Tag<flamingo::typelist_at_t<Project_Typelist,Index>>;
    public:
      void operator()(Project_Data_Type const* a_data, std::vector<QString>& a_result) const
      {
        // Go through all the handles for this section
        for (auto const& l_handle : a_data->cimp_handles(Tag_Type()))
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

// Does this name appear in the data?
template <typename T, typename...Args>
bool sak::Project_Data_Shared_Imp<T,Args...>::has_name(QString const& a_name) const
{
  return Do_Has_Name<T,Args...>()(this,a_name);
}

// Get all the objects names in data order
template <typename T, typename...Args>
std::vector<QString> sak::Project_Data_Shared_Imp<T,Args...>::get_all_names() const
{
  return Do_Get_All_Names<T,Args...>()(this);
}

// Alter the supplied name so that it is unique among the existing data names
template <typename T, typename...Args>
void sak::Project_Data_Shared_Imp<T,Args...>::fix_name(QString& a_name) const
{
  auto l_names = this->get_all_names();
  std::sort(l_names.begin(), l_names.end());
  uniqueify_name(a_name, l_names);
}

// Internal Interface
//============================================================
// Get the next id for making handles.
template <typename T, typename...Args>
std::size_t sak::Project_Data_Shared_Imp<T,Args...>::next_id() const
{
  ++m_next_id;
  assert(m_next_id != 0);
  return m_next_id;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------
// Project_Data_Section_Imp<List,T,Args...>
//---------------------------------------------------------------------------
// Implement the data sections via a recursive template. Each argument
// uses Project_Data_Shared_Imp via virtual inheritance.

// Special 6
//============================================================
template <typename T_List, typename T>
sak::Project_Data_Section_Imp<T_List,T>::Project_Data_Section_Imp():
  Base()
{}

template <typename T_List, typename T>
sak::Project_Data_Section_Imp<T_List,T>::~Project_Data_Section_Imp() = default;

template <typename T_List, typename T>
sak::Project_Data_Section_Imp<T_List,T>::Project_Data_Section_Imp(Project_Data_Section_Imp &&) = default;

template <typename T_List, typename T>
sak::Project_Data_Section_Imp<T_List,T>& sak::Project_Data_Section_Imp<T_List,T>::operator=(Project_Data_Section_Imp &&) = default;

// Public Interface
//============================================================
// Are there any handles of this type in the currently active project data?
template <typename T_List, typename T>
bool sak::Project_Data_Section_Imp<T_List,T>::empty(Tag<T>&&) const
{
  return cimp_handles(Tag<T>()).empty();
}

// How handles of this type in the currently active project data?
template <typename T_List, typename T>
std::size_t sak::Project_Data_Section_Imp<T_List,T>::count(Tag<T>&&) const
{
  return cimp_handles(Tag<T>()).size();
}

// Is this handle in the currently active project data?
template <typename T_List, typename T>
bool sak::Project_Data_Section_Imp<T_List,T>::has_handle(Handle<T> const& a_handle) const
{
  if (not_null(a_handle))
  {
    // search for the handle in the active handles.
    return do_find_handle(cimp_handles(Tag<T>()), a_handle) != cimp_handles(Tag<T>()).cend();
  }
  else
  {
    // null handles are always inactive
    return false;
  }
}

// Is this handle in the currently active project data?
template <typename T_List, typename T>
bool sak::Project_Data_Section_Imp<T_List,T>::has_handle_named(Tag<T>&&, QString const& a_name) const
{
  return do_find_handle_named(cimp_handles(Tag<T>()),a_name) != cimp_handles(Tag<T>()).cend();
}

// Get the handle at this index. Handles are sorted alphabetically by the name
// member of the objects they reference.
template <typename T_List, typename T>
sak::Handle<T> sak::Project_Data_Section_Imp<T_List,T>::get_handle_at(Tag<T>&&, std::size_t a_index) const
{
  if (a_index < cimp_handles(Tag<T>()).size())
  {
    return cimp_handles(Tag<T>()).at(a_index);
  }
  else
  {
    return Handle<T>{};
  }
}

// Get the handle with this name. If the name is invalid a null handle is returned.
template <typename T_List, typename T>
sak::Handle<T> sak::Project_Data_Section_Imp<T_List,T>::get_handle_named(Tag<T>&&, QString const& a_name) const
{
  auto l_found = do_find_handle_named(cimp_handles(Tag<T>()), a_name);
  if (l_found != cimp_handles(Tag<T>()).cend())
  {
    return *l_found;
  }
  return Handle<T>{};
}
// Get all the handles alphabetically sorted by name
template <typename T_List, typename T>
std::vector<sak::Handle<T>> const& sak::Project_Data_Section_Imp<T_List,T>::get_handles(Tag<T>&&) const
{
  return cimp_handles(Tag<T>());
}

// Get all the objects' alphabetically sorted names
template <typename T_List, typename T>
std::vector<QString> sak::Project_Data_Section_Imp<T_List,T>::get_names(Tag<T>&&) const
{
  std::vector<QString> l_result{};
  l_result.reserve(cimp_handles(Tag<T>()).size());
  for (auto const& l_handle : cimp_handles(Tag<T>()))
  {
    l_result.push_back(l_handle->cname());
  }
  return l_result;
}

// You may create new objects using these two functions. Objects created in this way
// are part of the data management system but nothing outside of it has been notified
// of their presense. Calling has_handle on the handle returned by these functions
// immediately after will return false.

// Make a new object using the supplied data. Project's data management system owns it but
// it is not part of the Project.
template <typename T_List, typename T>
sak::Handle<T> sak::Project_Data_Section_Imp<T_List,T>::make_emplace(Data<T>&& a_object) const
{
  // Capture the data
  auto l_object = std::make_shared<Data<T>>(std::move(a_object));

  // Alter it's name if it needs to be
  fix_name(l_object->name());

  // Make a handle out of the data.
  return Handle<T>{std::move(l_object),this->next_id()};
}

// Make a new file using the default parameters. Project's data management system owns it
// but it is not part of the Project.
template <typename T_List, typename T>
sak::Handle<T> sak::Project_Data_Section_Imp<T_List,T>::make_default(Tag<T>&&) const
{
  using Typestring_Type = typename T::Typestring_Type;
  // The default name for a new object.
  static QString const s_name{u8"New " + QString::fromStdString(Typestring_Type::data())};

  // Use make_emplace with data that has the default name
  return make_emplace(Data<T>{s_name});
}

// Attempt to add a handle to the data and return true if it succeeds. Will
// fail and return false if the handle is null or already present in the data.
template <typename T_List, typename T>
bool sak::Project_Data_Section_Imp<T_List,T>::add(Handle<T> const& a_handle)
{
  // If the handle is already in the project, don't add it
  if (!has_handle(a_handle))
  {
    // Alter it's name if it needs to be
    fix_name(a_handle->name());

    // Add it to the collection
    imp_handles(Tag<T>()).push_back(a_handle);
    return true;
  }
  return false;
}

// Attempt to remove a handle from the data and return true if it succeeds. Will
// fail and return false if the handle is null or not present in the data.
template <typename T_List, typename T>
bool sak::Project_Data_Section_Imp<T_List,T>::remove(Handle<T> const& a_handle)
{
  if (has_handle(a_handle))
  {
    auto l_found = do_find_handle(cimp_handles(Tag<T>()), a_handle);
    if (l_found != cimp_handles(Tag<T>()).cend())
    {
      imp_handles(Tag<T>()).erase(l_found);
      return true;
    }
  }
  return false;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Project_Data_Imp<T,Args...>
//---------------------------------------------------------------------------
// The top of the project data implements the parts of the project that are
// independent of all else (e.g. filename) and also the parts that require
// all the data sections (e.g. fix_name).

template <typename T, typename...Args>
sak::Project_Data_Imp<T,Args...>::Project_Data_Imp(QString const& a_filepath) :
  Inh(),
  m_filepath{a_filepath}
{}

template <typename T, typename...Args>
sak::Project_Data_Imp<T,Args...>::~Project_Data_Imp() = default;

template <typename T, typename...Args>
sak::Project_Data_Imp<T,Args...>::Project_Data_Imp(Project_Data_Imp &&) = default;

template <typename T, typename...Args>
sak::Project_Data_Imp<T,Args...>& sak::Project_Data_Imp<T,Args...>::operator=(Project_Data_Imp &&) = default;

template <typename T, typename...Args>
QString sak::Project_Data_Imp<T,Args...>::name() const
{
  return m_filepath.baseName();
}

template <typename T, typename...Args>
QString sak::Project_Data_Imp<T,Args...>::location() const
{
  return m_filepath.absolutePath();
}

template <typename T, typename...Args>
QString sak::Project_Data_Imp<T,Args...>::filepath() const
{
  return m_filepath.absoluteFilePath();
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

template class sak::Project_Data_Section_Data_Imp<sak::File_Definition,sak::Texture_Definition, sak::Material_Definition>;
template class sak::Project_Data_Shared_Imp<sak::File_Definition,sak::Texture_Definition, sak::Material_Definition>;
template class sak::Project_Data_Section_Imp<sak::Project_Typelist,sak::File_Definition>;
template class sak::Project_Data_Section_Imp<sak::Project_Typelist,sak::Texture_Definition>;
template class sak::Project_Data_Section_Imp<sak::Project_Typelist,sak::Material_Definition>;

template class sak::Project_Data;
