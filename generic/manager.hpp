#ifndef GENERIC_MANAGER_HPP
#define GENERIC_MANAGER_HPP

#include "fwd/manager.hpp"
#include <map>
#include <memory>
#include <vector>
#include <exception>
#include <cassert>
#include <type_traits>

namespace generic
{
  namespace internal
  {
    template <typename ID, typename T>
    class Holder
    {
    public:
      using id_type = ID;
      using value_type = T;

      Holder();
      Holder(id_type const& a_id, value_type&& a_value);

      id_type const& id() const;
      std::size_t ref_count() const;
      value_type& get();
      value_type const& cget() const;

      bool is_valid() const;
      void clear();

      bool operator==(Holder const& a_other) const;
      bool operator!=(Holder const& a_other) const;

      bool operator<(Holder const& a_other) const;
      bool operator>(Holder const& a_other) const;
      bool operator<=(Holder const& a_other) const;
      bool operator>=(Holder const& a_other) const;

      using shared_ptr_type = std::shared_ptr<std::pair<id_type, value_type>>;

      shared_ptr_type const& data() const { return m_data; }
    private:
      shared_ptr_type m_data;
    };
  }


  //---------------------------------------------------------------------------
  // generic::Manager<ID Manager, Type>
  //---------------------------------------------------------------------------
  // Object that manages a pool of objects allowing for shared referencing
  // via handles that can be expanded. When data is emplaced, a handle is
  // returned. If the last handle is destroyed, the data is destroyed.

  template <typename IDM, typename T>
  class Manager
  {
  public:
    using id_manager_type = IDM;
    using id_type = typename id_manager_type::id_type;
    using value_type = T;
    using handle_type = Handle<IDM,T>;
    friend class handle_type;

    using holder_type = internal::Holder<id_type, value_type>;
    using map_type = std::map<id_type, holder_type>;
    using pair_type = std::pair<id_type, holder_type>;

    handle_type make_null_handle() const;
    handle_type emplace_data(value_type&& a_value);
    handle_type get_handle(id_type const& a_id);
    std::size_t ref_count(id_type const& a_id) const;

    std::vector<id_type> all_ids() const;
    std::vector<handle_type> all_handles();

  private:
    bool if_unused_destroy(id_type const& a_id);

    id_manager_type m_id_manager;
    map_type m_data;
  };

  //---------------------------------------------------------------------------
  // generic::Handle<ID Manager, Type>
  //---------------------------------------------------------------------------
  // Corresponding handle for Manager. This is outside Manager to allow for
  // forward declaration.
  template <typename IDM, typename T>
  class Handle
  {
  public:
    using manager_type = Manager<IDM,T>;
    using id_type = typename manager_type::id_type;
    using value_type = typename manager_type::value_type;

    friend class manager_type;

  private:
    using holder_type = typename manager_type::holder_type;
    Handle(holder_type const& a_holder, manager_type* a_manager);
  public:
    Handle();
    ~Handle();
    Handle(Handle const& a_other);
    Handle& operator=(Handle const& a_other);
    Handle(Handle && a_other);
    Handle& operator=(Handle && a_other);

    bool is_valid() const;
    id_type const& id() const;
    std::size_t ref_count() const;
    value_type& get();
    value_type const& cget() const;

    bool operator==(Handle const& a_other) const;
    bool operator!=(Handle const& a_other) const;

    bool operator<(Handle const& a_other) const;
    bool operator>(Handle const& a_other) const;
    bool operator<=(Handle const& a_other) const;
    bool operator>=(Handle const& a_other) const;

  private:
    holder_type m_holder;
    manager_type* m_manager;
  };
}



//---------------------------------------------------------------------------
// generic::internal::Holder<ID, Type>
//---------------------------------------------------------------------------
// Nested convenience class.

template <typename ID, typename T>
generic::internal::Holder<ID,T>::Holder():
    m_data{nullptr}
{

}

