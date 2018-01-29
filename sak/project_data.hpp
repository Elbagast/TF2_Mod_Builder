#ifndef SAK_PROJECT_DATA_HPP
#define SAK_PROJECT_DATA_HPP

#ifndef SAK_PROJECT_DATA_FWD_HPP
#include "project_data_fwd.hpp"
#endif

#ifndef SAK_ABSTRACT_PROJECT_SIGNALBOX_FWD_HPP
#include "abstract_project_signalbox_fwd.hpp"
#endif

#include "section_data_manager_fwd.hpp"

#include "section_handle_fwd.hpp"
#include "section_interface_fwd.hpp"


#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif

#ifndef INCLUDE_STD_VECTOR
#define INCLUDE_STD_VECTOR
#include <vector>
#endif
/*
#ifndef INCLUDE_QT_QSTRING
#define INCLUDE_QT_QSTRING
#include <QString>
#endif
*/
class QString;

namespace sak
{
  //---------------------------------------------------------------------------
  // Project_Data
  //---------------------------------------------------------------------------
  /*
  Has:
  - filepath to the project file
  - root directory (that filepath is in)
  - sub directories and files as needed
  - data

  Widget has:
  - outliner displaying the data structure
  - list of widgets for open components
  - those widgets relay changes

  Thus:
  Operating on a model-view setup:
  - Project_Data stores and provides access to data anywhere in the structure
  - The handles capture attempts to edit the data
  - Changes propagate out of the data
  - Widget reads and displays the data as necessary

  Also:
  - Project_Data will handle all operations on files it manages
  - amy be worth stepping away from qt to do this

  Other:
  - Decide on exception classes for these operations, what library does them etc.


  Decisions:
  - Project is responsible for:
      - owning data and supplying access to it.
      - saving and loading.
      - signalling when and where data has changed to anything that cares.
  - Project_Widget is responsible for:
      - owning Project.
      - owning widgets.
      - maintaining model accuracy.

  Structure:
  - Currently the Project does not actually need to own the data management system.
  - It should probably own its undo system?

  Reorganising:
  - Generalising the internal structure means some stuff needs to be moved around.
  - However we need an unambiguous interface to all the types it holds.
  - Thus the public interface of Project is slightly different from the signals that
    shared:: types must make...
  - Use shared::dispatch_signals<T> to make the disambiguous functions usable by the templates.

  - This would be simpler if a class could contain a namespace...

  =============
  New thinking
  Looking over the structure we have things have gotten rather compolicated and circular.
  We have interface issues and the current setup means we're adapting the function calls
  twice: once when the shared::project_access template renames the function calls, and
  again internally when the named functions access the appropriate internal managers. This
  means that the code duplication we hoped to eliminate is still happening.

  This object must provide:
  - Read interface for each type
  - Write interface for each type
    - Resulting in internal command wrappers for
  - Expandable outbound signalling for each type
    - Detailing the user source of the signals
      - e.g. change made in outliner/editor/undo call/redo call/etc.

  Currently this is handled by the shared::project_access template for templated access
  to data, but it's messy as hell.

  */

  class Project_Data
  {
  public:
    // Special 6
    //============================================================
    // Construct the project using the supplied filename. If the directory
    // does not exist or is inaccessible it will fail. If the file does
    // not exist it will attempt to create it and save the initial data
    // to it. If the file exists it will attempt to load the data from it.
    //Project_Data();
    explicit Project_Data(QString const& a_filepath);
    ~Project_Data();

    Project_Data(Project_Data const&) = delete;
    Project_Data& operator=(Project_Data const&) = delete;

    Project_Data(Project_Data &&);
    Project_Data& operator=(Project_Data &&);

    // Interface
    //============================================================
    // If the final interface allows it, saving and loading should probably not be
    // member functions.

    // Save the current data to the file.
    //void save() const;

    // Get the data from the file and discard the current data.
    //void load();

    // if you want to move save/load then these need to move too.
    QString name() const;
    QString location() const;
    QString filepath() const;

    // Add an object that will rely on the Project's signals. If nulltpr, nothing happens.
    void add_signalbox(Abstract_Project_Signalbox* a_signalbox);

    // Remove an object that will rely on the Project's signals. If nulltpr, nothing happens.
    void remove_signalbox(Abstract_Project_Signalbox* a_signalbox);

    // Clear all the signalboxes so that nothing relies on changes to this.
    void clear_signalboxes();
    
    // Section data managers
    template <typename T>
    Section_Data_Manager<T>* get_manager();

    File_Data_Manager* get_file_manager();
    Texture_Data_Manager* get_texture_manager();

    // Section data managers
    template <typename T>
    Section_Data_Manager<T> const* cget_manager() const;

    File_Data_Manager const* cget_file_manager() const;
    Texture_Data_Manager const* cget_texture_manager() const;

  private:
    // Pimpl Data
    //============================================================
    class Implementation;
    std::unique_ptr<Implementation> m_data;

    Implementation& imp()                { return *m_data; }
    Implementation const& cimp() const   { return *m_data; }
  };
}

#endif // SAK_PROJECT_DATA_HPP
