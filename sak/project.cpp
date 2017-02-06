#include "project.h"

#include <QString>
#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include "exceptions/exception.h"

//---------------------------------------------------------------------------
// Project
//---------------------------------------------------------------------------

// Pimpl Data
//============================================================
class sak::Project::Data
{
public:
    QFileInfo m_filepath;
    QString m_message;
    QString m_data;

    Data(QString const& a_filepath):
        m_filepath{a_filepath},
        m_message{"got here"},
        m_data{}
    {
    }
    ~Data() = default;
};



// Special 6
//============================================================
// Construct the project using the supplied filename. If the directory
// does not exist or is inaccessible it will fail. If the file does
// not exist it will attempt to create it and save the initial data
// to it. If the file exists it will attempt to load the data from it.
sak::Project::Project(QString const& a_filepath):
    m_data{std::make_unique<Data>(a_filepath)}
{
    // If the directory does not exist it will fail.
    if(!data().m_filepath.dir().exists())
    {
        // Failure exception for directory not existing.
        throw Directory_Missing_Error(data().m_filepath.absoluteDir().absolutePath());
        //data().m_message = u8"Failure exception for directory not existing.";
    }
    /*
    if(!data().m_filepath.dir().isReadable())
    {
        // Failure exception for directory access.
        data().m_message = u8"Failure exception for directory access.";
    }
    */

    QFile l_file{(data().m_filepath.absoluteFilePath())};
    if(!l_file.exists())
    {
        if (!l_file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            // Failure exception for file writing.
            throw File_Write_Error(data().m_filepath.absoluteFilePath());
            //data().m_message = u8"Failure exception for file writing.";
        }
        else
        {
            QTextStream l_stream{(&l_file)};
            l_stream << "empty project: " << a_filepath;
            l_file.close();

            // should probably just call save at this point?
            data().m_message = u8"Created new project file.";
        }

    }
    else
    {
        if (!l_file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            // Failure exception for file loading.
            throw File_Read_Error(data().m_filepath.absoluteFilePath());
            //data().m_message = u8"Failure exception for file loading.";
        }
        else
        {
            QTextStream l_stream{(&l_file)};
            data().m_data = l_stream.readLine();
            l_file.close();
            data().m_message = u8"Loaded existing project file.";
        }

    }
}
sak::Project::~Project() = default;

sak::Project::Project(Project &&) = default;
sak::Project& sak::Project::operator=(Project &&) = default;

// Interface
//============================================================

QString sak::Project::name() const
{
    return cdata().m_filepath.baseName();
}

QString sak::Project::location() const
{
    return cdata().m_filepath.absolutePath();
}

QString sak::Project::filepath() const
{
    return cdata().m_filepath.absoluteFilePath();
}

QString sak::Project::message() const
{
    return cdata().m_message;
}

QString sak::Project::content() const
{
    return cdata().m_data;
}
