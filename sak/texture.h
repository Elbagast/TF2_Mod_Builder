#ifndef SAKLIB_TEXTURE_H
#define SAKLIB_TEXTURE_H

#include <memory>
#include <QWidget>
#include <QImage>
#include <QLineEdit>
#include "asset.h"

/*
class QHBoxLayout;
class QVBoxLayout;
class QLabel;
class QLineEdit;
class QTextEdit;


namespace saklib
{
    class Asset_Path;
    class Image_Data;
    class VTF_Compiler_Settings;
    class Asset_Widget;

    class Texture_Data
    {
    public:
        std::string const& cget_name() const;
        std::string const& cget_description() const;
        Asset_Path const& cget_build_target() const;
        Image_Data const& cget_source_image() const;
        // getters for vtf compiler settings.

    private:
        static QImage const s_icon_small; // Icon on outliner.
        static QImage const s_icon_large; // Icon on the main editor widget.
        std::string m_name; // utf8 name string. User set. Should be unique.
        std::string m_description; // utf8 description string. User set.
        Asset_Path m_build_target; // Ascii partial filepath that the texture will be built to. The user can select an existing location or set their own.
        Image_Data m_source_image; // User selects a source image file or makes a basic own out of simple settings. One or the other. Can change between them, or not set.
        VTF_Compiler_Settings m_vtf_compiler_settings;
    };

    class Texture_Widget :
            public QWidget
    {
    public:
        explicit Texture_Widget(Texture_Data& a_data);
        ~Texture_Widget() override;


    private:
        std::unique_ptr<QVBoxLayout> m_main_layout;

        // The top row os the widget
        std::unique_ptr<QVBoxLayout> m_top_layout;
        std::unique_ptr<QLabel> m_icon;
        std::unique_ptr<QLabel> m_title;
        std::unique_ptr<QLineEdit> m_name_entry;

        std::unique_ptr<QTextEdit> m_description_entry;



        std::unique_ptr<Asset_Widget> m_asset_widget;
    };
}
*/
#endif // SAKLIB_TEXTURE_H
