#include "project_signalling_data.hpp"

#include "data_definitions.hpp"
#include "class_definitions.hpp"
#include "data.hpp"
#include "handle.hpp"

namespace
{
  void test()
  {
    using namespace sak;

    Project_Signalling_Data* l_psdp{nullptr};
    if (l_psdp)
    {
      l_psdp->add_default(File_Tag{});
    }

    Project_Signalling_Data l_psd{};
    l_psd.add_default(File_Tag{});

  }
}
