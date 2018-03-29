#ifndef SAK_ENTITY_SYSTEM_DATA_MANAGER_HPP
#define SAK_ENTITY_SYSTEM_DATA_MANAGER_HPP

#ifndef SAK_ENTITY_ID_HPP
#include "entity_id.hpp"
#endif

#ifndef INCLUDE_STD_MAP
#define INCLUDE_STD_MAP
#include <map>
#endif

#ifndef INCLUDE_STD_VECTOR
#define INCLUDE_STD_VECTOR
#include <vector>
#endif

#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif

class QString;

namespace sak
{


  class Entity_Name_Data
  {
  private:
    Entity_ID m_id;
    QString m_name;
  public:
    Entity_Name_Data(Entity_ID a_id, QString const& a_name);

    Entity_ID id() const;

    QString name() const;
    bool set_name(QString const& a_name);

  };


  template <typename T_Part>
  class Entity_Part_Manager
  {
  public:
    using Part_Type = T_Part;
  private:
    std::map<Entity_ID, std::unique_ptr<Part_Type>> m_data;
  public:
    Entity_Part_Manager();

    bool has(Entity_ID a_id) const;
    std::size_t count() const;

    std::vector<Entity_ID> all_ids() const;
    std::vector<std::pair<Entity_ID, Part_Type*>> all_data() const; // ?

    Part_Type* get(Entity_ID a_id);
    Part_Type const* cget(Entity_ID a_id) const;

    bool add(Entity_ID a_id, std::unique_ptr<Part_Type>&& a_data);
    bool remove(Entity_ID a_id);


  };

  using Entity_Name_Data_Manager = Entity_Part_Manager<Entity_Name_Data>;


  class Abstract_Entity_System_Data
  {
  public:
    virtual ~Abstract_Entity_System_Data() = 0;

    virtual QString type() const = 0;
    virtual QString iconpath() const = 0;
    virtual QString name() const = 0;
    virtual bool set_name(QString const& a_name) = 0;

  };




  class Entity_System_Data_Manager
  {
  private:
    std::map<Entity_ID, std::unique_ptr<Abstract_Entity_System_Data>> m_data;
  public:
    Entity_System_Data_Manager();
  };

}

#endif // ENTITY_SYSTEM_DATA_MANAGER_HPP
