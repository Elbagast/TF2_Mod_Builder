#ifndef FILE_COMMAND_HPP
#define FILE_COMMAND_HPP

#include "../generic/command.hpp"
#include "fwd_file.hpp"
class QString;
#include <memory>

namespace sak
{
    class Project;


    std::unique_ptr<generic::abstract::Command> make_command_set_buildpath(QString const& a_value, File_Handle const& a_handle, Project* a_project);
    std::unique_ptr<generic::abstract::Command> make_command_set_sourcepath(QString const& a_value, File_Handle const& a_handle, Project* a_project);
}
#endif // FILE_COMMAND_HPP
