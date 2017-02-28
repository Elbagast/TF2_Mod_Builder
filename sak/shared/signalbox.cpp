#include "signalbox.hpp"

template <typename T>
sak::shared::abstract::signalbox<T>::~signalbox() = default;

// When a handle has its data changed, this is called.
template <typename T>
void sak::shared::abstract::signalbox<T>::changed(extended_handle_type const& )
{

}

// When a handle has its data changed in a specific place, this is called.
// a_section == 0 denotes the name and may have special logic requirements.
template <typename T>
void sak::shared::abstract::signalbox<T>::changed_at(extended_handle_type const& , std::size_t )
{

}

// When a handle has been added, this is called.
template <typename T>
void sak::shared::abstract::signalbox<T>::added(extended_handle_type const& )
{

}

// When a handle has been removed, this is called.
template <typename T>
void sak::shared::abstract::signalbox<T>::removed(extended_handle_type const& )
{

}

// When a handle editor is to be opened, this is called.
template <typename T>
void sak::shared::abstract::signalbox<T>::requests_editor(extended_handle_type const& )
{

}

// When focus is changed to be on a handle, call this
template <typename T>
void sak::shared::abstract::signalbox<T>::requests_focus(extended_handle_type const& )
{

}



// Forced Instantiations
//============================================================
template sak::file::abstract::signalbox;
