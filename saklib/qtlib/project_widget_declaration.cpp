#include "project_widget.h"

#include "../element.h"
#include "../attribute_type.h"

#include "element_widget.h"

#include "outliner/outliner_model.h"
#include "outliner/outliner_operations.h"
#include "outliner/outliner_delegate.h"
#include "outliner/outliner_treeview.h"

#include "qstring_operations.h"

#include <QHBoxLayout>
#include <QScrollArea>
#include <QLabel>

#include <cassert>

#include "../interal_element_definitions.h"

// Static Helpers
//============================================================
// Make an ElementID with the supplied manager by registering the Element type the first time
// this is run
Saklib::ElementID Saklib::Qtlib::Project_Widget::make_Project(Element_Manager& element_manager)
{
    static bool was_run{false};
    if (!was_run)
    {
        register_all_internal_definitions();
        was_run = true;
    }
    ElementID result{element_manager.make_element("Project")};
    assert(element_manager.is_valid(result));
    element_manager.element(result).set_name("Default_Project_Name");
    return result;
}


// Special 6
//============================================================
Saklib::Qtlib::Project_Widget::Project_Widget(Path const& filepath, QWidget* parent) :
    QWidget(parent),
    m_element_manager{},
    m_command_history{},

    m_outliner_model(new Outliner_Model(this)),
    m_outliner_delegate(new Outliner_Delegate(this)),

    m_project_elementid{make_Project(m_element_manager)},
    m_project_filepath{m_element_manager.attributeid(m_project_elementid, "Filepath")},

    m_outliner(new Outliner_Treeview(this)),
    m_scroll_area(new QScrollArea(this)),
    m_editor(nullptr),

    m_layout(new QHBoxLayout(this))
{
    // Store the filename in this attribute
    set_project_filepath(filepath);

    m_outliner->setModel(m_outliner_model.get());
    m_outliner->setItemDelegate(m_outliner_delegate.get());

    // TESTING LINES
    m_element_manager.make_element("File");
    m_element_manager.make_element("SingleInt");
    auto test_child =  this->make_element("SingleInt");
    auto parent_attribute = this->attributeid(m_project_elementid, "TestElement");
    attribute_set_value(parent_attribute, test_child);



    // Does this need to be a signal?
    //QObject::connect(m_outliner_model.get, &Outliner_Model::signal_editorRequestedFor,
     //                this, &Project_Widget::slot_editorRequestedFor);

    m_scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    m_layout->addWidget(m_outliner.get(), 1);
    m_layout->addWidget(m_scroll_area.get(), 3);
    setLayout(m_layout.get());

    open_editor(m_project_elementid);
}
Saklib::Qtlib::Project_Widget::~Project_Widget()
{
    // Break all parenting so the Uptr can clean them up without double deletes
    //if (m_outliner_model) m_outliner_model->setParent(nullptr);
    //if (m_outliner_delegate) m_outliner_delegate->setParent(nullptr);
    if (m_outliner) m_outliner->setParent(nullptr);
    if (m_scroll_area)
    {
        m_scroll_area->setParent(nullptr);
        m_scroll_area->setWidget(nullptr);
    }
    if (m_editor) m_editor->setParent(nullptr);
    //if (m_layout) m_layout->setParent(nullptr);
}



// Interface
//============================================================

// Lifetime
//------------------------------------------------------------
// Make a new Element and return all info about it
Saklib::ElementID Saklib::Qtlib::Project_Widget::make_element(String const& type)
{
    // make an element
    ElementID newid = m_element_manager.make_element(type);
    return newid;
}

// Destory an Element and everything associated with it
void Saklib::Qtlib::Project_Widget::destroy_element(ElementID elementid)
{
    m_element_manager.destroy_element(elementid);
    if (m_editor && m_editor->elementid() == elementid)
    {
        m_editor.reset();
    }
}

// Does this refer to something in this? - rename these to has(blah) ?
bool Saklib::Qtlib::Project_Widget::is_valid(ElementID elementid) const
{
    return m_element_manager.is_valid(elementid);
}
bool Saklib::Qtlib::Project_Widget::is_valid(AttributeID attributeid) const
{
    return m_element_manager.is_valid(attributeid);
}
bool Saklib::Qtlib::Project_Widget::is_valid(ProxyID proxyid) const
{
    return m_element_manager.is_valid(proxyid.elementid());
}

