#include <QApplication>
#include <iostream>
#include <QMenu>
#include <QAction>
#include <QPointer>
#include <QMenuBar>
#include <QWidget>
#include <QHBoxLayout>
#include <memory>
#include "sak/project_window.h"

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

    {
        QPointer<QAction> l_action{new QAction("blah")};
        QPointer<QMenu> l_menu{new QMenu};
        {
            std::unique_ptr<QMenu> l_menu2{new QMenu};
            l_menu2->addAction(l_action);
            l_menu2->addMenu(l_menu);
        }
        if (!l_action.isNull())
        {
            delete l_action.data();
        }
        else
        {
            std::cout << "QAction destroyed by QMenu." << std::endl;
        }

        if (!l_menu.isNull())
        {
            delete l_menu.data();
        }
        else
        {
            std::cout << "QMenu destroyed by QMenu." << std::endl;
        }
    }

    {
        QPointer<QAction> l_action{new QAction("blah")};
        QPointer<QMenu> l_menu{new QMenu};
        {
            std::unique_ptr<QMenuBar> l_menubar{new QMenuBar};
            l_menubar->addMenu(l_menu);
            l_menubar->addAction(l_action);
        }
        if (!l_action.isNull())
        {
            delete l_action.data();
        }
        else
        {
            std::cout << "QAction destroyed by QMenuBar." << std::endl;
        }

        if (!l_menu.isNull())
        {
            delete l_menu.data();
        }
        else
        {
            std::cout << "QMenu destroyed by QMenuBar." << std::endl;
        }
    }

    {
        QPointer<QWidget> l_child{new QWidget};
        QPointer<QHBoxLayout> l_layout{new QHBoxLayout};
        {
            std::unique_ptr<QWidget> l_parent{new QWidget};
            //QPointer<QWidget> l_parent{new QWidget};
            l_layout->addWidget(l_child);
            l_parent->setLayout(l_layout);
        }
        if (!l_child.isNull())
        {
            delete l_child.data();
        }
        else
        {
            std::cout << "QWidget Child previously destroyed by QWidget." << std::endl;
        }

        if (!l_layout.isNull())
        {
            delete l_layout.data();
        }
        else
        {
            std::cout << "QHBoxLayout previously destroyed by QWidget." << std::endl;
        }
    }
    return l_application.exec();

    return 0;
}
