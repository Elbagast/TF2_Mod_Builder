#include "project.h"

#include <QString>
#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include "exceptions/exception.h"
#include <QDebug>
#include <cassert>


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

        Implementation(QString const& a_filepath):
            m_filepath{a_filepath},
            m_message{"got here"},
            m_data{},
            m_files{}
        {
        }
        ~Implementation() = default;
    };
}

// Special 6
//============================================================
// Construct the project using the supplied filename. If the directory
// does not exist or is inaccessible it will fail. If the file does
// not exist it will attempt to create it and save the initial data
// to it. If the file exists it will attempt to load the data from it.
sak::Project::Project(QString const& a_filepath):
    m_data{std::make_unique<Implementation>(a_filepath)}
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

    this->add_file(File("dummy1", "poop"));
    this->add_file(File("dummy2", "pee"));

    auto l_temp = this->get_file_at(0);
    assert(l_temp.ref_count() == 2);
    {
        auto l_temp2 = l_temp;
        assert(l_temp.ref_count() == 3);
    }
    assert(l_temp.ref_count() == 2);
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
    auto l_data{std::make_unique<Implementation>(cimp().m_filepath.absoluteFilePath())};

    // Create a file object
    QFile l_file{cimp().m_filepath.absoluteFilePath()};

    // Attempt to open the file to read it
    if (l_file.exists() && l_file.open(QFile::ReadOnly | QFile::Text))
    {
        // make an xml stream
        QXmlStreamReader xml_stream{&l_file};

        // if the token is for "Project"
        if (xml_stream.readNextStartElement() && xml_stream.name().toString() == "Project")
        {
            // Read the Filepath
            if (xml_stream.readNextStartElement() && xml_stream.name().toString() == "Filepath")
            {
                l_data->m_filepath = QFileInfo(xml_stream.readElementText());
                qDebug() << "Filepath: " << l_data->m_filepath.absoluteFilePath();
            }
            else
            {
                // Bad file structure
                qDebug() << "Didn't find Filepath";
            }

            // Read the data
            if (xml_stream.readNextStartElement() && xml_stream.name().toString() == "Data")
            {
                l_data->m_data = xml_stream.readElementText();
                qDebug() << "Data: " << l_data->m_data;
            }
            else
            {
                // Bad file structure
                qDebug() << "Didn't find Data";
            }
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

// Add a new file. Project takes ownership of the File. File is inserted in
// the appropriate place to maintain sorting and Project signals that the File list
// has gained an item at that positon.
sak::File_Handle sak::Project::add_file(File&& a_file)
{
    auto l_handle = imp().m_file_manager.emplace_data(std::move(a_file));
    assert(l_handle.ref_count() == 1);
    imp().m_files.push_back(l_handle);
    assert(l_handle.ref_count() == 2);
    //auto l_location
    //auto l_index =
    //signal_file_added_at(a_index);
    return l_handle;
}

// Remove the file at this index and return it. Project is no longer its owner.
// Project signals that the File list has lost an item at that location.
sak::File_Handle sak::Project::remove_file_at(std::size_t a_index)
{
    auto l_result = cimp().m_files.at(a_index);
    auto l_position = cimp().m_files.begin();
    std::advance(l_position, a_index);
    imp().m_files.erase(l_position);
    //signal_file_removed_at(a_index);
    return l_result;
}
