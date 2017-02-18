#ifndef FWD_EXTENDED_MANAGER_H
#define FWD_EXTENDED_MANAGER_H

#include "fwd_manager.h"

namespace generic
{
    template <typename H>
    class No_Interface_Traits;

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
    class Extended_Manager;

    template <typename IDM, typename T, typename IT = No_Interface_Traits<typename Manager<IDM,T>::handle_type>>
    class Extended_Handle;
}

#endif // FWD_EXTENDED_MANAGER_H