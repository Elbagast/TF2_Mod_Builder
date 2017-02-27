#ifndef SAK_SHARED_FWD_WIDGET_HPP
#define SAK_SHARED_FWD_WIDGET_HPP

#include <cstddef>

namespace sak
{
  namespace shared
  {
    namespace abstract
    {
      //---------------------------------------------------------------------------
      // shared::abstract::member_edit_widget
      //---------------------------------------------------------------------------
      // This is the base class for member value editor widgets. These are the
      // things that must be supplied. Inherit this class and compose the true
      // editor in it. Also for a signal to be generated it must not be part of a template.
      class member_edit_widget;
    }

    //---------------------------------------------------------------------------
    // shared::member_edit_widget
    //---------------------------------------------------------------------------
    // Wraps the editor for the member value and normalises the signals so that we
    // can use it. This widget is responsible for dispatching the call to change
    // the member value when it is edited.

    template <typename T, std::size_t Index>
    class member_edit_widget;

    //---------------------------------------------------------------------------
    // shared::widget<T>
    //---------------------------------------------------------------------------
    template <typename T>
    class widget;
  }
}

#endif // SAK_SHARED_FWD_WIDGET_HPP