template <typename ID, typename T>
generic::internal::Holder<ID,T>::Holder(id_type const& a_id, value_type&& a_value):
    m_data{std::make_shared<std::pair<id_type, value_type>>(std::pair<id_type, value_type>(a_id, std::move(a_value)))}
{}

template <typename ID, typename T>
typename generic::internal::Holder<ID,T>::id_type const& generic::internal::Holder<ID,T>::id() const
{
    return m_data->first;
}

template <typename ID, typename T>
std::size_t generic::internal::Holder<ID,T>::ref_count() const
{
    return m_data.use_count() - 1;
}

template <typename ID, typename T>
typename generic::internal::Holder<ID,T>::value_type& generic::internal::Holder<ID,T>::get()
{
    if (!m_data) throw std::out_of_range("already deleted");
    return m_data->second;
}

template <typename ID, typename T>
typename generic::internal::Holder<ID,T>::value_type const& generic::internal::Holder<ID,T>::cget() const
{
    if (!m_data) throw std::out_of_range("already deleted");
    return m_data->second;
}

template <typename ID, typename T>
bool generic::internal::Holder<ID,T>::is_valid() const
{
    return m_data.get() != nullptr;
}

template <typename ID, typename T>
void generic::internal::Holder<ID,T>::clear()
{
    m_data = shared_ptr_type(nullptr);
}

template <typename ID, typename T>
bool generic::internal::Holder<ID,T>::operator==(Holder const& a_other) const
{
    return m_data == a_other.m_data;
}

template <typename ID, typename T>
bool generic::internal::Holder<ID,T>::operator!=(Holder const& a_other) const
{
   return !this->operator==(a_other);
}

template <typename ID, typename T>
bool generic::internal::Holder<ID,T>::operator<(Holder const& a_other) const
{
   return m_data < a_other.m_data;
}

template <typename ID, typename T>
bool generic::internal::Holder<ID,T>::operator>(Holder const& a_other) const
{
   return a_other.operator<(*this);
}
template <typename ID, typename T>
bool generic::internal::Holder<ID,T>::operator<=(Holder const& a_other) const
{
   return !this->operator>(a_other);
}

template <typename ID, typename T>
bool generic::internal::Holder<ID,T>::operator>=(Holder const& a_other) const
{
   return !this->operator<(a_other);
}





//---------------------------------------------------------------------------
// generic::Manager<ID Manager, Type>
//---------------------------------------------------------------------------
// Object that manages a pool of objects allowing for shared referencing
// via handles that can be expanded. When data is emplaced, a handle is
// returned. If the last handle is destroyed, the data is destroyed.

template <typename IDM, typename T>
typename generic::Manager<IDM,T>::handle_type generic::Manager<IDM,T>::make_null_handle() const
{
    return handle_type();
}

template <typename IDM, typename T>
typename generic::Manager<IDM,T>::handle_type generic::Manager<IDM,T>::emplace_data(value_type&& a_value)
{
    auto l_id = m_id_manager.make_id();
    m_data.emplace(l_id, holder_type(l_id, std::move(a_value)));
    return get_handle(l_id);
}

template <typename IDM, typename T>
typename generic::Manager<IDM,T>::handle_type generic::Manager<IDM,T>::get_handle(id_type const& a_id)
{
    return handle_type{m_data.at(a_id), this};
}

template <typename IDM, typename T>
std::size_t generic::Manager<IDM,T>::ref_count(id_type const& a_id) const
{
    return m_data.at(a_id).ref_count();
}

template <typename IDM, typename T>
std::vector<typename generic::Manager<IDM,T>::id_type> generic::Manager<IDM,T>::all_ids() const
{
    std::vector<id_type> l_result{};
    l_result.reserve(m_data.size());
    for (auto const& l_item : m_data)
    {
        l_result.push_back(l_item.first);
    }
    return l_result;
}

