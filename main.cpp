#include <QApplication>
#include <iostream>
#include "sak/project_window.hpp"

#include <dclib/litype/testing/test_string.hpp>
#include <dclib/litype/testing/test_integer.hpp>
//#include <dclib/litype/testing/test_float.hpp>

#include <dclib/ct/testing/test_object.hpp>
#include <dclib/rt/testing/test_object.hpp>

#include <sak/shared/extended_manager.hpp>
#include <sak/shared/interface.hpp>
#include <sak/shared/interface_traits.hpp>
#include <sak/shared/command.hpp>
#include <sak/shared/widget.hpp>

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
    QApplication l_application(argc, argv);
    sak::Project_Window l_window{};
    l_window.show();

    dclib::litype::test_string();
    dclib::litype::test_integer();
    //dclib::litype::test_float();

    dclib::ct::test_object();
    dclib::rt::test_object();

    sak::file::extended_manager fem{};
    sak::file::widget fw{fem.make_null_handle(), nullptr};

    return l_application.exec();

    return 0;
}
