#ifndef GENERIC_EXTENDED_MANAGER_H
#define GENERIC_EXTENDED_MANAGER_H

#include "manager.h"

namespace generic
{
    template <typename H>
    class No_Interface_Traits
    {
    public:
        using interface_type = typename H::value_type&;
        using const_interface_type = typename H::value_type const&;

        interface_type get(H& a_ref)                    { return a_ref.get(); }
        const_interface_type cget(H const& a_ref) const { return a_ref.cget(); }
    };

    //---------------------------------------------------------------------------
    // generic::Extended_Manager<ID Extended_Manager, Type, Interface Traits>
    //---------------------------------------------------------------------------
    // Object that manages a pool of objects allowing for shared referencing
    // via handles that can be expanded. When data is emplaced, a handle is
    // returned. If the last handle is destroyed, the data is destroyed.

    // The interface traits class is responsible for intercepting the direct
    // data call and supplying an interface to use the data instead. It must
    // be default constructible, copyable and copy-assignable, and must supply
    // an interface that is at minimum the same as No_Interface_Traits above.
    // It can have state for e.g. intercepting the calls and logging the changes,
    // or diverting them to

    template <typename IDM, typename T, typename IT = No_Interface_Traits<typename Manager<IDM,T>::handle_type>>
    class Extended_Manager
    {
    public:
        using basic_manager_type = Manager<IDM,T>;

        using id_manager_type = typename basic_manager_type::id_manager_type;
        using id_type = typename basic_manager_type::id_type;
        using value_type = typename basic_manager_type::value_type;

        using basic_handle_type = typename basic_manager_type::handle_type;

        using interface_traits_type = IT;
        using interface_type = typename interface_traits_type::interface_type;
        using const_interface_type = typename interface_traits_type::const_interface_type;


        class Handle
        {
            friend class Extended_Manager;
        public:
            using Extended_Manager_type = Extended_Manager;
            using id_type = typename Extended_Manager::id_type;
            using value_type = typename Extended_Manager::value_type;
            using interface_traits_type = typename Extended_Manager::interface_traits_type;
            using interface_type = typename Extended_Manager::interface_type;
            using const_interface_type = typename Extended_Manager::const_interface_type;

        private:
            Handle(basic_handle_type const& a_handle, Extended_Manager_type* a_manager, interface_traits_type const& a_interface);
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
            interface_type get();
            const_interface_type cget() const;

        private:
            basic_handle_type m_handle;
            Extended_Manager_type* m_manager;
            interface_traits_type m_interface_traits;
        };

        using handle_type = Handle;

        Extended_Manager();
        explicit Extended_Manager(interface_traits_type&& a_interface_traits);

        handle_type make_null_handle() const;
        handle_type emplace_data(value_type&& a_value);
        handle_type get_handle(id_type const& a_id);
        std::size_t ref_count(id_type const& a_id) const;

        std::vector<id_type> all_ids() const;
        std::vector<basic_handle_type> all_basic_handles() const;
        std::vector<handle_type> all_handles() const;

    private:
        basic_manager_type m_manager;
        interface_traits_type m_interface_traits;
    };
}




template <typename IDM, typename T, typename IT>
generic::Extended_Manager<IDM,T,IT>::Handle::Handle(basic_handle_type const& a_handle, Extended_Manager_type* a_manager, interface_traits_type const& a_interface):
    m_handle{a_handle},
    m_manager{a_manager},
    m_interface_traits{a_interface}
{}

template <typename IDM, typename T, typename IT>
generic::Extended_Manager<IDM,T,IT>::Handle::Handle():
    m_handle{},
    m_manager{nullptr},
    m_interface_traits{}
{}

template <typename IDM, typename T, typename IT>
generic::Extended_Manager<IDM,T,IT>::Handle::~Handle() = default;

template <typename IDM, typename T, typename IT>
generic::Extended_Manager<IDM,T,IT>::Handle::Handle(Handle const& /*a_other*/) = default;

template <typename IDM, typename T, typename IT>
typename generic::Extended_Manager<IDM,T,IT>::Handle& generic::Extended_Manager<IDM,T,IT>::Handle::operator=(Handle const& /*a_other*/) = default;

