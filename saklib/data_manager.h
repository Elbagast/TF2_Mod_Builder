#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include "idata_manager.h"
#include "data.h"
#include <map>

namespace Saklib
{
    /*
    Data_Manager
    ====================================================================================================
    Simple manager for Nodes via NodeIDs. It's really just map with a simplified interface. You will
    need access to this class to make use of the ID types.

    */

    class Data_Manager :
            public IData_Manager<DataID>
    {
    public:
        // Special 6
        //============================================================
        Data_Manager();
        ~Data_Manager() override;

        // NO COPYING
        Data_Manager(Data_Manager const& other) = delete;
        Data_Manager& operator=(Data_Manager const& other) = delete;

        // Implicit default move
        //Data_Manager(Data_Manager && other) = default;
        //Data_Manager& operator=(Data_Manager && other) = default;

        // IData_Manager Interface
        //============================================================
        // Does this manager have a value with this key?
        bool has_data(key_type key) const override;

        // Get the interface to the value with this key, return nullptr if none exists
        IData* idata(key_type key) override;
        IData const* idata(key_type key) const override;

        // Make a value with this key and return its interface
        IData* emplace_data(key_type key, Uptr<IData>&& data) override;

        // Destroy the value with this key
        void destroy(key_type key) override;

        // Destroy everything held by this
        void clear() override;

    private:
        using map_type = std::map < key_type, Uptr<IData> >;

        map_type m_map;
    };

} // namespace Saklib

#endif // DATA_MANAGER_H
