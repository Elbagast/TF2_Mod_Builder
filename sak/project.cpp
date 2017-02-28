#include "project.hpp"

#include <QString>
#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>
#include <cassert>
#include <algorithm>
#include <iterator>

#include "project_signalbox.hpp"
#include "exceptions/exception.hpp"
#include "shared/manager.hpp"
#include "shared/extended_manager.hpp"
#include "../generic/command_history.hpp"
#include "name_utilities.hpp"

//---------------------------------------------------------------------------
// Project
//---------------------------------------------------------------------------
namespace
{
    template <typename T, typename... Args>
    void emit_signals_for(std::vector<T*>& a_vector, void(T::*a_func)(Args...), Args&&... a_args)
    {
        for (auto l_item : a_vector)
        {
            l_item.(*a_func)(std::forward<Args>(a_args)...);
        }
    }
}



// Pimpl Data
//============================================================
namespace sak
{
    class Project::Implementation :
            public Project_Signalbox
    {
    public:
        QFileInfo m_filepath;
        QString m_message;
        QString m_data;
        file::extended_manager m_file_manager;

        std::vector<file::extended_handle> m_files;

        std::vector<Project_Signalbox*> m_dependents;
        generic::Command_History m_command_history;

        Implementation(QString const& a_filepath, Project* a_owner):
            Project_Signalbox(),
            m_filepath{a_filepath},
            m_file_manager{file::interface_traits(a_owner)},
            m_files{},
            m_dependents{},
            m_command_history{}
        {
        }
        ~Implementation() = default;

        // Signalbox Interface
        //============================================================
        // Call these to call the signalbox functions in all dependents.

        // When a File has its data changed(anything but the name), this is called.
        void changed(file::extended_handle const& a_file) override final
        {
            qDebug() << "\nProject::Implementation::change";
            // This thing must exist
            assert(a_file.is_valid());
            assert(std::find(m_files.cbegin(), m_files.cend(), a_file) != m_files.cend());
            for (auto l_item : m_dependents)
            {
                l_item->changed(a_file);
            }
        }
        // When a File has its data changed in a specific place, this is called.
        void changed_at(file::extended_handle const& a_file, std::size_t a_section) override final
        {
            qDebug() << "\nProject::Implementation::changed_at " << a_section;
            // This thing must exist
            assert(a_file.is_valid());
            assert(std::find(m_files.cbegin(), m_files.cend(), a_file) != m_files.cend());
            for (auto l_item : m_dependents)
            {
                l_item->changed_at(a_file, a_section);
            }
        }
        // When a File has been added, this is called.
        void added(file::extended_handle const& a_file) override final
        {
            qDebug() << "\nProject::Implementation::added";
            // This thing must exist
            assert(a_file.is_valid());
            // but not yet be part of the Project
            assert(std::find(m_files.cbegin(), m_files.cend(), a_file) == m_files.cend());
            m_files.push_back(a_file);

            for (auto l_item : m_dependents)
            {
                l_item->added(a_file);
            }
        }
        // When a File has been removed, this is called.
        void removed(file::extended_handle const& a_file) override final
        {
            qDebug() << "\nProject::Implementation::removed";
            assert(a_file.is_valid());
            auto l_found = std::find(m_files.begin(), m_files.end(), a_file);
            assert(l_found != m_files.cend());
            assert(std::addressof(a_file) != std::addressof(*l_found));

            // Copy the file::extended_handle locally. We don't know where it came from and have to propagate
            // the signal from here rather than who knows where to insure the signal reference stays
            // valid for all that need it.
            file::extended_handle l_file = a_file;
            // Now kill it, because if it's still in the project the signal will call back to find it
            // is still present.
            m_files.erase(l_found);

            // Now signal with the copy we made.
            for (auto l_item : m_dependents)
            {
                l_item->removed(l_file);
            }
        }
        // When a File requests an editor, this is called.
        void requests_editor(file::extended_handle const& a_file) override final
        {
            qDebug() << "\nProject::Implementation::requests_editor";
            // This thing must exist
            assert(a_file.is_valid());
            assert(std::find(m_files.cbegin(), m_files.cend(), a_file) != m_files.cend());
            for (auto l_item : m_dependents)
            {
                l_item->requests_editor(a_file);
            }
        }

        // When a File requests an editor, this is called.
        void requests_focus(file::extended_handle const& a_file) override final
        {
            qDebug() << "\nProject::Implementation::requests_focus";
            // This thing must exist
            assert(a_file.is_valid());
            assert(std::find(m_files.cbegin(), m_files.cend(), a_file) != m_files.cend());
            for (auto l_item : m_dependents)
            {
                l_item->requests_focus(a_file);
            }
        }

    };
}

