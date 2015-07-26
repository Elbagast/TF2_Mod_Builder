#include "saklib/qtlib/project_main_window.h"
#include <QApplication>
#include <iostream>
#include "saklib/project_manager.h"
#include "saklib/internal_element_definitions.h"

#include "saklib/all_nodes.h"

void myMessageOutput(QtMsgType type, QMessageLogContext const& context, QString const& msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        std::cerr
                << "Debug: " << localMsg.constData()
                << " (" << context.file <<":"<< context.line << ", " << context.function <<")" << std::endl;
        break;
    case QtWarningMsg:
        std::cerr
                << "Warning: " << localMsg.constData()
                << " (" << context.file <<":"<< context.line << ", " << context.function <<")" << std::endl;
        break;
    case QtCriticalMsg:
        std::cerr
                << "Critical: " << localMsg.constData()
                << " (" << context.file <<":"<< context.line << ", " << context.function <<")" << std::endl;
        break;
    case QtFatalMsg:
        std::cerr
                << "Fatal: " << localMsg.constData()
                << " (" << context.file <<":"<< context.line << ", " << context.function <<")" << std::endl;
        abort();
    }
}


int main(int argc, char *argv[])
{
    Saklib::test_nodes();

    //qInstallMessageHandler(myMessageOutput);
    Saklib::Project_Manager project_manager{};
    project_manager.register_element_definition( Saklib::internal_definition_of_Project());
    project_manager.register_element_definition( Saklib::internal_definition_of_File());
    project_manager.register_element_definition( Saklib::internal_definition_of_SingleInt());
    project_manager.register_element_definition( Saklib::internal_definition_of_Build());

    QApplication a(argc, argv);
    Saklib::Qtlib::Project_Main_Window window(project_manager);
    window.show();

    return a.exec();
}
