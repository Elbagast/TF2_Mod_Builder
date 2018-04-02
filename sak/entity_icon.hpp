#ifndef SAK_ENTITY_ICON_HPP
#define SAK_ENTITY_ICON_HPP

#ifndef SAK_ENTITY_ICON_FWD_HPP
#include "entity_icon_fwd.hpp"
#endif

#ifndef SAK_ABSTRACT_ENTITY_ICON_HPP
#include "abstract_entity_icon.hpp"
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Local_Entity_Icon
  //---------------------------------------------------------------------------
  // The component of an Entity that holds the icon interface. Stores the icon
  // path as a variable.

  class Local_Entity_Icon :
      public Abstract_Entity_Icon
  {
  private:
    // Data Members
    //============================================================
    std::string m_iconpath;

  public:
    // Special 6
    //============================================================
    explicit Local_Entity_Icon(std::string const& a_iconpath);
    ~Local_Entity_Icon() override final;

    // Block copying components.
    Local_Entity_Icon(Local_Entity_Icon const&) = delete;
    Local_Entity_Icon& operator=(Local_Entity_Icon const&) = delete;

    // Block moving components.
    Local_Entity_Icon(Local_Entity_Icon &&) = delete;
    Local_Entity_Icon& operator=(Local_Entity_Icon &&) = delete;

    // Interface
    //============================================================
    std::string const& iconpath() const override final;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Remote_Entity_Icon
  //---------------------------------------------------------------------------
  // The component of an Entity that holds the icon interface. Stores the icon
  // path as a reference to a string held elsewhere.

  class Remote_Entity_Icon :
      public Abstract_Entity_Icon
  {
  private:
    // Data Members
    //============================================================
    std::string const& m_iconpath;

  public:
    // Special 6
    //============================================================
    explicit Remote_Entity_Icon(std::string const& a_iconpath);
    ~Remote_Entity_Icon() override final;

    // Block copying components.
    Remote_Entity_Icon(Remote_Entity_Icon const&) = delete;
    Remote_Entity_Icon& operator=(Remote_Entity_Icon const&) = delete;

    // Block moving components.
    Remote_Entity_Icon(Remote_Entity_Icon &&) = delete;
    Remote_Entity_Icon& operator=(Remote_Entity_Icon &&) = delete;

    // Interface
    //============================================================
    std::string const& iconpath() const override final;
  };
}

#endif // SAK_ENTITY_ICON_HPP
