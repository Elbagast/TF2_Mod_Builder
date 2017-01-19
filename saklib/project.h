#ifndef SAKLIB_PROJECT_H
#define SAKLIB_PROJECT_H

namespace saklib
{
    class Size_Type;
    class File_Path;
    class Directory_Path;
    class String;

    template <typename T>
    class Vector;

    class Element;


    //---------------------------------------------------------------------------
    // Project
    //---------------------------------------------------------------------------
    /*
    - A Project is stored in a project file, in a directory of the same name, with
      that directory containing everything the project is responsible for.
       e.g.
        C:/somewhere/else/Some_Project/Some_Project.project
       with
        C:/somewhere/else/Some_Project/dependent_file.extention
        C:/somewhere/else/Some_Project/data/some_data_file.extention
       etc.
    - A Project is thus created from a directory name that will be the project
      folder or by loading an existing project file.
       e.g.
        Create Project: [specify new or existing valid directory]
       or
        Load Project: [specify existing valid project file]
    - A Project contains a development branch that contains data necessary to build
      a number of Assets.
    - Assets have specific types and may contain a hierarchy of data, but all have
      common parts: source data and/or file(s), target data and/or file(s), parameters
      for the building of that Asset and a build function to use the parameters to
      turn the source into the target.
       e.g.
        Texture:
        Source File: [project folder]/source_files/textures/some_file.imagetype
        Target File: [package folder]/textures/final_file.compiled_image
        Options: [texture compression method, dimensions, compression options, etc.]
    - The parameters of an Asset may instead reference a paremeter of the same type in
      another asset so that a seperate Asset can be built using shared parameters.
       e.g.
        Texture: texture_1
        Source File: [project folder]/source_files/textures/some_file.imagetype
        Target File: [package folder]/textures/final_file_1.compiled_image
        Options: height = 512, width = 512

        Texture: texture_2
        Source File: texture_1::Source File
        Target File: [package folder]/textures/final_file_2.compiled_image
        Options: height = 256, width = 256
    */

    class Project;

    // A GUI implementation of create_project should not allow the creation of a Project where one already exists.
    Project create_project(Directory_Path const& a_directory_path); // throw if invalid variable is supplied
    Project load_project(File_Path const& a_file_path); // throw if invalid variable is supplied

    class Texture;
    class Material;
    class Model;
    class File;
    class Asset;

    void build(Texture const& a_texture);
    void build(Material const& a_material);
    void build(Model const& a_model);

    class Project
    {
    public:
        // Make a new Project with this name
        explicit Project(String const& a_name);
        // Make a Project out of the data in this file.
        explicit Project(File_Path const& a_file_path);

        // Data saving / loading
        //---------------------------

        // Has the Project been edited since it was last saved?
        bool has_unsaved_data() const;

        // Save the data to the file
        void save() const;

        // load the data from the file again
        void reload();

        // Files
        //---------------------------
        bool has_files() const;
        bool has_file_at(Size_Type a_index) const;
        Size_Type get_file_count() const;
        void add_file(File const& a_file);
        void remove_file_at(Size_Type a_index);
        File get_file_at(Size_Type a_index) const;

        // Textures
        //---------------------------
        bool has_textures() const;
        bool has_texture_at(Size_Type a_index) const;
        Size_Type get_texture_count() const;
        void add_texture(Texture const& a_texture);
        void remove_texture_at(Size_Type a_index);
        Texture get_texture_at(Size_Type a_index) const;

    };

} // namespace saklib

#endif // SAKLIB_PROJECT_H
