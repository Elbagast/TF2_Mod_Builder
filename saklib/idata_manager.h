#ifndef IDATA_MANAGER_H
#define IDATA_MANAGER_H

#include "idata.h"
#include "types.h"

namespace Saklib
{
    /*
    IData_Manager<K>
    ====================================================================================================
    Simple manager for Nodes via NodeIDs. It's really just map with a simplified interface. You will
    need access to this class to make use of the ID types.

    */

    template <typename K>
    class IData_Manager
    {
    public:
        using key_type = K;

        // Special 6
        //============================================================
        virtual ~IData_Manager() = 0;

        // Virtual Interface
        //============================================================
        // Does this manager have a value with this key?
        virtual bool has_data(key_type key) const = 0;

        // Get the interface to the value with this key, return nullptr if none exists
        virtual IData* idata(key_type key) = 0;
        virtual IData const* idata(key_type key) const = 0;

        // Make a value with this key and return its interface
        virtual IData* emplace_data(key_type key, Uptr<IData>&& data) = 0;

        // Destroy the value with this key
        virtual void destroy(key_type key) = 0;

        // Destroy everything held by this
        virtual void clear() = 0;
    };

} // namespace Saklib

template <typename K, typename T>
Saklib::IData_Manager::~IData_Manager() = default;

#endif // IDATA_MANAGER_H