// Special 6
//============================================================
// Construct the project using the supplied filename. If the directory
// does not exist or is inaccessible it will fail. If the file does
// not exist it will attempt to create it and save the initial data
// to it. If the file exists it will attempt to load the data from it.
sak::Project::Project(QString const& a_filepath):
    m_data{std::make_unique<Implementation>(a_filepath, this)}
{
    // If the directory does not exist it will fail.
    if(!imp().m_filepath.dir().exists())
    {
        // Failure exception for directory not existing.
        throw Directory_Missing_Error(imp().m_filepath.absoluteDir().absolutePath());
        //data().m_message = u8"Failure exception for directory not existing.";
    }
    /*
    if(!data().m_filepath.dir().isReadable())
    {
        // Failure exception for directory access.
        data().m_message = u8"Failure exception for directory access.";
    }
    */
    // if the file exists, load it
    if(cimp().m_filepath.exists())
    {
        load();
    }
    // else make a new file using the empty initialsed data.
    else
    {
        save();
    }
/*
    this->add_file(File("dummy1", "poop"));
    this->add_file(File("dummy2", "pee"));
    this->add_file(File("dummy3", "pee"));
    this->add_file(File("dummy4", "pee"));

    auto l_temp = this->get_file_at(0);
    assert(l_temp.ref_count() == 2);
    {
        auto l_temp2 = l_temp;
        assert(l_temp.ref_count() == 3);
    }
    assert(l_temp.ref_count() == 2);
    assert(cimp().m_files.size() == 4);*/
}
sak::Project::~Project() = default;

sak::Project::Project(Project &&) = default;
sak::Project& sak::Project::operator=(Project &&) = default;

// Interface
//============================================================
// Save the current data to the file.
void sak::Project::save() const
{
   QFile l_file{(cimp().m_filepath.absoluteFilePath())};
   if (l_file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text))
   {
       //qDebug() << "File opened";

       //QTextStream out_stream(&file);

       //qDebug() << static_cast<QFile*>(out_stream.device())->fileName();
       QXmlStreamWriter xml_stream{&l_file};
       xml_stream.setAutoFormatting(true);
       xml_stream.writeStartDocument();

       // start the element that contains all the data
       xml_stream.writeStartElement("Project");

       // Start the Files block
       xml_stream.writeStartElement("Files");
       xml_stream.writeTextElement("Count", QString::number(cimp().m_files.size()));

       for (auto const& l_file : cimp().m_files)
       {
           xml_stream.writeStartElement("File");
           xml_stream.writeTextElement("Name", l_file.cget().cat<0>().cget());
           xml_stream.writeTextElement("Description", l_file.cget().cat<1>().cget());
           xml_stream.writeTextElement("Buildpath", l_file.cget().cat<2>().cget());
           xml_stream.writeTextElement("Sourcepath", l_file.cget().cat<3>().cget());
           xml_stream.writeEndElement();
       }

       // End the Files block
       xml_stream.writeEndElement();


       // end the element that contains all the data
       xml_stream.writeEndElement();

       xml_stream.writeEndDocument();

       l_file.close();
   }
   else
   {
       throw File_Write_Error(cimp().m_filepath.absoluteFilePath());
   }
}

