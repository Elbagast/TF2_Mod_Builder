#ifndef SAK_PROJECT_SIGNAL_DISPATCHER_HPP
#define SAK_PROJECT_SIGNAL_DISPATCHER_HPP

#include "signalbox.hpp"
#include <vector>

namespace sak
{
  namespace project
  {
    //---------------------------------------------------------------------------
    // project::signal_dispatcher
    //---------------------------------------------------------------------------
    // project::object uses this class to dispatch signals to objects that
    // represent its data and have to keep it up to date.

    class signal_dispatcher :
        public abstract::signalbox
    {
    public:
      explicit signal_dispatcher(abstract::signalbox* a_forbidden);

      ~signal_dispatcher() override;

      // Add an object that will rely on the Project's signals. If nulltpr, nothing happens.
      void add_signalbox(abstract::signalbox* a_signalbox);

      // Remove an object that will rely on the Project's signals. If nulltpr, nothing happens.
      void remove_signalbox(abstract::signalbox* a_signalbox);

      // When a File has its data changed(anything but the name), this is called.
      void changed(file::extended_handle const& a_ehandle) override final;
      // When a File has its data changed in a specific place, this is called.
      void changed_at(file::extended_handle const& a_ehandle, std::size_t a_section) override final;
      // When a File has been added, this is called.
      void added(file::extended_handle const& a_ehandle) override final;
      // When a File has been removed, this is called.
      void removed(file::extended_handle const& a_ehandle) override final;
      // When a File requests an editor, this is called.
      void requests_editor(file::extended_handle const& a_ehandle) override final;
      // When a File requests an editor, this is called.
      void requests_focus(file::extended_handle const& a_ehandle) override final;

      // When a texture has its data changed(anything but the name), this is called.
      void changed(texture::extended_handle const& a_ehandle) override final;
      // When a texture has its data changed in a specific place, this is called.
      void changed_at(texture::extended_handle const& a_ehandle, std::size_t a_section) override final;
      // When a texture has been added, this is called.
      void added(texture::extended_handle const& a_ehandle) override final;
      // When a texture has been removed, this is called.
      void removed(texture::extended_handle const& a_ehandle) override final;
      // When a texture requests an editor, this is called.
      void requests_editor(texture::extended_handle const& a_ehandle) override final;
      // When a texture requests an editor, this is called.
      void requests_focus(texture::extended_handle const& a_ehandle) override final;

    private:
      abstract::signalbox* m_forbidden;
      std::vector<abstract::signalbox*> m_dependents;
    };
  }
}

#endif // SAK_PROJECT_SIGNAL_DISPATCHER_HPP
