#include "project_observer.h"
#include "project_manager.h"

Saklib::Project_Observer::Project_Observer(Project_Manager& project_manager):
    mr_project_manager(project_manager)
{
    mr_project_manager.add_observer(this);
}

Saklib::Project_Observer::~Project_Observer()
{
    mr_project_manager.remove_observer(this);
}

