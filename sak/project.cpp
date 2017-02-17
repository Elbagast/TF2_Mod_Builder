#include "project.h"

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

#include "project_signalbox.h"
#include "exceptions/exception.h"
#include "file_manager.h"
#include "name_utilities.h"

//---------------------------------------------------------------------------
// Project
//---------------------------------------------------------------------------

// Pimpl Data
//============================================================
namespace sak
{
    class Project::Implementation
    {
    public:
        QFileInfo m_filepath;
        QString m_message;
        QString m_data;
        File_Manager m_file_manager;

        std::vector<File_Handle> m_files;

        std::vector<Project_Signalbox*> m_dependents;

        Implementation(QString const& a_filepath, Project* a_owner):
            m_filepath{a_filepath},
            m_message{"got here"},
            m_data{},
            m_file_manager{File_Interface_Traits(a_owner)},
            m_files{},
            m_dependents{}
        {
        }
        ~Implementation() = default;

        // Signalbox Interface
        //============================================================
        // Call these to call the signalbox functions in all dependents.

        // When the Files section has changed order due to a name change, this is called.
        void signal_file_names_reordered()
        {
            for (auto l_item : m_dependents)
            {
                l_item->file_names_reordered();
            }
        }
        // When a File has had its name changed, this is called.
        void signal_file_name_changed(File_Handle const& a_file, std::size_t a_index_old, std::size_t a_index_new)
        {
            for (auto l_item : m_dependents)
            {
                l_item->file_name_changed(a_file, a_index_old, a_index_new);
            }
        }
        // When a File has its data changed(anything but the name), this is called.
        void signal_file_data_changed(File_Handle const& a_file, std::size_t a_index)
        {
            for (auto l_item : m_dependents)
            {
                l_item->file_data_changed(a_file, a_index);
            }
        }
        // When a File has been added, this is called.
        void signal_file_added(File_Handle const& a_file, std::size_t a_index)
        {
            for (auto l_item : m_dependents)
            {
                l_item->file_added(a_file, a_index);
            }
        }
        // When a File has been removed, this is called.
        void signal_file_removed(File_Handle const& a_file, std::size_t a_index)
        {
            for (auto l_item : m_dependents)
            {
                l_item->file_removed(a_file, a_index);
            }
        }
        // When a File requests an editor, this is called.
        void signal_file_requests_editor(File_Handle const& a_file, std::size_t a_index)
        {
            for (auto l_item : m_dependents)
            {
                l_item->file_requests_editor(a_file, a_index);
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

       xml_stream.writeTextElement("Filepath", cimp().m_filepath.absoluteFilePath());
       xml_stream.writeTextElement("Data", cimp().m_data);

       // Start the Files block
       xml_stream.writeStartElement("Files");
       xml_stream.writeTextElement("Count", QString::number(cimp().m_files.size()));

       for (auto const& l_file : cimp().m_files)
       {
           xml_stream.writeStartElement("File");
           xml_stream.writeTextElement("Name", l_file.cget().cget_name());
           xml_stream.writeTextElement("Description", l_file.cget().cget_description());
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
            // <Filepath>
            if (xml_stream.readNextStartElement() && xml_stream.name().toString() == "Filepath")
            {
                l_data->m_filepath = QFileInfo(xml_stream.readElementText());
                //qDebug() << "Filepath: " << l_data->m_filepath.absoluteFilePath();

                // </Filepath>
                xml_stream.readNext();
            }
            else
            {
                // Bad file structure
                qDebug() << "Didn't find Filepath";
            }

            // <Data>
            if (xml_stream.readNextStartElement() && xml_stream.name().toString() == "Data")
            {
                l_data->m_data = xml_stream.readElementText();
                //qDebug() << "Data: " << l_data->m_data;

                // </Data>
                xml_stream.readNext();
            }
            else
            {
                // Bad file structure
                qDebug() << "Didn't find Data";
            }

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
                        File l_file{};
                        //qDebug() << "File: "<< l_index ;
                        // <Name>
                        if (xml_stream.readNextStartElement() && xml_stream.name().toString() == "Name")
                        {
                            auto l_data = xml_stream.readElementText();
                            //qDebug() << "Name: " << l_data;
                            l_file.set_name(l_data);

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
                            l_file.set_description(l_data);

                            // </Description>
                            xml_stream.readNext();
                        }
                        else
                        {
                            qDebug() << "Didn't find Description" ;
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

QString sak::Project::message() const
{
    return cimp().m_message;
}

QString sak::Project::content() const
{
    return cimp().m_data;
}

// Add an object that will rely on the Project's signals. If nulltpr, nothing happens.
void sak::Project::add_signalbox(Project_Signalbox* a_signalbox)
{
    if (a_signalbox != nullptr && std::find(cimp().m_dependents.cbegin(), cimp().m_dependents.cend(), a_signalbox) == cimp().m_dependents.cend())
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
sak::File_Handle sak::Project::get_file_at(std::size_t a_index) const
{
    return cimp().m_files.at(a_index);
}

// Get all the Files alphabetically sorted by name
std::vector<sak::File_Handle> sak::Project::get_all_files() const
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
        l_result.push_back(l_file.cget().cget_name());
    }
    return l_result;
}

// Add a new file. Project takes ownership of the File. File is inserted in
// the appropriate place to maintain sorting and Project signals that the File list
// has gained an item at that positon.
sak::File_Handle sak::Project::add_file(File&& a_file)
{
    // determine where the file will be inserted to maintain alphabetical sorting
    auto l_position = std::find_if(cimp().m_files.cbegin(),
                                   cimp().m_files.cend(),
                                   [&](File_Handle const& a_handle){ return a_file.cget_name() < a_handle.cget().cget_name(); });
    auto l_index = std::distance(cimp().m_files.cbegin(), l_position);

    auto l_handle = imp().m_file_manager.emplace_data(std::move(a_file));
    assert(l_handle.ref_count() == 1);

    imp().m_files.insert(l_position,l_handle);

    assert(l_handle.ref_count() == 2);
    //auto l_location
    //auto l_index =
    imp().signal_file_added(l_handle, l_index);
    return l_handle;
}

// Add a new default parameters File.
sak::File_Handle sak::Project::add_new_file()
{
    // uniqueify the name.
    QString l_name{u8"New File"};
    uniqueify_name(l_name, get_all_file_names());
    return add_file(File(l_name));
}

// Remove the file at this index and return it. Project is no longer its owner.
// Project signals that the File list has lost an item at that location.
sak::File_Handle sak::Project::remove_file_at(std::size_t a_index)
{
    auto l_result = cimp().m_files.at(a_index);
    auto l_position = cimp().m_files.begin();
    std::advance(l_position, a_index);
    imp().m_files.erase(l_position);
    imp().signal_file_removed(l_result, a_index);
    return l_result;
}

// Remove the File with this handle.
sak::File_Handle sak::Project::remove_file(File_Handle const& a_file)
{
    auto l_found = std::find(cimp().m_files.cbegin(), cimp().m_files.cend(), a_file);
    auto l_index = std::distance(cimp().m_files.cbegin(), l_found);
    imp().m_files.erase(l_found);
    imp().signal_file_removed(a_file, l_index);
    return a_file;
}


// File_Interface will call this when the File's name is changed. This causes Project
// to propagate the changes to where they need to go.
void sak::Project::file_name_changed(File_Basic_Handle const& a_file)
{
    auto l_old_position = std::find(cimp().m_files.cbegin(), cimp().m_files.cend(), a_file);
    auto l_old_index = std::distance(cimp().m_files.cbegin(), l_old_position);
    std::sort(imp().m_files.begin(), imp().m_files.end(), File_Handle_Less_By_Name());
    auto l_new_position = std::find(cimp().m_files.cbegin(), cimp().m_files.cend(), a_file);
    auto l_new_index = std::distance(cimp().m_files.cbegin(), l_new_position);

    imp().signal_file_name_changed(*l_new_position, l_old_index, l_new_index);
}

// File_Interface will call this when the File's data is changed. This causes Project
// to propagate the changes to where they need to go.
void sak::Project::file_data_changed(File_Basic_Handle const& a_file)
{
    auto l_position = std::find(cimp().m_files.cbegin(), cimp().m_files.cend(), a_file);
    auto l_index = std::distance(cimp().m_files.cbegin(), l_position);

    imp().signal_file_data_changed(*l_position, l_index);
}

// Outliner File_Item Interface
//============================================================
// outliner::File_Item calls this to request an editor. Project propagates the signal
// to anything that needs to change as a result.
void sak::Project::file_requests_editor(std::size_t a_index)
{
    imp().signal_file_requests_editor(cimp().m_files.at(a_index), a_index);
}
