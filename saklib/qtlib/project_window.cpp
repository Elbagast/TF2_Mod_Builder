#include "project_window.h"
#include "ui_project_window.h"

Project_Window::Project_Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Project_Window)
{
    ui->setupUi(this);
}

Project_Window::~Project_Window()
{
    delete ui;
}
