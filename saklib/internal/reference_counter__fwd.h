#ifndef SAKLIB_INTERNAL_REFERENCE_COUNTER__FWD_H
#define SAKLIB_INTERNAL_REFERENCE_COUNTER__FWD_H

namespace saklib
{
    namespace internal
    {
        template <typename T_Storage, typename T_Handle, typename F_Incrementor, typename F_Decrementor>
        class Reference_Counter;

        template <typename T_Storage, typename T_Handle, void(T_Storage::*F_Incrementor)(T_Handle const&), void(T_Storage::*F_Decrementor)(T_Handle const&)>
        class Member_Reference_Counter;

    } // namespace internal
} // namespace saklib

#endif // SAKLIB_INTERNAL_REFERENCE_COUNTER__FWD_H

