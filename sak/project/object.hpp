#ifndef SAK_PROJECT_OBJECT_HPP
#define SAK_PROJECT_OBJECT_HPP

#include "fwd/object.hpp"
#include "fwd/signalbox.hpp"
//#include "fwd/command.hpp"

#include <sak/shared/object.hpp>
#include <sak/shared/fwd/manager.hpp>
//#include <sak/shared/fwd/signalbox.hpp>

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


      // File Interface
      //============================================================
      // This is the interface that deals with Files.

      // Are there any Files in this Project?
      bool has_files() const;

      // How many any Files are in this Project?
      std::size_t file_count() const;

      // Get the file at this index
      file::handle get_file_at(std::size_t a_index) const;

      // Get all the Files
      std::vector<file::handle> get_all_files() const;

      // Get all the Files names
      std::vector<QString> get_all_file_names() const;

      // Make a new file using the supplied data. Project's data management system owns it but
      // it is not part of the Project.
      file::handle make_emplace_file(file::object&& a_file);

      // Make a new file using the default parameters. Project's data management system owns it
      // but it is not part of the Project.
      file::handle make_file();

      // Create a new default file and add it.
      void file_add_new();

      // Add a new file using the supplied data.
      void file_add_emplace(file::object&& a_file);

      // Add a new file using the supplied handle. If this handle is invalid or already in the data
      // then nothing happens.
      void file_add(file::handle const& a_handle);

      // Remove this file. It is removed from the file list and the data of anything that references it.
      // Data is not deleted until the last reference is deleted.
      void file_remove(file::handle const& a_handle);

      // Change a file's member value.
      void file_change_at(file::handle const& a_handle, std::size_t a_section, typename file::object::member_value_variant const& a_variant);

      // Request that the focus change to this file.
      void file_request_focus(file::handle const& a_handle);

      // Request that the editor for this file be opened or switched to.
      void file_request_editor(file::handle const& a_handle);

      // Texture Interface
      //============================================================
      // This is the interface that deals with textures.

      // Are there any textures in this Project?
      bool has_textures() const;

      // How many any textures are in this Project?
      std::size_t texture_count() const;

      // Get the texture at this index
      texture::handle get_texture_at(std::size_t a_index) const;

      // Get all the textures
      std::vector<texture::handle> get_all_textures() const;

      // Get all the textures names
      std::vector<QString> get_all_texture_names() const;

      // Make a new texture using the supplied data. Project's data management system owns it but
      // it is not part of the Project.
      texture::handle make_emplace_texture(texture::object&& a_texture);

      // Make a new texture using the default parameters. Project's data management system owns it
      // but it is not part of the Project.
      texture::handle make_texture();

      // Create a new default texture and add it.
      void texture_add_new();

      // Add a new texture using the supplied data.
      void texture_add_emplace(texture::object&& a_texture);

      // Add a new texture using the supplied handle. If this handle is invalid or already in the data
      // then nothing happens.
      void texture_add(texture::handle const& a_handle);

      // Remove this texture. It is removed from the texture list and the data of anything that references it.
      // Data is not deleted until the last reference is deleted.
      void texture_remove(texture::handle const& a_handle);

      // Change a texture's member value.
      void texture_change_at(texture::handle const& a_handle, std::size_t a_section, typename texture::object::member_value_variant const& a_variant);

      // Request that the focus change to this texture.
      void texture_request_focus(texture::handle const& a_handle);

      // Request that the editor for this texture be opened or switched to.
      void texture_request_editor(texture::handle const& a_handle);

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
