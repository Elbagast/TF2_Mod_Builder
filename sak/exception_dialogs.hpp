#ifndef SAK_EXCEPTION_DIALOGS_HPP
#define SAK_EXCEPTION_DIALOGS_HPP

#ifndef SAK_EXCEPTION_FWD_HPP
#include "exception_fwd.hpp"
#endif

class QString;
class QWidget;

// is this lot even necessary? Just make boxes as needed?

namespace sak
{
  /*
  void make_exception_dialog(Exception& a_exception);
  void make_filesystem_error_dialog(Filesystem_Error& a_exception);

  void make_directory_error_dialog(Directory_Error& a_exception);
  void make_directory_missing_error_dialog(Directory_Creation_Error& a_exception);
  void make_directory_creation_error_dialog(Directory_Missing_Error& a_exception);
  void make_directory_read_error_dialog(Directory_Read_Error& a_exception);
  void make_directory_write_error_dialog(Directory_Write_Error& a_exception);

  void make_file_error_dialog(File_Error& a_exception);
  void make_file_missing_error_dialog(File_Missing_Error& a_exception);
  void make_file_creation_error_dialog(File_Creation_Error& a_exception);
  void make_file_read_error_dialog(File_Read_Error& a_exception);
  void make_file_write_error_dialog(File_Write_Error& a_exception);
  */

  void make_exception_dialog(QWidget* a_parent, QString const& a_message);
  void make_filesystem_error_dialog(QWidget* a_parent, QString const& a_message);

  void make_directory_error_dialog(QWidget* a_parent, QString const& a_dirpath);
  void make_directory_missing_error_dialog(QWidget* a_parent, QString const& a_dirpath);
  void make_directory_creation_error_dialog(QWidget* a_parent, QString const& a_dirpath);
  void make_directory_read_error_dialog(QWidget* a_parent, QString const& a_dirpath);
  void make_directory_write_error_dialog(QWidget* a_parent, QString const& a_dirpath);

  void make_file_error_dialog(QWidget* a_parent, QString const& a_filepath);
  void make_file_missing_error_dialog(QWidget* a_parent, QString const& a_filepath);
  void make_file_creation_error_dialog(QWidget* a_parent, QString const& a_filepath);
  void make_file_read_error_dialog(QWidget* a_parent, QString const& a_filepath);
  void make_file_write_error_dialog(QWidget* a_parent, QString const& a_filepath);
}

#endif // SAK_EXCEPTION_DIALOGS_HPP
