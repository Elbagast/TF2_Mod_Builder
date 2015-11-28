#include "windowtitle.h"
#include <QMainWindow>

// Special 6
//============================================================
saklib::Qtlib::WindowTitle::WindowTitle(QMainWindow* window, QString const& fixedTitle, QString const& editsMarker, QString const& spacer, QString const& variableTitle):
    m_window(window),
    m_fixedTitle(fixedTitle),
    m_editsMarker(editsMarker),
    m_spacer(spacer),
    m_variableTitle(variableTitle),
    m_unsavedEdits(false),
    m_fullTitle(),
    m_fullTitleUnsavedEdits()
{
    update_full_titles();
}

// Interface
//============================================================
void saklib::Qtlib::WindowTitle::set_window(QMainWindow* window)
{
    if (m_window != window)
    {
        m_window = window;
    }
}
void saklib::Qtlib::WindowTitle::set_fixed_title(QString const& fixedTitle)
{
    if (m_fixedTitle != fixedTitle)
    {
        m_fixedTitle = fixedTitle;
        update_full_titles();
    }
}
void saklib::Qtlib::WindowTitle::set_edits_marker(QString const& editsMarker)
{
    if (m_editsMarker != editsMarker)
    {
        m_editsMarker = editsMarker;
        update_full_titles();
    }
}
void saklib::Qtlib::WindowTitle::set_spacer(QString const& spacer)
{
    if (m_spacer != spacer)
    {
        m_spacer = spacer;
        update_full_titles();
    }
}
void saklib::Qtlib::WindowTitle::set_variable_title(QString const& variable)
{
    if (m_variableTitle != variable)
    {
        m_variableTitle = variable;
        m_unsavedEdits = false;
        update_full_titles();
    }
}
void saklib::Qtlib::WindowTitle::set_unsaved_edits(bool state)
{
    if (m_unsavedEdits != state)
    {
        m_unsavedEdits = state;
        update_window_title();
    }
}

void saklib::Qtlib::WindowTitle::clear_variable_title()
{
    m_variableTitle.clear();
    m_unsavedEdits = false;
    update_full_titles();
}

bool saklib::Qtlib::WindowTitle::has_unsaved_edits() const
{
    return m_unsavedEdits;
}

QString const& saklib::Qtlib::WindowTitle::full_title() const
{
    return m_unsavedEdits ? m_fullTitleUnsavedEdits : m_fullTitle;
}

void saklib::Qtlib::WindowTitle::update_full_titles()
{
    m_fullTitle.clear();
    m_fullTitleUnsavedEdits = m_editsMarker;

    if (!m_variableTitle.isEmpty())
    {
        m_fullTitle.append(m_variableTitle);
        m_fullTitle.append(m_spacer);
    }
    m_fullTitle.append(m_fixedTitle);
    m_fullTitleUnsavedEdits.append(m_fullTitle);

    update_window_title();
}

void saklib::Qtlib::WindowTitle::update_window_title()
{
    if (m_window)
    {
        m_window->setWindowTitle(full_title());
    }
}
