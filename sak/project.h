#ifndef PROJECT_H
#define PROJECT_H

#include <memory>
class QString;

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
