#ifndef SAK_SHARED_SIGNALBOX_HPP
#define SAK_SHARED_SIGNALBOX_HPP

#include "fwd/signalbox.hpp"
#include "fwd/extended_manager.hpp"
#include <cstddef>

namespace sak
{
  namespace shared
  {
    namespace abstract
    {
      //---------------------------------------------------------------------------
      // shared::abstract::signalbox<T>
      //---------------------------------------------------------------------------
      // All signals that are dispatched from Project for a given handle type.
      template <typename T>
      class signalbox
      {
      public:
        using extended_handle_type = extended_handle<T>;

        virtual ~signalbox() = default;

        // When a handle has its data changed, this is called.
        virtual void changed(extended_handle_type const& a_ehandle) = 0;
        // When a handle has its data changed in a specific place, this is called.
        // a_section == 0 denotes the name and may have special logic requirements.
        virtual void changed_at(extended_handle_type const& a_ehandle, std::size_t a_section) = 0;
        // When a handle has been added, this is called.
        virtual void added(extended_handle_type const& a_ehandle) = 0;
        // When a handle has been removed, this is called.
        virtual void removed(extended_handle_type const& a_ehandle) = 0;
        // When a handle editor is to be opened, this is called.
        virtual void requests_editor(extended_handle_type const& a_ehandle) = 0;
        // When focus is changed to be on a handle, call this
        virtual void requests_focus(extended_handle_type const& a_ehandle) = 0;
      };
    }
  }
}

#endif // SAK_SHARED_SIGNALBOX_HPP
