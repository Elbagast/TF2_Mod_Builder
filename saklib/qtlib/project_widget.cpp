#include "project_widget.h"
#include "../project_manager.h"

#include "element_widget.h"
#include "outliner/outliner_model.h"
#include "outliner/outliner_delegate.h"
#include "outliner/outliner_treeview.h"
#include "qstring_operations.h"

#include <QHBoxLayout>
#include <QScrollArea>
#include <QLabel>
#include <cassert>
#include <QDebug>

Saklib::Qtlib::Project_Widget::Project_Widget(Project_Manager& project_manager, QWidget* parent):
    QWidget(parent),
    Project_Observer(project_manager),
    m_outliner_model(make_quptr<Outliner_Model>(this)),
    m_outliner_delegate(make_quptr<Outliner_Delegate>(this)),
    m_outliner(make_quptr<Outliner_Treeview>(this)),
    m_scroll_area(make_quptr<QScrollArea>(this)),
    m_editor(nullptr),
    m_layout(make_quptr<QHBoxLayout>(this))
{
    m_outliner->setModel(m_outliner_model.get());
    m_outliner->setItemDelegate(m_outliner_delegate.get());
    // Does this need to be a signal?
    //QObject::connect(m_outliner_model.get, &Outliner_Model::signal_editorRequestedFor,
    // this, &Project_Widget::slot_editorRequestedFor);
    m_scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_layout->addWidget(m_outliner.get(), 1);
    m_layout->addWidget(m_scroll_area.get(), 3);
    setLayout(m_layout.get());
    open_editor(this->project_manager().project_elementid());
}
Saklib::Qtlib::Project_Widget::~Project_Widget() = default;

// Element Widget
//------------------------------------------------------------
// Alter the Element currently being edited
// Make an Element_Widget for this ElementID
void Saklib::Qtlib::Project_Widget::open_editor(ElementID elementid)
{
    // if the editor isn't set or it is and is for a different ElementID
    if (!m_editor || m_editor->elementid() != elementid)
    {
        // Replace it with a new Element_Widget
        m_editor = std::make_unique<Element_Widget>(this, elementid);
        m_scroll_area->setWidget(m_editor.get());
        m_scroll_area->setWidgetResizable(true);
    }
}
// The ElementID of the Element that is currently being edited
Saklib::ElementID Saklib::Qtlib::Project_Widget::currently_open_elementid() const
{
    if (m_editor)
        return m_editor->elementid();
    else
        return invalid_elementid();
}
// Overall Project
//------------------------------------------------------------
Saklib::ElementID Saklib::Qtlib::Project_Widget::project_elementid() const
{
    return project_manager().project_elementid();
}
Saklib::Path const& Saklib::Qtlib::Project_Widget::project_filepath() const
{
    return project_manager().project_filepath();
}
void Saklib::Qtlib::Project_Widget::set_project_filepath(Path const& filepath)
{
    project_manager().set_project_filepath(filepath);
}
void Saklib::Qtlib::Project_Widget::save() const
{
    project_manager().save();
}
void Saklib::Qtlib::Project_Widget::save_as(Path const& filepath)
{
    project_manager().save_as(filepath);
}



// Project_Observer Virtuals
//============================================================
void Saklib::Qtlib::Project_Widget::begin_model_reset()
{
    m_outliner->cache_expanded_indexes();
    m_outliner_model->begin_model_reset();
}

void Saklib::Qtlib::Project_Widget::end_model_reset()
{
    m_outliner_model->end_model_reset();
    m_outliner->restore_expanded_indexes();
}

void Saklib::Qtlib::Project_Widget::data_changed(ElementID elementid)
{
    // if the ElementID is valid and editor is valid and is for a this ElementID
    if (elementid.is_valid()
        && project_manager().is_valid(elementid)
        && m_editor
        && m_editor->elementid() == elementid)
    {
        m_editor->refresh_data();
    }
}

void Saklib::Qtlib::Project_Widget::data_changed(AttributeID attributeid)
{
    // if the ElementID is valid and editor is valid and is for a this ElementID
    if (attributeid.is_valid()
        && project_manager().is_valid(attributeid)
        && m_editor
        && m_editor->elementid() == attributeid.elementid())
    {
        m_editor->refresh_data(attributeid.index());
    }
}

void Saklib::Qtlib::Project_Widget::element_name_changed(ElementID elementid)
{
    data_changed(elementid);
}

void Saklib::Qtlib::Project_Widget::element_parent_changed(ElementID elementid)
{
    data_changed(elementid);
}
void Saklib::Qtlib::Project_Widget::element_destroyed(ElementID elementid)
{
    if (m_editor
        && m_editor->elementid() == elementid)
    {
        m_editor.reset();
    }
}

void Saklib::Qtlib::Project_Widget::attribute_value_changed(AttributeID attributeid)
{
    data_changed(attributeid);
}

void Saklib::Qtlib::Project_Widget::unsaved_edits_changed(bool state)
{
    emit signal_unsaved_edits(state);
}

void Saklib::Qtlib::Project_Widget::undo_counts_changed(size_type undo_count, size_type redo_count)
{
    emit signal_update_undo_actions(undo_count, redo_count);
}
