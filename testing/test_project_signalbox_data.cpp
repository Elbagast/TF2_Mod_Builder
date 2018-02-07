#include "test_project_signalbox_data.hpp"

#include <sak/data_definitions.hpp>
#include <sak/class_definitions.hpp>
#include <sak/data.hpp>
#include <sak/handle.hpp>
#include <sak/tag.hpp>
#include <sak/abstract_project_signalbox.hpp>
#include <sak/project_signalbox_data.hpp>

#include <iostream>
#include <cassert>
#include <type_traits>

namespace sak
{
  namespace
  {

    template <typename...Args>
    class Project_Signalbox_Section_Imp;

    template <typename T>
    class Project_Signalbox_Section_Imp<T> :
        protected virtual Abstract_Signalbox<T>
    {
    public:
      using Class_Def = T;
      using Typestring_Type =  typename Class_Def::Typestring_Type;

      Project_Signalbox_Section_Imp() = default;
      ~Project_Signalbox_Section_Imp() override = default;

      void do_message(Handle<T> const& a_handle, char const* a_funcname)
      {
        std::cout << "Project_Signalbox_Imp<T>::\"" << a_funcname
                  << "\": add=\"" << this
                  << "\" T=\"" << Typestring_Type::data()
                  <<"\" id=\"" << a_handle.id()
                  << "\""
                  << std::endl;
      }

      void do_message(Handle<T> const& a_handle, std::size_t a_index, char const* a_funcname)
      {
        std::cout << "Project_Signalbox_Imp<T>::\"" << a_funcname
                  << "\": add=|" << this
                  << "\" T=\"" << Typestring_Type::data()
                  <<"\" id=\"" << a_handle.id()
                  <<"\" index=\"" << a_index
                  << "\""
                  << std::endl;
      }

      // When a handle has its data changed, this is called.
      void changed(Handle<T> const& a_handle) override
      {
        do_message(a_handle, "changed()");
      }
      // When a handle has its name changed, this is called.
      void changed_name(Handle<T> const& a_handle) override
      {
        do_message(a_handle, "changed_name()");
      }
      // When a handle has its data changed in a specific place, this is called.
      // a_section == 0 denotes the name and may have special logic requirements.
      void changed_at(Handle<T> const& a_handle, std::size_t a_section) override
      {
        do_message(a_handle, a_section, "changed_at()");
      }
      // When a handle has been added, this is called.
      void added(Handle<T> const& a_handle) override
      {
        do_message(a_handle, "added()");
      }
      // When a handle has been removed, this is called.
      void removed(Handle<T> const& a_handle) override
      {
        do_message(a_handle, "removed()");
      }
      // When a handle editor is to be opened, this is called.
      void requests_editor(Handle<T> const& a_handle) override
      {
        do_message(a_handle, "requests_editor()");
      }
      // When focus is changed to be on a handle, call this
      void requests_focus(Handle<T> const& a_handle) override
      {
        do_message(a_handle, "requests_focus()");
      }
    };

    template <typename T, typename R, typename...Args>
    class Project_Signalbox_Section_Imp<T,R,Args...> :
        protected Project_Signalbox_Section_Imp<T>,
        protected Project_Signalbox_Section_Imp<R,Args...>
    {
    public:
      using Class_Def = T;
      using Typestring_Type =  typename Class_Def::Typestring_Type;

      Project_Signalbox_Section_Imp() = default;
      ~Project_Signalbox_Section_Imp() override = default;

    };

    template <typename T, typename...Args>
    class Project_Signalbox_Imp :
        public virtual Abstract_Signalbox<T,Args...>,
        protected Project_Signalbox_Section_Imp<T,Args...>
    {
    public:
      Project_Signalbox_Imp() = default;
      ~Project_Signalbox_Imp() override = default;

    };

    using Project_Signalbox = Project_Signalbox_Imp<File_Definition,Texture_Definition,Material_Definition>;




    template <typename T>
    void do_project_signalbox_test(sak::Project_Signalbox_Data& a_project)
    {
      using namespace sak;

      std::cout << "-------------------------" << std::endl;

      Handle<T> l_handle{};

      a_project.changed(l_handle);
      a_project.changed_name(l_handle);
      a_project.changed_at(l_handle, 0u);
      a_project.added(l_handle);
      a_project.removed(l_handle);
      a_project.requests_editor(l_handle);
      a_project.requests_focus(l_handle);

      std::cout << "-------------------------" << std::endl;
    }
  }

  class A{};
  class B{};
  class C{};
  class D{};
}


void sak::testing::test_project_signalbox_data()
{
  std::cout << "Testing sak::Project_Signalbox_Data" << std::endl;
  std::cout << "==============================" << std::endl;

  using namespace sak;

  Project_Signalbox_Data l_psd{};

  Project_Signalbox l_ps1{};
  Project_Signalbox l_ps2{};
  Project_Signalbox l_ps3{};

  std::cout << "sizeof(void*)                       = " << sizeof(void*) <<  std::endl;
  std::cout << "sizeof(Abstract_Signalbox<A>)       = " << sizeof(Abstract_Signalbox<A>) <<  std::endl;
  std::cout << "sizeof(Abstract_Signalbox<A,B>)     = " << sizeof(Abstract_Signalbox<A,B>) <<  std::endl;
  std::cout << "sizeof(Abstract_Signalbox<A,B,C>)   = " << sizeof(Abstract_Signalbox<A,B,C>) <<  std::endl;
  std::cout << "sizeof(Abstract_Signalbox<A,B,C,D>) = " << sizeof(Abstract_Signalbox<A,B,C,D>) <<  std::endl;

  std::cout << "sizeof(Abstract_Project_Signalbox) = " << sizeof(Abstract_Project_Signalbox) <<  std::endl;
  std::cout << "sizeof(Project_Signalbox) = " << sizeof(Project_Signalbox) <<  std::endl;

  std::cout << "add some signalboxes:" << std::endl;
  std::cout << "address = " << dynamic_cast<Project_Signalbox*>(&l_ps1) <<  std::endl;
  std::cout << "address = " << dynamic_cast<Project_Signalbox*>(&l_ps2) << std::endl;
  std::cout << "address = " << dynamic_cast<Project_Signalbox*>(&l_ps3) << std::endl;

  l_psd.add_signalbox(nullptr);
  l_psd.add_signalbox(&l_ps1);
  l_psd.add_signalbox(&l_ps2);
  l_psd.add_signalbox(&l_ps3);

  do_project_signalbox_test<File_Definition>(l_psd);
  do_project_signalbox_test<Texture_Definition>(l_psd);

  std::cout << "remove some signalboxes:" << std::endl;
  std::cout << "address = " << dynamic_cast<Project_Signalbox*>(&l_ps2) << std::endl;
  std::cout << "address = " << dynamic_cast<Project_Signalbox*>(&l_ps3) << std::endl;

  l_psd.remove_signalbox(nullptr);
  l_psd.remove_signalbox(&l_ps2);
  l_psd.remove_signalbox(&l_ps3);

  do_project_signalbox_test<File_Definition>(l_psd);
  do_project_signalbox_test<Texture_Definition>(l_psd);
  do_project_signalbox_test<Material_Definition>(l_psd);

  std::cout << "==============================" << std::endl;
}
