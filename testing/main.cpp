//#include <sak/gui/line_edit.hpp>
//#include <QApplication>

#include "test_class_definitions.hpp"
#include "test_data.hpp"
#include "test_handle.hpp"
#include "test_handle_factory.hpp"
#include "test_project_data.hpp"
#include "test_project_signalbox_data.hpp"
#include "test_abstract_project_interface.hpp"
#include "test_project_handle_factory.hpp"
#include "test_project_handle_data.hpp"

int main(int argc, char *argv[])
{
  using namespace sak::testing;

  test_class_definitions();
  test_data();
  test_handle();
  test_handle_factory();
  test_project_data();
  test_project_signalbox_data();
  test_abstract_project_interface();
  test_project_handle_factory();
  test_project_handle_data();

  return 0;

  /*
  QApplication a(argc, argv);

  sak::gui::Line_Edit le{};
  le.show();

  return a.exec();
  */
}