// Elements
//------------------------------------------------------------
Saklib::Element& Saklib::Qtlib::Project_Widget::element(ElementID elementid)
{
    return m_element_manager.element(elementid);
}

Saklib::Element const& Saklib::Qtlib::Project_Widget::element(ElementID elementid) const
{
    return m_element_manager.element(elementid);
}

Saklib::String const& Saklib::Qtlib::Project_Widget::element_type(ElementID elementid) const
{
    return m_element_manager.element(elementid).type();
}

Saklib::String const& Saklib::Qtlib::Project_Widget::element_name(ElementID elementid) const
{
    return m_element_manager.element(elementid).name();
}

void Saklib::Qtlib::Project_Widget::element_set_name(ElementID elementid, String const& value)
{
    assert(is_valid(elementid));
    // maintaining unique names should have been done before getting here

    m_element_manager.element(elementid).set_name(value);
    update_widget(elementid);
    update_model(elementid);
    emit signal_unsaved_edits(true);
}

Saklib::AttributeID Saklib::Qtlib::Project_Widget::element_parent(ElementID elementid) const
{
     return m_element_manager.parent(elementid);
}

void Saklib::Qtlib::Project_Widget::element_set_parent(ElementID elementid, AttributeID attributeid)
{
    m_element_manager.set_parent(elementid, attributeid);
}

// Attributes
//------------------------------------------------------------
Saklib::AttributeID Saklib::Qtlib::Project_Widget::attributeid(ElementID elementid, String const& attribute_name) const
{
    return m_element_manager.attributeid(elementid, attribute_name);
}

Saklib::Attribute *const Saklib::Qtlib::Project_Widget::attribute(AttributeID attributeid)
{
    return m_element_manager.attribute(attributeid);
}
Saklib::Attribute *const Saklib::Qtlib::Project_Widget::attribute(ElementID elementid, size_type attribute_index)
{
    return m_element_manager.attribute(elementid, attribute_index);
}
Saklib::Attribute *const Saklib::Qtlib::Project_Widget::attribute(ElementID elementid, String const& attribute_name)
{
    return m_element_manager.attribute(elementid, attribute_name);
}


Saklib::Attribute const*const Saklib::Qtlib::Project_Widget::attribute(AttributeID attributeid) const
{
    return m_element_manager.attribute(attributeid);
}
Saklib::Attribute const*const Saklib::Qtlib::Project_Widget::attribute(ElementID elementid, size_type attribute_index) const
{
    return m_element_manager.attribute(elementid, attribute_index);
}
Saklib::Attribute const*const Saklib::Qtlib::Project_Widget::attribute(ElementID elementid, String const& attribute_name) const
{
    return m_element_manager.attribute(elementid, attribute_name);
}

Saklib::String const& Saklib::Qtlib::Project_Widget::attribute_name(AttributeID attributeid) const
{
    return m_element_manager.attribute(attributeid)->name();
}
Saklib::Type_Enum Saklib::Qtlib::Project_Widget::attribute_type_enum(AttributeID attributeid) const
{
    return m_element_manager.attribute(attributeid)->type_enum();
}
Saklib::String Saklib::Qtlib::Project_Widget::attribute_type_string(AttributeID attributeid) const
{
    return m_element_manager.attribute(attributeid)->type_string();
}



