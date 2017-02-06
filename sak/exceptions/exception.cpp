#include "exception.h"
#include <QMessageBox>

namespace
{
    QString const c_filesystem_error_title{u8"Filesystem Error"};
    QString const c_filesystem_error_message{u8"There was a filesystem error."};

    QString const c_directory_error_title{u8"Directory Error"};
    QString const c_directory_missing_error_message{u8"The expected directory does not exist:\n"};

    QString const c_file_error_title{u8"File Error"};
    QString const c_file_missing_error_message{u8"The expected file does not exist:\n"};
    QString const c_file_read_error_message{u8"Could not read from file:\n"};
    QString const c_file_write_error_message{u8"Could not write to file:\n"};
}

sak::Exception::~Exception() = default;

// When there is an error with the filesystem
sak::Filesystem_Error::Filesystem_Error(QString const& a_path1, QString const& a_path2):
    Exception(),
    m_path1{a_path1},
    m_path2{a_path2}
{}
sak::Filesystem_Error::~Filesystem_Error() = default;
void sak::Filesystem_Error::dialog(QWidget* a_parent) const
{
    QMessageBox::critical(a_parent, c_filesystem_error_title, c_filesystem_error_message);
}

QString const& sak::Filesystem_Error::path1() const
{
    return m_path1;
}

QString const& sak::Filesystem_Error::path2() const
{
    return m_path2;
}

// When an expected directory is missing
sak::Directory_Missing_Error::Directory_Missing_Error(QString const& a_dirpath):
    Filesystem_Error(a_dirpath,QString())
{
}
sak::Directory_Missing_Error::~Directory_Missing_Error() = default;
void sak::Directory_Missing_Error::dialog(QWidget* a_parent) const
{
    QMessageBox::critical(a_parent, c_directory_error_title, c_directory_missing_error_message + path1());
}

// When an expected file is missing
sak::File_Missing_Error::File_Missing_Error(QString const& a_filepath):
    Filesystem_Error(a_filepath,QString())
{
}
sak::File_Missing_Error::~File_Missing_Error() = default;
void sak::File_Missing_Error::dialog(QWidget* a_parent) const
{
    QMessageBox::critical(a_parent, c_file_error_title, c_file_missing_error_message + path1());
}

// When write access to a file fails
sak::File_Write_Error::File_Write_Error(QString const& a_filepath):
    Filesystem_Error(a_filepath,QString())
{
}
sak::File_Write_Error::~File_Write_Error() = default;
void sak::File_Write_Error::dialog(QWidget* a_parent) const
{
    QMessageBox::critical(a_parent, c_file_error_title, c_file_read_error_message + path1());
}

// When read access to a file fails
sak::File_Read_Error::File_Read_Error(QString const& a_filepath):
    Filesystem_Error(a_filepath,QString())
{
}
sak::File_Read_Error::~File_Read_Error() = default;
void sak::File_Read_Error::dialog(QWidget* a_parent) const
{
    QMessageBox::critical(a_parent, c_file_error_title, c_file_write_error_message + path1());
}