// Get the data from the file and discard the current data.
void sak::Project::load()
{
    // Initialise new data
    auto l_data{std::make_unique<Implementation>(cimp().m_filepath.absoluteFilePath(),this)};

    // Create a file object
    QFile l_file{cimp().m_filepath.absoluteFilePath()};

    // Attempt to open the file to read it
    if (l_file.exists() && l_file.open(QFile::ReadOnly | QFile::Text))
    {
        // make an xml stream
        QXmlStreamReader xml_stream{&l_file};

        // <Project>
        if (xml_stream.readNextStartElement() && xml_stream.name().toString() == "Project")
        {
            // Read the Files
            if (xml_stream.readNextStartElement() && xml_stream.name().toString() == "Files")
            {
                //qDebug() << "Files:";


                int l_count {0};

                // <Count>
                if (xml_stream.readNextStartElement() && xml_stream.name().toString() == "Count")
                {
                    l_count = xml_stream.readElementText().toInt();
                    //qDebug() << "Count = " << l_count;

                    // </Count>
                    xml_stream.readNext();
                }
                else
                {
                    qDebug() << "Didn't find File Count";
                    // file format error
                }

                l_data->m_files.reserve(l_count);
                // read the files
                for (int l_index = 0; l_index != l_count; ++l_index)
                {
                    if (xml_stream.readNextStartElement() && xml_stream.name().toString() == "File")
                    {
                        file::object l_file{};
                        //qDebug() << "File: "<< l_index ;
                        // <Name>
                        if (xml_stream.readNextStartElement() && xml_stream.name().toString() == "Name")
                        {
                            auto l_data = xml_stream.readElementText();
                            //qDebug() << "Name: " << l_data;
                            l_file.at<0>().get() = l_data;

                            // </Name>
                            xml_stream.readNext();
                        }
                        else
                        {
                            qDebug() << "Didn't find Name" ;
                        }
                        // <Description>
                        if (xml_stream.readNextStartElement() && xml_stream.name().toString() == "Description")
                        {
                            auto l_data = xml_stream.readElementText();
                            //qDebug() << "Description:" << l_data;
                            l_file.at<1>().get() = l_data;

                            // </Description>
                            xml_stream.readNext();
                        }
                        else
                        {
                            qDebug() << "Didn't find Description" ;
                        }
                        // <Buildpath>
                        if (xml_stream.readNextStartElement() && xml_stream.name().toString() == "Buildpath")
                        {
                            auto l_data = xml_stream.readElementText();
                            //qDebug() << "Description:" << l_data;
                            l_file.at<2>().get() = l_data;

                            // </Buildpath>
                            xml_stream.readNext();
                        }
                        else
                        {
                            qDebug() << "Didn't find Buildpath" ;
                        }
                        // <Sourcepath>
                        if (xml_stream.readNextStartElement() && xml_stream.name().toString() == "Sourcepath")
                        {
                            auto l_data = xml_stream.readElementText();
                            //qDebug() << "Description:" << l_data;
                            l_file.at<3>().get() = l_data;

                            // </Sourcepath>
                            xml_stream.readNext();
                        }
                        else
                        {
                            qDebug() << "Didn't find Sourcepath" ;
                        }
                        // Read the end element
                        xml_stream.readNext();

                        auto l_handle = l_data->m_file_manager.emplace_data(std::move(l_file));
                        l_data->m_files.push_back(std::move(l_handle));

                    }
                    else
                    {
                        qDebug() << "Didn't find File " << l_index ;
                    }

                }
                // </Files>
                xml_stream.readNext();

            }
            else
            {
                // Bad file structure
                qDebug() << "Didn't find Filepath";
            }

            // </Project>
            xml_stream.readNext();
        }
        else
        {
            // Bad file structure
            qDebug() << "Didn't find Project";
        }

        l_file.close();

        // Replace the current data and consign it to oblivion. The data
        // is now that which has been loaded.
        std::swap(m_data, l_data);
    }
    else
    {
        // Failure exception for file loading.
        throw File_Read_Error(imp().m_filepath.absoluteFilePath());
    }
}

QString sak::Project::name() const
{
    return cimp().m_filepath.baseName();
}

QString sak::Project::location() const
{
    return cimp().m_filepath.absolutePath();
}

