#ifndef SAK_PROJECT_INTERFACE_HPP
#define SAK_PROJECT_INTERFACE_HPP

#ifndef SAK_PROJECT_INTERFACE_FWD_HPP
#include "project_interface_fwd.hpp"
#endif

#ifndef SAK_PROJECT_DATA_FWD_HPP
#include "project_data_fwd.hpp"
#endif

#ifndef SAK_ABSTRACT_PROJECT_SIGNALBOX_FWD_HPP
#include "abstract_project_signalbox_fwd.hpp"
#endif

#ifndef SAK_COMMAND_HISTORY_FWD_HPP
#include "command_history_fwd.hpp"
#endif

#ifndef SAK_SECTION_INTERFACE_FWD_HPP
#include "section_interface_fwd.hpp"
#endif

class QString;

namespace sak 
{
  //---------------------------------------------------------------------------
  // Project_Interface
  //---------------------------------------------------------------------------
  // Provides an interface to Project_Data that intercepts direct calls and
  // makes them into undoable commands stored in the supplied Command_History.

  class Project_Interface
  {
  public:
    // Special 6
    //============================================================
    // Construct using Project_Data*. This is not owned. calling delete on this
    // pointer will invalidate Project_Interface.
    Project_Interface(Project_Data* a_data, Command_History* a_command_history);
    ~Project_Interface();

    Project_Interface(Project_Interface const&);
    Project_Interface& operator=(Project_Interface const&);

    Project_Interface(Project_Interface &&);
    Project_Interface& operator=(Project_Interface &&);

    // Interface
    //============================================================
    // If the final interface allows it, saving and loading should probably not be
    // member functions.

    // Save the current data to the file.
    void save() const;

    // Get the data from the file and discard the current data.
    void load();
    
    // Data that is fixed on contruction.
    QString name() const;
    QString location() const;
    QString filepath() const;

    // Add an object that will rely on the Project's signals. If nulltpr, nothing happens.
    void add_signalbox(Abstract_Project_Signalbox* a_signalbox);

    // Remove an object that will rely on the Project's signals. If nulltpr, nothing happens.
    void remove_signalbox(Abstract_Project_Signalbox* a_signalbox);

    // Can we currently call undo?
    bool can_undo() const;

    // Can we currently call redo?
    bool can_redo() const;

    // How many times can undo() be called?
    std::size_t undo_count() const;

    // How many times can redo() be called?
    std::size_t redo_count() const;

    // Undo the last command issued.
    void undo();

    // Redo the last undone command in the command history
    void redo();

    // Clear the undo/redo history.
    void clear_history();

    // Section interfaces
    template <typename T>
    Section_Interface<T> get_interface();

    File_Interface get_file_interface();
    Texture_Interface get_texture_interface();

  private:
    // Data
    //============================================================
    Project_Data* m_project_data;
    Command_History* m_command_history;
  };
  
  // Section interface could probably go here...then it can be friends and the usage
  // is a bit more obvious.
}

#endif // SAK_PROJECT_INTERFACE_HPP
