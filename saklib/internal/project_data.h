#ifndef SAKLIB_INTERNAL_PROJECT_H
#define SAKLIB_INTERNAL_PROJECT_H

namespace saklib
{
    namespace internal
    {
        //---------------------------------------------------------------------------
        // Project
        //---------------------------------------------------------------------------

        class File_Path;
        class String;



        class Project
        {
        public:
            // Make a Project with this name
            explicit Project(String const& a_name);
            // Make a Project out of the data in this file.
            explicit Project(File_Path const& a_file_path);


        private:
        };

    } // namespace internal
} // namespace saklib


#endif // SAKLIB_INTERNAL_PROJECT_H
