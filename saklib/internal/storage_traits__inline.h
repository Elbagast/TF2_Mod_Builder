#ifndef SAKLIB_INTERNAL_STORAGE_TRAITS__INLINE_H
#define SAKLIB_INTERNAL_STORAGE_TRAITS__INLINE_H

#ifndef SAKLIB_INTERNAL_STORAGE_TRAITS__FWD_H
#include "storage_traits.h"
#endif

#ifndef SAKLIB_INTERNAL_BAD_DATA_HANDLE_H
#include "exceptions/bad_data_handle.h"
#endif


//---------------------------------------------------------------------------
// Storage_Traits<T>
//---------------------------------------------------------------------------

// Interface
//============================================================

template <typename T>
typename saklib::internal::Storage_Traits<T>::return_type saklib::internal::Storage_Traits<T>::get_data_from_stored(stored_type& a_stored)
{
    return a_stored;
}

template <typename T>
typename saklib::internal::Storage_Traits<T>::const_return_type saklib::internal::Storage_Traits<T>::cget_data_from_stored(stored_type const& a_stored)
{
    return a_stored;
}

template <typename T>
typename saklib::internal::Storage_Traits<T>::return_type saklib::internal::Storage_Traits<T>::get_data_fail()
{
    throw Bad_Data_Handle();
}

template <typename T>
typename saklib::internal::Storage_Traits<T>::const_return_type saklib::internal::Storage_Traits<T>::cget_data_fail()
{
    throw Bad_Data_Handle();
}


//---------------------------------------------------------------------------
// Storage_Traits<T*>
//---------------------------------------------------------------------------

// Interface
//============================================================

template <typename T>
typename saklib::internal::Storage_Traits<T*>::return_type saklib::internal::Storage_Traits<T*>::get_data_from_stored(stored_type& a_stored)
{
    return a_stored.get();
}

template <typename T>
typename saklib::internal::Storage_Traits<T*>::const_return_type saklib::internal::Storage_Traits<T*>::cget_data_from_stored(stored_type const& a_stored)
{
    return a_stored.get();
}

template <typename T>
typename saklib::internal::Storage_Traits<T*>::return_type saklib::internal::Storage_Traits<T*>::get_data_fail()
{
    return nullptr;
}

template <typename T>
typename saklib::internal::Storage_Traits<T*>::const_return_type saklib::internal::Storage_Traits<T*>::cget_data_fail()
{
    return nullptr;
}


#endif // SAKLIB_INTERNAL_STORAGE_TRAITS__INLINE_H

