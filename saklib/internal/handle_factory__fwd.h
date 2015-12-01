#ifndef SAKLIB_INTERNAL_HANDLE_FACTORY__FWD_H
#define SAKLIB_INTERNAL_HANDLE_FACTORY__FWD_H

namespace saklib
{
    namespace internal
    {
        template <typename T>
        class Handle_Factory;

        using Any_Handle_Factory = Handle_Factory<void>;

        template <typename T>
        class Sequential_Handle_Factory;

        using Sequential_Any_Handle_Factory = Sequential_Handle_Factory<void>;

    } // namespace internal
} // namespace saklib

#endif // SAKLIB_INTERNAL_HANDLE_FACTORY__FWD_H

