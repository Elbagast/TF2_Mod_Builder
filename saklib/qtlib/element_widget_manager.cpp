#include "element_widget_manager.h"
#include "project_manager.h"
//#include "../command_history.h"
#include "element_widget.h"


// Special 6
//============================================================
Saklib::Qtlib::Element_Widget_Manager::Element_Widget_Manager():
    m_map()
{}

Saklib::Qtlib::Element_Widget_Manager::~Element_Widget_Manager()
{
    nullify_all_parents();
}

// Interface
//============================================================
// Build a new Element_Widget for a given ElementID and return it
// This function forwards all these arguments to the Element_Widget constructor as only
// they will need to do anything with them.
Saklib::Qtlib::Element_Widget*const Saklib::Qtlib::Element_Widget_Manager::make_widget(Command_History& command_history, Project_Manager& project_manager, ElementID elementid)
{
    // Check the validity of the ElementID
    if (project_manager.is_valid(elementid))
    {
        // Check if a widget exists already and return it if there is one...
        auto existing_widget = widget(elementid);
        if (existing_widget != nullptr)
            return existing_widget;

        // Otherwise make a new widget and return it

        // Need to figure out Element_Widget first.
        auto result = m_map.emplace(elementid, std::make_unique<Element_Widget>(command_history, project_manager, elementid));

        // if the emplace succeeded, return the resulting widget
        if (result.second)
            return result.first->second.get();

    }
    return nullptr;
}

// Destory the Element_Widget associated with this ElementID
void Saklib::Qtlib::Element_Widget_Manager::destroy_widget(ElementID elementid)
{
    m_map.erase(elementid);
}

// Is this ElementID valid for this?
bool Saklib::Qtlib::Element_Widget_Manager::has_widget(ElementID elementid) const
{
    return m_map.find(elementid) != m_map.end();
}


// Access the Element associated with this id
Saklib::Qtlib::Element_Widget*const Saklib::Qtlib::Element_Widget_Manager::widget(ElementID elementid) const
{
    auto found = m_map.find(elementid);
    if (found != m_map.end())
        return found->second.get();
    else
        return nullptr;
}
/*
Saklib::Qtlib::Element_Widget const*const Saklib::Qtlib::Element_Widget_Manager::widget(ElementID elementid) const
{
    if (mr_element_manager.is_valid(elementid))
    {
        auto found = m_map.find(elementid);
        if (found != m_map.end())
            return found->second.get();
    }
    return nullptr;
}
*/
// Refresh the data in the widget relevent to this id
void Saklib::Qtlib::Element_Widget_Manager::refresh_widget_data(ElementID elementid)
{
    auto found_widget = widget(elementid);
    if (found_widget != nullptr)
    {
        //found_widget->refresh_data();
    }
}

void Saklib::Qtlib::Element_Widget_Manager::refresh_widget_data(AttributeID attributeid)
{
    auto found_widget = widget(attributeid.elementid());
    if (found_widget != nullptr)
    {
        //found_widget->refresh_data(attributeid.index());
    }
}

// Auxillary access
Saklib::Vector_ElementID Saklib::Qtlib::Element_Widget_Manager::all_elementids() const
{
    Vector_ElementID result{m_map.size()};
    for (auto const& value : m_map)
        result.push_back(value.first);
    return result;
}

void Saklib::Qtlib::Element_Widget_Manager::nullify_all_parents()
{
    for (auto& value : m_map)
        value.second->setParent(nullptr); // stuff has been deleted by the time we've gotten here...
}

