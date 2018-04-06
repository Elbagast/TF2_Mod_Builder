//#include <sak/gui/line_edit.hpp>
//#include <QApplication>

#include "test_entity_id.hpp"
#include "test_observer_manager.hpp"
#include "test_entity_maker.hpp"

int main()//int argc, char *argv[])
{
  using namespace sak::testing;

  test_entity_id();
  test_observer_manager();
  test_entity_maker();

  return 0;

  /*
  QApplication a(argc, argv);

  sak::gui::Line_Edit le{};
  le.show();

  return a.exec();
  */
}