// Attribute_Type<T>
//------------------------------------------------------------
// These functions set the data without question, and tell the model and widget to update.
template <>
void Saklib::Qtlib::Project_Widget::attribute_set_value<Saklib::ElementID>(AttributeID attributeid, ElementID const& value)
//void Saklib::Qtlib::Project_Widget::attribute_set_value(AttributeID attributeid, ElementID value)
{
    assert(attributeid.is_valid());
    assert(this->attribute_type_enum(attributeid) == Type_Traits<ElementID>::type_enum());

    ElementID old_value = m_element_manager.element(attributeid.elementid()).attribute_type_cast<ElementID>(attributeid.index())->value();

    // if the ElementID changed from invalid to valid,
    if (!old_value.is_valid() && value.is_valid())
    {
        // tell the model that row 0 was added as a child of attributeid
        Outliner_Row_Inserter inserter(m_outliner_model.get(), m_outliner_model->make_index_of(attributeid), 0);

        attribute_type_cast<ElementID>(attributeid)->set_value(value);
        m_element_manager.set_parent(old_value, invalid_attributeid());
        m_element_manager.set_parent(value, attributeid);

        //m_outliner_model->add_row(attributeid, 0);
    }
    // else if the ElementID changed from valid to invalid,
    else if (old_value.is_valid() && !value.is_valid())
    {
        Outliner_Row_Remover remover(m_outliner_model.get(), m_outliner_model->make_index_of(attributeid), 0);

        attribute_type_cast<ElementID>(attributeid)->set_value(value);
        m_element_manager.set_parent(old_value, invalid_attributeid());
        m_element_manager.set_parent(value, attributeid);

        //m_outliner_model->remove_row(attributeid, 0);
    }
    else
    {
        // tell the model to update the children of attributeid
        m_outliner_model->update_item(value);
        m_element_manager.set_parent(old_value, invalid_attributeid());
        m_element_manager.set_parent(value, attributeid);
    }

    update_widget(attributeid);
    //m_outliner_model->update_children(attributeid); // doesn't work...

    //m_outliner_model->update_all(); // using this shows everything is there
    emit signal_unsaved_edits(true);
}


// Attribute_Type<Vector<T>> Type-Anonymous Functions
//------------------------------------------------------------
// We do not need to know the underlying type to call these functions, but this must figure
// it out and act appropriately.


// if the attribute is a vector, return it's size, otherwise 0
Saklib::size_type Saklib::Qtlib::Project_Widget::any_attribute_vector_size(AttributeID attributeid) const
{
    auto attribute_type = attribute_type_enum(attributeid);
    switch(attribute_type)
    {
    case Type_Enum::Vector_Bool:        return attribute_vector_size<TypeHolder_vt<Type_Enum::Vector_Bool>>(attributeid);
    case Type_Enum::Vector_Int:         return attribute_vector_size<TypeHolder_vt<Type_Enum::Vector_Int>>(attributeid);
    case Type_Enum::Vector_Double:      return attribute_vector_size<TypeHolder_vt<Type_Enum::Vector_Double>>(attributeid);
    case Type_Enum::Vector_String:      return attribute_vector_size<TypeHolder_vt<Type_Enum::Vector_String>>(attributeid);
    case Type_Enum::Vector_Path:        return attribute_vector_size<TypeHolder_vt<Type_Enum::Vector_Path>>(attributeid);
    case Type_Enum::Vector_ElementID:   return attribute_vector_size<TypeHolder_vt<Type_Enum::Vector_ElementID>>(attributeid);
    default: return 0;
    }
}

// if the attribute is a vector, return it's size, otherwise 0
bool Saklib::Qtlib::Project_Widget::any_attribute_vector_empty(AttributeID attributeid) const
{
    auto attribute_type = attribute_type_enum(attributeid);
    switch(attribute_type)
    {
    case Type_Enum::Vector_Bool:        return attribute_vector_empty<TypeHolder_vt<Type_Enum::Vector_Bool>>(attributeid);
    case Type_Enum::Vector_Int:         return attribute_vector_empty<TypeHolder_vt<Type_Enum::Vector_Int>>(attributeid);
    case Type_Enum::Vector_Double:      return attribute_vector_empty<TypeHolder_vt<Type_Enum::Vector_Double>>(attributeid);
    case Type_Enum::Vector_String:      return attribute_vector_empty<TypeHolder_vt<Type_Enum::Vector_String>>(attributeid);
    case Type_Enum::Vector_Path:        return attribute_vector_empty<TypeHolder_vt<Type_Enum::Vector_Path>>(attributeid);
    case Type_Enum::Vector_ElementID:   return attribute_vector_empty<TypeHolder_vt<Type_Enum::Vector_ElementID>>(attributeid);
    default: return false;
    }
}


