#ifndef FWD_MANAGER_H
#define FWD_MANAGER_H

namespace generic
{
    //---------------------------------------------------------------------------
    // generic::Manager<ID Manager, Type>
    //---------------------------------------------------------------------------
    // Object that manages a pool of objects allowing for shared referencing
    // via handles that can be expanded. When data is emplaced, a handle is
    // returned. If the last handle is destroyed, the data is destroyed.

    template <typename IDM, typename T>
    class Manager;

    template <typename IDM, typename T>
    class Handle;
}

#endif // FWD_MANAGER_H
