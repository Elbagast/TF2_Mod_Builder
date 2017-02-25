#ifndef GENERIC_EXTENDED_MANAGER_HPP
#define GENERIC_EXTENDED_MANAGER_HPP

#include "fwd/extended_manager.hpp"
#include "manager.hpp"

namespace generic
{
    // Using these 3 parameters, create typedefs of all the relevent types.
    template <typename IDM, typename T, typename IT>
    struct Extended_Manager_Types
    {
        using id_manager_type = IDM;
        //using id_type = typename id_manager_type::id_type;
        using value_type = T;
        using basic_manager_type = Manager<IDM,T>;
        using basic_handle_type = Handle<IDM,T>;
        using manager_type = Extended_Manager<IDM,T,IT>;
        using handle_type = Extended_Handle<IDM,T,IT>;

        using interface_traits_type = IT;
        //using interface_type = typename interface_traits_type::interface_type;
        //using const_interface_type = typename interface_traits_type::const_interface_type;
    };


    template <typename IDM, typename T>
    class No_Interface_Traits :
            public Extended_Manager_Types<IDM, T, No_Interface_Traits<IDM,T>>
    {
    public:
        using interface_type = typename basic_handle_type::value_type&;
        using const_interface_type = typename basic_handle_type::value_type const&;

        interface_type get(handle_type const& a_handle, basic_handle_type& a_data)                    { return a_data.get(); }
        const_interface_type cget(handle_type const& a_handle, basic_handle_type const& a_data) const { return a_data.cget(); }
    };


    //---------------------------------------------------------------------------
    // generic::Extended_Manager<ID Manager, Type, Interface Traits>
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

    template <typename IDM, typename T, typename IT>
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

        using handle_type = Extended_Handle<IDM,T,IT>;

        Extended_Manager();
        explicit Extended_Manager(interface_traits_type&& a_interface_traits);

        handle_type make_null_handle() const;
        handle_type emplace_data(value_type&& a_value);
        handle_type get_handle(id_type const& a_id);
        std::size_t ref_count(id_type const& a_id) const;

        std::vector<id_type> all_ids() const;
        std::vector<basic_handle_type> all_basic_handles();
        std::vector<handle_type> all_handles();

    private:
        basic_manager_type m_manager;
        interface_traits_type m_interface_traits;
    };

    //---------------------------------------------------------------------------
    // generic::Extended_Handle<ID Manager, Type, Interface Traits>
    //---------------------------------------------------------------------------
    // Corresponding handle type for Extended_Manager. This is outside
    // Extended_Manager to allow for forward declaration.

    template <typename IDM, typename T, typename IT>
    class Extended_Handle
    {
    public:
        using extended_manager_type = Extended_Manager<IDM,T,IT>;
        using id_type = typename extended_manager_type::id_type;
        using value_type = typename extended_manager_type::value_type;
        using interface_traits_type = typename extended_manager_type::interface_traits_type;
        using interface_type = typename extended_manager_type::interface_type;
        using const_interface_type = typename extended_manager_type::const_interface_type;
        using basic_handle_type = typename extended_manager_type::basic_handle_type;

        friend class extended_manager_type;
        //friend class interface_type;
        //friend class const_interface_type;

    private:
        Extended_Handle(basic_handle_type const& a_handle, extended_manager_type* a_manager, interface_traits_type const& a_interface);
        Extended_Handle(basic_handle_type && a_handle, extended_manager_type* a_manager, interface_traits_type const& a_interface);
    public:
        Extended_Handle();
        ~Extended_Handle();
        Extended_Handle(Extended_Handle const& a_other);
        Extended_Handle& operator=(Extended_Handle const& a_other);
        Extended_Handle(Extended_Handle && a_other);
        Extended_Handle& operator=(Extended_Handle && a_other);

        bool is_valid() const;
        id_type const& id() const;
        std::size_t ref_count() const;
        interface_type get();
        const_interface_type cget() const;

        basic_handle_type& get_basic_handle();
        basic_handle_type const& cget_basic_handle() const;

        bool operator==(Extended_Handle const& a_other) const;
        bool operator!=(Extended_Handle const& a_other) const;

        bool operator==(basic_handle_type const& a_other) const;
        bool operator!=(basic_handle_type const& a_other) const;
    private:
        basic_handle_type m_handle;
        extended_manager_type* m_manager; // is this even needed? it isn't being used right now...
        interface_traits_type m_interface_traits;
    };
}

//---------------------------------------------------------------------------
// generic::Extended_Manager<ID Manager, Type, Interface Traits>
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
    return handle_type(basic_handle_type(), nullptr, m_interface_traits);
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
std::vector<typename generic::Extended_Manager<IDM,T,IT>::basic_handle_type> generic::Extended_Manager<IDM,T,IT>::all_basic_handles()
{
    return m_manager.all_handles();
}

