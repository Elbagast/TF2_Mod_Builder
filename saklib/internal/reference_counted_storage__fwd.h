#ifndef SAKLIB_INTERNAL_REFERENCE_COUNTED_STORAGE__FWD_H
#define SAKLIB_INTERNAL_REFERENCE_COUNTED_STORAGE__FWD_H

namespace saklib
{
    namespace internal
    {
        template <typename T>
        class No_Pre_Destructor;

        template <typename T, typename F_Pre_Destructor>
        class Reference_Counted_Storage;
    } // namespace internal
} // namespace saklib

#endif // SAKLIB_INTERNAL_REFERENCE_COUNTED_STORAGE__FWD_H
