#ifndef DATA_TYPE_MANAGER_H
#define DATA_TYPE_MANAGER_H

#include "data.h"
#include <map>

namespace Saklib
{
    /*
    Data_Type_Manager<K,T>
    ====================================================================================================
    Simple manager for Nodes via NodeIDs. It's really just map with a simplified interface. You will
    need access to this class to make use of the ID types.

    */

    template <typename K, typename T>
    class Data_Manager
    {
    public:
        using key_type = K;
        using data_type = Data<T>;
        using stored_type = typename data_type::stored_type;

        // Special 6
        //============================================================
        // Implicit default constructor
        //Data_Manager();

        // Implicit default destructor
        //~Data_Manager();

        // Implicit default copy
        //Data_Manager(Data_Manager const& other) = default;
        //Data_Manager& operator=(Data_Manager const& other) = default;

        // Implicit default move
        //Data_Manager(Data_Manager && other) = default;
        //Data_Manager& operator=(Data_Manager && other) = default;

        // Interface
        //============================================================

        bool has_data(key_type key) const;

        data_type& make_data(key_type key, stored_type const& value = stored_type(), bool value_is_user_editable = true);

        data_type* data(key_type key);
        data_type const* data(key_type key) const;

        void destroy(key_type key);

        void clear();

    private:
        using map_type = std::map < key_type, Data<stored_type> >;

        map_type m_map;
    };

} // namespace Saklib

#endif // DATA_TYPE_MANAGER_H

