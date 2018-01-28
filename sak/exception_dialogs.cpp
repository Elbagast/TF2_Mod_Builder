#include "exception_dialogs.hpp"

#include <QMessageBox>

namespace
{
  QString const c_exception_title{u8"Exception"};
  QString const c_exception_message{u8"An unhandled exception occured:\n"};


  QString const c_filesystem_error_title{u8"Filesystem Error"};
  QString const c_filesystem_error_message{u8"There was a filesystem error:\n"};

  QString const c_directory_error_title{u8"Directory Error"};
  QString const c_directory_error_message{u8"A directory error occured at:\n"};
  QString const c_directory_missing_error_message{u8"The expected directory does not exist:\n"};
  QString const c_directory_creation_error_message{u8"The following directory could not be created:\n"};
  QString const c_directory_read_error_message{u8"The following directory could not be read:\n"};
  QString const c_directory_write_error_message{u8"The following directory could not be written to:\n"};

  QString const c_file_error_title{u8"File Error"};
  QString const c_file_error_message{u8"A file error occured at:\n"};
  QString const c_file_missing_error_message{u8"The expected file does not exist:\n"};
  QString const c_file_creation_error_message{u8"The following file could not be created:\n"};
  QString const c_file_read_error_message{u8"The following file could not be read:\n"};
  QString const c_file_write_error_message{u8"The following file could not be written to:\n"};

}


void sak::make_exception_dialog(QWidget* a_parent, QString const& a_message)
{
  QMessageBox::critical(a_parent, c_exception_title, c_exception_message + a_message);
}

void sak::make_filesystem_error_dialog(QWidget* a_parent, QString const& a_message)
{
  QMessageBox::critical(a_parent, c_filesystem_error_title, c_filesystem_error_message + a_message);
}


void sak::make_directory_error_dialog(QWidget* a_parent, QString const& a_dirpath)
{
  QMessageBox::critical(a_parent, c_directory_error_title, c_directory_error_message + a_dirpath);
}

void sak::make_directory_missing_error_dialog(QWidget* a_parent, QString const& a_dirpath)
{
  QMessageBox::critical(a_parent, c_directory_error_title, c_directory_missing_error_message + a_dirpath);
}

void sak::make_directory_creation_error_dialog(QWidget* a_parent, QString const& a_dirpath)
{
  QMessageBox::critical(a_parent, c_directory_error_title, c_directory_creation_error_message + a_dirpath);
}

void sak::make_directory_read_error_dialog(QWidget* a_parent, QString const& a_dirpath)
{
  QMessageBox::critical(a_parent, c_directory_error_title, c_directory_write_error_message + a_dirpath);
}

void sak::make_directory_write_error_dialog(QWidget* a_parent, QString const& a_dirpath)
{
  QMessageBox::critical(a_parent, c_directory_error_title, c_directory_read_error_message + a_dirpath);
}



void sak::make_file_error_dialog(QWidget* a_parent, QString const& a_dirpath)
{
  QMessageBox::critical(a_parent, c_file_error_title, c_file_error_message + a_dirpath);
}

void sak::make_file_missing_error_dialog(QWidget* a_parent, QString const& a_dirpath)
{
  QMessageBox::critical(a_parent, c_file_error_title, c_file_missing_error_message + a_dirpath);
}

void sak::make_file_creation_error_dialog(QWidget* a_parent, QString const& a_dirpath)
{
  QMessageBox::critical(a_parent, c_file_error_title, c_file_creation_error_message + a_dirpath);
}

void sak::make_file_read_error_dialog(QWidget* a_parent, QString const& a_dirpath)
{
  QMessageBox::critical(a_parent, c_file_error_title, c_file_write_error_message + a_dirpath);
}

void sak::make_file_write_error_dialog(QWidget* a_parent, QString const& a_dirpath)
{
  QMessageBox::critical(a_parent, c_file_error_title, c_file_read_error_message + a_dirpath);
}


