#ifndef PROJECT_OBSERVER_H
#define PROJECT_OBSERVER_H

#include "types.h"

namespace saklib
{
    class Project_Manager;
    /*
    Project_Observer
    ====================================================================================================
    Interface for subclasses to accept specific signals from Project_Manager without using Qt signals.
    Doing this means the management of data can be seperate from the GUI, so that we can potentially
    not use a GUI at all if the program is called without the need for one.

    */
    class Project_Observer
    {
        friend class Project_Manager;
    public:
        explicit Project_Observer(Project_Manager& project_manager);
        virtual ~Project_Observer();

        Project_Manager& project_manager() { return mr_project_manager; }
        Project_Manager const& project_manager() const { return mr_project_manager; }
    protected:
        // Called before and after data change operations to signal Qt models to reset.
        virtual void begin_model_reset() = 0;
        virtual void end_model_reset() = 0;

        virtual void data_changed(ElementID elementid) = 0;
        virtual void data_changed(AttributeID attributeid) = 0;

        virtual void element_name_changed(ElementID elementid) = 0;
        virtual void element_parent_changed(ElementID elementid) = 0;
        virtual void element_destroyed(ElementID elementid) = 0;

        virtual void attribute_value_changed(AttributeID attributeid) = 0;

        virtual void unsaved_edits_changed(bool state) = 0;
        virtual void undo_counts_changed(size_type undo_count, size_type redo_count) = 0;

    private:
        Project_Manager& mr_project_manager;
    };

} //namespace saklib

#endif // PROJECT_OBSERVER_H
