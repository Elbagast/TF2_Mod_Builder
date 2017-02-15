#ifndef PROJECT_H
#define PROJECT_H

#include <memory>
#include <vector>
class QString;
#include <QString>

#include "fwd_file.h"

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

        QString message() const;
        QString content() const;

        // File Interface
        //============================================================

        // Are there any Files in this Project?
        bool has_files() const;

        // How many any Files are in this Project?
        std::size_t file_count() const;

        // Get the file at this index, asssuming the Files are alphabetically sorted by name
        File_Handle get_file_at(std::size_t a_index) const;

        // Get all the Files alphabetically sorted by name
        std::vector<File_Handle> get_all_files() const;

        // Get all the Files alphabetically sorted names
        std::vector<QString> get_all_file_names() const;

        // Add a new file. Project takes ownership of the File. File is inserted in
        // the appropriate place to maintain sorting and Project signals that the File list
        // has gained an item at that positon.
        File_Handle add_file(File&& a_file);

        // Remove the file at this index and return it. Project is no longer its owner.
        // Project signals that the File list has lost an item at that location.
        File_Handle remove_file_at(std::size_t a_index);

        // When the Files section has changed, this is called.
        void signal_files_changed();
        // When a File at this index has changed, this is called.
        void signal_file_changed_at(std::size_t a_index);
        // When a File has been added at this index, this is called.
        void signal_file_added_at(std::size_t a_index);
        // When a File has been removed at this index, this is called.
        void signal_file_removed_at(std::size_t a_index);


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
