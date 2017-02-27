#ifndef SAK_FILE_FWD_WIDGET_HPP
#define SAK_FILE_FWD_WIDGET_HPP

#include <sak/shared/fwd/widget.hpp>
#include "object.hpp"

namespace sak
{
  namespace file
  {
    namespace abstract
    {
      //---------------------------------------------------------------------------
      // shared::abstract::member_edit_widget
      //---------------------------------------------------------------------------
      // This is the base class for member value editor widgets. These are the
      // things that must be supplied. Inherit this class and compose the true
      // editor in it. Also for a signal to be generated it must not be part of a template.
      using member_edit_widget = shared::abstract::member_edit_widget;
    }

    //---------------------------------------------------------------------------
    // shared::member_edit_widget
    //---------------------------------------------------------------------------
    // Wraps the editor for the member value and normalises the signals so that we
    // can use it. This widget is responsible for dispatching the call to change
    // the member value when it is edited.

    template <std::size_t Index>
    using member_edit_widget = shared::member_edit_widget<object, Index>;

    //---------------------------------------------------------------------------
    // shared::widget<T>
    //---------------------------------------------------------------------------
    using widget = shared::widget<object>;
  }
}

#endif // SAK_FILE_FWD_WIDGET_HPP
