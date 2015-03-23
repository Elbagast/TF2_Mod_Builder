#ifndef PROJECT_WINDOW_H
#define PROJECT_WINDOW_H

#include <QMainWindow>

namespace Ui {
    class Project_Window;
}

class Project_Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Project_Window(QWidget *parent = 0);
    ~Project_Window();

private:
    Ui::Project_Window *ui;
};

#endif // PROJECT_WINDOW_H
