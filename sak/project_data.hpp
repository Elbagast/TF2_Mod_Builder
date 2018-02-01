#ifndef SAK_PROJECT_DATA_HPP
#define SAK_PROJECT_DATA_HPP

#ifndef SAK_PROJECT_DATA_FWD_HPP
#include "project_data_fwd.hpp"
#endif

#ifndef SAK_ABSTRACT_PROJECT_SIGNALBOX_FWD_HPP
#include "abstract_project_signalbox_fwd.hpp"
#endif

#ifndef SAK_SECTION_DATA_MANAGER_FWD_HPP
#include "section_data_manager_fwd.hpp"
#endif

#ifndef SAK_SECTION_INTERFACE_FWD_HPP
#include "section_interface_fwd.hpp"
#endif

#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif

#ifndef INCLUDE_STD_VECTOR
#define INCLUDE_STD_VECTOR
#include <vector>
#endif

class QString;

namespace sak
{
  //---------------------------------------------------------------------------
  // Project_Data
  //---------------------------------------------------------------------------

  class Project_Data
  {
  public:
    // Special 6
    //============================================================
    // Construct the project using the supplied filename. If the directory
    // does not exist or is inaccessible it will fail. If the file does
    // not exist it will attempt to create it and save the initial data
    // to it. If the file exists it will attempt to load the data from it.
    explicit Project_Data(QString const& a_filepath);
    ~Project_Data();

    Project_Data(Project_Data const&) = delete;
    Project_Data& operator=(Project_Data const&) = delete;

    Project_Data(Project_Data &&);
    Project_Data& operator=(Project_Data &&);

    // Interface
    //============================================================
    QString name() const;
    QString location() const;
    QString filepath() const;

    // Add an object that will rely on the Project's signals. If nulltpr, nothing happens.
    void add_signalbox(Abstract_Project_Signalbox* a_signalbox);

    // Remove an object that will rely on the Project's signals. If nulltpr, nothing happens.
    void remove_signalbox(Abstract_Project_Signalbox* a_signalbox);

    // Clear all the signalboxes so that nothing relies on changes to this.
    void clear_signalboxes();
    
    // Section data managers
    template <typename T>
    Section_Data_Manager<T>* get_manager();

    File_Data_Manager* get_file_manager();
    Texture_Data_Manager* get_texture_manager();

    // Section data managers
    template <typename T>
    Section_Data_Manager<T> const* cget_manager() const;

    File_Data_Manager const* cget_file_manager() const;
    Texture_Data_Manager const* cget_texture_manager() const;

  private:
    // Pimpl Data
    //============================================================
    class Implementation;
    std::unique_ptr<Implementation> m_data;

    Implementation& imp()                { return *m_data; }
    Implementation const& cimp() const   { return *m_data; }
  };
}

#endif // SAK_PROJECT_DATA_HPP
