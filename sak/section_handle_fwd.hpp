#ifndef SAK_SECTION_HANDLE_FWD_HPP
#define SAK_SECTION_HANDLE_FWD_HPP

#ifndef FLAMINGO_HANDLE_FWD_HPP
#include <flamingo/handle_fwd.hpp>
#endif

#ifndef SAK_SECTION_DATA_FWD_HPP
#include "section_data_fwd.hpp"
#endif

namespace sak
{
  template <typename T>
  using Section_Manager = flamingo::manager<T>;

  template <typename T>
  using Section_Handle = flamingo::handle<T>;


  using File_Manager = Section_Manager<File_Data>;
  using File_Handle = Section_Handle<File_Data>;

  using Texture_Manager = Section_Manager<Texture_Data>;
  using Texture_Handle = Section_Handle<Texture_Data>;

} // namespace sak

#endif // SAK_SECTION_HANDLE_FWD_HPP
