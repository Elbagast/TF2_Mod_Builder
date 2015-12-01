#include "project_observer.h"
#include "project_manager.h"

saklib::Project_Observer::Project_Observer(Project_Manager& project_manager):
    mr_project_manager(project_manager)
{
    mr_project_manager.add_observer(this);
}

saklib::Project_Observer::~Project_Observer()
{
    mr_project_manager.remove_observer(this);
}

