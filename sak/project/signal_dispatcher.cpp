#include "signal_dispatcher.hpp"
#include <QDebug>

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
void sak::project::signal_dispatcher::changed(file::extended_handle const& a_ehandle) override final
{
  qDebug() << "sak::project::signal_dispatcher::changed "<< a_ehandle.id().get();
  for (auto l_item : m_dependents) l_item->changed(a_ehandle);
}
// When a File has its data changed in a specific place, this is called.
void sak::project::signal_dispatcher::changed_at(file::extended_handle const& a_ehandle, std::size_t a_section) override final
{
  qDebug() << "sak::project::signal_dispatcher::changed_at "<< a_ehandle.id().get() << ", " << a_section;
  for (auto l_item : m_dependents) l_item->changed_at(a_ehandle, a_section);
}
// When a File has been added, this is called.
void sak::project::signal_dispatcher::added(file::extended_handle const& a_ehandle) override final
{
  qDebug() << "sak::project::signal_dispatcher::added "<< a_ehandle.id().get();
  for (auto l_item : m_dependents) l_item->added(a_ehandle);
}
// When a File has been removed, this is called.
void sak::project::signal_dispatcher::removed(file::extended_handle const& a_ehandle) override final
{
  qDebug() << "sak::project::signal_dispatcher::removed "<< a_ehandle.id().get();
  for (auto l_item : m_dependents) l_item->removed(a_ehandle);
}
// When a File requests an editor, this is called.
void sak::project::signal_dispatcher::requests_editor(file::extended_handle const& a_ehandle) override final
{
  qDebug() << "sak::project::signal_dispatcher::requests_editor "<< a_ehandle.id().get();
  for (auto l_item : m_dependents) l_item->requests_editor(a_ehandle);
}

// When a File requests an editor, this is called.
void sak::project::signal_dispatcher::requests_focus(file::extended_handle const& a_ehandle) override final
{
  qDebug() << "sak::project::signal_dispatcher::requests_focus "<< a_ehandle.id().get();
  for (auto l_item : m_dependents) l_item->requests_focus(a_ehandle);
}