template <typename IDM, typename T>
std::vector<typename generic::Manager<IDM,T>::handle_type> generic::Manager<IDM,T>::all_handles()
{
    std::vector<handle_type> l_result{};
    l_result.reserve(m_data.size());
    for (auto const& l_item : m_data)
    {
        auto l_handle = handle_type(l_item.second, this);
        l_result.push_back(std::move(l_handle));
    }
    return l_result;
}

template <typename IDM, typename T>
bool generic::Manager<IDM,T>::if_unused_destroy(id_type const& a_id)
{
    auto l_found = m_data.find(a_id);
    if (l_found->second.ref_count() == 0)
    {
        m_data.erase(l_found);
        return true;
    }
    else
    {
        return false;
    }
}


//---------------------------------------------------------------------------
// generic::Handle<ID Manager, Type>
//---------------------------------------------------------------------------
// Corresponding handle for Manager. This is outside Manager to allow for
// forward declaration.


template <typename IDM, typename T>
generic::Handle<IDM,T>::Handle(holder_type const& a_holder, manager_type* a_manager):
    m_holder{a_holder},
    m_manager{a_manager}
{}

template <typename IDM, typename T>
generic::Handle<IDM,T>::Handle():
    m_holder{},
    m_manager{nullptr}
{}

template <typename IDM, typename T>
generic::Handle<IDM,T>::~Handle()
{
    if (is_valid())
    {
       assert(m_holder.data() != nullptr);
       // get the id
       auto l_id = m_holder.id();
       // destroy the shared pointer
       //m_holder.clear();
       // tell the manager to cleanup if this was the last one
       m_manager->if_unused_destroy(l_id);
    }
}

template <typename IDM, typename T>
generic::Handle<IDM,T>::Handle(Handle const& /*a_other*/) = default;

template <typename IDM, typename T>
typename generic::Handle<IDM,T>& generic::Handle<IDM,T>::operator=(Handle const& /*a_other*/) = default;

template <typename IDM, typename T>
generic::Handle<IDM,T>::Handle(Handle && /*a_other*/) = default;

template <typename IDM, typename T>
typename generic::Handle<IDM,T>& generic::Handle<IDM,T>::operator=(Handle && /*a_other*/) = default;

template <typename IDM, typename T>
bool generic::Handle<IDM,T>::is_valid() const
{
    return m_holder.is_valid();
}

template <typename IDM, typename T>
typename generic::Handle<IDM,T>::id_type const& generic::Handle<IDM,T>::id() const
{
    return m_holder.id();
}

template <typename IDM, typename T>
std::size_t generic::Handle<IDM,T>::ref_count() const
{
    return m_holder.ref_count();
}

template <typename IDM, typename T>
typename generic::Handle<IDM,T>::value_type& generic::Handle<IDM,T>::get()
{
    return m_holder.get();
}

template <typename IDM, typename T>
typename generic::Handle<IDM,T>::value_type const& generic::Handle<IDM,T>::cget() const
{
    return m_holder.cget();
}

template <typename IDM, typename T>
bool generic::Handle<IDM,T>::operator==(Handle<IDM,T> const& a_other) const
{
    return m_manager == a_other.m_manager && m_holder == a_other.m_holder;
}

template <typename IDM, typename T>
bool generic::Handle<IDM,T>::operator!=(Handle<IDM,T> const& a_other) const
{
    return !this->operator==(a_other);
}

template <typename IDM, typename T>
bool generic::Handle<IDM,T>::operator<(Handle<IDM,T> const& a_other) const
{
    return m_manager < a_other.m_manager && m_holder < a_other.m_holder;
}

template <typename IDM, typename T>
bool generic::Handle<IDM,T>::operator>(Handle<IDM,T> const& a_other) const
{
    return a_other.operator<(*this);
}
template <typename IDM, typename T>
bool generic::Handle<IDM,T>::operator<=(Handle<IDM,T> const& a_other) const
{
    return !this->operator>(a_other);
}

template <typename IDM, typename T>
bool generic::Handle<IDM,T>::operator>=(Handle<IDM,T> const& a_other) const
{
    return !this->operator<(a_other);
}


#endif // GENERIC_MANAGER_HPP
