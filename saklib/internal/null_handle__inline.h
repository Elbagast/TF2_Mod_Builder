#ifndef SAKLIB_INTERNAL_NULL_HANDLE__INLINE_H
#define SAKLIB_INTERNAL_NULL_HANDLE__INLINE_H

#ifndef SAKLIB_INTERNAL_NULL_HANDLE_H
#include "null_handle.h"
#endif

//---------------------------------------------------------------------------
// Handle_Value_Type
//---------------------------------------------------------------------------

// Factory Functions
//============================================================
// constexpr
inline
saklib::internal::Null_Handle_Type saklib::internal::null_handle()
{
    return Null_Handle_Type();
}

//---------------------------------------------------------------------------
// Null_Handle_Type
//---------------------------------------------------------------------------

// Factory Functions
//============================================================
// constexpr
inline
saklib::internal::Handle_Value_Type saklib::internal::null_handle_value()
{
    return Null_Handle_Type::value;
}

#endif // SAKLIB_INTERNAL_NULL_HANDLE__INLINE_H

