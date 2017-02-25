#ifndef FILE_HPP
#define FILE_HPP

#include "fwd_file.hpp"
#include "common_data.hpp"

namespace sak
{
    //---------------------------------------------------------------------------
    // File
    //---------------------------------------------------------------------------
    /*
    Common Data:
    - Name
    - Description
    Unique Data:
    - Build target
        - Game location
        or
        - Game file to replace
        or
        - Inform user that it will replace a game file without storing whether or not it will.
    - Source file
        - File path
        - Edited by having the user browse for a file with a valid extension.
        - When selected ask the user whether we are going to cache the file or not.

    Build Method:
    - Establish a build location in the Project subfolders. e.g. directory [project]/build/File-[name]
    - Build the directory the file will go in at that location.
    - Copy the file to the location, renaming it as appropriate.
    - Make a .txt file detailing the build info/timestamp etc. and put in in the build location.
    - Make a .vpk of the build location and put it in [project]/build.

    Install Method:
    ...
    Installing is the same for anything that's a .vpk, and is going to need some kind of monitoring system...
    */

    class File :
            public Common_Data
    {
    public:
        File();
        explicit File(QString const& a_name, QString const& a_description = QString());
        ~File() override;

        QString const& cget_buildpath() const;
        QString const& cget_sourcepath() const;

        void set_buildpath(QString const& a_buildpath);
        void set_sourcepath(QString const& a_sourcepath);
    private:

        // Relative path of where in the game this file will be.
        // Could be an existing file.
        // Probably better off as a distinct data type?
        QString m_buildpath;
        QString m_sourcepath; // Absolute path, or relative path from the Project file location.
    };
}
#endif // FILE_HPP
