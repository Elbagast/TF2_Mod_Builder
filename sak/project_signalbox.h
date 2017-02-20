#ifndef PROJECT_SIGNALBOX_H
#define PROJECT_SIGNALBOX_H

#include <cstddef>
#include "fwd_file.h"

namespace sak
{
    // All signals that are dispatched from Project for a given handle type.
    template <typename H>
    class Handle_Signalbox_Out
    {
    public:
        using handle_type = H;

        virtual ~Handle_Signalbox_Out() = default;

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

    // All signals that are recieved by Project for a given handle type.
    template <typename H, typename BH>
    class Handle_Signalbox_In
    {
    public:
        using handle_type = H;
        using basic_handle_type = BH;

        virtual ~Handle_Signalbox_In() = default;

        // When a handle has had its name changed, this is called.
        virtual void name_changed(basic_handle_type const& a_handle) = 0;
        // When a handle has had its description changed, this is called.
        virtual void description_changed(basic_handle_type const& a_handle) = 0;
        // When a handle has its data changed(anything but the name), this is called.
        virtual void data_changed(basic_handle_type const& a_handle) = 0;
        // When a handle has its data changed in a specific place, this is called.
        virtual void data_changed_at(basic_handle_type const& a_handle, std::size_t a_section) = 0;
        // When a handle has been removed, this is called.
        virtual void removed(handle_type const& a_handle) = 0;
        // When a handle editor is to be opened, this is called.
        virtual void requests_editor(handle_type const& a_handle) = 0;
        // When focus is changed to be on a handle, call this
        virtual void requests_focus(handle_type const& a_handle) = 0;
    };

    class Project_Signalbox_Out :
            public Handle_Signalbox_Out<File_Handle>
            //,public Handle_Signalbox<Texture_Handle> // etc. Same functions, different arg types.
    {
    public:
        ~Project_Signalbox_Out() override = default;
    };


    class Project_Signalbox_In :
            public Handle_Signalbox_In<File_Handle, File_Basic_Handle>
            //,public Handle_Signalbox<Texture_Handle> // etc. Same functions, different arg types.
    {
    public:
        ~Project_Signalbox_In() override = default;
    };
}

#endif // PROJECT_SIGNALBOX_H
