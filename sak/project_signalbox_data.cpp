#include "project_signalbox_data.hpp"

#include "abstract_project_signalbox.hpp"

//---------------------------------------------------------------------------
// Project_Data_Shared_Imp<T,Args...>
//---------------------------------------------------------------------------
// Implement the parts that the data sections will depend on via virtual
// inheritance.

// Special 6
//============================================================
template <typename T, typename...Args>
sak::Project_Signalbox_Data_Shared_Imp<T,Args...>::Project_Signalbox_Data_Shared_Imp():
  m_signalboxes{}
{}

template <typename T, typename...Args>
sak::Project_Signalbox_Data_Shared_Imp<T,Args...>::~Project_Signalbox_Data_Shared_Imp() = default;

template <typename T, typename...Args>
sak::Project_Signalbox_Data_Shared_Imp<T,Args...>::Project_Signalbox_Data_Shared_Imp(Project_Signalbox_Data_Shared_Imp &&) = default;

template <typename T, typename...Args>
sak::Project_Signalbox_Data_Shared_Imp<T,Args...>& sak::Project_Signalbox_Data_Shared_Imp<T,Args...>::operator=(Project_Signalbox_Data_Shared_Imp &&) = default;

namespace
{
  template <typename...Args>
  decltype(auto) do_find_signalbox(std::vector<sak::Abstract_Signalbox<Args...>*> const& a_signalboxes, sak::Abstract_Signalbox<Args...>* a_signalbox)
  {
    return std::find(a_signalboxes.cbegin(), a_signalboxes.cend(), a_signalbox);
  }

  template <typename...Args>
  bool do_has_signalbox(std::vector<sak::Abstract_Signalbox<Args...>*> const& a_signalboxes, sak::Abstract_Signalbox<Args...>* a_signalbox)
  {
    return do_find_signalbox(a_signalboxes, a_signalbox) != a_signalboxes.cend();
  }
}


// Interface
//============================================================
// Add an object that will rely on the Project's signals. If nulltpr, nothing happens.
template <typename T, typename...Args>
void sak::Project_Signalbox_Data_Shared_Imp<T,Args...>::add_signalbox(Signalbox_Type* a_signalbox)
{
  if (a_signalbox != nullptr
      && !do_has_signalbox(m_signalboxes, a_signalbox))
  {
    m_signalboxes.push_back(a_signalbox);
  }
}

// Remove an object that will rely on the Project's signals. If nulltpr, nothing happens.
template <typename T, typename...Args>
void sak::Project_Signalbox_Data_Shared_Imp<T,Args...>::remove_signalbox(Signalbox_Type* a_signalbox)
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
template <typename T, typename...Args>
void sak::Project_Signalbox_Data_Shared_Imp<T,Args...>::clear_signalboxes()
{
  m_signalboxes.clear();
}

// Internal Interface
//============================================================
// Access the signalboxes so functions can be called in them.
template <typename T, typename...Args>
std::vector<typename sak::Project_Signalbox_Data_Shared_Imp<T,Args...>::Signalbox_Type*>& sak::Project_Signalbox_Data_Shared_Imp<T,Args...>::get_signalboxes()
{
  return m_signalboxes;
}

