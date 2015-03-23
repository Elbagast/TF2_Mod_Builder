#include "saklib/qtlib/project_main_window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Saklib::Qtlib::Project_Main_Window w;
    w.show();

    return a.exec();
}
