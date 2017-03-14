#include "signal_dispatcher.hpp"
#include <QDebug>
#include <sak/shared/manager.hpp>
#include <sak/shared/object.hpp>

sak::project::signal_dispatcher::signal_dispatcher(abstract::signalbox* a_forbidden):
  abstract::signalbox(),
  m_forbidden{a_forbidden}
{}

sak::project::signal_dispatcher::~signal_dispatcher() = default;

// Add an object that will rely on the Project's signals. If nulltpr, nothing happens.
void sak::project::signal_dispatcher::add_signalbox(abstract::signalbox* a_signalbox)
{
  if (a_signalbox != nullptr
      && a_signalbox != this
      && a_signalbox != m_forbidden
      && std::find(m_dependents.cbegin(), m_dependents.cend(), a_signalbox) == m_dependents.cend())
  {
    m_dependents.push_back(a_signalbox);
  }
}

// Remove an object that will rely on the Project's signals. If nulltpr, nothing happens.
void sak::project::signal_dispatcher::remove_signalbox(abstract::signalbox* a_signalbox)
{
  auto l_found = std::find(m_dependents.cbegin(), m_dependents.cend(), a_signalbox);
  if (l_found != m_dependents.cend())
  {
    m_dependents.erase(l_found);
  }
}

// When a File has its data changed(anything but the name), this is called.
void sak::project::signal_dispatcher::changed(file::handle const& a_handle)
{
  qDebug() << "sak::project::signal_dispatcher::changed "<< QString::fromStdString(file::object::type()) <<" " << a_handle.id().get();
  for (file::abstract::signalbox* l_item : m_dependents) l_item->changed(a_handle);
}
// When a File has its data changed in a specific place, this is called.
void sak::project::signal_dispatcher::changed_at(file::handle const& a_handle, std::size_t a_section)
{
  qDebug() << "sak::project::signal_dispatcher::changed_at "<< QString::fromStdString(file::object::type()) <<" " << a_handle.id().get() << ", " << a_section;
  for (file::abstract::signalbox* l_item : m_dependents) l_item->changed_at(a_handle, a_section);
}
// When a File has been added, this is called.
void sak::project::signal_dispatcher::added(file::handle const& a_handle)
{
  qDebug() << "sak::project::signal_dispatcher::added "<< QString::fromStdString(file::object::type()) <<" " << a_handle.id().get();
  for (file::abstract::signalbox* l_item : m_dependents) l_item->added(a_handle);
}
// When a File has been removed, this is called.
void sak::project::signal_dispatcher::removed(file::handle const& a_handle)
{
  qDebug() << "sak::project::signal_dispatcher::removed "<< QString::fromStdString(file::object::type()) <<" " << a_handle.id().get();
  for (file::abstract::signalbox* l_item : m_dependents) l_item->removed(a_handle);
}
// When a File requests an editor, this is called.
void sak::project::signal_dispatcher::requests_editor(file::handle const& a_handle)
{
  qDebug() << "sak::project::signal_dispatcher::requests_editor "<< QString::fromStdString(file::object::type()) <<" " << a_handle.id().get();
  for (file::abstract::signalbox* l_item : m_dependents) l_item->requests_editor(a_handle);
}

// When a File requests an editor, this is called.
void sak::project::signal_dispatcher::requests_focus(file::handle const& a_handle)
{
  qDebug() << "sak::project::signal_dispatcher::requests_focus "<< QString::fromStdString(file::object::type()) <<" " << a_handle.id().get();
  for (file::abstract::signalbox* l_item : m_dependents) l_item->requests_focus(a_handle);
}



// When a texture has its data changed(anything but the name), this is called.
void sak::project::signal_dispatcher::changed(texture::handle const& a_handle)
{
  qDebug() << "sak::project::signal_dispatcher::changed "<< QString::fromStdString(texture::object::type()) <<" " << a_handle.id().get();
  for (texture::abstract::signalbox* l_item : m_dependents) l_item->changed(a_handle);
}
// When a texture has its data changed in a specific place, this is called.
void sak::project::signal_dispatcher::changed_at(texture::handle const& a_handle, std::size_t a_section)
{
  qDebug() << "sak::project::signal_dispatcher::changed_at "<< QString::fromStdString(texture::object::type()) <<" " << a_handle.id().get() << ", " << a_section;
  for (texture::abstract::signalbox* l_item : m_dependents) l_item->changed_at(a_handle, a_section);
}
// When a texture has been added, this is called.
void sak::project::signal_dispatcher::added(texture::handle const& a_handle)
{
  qDebug() << "sak::project::signal_dispatcher::added "<< QString::fromStdString(texture::object::type()) <<" " << a_handle.id().get();
  for (texture::abstract::signalbox* l_item : m_dependents) l_item->added(a_handle);
}
// When a texture has been removed, this is called.
void sak::project::signal_dispatcher::removed(texture::handle const& a_handle)
{
  qDebug() << "sak::project::signal_dispatcher::removed "<< QString::fromStdString(texture::object::type()) <<" " << a_handle.id().get();
  for (texture::abstract::signalbox* l_item : m_dependents) l_item->removed(a_handle);
}
// When a texture requests an editor, this is called.
void sak::project::signal_dispatcher::requests_editor(texture::handle const& a_handle)
{
  qDebug() << "sak::project::signal_dispatcher::requests_editor "<< QString::fromStdString(texture::object::type()) <<" " << a_handle.id().get();
  for (texture::abstract::signalbox* l_item : m_dependents) l_item->requests_editor(a_handle);
}

// When a texture requests an editor, this is called.
void sak::project::signal_dispatcher::requests_focus(texture::handle const& a_handle)
{
  qDebug() << "sak::project::signal_dispatcher::requests_focus "<< QString::fromStdString(texture::object::type()) <<" " << a_handle.id().get();
  for (texture::abstract::signalbox* l_item : m_dependents) l_item->requests_focus(a_handle);
}
