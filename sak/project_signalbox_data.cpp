#include "project_signalbox_data.hpp"

#include "abstract_project_signalbox.hpp"
#include "signal_source.hpp"

namespace sak
{
  namespace
  {
    //---------------------------------------------------------------------------
    // Do_Signalboxes<T_Signalbox, T>
    //---------------------------------------------------------------------------
    // Implement the functionality in one place rather than twice.
    template <typename T_Signalbox, typename T>
    class Do_Signalboxes
    {
    public:
      // When a handle has been added at a given index.
      static void added(Signal_Source a_source, std::vector<T_Signalbox*>& a_signalboxes, Handle<T> const& a_handle, std::size_t a_index)
      {
        for (auto l_item : a_signalboxes)
        {
          l_item->added(a_source, a_handle, a_index);
        }
      }

      // When a handle has been removed from a given index.
      static void removed(Signal_Source a_source, std::vector<T_Signalbox*>& a_signalboxes, Handle<T> const& a_handle, std::size_t a_index)
      {
        for (auto l_item : a_signalboxes)
        {
          l_item->removed(a_source, a_handle, a_index);
        }
      }

      // When a handle at a given index has been moved to another index.
      static void moved(Signal_Source a_source, std::vector<T_Signalbox*>& a_signalboxes, Handle<T> const& a_handle, std::size_t a_from,  std::size_t a_to)
      {
        for (auto l_item : a_signalboxes)
        {
          l_item->moved(a_source, a_handle, a_from, a_to);
        }
      }

      // When a handle at a given index has its name changed.
      static void changed_name(Signal_Source a_source, std::vector<T_Signalbox*>& a_signalboxes, Handle<T> const& a_handle, std::size_t a_index)
      {
        for (auto l_item : a_signalboxes)
        {
          l_item->changed_name(a_source, a_handle, a_index);
        }
      }

      // When a handle at a given index has all of its data changed.
      static void changed_data(Signal_Source a_source, std::vector<T_Signalbox*>& a_signalboxes, Handle<T> const& a_handle, std::size_t a_index)
      {
        for (auto l_item : a_signalboxes)
        {
          l_item->changed_data(a_source, a_handle, a_index);
        }
      }

      // When a handle at a given index has its data changed in a specific place.
      static void changed_data_at(Signal_Source a_source, std::vector<T_Signalbox*>& a_signalboxes, Handle<T> const& a_handle, std::size_t a_index, std::size_t a_member)
      {
        for (auto l_item : a_signalboxes)
        {
          l_item->changed_data_at(a_source, a_handle, a_index, a_member);
        }
      }

      // When a handle at a given index requests its editor be opened/brought to the top.
      static void requests_editor(Signal_Source a_source, std::vector<T_Signalbox*>& a_signalboxes, Handle<T> const& a_handle, std::size_t a_index)
      {
        for (auto l_item : a_signalboxes)
        {
          l_item->requests_editor(a_source, a_handle, a_index);
        }
      }

      // When a handle at a given index requests focus in the outliner.
      static void requests_outliner(Signal_Source a_source, std::vector<T_Signalbox*>& a_signalboxes, Handle<T> const& a_handle, std::size_t a_index)
      {
        for (auto l_item : a_signalboxes)
        {
          l_item->requests_outliner(a_source, a_handle, a_index);
        }
      }
    };

    template <typename T>
    decltype(auto) do_find_signalbox(std::vector<T*> const& a_vector, T* a_value)
    {
      return std::find(a_vector.cbegin(), a_vector.cend(), a_value);
    }

