#ifndef PROJECT_SIGNALBOX_H
#define PROJECT_SIGNALBOX_H

#include <cstddef>
#include "fwd_file.h"

namespace sak
{
    class Project_Signalbox
    {
    public:
        virtual ~Project_Signalbox() = default;

        // When the Files section has changed order due to a name change, this is called.
        virtual void file_names_reordered() = 0;
        // When a File has had its name changed, this is called.
        virtual void file_name_changed(File_Handle const& a_file, std::size_t a_index_old, std::size_t a_index_new) = 0;
        // When a File has its data changed(anything but the name), this is called.
        virtual void file_data_changed(File_Handle const& a_file, std::size_t a_index) = 0;
        // When a File has been added, this is called.
        virtual void file_added(File_Handle const& a_file, std::size_t a_index) = 0;
        // When a File has been removed, this is called.
        virtual void file_removed(File_Handle const& a_file, std::size_t a_index) = 0;
        // When a File editor is to be opened, this is called.
        virtual void file_requests_editor(File_Handle const& a_file, std::size_t a_index) = 0;
    };

    class Project_File_Signalbox
    {
    public:
        virtual ~Project_File_Signalbox() = default;

        // When a File has had its name changed, this is called.
        virtual void file_name_changed(File_Handle const& a_file) = 0;
        // When a File has its data changed(anything but the name), this is called.
        virtual void file_data_changed(File_Handle const& a_file) = 0;
        // When a File has its data changed in a specific place, this is called.
        virtual void file_data_changed_at(File_Handle const& a_file, std::size_t a_section) = 0;
        // When a File has been added, this is called.
        virtual void file_added(File_Handle const& a_file) = 0;
        // When a File has been removed, this is called.
        virtual void file_removed(File_Handle const& a_file) = 0;
        // When a File editor is to be opened, this is called.
        virtual void file_requests_editor(File_Handle const& a_file) = 0;
        // When focus is changed to be on a File, call this
        virtual void file_requests_focus(File_Handle const& a_file) = 0;
    };
}

#endif // PROJECT_SIGNALBOX_H