void Saklib::Qtlib::Project_Widget::any_attribute_vector_clear(AttributeID attributeid)
{
    auto attribute_type = attribute(attributeid)->type_enum();
    switch(attribute_type)
    {
    case Type_Enum::Vector_Bool:        attribute_vector_clear<TypeHolder_vt<Type_Enum::Vector_Bool>>(attributeid); break;
    case Type_Enum::Vector_Int:         attribute_vector_clear<TypeHolder_vt<Type_Enum::Vector_Int>>(attributeid); break;
    case Type_Enum::Vector_Double:      attribute_vector_clear<TypeHolder_vt<Type_Enum::Vector_Double>>(attributeid); break;
    case Type_Enum::Vector_String:      attribute_vector_clear<TypeHolder_vt<Type_Enum::Vector_String>>(attributeid); break;
    case Type_Enum::Vector_Path:        attribute_vector_clear<TypeHolder_vt<Type_Enum::Vector_Path>>(attributeid); break;
    case Type_Enum::Vector_ElementID:   attribute_vector_clear<TypeHolder_vt<Type_Enum::Vector_ElementID>>(attributeid); break;
    default: assert(false); // called on the wrong type
    }
}

void Saklib::Qtlib::Project_Widget::any_attribute_vector_pop_back(AttributeID attributeid)
{
    auto attribute_type = attribute(attributeid)->type_enum();
    switch(attribute_type)
    {
    case Type_Enum::Vector_Bool:        attribute_vector_pop_back<TypeHolder_vt<Type_Enum::Vector_Bool>>(attributeid); break;
    case Type_Enum::Vector_Int:         attribute_vector_pop_back<TypeHolder_vt<Type_Enum::Vector_Int>>(attributeid); break;
    case Type_Enum::Vector_Double:      attribute_vector_pop_back<TypeHolder_vt<Type_Enum::Vector_Double>>(attributeid); break;
    case Type_Enum::Vector_String:      attribute_vector_pop_back<TypeHolder_vt<Type_Enum::Vector_String>>(attributeid); break;
    case Type_Enum::Vector_Path:        attribute_vector_pop_back<TypeHolder_vt<Type_Enum::Vector_Path>>(attributeid); break;
    case Type_Enum::Vector_ElementID:   attribute_vector_pop_back<TypeHolder_vt<Type_Enum::Vector_ElementID>>(attributeid); break;
    default: assert(false); // called on the wrong type
    }
}
void Saklib::Qtlib::Project_Widget::any_attribute_vector_swap_at(AttributeID attributeid, size_type index, size_type other_index)
{
    auto attribute_type = attribute(attributeid)->type_enum();
    switch(attribute_type)
    {
    case Type_Enum::Vector_Bool:        attribute_vector_swap_at<TypeHolder_vt<Type_Enum::Vector_Bool>>(attributeid, index, other_index); break;
    case Type_Enum::Vector_Int:         attribute_vector_swap_at<TypeHolder_vt<Type_Enum::Vector_Int>>(attributeid, index, other_index); break;
    case Type_Enum::Vector_Double:      attribute_vector_swap_at<TypeHolder_vt<Type_Enum::Vector_Double>>(attributeid, index, other_index); break;
    case Type_Enum::Vector_String:      attribute_vector_swap_at<TypeHolder_vt<Type_Enum::Vector_String>>(attributeid, index, other_index); break;
    case Type_Enum::Vector_Path:        attribute_vector_swap_at<TypeHolder_vt<Type_Enum::Vector_Path>>(attributeid, index, other_index); break;
    case Type_Enum::Vector_ElementID:   attribute_vector_swap_at<TypeHolder_vt<Type_Enum::Vector_ElementID>>(attributeid, index, other_index); break;
    default: assert(false); // called on the wrong type
    }
}

// Attribute_Type<Vector<T>> Forwarding Functions
//------------------------------------------------------------
// We must know the type to use these ones, and they should be called without specifying the
// explicitly so that the ElementID overload can be used (specialisation for it doesn't work).

template <>
void Saklib::Qtlib::Project_Widget::attribute_vector_clear<Saklib::ElementID>(AttributeID attributeid)
{
    assert_attribute<Vector_ElementID>(attributeid);

    assert(0);
}

template <>
void Saklib::Qtlib::Project_Widget::attribute_vector_set_at<Saklib::ElementID>(AttributeID attributeid, size_type index, ElementID const& value)
//void Saklib::Qtlib::Project_Widget::attribute_vector_set_at(AttributeID attributeid, size_type index, ElementID const& value)
//void Saklib::Qtlib::Project_Widget::attribute_vector_set_at(AttributeID attributeid, size_type index, ElementID value)
{
    assert_attribute<Vector_ElementID>(attributeid);
    ElementID old_value = attribute_vector_at<ElementID>(attributeid, index);

    attribute_type_cast<Vector_ElementID>(attributeid)->set_at(index, value);

    element_set_parent(old_value, invalid_attributeid());
    element_set_parent(value, attributeid);

    update_widget(attributeid);
    update_model(attributeid);

    // need to do the following...


    //m_outliner_model->update_children(attributeid); // doesn't work...

    //m_outliner_model->update_all(); // using this shows everything is there
    emit signal_unsaved_edits(true);
}

