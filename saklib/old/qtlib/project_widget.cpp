#include "project_widget.h"
#include "../project_manager.h"

#include "element_widget.h"
#include "outliner/outliner_model.h"
#include "outliner/outliner_delegate.h"
#include "outliner/outliner_treeview.h"
//#include "qstring_operations.h"

#include <QHBoxLayout>
#include <QSplitter>
#include <QScrollArea>
#include <QLabel>
#include <cassert>
#include <QDebug>

saklib::Qtlib::Project_Widget::Project_Widget(Project_Manager& project_manager, QWidget* parent):
    QWidget(parent),
    Project_Observer(project_manager),
    m_outliner_model(make_quptr<Outliner_Model>(this)),
    m_outliner_delegate(make_quptr<Outliner_Delegate>(this)),
    m_splitter(make_quptr<QSplitter>(Qt::Orientation::Horizontal, this)),
    m_outliner(make_quptr<Outliner_Treeview>(this)),
    m_scroll_area(make_quptr<QScrollArea>(this)),
    m_editor(nullptr),
    m_layout(make_quptr<QHBoxLayout>(this))
{
    m_outliner->setModel(m_outliner_model.get());
    m_outliner->setItemDelegate(m_outliner_delegate.get());

    m_scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    m_splitter->addWidget(m_outliner.get());
    m_splitter->setStretchFactor(0,0);

    m_splitter->addWidget(m_scroll_area.get());
    m_splitter->setStretchFactor(1,1);

    //m_layout->addWidget(m_outliner.get(), 1);
    //m_layout->addWidget(m_scroll_area.get(), 3);

    m_layout->addWidget(m_splitter.get());

    setLayout(m_layout.get());
    open_editor(this->project_manager().project_elementid());
    m_splitter->refresh();
}
saklib::Qtlib::Project_Widget::~Project_Widget() = default;

// Element Widget
//------------------------------------------------------------
// Alter the Element currently being edited
// Make an Element_Widget for this ElementID
void saklib::Qtlib::Project_Widget::open_editor(ElementID elementid)
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
saklib::ElementID saklib::Qtlib::Project_Widget::currently_open_elementid() const
{
    if (m_editor)
        return m_editor->elementid();
    else
        return invalid_elementid();
}
// Overall Project
//------------------------------------------------------------
saklib::ElementID saklib::Qtlib::Project_Widget::project_elementid() const
{
    return project_manager().project_elementid();
}
saklib::Path const& saklib::Qtlib::Project_Widget::project_filepath() const
{
    return project_manager().project_filepath();
}
void saklib::Qtlib::Project_Widget::set_project_filepath(Path const& filepath)
{
    project_manager().set_project_filepath(filepath);
}
void saklib::Qtlib::Project_Widget::save() const
{
    project_manager().save();
}
void saklib::Qtlib::Project_Widget::save_as(Path const& filepath)
{
    project_manager().save_as(filepath);
}



// Project_Observer Virtuals
//============================================================
void saklib::Qtlib::Project_Widget::begin_model_reset()
{
    m_outliner->cache_expanded_indexes();
    m_outliner_model->begin_model_reset();
}

void saklib::Qtlib::Project_Widget::end_model_reset()
{
    m_outliner_model->end_model_reset();
    m_outliner->restore_expanded_indexes();
}

void saklib::Qtlib::Project_Widget::data_changed(ElementID elementid)
{
    // if the ElementID is valid and editor is valid and is for a this ElementID
    if (elementid.is_valid()
        && project_manager().has_elementid(elementid)
        && m_editor
        && m_editor->elementid() == elementid)
    {
        m_editor->refresh_data();
    }
}

void saklib::Qtlib::Project_Widget::data_changed(AttributeID attributeid)
{
    // if the ElementID is valid and editor is valid and is for a this ElementID
    if (attributeid.is_valid()
        && project_manager().has_attributeid(attributeid)
        && m_editor
        && m_editor->elementid() == attributeid.elementid())
    {
        m_editor->refresh_data(attributeid.index());
    }
}

void saklib::Qtlib::Project_Widget::element_name_changed(ElementID elementid)
{
    // if the ElementID is valid and editor is valid and is for a this ElementID
    if (elementid.is_valid()
        && project_manager().has_elementid(elementid)
        && m_editor
        && m_editor->elementid() == elementid)
    {
        m_editor->refresh_name();
        m_outliner_model->update_item(elementid);
    }

}

void saklib::Qtlib::Project_Widget::element_parent_changed(ElementID elementid)
{
    data_changed(elementid);
}
void saklib::Qtlib::Project_Widget::element_destroyed(ElementID elementid)
{
    if (m_editor
        && m_editor->elementid() == elementid)
    {
        m_editor.reset();
    }
}

void saklib::Qtlib::Project_Widget::attribute_value_changed(AttributeID attributeid)
{
    data_changed(attributeid);
}

void saklib::Qtlib::Project_Widget::unsaved_edits_changed(bool state)
{
    emit signal_unsaved_edits(state);
}

void saklib::Qtlib::Project_Widget::undo_counts_changed(size_type undo_count, size_type redo_count)
{
    emit signal_update_undo_actions(undo_count, redo_count);
}