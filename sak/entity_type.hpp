#ifndef SAK_ENTITY_TYPE_HPP
#define SAK_ENTITY_TYPE_HPP

#ifndef SAK_ENTITY_TYPE_FWD_HPP
#include "entity_type_fwd.hpp"
#endif

#ifndef SAK_ABSTRACT_ENTITY_TYPE_HPP
#include "abstract_entity_type.hpp"
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Local_Entity_Type
  //---------------------------------------------------------------------------
  // The component of an Entity that holds the type interface. Stores the type
  // as a variable.

  class Local_Entity_Type :
      public Abstract_Entity_Type
  {
  private:
    // Data Members
    //============================================================
    std::string m_type;

  public:
    // Special 6
    //============================================================
    // Construct with this type as the intial.
    explicit Local_Entity_Type(std::string const& a_type);
    ~Local_Entity_Type() override final;

    // Block copying components.
    Local_Entity_Type(Local_Entity_Type const&) = delete;
    Local_Entity_Type& operator=(Local_Entity_Type const&) = delete;

    // Block moving components.
    Local_Entity_Type(Local_Entity_Type &&) = delete;
    Local_Entity_Type& operator=(Local_Entity_Type &&) = delete;

    // Interface
    //============================================================
    std::string const& type() const override final;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Remote_Entity_Type
  //---------------------------------------------------------------------------
  // The component of an Entity that holds the type interface. Stores the type
  // as a reference to a string held elsewhere.

  class Remote_Entity_Type :
      public Abstract_Entity_Type
  {
  private:
    // Data Members
    //============================================================
    std::string const& m_type;

  public:
    // Special 6
    //============================================================
    // Construct with this type as the intial.
    explicit Remote_Entity_Type(std::string const& a_type);
    ~Remote_Entity_Type() override final;

    // Block copying components.
    Remote_Entity_Type(Remote_Entity_Type const&) = delete;
    Remote_Entity_Type& operator=(Remote_Entity_Type const&) = delete;

    // Block moving components.
    Remote_Entity_Type(Remote_Entity_Type &&) = delete;
    Remote_Entity_Type& operator=(Remote_Entity_Type &&) = delete;

    // Interface
    //============================================================
    std::string const& type() const override final;
  };
}

#endif // SAK_ENTITY_TYPE_HPP