template<>
void Saklib::Qtlib::Project_Widget::attribute_vector_set_front<Saklib::ElementID>(AttributeID attributeid, ElementID const& value)
{
    assert_attribute<Vector_ElementID>(attributeid);

    assert(0);
}

template<>
void Saklib::Qtlib::Project_Widget::attribute_vector_set_back<Saklib::ElementID>(AttributeID attributeid, ElementID const& value)
{
    assert_attribute<Vector_ElementID>(attributeid);

    assert(0);
}

template<>
void Saklib::Qtlib::Project_Widget::attribute_vector_push_back<Saklib::ElementID>(AttributeID attributeid, ElementID const& value)
//void Saklib::Qtlib::Project_Widget::attribute_vector_push_back(AttributeID attributeid, ElementID const& value)
//void Saklib::Qtlib::Project_Widget::attribute_vector_push_back(AttributeID attributeid, ElementID value)
{
    assert_attribute<Vector_ElementID>(attributeid);

    auto attribute = this->attribute_type_cast<Vector_ElementID>(attributeid);

    {
        Outliner_Row_Inserter inserter(m_outliner_model.get(), m_outliner_model->make_index_of(attributeid), outliner_row_count(attributeid));

        attribute->push_back(value);
        element_set_parent(value, attributeid);
    }
    update_widget(attributeid);

    emit signal_unsaved_edits(true);
}
template<>
void Saklib::Qtlib::Project_Widget::attribute_vector_pop_back<Saklib::ElementID>(AttributeID attributeid)
{
    assert_attribute<Vector_ElementID>(attributeid);

    auto attribute = this->attribute_type_cast<Vector_ElementID>(attributeid);

    {
        Outliner_Row_Remover remover(m_outliner_model.get(), m_outliner_model->make_index_of(attributeid), outliner_row_count(attributeid));

        ElementID last_value = attribute->back();
        attribute->pop_back();
        element_set_parent(last_value, invalid_attributeid());
    }
    update_widget(attributeid);

    emit signal_unsaved_edits(true);
}

template<>
void Saklib::Qtlib::Project_Widget::attribute_vector_insert_at<Saklib::ElementID>(AttributeID attributeid, size_type index, ElementID const& value)
//void Saklib::Qtlib::Project_Widget::attribute_vector_insert_at(AttributeID attributeid, size_type index, ElementID value)
{
    assert_attribute<Vector_ElementID>(attributeid);

    assert(0);
}

template<>
void Saklib::Qtlib::Project_Widget::attribute_vector_remove_at<Saklib::ElementID>(AttributeID attributeid, size_type index)
{
    assert_attribute<Vector_ElementID>(attributeid);

    assert(0);
}







// Data Setters
//------------------------------------------------------------
// You must only set data though these in order to keep everything in sync. These setters will issue
// appropriate commands as necessary and return true if a change was actually made to data.




// Type Anonymous Vector Write Functions
//------------------------------------------------------------
// We do not need to know the underlying type to call these functions, but this must figure
// it out and act appropriately.



// Commands - indirect write access
//------------------------------------------------------------
// To support undoing edits use these functions to edit data from the outliner/widgets.

bool Saklib::Qtlib::Project_Widget::undoable_element_set_name(ElementID elementid, String const& value)
{
    // if conditions are right to issue a command
    if(elementid.is_valid()
       && this->is_valid(elementid)
       && this->element_name(elementid) != value)
    {
        // do it. The command should call the update_... function(s) when it is executed/unexecuted
        m_command_history.emplace_execute<PWC_Element_Set_Name>(this, elementid, value);
        command_history_changed();
        return true;
    }
    else
    {
        return false;
    }
}

