#include "project_widget.h"


#include <QHBoxLayout>
#include <QTabWidget>
#include <QTreeView>

class sak::Project_Widget::Data
{
public:
    explicit Data(QString const& a_filepath):
        m_location{},
        m_name{}
    {}
    Data(QString const& a_location, QString const& a_name):
        m_location{a_location},
        m_name{a_name}
    {}


    QString m_location;
    QString m_name;
};


sak::Project_Widget::Project_Widget(QString const& a_filepath, QWidget* a_parent):
    QWidget(a_parent),
    m_layout{},
    m_outliner{},
    m_tabs{},
    m_data{std::make_unique<Data>(a_filepath)}
{}
/*
sak::Project_Widget::Project_Widget(QString const& a_location, QString const& a_name, QWidget* a_parent):
    QWidget(a_parent),
    m_layout{},
    m_outliner{},
    m_tabs{},
    m_data{std::make_unique<Data>(a_location, a_name)}
{}
*/
