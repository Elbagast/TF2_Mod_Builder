#ifndef ELEMENT_EDITOR_H
#define ELEMENT_EDITOR_H

#include "types.h"
#include "all_element.h"
#include "element_manager.h"
#include "elementid.h"
#include "command_history.h"
#include "command_attribute.h"

namespace Saklib
{
    /*
    Element_Editor
    ====================================================================================================
    Class which contains a single root Element and all of the facilities to edit the structure of it
    with undoable operations.
    */

    class Element_Editor
    {
    public:
        // Special 6
        //============================================================
        // Root is only set on construction.
		explicit Element_Editor(String const& root_type) :
			m_element_manager(),
			m_command_history(),
			m_root_elementid(&m_element_manager, root_type)
        {
            m_root_elementid.element().set_name("Root");
        }
        // Implicit default destructor

        // NO COPYING
        Element_Editor(Element_Editor const& other) = delete;
        Element_Editor& operator=(Element_Editor const& other) = delete;

        // Implicit default move

        // Root Element and Attribute Access
        //============================================================
		Element_Manager& manager() { return m_element_manager; }

        ElementID root_elementid() const                            { return m_root_elementid; }
        Element& root_element()                                     { return m_root_elementid.element(); }
        Element const& root_element() const                         { return m_root_elementid.element(); }

        AttributeID root_attributeid(String const& name) const { return AttributeID(m_root_elementid, name); }

        // Access Attributes of the Element this references
        Attribute* root_attribute(String const& name) const    { return m_root_elementid.attribute(name); }

        // Get a pointer to a derived Attribute type for the Attribute specified by name
        template <typename T_Stored_Type>
        Attribute_Type<T_Stored_Type>* root_attribute_type_cast(String const& name) const
        {
            return m_root_elementid.element().attribute_type_cast<T_Stored_Type>(name);
        }

        template <Type_Enum TE>
        Attribute_Type<TypeHolder_st<TE> >* root_attribute_enum_cast(String const& name) const
        {
            return m_root_elementid.element().attribute_enum_cast<TE>(name);
        }

        // Other Element and Attribute Access
        //============================================================
		// Construct a new Element within this Editor
		ElementID make_ElementID(String const& element_type)
		{
			return ElementID(&m_element_manager, element_type);
		}
        // Access to the Element manager so that we can get other Elements to play with...
        // Get a list of all ElementIDs currently in the data structure...
		// Otherwise we'll have to walk the structure to get to Elements


        // Element and Attribute Editing via commands...
        //============================================================
        
        // now we get to the meat. we need to check against contraints and issue a command if there would be success.
        // Doing this means the editor / user checks for constraints before attempting to edit with commands.

        template <typename T>
        bool root_attribute_try_set(String const& name, T const& value)
        {
            return attribute_try_set<T>(AttributeID(m_root_elementid, name), value);
        }

        // Start simple:
		template <typename T>
		bool attribute_can_set_to(AttributeID const& attributeid, T const& value)
		{
			Attribute_Type<T>* typed_attribute = attributeid.attribute_type_cast<T>();
			if (typed_attribute != nullptr              // the cast succeeded, i.e. a typematch,
				&& typed_attribute->get() != value      // ane this wouldn't be a pointless edit,
				&& typed_attribute->can_set_to(value))  // and it can be set to this value
			{
				return true; // could test if the command executed properly...
			}
			else
				return false;
		}

        template <typename T>
        bool attribute_try_set(AttributeID const& attributeid, T const& value)
        {
            Attribute_Type<T>* typed_attribute = attributeid.attribute_type_cast<T>();
            if (typed_attribute != nullptr              // the cast succeeded, i.e. a typematch,
                && typed_attribute->get() != value      // ane this wouldn't be a pointless edit,
                //&& typed_attribute->can_set_to(value)  // and it can be set to this value
				)
            {
                // Issue an undoable command for this operation
				m_command_history.emplace_execute<Command_Attribute_Set<T>>(attributeid, value); // Commands can't use raw Attribute pointers since they don't guarantee lifetime
                return true; // could test if the command executed properly...
            }
            else
                return false;
        }

        // Vector operations....need to define them all first...

        // Command History Access
        //============================================================
        // These are all forwarding functions.
		Command_History const& command_history() const { return m_command_history; }

        // Will calling undo do anything?
		bool can_undo() const           { return m_command_history.can_undo(); }
        // Will calling redo do anything?
		bool can_redo() const           { return m_command_history.can_redo(); }

        // How many commands are stored?
		size_type size() const          { return m_command_history.size(); }
        // Is the container empty?
		bool empty() const              { return m_command_history.empty(); }

        // How many times can undo() be called()?
		size_type undo_count() const    { return m_command_history.undo_count(); }
        // How many times can redo() be called()?
		size_type redo_count() const    { return m_command_history.redo_count(); }

        // Call unexecute() in the current command and step back one in the history.
		void undo()                     { m_command_history.undo(); }
        // Step forward one in the history and call execute() on that command.
		void redo()                     { m_command_history.redo(); }

        // Clear all stored commands.
		void clear()                    { m_command_history.clear(); }

    private:
		Element_Manager m_element_manager;
		Command_History m_command_history;
        ElementID m_root_elementid; // in an Attribute_Type<ElementID> ?

        // If we wanted to cache all the ElementIDs for those in the data structure, it should probably be here...
    };

} // namespace Saklib

#endif // ELEMENT_EDITOR_H