template <typename T, typename...Args>
std::vector<typename sak::Project_Signalbox_Data_Shared_Imp<T,Args...>::Signalbox_Type*> const& sak::Project_Signalbox_Data_Shared_Imp<T,Args...>::cget_signalboxes() const
{
  return m_signalboxes;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Project_Signalbox_Data_Section_Imp<List,T,Args...>
//---------------------------------------------------------------------------

// Special 6
//============================================================
template <typename T_List, typename T>
sak::Project_Signalbox_Data_Section_Imp<T_List,T>::Project_Signalbox_Data_Section_Imp():
  Base()
{}

template <typename T_List, typename T>
sak::Project_Signalbox_Data_Section_Imp<T_List,T>::~Project_Signalbox_Data_Section_Imp() = default;

template <typename T_List, typename T>
sak::Project_Signalbox_Data_Section_Imp<T_List,T>::Project_Signalbox_Data_Section_Imp(Project_Signalbox_Data_Section_Imp &&) = default;

template <typename T_List, typename T>
sak::Project_Signalbox_Data_Section_Imp<T_List,T>& sak::Project_Signalbox_Data_Section_Imp<T_List,T>::operator=(Project_Signalbox_Data_Section_Imp &&) = default;

// Public Interface
//============================================================

// calls each of these on all the stored signalboxes.

// When a handle has its data changed, this is called.
template <typename T_List, typename T>
void sak::Project_Signalbox_Data_Section_Imp<T_List,T>::changed(Handle<T> const& a_handle)
{
  for (auto l_item : get_signalboxes()) l_item->changed(a_handle);
}

// When a handle has its name changed, this is called.
template <typename T_List, typename T>
void sak::Project_Signalbox_Data_Section_Imp<T_List,T>::changed_name(Handle<T> const& a_handle)
{
  for (auto l_item : get_signalboxes()) l_item->changed_name(a_handle);
}

// When a handle has its data changed in a specific place, this is called.
// a_section == 0 denotes the name and may have special logic requirements.
template <typename T_List, typename T>
void sak::Project_Signalbox_Data_Section_Imp<T_List,T>::changed_at(Handle<T> const& a_handle, std::size_t a_section)
{
  for (auto l_item : get_signalboxes()) l_item->changed_at(a_handle, a_section);
}

// When a handle has been added, this is called.
template <typename T_List, typename T>
void sak::Project_Signalbox_Data_Section_Imp<T_List,T>::added(Handle<T> const& a_handle)
{
  for (auto l_item : get_signalboxes()) l_item->added(a_handle);
}

// When a handle has been removed, this is called.
template <typename T_List, typename T>
void sak::Project_Signalbox_Data_Section_Imp<T_List,T>::removed(Handle<T> const& a_handle)
{
  for (auto l_item : get_signalboxes()) l_item->removed(a_handle);
}

// When a handle editor is to be opened, this is called.
template <typename T_List, typename T>
void sak::Project_Signalbox_Data_Section_Imp<T_List,T>::requests_editor(Handle<T> const& a_handle)
{
  for (auto l_item : get_signalboxes()) l_item->requests_editor(a_handle);
}

// When focus is changed to be on a handle, call this
template <typename T_List, typename T>
void sak::Project_Signalbox_Data_Section_Imp<T_List,T>::requests_focus(Handle<T> const& a_handle)
{
  for (auto l_item : get_signalboxes()) l_item->requests_focus(a_handle);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Project_Signalbox_Data_Imp<T,Args...>
//---------------------------------------------------------------------------

// Special 6
//============================================================
template <typename T, typename...Args>
sak::Project_Signalbox_Data_Imp<T,Args...>::Project_Signalbox_Data_Imp() = default;

template <typename T, typename...Args>
sak::Project_Signalbox_Data_Imp<T,Args...>::~Project_Signalbox_Data_Imp() = default;

template <typename T, typename...Args>
sak::Project_Signalbox_Data_Imp<T,Args...>::Project_Signalbox_Data_Imp(Project_Signalbox_Data_Imp &&) = default;

template <typename T, typename...Args>
sak::Project_Signalbox_Data_Imp<T,Args...>& sak::Project_Signalbox_Data_Imp<T,Args...>::operator=(Project_Signalbox_Data_Imp &&) = default;


//------------------------------------------------------------------------------------------------------------------------------------------------------

namespace
{
  using Project_Typelist = flamingo::typelist<sak::File_Definition,sak::Texture_Definition, sak::Material_Definition>;
}
template class sak::Project_Signalbox_Data_Shared_Imp<sak::File_Definition,sak::Texture_Definition, sak::Material_Definition>;

template class sak::Project_Signalbox_Data_Section_Imp<Project_Typelist,sak::File_Definition>;
template class sak::Project_Signalbox_Data_Section_Imp<Project_Typelist,sak::Texture_Definition>;
template class sak::Project_Signalbox_Data_Section_Imp<Project_Typelist,sak::Material_Definition>;

template class sak::Project_Signalbox_Data_Imp<sak::File_Definition,sak::Texture_Definition, sak::Material_Definition>;