bool Saklib::Qtlib::Project_Widget::undoable_any_attribute_vector_clear(AttributeID attributeid)
{
    auto attribute_type = attribute(attributeid)->type_enum();
    switch(attribute_type)
    {
    case Type_Enum::Vector_Bool:        return undoable_attribute_vector_clear<TypeHolder_vt<Type_Enum::Vector_Bool>>(attributeid);
    case Type_Enum::Vector_Int:         return undoable_attribute_vector_clear<TypeHolder_vt<Type_Enum::Vector_Int>>(attributeid);
    case Type_Enum::Vector_Double:      return undoable_attribute_vector_clear<TypeHolder_vt<Type_Enum::Vector_Double>>(attributeid);
    case Type_Enum::Vector_String:      return undoable_attribute_vector_clear<TypeHolder_vt<Type_Enum::Vector_String>>(attributeid);
    case Type_Enum::Vector_Path:        return undoable_attribute_vector_clear<TypeHolder_vt<Type_Enum::Vector_Path>>(attributeid);
    case Type_Enum::Vector_ElementID:   return undoable_attribute_vector_clear<TypeHolder_vt<Type_Enum::Vector_ElementID>>(attributeid);
    default: assert(false); // called on the wrong type
    }
    return false;
}

bool Saklib::Qtlib::Project_Widget::undoable_any_attribute_vector_swap_at(AttributeID attributeid, size_type index, size_type other_index)
{
    auto attribute_type = attribute(attributeid)->type_enum();
    switch(attribute_type)
    {
    case Type_Enum::Vector_Bool:        return undoable_attribute_vector_swap_at<TypeHolder_vt<Type_Enum::Vector_Bool>>(attributeid, index, other_index);
    case Type_Enum::Vector_Int:         return undoable_attribute_vector_swap_at<TypeHolder_vt<Type_Enum::Vector_Int>>(attributeid, index, other_index);
    case Type_Enum::Vector_Double:      return undoable_attribute_vector_swap_at<TypeHolder_vt<Type_Enum::Vector_Double>>(attributeid, index, other_index);
    case Type_Enum::Vector_String:      return undoable_attribute_vector_swap_at<TypeHolder_vt<Type_Enum::Vector_String>>(attributeid, index, other_index);
    case Type_Enum::Vector_Path:        return undoable_attribute_vector_swap_at<TypeHolder_vt<Type_Enum::Vector_Path>>(attributeid, index, other_index);
    case Type_Enum::Vector_ElementID:   return undoable_attribute_vector_swap_at<TypeHolder_vt<Type_Enum::Vector_ElementID>>(attributeid, index, other_index);
    default: assert(false); // called on the wrong type
    }
    return false;
}

bool Saklib::Qtlib::Project_Widget::undoable_any_attribute_vector_pop_back(AttributeID attributeid)
{
    auto attribute_type = attribute(attributeid)->type_enum();
    switch(attribute_type)
    {
    case Type_Enum::Vector_Bool:        return undoable_attribute_vector_pop_back<TypeHolder_vt<Type_Enum::Vector_Bool>>(attributeid);
    case Type_Enum::Vector_Int:         return undoable_attribute_vector_pop_back<TypeHolder_vt<Type_Enum::Vector_Int>>(attributeid);
    case Type_Enum::Vector_Double:      return undoable_attribute_vector_pop_back<TypeHolder_vt<Type_Enum::Vector_Double>>(attributeid);
    case Type_Enum::Vector_String:      return undoable_attribute_vector_pop_back<TypeHolder_vt<Type_Enum::Vector_String>>(attributeid);
    case Type_Enum::Vector_Path:        return undoable_attribute_vector_pop_back<TypeHolder_vt<Type_Enum::Vector_Path>>(attributeid);
    case Type_Enum::Vector_ElementID:   return undoable_attribute_vector_pop_back<TypeHolder_vt<Type_Enum::Vector_ElementID>>(attributeid);
    default: assert(false); // called on the wrong type
    }
    return false;
}

