#include "saklib/qtlib/project_main_window.h"
#include <QApplication>
#include <iostream>
#include "saklib/project_manager.h"

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
    //qInstallMessageHandler(myMessageOutput);
    Saklib::Project_Manager project_manager{};

    QApplication a(argc, argv);
    Saklib::Qtlib::Project_Main_Window window(project_manager);
    window.show();

    return a.exec();
}
