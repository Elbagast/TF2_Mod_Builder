#ifndef PROJECT_SIGNALBOX_HPP
#define PROJECT_SIGNALBOX_HPP

#include <cstddef>
#include "fwd_file.hpp"

namespace sak
{
    // All signals that are dispatched from Project for a given handle type.
    template <typename H>
    class Handle_Signalbox
    {
    public:
        using handle_type = H;

        virtual ~Handle_Signalbox() = default;

        // When a handle has had its name changed, this is called.
        virtual void name_changed(handle_type const& a_handle) = 0;
        // When a handle has had its description changed, this is called.
        virtual void description_changed(handle_type const& a_handle) = 0;
        // When a handle has its data changed(anything but the name), this is called.
        virtual void data_changed(handle_type const& a_handle) = 0;
        // When a handle has its data changed in a specific place, this is called.
        virtual void data_changed_at(handle_type const& a_handle, std::size_t a_section) = 0;
        // When a handle has been added, this is called.
        virtual void added(handle_type const& a_handle) = 0;
        // When a handle has been removed, this is called.
        virtual void removed(handle_type const& a_handle) = 0;
        // When a handle editor is to be opened, this is called.
        virtual void requests_editor(handle_type const& a_handle) = 0;
        // When focus is changed to be on a handle, call this
        virtual void requests_focus(handle_type const& a_handle) = 0;
    };


    using Project_File_Signalbox = Handle_Signalbox<File_Handle>;

    class Project_Signalbox :
            public Project_File_Signalbox
            //,public Handle_Signalbox<Texture_HPPandle> // etc. Same functions, different arg types.
    {
    public:
        ~Project_Signalbox() override = default;
    };

}

#endif // PROJECT_SIGNALBOX_HPP
