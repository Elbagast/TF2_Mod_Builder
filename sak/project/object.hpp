#ifndef SAK_PROJECT_OBJECT_HPP
#define SAK_PROJECT_OBJECT_HPP

#include "fwd/object.hpp"
#include "fwd/signalbox.hpp"
//#include "fwd/command.hpp"

#include <sak/shared/object.hpp>
#include <sak/shared/fwd/manager.hpp>
//#include <sak/shared/fwd/signalbox.hpp>
#include <sak/shared/fwd/interface.hpp>

#include <memory>
#include <vector>
#include <QString>

namespace sak
{
  namespace project
  {
    //---------------------------------------------------------------------------
    // project::object
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

    class object
    {
    public:
      // Special 6
      //============================================================
      // Construct the project using the supplied filename. If the directory
      // does not exist or is inaccessible it will fail. If the file does
      // not exist it will attempt to create it and save the initial data
      // to it. If the file exists it will attempt to load the data from it.
      explicit object(QString const& a_filepath);
      ~object();

      object(object const&) = delete;
      object& operator=(object const&) = delete;

      object(object &&);
      object& operator=(object &&);


      // Interface
      //============================================================
      // If the final interface allows it, saving and loading should probably not be
      // member functions.

      // Save the current data to the file.
      void save() const;

      // Get the data from the file and discard the current data.
      void load();

      QString name() const;
      QString location() const;
      QString filepath() const;

      // Add an object that will rely on the Project's signals. If nulltpr, nothing happens.
      void add_signalbox(abstract::signalbox* a_signalbox);

      // Remove an object that will rely on the Project's signals. If nulltpr, nothing happens.
      void remove_signalbox(abstract::signalbox* a_signalbox);

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

      // Commands get sent here.
      //void emplace_execute(std::unique_ptr<abstract::command>&& a_command); //should this even be exposed? probably not...

      // Clear the undo/redo history.
      void clear_history();

      // Section interfaces
      template <typename T>
      shared::interface<T> get_interface();

      file::interface get_file_interface();
      texture::interface get_texture_interface();

    private:
      // Pimpl Data
      //============================================================
      class impl;
      std::unique_ptr<impl> m_data;

      impl& imp()                { return *m_data; }
      impl const& cimp() const   { return *m_data; }
    };
  }
}

#endif // SAK_PROJECT_OBJECT_HPP
