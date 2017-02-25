#ifndef SAK_FILE_INTERFACE_HPP
#define SAK_FILE_INTERFACE_HPP

#include "fwd/manager.hpp"
#include "fwd/extended_manager.hpp"
class QString;

namespace sak
{
  class Project;

  namespace file
  {
    // ok so this is definately going to all need to be template generated...hmmm

    //---------------------------------------------------------------------------
    // file::interface
    //---------------------------------------------------------------------------
    class interface
    {
    public:
      interface(extended_handle const& a_ehandle, handle& a_handle, Project* a_project);

      void set_name(QString const& a_name);
      void set_description(QString const& a_description);
      void set_buildpath(QString const& a_buildpath);
      void set_sourcepath(QString const& a_sourcepath);

    private:
      extended_handle const& m_ehandle;
      handle& m_handle;
      Project* m_project;
    };

    //---------------------------------------------------------------------------
    // file::const_interface
    //---------------------------------------------------------------------------
    class const_interface
    {
    public:
      const_interface(extended_handle const& a_ehandle, handle const& a_handle);

      QString const& cget_name() const;
      QString const& cget_description() const;
      QString const& cget_buildpath() const;
      QString const& cget_sourcepath() const;
    private:
      extended_handle const& m_ehandle;
      handle const& m_handle;
    };
  }
}

#endif // SAK_FILE_INTERFACE_HPP
