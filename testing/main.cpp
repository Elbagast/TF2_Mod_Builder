#include <sak/gui/line_edit.hpp>
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  sak::gui::Line_Edit le{};
  le.show();

  return a.exec();
}
