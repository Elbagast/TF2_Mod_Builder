//#include "saklib/qtlib/project_main_window.h"
#include <QApplication>
#include <iostream>
//#include "saklib/project_manager.h"
//#include "saklib/internal_element_definitions.h"
//#include "saklib/attribute/attribute.h"
//#include "saklib/attribute/attribute_test.h"
//#include "saklib/element/element_test.h"
//#include "saklib/named_properties/property_test.h"

#include "saklib/internal/test.h"
#include "saklib/internal/attribute_data_int__test.h"
#include "saklib/internal/attribute_data_bool__test.h"
#include "saklib/internal/attribute_data__test.h"
#include "saklib/internal/element_data__test.h"
#include "saklib/internal/element_data_manager__test.h"
#include "saklib/internal/undoable_element_data_manager__test.h"

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
    saklib::internal::test_handle();
    saklib::internal::test_handle_factory();

    //saklib::internal::test_constraint_boolean_type();
    //saklib::internal::test_constrained_boolean_type();

    //saklib::internal::test_constraint_integral_type();

    //saklib::internal::test_attribute();

    //saklib::internal::test_element();

    saklib::internal::test_element_manager();
    saklib::internal::test_undoable_element_data_manager();

    //saklib::attribute_test();
    //saklib::element_test();
    //saklib::property_test();
    //datalib::test();
    //datalib::test2();
    //datalib::test3();
    /*
    //qInstallMessageHandler(myMessageOutput);
    saklib::Project_Manager project_manager{};
    project_manager.register_element_definition( saklib::internal_definition_of_Project());
    project_manager.register_element_definition( saklib::internal_definition_of_File());
    project_manager.register_element_definition( saklib::internal_definition_of_SingleInt());
    project_manager.register_element_definition( saklib::internal_definition_of_Build());
    */

    //QApplication a(argc, argv);
    //saklib::Qtlib::Project_Main_Window window(project_manager);
    //window.show();

    //return a.exec();

    return 0;
}