bool Saklib::Qtlib::Project_Widget::undoable_any_attribute_vector_remove_at(AttributeID attributeid, size_type index)
{
    auto attribute_type = attribute(attributeid)->type_enum();
    switch(attribute_type)
    {
    case Type_Enum::Vector_Bool:        return undoable_attribute_vector_remove_at<TypeHolder_vt<Type_Enum::Vector_Bool>>(attributeid, index);
    case Type_Enum::Vector_Int:         return undoable_attribute_vector_remove_at<TypeHolder_vt<Type_Enum::Vector_Int>>(attributeid, index);
    case Type_Enum::Vector_Double:      return undoable_attribute_vector_remove_at<TypeHolder_vt<Type_Enum::Vector_Double>>(attributeid, index);
    case Type_Enum::Vector_String:      return undoable_attribute_vector_remove_at<TypeHolder_vt<Type_Enum::Vector_String>>(attributeid, index);
    case Type_Enum::Vector_Path:        return undoable_attribute_vector_remove_at<TypeHolder_vt<Type_Enum::Vector_Path>>(attributeid, index);
    case Type_Enum::Vector_ElementID:   return undoable_attribute_vector_remove_at<TypeHolder_vt<Type_Enum::Vector_ElementID>>(attributeid, index);
    default: assert(false); // called on the wrong type
    }
    return false;
}





// Flat Access
//------------------------------------------------------------
Saklib::Vector_ElementID Saklib::Qtlib::Project_Widget::all_elementids() const
{
    return m_element_manager.all_elementids();
}
Saklib::Vector_ElementID Saklib::Qtlib::Project_Widget::root_elementids() const
{
    return m_element_manager.root_elementids();
}

// Model Interface
//------------------------------------------------------------
// Functions that provide data to the outliner model

// What are this item's children?
Saklib::Vector_AttributeID Saklib::Qtlib::Project_Widget::outliner_children(ElementID elementid) const
{
    // Assuming a valid ElementID...
    Vector_AttributeID results{};

    // For each Attribute by index
    auto const& attributes = element(elementid).attributes();
    for(size_type index = 0, end = attributes.size(); index != end; ++index)
    {
        // If the type is of interest
        Type_Enum type{attributes.at(index)->type_enum()};
        if (type == Type_Enum::ElementID || type == Type_Enum::Vector_ElementID)
        {
            results.push_back(AttributeID(elementid, index));
        }
    }

    return results;
}
Saklib::Vector_ElementID Saklib::Qtlib::Project_Widget::outliner_children(AttributeID attributeid) const
{
    // Assuming a valid AttributeID...
    Vector_ElementID results{};

    // If invalid get the root children
    if (!attributeid.is_valid())
    {
        return root_elementids();
    }

    Type_Enum type{attribute_type_enum(attributeid)};
    if (type == Type_Enum::ElementID)
    {
        // Get the ElementID held
        ElementID held_elementid = attribute_type_cast<ElementID>(attributeid)->value();
        if (held_elementid.is_valid())
        {
            results.push_back(held_elementid);
        }
    }
    else if (type == Type_Enum::Vector_ElementID)
    {
        // For each stored ElementID
        auto const& elementid_vector = attribute_type_cast<Vector_ElementID>(attributeid)->vector();
        for(auto elementid : elementid_vector)
        {
            if (elementid.is_valid())
            {
                results.push_back(elementid);
            }
        }
    }
    else
    {
        // ignore other Attribute types
    }

    return results;
}

// What item is the child at row?
Saklib::AttributeID Saklib::Qtlib::Project_Widget::outliner_child_at_row(ElementID elementid, int row) const
{
    auto children = outliner_children(elementid);
    auto unsigned_row = static_cast<size_type>(row);
    if (row >=0 && unsigned_row < children.size())
    {
        return children.at(unsigned_row);
    }
    else
    {
        return invalid_attributeid();
    }
}
Saklib::ElementID Saklib::Qtlib::Project_Widget::outliner_child_at_row(AttributeID attributeid, int row) const
{
    auto children = outliner_children(attributeid);
    auto unsigned_row = static_cast<size_type>(row);
    if (row >=0 && unsigned_row < children.size())
    {
        return children.at(unsigned_row);
    }
    else
    {
        return invalid_elementid();
    }
}

// How many rows does this item have?
int Saklib::Qtlib::Project_Widget::outliner_row_count_root() const
{
    return root_elementids().size();
}
int Saklib::Qtlib::Project_Widget::outliner_row_count(ElementID elementid) const
{
    return outliner_children(elementid).size();
}
int Saklib::Qtlib::Project_Widget::outliner_row_count(AttributeID attributeid) const
{
    return outliner_children(attributeid).size();
}

// What is the parent of this item?
Saklib::AttributeID Saklib::Qtlib::Project_Widget::parent_of(ElementID elementid) const
{
    return m_element_manager.parent(elementid);
}
Saklib::ElementID Saklib::Qtlib::Project_Widget::parent_of(AttributeID attributeid) const
{
    return attributeid.elementid();
}

