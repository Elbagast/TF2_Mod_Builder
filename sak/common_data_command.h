#ifndef COMMON_DATA_COMMAND_H
#define COMMON_DATA_COMMAND_H

#include "../generic/command.h"
#include "fwd_file.h"
class QString;
#include <memory>

namespace sak
{
    class Project;


    std::unique_ptr<generic::abstract::Command> make_command_set_name(QString const& a_value, File_Handle const& a_handle, Project* a_project);
    std::unique_ptr<generic::abstract::Command> make_command_set_description(QString const& a_value, File_Handle const& a_handle, Project* a_project);
}

#endif // COMMON_DATA_COMMAND_H
