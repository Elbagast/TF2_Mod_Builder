#ifndef SAK_HANDLE_FACTORY_HPP
#define SAK_HANDLE_FACTORY_HPP

#ifndef SAK_HANDLE_FACTORY_FWD_HPP
#include "handle_factory_fwd.hpp"
#endif

#ifndef SAK_HANDLE_FWD_HPP
#include "handle_fwd.hpp"
#endif

#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Handle_Factory<T_Class_Def>
  //---------------------------------------------------------------------------
  // Object that makes Handle<T> by encapsulating the production of id values.

  template <typename T_Class_Def>
  class Handle_Factory
  {
  public:
    // Typedefs
    //============================================================
    using Element_Type = typename Handle<T_Class_Def>::Element_Type;
    using ID_Type = std::size_t;

    // Special 6
    //============================================================
    Handle_Factory() noexcept;
    ~Handle_Factory() noexcept;

    Handle_Factory(Handle_Factory const& a_other) noexcept;
    Handle_Factory& operator=(Handle_Factory const& a_other) noexcept;

    Handle_Factory(Handle_Factory && a_other) noexcept;
    Handle_Factory& operator=(Handle_Factory && a_other) noexcept;

    // Interface
    //============================================================
    // Explicitly make a null handle.
    static Handle<T_Class_Def> make_null_handle();

    // Make a new handle with the supplied data. This data will be associated
    // with the returned handle's id value until all handles referencing it
    // are destroyed.
    Handle<T_Class_Def> make_handle(std::shared_ptr<Element_Type>&& a_data);

  private:
    ID_Type m_next_id;
  };
}


#endif // SAK_HANDLE_FACTORY_HPP