template <typename IDM, typename T, typename IT>
std::vector<typename generic::Extended_Manager<IDM,T,IT>::handle_type> generic::Extended_Manager<IDM,T,IT>::all_handles()
{
    auto l_basic_handles = m_manager.all_handles();
    std::vector<handle_type> l_result{};
    l_result.reserve(l_basic_handles.size());
    for (auto& l_item : l_basic_handles)
    {
        auto l_handle = handle_type(std::move(l_item), this,m_interface_traits);
        l_result.push_back(std::move(l_handle));
    }
    return l_result;
}


//---------------------------------------------------------------------------
// generic::Extended_Handle<ID Manager, Type, Interface Traits>
//---------------------------------------------------------------------------
// Corresponding handle type for Extended_Manager. This is outside
// Extended_Manager to allow for forward declaration.

template <typename IDM, typename T, typename IT>
generic::Extended_Handle<IDM,T,IT>::Extended_Handle(basic_handle_type const& a_handle, extended_manager_type* a_manager, interface_traits_type const& a_interface):
    m_handle{a_handle},
    m_manager{a_manager},
    m_interface_traits{a_interface}
{}

template <typename IDM, typename T, typename IT>
generic::Extended_Handle<IDM,T,IT>::Extended_Handle(basic_handle_type && a_handle, extended_manager_type* a_manager, interface_traits_type const& a_interface):
    m_handle{std::move(a_handle)},
    m_manager{a_manager},
    m_interface_traits{a_interface}
{}

template <typename IDM, typename T, typename IT>
generic::Extended_Handle<IDM,T,IT>::Extended_Handle():
    m_handle{},
    m_manager{nullptr},
    m_interface_traits{}
{}

template <typename IDM, typename T, typename IT>
generic::Extended_Handle<IDM,T,IT>::~Extended_Handle() = default;

template <typename IDM, typename T, typename IT>
generic::Extended_Handle<IDM,T,IT>::Extended_Handle(Extended_Handle const& /*a_other*/) = default;

template <typename IDM, typename T, typename IT>
typename generic::Extended_Handle<IDM,T,IT>& generic::Extended_Handle<IDM,T,IT>::operator=(Extended_Handle const& /*a_other*/) = default;

template <typename IDM, typename T, typename IT>
generic::Extended_Handle<IDM,T,IT>::Extended_Handle(Extended_Handle && /*a_other*/) = default;

template <typename IDM, typename T, typename IT>
typename generic::Extended_Handle<IDM,T,IT>& generic::Extended_Handle<IDM,T,IT>::operator=(Extended_Handle && /*a_other*/) = default;

template <typename IDM, typename T, typename IT>
bool generic::Extended_Handle<IDM,T,IT>::is_valid() const
{
    return m_handle.is_valid();
}

template <typename IDM, typename T, typename IT>
typename generic::Extended_Handle<IDM,T,IT>::id_type const& generic::Extended_Handle<IDM,T,IT>::id() const
{
    return m_handle.id();
}

template <typename IDM, typename T, typename IT>
std::size_t generic::Extended_Handle<IDM,T,IT>::ref_count() const
{
    return m_handle.ref_count();
}

template <typename IDM, typename T, typename IT>
typename generic::Extended_Handle<IDM,T,IT>::interface_type generic::Extended_Handle<IDM,T,IT>::get()
{
    return m_interface_traits.get(*this, m_handle);
}

template <typename IDM, typename T, typename IT>
typename generic::Extended_Handle<IDM,T,IT>::const_interface_type generic::Extended_Handle<IDM,T,IT>::cget() const
{
    return m_interface_traits.cget(*this, m_handle);
}

template <typename IDM, typename T, typename IT>
typename generic::Extended_Handle<IDM,T,IT>::basic_handle_type& generic::Extended_Handle<IDM,T,IT>::get_basic_handle()
{
    return m_handle;
}
template <typename IDM, typename T, typename IT>
typename generic::Extended_Handle<IDM,T,IT>::basic_handle_type const& generic::Extended_Handle<IDM,T,IT>::cget_basic_handle() const
{
    return m_handle;
}

template <typename IDM, typename T, typename IT>
bool generic::Extended_Handle<IDM,T,IT>::operator==(Extended_Handle const& a_other) const
{
    return m_manager == a_other.m_manager && m_handle == a_other.m_handle;
}

template <typename IDM, typename T, typename IT>
bool generic::Extended_Handle<IDM,T,IT>::operator!=(Extended_Handle const& a_other) const
{
    return !(m_manager == a_other.m_manager && m_handle == a_other.m_handle);
}

template <typename IDM, typename T, typename IT>
bool generic::Extended_Handle<IDM,T,IT>::operator==(basic_handle_type const& a_other) const
{
    return m_handle == a_other;
}

template <typename IDM, typename T, typename IT>
bool generic::Extended_Handle<IDM,T,IT>::operator!=(basic_handle_type const& a_other) const
{
    return m_handle != a_other;
}

#endif // GENERIC_EXTENDED_MANAGER_HPP
