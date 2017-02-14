#include "uintid_manager.h"

#include <deque>
#include <algorithm>

template <typename T>
generic::internal::UintID_Manager<T>::UintID_Manager():
    m_next_id{1},
    m_retired_ids{}
{
}


template <typename T>
typename generic::internal::UintID_Manager<T>::id_type generic::internal::UintID_Manager<T>::make_null_id()
{
    return id_type(0);
}

template <typename T>
typename generic::internal::UintID_Manager<T>::id_type generic::internal::UintID_Manager<T>::make_id()
{
    if (!m_retired_ids.empty())
    {
        auto l_result = id_type(m_retired_ids.front());
        m_retired_ids.pop_front();
        return l_result;
    }
    else
    {
        return id_type(m_next_id++);
    }
}

template <typename T>
bool generic::internal::UintID_Manager<T>::retire_id(id_type a_id)
{
    if (is_active(a_id))
    {
        m_retired_ids.push_back(a_id.get());
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
bool generic::internal::UintID_Manager<T>::is_active(id_type a_id) const
{
    return (a_id.get() < m_next_id) && (std::find(m_retired_ids.cbegin(), m_retired_ids.cend(), a_id.get()) != m_retired_ids.end());
}


template generic::internal::UintID_Manager<unsigned char>;
template generic::internal::UintID_Manager<unsigned short>;
template generic::internal::UintID_Manager<unsigned int>;
template generic::internal::UintID_Manager<unsigned long>;
template generic::internal::UintID_Manager<unsigned long long>;
