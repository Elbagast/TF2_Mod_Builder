#ifndef SAK_PROJECT_HOLDER_HPP
#define SAK_PROJECT_HOLDER_HPP

#ifndef SAK_PROJECT_FWD_HPP
#include "project_fwd.hpp"
#endif

#ifndef SAK_PROJECT_MAIN_WIDGET_FWD_HPP
#include "project_main_widget_fwd.hpp"
#endif

#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif

class QString;

namespace sak
{
  //---------------------------------------------------------------------------
  // Project_Holder
  //---------------------------------------------------------------------------
  // Group a load of things unique to a project and supply a simple interface
  // to them. This class then makes sure these heavily linked objects are in a
  // valid state and seperates out the save/load logic, which relates to both
  // the Entity data and the editor data.

  class Project_Holder
  {
  private:
    // Member Data
    //============================================================
    std::unique_ptr<Project> m_project;
    std::unique_ptr<Project_Main_Widget> m_widget;

  public:
    // Special 6
    //============================================================
    // Project_Holder cannot exist without a valid project filepath.
    // Can throw Directory_Missing_Error, File_Missing_Error, File_Write_Error, File_Read_Error, XML_Error
    explicit Project_Holder(QString const& a_filepath);
    ~Project_Holder();

    Project_Holder(Project_Holder const&) = delete;
    Project_Holder& operator=(Project_Holder const&) = delete;

    Project_Holder(Project_Holder &&);
    Project_Holder& operator=(Project_Holder &&);

    // Interface
    //============================================================
    // Save the current data to the file.
    // Can throw File_Missing_Error, File_Write_Error
    void save() const;

    // Get the data from the file and discard the current data.
    // Can throw File_Missing_Error, File_Read_Error, XML_Error
    void load();

    Project* project() const;
    Project_Main_Widget* widget() const;

  };
} // namespace sak

#endif // SAK_PROJECT_HOLDER_HPP
