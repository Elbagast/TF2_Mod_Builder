#ifndef FILE_WIDGET_HPP
#define FILE_WIDGET_HPP

#include <memory>
#include <QWidget>
#include "fwd_file.hpp"

namespace sak
{
    //---------------------------------------------------------------------------
    // File_Widget
    //---------------------------------------------------------------------------
    class File_Widget :
            public QWidget
    {
    public:
        // Special 6
        //============================================================
        explicit File_Widget(File_Handle const& a_file, QWidget* a_parent = nullptr);
        ~File_Widget() override;

        // Interface
        //============================================================
        File_Handle& get_file();
        File_Handle const& cget_file() const;

        // update all the data to match the handle.
        void update();
        void update_name();
        void update_description();
        void update_data();
        void update_data_at(std::size_t a_section);
    private:
        // Pimpl Data
        //============================================================
        class Implementation;
        std::unique_ptr<Implementation> m_data;

        Implementation& imp()                { return *m_data; }
        Implementation const& cimp() const   { return *m_data; }
    };

    // for matching the sort algorithm
    class File_Widget_Less_By_Name
    {
    public:
        bool operator()(std::unique_ptr<File_Widget> const& a_lhs, std::unique_ptr<File_Widget> const& a_rhs) const;
    };

    class File_Widget_Equals_Handle
    {
    public:
        explicit File_Widget_Equals_Handle(File_Handle const& a_file);

        bool operator()(std::unique_ptr<File_Widget> const& a_widget) const;
    private:
        File_Handle const& m_file;
    };
}


#endif // FILE_WIDGET_HPP