    template <typename T>
    bool do_has_signalbox(std::vector<T*> const& a_vector, T* a_value)
    {
      return do_find_signalbox(a_vector,a_value) != a_vector.cend();
    }

  }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Project_Signalbox_Data_Part_Imp<List, Index, End>
//---------------------------------------------------------------------------
// For a type that isn't at the end of the list.

template <std::size_t Index, std::size_t End, typename...Args>
sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,Index,End>::Project_Signalbox_Data_Part_Imp() = default;

template <std::size_t Index, std::size_t End, typename...Args>
sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,Index,End>::~Project_Signalbox_Data_Part_Imp() = default;

template <std::size_t Index, std::size_t End, typename...Args>
sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,Index,End>::Project_Signalbox_Data_Part_Imp(Project_Signalbox_Data_Part_Imp const&) = default;

template <std::size_t Index, std::size_t End, typename...Args>
sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,Index,End>& sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,Index,End>::operator=(Project_Signalbox_Data_Part_Imp const&) = default;

template <std::size_t Index, std::size_t End, typename...Args>
sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,Index,End>::Project_Signalbox_Data_Part_Imp(Project_Signalbox_Data_Part_Imp &&) = default;

template <std::size_t Index, std::size_t End, typename...Args>
sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,Index,End>& sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,Index,End>::operator=(Project_Signalbox_Data_Part_Imp &&) = default;

// Interface
//============================================================
// calls each of these on all the stored signalboxes.

// When a handle has been added at a given index.
template <std::size_t Index, std::size_t End, typename...Args>
void sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,Index,End>::added(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index)
{
  Do_Signalboxes<Signalbox_Type,Type>::added(a_source, get_signalboxes(), a_handle, a_index);
}

// When a handle has been removed from a given index.
template <std::size_t Index, std::size_t End, typename...Args>
void sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,Index,End>::removed(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index)
{
  Do_Signalboxes<Signalbox_Type,Type>::removed(a_source, get_signalboxes(), a_handle, a_index);
}

// When a handle at a given index has been moved to another index.
template <std::size_t Index, std::size_t End, typename...Args>
void sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,Index,End>::moved(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_from, std::size_t a_to)
{
  Do_Signalboxes<Signalbox_Type,Type>::moved(a_source, get_signalboxes(), a_handle, a_from, a_to);
}

// When a handle at a given index has its name changed.
template <std::size_t Index, std::size_t End, typename...Args>
void sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,Index,End>::changed_name(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index)
{
  Do_Signalboxes<Signalbox_Type,Type>::changed_name(a_source, get_signalboxes(), a_handle, a_index);
}

// When a handle at a given index has all of its data changed.
template <std::size_t Index, std::size_t End, typename...Args>
void sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,Index,End>::changed_data(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index)
{
  Do_Signalboxes<Signalbox_Type,Type>::changed_data(a_source, get_signalboxes(), a_handle, a_index);
}

// When a handle at a given index has its data changed in a specific place.
template <std::size_t Index, std::size_t End, typename...Args>
void sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,Index,End>::changed_data_at(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index, std::size_t a_member)
{
  Do_Signalboxes<Signalbox_Type,Type>::changed_data_at(a_source, get_signalboxes(), a_handle, a_index, a_member);
}

// When a handle at a given index requests its editor be opened/brought to the top.
template <std::size_t Index, std::size_t End, typename...Args>
void sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,Index,End>::requests_editor(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index)
{
  Do_Signalboxes<Signalbox_Type,Type>::requests_editor(a_source, get_signalboxes(), a_handle, a_index);
}

// When a handle at a given index requests focus in the outliner.
template <std::size_t Index, std::size_t End, typename...Args>
void sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,Index,End>::requests_outliner(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index)
{
  Do_Signalboxes<Signalbox_Type,Type>::requests_outliner(a_source, get_signalboxes(), a_handle, a_index);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Project_Signalbox_Data_Part_Imp<List, End, End>
//---------------------------------------------------------------------------
// For the last type in the list

template <std::size_t End, typename...Args>
sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,End,End>::Project_Signalbox_Data_Part_Imp():
  m_signalboxes{}
{}

template <std::size_t End, typename...Args>
sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,End,End>::~Project_Signalbox_Data_Part_Imp() = default;

template <std::size_t End, typename...Args>
sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,End,End>::Project_Signalbox_Data_Part_Imp(Project_Signalbox_Data_Part_Imp const&) = default;

template <std::size_t End, typename...Args>
sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,End,End>& sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,End,End>::operator=(Project_Signalbox_Data_Part_Imp const&) = default;

template <std::size_t End, typename...Args>
sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,End,End>::Project_Signalbox_Data_Part_Imp(Project_Signalbox_Data_Part_Imp &&) = default;

template <std::size_t End, typename...Args>
sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,End,End>& sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,End,End>::operator=(Project_Signalbox_Data_Part_Imp &&) = default;

// Interface
//============================================================
// calls each of these on all the stored signalboxes.


// When a handle has been added at a given index.
template <std::size_t End, typename...Args>
void sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,End,End>::added(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index)
{
  Do_Signalboxes<Signalbox_Type,Type>::added(a_source, get_signalboxes(), a_handle, a_index);
}

// When a handle has been removed from a given index.
template <std::size_t End, typename...Args>
void sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,End,End>::removed(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index)
{
  Do_Signalboxes<Signalbox_Type,Type>::removed(a_source, get_signalboxes(), a_handle, a_index);
}

// When a handle at a given index has been moved to another index.
template <std::size_t End, typename...Args>
void sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,End,End>::moved(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_from, std::size_t a_to)
{
  Do_Signalboxes<Signalbox_Type,Type>::moved(a_source, get_signalboxes(), a_handle, a_from, a_to);
}

// When a handle at a given index has its name changed.
template <std::size_t End, typename...Args>
void sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,End,End>::changed_name(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index)
{
  Do_Signalboxes<Signalbox_Type,Type>::changed_name(a_source, get_signalboxes(), a_handle, a_index);
}

// When a handle at a given index has all of its data changed.
template <std::size_t End, typename...Args>
void sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,End,End>::changed_data(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index)
{
  Do_Signalboxes<Signalbox_Type,Type>::changed_data(a_source, get_signalboxes(), a_handle, a_index);
}

// When a handle at a given index has its data changed in a specific place.
template <std::size_t End, typename...Args>
void sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,End,End>::changed_data_at(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index, std::size_t a_member)
{
  Do_Signalboxes<Signalbox_Type,Type>::changed_data_at(a_source, get_signalboxes(), a_handle, a_index, a_member);
}

// When a handle at a given index requests its editor be opened/brought to the top.
template <std::size_t End, typename...Args>
void sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,End,End>::requests_editor(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index)
{
  Do_Signalboxes<Signalbox_Type,Type>::requests_editor(a_source, get_signalboxes(), a_handle, a_index);
}

// When a handle at a given index requests focus in the outliner.
template <std::size_t End, typename...Args>
void sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,End,End>::requests_outliner(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index)
{
  Do_Signalboxes<Signalbox_Type,Type>::requests_outliner(a_source, get_signalboxes(), a_handle, a_index);
}


// Add an object that will rely on the Project's signals. If nulltpr, nothing happens.
template <std::size_t End, typename...Args>
void sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,End,End>::add_signalbox(Signalbox_Type* a_signalbox)
{
  if (a_signalbox != nullptr
      && !do_has_signalbox(m_signalboxes, a_signalbox))
  {
    m_signalboxes.push_back(a_signalbox);
  }
}

// Remove an object that will rely on the Project's signals. If nulltpr, nothing happens.
template <std::size_t End, typename...Args>
void sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,End,End>::remove_signalbox(Signalbox_Type* a_signalbox)
{
  if (a_signalbox == nullptr)
  {
    return;
  }
  auto l_found = do_find_signalbox(m_signalboxes, a_signalbox);
  if (l_found != m_signalboxes.cend())
  {
    m_signalboxes.erase(l_found);
  }
}

// Clear all the signalboxes so that nothing relies on changes to this.
template <std::size_t End, typename...Args>
void sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,End,End>::clear_signalboxes()
{
  m_signalboxes.clear();
}


// Internal Interface
//============================================================
// Access the signalboxes so functions can be called in them.
template <std::size_t End, typename...Args>
std::vector<typename sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,End,End>::Signalbox_Type*>& sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,End,End>::get_signalboxes()
{
  return m_signalboxes;
}

template <std::size_t End, typename...Args>
std::vector<typename sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,End,End>::Signalbox_Type*> const& sak::Project_Signalbox_Data_Part_Imp<flamingo::typelist<Args...>,End,End>::cget_signalboxes() const
{
  return m_signalboxes;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------
// Project_Signalbox_Data_Imp<T,Args...>
//---------------------------------------------------------------------------
// The top class of the template chain, where we gather and cleanup
// everything. Also the requirement of at least one type stops bad template
// instantiations.

// Special 6
//============================================================
template <typename T, typename...Args>
sak::Project_Signalbox_Data_Imp<T,Args...>::Project_Signalbox_Data_Imp() = default;

template <typename T, typename...Args>
sak::Project_Signalbox_Data_Imp<T,Args...>::~Project_Signalbox_Data_Imp() = default;

template <typename T, typename...Args>
sak::Project_Signalbox_Data_Imp<T,Args...>::Project_Signalbox_Data_Imp(Project_Signalbox_Data_Imp const&) = default;

template <typename T, typename...Args>
sak::Project_Signalbox_Data_Imp<T,Args...>& sak::Project_Signalbox_Data_Imp<T,Args...>::operator=(Project_Signalbox_Data_Imp const&) = default;

template <typename T, typename...Args>
sak::Project_Signalbox_Data_Imp<T,Args...>::Project_Signalbox_Data_Imp(Project_Signalbox_Data_Imp &&) = default;

template <typename T, typename...Args>
sak::Project_Signalbox_Data_Imp<T,Args...>& sak::Project_Signalbox_Data_Imp<T,Args...>::operator=(Project_Signalbox_Data_Imp &&) = default;


//------------------------------------------------------------------------------------------------------------------------------------------------------

namespace
{
  using Project_Typelist = flamingo::typelist<sak::File_Definition,sak::Texture_Definition, sak::Material_Definition>;
}

// This is the downside of doing it like this if you want to hide stuff....
template class sak::Project_Signalbox_Data_Part_Imp<Project_Typelist,0,2>;
template class sak::Project_Signalbox_Data_Part_Imp<Project_Typelist,1,2>;
template class sak::Project_Signalbox_Data_Part_Imp<Project_Typelist,2,2>;

template class sak::Project_Signalbox_Data_Imp<sak::File_Definition, sak::Texture_Definition, sak::Material_Definition>;

