#ifndef SAK_ABSTRACT_OUTLINER_MULTITRUNK_ITEM_FWD_HPP
#define SAK_ABSTRACT_OUTLINER_MULTITRUNK_ITEM_FWD_HPP

namespace sak
{
  template <typename T_Parent_Item, typename... T_Children>
  class Abstract_Outliner_Multitrunk_Item;

  template <typename T_Parent_Item, typename... T_Children>
  class Abstract_Outliner_Readonly_Multitrunk_Item;

  template <typename... T_Children>
  class Abstract_Outliner_Root_Multitrunk_Item;
}

#endif // SAK_ABSTRACT_OUTLINER_MULTITRUNK_ITEM_FWD_HPP