// What row is this in its parent as far as the model is concerned?
int Saklib::Qtlib::Project_Widget::outliner_row_in_parent(ElementID elementid) const
{
    auto parent = parent_of(elementid);
    auto siblings = outliner_children(parent);
    int row = 0;
    for (auto sibling : siblings)
    {
        if (sibling == elementid)
        {
            return row;
        }
        ++row;
    }
    return 0;
}
int Saklib::Qtlib::Project_Widget::outliner_row_in_parent(AttributeID attributeid) const
{
    auto parent = parent_of(attributeid);
    auto siblings = outliner_children(parent);
    int row = 0;
    for (auto sibling : siblings)
    {
        if (sibling == attributeid)
        {
            return row;
        }
        ++row;
    }
    return 0;
}



// Command History
//------------------------------------------------------------
// Provide limited access to the underlying history
//Command_History const& command_history() const;

// Will calling undo do anything?
bool Saklib::Qtlib::Project_Widget::can_undo() const
{
    return m_command_history.can_undo();
}

// Will calling redo do anything?
bool Saklib::Qtlib::Project_Widget::can_redo() const
{
    return m_command_history.can_redo();
}

// How many times can undo() be called()?
Saklib::size_type Saklib::Qtlib::Project_Widget::undo_count() const
{
    return m_command_history.undo_count();
}

// How many times can redo() be called()?
Saklib::size_type Saklib::Qtlib::Project_Widget::redo_count() const
{
    return m_command_history.redo_count();
}

// Call unexecute() in the current command and step back one in the history.
void Saklib::Qtlib::Project_Widget::undo()
{
    m_command_history.undo();
    command_history_changed();
}

// Step forward one in the history and call execute() on that command.
void Saklib::Qtlib::Project_Widget::redo()
{
    m_command_history.redo();
    command_history_changed();
}

// Clear all stored commands.
void Saklib::Qtlib::Project_Widget::clear_history()
{
    m_command_history.clear();
    command_history_changed();
}

// Call whenever commands are issued or called
void Saklib::Qtlib::Project_Widget::command_history_changed()
{
    emit signal_update_undo_actions(m_command_history.undo_count(), m_command_history.redo_count());
}

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
    return m_project_elementid;
}
Saklib::Path const& Saklib::Qtlib::Project_Widget::project_filepath() const
{
    return Saklib::attribute_type_cast<Path>(m_element_manager.attribute(m_project_filepath))->value();
}
void Saklib::Qtlib::Project_Widget::set_project_filepath(Path const& filepath)
{
    m_element_manager.element(m_project_elementid).set_name(Saklib::to_String(filepath.filename()));
    Saklib::attribute_type_cast<Path>(m_element_manager.attribute(m_project_filepath))->set_value(filepath);
}

void Saklib::Qtlib::Project_Widget::save() const
{
    emit signal_unsaved_edits(false);
}
void Saklib::Qtlib::Project_Widget::save_as(Path const& filepath)
{
    set_project_filepath(filepath);
    save();
}


// Internal
//============================================================
void Saklib::Qtlib::Project_Widget::assert_element(ElementID elementid) const
{
    assert(elementid.is_valid());
    assert(this->is_valid(elementid));
}


void Saklib::Qtlib::Project_Widget::update_widget(ElementID elementid)
{
    // if the ElementID is valid and editor is valid and is for a this ElementID
    if (m_element_manager.is_valid(elementid)
        && m_editor
        && m_editor->elementid() == elementid)
    {
        m_editor->refresh_data();
    }
}
void Saklib::Qtlib::Project_Widget::update_widget(AttributeID attributeid)
{
    // if the AttributeID is valid and editor is valid and is for this AttributeID's ElementID
    if (m_element_manager.is_valid(attributeid)
        && m_editor
        && m_editor->elementid() == attributeid.elementid())
    {
        m_editor->refresh_data(attributeid.index());
    }
}

void Saklib::Qtlib::Project_Widget::update_model(ElementID elementid)
{
    m_outliner_model->update_item(elementid);
}
void Saklib::Qtlib::Project_Widget::update_model(AttributeID attributeid)
{
    m_outliner_model->update_item(attributeid);
}
