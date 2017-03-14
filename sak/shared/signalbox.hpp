#ifndef SAK_SHARED_SIGNALBOX_HPP
#define SAK_SHARED_SIGNALBOX_HPP

#include "fwd/signalbox.hpp"
#include "fwd/manager.hpp"
#include <cstddef>

namespace sak
{
  namespace shared
  {
    namespace abstract
    {
      //---------------------------------------------------------------------------
      // shared::abstract::signalbox_out<T>
      //---------------------------------------------------------------------------
      // All signals that are dispatched from Project for a given object type.
      template <typename T>
      class signalbox
      {
      public:
        using object_type = T;
        using handle_type = handle<T>;

        virtual ~signalbox() = 0;

        // When a handle has its data changed, this is called.
        virtual void changed(handle_type const& a_handle) = 0;
        // When a handle has its data changed in a specific place, this is called.
        // a_section == 0 denotes the name and may have special logic requirements.
        virtual void changed_at(handle_type const& a_handle, std::size_t a_section) = 0;
        // When a handle has been added, this is called.
        virtual void added(handle_type const& a_handle) = 0;
        // When a handle has been removed, this is called.
        virtual void removed(handle_type const& a_handle) = 0;
        // When a handle editor is to be opened, this is called.
        virtual void requests_editor(handle_type const& a_handle) = 0;
        // When focus is changed to be on a handle, call this
        virtual void requests_focus(handle_type const& a_handle) = 0;
      };
    }
  }
}

#endif // SAK_SHARED_SIGNALBOX_HPP