QString sak::Project::filepath() const
{
    return cimp().m_filepath.absoluteFilePath();
}


// Add an object that will rely on the Project's signals. If nulltpr, nothing happens.
void sak::Project::add_signalbox(Project_Signalbox* a_signalbox)
{
    if (a_signalbox != nullptr
        && a_signalbox != m_data.get()
        && std::find(cimp().m_dependents.cbegin(), cimp().m_dependents.cend(), a_signalbox) == cimp().m_dependents.cend())
    {
        imp().m_dependents.push_back(a_signalbox);
    }
}

// Remove an object that will rely on the Project's signals. If nulltpr, nothing happens.
void sak::Project::remove_signalbox(Project_Signalbox* a_signalbox)
{
    auto l_found = std::find(cimp().m_dependents.cbegin(), cimp().m_dependents.cend(), a_signalbox);
    if (l_found != cimp().m_dependents.cend())
    {
        imp().m_dependents.erase(l_found);
    }
}

// Can we currently call undo?
bool sak::Project::can_undo() const
{
    return cimp().m_command_history.can_undo();
}

// Can we currently call redo?
bool sak::Project::can_redo() const
{
    return cimp().m_command_history.can_redo();
}

// How many times can undo() be called?
std::size_t sak::Project::undo_count() const
{
    return cimp().m_command_history.undo_count();
}

// How many times can redo() be called?
std::size_t sak::Project::redo_count() const
{
    return cimp().m_command_history.redo_count();
}

// Undo the last command issued.
void sak::Project::undo()
{
    imp().m_command_history.undo();
}

// Redo the last undone command in the command history
void sak::Project::redo()
{
    imp().m_command_history.redo();
}

// Commands get sent here.
void sak::Project::emplace_execute(std::unique_ptr<command_type>&& a_command)
{
    if (a_command != nullptr)
    {
        imp().m_command_history.add_execute(std::move(a_command));
    }
}

// Clear the undo/redo history.
void sak::Project::clear_history()
{
    imp().m_command_history.clear();
}

// File Interface
//============================================================

// Are there any Files in this Project?
bool sak::Project::has_files() const
{
    return !(cimp().m_files.empty());
}

// How many any Files are in this Project?
std::size_t sak::Project::file_count() const
{
    return cimp().m_files.size();
}

// Get the file at this index, asssuming the Files are alphabetically sorted by name
sak::file::extended_handle sak::Project::get_file_at(std::size_t a_index) const
{
    return cimp().m_files.at(a_index);
}

// Get all the Files alphabetically sorted by name
std::vector<sak::file::extended_handle> sak::Project::get_all_files() const
{
    return cimp().m_files;
}


// Get all the Files alphabetically sorted names
std::vector<QString> sak::Project::get_all_file_names() const
{
    std::vector<QString> l_result{};
    l_result.reserve(cimp().m_files.size());
    for (auto const& l_file : cimp().m_files)
    {
        l_result.push_back(l_file.cget().cat<0>().cget());
    }
    return l_result;
}

// You may create new Files using these two functions. Files created in this way
// are part of the Project's data management system but have not yet been added to the
// Project properly. That will only happen when the Project recieves a signal via its
// Project_Signalbox that it should be addeed.

// Make a new file using the supplied data. Project's data management system owns it but
// it is not part of the Proeject.
sak::file::extended_handle sak::Project::make_emplace_file(file::object&& a_file)
{
    return imp().m_file_manager.emplace_data(std::move(a_file));
}

// Make a new file using the default parameters. Project's data management system owns it
// but it is not part of the Project.
sak::file::extended_handle sak::Project::make_file()
{
    // uniqueify the name.
    QString l_name{u8"New File"};
    uniqueify_name(l_name, get_all_file_names());
    file::object l_file{};
    l_file.at<0>().get() = l_name;
    return make_emplace_file(std::move(l_file));
}

// To signal that something should be done to the project, you may access the signalbox
// for a specific type, then call the signals to make and propagate changes.
sak::Project_Signalbox* sak::Project::get_signalbox() const
{
    return m_data.get();
}


