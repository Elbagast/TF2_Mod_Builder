#ifndef SAKLIB_INTERNAL_UINT_ID__FWD_H
#define SAKLIB_INTERNAL_UINT_ID__FWD_H

namespace saklib
{
    namespace internal
    {
        template <typename T>
        class Unsigned_Integer_ID;

        using Uchar_ID = Unsigned_Integer_ID<unsigned char>;
        using Ushort_ID = Unsigned_Integer_ID<unsigned short>;
        using Uint_ID = Unsigned_Integer_ID<unsigned int>;
        using Ulong_ID = Unsigned_Integer_ID<unsigned long>;
        using Ulonglong_ID = Unsigned_Integer_ID<unsigned long long>;

        template <typename T>
        class Unsigned_Integer_ID_Factory;

        using Uchar_ID_Factory = Unsigned_Integer_ID_Factory<unsigned char>;
        using Ushort_ID_Factory = Unsigned_Integer_ID_Factory<unsigned short>;
        using Uint_ID_Factory = Unsigned_Integer_ID_Factory<unsigned int>;
        using Ulong_ID_Factory = Unsigned_Integer_ID_Factory<unsigned long>;
        using Ulonglong_ID_Factory = Unsigned_Integer_ID_Factory<unsigned long long>;
    } // namespace internal
} // namespace saklib

#endif // SAKLIB_INTERNAL_UINT_ID__FWD_H
