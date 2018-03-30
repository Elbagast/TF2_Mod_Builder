#ifndef SAK_DUMMY_ENTITY_HPP
#define SAK_DUMMY_ENTITY_HPP

#include <sak/entity.hpp>

namespace sak
{
  class Dummy_Entity_Name :
      public Abstract_Entity_Name
  {
  private:
    std::string m_name;
  public:
    explicit Dummy_Entity_Name(std::string const& a_name):
      Abstract_Entity_Name(),
      m_name{a_name}
    {
    }
    ~Dummy_Entity_Name() override final = default;

    std::string const& get_name() const override final
    {
      return m_name;
    }
    bool set_name(std::string const& a_name) override final
    {
      if (a_name != m_name)
      {
        m_name = a_name;
        return true;
      }
      else
      {
        return false;
      }
    }
  };

  class Dummy_Entity_Type :
      public Abstract_Entity_Type
  {
  private:
    std::string m_data;
  public:
    explicit Dummy_Entity_Type(std::string const& a_data):
      Abstract_Entity_Type(),
      m_data{a_data}
    {
    }
    ~Dummy_Entity_Type() override final = default;

    std::string const& get_type() const override final
    {
      return m_data;
    }
  };

  class Dummy_Entity_Tooltip :
      public Abstract_Entity_Tooltip
  {
  private:
    std::string m_data;
  public:
    explicit Dummy_Entity_Tooltip(std::string const& a_data):
      Abstract_Entity_Tooltip(),
      m_data{a_data}
    {
    }
    ~Dummy_Entity_Tooltip() override final = default;

    std::string const& get_tooltip() const override final
    {
      return m_data;
    }
  };

  class Dummy_Entity_Icon :
      public Abstract_Entity_Icon
  {
  private:
    std::string m_data;
  public:
    explicit Dummy_Entity_Icon(std::string const& a_data):
      Abstract_Entity_Icon(),
      m_data{a_data}
    {
    }
    ~Dummy_Entity_Icon() override final = default;

    std::string const& get_iconpath() const override final
    {
      return m_data;
    }
  };

}

#endif // SAK_DUMMY_ENTITY_HPP
