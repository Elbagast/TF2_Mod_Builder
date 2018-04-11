#ifndef SAK_ENTITY_TOOLTIP_HPP
#define SAK_ENTITY_TOOLTIP_HPP

#ifndef SAK_ENTITY_TOOLTIP_FWD_HPP
#include "entity_tooltip_fwd.hpp"
#endif

#ifndef SAK_ABSTRACT_ENTITY_TOOLTIP_HPP
#include "abstract_entity_tooltip.hpp"
#endif

#ifndef SAK_STRING_HPP
#include "../string.hpp"
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Local_Entity_Tooltip
  //---------------------------------------------------------------------------
  // The component of an Entity that holds the type interface. Stores the type
  // as a variable.

  class Local_Entity_Tooltip :
      public Abstract_Entity_Tooltip
  {
  private:
    // Data Members
    //============================================================
    String m_tooltip;

  public:
    // Special 6
    //============================================================
    explicit Local_Entity_Tooltip(String const& a_tooltip);
    ~Local_Entity_Tooltip() override final;

    // Block copying components.
    Local_Entity_Tooltip(Local_Entity_Tooltip const&) = delete;
    Local_Entity_Tooltip& operator=(Local_Entity_Tooltip const&) = delete;

    // Block moving components.
    Local_Entity_Tooltip(Local_Entity_Tooltip &&) = delete;
    Local_Entity_Tooltip& operator=(Local_Entity_Tooltip &&) = delete;

    // Interface
    //============================================================
    String const& tooltip() const override final;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Remote_Entity_Tooltip
  //---------------------------------------------------------------------------
  // The component of an Entity that holds the type interface. Stores the type
  // as a reference to a string held elsewhere.

  class Remote_Entity_Tooltip :
      public Abstract_Entity_Tooltip
  {
  private:
    // Data Members
    //============================================================
    String const& m_tooltip;

  public:
    // Special 6
    //============================================================
    explicit Remote_Entity_Tooltip(String const& a_tooltip);
    ~Remote_Entity_Tooltip() override final;

    // Block copying components.
    Remote_Entity_Tooltip(Remote_Entity_Tooltip const&) = delete;
    Remote_Entity_Tooltip& operator=(Remote_Entity_Tooltip const&) = delete;

    // Block moving components.
    Remote_Entity_Tooltip(Remote_Entity_Tooltip &&) = delete;
    Remote_Entity_Tooltip& operator=(Remote_Entity_Tooltip &&) = delete;

    // Interface
    //============================================================
    String const& tooltip() const override final;
  };
}

#endif // SAK_ENTITY_TOOLTIP_HPP
