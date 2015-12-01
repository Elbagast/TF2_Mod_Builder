#ifndef SAKLIB_INTERNAL_HANDLE__FWD_H
#define SAKLIB_INTERNAL_HANDLE__FWD_H

namespace saklib
{
    namespace internal
    {
        template <typename T>
        class Handle;

        using Any_Handle = Handle<void>;
    } // namespace internal
} // namespace saklib

#endif // SAKLIB_INTERNAL_HANDLE__FWD_H
