#ifndef SAK_SHARED_FWD_ABSTRACT_MEMBER_WIDGET_HPP
#define SAK_SHARED_FWD_ABSTRACT_MEMBER_WIDGET_HPP

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
  }
}
#endif // SAK_SHARED_FWD_ABSTRACT_MEMBER_WIDGET_HPP
