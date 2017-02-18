#ifndef PROJECT_H
#define PROJECT_H

#include <memory>
#include <vector>
class QString;
#include <QString>

#include "fwd_file.h"

namespace sak
{
    class Project_Signalbox;
    class Project_File_Signalbox;
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

        // Add an object that will rely on the Project's signals. If nulltpr, nothing happens.
        void add_signalbox(Project_File_Signalbox* a_signalbox);

        // Remove an object that will rely on the Project's signals. If nulltpr, nothing happens.
        void remove_signalbox(Project_File_Signalbox* a_signalbox);


        // File Interface
        //============================================================

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

        // Add a new file. Project takes ownership of the File. File is inserted in
        // the appropriate place to maintain sorting and Project signals that the File list
        // has gained an item at that positon.
        File_Handle add_file(File&& a_file);

        // Add a new default parameters File.
        File_Handle add_new_file();

        // Remove the File with this handle.
        void remove_file(File_Handle const& a_file);



        //-----------
        // File_Handle gives File_Interface.
        // File_Interface does what needs to be done without revealing it.
        // Only File_Interface needs these functions, so they should probably be hidden somehow.

        // Outliner File_Interface Interface
        //============================================================
        // File_Interface will call this when the File's name is changed. This causes Project
        // to propagate the changes to where they need to go.
        void file_name_changed(File_Basic_Handle const& a_file);

        // File_Interface will call this when the File's data is changed. This causes Project
        // to propagate the changes to where they need to go.
        void file_data_changed(File_Basic_Handle const& a_file);


        // Outliner File_Item Interface
        //============================================================
        // outliner::File_Item calls this to request an editor. Project propagates the signal
        // to anything that needs to change as a result.
        void file_requests_editor(File_Handle const& a_file);
        // This could be in the handle....

        // Project_Editor calls this to request a File be focused on.
        void file_requests_focus(File_Handle const& a_file);

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
