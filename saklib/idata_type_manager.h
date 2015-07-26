#ifndef IDATA_TYPE_MANAGER_H
#define IDATA_TYPE_MANAGER_H

//#include "idata_manager.h"
#include "idata_type.h"
#include "types.h"

namespace Saklib
{
    /*
    IData_Manager<K>
    ====================================================================================================
    Simple manager for Nodes via NodeIDs. It's really just map with a simplified interface. You will
    need access to this class to make use of the ID types.

    */

    template <typename K, typename T>
    class IData_Type_Manager
    {
    public:
        using key_type = K;
        using stored_type = T;
        using idata_type = IData_Type<stored_type>;

        // Special 6
        //============================================================
        virtual ~IData_Type_Manager() = 0;

        // IData_Manager Virtual Interface
        //============================================================
        // Does this manager have a value with this key?
        virtual bool has_data(key_type key) const = 0;

        // Make a value with this key and return its interface
        virtual idata_type* emplace_data(key_type key, Uptr<idata_type>&& data) = 0;
        virtual idata_type* make_data(key_type key, stored_type const& value, bool data_is_user_editable = true) = 0;

        // Get the interface to the value with this key, return nullptr if none exists
        virtual idata_type* idata(key_type key) = 0;
        virtual idata_type const* idata(key_type key) const = 0;

        // Destroy the value with this key
        virtual void destroy(key_type key) = 0;

        // Destroy everything held by this
        virtual void clear() = 0;
    };

} // namespace Saklib

template <typename K, typename T>
Saklib::IData_Type_Manager::~IData_Type_Manager() = default;

#endif // IDATA_TYPE_MANAGER_H