template <typename IDM, typename T, typename IT>
generic::Extended_Manager<IDM,T,IT>::Handle::Handle(Handle && /*a_other*/) = default;

template <typename IDM, typename T, typename IT>
typename generic::Extended_Manager<IDM,T,IT>::Handle& generic::Extended_Manager<IDM,T,IT>::Handle::operator=(Handle && /*a_other*/) = default;

template <typename IDM, typename T, typename IT>
bool generic::Extended_Manager<IDM,T,IT>::Handle::is_valid() const
{
    return m_handle.is_valid();
}

template <typename IDM, typename T, typename IT>
typename generic::Extended_Manager<IDM,T,IT>::Handle::id_type const& generic::Extended_Manager<IDM,T,IT>::Handle::id() const
{
    return m_handle.id();
}

template <typename IDM, typename T, typename IT>
std::size_t generic::Extended_Manager<IDM,T,IT>::Handle::ref_count() const
{
    return m_handle.ref_count();
}

template <typename IDM, typename T, typename IT>
typename generic::Extended_Manager<IDM,T,IT>::Handle::interface_type generic::Extended_Manager<IDM,T,IT>::Handle::get()
{
    return m_interface_traits.get(m_handle);
}

template <typename IDM, typename T, typename IT>
typename generic::Extended_Manager<IDM,T,IT>::Handle::const_interface_type generic::Extended_Manager<IDM,T,IT>::Handle::cget() const
{
    return m_interface_traits.cget(m_handle);
}




template <typename IDM, typename T, typename IT>
generic::Extended_Manager<IDM,T,IT>::Extended_Manager():
    m_manager{},
    m_interface_traits{}
{}
template <typename IDM, typename T, typename IT>
generic::Extended_Manager<IDM,T,IT>::Extended_Manager(interface_traits_type&& a_interface_traits):
    m_manager{},
    m_interface_traits{std::move(a_interface_traits)}
{}

template <typename IDM, typename T, typename IT>
typename generic::Extended_Manager<IDM,T,IT>::handle_type generic::Extended_Manager<IDM,T,IT>::make_null_handle() const
{
    return handle_type();
}

template <typename IDM, typename T, typename IT>
typename generic::Extended_Manager<IDM,T,IT>::handle_type generic::Extended_Manager<IDM,T,IT>::emplace_data(value_type&& a_value)
{
    auto l_basic_handle = m_manager.emplace_data(std::move(a_value));
    return handle_type(std::move(l_basic_handle), this, m_interface_traits);
}

template <typename IDM, typename T, typename IT>
typename generic::Extended_Manager<IDM,T,IT>::handle_type generic::Extended_Manager<IDM,T,IT>::get_handle(id_type const& a_id)
{
    return handle_type{m_manager.get_handle(a_id), this, m_interface_traits};
}

template <typename IDM, typename T, typename IT>
std::size_t generic::Extended_Manager<IDM,T,IT>::ref_count(id_type const& a_id) const
{
    return m_manager.ref_count(a_id);
}

template <typename IDM, typename T, typename IT>
std::vector<typename generic::Extended_Manager<IDM,T,IT>::id_type> generic::Extended_Manager<IDM,T,IT>::all_ids() const
{
    return m_manager.all_ids();
}

template <typename IDM, typename T, typename IT>
std::vector<typename generic::Extended_Manager<IDM,T,IT>::basic_handle_type> generic::Extended_Manager<IDM,T,IT>::all_basic_handles() const
{
    return m_manager.all_handles();
}

template <typename IDM, typename T, typename IT>
std::vector<typename generic::Extended_Manager<IDM,T,IT>::handle_type> generic::Extended_Manager<IDM,T,IT>::all_handles() const
{
    auto l_basic_handles = m_manager.all_handles();
    std::vector<handle_type> l_result{};
    l_result.reserve(l_basic_handles.size());
    for (auto const& l_item : l_basic_handles)
    {
        // move calls instead?
        l_result.push_back(handle_type(l_item, this, m_interface_traits));
    }
    return l_result;
}

#endif // GENERIC_EXTENDED_MANAGER_H
