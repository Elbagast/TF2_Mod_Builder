#ifndef PROJECT_H
#define PROJECT_H

#include <memory>
#include <vector>
class QString;
#include <QString>

#include "fwd_file.h"
#include "project_signalbox.h"
#include "../generic/command.h"

namespace sak
{
    //---------------------------------------------------------------------------
    // Project
    //---------------------------------------------------------------------------
    // temporary implementation
    // Operating on the assumption that the widget handles display of data and
    // providing a mechanism for editing data, what does a Project have and
    // what does it need to provide?
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
    */
    class Project
    {
    public:
        // Special 6
        //============================================================
        // Construct the project using the supplied filename. If the directory
        // does not exist or is inaccessible it will fail. If the file does
        // not exist it will attempt to create it and save the initial data
        // to it. If the file exists it will attempt to load the data from it.
        Project(QString const& a_filepath);
        ~Project();

        Project(Project const&) = delete;
        Project& operator=(Project const&) = delete;

        Project(Project &&);
        Project& operator=(Project &&);


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
        void add_signalbox(Project_Signalbox* a_signalbox);

        // Remove an object that will rely on the Project's signals. If nulltpr, nothing happens.
        void remove_signalbox(Project_Signalbox* a_signalbox);

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
        void emplace_execute(std::unique_ptr<generic::abstract::Command>&& a_command);


        // File Interface
        //============================================================
        // This is the interface that deals with Files.

        // Are there any Files in this Project?
        bool has_files() const;

        // How many any Files are in this Project?
        std::size_t file_count() const;

        // Get the file at this index
        File_Handle get_file_at(std::size_t a_index) const;

        // Get all the Files
        std::vector<File_Handle> get_all_files() const;

        // Get all the Files names
        std::vector<QString> get_all_file_names() const;

        // You may create new Files using these two functions. Files created in this way
        // are part of the Project's data management system but have not yet been added to the
        // Project properly. That will only happen when the Project recieves a signal via its
        // Project_Signalbox that it should be addeed.

        // Make a new file using the supplied data. Project's data management system owns it but
        // it is not part of the Project.
        File_Handle make_emplace_file(File&& a_file);

        // Make a new file using the default parameters. Project's data management system owns it
        // but it is not part of the Project.
        File_Handle make_file();

        // To signal that something should be done to the project, you may access the signalbox
        // for a specific type, then call the signals to make and propagate changes.
        Project_Signalbox* get_signalbox() const;

        // If we're exposing the signals like this should we not just supply the functions outright here?


        //============================================================

    private:
        // Pimpl Data
        //============================================================
        class Implementation;
        std::unique_ptr<Implementation> m_data;

        Implementation& imp()                { return *m_data; }
        Implementation const& cimp() const   { return *m_data; }
    };
}

#endif // PROJECT_H
